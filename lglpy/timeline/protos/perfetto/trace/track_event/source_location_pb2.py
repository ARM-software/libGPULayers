# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/track_event/source_location.proto
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
    'protos/perfetto/trace/track_event/source_location.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7protos/perfetto/trace/track_event/source_location.proto\x12\x0fperfetto.protos\"M\n\x1aUnsymbolizedSourceLocation\x12\x0b\n\x03iid\x18\x01 \x01(\x04\x12\x12\n\nmapping_id\x18\x02 \x01(\x04\x12\x0e\n\x06rel_pc\x18\x03 \x01(\x04\"\\\n\x0eSourceLocation\x12\x0b\n\x03iid\x18\x01 \x01(\x04\x12\x11\n\tfile_name\x18\x02 \x01(\t\x12\x15\n\rfunction_name\x18\x03 \x01(\t\x12\x13\n\x0bline_number\x18\x04 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.track_event.source_location_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_UNSYMBOLIZEDSOURCELOCATION']._serialized_start=76
  _globals['_UNSYMBOLIZEDSOURCELOCATION']._serialized_end=153
  _globals['_SOURCELOCATION']._serialized_start=155
  _globals['_SOURCELOCATION']._serialized_end=247
# @@protoc_insertion_point(module_scope)
