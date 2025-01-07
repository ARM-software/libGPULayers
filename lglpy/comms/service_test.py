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
This module implements the server-side communications module service that
implements a basic message endpoint for comms module unit testing.
'''

from typing import Optional

from lglpy.comms.server import Message, MessageType


class TestService:
    '''
    A simple service used for testing.
    '''

    def get_service_name(self) -> str:
        '''
        Get the service endpoint name.

        Returns:
            The endpoint name.
        '''
        return 'test'

    def handle_message(self, message: Message) -> Optional[bytes]:
        '''
        Handle a service request from a layer.

        Returns:
            The response if message is a TX_RX message, None otherwise.
        '''
        # Print received payloads
        payload = message.payload.decode('utf-8')
        print(f'{message.message_type.name}: {payload} ({len(payload)} bytes)')

        # Reverse payloads for response to TX_RX messages
        if message.message_type == MessageType.TX_RX:
            response = payload[::-1]
            return response.encode('utf-8')

        return None
