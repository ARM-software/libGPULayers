# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/etw/etw_config.proto
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
    'protos/perfetto/config/etw/etw_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+protos/perfetto/config/etw/etw_config.proto\x12\x0fperfetto.protos\"s\n\tEtwConfig\x12;\n\x0ckernel_flags\x18\x01 \x03(\x0e\x32%.perfetto.protos.EtwConfig.KernelFlag\")\n\nKernelFlag\x12\x0b\n\x07\x43SWITCH\x10\x00\x12\x0e\n\nDISPATCHER\x10\x01')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.etw.etw_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ETWCONFIG']._serialized_start=64
  _globals['_ETWCONFIG']._serialized_end=179
  _globals['_ETWCONFIG_KERNELFLAG']._serialized_start=138
  _globals['_ETWCONFIG_KERNELFLAG']._serialized_end=179
# @@protoc_insertion_point(module_scope)
