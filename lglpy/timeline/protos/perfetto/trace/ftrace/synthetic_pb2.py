# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/synthetic.proto
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
    'protos/perfetto/trace/ftrace/synthetic.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,protos/perfetto/trace/ftrace/synthetic.proto\x12\x0fperfetto.protos\"X\n\x1bRssStatThrottledFtraceEvent\x12\x0c\n\x04\x63urr\x18\x01 \x01(\r\x12\x0e\n\x06member\x18\x02 \x01(\x05\x12\r\n\x05mm_id\x18\x03 \x01(\r\x12\x0c\n\x04size\x18\x04 \x01(\x03\"0\n\x1fSuspendResumeMinimalFtraceEvent\x12\r\n\x05start\x18\x01 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.synthetic_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_RSSSTATTHROTTLEDFTRACEEVENT']._serialized_start=65
  _globals['_RSSSTATTHROTTLEDFTRACEEVENT']._serialized_end=153
  _globals['_SUSPENDRESUMEMINIMALFTRACEEVENT']._serialized_start=155
  _globals['_SUSPENDRESUMEMINIMALFTRACEEVENT']._serialized_end=203
# @@protoc_insertion_point(module_scope)
