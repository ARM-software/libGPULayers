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
import enum
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
    Type information for any per-workload sample JSON message.
    '''
    type: str
    counters: list[dict[str, Union[int, float]]]
    labels: list[str]


class FrameMessage(TypedDict):
    '''
    Type information for a per-frame sample JSON message.
    '''
    type: str
    counters: list[dict[str, Union[int, float]]]
    frame: int


class SampleMode(enum.Enum):
    '''
    Type of sampling detected.
    '''
    PER_WORKLOAD = 0
    PER_FRAME = 1


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

        # Sample mode is detected on the fly when we get our first data
        self.sample_mode = SampleMode.PER_WORKLOAD

        self.frame_id: Optional[int] = None

        self.table_header: Optional[list[str]] = None
        self.table_data: list[list[str]] = []

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
        self.table_header = None
        self.table_data.clear()

    def handle_end_frame(self, message: EndFrameMessage):
        '''
        Handle an end_frame message.

        Args:
            message: The decoded JSON.
        '''
        # Message contains nothing we need
        del message

        assert self.frame_id is not None
        assert self.table_header is not None

        # Emit the CSV file
        print(f'Generating CSV for frame {self.frame_id}')
        path = os.path.join(self.base_dir, f'frame_{self.frame_id:05d}.csv')
        with open(path, 'w', newline='') as handle:
            writer = csv.writer(handle)
            writer.writerow(self.table_header)
            writer.writerows(self.table_data)

        # Reset the state
        self.frame_id = None
        self.table_header = None
        self.table_data.clear()

    def create_workload_header(self, message: WorkloadMessage):
        '''
        Create a table header row from a workload sample.

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

        self.table_header = columns

    def create_workload_data(self, message: WorkloadMessage):
        '''
        Create a table data row from a workload sample.

        Args:
            message: The decoded JSON.
        '''
        assert self.frame_id is not None
        assert self.table_header is not None

        columns: list[str] = []

        columns.append(str(len(self.table_data)))
        columns.append(message['type'])

        for counter in message['counters']:
            value = list(counter.values())[0]
            columns.append(f'{value:0.2f}')
        columns.append('|'.join(message['labels']))

        self.table_data.append(columns)

    def handle_workload_sample(self, message: WorkloadMessage):
        '''
        Handle a workload sample message.

        Args:
            message: The decoded JSON.
        '''
        if not self.table_header:
            self.create_workload_header(message)

        self.create_workload_data(message)

    def create_frame_header(self, message: FrameMessage):
        '''
        Create a table header row from a frame sample.
        Args:
            message: The decoded JSON.
        '''
        columns = []

        columns.append('Frame ID')
        for counter in message['counters']:
            key = list(counter.keys())[0]
            columns.append(key)

        self.table_header = columns

    def create_frame_data(self, message: FrameMessage):
        '''
        Create a table data row from a frame sample.

        Args:
            message: The decoded JSON.
        '''
        assert self.table_header is not None

        columns: list[str] = []

        columns.append(f'{self.frame_id}')

        for counter in message['counters']:
            value = list(counter.values())[0]
            columns.append(f'{value:0.2f}')

        self.table_data.append(columns)

    def handle_frame_sample(self, message: FrameMessage):
        '''
        Handle a frame message.

        Args:
            message: The decoded JSON.
        '''
        self.frame_id = message['frame']

        if not self.table_header:
            self.create_frame_header(message)

        assert self.table_header is not None
        self.create_frame_data(message)

        print(f'Updating CSV for frame {self.frame_id}')
        path = os.path.join(self.base_dir, f'capture.csv')
        with open(path, 'w', newline='') as handle:
            writer = csv.writer(handle)
            writer.writerow(self.table_header)
            writer.writerows(self.table_data)

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
        elif payload['type'] == 'frame':
            self.handle_frame_sample(payload)
        else:
            self.handle_workload_sample(payload)
