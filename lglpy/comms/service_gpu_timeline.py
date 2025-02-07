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
handles record preprocessing and serializing the resulting GPU Timeline layer
frame records to a file on the host.
'''

import json
import struct
from typing import Any, TypedDict

from lglpy.comms.server import Message
from lglpy.timeline.protos.layer_driver import timeline_pb2


class RenderpassAttachmentMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    binding: str
    load: bool
    store: bool
    resolve: bool


class RenderpassMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    type: str
    tid: int
    width: int
    height: int
    drawCallCount: int
    subpassCount: int
    label: list[str]
    attachments: list[RenderpassAttachmentMetadataType]


class DispatchMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    type: str
    tid: int
    xGroups: int
    yGroups: int
    zGroups: int
    label: list[str]


class TraceRaysMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    type: str
    tid: int
    xItems: int
    yItems: int
    zItems: int
    label: list[str]


class ImageTransferMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    type: str
    tid: int
    subtype: str
    pixelCount: int
    label: list[str]


class BufferTransferMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    type: str
    tid: int
    subtype: str
    byteCount: int
    label: list[str]


class SubmitMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    device: int
    queue: int
    timestamp: int
    workloads: list[RenderpassMetadataType
                    | DispatchMetadataType
                    | TraceRaysMetadataType
                    | ImageTransferMetadataType
                    | BufferTransferMetadataType]


class FrameMetadataType(TypedDict):
    '''
    Structured dict type for type hinting.
    '''
    device: int
    frame: int
    presentTimestamp: int
    submits: list[SubmitMetadataType]


def expect_int(v: int | None) -> int:
    if v is None:
        return 0
    assert isinstance(v, int)
    return v


def map_renderpass_binding(type, index: int | None) -> str:
    '''
    Map the PB encoded renderpass attachment type to a corresponding description
    string
    '''
    if type == timeline_pb2.RenderpassAttachmentType.undefined:
        assert ((index is None) or (index == 0))
        return "U"
    elif type == timeline_pb2.RenderpassAttachmentType.color:
        assert (index is not None)
        return f"C{index}"
    elif type == timeline_pb2.RenderpassAttachmentType.depth:
        assert ((index is None) or (index == 0))
        return "D"
    elif type == timeline_pb2.RenderpassAttachmentType.stencil:
        assert ((index is None) or (index == 0))
        return "S"
    else:
        assert False


def map_image_transfer_type(type) -> str:
    '''
    Map the PB encoded image transfer type to some corresponding description
    string
    '''
    if type == timeline_pb2.ImageTransferType.unknown_image_transfer:
        return "Unknown"
    elif type == timeline_pb2.ImageTransferType.clear_image:
        return "Clear image"
    elif type == timeline_pb2.ImageTransferType.copy_image:
        return "Copy image"
    elif type == timeline_pb2.ImageTransferType.copy_buffer_to_image:
        return "Copy buffer to image"
    elif type == timeline_pb2.ImageTransferType.copy_image_to_buffer:
        return "Copy image to buffer"
    else:
        assert False


def map_buffer_transfer_type(type) -> str:
    '''
    Map the PB encoded image transfer type to some corresponding description
    string
    '''
    if type == timeline_pb2.BufferTransferType.unknown_buffer_transfer:
        return "Unknown"
    elif type == timeline_pb2.BufferTransferType.fill_buffer:
        return "Fill buffer"
    elif type == timeline_pb2.BufferTransferType.copy_buffer:
        return "Copy buffer"
    else:
        assert False


def map_debug_label(labels: list[str] | None) -> list[str]:
    '''
    Normalize the 'debug_label' field from the PB data
    '''
    if labels is None:
        return []
    # need to convert it to a list from a RepeatedScalarContainer
    return [str(label) for label in labels]


class GPUDeviceState:
    '''
    Holds per device state.

    Typically there will only be one physical device, and one corresponding
    VkDevice, but the protocol and API are both designed to support multiple
    devices so abstract that here.

    Args:
        device_id: The device id associated with the state object
    '''

    def __init__(self, device_id: int):
        '''
        Initialize the state for a single device
        '''
        # Create a default frame record
        # End time written on queuePresent
        self.frame: FrameMetadataType = {
            'device': device_id,
            'frame': 0,
            'presentTimestamp': 0,
            'submits': []
        }


class GPUTimelineService:
    '''
    A service for handling network comms from the layer_gpu_timeline layer.
    '''

    def __init__(self, file_path: str, verbose: bool = False):
        '''
        Initialize the timeline service.

        Args:
            file_path: File to write on the filesystem
            verbose: Should this use verbose logging?
        '''
        self.devices: dict[int, GPUDeviceState] = dict()
        self.last_submit: SubmitMetadataType | None = None
        self.last_render_pass: RenderpassMetadataType | None = None
        # pylint: disable=consider-using-with
        self.file_handle = open(file_path, 'wb')
        self.verbose = verbose
        self.seen_header = False

    def get_device(self, device: int) -> GPUDeviceState:
        '''
        Get or create a device object with the specified handle
         '''
        state = self.devices.get(device, None)
        if state is None:
            state = GPUDeviceState(device)
            self.devices[device] = state
        return state

    def get_service_name(self) -> str:
        '''
        Get the service endpoint name.

        Returns:
            The endpoint name.
        '''
        return 'GPUTimeline'

    def handle_header(self, msg: Any) -> None:
        '''
        Handle the header packet.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        assert msg.version_no == timeline_pb2.HeaderVersionNo.version_1
        assert not self.seen_header

        self.seen_header = True

    def handle_device(self, msg: Any) -> None:
        '''
        Handle a device config packet.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Reset the local frame state for the next frame
        device_id = expect_int(msg.id)
        self.devices[device_id] = GPUDeviceState(device_id)

        # This clears the last submit; expect a submit message before any new
        # workloads
        self.last_submit = None
        self.last_render_pass = None

        if self.verbose:
            major = expect_int(msg.major_version)
            minor = expect_int(msg.minor_version)
            patch = expect_int(msg.patch_version)
            print(f'Device:  {msg.name} (0x{device_id:02X})')
            print(f'Driver:  r{major}p{minor} ({patch})')
            print(f'Process: {msg.process_id}')

    def handle_frame(self, msg: Any) -> None:
        '''
        Handle a frame boundary workload.

        This will write the current frame record to the output file, and then
        reset the frame tracker ready for the next frame.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the device object
        device_id = expect_int(msg.device)
        device = self.get_device(device_id)

        # This clears the last submit; expect a submit message before any new
        # workloads
        self.last_submit = None
        self.last_render_pass = None

        # Update end time of the current frame
        device.frame['presentTimestamp'] = expect_int(msg.timestamp)

        # Write frame packet to the file
        # FIXME: No need to write the first empty frame?
        last_frame = json.dumps(device.frame).encode('utf-8')
        length = struct.pack('<I', len(last_frame))

        self.file_handle.write(length)
        self.file_handle.write(last_frame)

        # Reset the local frame state for the next frame
        next_frame = expect_int(msg.id)
        device.frame = {
            'device': device_id,
            'frame': next_frame,
            'presentTimestamp': 0,
            'submits': []
        }

        if self.verbose and (next_frame % 100 == 0):
            print(f'Starting frame {next_frame} for 0x{device_id:02X} ...')

    def handle_submit(self, msg: Any) -> None:
        '''
        Handle a submit boundary workload.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the device object
        device = self.get_device(expect_int(msg.device))

        # Write frame packet to the file
        submit: SubmitMetadataType = {
            'device': expect_int(msg.device),
            'queue': expect_int(msg.queue),
            'timestamp': expect_int(msg.timestamp),
            'workloads': []
        }

        # Reset the local frame state for the next frame
        device.frame['submits'].append(submit)

        # Track this new submit object; all subsequent workloads will attach to
        # it up to the point of the next submit/frame/device
        self.last_submit = submit
        self.last_render_pass = None

    def handle_render_pass(self, msg: Any) -> None:
        '''
        Handle a render pass workload.

        Render passes may generate multiple messages if suspended and resumed
        when using Vulkan 1.3 dynamic render passes; this message may be
        followed by zero or more continuation messages that will be
        merged into this renderpass.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        assert self.last_submit is not None
        submit = self.last_submit

        # Convert the PB message into our data representation
        renderpass: RenderpassMetadataType = {
            'type': 'renderpass',
            'tid': expect_int(msg.tag_id),
            'width': expect_int(msg.width),
            'height': expect_int(msg.height),
            'drawCallCount': expect_int(msg.draw_call_count),
            'subpassCount': expect_int(msg.subpass_count),
            'label': map_debug_label(msg.debug_label),
            'attachments': []
        }

        for pb_attachment in msg.attachments:
            attachment: RenderpassAttachmentMetadataType = {
                'binding': map_renderpass_binding(pb_attachment.type,
                                                  pb_attachment.index),
                'load': not bool(pb_attachment.not_loaded),
                'store': not bool(pb_attachment.not_stored),
                'resolve': bool(pb_attachment.resolved),
            }
            renderpass['attachments'].append(attachment)

        submit['workloads'].append(renderpass)

        # Save it, for any continuations
        self.last_render_pass = renderpass

    def handle_render_pass_continuation(self, msg: Any) -> None:
        '''
        Handle a render pass workload continuation.

        Render passes may generate multiple messages if suspended and resumed
        when using Vulkan 1.3 dynamic render passes, so merge those into a
        single workload.

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Validate that this is a continuation of the last renderpass
        assert ((self.last_render_pass is not None)
                and (self.last_render_pass['tid'] == expect_int(msg.tag_id)))

        # Don't accumulate if tag_id is flagged as ambiguous
        if self.last_render_pass['drawCallCount'] >= 0:
            dcc = expect_int(msg.draw_call_count)
            self.last_render_pass['drawCallCount'] += dcc

    def handle_dispatch(self, msg: Any) -> None:
        '''
        Handle a dispatch workload

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the active submit to append to
        assert self.last_submit is not None
        submit = self.last_submit

        # Clear the last renderpass
        self.last_render_pass = None

        # Convert the PB message into our data representation
        dispatch: DispatchMetadataType = {
            'type': 'dispatch',
            'tid': expect_int(msg.tag_id),
            'xGroups': expect_int(msg.x_groups),
            'yGroups': expect_int(msg.y_groups),
            'zGroups': expect_int(msg.z_groups),
            'label': map_debug_label(msg.debug_label),
        }

        submit['workloads'].append(dispatch)

    def handle_trace_rays(self, msg: Any) -> None:
        '''
        Handle a trace rays workload

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the active submit to append to
        assert self.last_submit is not None
        submit = self.last_submit

        # Clear the last renderpass
        self.last_render_pass = None

        # Convert the PB message into our data representation
        trace_rays: TraceRaysMetadataType = {
            'type': 'tracerays',
            'tid': expect_int(msg.tag_id),
            'xItems': expect_int(msg.x_items),
            'yItems': expect_int(msg.y_items),
            'zItems': expect_int(msg.z_items),
            'label': map_debug_label(msg.debug_label),
        }

        submit['workloads'].append(trace_rays)

    def handle_image_transfer(self, msg: Any) -> None:
        '''
        Handle an image transfer workload

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the active submit to append to
        assert self.last_submit is not None
        submit = self.last_submit

        # Clear the last renderpass
        self.last_render_pass = None

        # Convert the PB message into our data representation
        image_transfer: ImageTransferMetadataType = {
            'type': 'imagetransfer',
            'tid': expect_int(msg.tag_id),
            'subtype': map_image_transfer_type(msg.transfer_type),
            'pixelCount': expect_int(msg.pixel_count),
            'label': map_debug_label(msg.debug_label),
        }

        submit['workloads'].append(image_transfer)

    def handle_buffer_transfer(self, msg: Any) -> None:
        '''
        Handle a buffer transfer workload

        Args:
            msg: The Python decode of a Timeline PB payload.
        '''
        # Get the active submit to append to
        assert self.last_submit is not None
        submit = self.last_submit

        # Clear the last renderpass
        self.last_render_pass = None

        # Convert the PB message into our data representation
        buffer_transfer: BufferTransferMetadataType = {
            'type': 'buffertransfer',
            'tid': expect_int(msg.tag_id),
            'subtype': map_buffer_transfer_type(msg.transfer_type),
            'byteCount': expect_int(msg.byte_count),
            'label': map_debug_label(msg.debug_label),
        }

        submit['workloads'].append(buffer_transfer)

    def handle_message(self, message: Message) -> None:
        '''
        Handle a service request from a layer.

        Note that this service only expects pushed TX or TX_ASYNC messages, so
        never provides a response.
        '''
        pb_record = timeline_pb2.TimelineRecord()  # pylint: disable=no-member
        pb_record.ParseFromString(message.payload)

        # Assert there is at most one member message
        assert ((int(pb_record.HasField('header'))
                 + int(pb_record.HasField('metadata'))
                 + int(pb_record.HasField('frame'))
                 + int(pb_record.HasField('submit'))
                 + int(pb_record.HasField('renderpass'))
                 + int(pb_record.HasField('continue_renderpass'))
                 + int(pb_record.HasField('dispatch'))
                 + int(pb_record.HasField('trace_rays'))
                 + int(pb_record.HasField('image_transfer'))
                 + int(pb_record.HasField('buffer_transfer'))) <= 1)

        # Process the message
        if pb_record.HasField('header'):
            self.handle_header(pb_record.header)
        elif pb_record.HasField('metadata'):
            self.handle_device(pb_record.metadata)
        elif pb_record.HasField('frame'):
            self.handle_frame(pb_record.frame)
        elif pb_record.HasField('submit'):
            self.handle_submit(pb_record.submit)
        elif pb_record.HasField('renderpass'):
            self.handle_render_pass(pb_record.renderpass)
        elif pb_record.HasField('continue_renderpass'):
            self.handle_render_pass_continuation(pb_record.continue_renderpass)
        elif pb_record.HasField('dispatch'):
            self.handle_dispatch(pb_record.dispatch)
        elif pb_record.HasField('trace_rays'):
            self.handle_trace_rays(pb_record.trace_rays)
        elif pb_record.HasField('image_transfer'):
            self.handle_image_transfer(pb_record.image_transfer)
        elif pb_record.HasField('buffer_transfer'):
            self.handle_buffer_transfer(pb_record.buffer_transfer)
        else:
            assert False, f'Unknown payload {pb_record}'
