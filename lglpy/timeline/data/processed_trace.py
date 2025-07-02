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
This module implements the processed trace that stores the formatted workloads
that merge data from the Perfetto data and GPU Timeline layer data into a
single combined representation.
'''

import re
from typing import Optional, Union

from .raw_trace import RawTrace, RenderstageEvent, MetadataWork, \
    MetadataRenderPass, MetadataDispatch, MetadataTraceRays, \
    MetadataBufferTransfer, MetadataImageTransfer, MetadataASBuild, \
    MetadataASTransfer, GPUStreamID, GPUStageID

LABEL_HEURISTICS = True
LABEL_MAX_LEN = 60


class GPUWorkload:
    '''
    Base class holding command data for GPU workloads in a trace.

    Attributes:
        tag_id: The unique tag ID assigned by the layer.
        start_time: The event start time in nanoseconds.
        duration: The event duration in nanoseconds.
        stream: The scheduling stream of this workload.
        stage: The render stage of this workload.
        frame: The frame index in the application.
        label_stack: Application debug label stack.
    '''

    FRAME_LABEL = re.compile(r'^Frame (\d+)$')
    PARENS = re.compile(r'(\(.*\))')
    RESOLUTION = re.compile(r'\d+x\d+')
    WHITESPACE = re.compile(r'\s\s+')

    def __init__(
            self, event: RenderstageEvent, metadata: Optional[MetadataWork]):
        '''
        Base class for workloads in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Common data we from the Perfetto event
        self.submit_id = event.submit_id
        self.tag_id = event.user_label
        self.start_time = event.start_time
        self.duration = event.duration
        self.stream = event.stream
        self.stage = event.stage

        # Common data we get from the layer metadata
        self.submit = None
        self.label_stack = None
        self.parsed_label_name: Optional[str] = None

        if metadata:
            self.submit = metadata.submit
            self.label_stack = metadata.label_stack

    def get_label_name(self) -> Optional[str]:
        '''
        Get a cleaned up label name for a workload.

        Warning: The heuristics here are not robust.

        Returns:
            A modified label for use in the UI.
        '''
        # No label to parse
        if not self.label_stack:
            return None

        # Cached label already parsed
        if self.parsed_label_name is not None:
            return self.parsed_label_name

        if not LABEL_HEURISTICS:
            return self.label_stack[-1]

        # Create a copy we can edit ...
        labels = list(self.label_stack)

        # Heuristic to remove app-concatenated leaf nodes in UE
        if 'Scene.' in labels[-1]:
            del labels[-1]

        # Pop off low value root nodes in UE captures
        if labels and self.FRAME_LABEL.match(labels[0]):
            del labels[0]

        if labels and labels[0] == 'Scene':
            del labels[0]

        # String substitutions
        for i, label in enumerate(labels):
            label = self.PARENS.sub('', label)
            label = self.RESOLUTION.sub('', label)
            label = self.WHITESPACE.sub(' ', label)
            label = label.replace('Light::', '')
            labels[i] = label.strip()

        # Stack prefix substitutions
        for i, label in enumerate(labels):
            for j in range(i + 1, len(labels)):
                next_label = labels[j]
                if not next_label.startswith(label):
                    break
                labels[j] = next_label[len(label):].strip()

        # Remove labels that are now empty
        labels = list(filter(bool, labels))

        if not labels:
            label = ''
        else:
            label = '.'.join(labels)

        if len(label) > LABEL_MAX_LEN:
            half_max = LABEL_MAX_LEN // 2
            prefix = label[0:half_max]
            postfix = label[-half_max:]
            label = f'{prefix}...{postfix}'

        self.parsed_label_name = label
        return self.parsed_label_name

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Unknown type'

    def get_workload_name(self) -> str:
        '''
        Get a name for the workload.

        This is based on the application debug label if there is one, but
        with some heuristics to try and clean is up ...

        Returns:
            Returns the label for use in the UI.
        '''
        label = None
        if self.label_stack:
            label = self.get_label_name()

        # Default label if no label or get_label_name heuristics stripped it
        if not label:
            return self.get_workload_type_name()

        return label

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        # Subclass will override this if metadata exists
        # Submit ID isn't useful, but traces back to Perfetto data for debug
        return f'Submit: {self.submit_id}'

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        # Subclass will override this if metadata exists
        # Submit ID isn't useful, but traces back to Perfetto data for debug
        return f'Submit: {self.submit_id}'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        # Subclass will override this if key-value metadata exists
        return {}

    def get_frame(self):
        '''
        Get the frame of this workload.
        '''
        if self.submit:
            return self.submit.frame

        return None

    def get_submit(self):
        '''
        Get the submit of this workload.
        '''
        return self.submit

    def get_queue(self):
        '''
        Get the queue of this workload.
        '''
        if self.submit:
            return self.submit.queue

        return None

    def get_workload(self):
        '''
        Get the workload of this workload.
        '''
        return self.tag_id


