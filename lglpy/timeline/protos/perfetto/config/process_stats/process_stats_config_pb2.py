# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/process_stats/process_stats_config.proto
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
    'protos/perfetto/config/process_stats/process_stats_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?protos/perfetto/config/process_stats/process_stats_config.proto\x12\x0fperfetto.protos\"\xa6\x03\n\x12ProcessStatsConfig\x12:\n\x06quirks\x18\x01 \x03(\x0e\x32*.perfetto.protos.ProcessStatsConfig.Quirks\x12#\n\x1bscan_all_processes_on_start\x18\x02 \x01(\x08\x12\x1b\n\x13record_thread_names\x18\x03 \x01(\x08\x12\x1a\n\x12proc_stats_poll_ms\x18\x04 \x01(\r\x12\x1f\n\x17proc_stats_cache_ttl_ms\x18\x06 \x01(\r\x12\x1b\n\x13resolve_process_fds\x18\t \x01(\x08\x12\x19\n\x11scan_smaps_rollup\x18\n \x01(\x08\x12\x1a\n\x12record_process_age\x18\x0b \x01(\x08\x12\x1e\n\x16record_process_runtime\x18\x0c \x01(\x08\"U\n\x06Quirks\x12\x16\n\x12QUIRKS_UNSPECIFIED\x10\x00\x12\x1c\n\x14\x44ISABLE_INITIAL_DUMP\x10\x01\x1a\x02\x08\x01\x12\x15\n\x11\x44ISABLE_ON_DEMAND\x10\x02J\x04\x08\x07\x10\x08J\x04\x08\x08\x10\t')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.process_stats.process_stats_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PROCESSSTATSCONFIG_QUIRKS'].values_by_name["DISABLE_INITIAL_DUMP"]._loaded_options = None
  _globals['_PROCESSSTATSCONFIG_QUIRKS'].values_by_name["DISABLE_INITIAL_DUMP"]._serialized_options = b'\010\001'
  _globals['_PROCESSSTATSCONFIG']._serialized_start=85
  _globals['_PROCESSSTATSCONFIG']._serialized_end=507
  _globals['_PROCESSSTATSCONFIG_QUIRKS']._serialized_start=410
  _globals['_PROCESSSTATSCONFIG_QUIRKS']._serialized_end=495
# @@protoc_insertion_point(module_scope)
