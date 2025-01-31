# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024-2025 Arm Limited
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the 'Software'), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------

'''
This module implements the server-side communications module that can accept
client connections from a layer driver, and dispatch messages to registered
service handler in the server.

This module currently only accepts a single connection at a time and message
handling is synchronous inside the server. It is therefore not possible to
implement pseudo-host-driven event loops if the layer is using multiple
services concurrently - this needs threads per service.
'''

import enum
import socket
import struct
from typing import Any, Optional


class MessageType(enum.Enum):
    '''
    The received message type.

    NOTE: Values defined by the protocol; do not change.

    Attributes:
        TX_ASYNC: Message is an async client transmit, no response allowed.
        TX: Message is a sync client transmit, no response allowed.
        TX_RX: Message is a sync client transmit, response required.
    '''
    TX_ASYNC = 0
    TX = 1
    TX_RX = 2


class Message:
    '''
    A decoded message header for a received message.

    NOTE: Fields and sizes defined by the protocol; do not change.

    Attributes:
        message_type: The type of the message sent by the client.
        endpoint_id: The endpoint service address.
        message_id: The message cookie to use in a TX_RX response.
        payload_size: The size of the payload in bytes.
        payload: The data payload.
    '''

    HEADER_LEN = 14

    def __init__(self, header: bytes):
        '''
        Populate a new message based on the header info.

        Args:
            header: The header byte stream.
        '''
        assert len(header) == Message.HEADER_LEN, 'Header length is incorrect'

        fields = struct.unpack('<BBQL', header)

        self.message_type = MessageType(fields[0])
        self.endpoint_id = int(fields[1])
        self.message_id = int(fields[2])
        self.payload_size = int(fields[3])
        self.payload = b''

    def add_payload(self, data: bytes) -> None:
        '''
        Attach a payload to this message.

        Args:
            Data: The payload byte stream.
        '''
        self.payload = data


class Response:
    '''
    An encoded message header for a message to be transmitted.

    NOTE: Fields and sizes defined by the protocol; do not change.

    Attributes:
        message_type: The type of the message sent by the client.
        message_id: The message cookie to use in a TX_RX response.
        payload_size: The size of the payload in bytes.
    '''

    def __init__(self, message: Message, data: bytes):
        '''
        Populate a message header for a response.

        Args:
            message: The message we are responding to.
            data: The response payload byte stream.
        '''
        self.message_type = message.message_type
        self.message_id = message.message_id
        self.payload_size = len(data)

    def get_header(self) -> bytes:
        '''
        Get the header byte stream for this response.

        Returns:
            The response header byte stream.
        '''
        return struct.pack('<BBQL', self.message_type.value, 0,
                           self.message_id, self.payload_size)


class ClientDropped(Exception):
    '''
    Exception representing loss of Client connection.
    '''


class CommsServer:
    '''
    Class listening for client connection from a layer and handling messages.

    This implementation is designed to run in a thread, so has a run method
    that will setup and listen on the server socket.q

    This implementation only handles a single layer connection at a time, but
    can handle multiple connections serially without restarting.

    This implementation handles all messages synchronously, passing a message
    to a microservice and sending any resulting response before handling the
    next message.

    Attributes:
        port: The port the server listens on, or 0 for auto-assign.
        endpoints: The mapping of addresses to registered microservices.
        sockl: The listener socket, or None if not listening.
        sockd: The client data socket, or None if no client connected.
        shutdown Flag fro tracking shutdown status.
    '''

    def __init__(self, port: int, verbose: bool = False):
        '''
        Construct, but do not start, a server instance.

        Args:
            port: The local TCP/IP port to listen on.
            verbose: Should this use verbose logging?
        '''
        self.verbose = verbose
        self.endpoints = {}  # type: dict[int, Any]
        self.register_endpoint(self)

        self.shutdown = False
        self.sockd = None  # type: Optional[socket.socket]

        self.sockl = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sockl.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        # Set up the listening socket
        self.sockl.bind(('localhost', port))
        self.sockl.listen(1)

        # Work out which port was assigned if not user-defined
        self.port = self.sockl.getsockname()[1]

    def register_endpoint(self, endpoint: Any) -> int:
        '''
        Register a new service endpoint with the server.

        Args:
            endpoint: The endpoint object that can handle messages.

        Returns:
            The assigned endpoint address.
        '''
        endpoint_id = len(self.endpoints)
        self.endpoints[endpoint_id] = endpoint
        return endpoint_id

    def get_service_name(self) -> str:
        '''
        Get the name of the self-hosted registry microservice.

        Returns:
            The name of the service endpoint.
        '''
        return 'registry'

    def handle_message(self, message: Message) -> Optional[bytes]:
        '''
        Handle a message in the self-hosted registry microservice.

        Returns:
            The response to the message.
        '''
        # Message is unused for this microservice - keep pylint happy
        del message

        data = []
        for endpoint_id, endpoint in self.endpoints.items():
            name = endpoint.get_service_name().encode('utf-8')
            data.append(struct.pack('<BL', endpoint_id, len(name)))
            data.append(name)

        return b''.join(data)

    def run(self) -> None:
        '''
        Enter server connection handler run loop.
        '''
        # Accept a new client connection and assign a data socket
        while not self.shutdown:
            if self.verbose:
                print('Waiting for client connection')
            try:
                self.sockd, _ = self.sockl.accept()
                if self.verbose:
                    print('  + Client connected')

                self.run_client()

                if self.verbose:
                    print('  + Client disconnected')
                self.sockd.close()
                self.sockd = None

            except ClientDropped:
                if self.verbose:
                    print('  + Client disconnected')
                if self.sockd:
                    self.sockd.close()
                    self.sockd = None

            except OSError:
                continue

        self.sockl.close()

    def run_client(self) -> None:
        '''
        Enter client message handler run loop.

        Raises:
            ClientDropped: The client disconnected from the socket.
        '''
        while not self.shutdown:
            # Read the header
            data = self.receive_data(Message.HEADER_LEN)
            message = Message(data)

            # Read the payload if there is one
            if message.payload_size:
                data = self.receive_data(message.payload_size)
                message.add_payload(data)

            # Dispatch to a service handler
            endpoint = self.endpoints[message.endpoint_id]
            response = endpoint.handle_message(message)

            # Send a response for all TX_RX messages
            if message.message_type == MessageType.TX_RX:
                header = Response(message, response)
                self.send_data(header.get_header())
                self.send_data(response)

    def stop(self) -> None:
        '''
        Shut down the server.
        '''
        self.shutdown = True

        if self.sockl is not None:
            self.sockl.close()

        if self.sockd is not None:
            self.sockd.shutdown(socket.SHUT_RDWR)

    def receive_data(self, size: int) -> bytes:
        '''
        Fetch a fixed size packet from the socket.

        Args:
            size: The length of the packet in bytes.

        Returns:
            The packet data.

        Raises:
            ClientDropped: The client disconnected from the socket.
        '''
        assert self.sockd is not None

        data = b''
        while len(data) < size:
            new_data = self.sockd.recv(size - len(data))
            if not new_data:
                raise ClientDropped()
            data = data + new_data

        return data

    def send_data(self, data: bytes) -> None:
        '''
        Send a fixed size packet to the socket.

        Args:
            data: The binary data to send.

        Raises:
            ClientDropped: The client disconnected from the socket.
        '''
        assert self.sockd is not None

        while len(data):
            sent_bytes = self.sockd.send(data)
            if not sent_bytes:
                raise ClientDropped()
            data = data[sent_bytes:]
