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
handles record preprocessing and serializing the resulting GPU Profile layer.
'''

import csv
import json
import os
from typing import Any, Optional, TypedDict, Union

from lglpy.comms.server import Message


class StartFrameMessage(TypedDict):
    '''
    Type information for a start_frame JSON message.
    '''
    type: str
    frame: int


class EndFrameMessage(TypedDict):
    '''
    Type information for an end_frame JSON message.
    '''
    type: str


class WorkloadMessage(TypedDict):
    '''
    Type information for any workload JSON message.
    '''
    type: str
    counters: list[dict[str, Union[int, float]]]
    labels: list[str]


class GPUProfileService:
    '''
    A service for handling network comms from the layer_gpu_profile layer.
    '''

    def __init__(self, dir_path: str, verbose: bool = False):
        '''
        Initialize the profile service.

        Args:
            dir_path: Directory to write on the filesystem
            verbose: Should this use verbose logging?
        '''
        self.base_dir = dir_path

        self.frame_id: Optional[int] = None
        self.frame_header: Optional[list[str]] = None
        self.frame_data: Optional[list[list[str]]] = None

        os.makedirs(dir_path, exist_ok=True)

    def get_service_name(self) -> str:
        '''
        Get the service endpoint name.

        Returns:
            The endpoint name.
        '''
        return 'GPUProfile'

    def handle_start_frame(self, message: StartFrameMessage):
        '''
        Handle a start_frame message.

        Args:
            message: The decoded JSON.
        '''
        self.frame_id = message["frame"]
        self.frame_header = None
        self.frame_data = []

    def handle_end_frame(self, message: EndFrameMessage):
        '''
        Handle an end_frame message.

        Args:
            message: The decoded JSON.
        '''
        # Message contains nothing we need
        del message

        assert self.frame_id is not None
        assert self.frame_header is not None
        assert self.frame_data is not None

        # Emit the CSV file
        print(f'Generating CSV for frame {self.frame_id}')
        path = os.path.join(self.base_dir, f'frame_{self.frame_id:05d}.csv')
        with open(path, 'w', newline='') as handle:
            writer = csv.writer(handle)
            writer.writerow(self.frame_header)
            writer.writerows(self.frame_data)

        # Reset the state
        self.frame_id = None
        self.frame_header = None
        self.frame_data = None

    def create_workload_header(self, message: WorkloadMessage):
        '''
        Create a table header row from a workload.

        Args:
            message: The decoded JSON.
        '''
        columns = []

        columns.append('Index')
        columns.append('Workload type')
        for counter in message['counters']:
            key = list(counter.keys())[0]
            columns.append(key)
        columns.append('Label')

        self.frame_header = columns

    def create_workload_data(self, message: WorkloadMessage):
        '''
        Create a table data row from a workload.

        Args:
            message: The decoded JSON.
        '''
        assert self.frame_id is not None
        assert self.frame_header is not None
        assert self.frame_data is not None

        columns: list[str] = []

        columns.append(str(len(self.frame_data)))
        columns.append(message['type'])

        for counter in message['counters']:
            value = list(counter.values())[0]
            columns.append(f'{value:0.2f}')
        columns.append('|'.join(message['labels']))

        self.frame_data.append(columns)

    def handle_workload(self, message: WorkloadMessage):
        '''
        Handle a workload message.

        Args:
            message: The decoded JSON.
        '''
        if not self.frame_header:
            self.create_workload_header(message)

        self.create_workload_data(message)

    def handle_message(self, message: Message) -> None:
        '''
        Handle a service request from a layer.

        Note that this service only expects pushed TX or TX_ASYNC messages, so
        never provides a response.
        '''
        encoded_payload = message.payload.decode('utf-8')
        payload = json.loads(encoded_payload)

        if payload['type'] == 'start_frame':
            self.handle_start_frame(payload)
        elif payload['type'] == 'end_frame':
            self.handle_end_frame(payload)
        else:
            self.handle_workload(payload)
