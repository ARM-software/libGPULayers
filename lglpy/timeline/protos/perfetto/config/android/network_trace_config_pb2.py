# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/android/network_trace_config.proto
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
    'protos/perfetto/config/android/network_trace_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9protos/perfetto/config/android/network_trace_config.proto\x12\x0fperfetto.protos\"\xab\x01\n\x18NetworkPacketTraceConfig\x12\x0f\n\x07poll_ms\x18\x01 \x01(\r\x12\x1d\n\x15\x61ggregation_threshold\x18\x02 \x01(\r\x12\x14\n\x0cintern_limit\x18\x03 \x01(\r\x12\x17\n\x0f\x64rop_local_port\x18\x04 \x01(\x08\x12\x18\n\x10\x64rop_remote_port\x18\x05 \x01(\x08\x12\x16\n\x0e\x64rop_tcp_flags\x18\x06 \x01(\x08')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.android.network_trace_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_NETWORKPACKETTRACECONFIG']._serialized_start=79
  _globals['_NETWORKPACKETTRACECONFIG']._serialized_end=250
# @@protoc_insertion_point(module_scope)
