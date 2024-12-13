# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024 Arm Limited
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------

# This module implements the server-side communications module that can
# accept client connections from the layer drivers, and dispatch them to
# handlers in the server.
#
# This module currently only accepts a single connection from a layer at a time
# and runs in the context of the calling thread, so if it needs to run in the
# background the user must create a new thread to contain it. It is therefore
# not possible to implement pseudo-host-driven event loops if the layer is
# using multiple services concurrently - this needs threads per service.

import enum
import socket
import struct


class MessageType(enum.Enum):
    '''
    The received message type.
    '''
    TX_ASYNC = 0
    TX = 1
    TX_RX = 2


class Message:
    '''
    A decoded message header packet.

    See the MessageHeader struct in comms_message.hpp for binary layout.
    '''

    def __init__(self, header):
        assert len(header) == 14, 'Header length is incorrect'

        fields = struct.unpack('<BBQL', header)

        self.message_type = MessageType(fields[0])
        self.endpoint_id = fields[1]
        self.message_id = fields[2]
        self.payload_size = fields[3]
        self.payload = b''

    def add_payload(self, data):
        self.payload = data

class Response:
    '''
    An encoded message header packet.

    See the MessageHeader struct in comms_message.hpp for binary layout.
    '''

    def __init__(self, message, data):

        self.message_type = message.message_type
        self.message_id = message.message_id
        self.payload_size = len(data)

    def get_header(self):
        data = struct.pack('<BBQL', self.message_type.value, 0,
                           self.message_id, self.payload_size)
        return data

class CommsServer:

    def __init__(self, port: int):
        self.port = port
        self.endpoints = {}
        self.register_endpoint(self)

        self.shutdown = False
        self.listen_sockfd = None
        self.data_sockfd = None

    def get_service_name(self) -> str:
        return 'registry'

    def register_endpoint(self, endpoint) -> int:
        endpoint_id = len(self.endpoints)
        self.endpoints[endpoint_id] = endpoint
        return endpoint_id

    def handle_message(self, message: Message):
        data = []
        for endpoint_id, endpoint in self.endpoints.items():
            name = endpoint.get_service_name().encode('utf-8')
            data.append(struct.pack('<BL', endpoint_id, len(name)))
            data.append(name)

        return b''.join(data)

    def run(self):
        listen_sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        listen_sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        listen_sockfd.bind(('localhost', self.port))
        listen_sockfd.listen(1)

        self.listen_sockfd = listen_sockfd

        # Accept connections from outside
        while not self.shutdown:
            print('Waiting for client connection')
            try:
                sockfd, _ = listen_sockfd.accept()
            except OSError:
                continue

            self.data_sockfd = sockfd
            print('  + Client connected')

            while not self.shutdown:
                # Read the header
                data = self.receive_data(sockfd, 14)
                if not data:
                    break
                message = Message(data)

                if message.payload_size:
                    # Read the payload
                    data = self.receive_data(sockfd, message.payload_size)
                    if not data:
                        break
                    message.add_payload(data)

                # Dispatch to a handler
                endpoint = self.endpoints[message.endpoint_id]
                response = endpoint.handle_message(message)

                # Send a response for all TX_RX messages
                if message.message_type == MessageType.TX_RX:
                    header = Response(message, response)
                    sent = self.send_data(sockfd, header.get_header())
                    if not sent:
                        break
                    sent = self.send_data(sockfd, response)
                    if not sent:
                        break

            sockfd.close()
            self.data_sockfd = None

        listen_sockfd.close()
        self.listen_sockfd = None

    def stop(self):
        self.shutdown = True

        if self.listen_sockfd is not None:
            self.listen_sockfd.close()

        if self.data_sockfd is not None:
            self.data_sockfd.shutdown(socket.SHUT_RDWR)

    def receive_data(self, sockfd, byte_count):
        data = b''

        while len(data) < byte_count:
            new_data = sockfd.recv(byte_count - len(data))
            if not new_data:
                print("  - Client disconnected")
                return None
            data = data + new_data

        return data

    def send_data(self, sockfd, data):
        while len(data):
            sent_bytes = sockfd.send(data)
            if not sent_bytes:
                print("  - Client disconnected")
                return False
            data = data[sent_bytes:]

        return True