class GPURenderPass(GPUWorkload):
    '''
    Workload class representing a render pass.

    Attributes:
        width: The workload width, in pixels.
        height: The workload height, in pixels.
        draw_call_count: The number of draw calls in the render pass.
        attachments: The list of framebuffer attachments.
    '''

    def __init__(self, event: RenderstageEvent, metadata: MetadataRenderPass):
        '''
        Render pass workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.width = metadata.width
        self.height = metadata.height
        self.draw_call_count = metadata.draw_call_count
        self.attachments = list(metadata.attachments.attachments)

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Render pass'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'resolution': self.get_resolution_str(),
            'draw count': self.get_draw_count_str(),
            'attachments': self.get_attachment_present_str(),
            'attachments loaded': self.get_attachment_loadop_str(),
            'attachments stored': self.get_attachment_storeop_str()
        }

    def get_resolution_str(self) -> str:
        '''
        Get the resolution string.

        Returns:
            Returns the label for use in the UI.
        '''
        return f'{self.width}x{self.height}'

    def get_draw_count_str(self) -> str:
        '''
        Get the draw call count string.

        Returns:
            Returns the label for use in the UI.
        '''
        if self.draw_call_count < 0:
            return 'Unknown draws'

        if self.draw_call_count == 1:
            return '1 draw'

        return f'{self.draw_call_count} draws'

    def get_attachment_present_str(self) -> str:
        '''
        Get the attachment present string.

        Returns:
            Returns the label for use in the UI.
        '''
        bindings = [x.binding for x in self.attachments]
        return self.get_compact_string(bindings)

    def get_attachment_loadop_str(self) -> str:
        '''
        Get the attachment loadop string.

        Returns:
            Returns the label for use in the UI.
        '''
        bindings = [x.binding for x in self.attachments if x.is_loaded]
        return self.get_compact_string(bindings)

    def get_attachment_storeop_str(self) -> str:
        '''
        Get the attachment loadop string.

        Returns:
            Returns the label for use in the UI.
        '''
        bindings = [x.binding for x in self.attachments if x.is_stored]
        return self.get_compact_string(bindings)

    @classmethod
    def get_compact_string(cls, bindings: list[str]) -> str:
        '''
        Get the compact UI string for a set of attachment bind points.

        Args:
            bindings: The list of binding names for the binding type.

        Returns:
            A binding string of the form, e.g. "C0124DS".
        '''
        merge = ''.join(bindings)
        return ''.join([j for i, j in enumerate(merge) if j not in merge[:i]])

    def get_attachment_long_label(self) -> str:
        '''
        Get the long label showing use of render pass attachments.

        Returns:
            A string showing loadOp, attachment, storeOp.
        '''
        present = self.get_attachment_present_str()
        loaded = self.get_attachment_loadop_str()
        stored = self.get_attachment_storeop_str()

        if loaded:
            loaded = f'load({loaded}) > '

        if stored:
            stored = f' > store({stored}) '

        return f'{loaded}[{present}]{stored}'

    def get_attachment_short_label(self) -> str:
        '''
        Get the short label showing use of render pass attachments.

        Returns:
            A string showing attachments without load/storeOp usage.
        '''
        present = self.get_attachment_present_str()
        return f'[{present}]'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        line = f'{self.get_resolution_str()} ({self.get_draw_count_str()})'
        lines.append(line)

        line = self.get_attachment_long_label()
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        line = self.get_resolution_str()
        lines.append(line)

        line = self.get_attachment_short_label()
        lines.append(line)

        return '\n'.join(lines)


class GPUDispatch(GPUWorkload):
    '''
    Workload class representing a compute dispatch.
    '''

    def __init__(self, event: RenderstageEvent, metadata: MetadataDispatch):
        '''
        Compute dispatch workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.groups_x = metadata.groups_x
        self.groups_y = metadata.groups_y
        self.groups_z = metadata.groups_z

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Compute dispatch'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'resolution': self.get_resolution_str()
        }

    def get_resolution_str(self) -> str:
        '''
        Get the resolution string

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.groups_x == -1:
            return "?x?x? groups"

        # Else show the actual dimension
        dims = [self.groups_x, self.groups_y]

        # Hide Z dimension unless greater than 1
        if self.groups_z > 1:
            dims.append(self.groups_z)

        return f'{"x".join([str(dim) for dim in dims])} groups'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        lines.append(self.get_short_label())
        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []
        line = self.get_resolution_str()
        lines.append(line)
        return '\n'.join(lines)


class GPUTraceRays(GPUWorkload):
    '''
    Workload class representing a trace rays dispatch.
    '''

    def __init__(self, event: RenderstageEvent, metadata: MetadataTraceRays):
        '''
        Trace rays workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.items_x = metadata.items_x
        self.items_y = metadata.items_y
        self.items_z = metadata.items_z

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Trace rays dispatch'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'resolution': self.get_resolution_str()
        }

    def get_resolution_str(self) -> str:
        '''
        Get the resolution string.

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.items_x == -1:
            return "?x?x? items"

        # Else show the actual dimension
        dims = [self.items_x, self.items_y]

        # Hide Z dimension unless greater than 1
        if self.items_z > 1:
            dims.append(self.items_z)

        return f'{"x".join([str(dim) for dim in dims])} items'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        lines.append(self.get_short_label())
        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []
        lines.append(self.get_resolution_str())
        return '\n'.join(lines)


class GPUImageTransfer(GPUWorkload):
    '''
    Workload class representing an image transfer.

    Image transfers are any transfer that writes to an image. Source may be
    an image or a buffer.
    '''

    def __init__(
            self, event: RenderstageEvent, metadata: MetadataImageTransfer):
        '''
        Image transfer workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.transfer_type = metadata.subtype
        self.pixel_count = metadata.pixel_count

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Image transfer'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'transfer size': self.get_transfer_size_str()
        }

    def get_transfer_size_str(self) -> str:
        '''
        Get the transfer size string.

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.pixel_count == -1:
            return f'? pixels'

        s = 's' if self.pixel_count != 1 else ''
        return f'{self.pixel_count} pixel{s}'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        line = f'{self.transfer_type} ({self.get_transfer_size_str()})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return self.transfer_type


class GPUBufferTransfer(GPUWorkload):
    '''
    Workload class representing a buffer transfer.

    Buffer transfers are any transfer that writes to a buffer. Source may be
    an image or a buffer.
    '''

    def __init__(
            self, event: RenderstageEvent, metadata: MetadataBufferTransfer):
        '''
        Buffer transfer workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.transfer_type = metadata.subtype
        self.byte_count = metadata.byte_count

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Buffer transfer'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'transfer size': self.get_transfer_size_str()
        }

    def get_transfer_size_str(self) -> str:
        '''
        Get the transfer size string.

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.byte_count == -1:
            return f'? bytes'

        s = 's' if self.byte_count != 1 else ''
        return f'{self.byte_count} byte{s}'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        line = f'{self.transfer_type} ({self.get_transfer_size_str()})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return self.transfer_type


class GPUASBuild(GPUWorkload):
    '''
    Workload class representing an acceleration structure build.
    '''

    def __init__(
            self, event: RenderstageEvent, metadata: MetadataASBuild):
        '''
        Buffer transfer workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We cannot get specific subtypes from the layer, as one API call can
        # contain a mixture of subtypes and is ambiguous. Instead we infer it
        # from the Perfetto stage data generated by the driver which is
        # subtype-specific, with multiple workloads per Vulkan command if
        # the command contains multiple subtypes.
        assert metadata.subtype == 'Unknown'
        assert event.stage is not None
        self.build_type = GPUStageID.get_ui_name(event.stage)

        # We must have metadata so no need to check
        self.primitive_count = metadata.primitive_count

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Acceleration structure build'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'build size': self.get_transfer_size_str()
        }

    def get_transfer_size_str(self) -> str:
        '''
        Get the transfer size string.

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.primitive_count == -1:
            return f'? primitives'

        s = 's' if self.primitive_count != 1 else ''
        return f'{self.primitive_count} primitive{s}'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        line = f'{self.build_type} ({self.get_transfer_size_str()})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return self.build_type


class GPUASTransfer(GPUWorkload):
    '''
    Workload class representing an acceleration structure transfer.
    '''

    def __init__(
            self, event: RenderstageEvent, metadata: MetadataASTransfer):
        '''
        Acceleration structure transfer workload in a trace.

        Args:
            event: Parsed render stage event.
            metadata: Parsed metadata annotation.
        '''
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.transfer_type = metadata.subtype
        self.byte_count = metadata.byte_count

    def get_workload_type_name(self) -> str:
        '''
        Get the type of this workload.
        '''
        return 'Acceleration structure transfer'

    def get_key_value_properties(self) -> dict[str, str]:
        '''
        Get an ordered list of key-value pairs for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return {
            'transfer size': self.get_transfer_size_str()
        }

    def get_transfer_size_str(self) -> str:
        '''
        Get the transfer size string.

        Returns:
            Returns the label for use in the UI.
        '''
        # If indirect then show a placeholder
        if self.byte_count == -1:
            return f'? bytes'

        s = 's' if self.byte_count != 1 else ''
        return f'{self.byte_count} byte{s}'

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        line = f'{self.transfer_type} ({self.get_transfer_size_str()})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        return self.transfer_type


