# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/track_event/chrome_mojo_event_info.proto
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
    'protos/perfetto/trace/track_event/chrome_mojo_event_info.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n>protos/perfetto/trace/track_event/chrome_mojo_event_info.proto\x12\x0fperfetto.protos\"\xcc\x01\n\x13\x43hromeMojoEventInfo\x12$\n\x1cwatcher_notify_interface_tag\x18\x01 \x01(\t\x12\x10\n\x08ipc_hash\x18\x02 \x01(\r\x12\x1a\n\x12mojo_interface_tag\x18\x03 \x01(\t\x12!\n\x19mojo_interface_method_iid\x18\x04 \x01(\x04\x12\x10\n\x08is_reply\x18\x05 \x01(\x08\x12\x14\n\x0cpayload_size\x18\x06 \x01(\x04\x12\x16\n\x0e\x64\x61ta_num_bytes\x18\x07 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.track_event.chrome_mojo_event_info_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CHROMEMOJOEVENTINFO']._serialized_start=84
  _globals['_CHROMEMOJOEVENTINFO']._serialized_end=288
# @@protoc_insertion_point(module_scope)
