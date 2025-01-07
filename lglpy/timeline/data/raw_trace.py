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
TODO
'''
import collections
import struct
import json

from lglpy.timeline.data.processed_trace import *

import lglpy.timeline.protos.perfetto.trace.trace_pb2 as trace_pb2


class PerfettoConfig:
    '''
    This class persists settings found in the Perfetto trace that
    are needed to fully decode later event packets in the trace.
    '''

    # Known Perfetto streams and their remapped names
    STREAM_REMAP = {
        "compute": GPUStreamID.COMPUTE,
        "non-fragment": GPUStreamID.NONFRAGMENT,
        "fragment": GPUStreamID.FRAGMENT,
        "binning": GPUStreamID.BINNING,
        "main": GPUStreamID.MAIN,
        "transfer": GPUStreamID.TRANSFER
    }

    # Known Perfetto render stages and their remapped names
    STAGE_REMAP = {
        "clear image": GPUStageID.IMAGE_TRANSFER,
        "copy image": GPUStageID.IMAGE_TRANSFER,
        "blit image": GPUStageID.IMAGE_TRANSFER,
        "generate mipmap": GPUStageID.IMAGE_TRANSFER,
        "copy buffer": GPUStageID.BUFFER_TRANSFER,
        "fill buffer": GPUStageID.BUFFER_TRANSFER,
        "compute": GPUStageID.COMPUTE,
        "advanced geometry": GPUStageID.ADVANCED_GEOMETRY,
        "vertex": GPUStageID.VERTEX,
        "fragment": GPUStageID.FRAGMENT,
        "binning": GPUStageID.BINNING,
        "main": GPUStageID.MAIN,
    }

    def __init__(self):
        '''
        Initialize an empty configuration to be populated incrementally.
        '''
        # Clock sync information
        self.clock_sync = {}

        # Interned data references
        self.raw_iids = {}
        self.stream_iids = {}
        self.stage_iids = {}

    def add_interned_data(self, spec):
        '''
        Add raw interned string data which we can reference later.
        '''
        iid = spec.iid if spec.HasField('iid') else 0
        name = spec.name if spec.HasField('name') else None
        assert iid and name, 'ERROR: Interned data missing expected fields'
        self.raw_iids[iid] = name

    def add_clock_sync_data(self, event):
        '''
        Add raw clock sync data which we can use to correct timing later.
        '''
        root_clock = 5
        root_time = None

        # Find the root clock
        cs = event.clock_snapshot
        for clock in cs.clocks:
            assert clock.HasField('clock_id')
            assert clock.HasField('timestamp')
            assert not clock.HasField('unit_multiplier_ns') or \
                   not clock.unit_multiplier_ns

            if clock.clock_id == root_clock:
                root_time = clock.timestamp

        assert root_time is not None

        # Compute the correction sync deltas
        for clock in cs.clocks:
            correction = clock.timestamp - root_time
            self.clock_sync[clock.clock_id] = correction

    def get_event_time(self, event):
        '''
        Get the event time in a unified clock domain applying clock sync.
        '''
        clock_id = 6
        if event.HasField('timestamp_clock_id'):
            clock_id = event.timestamp_clock_id

        return event.timestamp - self.clock_sync[clock_id]

    def replace_interned_stream(self, event):
        '''
        Replaced interned data stream references with the real data.
        '''
        # Rewrite the hardware stream
        stream = event.stream

        # Interned ID has been found and remapped already
        if stream in self.stream_iids:
            event.stream = self.stream_iids[stream]

        # Interned ID exists but has not yet been remapped
        elif stream in self.raw_iids:
            raw_name = self.raw_iids[stream]

            assert raw_name in self.STREAM_REMAP, \
                   f'ERROR: Unknown stream remap: {raw_name}'

            self.stream_iids[stream] = self.STREAM_REMAP[raw_name]
            event.stream = self.stream_iids[stream]

        # Interned ID does not exist
        else:
            assert False, 'ERROR: Unknown stream interned data ID'

    def replace_interned_stage(self, event):
        '''
        Replaced interned data stage references with the real data.
        '''
        # Rewrite the hardware stage
        stage = event.stage

        # Interned ID has been found and remapped already
        if stage in self.stage_iids:
            event.stage = self.stage_iids[stage]

        # Interned ID exists by has not yet been remapped
        elif stage in self.raw_iids:
            raw_name = self.raw_iids[stage]

            assert raw_name in self.STAGE_REMAP, \
                   f'ERROR: Unknown stage remap: {raw_name}'

            self.stage_iids[stage] = self.STAGE_REMAP[raw_name]
            event.stage = self.stage_iids[stage]

        # Interned ID does not exist
        else:
            assert False, "Stage IID not found"


class MetadataAttachment:

    def __init__(self, metadata):
        self.binding = metadata['binding']
        self.is_loaded = metadata.get('load', False)
        self.is_stored = metadata.get('store', True)
        self.is_resolved = metadata.get('resolve', True)


class MetadataAttachments:

    def __init__(self, metadata):
        self.attachments = []

        for attach_meta in metadata['attachments']:
            attachment = MetadataAttachment(attach_meta)
            self.attachments.append(attachment)

        self.attachments.sort(key=lambda x: x.binding)

class MetadataRenderPass:

    def __init__(self, frame, metadata):
        self.frame = frame
        self.tagID = metadata['tid']

        self.label_stack = None
        label_stack = metadata.get('label', None)
        if label_stack:
            self.label_stack = label_stack.split('|')

        self.width = metadata['width']
        self.height = metadata['height']
        self.draw_call_count = metadata['drawCallCount']

        self.attachments = MetadataAttachments(metadata)

    def getKey(self):
        return f't{self.tagID}'


class MetadataDispatch:

    def __init__(self, frame, metadata):
        self.frame = frame
        self.tagID = metadata['tid']

        self.label_stack = None
        label_stack = metadata.get('label', None)
        if label_stack:
            self.label_stack = label_stack.split('|')

        self.xGroups = metadata['xGroups']
        self.yGroups = metadata['yGroups']
        self.zGroups = metadata['zGroups']

    def getKey(self):
        return f't{self.tagID}'


class MetadataImageTransfer:

    def __init__(self, frame, metadata):
        self.frame = frame
        self.tagID = metadata['tid']

        self.label_stack = None
        label_stack = metadata.get('label', None)
        if label_stack:
            self.label_stack = label_stack.split('|')

        self.subtype = metadata['subtype']
        self.pixel_count = metadata['pixels'] ## TODO: pixelCount

    def getKey(self):
        return f't{self.tagID}'

    def get_long_label(self):
        lines = []

        if self.label_stack:
            lines.append(self.label_stack[-1])

        # If indirect then show a placeholder
        if self.pixelCount == -1:
            line = f'{self.subtype} (? pixels)'
        elif self.pixelCount == 1:
            line = f'{self.subtype} (1 pixel)'
        # If 3D then show a 3D dimension
        else:
            line = f'{self.subtype} ({self.pixelCount} pixels)'

        lines.append(line)
        return '\n'.join(lines)

    def get_short_label(self):
        if None is self.subtype:
            return "Missing subtype"
        return self.subtype


class MetadataBufferTransfer:

    def __init__(self, frame, metadata):
        self.frame = frame
        self.tagID = metadata['tid']

        self.label_stack = None
        label_stack = metadata.get('label', None)
        if label_stack:
            self.label_stack = label_stack.split('|')

        self.subtype = metadata['subtype']
        self.byte_count = metadata['bytes'] ## TODO: byteCount

    def getKey(self):
        return f't{self.tagID}'


class RenderstageEvent:

    def __init__(self, start_time, spec):
        self.start_time = start_time
        self.duration = spec.duration
        self.stream = spec.hw_queue_iid
        self.stage = spec.stage_iid

        # Decode the user label if we have one
        self.user_label = None
        for i, item in enumerate(spec.extra_data):
            if item.name != 'Labels':
                continue

            self.user_label = item.value

        self.submission_id = spec.submission_id

        self.command_buffer_handle = None
        if spec.HasField('command_buffer_handle'):
            self.command_buffer_handle = spec.command_buffer_handle
            self.command_buffer_handle &= 0x00FFFFFFFFFFFFFF

        self.framebuffer_handle = None
        if spec.HasField('render_target_handle'):
            self.framebuffer_handle = spec.render_target_handle
            self.framebuffer_handle &= 0x00FFFFFFFFFFFFFF

        self.framebuffer_handle = None
        if spec.HasField('render_pass_handle'):
            self.render_pass_handle = spec.render_pass_handle
            self.render_pass_handle &= 0x00FFFFFFFFFFFFFF

        assert self.stream and self.stage

    def get_long_label(self):
        # Get metadata
        if self.metadata:
            return self.metadata.get_long_label()
        elif self.user_label:
            return f'L: {self.user_label}\n{self.stage}'
        return f'S: {self.submission_id}\n{self.stage}'

    def get_short_label(self):
        # Get metadata
        if self.metadata:
            return self.metadata.get_short_label()
        elif self.user_label:
            return f'L: {self.user_label}'
        return f'S: {self.submission_id}'


class RawTrace:

    @classmethod
    def load_metadata_from_file(cls, metadata_file):
        '''
        Load the raw metadata from file.
        '''
        metadata = {}
        with open(metadata_file, 'rb') as handle:

            while True:
                # Read frame header and exit on partial read
                frame_size = handle.read(4)
                if len(frame_size) != 4:
                    break

                frame_size = struct.unpack('<I', frame_size)[0]

                frame_data = handle.read(frame_size)
                if len(frame_data) != frame_size:
                    break

                data = json.loads(frame_data.decode(encoding='utf-8'))

                frameID = data['frame']
                for workload in data['workloads']:
                    if workload['type'] == 'renderpass':
                        meta = MetadataRenderPass(frameID, workload)
                        metadata[meta.getKey()] = meta
                    elif workload['type'] == 'dispatch':
                        meta = MetadataDispatch(frameID, workload)
                        metadata[meta.getKey()] = meta
                    elif workload['type'] == 'imagetransfer':
                        meta = MetadataImageTransfer(frameID, workload)
                        metadata[meta.getKey()] = meta
                    elif workload['type'] == 'buffertransfer':
                        meta = MetadataBufferTransfer(frameID, workload)
                        metadata[meta.getKey()] = meta
                    else:
                        assert False, f'Unknown workload {workload["type"]}'

        return metadata

    @classmethod
    def load_perfetto_from_file(cls, file_path):
        '''
        Load the raw metadata from file.
        '''
        config = PerfettoConfig()
        trace_events = []

        # Open the Perfetto protobuf trace file
        protoc = trace_pb2.Trace()
        with open(file_path, 'rb') as handle:
            protoc.ParseFromString(handle.read())

        # Extract render stages events from Perfetto data
        for packet in protoc.packet:

            # Clock sync packet so update clock drift information
            if packet.HasField('clock_snapshot'):
                config.add_clock_sync_data(packet)

            # Interned data packet so update GPU configuration
            if packet.HasField('interned_data'):
                data = packet.interned_data

                # Decode render stages queue specification
                for spec in data.gpu_specifications:
                    config.add_interned_data(spec)

            # Render stage event packet so build a new event
            if packet.HasField('gpu_render_stage_event'):
                start_time = config.get_event_time(packet)
                raw_event = packet.gpu_render_stage_event
                event = RenderstageEvent(start_time, raw_event)
                trace_events.append(event)

        # Sort events into time order
        trace_events.sort(key=lambda x: x.start_time)

        # Replace time so first event starts at time = 0
        streams = {}
        start_time = trace_events[0].start_time
        for event in trace_events:
            event.start_time -= start_time

            # Also ensure that "queued time" does not show as running
            if event.stream not in streams:
                streams[event.stream] = [event]
                continue

            last_event = streams[event.stream][-1]
            last_event_end = last_event.start_time + last_event.duration

            # Remove overlap if queued while last event still running
            if event.start_time <= last_event_end:
                time_diff = last_event_end - event.start_time + 1
                event.start_time += time_diff
                event.duration -= time_diff

        # Replace all interned data cross-references
        for event in trace_events:
            config.replace_interned_stream(event)
            config.replace_interned_stage(event)



        return trace_events

    def __init__(self, trace_file, metadata_file):
        self.metadata = self.load_metadata_from_file(metadata_file)
        self.events = self.load_perfetto_from_file(trace_file)
