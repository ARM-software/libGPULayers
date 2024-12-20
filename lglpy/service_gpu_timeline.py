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

# This module implements the server-side communications module service that
# handles record preprocessing and serializing GPU Timeline layer messages to
# file on the host.

import json
import struct
from typing import Any

from lglpy.server import Message


class GPUTimelineService:

    def __init__(self):
        '''
        Initialize the timeline service.

        Returns:
            The endpoint name.
        '''
        # Create a default frame record
        self.frame = {
            "frame": 0,
            "workloads": []
        }

        # TODO: Make file name configurable
        self.file_handle = open('malivision.gputl', 'wb')

    def get_service_name(self) -> str:
        '''
        Get the service endpoint name.

        Returns:
            The endpoint name.
        '''
        return 'GPUTimeline'

    def handle_frame(self, msg: Any) -> None:
        '''
        Handle a frame boundary workload.

        This will write the current frame record to the output file, and then
        reset the frame tracker ready for the next frame.

        Args:
            msg: The Python decode of a JSON payload.
        '''
        # Write frame packet to the file
        last_frame = json.dumps(self.frame).encode('utf-8')
        length = struct.pack('<I', len(last_frame))

        self.file_handle.write(length)
        self.file_handle.write(last_frame)

        # Reset the local frame state for the next frame
        next_frame = msg['fid']
        self.frame = {
            'frame': next_frame,
            'workloads': []
        }

        if next_frame % 100 == 0:
            print(f'Starting frame {next_frame} ...')

    def handle_render_pass(self, msg: Any) -> None:
        '''
        Handle a render pass workload.

        Render passes may generate multiple messages if suspended and resumed
        when using Vulkan 1.3 dynamic render passes, so merge those into a
        single workload.

        Args:
            msg: The Python decode of a JSON payload.
        '''
        # Find the last workload
        last_render_pass = None
        if len(self.frame['workloads']):
            last_workload = self.frame['workloads'][-1]
            if last_workload['type'] == 'renderpass':
                last_render_pass = last_workload

        # If this is a continuation then merge records
        if last_render_pass and (last_render_pass['tid'] == msg['tid']):
            # Don't accumulate if tagID is flagged as ambiguous
            if last_render_pass['drawCallCount'] != -1:
                last_render_pass['drawCallCount'] += msg['drawCallCount']

        # Otherwise this is a new record
        else:
            self.frame['workloads'].append(msg)

    def handle_generic(self, msg: Any) -> None:
        '''
        Handle a generic workload that needs no special handling.

        Args:
            msg: The Python decode of a JSON payload.
        '''
        self.frame['workloads'].append(msg)

    def handle_message(self, message: Message) -> None:
        '''
        Handle a service request from a layer.

        Note that this service only expects pushed TX or TX_ASYNC messages, so
        never provides a response.
        '''
        encoded_payload = message.payload.decode('utf-8')
        payload = json.loads(encoded_payload)

        generic_payload_types = {
            'dispatch',
            'tracerays',
            'imagetransfer',
            'buffertransfer'
        }

        payload_type = payload['type']

        if payload_type == 'frame':
            self.handle_frame(payload)

        elif payload_type == 'renderpass':
            self.handle_render_pass(payload)

        elif payload_type in generic_payload_types:
            self.handle_generic(payload)

        else:
            assert False, f'Unknown payload type {payload_type}'
