# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ps/process_stats.proto
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
    'protos/perfetto/trace/ps/process_stats.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,protos/perfetto/trace/ps/process_stats.proto\x12\x0fperfetto.protos\"\xa4\x06\n\x0cProcessStats\x12\x38\n\tprocesses\x18\x01 \x03(\x0b\x32%.perfetto.protos.ProcessStats.Process\x12 \n\x18\x63ollection_end_timestamp\x18\x02 \x01(\x04\x1a\'\n\x06Thread\x12\x0b\n\x03tid\x18\x01 \x01(\x05J\x04\x08\x02\x10\x03J\x04\x08\x03\x10\x04J\x04\x08\x04\x10\x05\x1a\"\n\x06\x46\x44Info\x12\n\n\x02\x66\x64\x18\x01 \x01(\x04\x12\x0c\n\x04path\x18\x02 \x01(\t\x1a\xea\x04\n\x07Process\x12\x0b\n\x03pid\x18\x01 \x01(\x05\x12\x35\n\x07threads\x18\x0b \x03(\x0b\x32$.perfetto.protos.ProcessStats.Thread\x12\x12\n\nvm_size_kb\x18\x02 \x01(\x04\x12\x11\n\tvm_rss_kb\x18\x03 \x01(\x04\x12\x13\n\x0brss_anon_kb\x18\x04 \x01(\x04\x12\x13\n\x0brss_file_kb\x18\x05 \x01(\x04\x12\x14\n\x0crss_shmem_kb\x18\x06 \x01(\x04\x12\x12\n\nvm_swap_kb\x18\x07 \x01(\x04\x12\x14\n\x0cvm_locked_kb\x18\x08 \x01(\x04\x12\x11\n\tvm_hwm_kb\x18\t \x01(\x04\x12\x15\n\room_score_adj\x18\n \x01(\x03\x12\x1e\n\x16is_peak_rss_resettable\x18\x0c \x01(\x08\x12#\n\x1b\x63hrome_private_footprint_kb\x18\r \x01(\r\x12#\n\x1b\x63hrome_peak_resident_set_kb\x18\x0e \x01(\r\x12\x31\n\x03\x66\x64s\x18\x0f \x03(\x0b\x32$.perfetto.protos.ProcessStats.FDInfo\x12\x12\n\nsmr_rss_kb\x18\x10 \x01(\x04\x12\x12\n\nsmr_pss_kb\x18\x11 \x01(\x04\x12\x17\n\x0fsmr_pss_anon_kb\x18\x12 \x01(\x04\x12\x17\n\x0fsmr_pss_file_kb\x18\x13 \x01(\x04\x12\x18\n\x10smr_pss_shmem_kb\x18\x14 \x01(\x04\x12\x17\n\x0fsmr_swap_pss_kb\x18\x17 \x01(\x04\x12\x19\n\x11runtime_user_mode\x18\x15 \x01(\x04\x12\x1b\n\x13runtime_kernel_mode\x18\x16 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ps.process_stats_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PROCESSSTATS']._serialized_start=66
  _globals['_PROCESSSTATS']._serialized_end=870
  _globals['_PROCESSSTATS_THREAD']._serialized_start=174
  _globals['_PROCESSSTATS_THREAD']._serialized_end=213
  _globals['_PROCESSSTATS_FDINFO']._serialized_start=215
  _globals['_PROCESSSTATS_FDINFO']._serialized_end=249
  _globals['_PROCESSSTATS_PROCESS']._serialized_start=252
  _globals['_PROCESSSTATS_PROCESS']._serialized_end=870
# @@protoc_insertion_point(module_scope)
