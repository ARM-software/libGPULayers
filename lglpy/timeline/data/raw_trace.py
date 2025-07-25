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
This module implements the raw traces that store parsed, but not process,
data loaded from Perfetto data and GPU Timeline layer data. These traces are
subsequently parsed into a single combined representation for tool use.
'''

import enum
import struct
import json
from typing import Any, Optional, Union

from lglpy.timeline.protos.perfetto.trace import trace_pb2


# Helper for typing JSON payloads
JSONType = Any


class GPUStreamID(enum.IntEnum):
    '''
    Symbolic mapping of known GPU scheduling stream IDs.

    Attributes:
        COMPUTE: Compute and advanced geometry stream on all GPUs.
        NONFRAGMENT: Non-fragment stream on Bifrost and Valhall GPUs.
        FRAGMENT: Fragment stream on Bifrost and Valhall GPUs.
        BINNING: Binning phase stream on 5th Generation GPUs.
        MAIN: Main phase stream on 5th Generation GPUs.
        TRANSFER: Transfer stream on all GPUs.
    '''
    COMPUTE = 0
    NONFRAGMENT = 1
    FRAGMENT = 2
    BINNING = 3
    MAIN = 4
    TRANSFER = 5

    @classmethod
    def get_ui_name(cls, stream_id) -> str:
        '''
        Get presentable name for a stream.

        Args:
            stream_id: The enum value to convert.

        Returns:
            Pretty name for use in user interfaces.
        '''
        human_names = {
            cls.COMPUTE: 'Compute',
            cls.NONFRAGMENT: 'Non-fragment',
            cls.FRAGMENT: 'Fragment',
            cls.BINNING: 'Binning',
            cls.MAIN: 'Main',
            cls.TRANSFER: 'Transfer'
        }

        return human_names[stream_id]


class GPUStageID(enum.IntEnum):
    '''
    Symbolic mapping of known GPU workload stage IDs.

    Attributes:
        COMPUTE: Compute shaders.
        ADVANCED_GEOMETRY: Tessellation or Geometry shaders.
        VERTEX: Vertex shaders from a render pass.
        FRAGMENT: Fragment shaders from a render pass.
        BINNING: Binning subset of vertex shaders from a render pass.
        MAIN: Main phase vertex and fragment shaders from a render pass.
        TRACE_RAYS: Ray tracing pipeline dispatch.
        AS_TRANSFER: Transfer writing to/from an acceleration structure.
        BUFFER_TRANSFER: Transfer writing a buffer output.
        IMAGE_TRANSFER: Transfers writing an image output.
        AS_BUILD_FAST_BUILD: Acceleration structure build with fast_build.
        AS_BUILD_FAST_TRACE: Acceleration structure build with fast_trace.
        AS_BUILD_UPDATE: Acceleration structure build with update.
    '''
    COMPUTE = 0
    ADVANCED_GEOMETRY = 1
    VERTEX = 2
    FRAGMENT = 3
    BINNING = 4
    MAIN = 5
    TRACE_RAYS = 6
    AS_TRANSFER = 7
    BUFFER_TRANSFER = 8
    IMAGE_TRANSFER = 9
    AS_BUILD_FAST_BUILD = 10
    AS_BUILD_FAST_TRACE = 11
    AS_BUILD_UPDATE = 12

    @classmethod
    def get_ui_name(cls, stage_id) -> str:
        '''
        Get presentable name for a stage.

        Args:
            stage_id: The enum value to convert.

        Returns:
            Pretty name for use in user interfaces.
        '''
        human_names = {
            cls.COMPUTE: 'Compute',
            cls.ADVANCED_GEOMETRY: 'Advanced geometry',
            cls.VERTEX: 'Vertex',
            cls.FRAGMENT: 'Fragment',
            cls.BINNING: 'Binning',
            cls.MAIN: 'Main',
            cls.TRACE_RAYS: 'Trace rays',
            cls.AS_TRANSFER: 'AS transfer',
            cls.BUFFER_TRANSFER: 'Buffer transfer',
            cls.IMAGE_TRANSFER: 'Image transfer',
            cls.AS_BUILD_FAST_BUILD: 'AS build (fast build)',
            cls.AS_BUILD_FAST_TRACE: 'AS build (fast trace)',
            cls.AS_BUILD_UPDATE: 'AS build (update)'
        }

        return human_names[stage_id]


class MetadataAttachment:
    '''
    Parsed GPU Timeline layer payload for a single render pass attachment.

    Attributes:
        binding: The name of the attachment point.
        is_loaded: Is this attachment loaded from memory at start of pass?
        is_store: Is this attachment stored to memory at end of pass?
        is_resolved: Is this attachment a multi-sample resolve attachment?
    '''

    def __init__(self, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single render pass attachment.

        Args:
            metadata: JSON payload from the layer.
        '''
        self.binding = str(metadata['binding'])
        self.is_loaded = bool(metadata.get('load', False))
        self.is_stored = bool(metadata.get('store', True))
        self.is_resolved = bool(metadata.get('resolve', True))


