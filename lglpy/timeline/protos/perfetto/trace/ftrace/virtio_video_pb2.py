# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/virtio_video.proto
# Protobuf Python Version: 5.27.3
'''Generated protocol buffer code.'''
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import runtime_version as _runtime_version
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
_runtime_version.ValidateProtobufRuntimeVersion(
    _runtime_version.Domain.PUBLIC,
    5,
    27,
    3,
    '',
    'protos/perfetto/trace/ftrace/virtio_video.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/protos/perfetto/trace/ftrace/virtio_video.proto\x12\x0fperfetto.protos\"<\n\x19VirtioVideoCmdFtraceEvent\x12\x11\n\tstream_id\x18\x01 \x01(\r\x12\x0c\n\x04type\x18\x02 \x01(\r\"@\n\x1dVirtioVideoCmdDoneFtraceEvent\x12\x11\n\tstream_id\x18\x01 \x01(\r\x12\x0c\n\x04type\x18\x02 \x01(\r\"\xc4\x01\n#VirtioVideoResourceQueueFtraceEvent\x12\x12\n\ndata_size0\x18\x01 \x01(\r\x12\x12\n\ndata_size1\x18\x02 \x01(\r\x12\x12\n\ndata_size2\x18\x03 \x01(\r\x12\x12\n\ndata_size3\x18\x04 \x01(\r\x12\x12\n\nqueue_type\x18\x05 \x01(\r\x12\x13\n\x0bresource_id\x18\x06 \x01(\x05\x12\x11\n\tstream_id\x18\x07 \x01(\x05\x12\x11\n\ttimestamp\x18\x08 \x01(\x04\"\xc8\x01\n\'VirtioVideoResourceQueueDoneFtraceEvent\x12\x12\n\ndata_size0\x18\x01 \x01(\r\x12\x12\n\ndata_size1\x18\x02 \x01(\r\x12\x12\n\ndata_size2\x18\x03 \x01(\r\x12\x12\n\ndata_size3\x18\x04 \x01(\r\x12\x12\n\nqueue_type\x18\x05 \x01(\r\x12\x13\n\x0bresource_id\x18\x06 \x01(\x05\x12\x11\n\tstream_id\x18\x07 \x01(\x05\x12\x11\n\ttimestamp\x18\x08 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.virtio_video_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_VIRTIOVIDEOCMDFTRACEEVENT']._serialized_start=68
  _globals['_VIRTIOVIDEOCMDFTRACEEVENT']._serialized_end=128
  _globals['_VIRTIOVIDEOCMDDONEFTRACEEVENT']._serialized_start=130
  _globals['_VIRTIOVIDEOCMDDONEFTRACEEVENT']._serialized_end=194
  _globals['_VIRTIOVIDEORESOURCEQUEUEFTRACEEVENT']._serialized_start=197
  _globals['_VIRTIOVIDEORESOURCEQUEUEFTRACEEVENT']._serialized_end=393
  _globals['_VIRTIOVIDEORESOURCEQUEUEDONEFTRACEEVENT']._serialized_start=396
  _globals['_VIRTIOVIDEORESOURCEQUEUEDONEFTRACEEVENT']._serialized_end=596
# @@protoc_insertion_point(module_scope)