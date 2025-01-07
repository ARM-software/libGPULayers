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
import enum

import lglpy.timeline.data.raw_trace as raw


class GPUStreamID(enum.Enum):
    '''
    Symbolic mapping of known GPU scheduling stream IDs.
    '''
    COMPUTE = 0
    NONFRAGMENT = 1
    FRAGMENT = 2
    BINNING = 3
    MAIN = 4
    TRANSFER = 5

    @classmethod
    def get_ui_name(self, streamID) -> str:
        '''
        Get presentable name for a stream.
        '''
        HUMAN_NAMES = {
            self.COMPUTE: 'Compute',
            self.NONFRAGMENT: 'Non-fragment',
            self.FRAGMENT: 'Fragment',
            self.BINNING: 'Binning',
            self.MAIN: 'Main',
            self.TRANSFER: 'Transfer'
        }

        return HUMAN_NAMES[streamID]


class GPUStageID(enum.Enum):
    '''
    Symbolic mapping of known GPU workload stage IDs.
    '''
    COMPUTE = 0
    ADVANCED_GEOMETRY = 1
    VERTEX = 2
    FRAGMENT = 3
    BINNING = 4
    MAIN = 5
    IMAGE_TRANSFER = 6
    BUFFER_TRANSFER = 7

    @classmethod
    def get_ui_name(self, streamID) -> str:
        '''
        Get presentable name for a stream.
        '''
        HUMAN_NAMES = {
            self.COMPUTE: 'Compute',
            self.ADVANCED_GEOMETRY: 'Advanced geometry',
            self.VERTEX: 'Vertex',
            self.FRAGMENT: 'Fragment',
            self.BINNING: 'Binning',
            self.MAIN: 'Main',
            self.IMAGE_TRANSFER: 'Image transfer',
            self.BUFFER_TRANSFER: 'Buffer transfer'
        }

        return HUMAN_NAMES[streamID]


class GPUWorkload:
    '''
    Base class for workloads in a trace.
    '''

    def __init__(self, event, metadata):
        # Data we from the Perfetto event
        self.tag_id = event.user_label
        self.start_time = event.start_time
        self.duration = event.duration
        self.stream = event.stream
        self.stage = event.stage

        # Common data we get from the metadata
        self.frame = None
        self.label_stack = None
        if metadata:
            self.frame = metadata.frame
            self.label_stack = metadata.label_stack

    def get_long_label(self) -> str:
        return 'Long label'

    def get_short_label(self) -> str:
        return 'Short'


class GPURenderPassAttachment:
    '''
    Workload class representing a render pass attachment.
    '''

    def __init__(self, metadata):
        self.binding = metadata.binding
        self.is_loaded = metadata.is_loaded
        self.is_stored = metadata.is_stored
        self.is_resolved = metadata.is_resolved


class GPURenderPass(GPUWorkload):
    '''
    Workload class representing a render pass.
    '''

    def __init__(self, event, metadata):
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.workload_x = metadata.width
        self.workload_y = metadata.height
        self.draw_call_count = metadata.draw_call_count

        self.attachments = []
        for attachment in metadata.attachments.attachments:
            self.attachments.append(GPURenderPassAttachment(attachment))

    @classmethod
    def get_compact_string(cls, bindings):
        merge = ''.join(bindings)
        return ''.join([j for i, j in enumerate(merge) if j not in merge[:i]])

    def get_attachment_long_label(self):
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

    def get_attachment_short_label(self):
        bindings = [x.binding for x in self.attachments]
        present = f'[{self.get_compact_string(bindings)}]'
        return present

    def get_long_label(self):
        lines = []

        if self.label_stack:
            lines.append(self.label_stack[-1])

        if self.draw_call_count < 0:
            drawStr = 'Unknown draws'
        elif self.draw_call_count == 1:
            drawStr = '1 draw'
        else:
            drawStr = f'{self.draw_call_count} draws'

        line = f'{self.workload_x}x{self.workload_y} ({drawStr})'
        lines.append(line)

        line = self.get_attachment_long_label()
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self):
        lines = []

        line = f'{self.workload_x}x{self.workload_y}'
        lines.append(line)

        line = self.get_attachment_short_label()
        lines.append(line)

        return '\n'.join(lines)