class MetadataAttachments:
    '''
    Parsed GPU Timeline layer payload for a set of render pass attachments.

    Attributes:
        binding: The name of the attachment point.
        is_loaded: Is this attachment loaded from memory at start of pass?
        is_store: Is this attachment stored to memory at end of pass?
        is_resolved: Is this attachment a multi-sample resolve attachment?
    '''

    def __init__(self, metadata: JSONType):
        '''
        Parsed GPU Timeline layer attachment payload for a single render pass.

        Args:
            metadata: JSON payload from the layer.
        '''
        self.attachments = []  # type: list[MetadataAttachment]

        for attach_meta in metadata['attachments']:
            attachment = MetadataAttachment(attach_meta)
            self.attachments.append(attachment)

        self.attachments.sort(key=lambda x: x.binding)


class MetadataPresent:
    '''
    Baseclass for a submit.

    Attributes:
        frame:       The frame index in the application.
        start_time:  The present submit time.
    '''

    def __init__(self, frame: int, timestamp: int):
        '''
        Construct a new submit event.

        Args:
            frame: The frame index in the application.
            timestamp:  The present submit time.
        '''
        self.frame = frame
        self.start_time = timestamp

    def get_frame(self):
        '''
        Get the frame of this submit.
        '''
        return self.frame

    def get_submit(self):
        '''
        Get the submit of this submit.
        '''
        return self

    def get_queue(self):
        '''
        Get the queue of this submit.
        '''
        return ModuleNotFoundError

    def get_workload(self):
        '''
        Get the workload of this workload.
        '''
        return None


class MetadataSubmit:
    '''
    Baseclass for a submit.

    Attributes:
        frame:       The frame index in the application.
        queue:       The queue handle.
        start_time:  The submit time.
    '''

    def __init__(
            self, frame: int, present: MetadataPresent, metadata: JSONType):
        '''
        Construct a new submit event.

        Args:
            frame: The frame index in the application.
            present: The frame present information for the associated frame.
            metadata: JSON payload from the layer.
        '''
        self.frame = frame
        self.present = present
        self.queue = int(metadata['queue'])
        self.start_time = int(metadata['timestamp'])

    def get_frame(self):
        '''
        Get the frame of this submit.
        '''
        return self.frame

    def get_submit(self):
        '''
        Get the submit of this submit.
        '''
        return self

    def get_queue(self):
        '''
        Get the queue of this submit.
        '''
        return self.queue

    def get_workload(self):
        '''
        Get the workload of this workload.
        '''
        return None


