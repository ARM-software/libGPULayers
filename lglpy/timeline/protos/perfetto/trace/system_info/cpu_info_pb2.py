# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/system_info/cpu_info.proto
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
    'protos/perfetto/trace/system_info/cpu_info.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n0protos/perfetto/trace/system_info/cpu_info.proto\x12\x0fperfetto.protos\"v\n\x07\x43puInfo\x12*\n\x04\x63pus\x18\x01 \x03(\x0b\x32\x1c.perfetto.protos.CpuInfo.Cpu\x1a?\n\x03\x43pu\x12\x11\n\tprocessor\x18\x01 \x01(\t\x12\x13\n\x0b\x66requencies\x18\x02 \x03(\r\x12\x10\n\x08\x63\x61pacity\x18\x03 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.system_info.cpu_info_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CPUINFO']._serialized_start=69
  _globals['_CPUINFO']._serialized_end=187
  _globals['_CPUINFO_CPU']._serialized_start=124
  _globals['_CPUINFO_CPU']._serialized_end=187
# @@protoc_insertion_point(module_scope)
