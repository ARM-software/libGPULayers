# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/protolog.proto
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
    'protos/perfetto/trace/android/protolog.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.common import protolog_common_pb2 as protos_dot_perfetto_dot_common_dot_protolog__common__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,protos/perfetto/trace/android/protolog.proto\x12\x0fperfetto.protos\x1a,protos/perfetto/common/protolog_common.proto\"\x9b\x01\n\x0fProtoLogMessage\x12\x12\n\nmessage_id\x18\x01 \x01(\x06\x12\x16\n\x0estr_param_iids\x18\x02 \x03(\r\x12\x15\n\rsint64_params\x18\x03 \x03(\x12\x12\x15\n\rdouble_params\x18\x04 \x03(\x01\x12\x16\n\x0e\x62oolean_params\x18\x05 \x03(\x05\x12\x16\n\x0estacktrace_iid\x18\x06 \x01(\r\"\xd0\x02\n\x14ProtoLogViewerConfig\x12\x43\n\x08messages\x18\x01 \x03(\x0b\x32\x31.perfetto.protos.ProtoLogViewerConfig.MessageData\x12;\n\x06groups\x18\x02 \x03(\x0b\x32+.perfetto.protos.ProtoLogViewerConfig.Group\x1a\x85\x01\n\x0bMessageData\x12\x12\n\nmessage_id\x18\x01 \x01(\x06\x12\x0f\n\x07message\x18\x02 \x01(\t\x12-\n\x05level\x18\x03 \x01(\x0e\x32\x1e.perfetto.protos.ProtoLogLevel\x12\x10\n\x08group_id\x18\x04 \x01(\r\x12\x10\n\x08location\x18\x05 \x01(\t\x1a.\n\x05Group\x12\n\n\x02id\x18\x01 \x01(\r\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x0b\n\x03tag\x18\x03 \x01(\t')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.protolog_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PROTOLOGMESSAGE']._serialized_start=112
  _globals['_PROTOLOGMESSAGE']._serialized_end=267
  _globals['_PROTOLOGVIEWERCONFIG']._serialized_start=270
  _globals['_PROTOLOGVIEWERCONFIG']._serialized_end=606
  _globals['_PROTOLOGVIEWERCONFIG_MESSAGEDATA']._serialized_start=425
  _globals['_PROTOLOGVIEWERCONFIG_MESSAGEDATA']._serialized_end=558
  _globals['_PROTOLOGVIEWERCONFIG_GROUP']._serialized_start=560
  _globals['_PROTOLOGVIEWERCONFIG_GROUP']._serialized_end=606
# @@protoc_insertion_point(module_scope)