class MetadataWorkload:
    '''
    Baseclass for a parsed GPU Timeline layer payload for a workload.

    Attributes:
        frame: The frame index in the application.
        tag_id: The unique workload tag ID to cross-reference with Perfetto.
        submit: The submit information.
        label_stack: Debug label stack, or None if no user labels.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single render pass.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        self.tag_id = int(metadata['tid'])
        self.submit = submit

        self.label_stack = metadata.get('label', None)

    def get_perfetto_tag_id(self) -> str:
        '''
        Get the tag ID formatted to match the Perfetto data.

        Returns:
            The Perfetto-formatted tag ID.
        '''
        return f't{self.tag_id}'


class MetadataRenderPass(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a render pass workload.

    Attributes:
        width: Width of the render pass in pixels.
        height: Height of the render pass in pixels.
        draw_call_count: Number of draw calls in the render pass.
        attachments: List of render pass attachments.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single render pass.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.width = int(metadata['width'])
        self.height = int(metadata['height'])
        self.draw_call_count = int(metadata['drawCallCount'])
        self.subpass_count = int(metadata['subpassCount'])

        self.attachments = MetadataAttachments(metadata)


class MetadataDispatch(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a compute dispatch workload.

    Attributes:
        groups_x: Width of the dispatch in work groups, or -1 if unknown.
        groups_y: Height of the dispatch in work groups, or -1 if unknown.
        groups_z: Depth of the dispatch in work groups, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single dispatch.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.groups_x = int(metadata['xGroups'])
        self.groups_y = int(metadata['yGroups'])
        self.groups_z = int(metadata['zGroups'])

    def get_perfetto_tag_id(self) -> str:
        '''
        Get the tag ID formatted to match the Perfetto data.

        Returns:
            The Perfetto-formatted tag ID.
        '''
        return f't{self.tag_id}'


class MetadataTraceRays(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a ray tracing pipeline workload.

    Attributes:
        items_x: Width of the dispatch in work items, or -1 if unknown.
        items_y: Height of the dispatch in work items, or -1 if unknown.
        items_z: Depth of the dispatch in work items, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single dispatch.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.items_x = int(metadata['xItems'])
        self.items_y = int(metadata['yItems'])
        self.items_z = int(metadata['zItems'])

    def get_perfetto_tag_id(self) -> str:
        '''
        Get the tag ID formatted to match the Perfetto data.

        Returns:
            The Perfetto-formatted tag ID.
        '''
        return f't{self.tag_id}'


class MetadataImageTransfer(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a transfer that writes an image.

    Attributes:
        subtype: Specific type of the transfer.
        pixel_count: Number of pixels written, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single image transfer.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.subtype = str(metadata['subtype'])
        self.pixel_count = int(metadata['pixelCount'])


class MetadataBufferTransfer(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a transfer that writes a buffer.

    Attributes:
        subtype: Specific type of the transfer.
        byte_count: Number of bytes written, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single buffer transfer.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.subtype = str(metadata['subtype'])
        self.byte_count = int(metadata['byteCount'])


class MetadataASBuild(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for an acceleration structure build.

    Attributes:
        subtype: Specific type of the transfer.
        primitive_count: Number of bytes written, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single AS build.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.subtype = str(metadata['subtype'])
        self.primitive_count = int(metadata['primitiveCount'])


class MetadataASTransfer(MetadataWorkload):
    '''
    Parsed GPU Timeline layer payload for a transfer that writes an
    acceleration structure.

    Attributes:
        subtype: Specific type of the transfer.
        byte_count: Number of bytes written, or -1 if unknown.
    '''

    def __init__(self, submit: MetadataSubmit, metadata: JSONType):
        '''
        Parsed GPU Timeline layer payload for a single acceleration structure
        transfer.

        Args:
            submit: The submit information.
            metadata: JSON payload from the layer.
        '''
        super().__init__(submit, metadata)

        self.subtype = str(metadata['subtype'])
        self.byte_count = int(metadata['byteCount'])


class RenderstageEvent:
    '''
    Parsed Perfetto trace payload for a render stages event.

    The GPU Timeline layers embeds its tag_id used for cross-referencing in to
    the user_label field, otherwise this is the user debug label.

    Attributes:
        start_time: The event start time, in nanoseconds.
        duration: The event duration, in nanoseconds.
        stream_iid: The interned ID of the stream.
        stream: The type of the stream after resolving interning.
        stage_iid: The interned ID of the stage.
        stream: The type of the stage after resolving interning.
        user_label: The user debug label, if specified.
    '''

    def __init__(self, start_time: int, spec: Any):
        '''
        Parsed Perfetto trace payload for a render stages event.

        Args:
            start_time: The event start time, in nanoseconds.
            spec: The event payload.
        '''
        self.start_time = start_time
        self.duration = int(spec.duration)

        self.submit_id = None
        if spec.HasField('submission_id'):
            self.submit_id = spec.submission_id

        # Decode the interned stream and stage types
        # Interning is resolved later as packets may be out-of-order
        self.stream_iid = int(spec.hw_queue_iid)
        self.stream = None  # type: Optional[GPUStreamID]

        self.stage_iid = int(spec.stage_iid)
        self.stage = None  # type: Optional[GPUStageID]

        # Decode the user label if we have one
        self.user_label = None
        for item in spec.extra_data:
            if item.name != 'Labels':
                continue

            self.user_label = str(item.value)


# Helper for typing all workload subclasses of MetadataWorkload
MetadataWork = Union[
    MetadataRenderPass,
    MetadataDispatch,
    MetadataTraceRays,
    MetadataImageTransfer,
    MetadataBufferTransfer,
    MetadataASBuild,
    MetadataASTransfer
]


class PerfettoConfig:
    '''
    This class persists settings found in the Perfetto trace that
    are needed to fully decode later event packets in the trace.

    Attributes:
        STREAM_REMAP: Mapping of Perfetto stream names to enum values.
        STAGE_REMAP: Mapping of Perfetto stage names to enum values.
        clock_sync: Mapping of clock sync information to allow correction
            for clock drift across different clock sources.
        raw_iids: Mapping of numeric IDs to interned string labels.
        stream_iids: Mapping of numeric IDs to interned string labels that
            have been verified as belonging to GPU stream names.
        stage_iids: Mapping of numeric IDs to interned string labels that
            have been verified as belonging to GPU render stage names.
    '''
    # Known Perfetto streams and their remapped names
    STREAM_REMAP = {
        'compute': GPUStreamID.COMPUTE,
        'vertex': GPUStreamID.NONFRAGMENT,
        'non-fragment': GPUStreamID.NONFRAGMENT,
        'fragment': GPUStreamID.FRAGMENT,
        'binning': GPUStreamID.BINNING,
        'main': GPUStreamID.MAIN,
        'transfer': GPUStreamID.TRANSFER
    }

    # Known Perfetto render stages and their remapped names
    STAGE_REMAP = {
        'clear image': GPUStageID.IMAGE_TRANSFER,
        'copy image': GPUStageID.IMAGE_TRANSFER,
        'blit image': GPUStageID.IMAGE_TRANSFER,
        'resolve image': GPUStageID.IMAGE_TRANSFER,
        'generate mipmap': GPUStageID.IMAGE_TRANSFER,
        'copy buffer': GPUStageID.BUFFER_TRANSFER,
        'fill buffer': GPUStageID.BUFFER_TRANSFER,
        'copy query': GPUStageID.BUFFER_TRANSFER,
        'compute': GPUStageID.COMPUTE,
        'trace_rays': GPUStageID.TRACE_RAYS,
        'non-fragment': GPUStageID.VERTEX,
        'advanced geometry': GPUStageID.ADVANCED_GEOMETRY,
        'vertex': GPUStageID.VERTEX,
        'binning': GPUStageID.BINNING,
        'fragment': GPUStageID.FRAGMENT,
        'main': GPUStageID.MAIN,
        "acceleration structure 'fast build' build":
            GPUStageID.AS_BUILD_FAST_BUILD,
        "acceleration structure 'fast trace' build":
            GPUStageID.AS_BUILD_FAST_TRACE,
        'acceleration structure copy to memory': GPUStageID.AS_TRANSFER,
        'acceleration structure copy from memory': GPUStageID.AS_TRANSFER,
        'acceleration structure update': GPUStageID.BUFFER_TRANSFER
    }

    def __init__(self):
        '''
        Initialize an empty configuration to be populated incrementally.
        '''
        # Clock sync information
        self.clock_sync = {}  # type: dict[int, int]

        # Interned data reference IDs
        self.raw_iids = {}  # type: dict[int, str]
        self.stream_iids = {}  # type: dict[int, GPUStreamID]
        self.stage_iids = {}  # type: dict[int, GPUStageID]

    def add_interned_data(self, spec) -> None:
        '''
        Add raw interned string data which we can reference later.

        Args:
            spec: The Perfetto interned data specification object.
        '''
        iid = spec.iid if spec.HasField('iid') else 0
        name = spec.name if spec.HasField('name') else None
        assert iid and name, 'ERROR: Interned data missing expected fields'
        self.raw_iids[iid] = name

    def add_clock_sync_data(self, event) -> None:
        '''
        Add raw clock sync data which we can use to correct timing later.

        Args:
            spec: The Perfetto clock sync snapshot object.
        '''
        # Default clock domain is clock 5, BUILTIN_CLOCK_MONOTONIC_RAW
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

    def get_event_time(self, event) -> int:
        '''
        Get the event time in a unified clock domain.

        Args:
            event: The Perfetto event to extract the timestamp from.

        Returns:
            Event start time in a unified clock domain.
        '''
        # Determine the clock this event it using
        clock_id = 6  # Default is BUILTIN_CLOCK_BOOTTIME
        if event.HasField('timestamp_clock_id'):
            clock_id = event.timestamp_clock_id

        # Correct for clock offset and skew across the clock sources
        return event.timestamp - self.clock_sync[clock_id]

    def replace_interned_stream(self, event: RenderstageEvent) -> None:
        '''
        Replaced interned data stream references with the real data.

        Args:
            event: The Perfetto event to rewrite
        '''
        # Rewrite the hardware stream
        stream = event.stream_iid

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

    def replace_interned_stage(self, event: RenderstageEvent) -> None:
        '''
        Replaced interned data render stage references with the real data.

        Args:
            event: The Perfetto event to rewrite
        '''
        # Rewrite the hardware stage
        stage = event.stage_iid

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
            assert False, 'ERROR: Unknown stage interned data ID'


class RawTrace:
    '''
    A raw trace pair loaded from the file system.

    Attributes:
        events: The perfetto event data.
        metadata: The layer metadata for the events.
    '''

    @classmethod
    def load_metadata_from_file(
            cls,
            metadata_file: str,
            start_time: int) -> dict[str, MetadataWork]:
        '''
        Load the raw metadata from file.

        Args:
            metadata_file: The file path of the metadata payload.
            start_time: The start time bias to apply to align with Perfetto.
        '''
        metadata = {}  # type: dict[str, MetadataWork]
        with open(metadata_file, 'rb') as handle:

            while True:
                # End decoding if we get a partial frame header
                bin_data = handle.read(4)
                if len(bin_data) != 4:
                    break

                frame_size = int(struct.unpack('<I', bin_data)[0])

                # End decoding if we get a partial packet
                bin_data = handle.read(frame_size)
                if len(bin_data) != frame_size:
                    break

                # Decode a complete packet
                data = json.loads(bin_data.decode(encoding='utf-8'))

                frame_id = data['frame']
                present_time = data['presentTimestamp']

                present = MetadataPresent(frame_id, present_time - start_time)

                for submit in data['submits']:
                    # Create metadata with bias to match Perfetto
                    submeta = MetadataSubmit(frame_id, present, submit)
                    submeta.start_time -= start_time

                    for workload in submit['workloads']:
                        meta = None  # type: Optional[MetadataWork]

                        if workload['type'] == 'renderpass':
                            meta = MetadataRenderPass(submeta, workload)

                        elif workload['type'] == 'dispatch':
                            meta = MetadataDispatch(submeta, workload)

                        elif workload['type'] == 'tracerays':
                            meta = MetadataTraceRays(submeta, workload)

                        elif workload['type'] == 'imagetransfer':
                            meta = MetadataImageTransfer(submeta, workload)

                        elif workload['type'] == 'buffertransfer':
                            meta = MetadataBufferTransfer(submeta, workload)

                        elif workload['type'] == 'asbuild':
                            meta = MetadataASBuild(submeta, workload)

                        elif workload['type'] == 'astransfer':
                            meta = MetadataASTransfer(submeta, workload)

                        else:
                            assert False, f'Unknown workload {workload["type"]}'

                        if meta:
                            metadata[meta.get_perfetto_tag_id()] = meta

        return metadata

    @classmethod
    def load_perfetto_from_file(
            cls, perfetto_file: str) -> tuple[list[RenderstageEvent], int]:
        '''
        Load the raw Perfetto trace from file.

        Args:
            perfetto_file: The file path of the Perfetto trace payload.
        '''
        config = PerfettoConfig()
        trace_events = []

        # Open the Perfetto protobuf trace file
        protoc = trace_pb2.Trace()  # pylint: disable=no-member
        with open(perfetto_file, 'rb') as handle:
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

        # Replace all interned data cross-references to assign real stream
        # names before trying to use streams because we may get more than one
        # interned ID for the same physical stream and this will dedupe them
        for event in trace_events:
            config.replace_interned_stream(event)
            config.replace_interned_stage(event)

        # Replace time so first event starts at time = 0 and that queued time
        # waiting for earlier work does not show as running
        streams = {}
        start_time = trace_events[0].start_time
        for event in trace_events:
            event.start_time -= start_time

            # First job in stream so just add to stream
            if event.stream not in streams:
                streams[event.stream] = [event]
                continue

            # Later job in stream so remove any overlap with job N-1
            last_event = streams[event.stream][-1]
            last_event_end = last_event.start_time + last_event.duration

            # Remove overlap if queued while last event still running
            if event.start_time <= last_event_end:
                time_diff = last_event_end - event.start_time + 1
                event.start_time += time_diff
                event.duration -= time_diff

                # Ensure we don't have negative duration events
                if event.duration <= 0:
                    event.duration = 1

            # Add event to the stream after patching it
            streams[event.stream].append(event)

        return (trace_events, start_time)

    def __init__(self, trace_file: str, metadata_file: str):
        '''
        Load a trace from file.

        Args:
            trace_file: The file path of the Perfetto trace payload.
            metadata_file: The file path of the Timeline layer trace payload.
        '''
        trace_events, start_time = self.load_perfetto_from_file(trace_file)
        self.events = trace_events

        self.metadata = None
        if metadata_file:
            self.metadata = \
                self.load_metadata_from_file(metadata_file, start_time)
