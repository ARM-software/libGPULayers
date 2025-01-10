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
    MetadataRenderPass, MetadataDispatch, MetadataBufferTransfer, \
    MetadataImageTransfer, GPUStreamID, GPUStageID

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
        self.tag_id = event.user_label
        self.start_time = event.start_time
        self.duration = event.duration
        self.stream = event.stream
        self.stage = event.stage

        # Common data we get from the layer metadata
        self.frame = None
        self.label_stack = None
        self.parsed_label_name = None

        if metadata:
            self.frame = metadata.frame
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
            return GPUStageID.get_ui_name(self.stage)

        return label

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        assert False, 'Subclass must implement this'
        return ''

    def get_short_label(self) -> str:
        '''
        Get the short form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        assert False, 'Subclass must implement this'
        return ''


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
        bindings = [x.binding for x in self.attachments]
        present = self.get_compact_string(bindings)

        bindings = [x.binding for x in self.attachments if x.is_loaded]
        loaded = self.get_compact_string(bindings)

        bindings = [x.binding for x in self.attachments if x.is_stored]
        stored = self.get_compact_string(bindings)

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
        bindings = [x.binding for x in self.attachments]
        present = f'[{self.get_compact_string(bindings)}]'
        return present

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        if self.draw_call_count < 0:
            draw_str = 'Unknown draws'
        elif self.draw_call_count == 1:
            draw_str = '1 draw'
        else:
            draw_str = f'{self.draw_call_count} draws'

        line = f'{self.width}x{self.height} ({draw_str})'
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

        line = f'{self.width}x{self.height}'
        lines.append(line)

        line = self.get_attachment_short_label()
        lines.append(line)

        return '\n'.join(lines)


class GPUDispatch(GPUWorkload):
    '''
    Workload class representing a render pass.
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

        # If indirect then show a placeholder
        if self.groups_x == -1:
            line = "?x?x? groups"

        # Else show the actual dimension
        else:
            dims = [self.groups_x, self.groups_y]

            # Hide Z dimension unless greater than 1
            if self.groups_z > 1:
                dims.append(self.groups_z)

            line = f'{"x".join([str(dim) for dim in dims])} groups'

        lines.append(line)
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

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        # If indirect then show a placeholder
        if self.pixel_count == -1:
            line = f'{self.transfer_type} (? pixels)'
        else:
            s = 's' if self.pixel_count != 1 else ''
            line = f'{self.transfer_type} ({self.pixel_count} pixel{s})'
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

    def get_long_label(self) -> str:
        '''
        Get the long form label for this workload.

        Returns:
            Returns the label for use in the UI.
        '''
        lines = []

        if label_name := self.get_label_name():
            lines.append(label_name)

        # If indirect then show a placeholder
        if self.byte_count == -1:
            line = f'{self.transfer_type} (? bytes)'
        else:
            s = 's' if self.byte_count != 1 else ''
            line = f'{self.transfer_type} ({self.byte_count} byte{s})'
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
    GPUImageTransfer,
    GPUBufferTransfer
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

            elif isinstance(event_meta, MetadataImageTransfer):
                workload = GPUImageTransfer(event, event_meta)

            elif isinstance(event_meta, MetadataBufferTransfer):
                workload = GPUBufferTransfer(event, event_meta)

            else:
                assert False, 'Unknown metadata type'

            # All streams must have been decoded
            assert workload.stream is not None

            # Pack the workload into scheduling streams
            if workload.stream not in self.streams:
                self.streams[workload.stream] = []

            self.streams[workload.stream].append(workload)
