# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/fence.proto
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
    'protos/perfetto/trace/ftrace/fence.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(protos/perfetto/trace/ftrace/fence.proto\x12\x0fperfetto.protos\"X\n\x14\x46\x65nceInitFtraceEvent\x12\x0f\n\x07\x63ontext\x18\x01 \x01(\r\x12\x0e\n\x06\x64river\x18\x02 \x01(\t\x12\r\n\x05seqno\x18\x03 \x01(\r\x12\x10\n\x08timeline\x18\x04 \x01(\t\"[\n\x17\x46\x65nceDestroyFtraceEvent\x12\x0f\n\x07\x63ontext\x18\x01 \x01(\r\x12\x0e\n\x06\x64river\x18\x02 \x01(\t\x12\r\n\x05seqno\x18\x03 \x01(\r\x12\x10\n\x08timeline\x18\x04 \x01(\t\"`\n\x1c\x46\x65nceEnableSignalFtraceEvent\x12\x0f\n\x07\x63ontext\x18\x01 \x01(\r\x12\x0e\n\x06\x64river\x18\x02 \x01(\t\x12\r\n\x05seqno\x18\x03 \x01(\r\x12\x10\n\x08timeline\x18\x04 \x01(\t\"\\\n\x18\x46\x65nceSignaledFtraceEvent\x12\x0f\n\x07\x63ontext\x18\x01 \x01(\r\x12\x0e\n\x06\x64river\x18\x02 \x01(\t\x12\r\n\x05seqno\x18\x03 \x01(\r\x12\x10\n\x08timeline\x18\x04 \x01(\t')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.fence_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_FENCEINITFTRACEEVENT']._serialized_start=61
  _globals['_FENCEINITFTRACEEVENT']._serialized_end=149
  _globals['_FENCEDESTROYFTRACEEVENT']._serialized_start=151
  _globals['_FENCEDESTROYFTRACEEVENT']._serialized_end=242
  _globals['_FENCEENABLESIGNALFTRACEEVENT']._serialized_start=244
  _globals['_FENCEENABLESIGNALFTRACEEVENT']._serialized_end=340
  _globals['_FENCESIGNALEDFTRACEEVENT']._serialized_start=342
  _globals['_FENCESIGNALEDFTRACEEVENT']._serialized_end=434
# @@protoc_insertion_point(module_scope)
