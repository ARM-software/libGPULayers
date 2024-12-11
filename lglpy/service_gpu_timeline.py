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
# implements a basic message endpoint for testing.

from lglpy.server import Message
import json
import struct

class GPUTimelineService:

    def __init__(self):
        self.frame = {
            "frame": 0,
            "workloads": [

            ]
        }

        # TODO: Make file name configurable
        self.fileHandle = open('malivision.gputl', 'wb')

    def get_service_name(self) -> str:
        return 'GPUTimeline'

    def handle_frame(self, msg):
        print(json.dumps(self.frame, indent=4))

        # Write frame packet to the file
        lastFrame = json.dumps(self.frame).encode('utf-8')
        length = struct.pack('<I', len(lastFrame))

        self.fileHandle.write(length)
        self.fileHandle.write(lastFrame)

        # Reset the local frame state for the next frame
        self.frame = {
            'frame': msg['fid'],
            'workloads': []
        }

    def handle_renderpass(self, msg):
        # Find the last workload
        lastRenderPass = None
        if len(self.frame['workloads']):
            lastWorkload = self.frame['workloads'][-1]
            if lastWorkload['type'] == 'renderpass':
                lastRenderPass = lastWorkload

        # Continuation
        if lastRenderPass and lastRenderPass['tid'] == msg['tid']:
            lastRenderPass['drawCallCount'] += msg['drawCallCount']
        # New render pass
        else:
            self.frame['workloads'].append(msg)

    def handle_message(self, message: Message):
        payload = message.payload.decode('utf-8')
        parsedPayload = json.loads(payload)

        payloadType = parsedPayload['type']

        if payloadType == 'frame':
            self.handle_frame(parsedPayload)

        elif payloadType == 'renderpass':
            self.handle_renderpass(parsedPayload)

        else:
            assert False, f'Unknown payload type {payloadType}'

        return None