class GPUDispatch(GPUWorkload):
    '''
    Workload class representing a render pass.
    '''

    def __init__(self, event, metadata):
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.workload_x = metadata.xGroups
        self.workload_y = metadata.yGroups
        self.workload_z = metadata.zGroups

    def get_long_label(self):
        lines = []

        if self.label_stack:
            lines.append(self.label_stack[-1])

        lines.append(self.get_short_label())
        return '\n'.join(lines)

    def get_short_label(self):
        lines = []

        # If indirect then show a placeholder
        if self.workload_x == -1:
            line = "?x?x? groups"
        # If not 3D then show a 2D dimension
        else:
            dims = [self.workload_x, self.workload_y]
            # If 3D then show the Z dimension, else skip it
            if self.workload_z > 1:
                dims.append(self.workload_z)

            line = f'{"x".join([str(x) for x in dims])} groups'

        lines.append(line)
        return '\n'.join(lines)


class GPUImageTransfer(GPUWorkload):
    '''
    Workload class representing an image transfer.
    '''

    def __init__(self, event, metadata):
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.transfer_type = metadata.subtype
        self.pixel_count = metadata.pixel_count

    def get_long_label(self):
        lines = []

        if self.label_stack:
            lines.append(self.label_stack[-1])

        # If indirect then show a placeholder
        if self.pixel_count == -1:
            line = f'{self.transfer_type} (? pixels)'
        else:
            s = 's' if self.pixel_count != 1 else ''
            line = f'{self.transfer_type} ({self.pixel_count} pixel{s})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self):
        return self.transfer_type


class GPUBufferTransfer(GPUWorkload):
    '''
    Workload class representing a buffer transfer transfer.
    '''

    def __init__(self, event, metadata):
        # Populate common data
        super().__init__(event, metadata)

        # We must have metadata so no need to check
        self.transfer_type = metadata.subtype
        self.byte_count = metadata.byte_count

    def get_long_label(self):
        lines = []

        if self.label_stack:
            lines.append(self.label_stack[-1])

        # If indirect then show a placeholder
        if self.byte_count == -1:
            line = f'{self.transfer_type} (? bytes)'
        else:
            s = 's' if self.byte_count != 1 else ''
            line = f'{self.transfer_type} ({self.byte_count} byte{s})'
        lines.append(line)

        return '\n'.join(lines)

    def get_short_label(self):
        return self.transfer_type

class GPUTrace:
    '''
    Decoded GPU trace, combining data sources into a single representation.
    '''
    def __init__(self, raw_trace):

        self.streams = {}

        for event in raw_trace.events:

            # Find the metadata record for this event if we have one
            event_meta = None
            if event.user_label in raw_trace.metadata:
                event_meta = raw_trace.metadata[event.user_label]

            # Generic event
            if not event_meta:
                workload = GPUWorkload(event, None)
            # Specific event
            elif isinstance(event_meta, raw.MetadataRenderPass):
                workload = GPURenderPass(event, event_meta)
            elif isinstance(event_meta, raw.MetadataDispatch):
                workload = GPUDispatch(event, event_meta)
            elif isinstance(event_meta, raw.MetadataImageTransfer):
                workload = GPUImageTransfer(event, event_meta)
            elif isinstance(event_meta, raw.MetadataBufferTransfer):
                workload = GPUBufferTransfer(event, event_meta)
            else:
                assert False, 'Unknown metadata type'

            # Pack the workload into scheduling streams
            if workload.stream not in self.streams:
                self.streams[workload.stream] = []

            self.streams[workload.stream].append(workload)