# Helper for typing all workload subclasses of MetadataWorkload
GPUWork = Union[
    # Generic workload if no metadata
    GPUWorkload,

    # Specific workload if metadata
    GPURenderPass,
    GPUDispatch,
    GPUTraceRays,
    GPUImageTransfer,
    GPUBufferTransfer,
    GPUASBuild,
    GPUASTransfer,
]


class GPUTrace:
    '''
    Decoded GPU trace, combining data sources into a single representation.

    Attributes:
        streams: Mapping of stream name to list of events in that stream.
    '''

    def __init__(self, raw_trace: RawTrace):
        '''
        Create a processed trace, combining raw trace data sources.

        Args:
            raw_trace: The raw parsed file data.
        '''
        self.streams = {}  # type: dict[GPUStreamID, list[GPUWork]]

        for event in raw_trace.events:
            # Find the metadata record for this event if we have one
            event_meta = None
            if raw_trace.metadata and event.user_label in raw_trace.metadata:
                event_meta = raw_trace.metadata[event.user_label]

            # Generic event
            if not event_meta:
                workload = GPUWorkload(event, None)

            # Specific event
            elif isinstance(event_meta, MetadataRenderPass):
                workload = GPURenderPass(event, event_meta)

            elif isinstance(event_meta, MetadataDispatch):
                workload = GPUDispatch(event, event_meta)

            elif isinstance(event_meta, MetadataTraceRays):
                workload = GPUTraceRays(event, event_meta)

            elif isinstance(event_meta, MetadataImageTransfer):
                workload = GPUImageTransfer(event, event_meta)

            elif isinstance(event_meta, MetadataBufferTransfer):
                workload = GPUBufferTransfer(event, event_meta)

            elif isinstance(event_meta, MetadataASBuild):
                workload = GPUASBuild(event, event_meta)

            elif isinstance(event_meta, MetadataASTransfer):
                workload = GPUASTransfer(event, event_meta)

            else:
                assert False, 'Unknown metadata type'

            # All streams must have been decoded
            assert workload.stream is not None

            # Pack the workload into scheduling streams
            if workload.stream not in self.streams:
                self.streams[workload.stream] = []

            self.streams[workload.stream].append(workload)
