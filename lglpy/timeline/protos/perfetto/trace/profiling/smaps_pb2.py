# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/profiling/smaps.proto
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
    'protos/perfetto/trace/profiling/smaps.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+protos/perfetto/trace/profiling/smaps.proto\x12\x0fperfetto.protos\"\x83\x03\n\nSmapsEntry\x12\x0c\n\x04path\x18\x01 \x01(\t\x12\x0f\n\x07size_kb\x18\x02 \x01(\x04\x12\x18\n\x10private_dirty_kb\x18\x03 \x01(\x04\x12\x0f\n\x07swap_kb\x18\x04 \x01(\x04\x12\x11\n\tfile_name\x18\x05 \x01(\t\x12\x15\n\rstart_address\x18\x06 \x01(\x04\x12\x18\n\x10module_timestamp\x18\x07 \x01(\x04\x12\x16\n\x0emodule_debugid\x18\x08 \x01(\t\x12\x19\n\x11module_debug_path\x18\t \x01(\t\x12\x18\n\x10protection_flags\x18\n \x01(\r\x12!\n\x19private_clean_resident_kb\x18\x0b \x01(\x04\x12 \n\x18shared_dirty_resident_kb\x18\x0c \x01(\x04\x12 \n\x18shared_clean_resident_kb\x18\r \x01(\x04\x12\x11\n\tlocked_kb\x18\x0e \x01(\x04\x12 \n\x18proportional_resident_kb\x18\x0f \x01(\x04\"H\n\x0bSmapsPacket\x12\x0b\n\x03pid\x18\x01 \x01(\r\x12,\n\x07\x65ntries\x18\x02 \x03(\x0b\x32\x1b.perfetto.protos.SmapsEntry')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.profiling.smaps_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_SMAPSENTRY']._serialized_start=65
  _globals['_SMAPSENTRY']._serialized_end=452
  _globals['_SMAPSPACKET']._serialized_start=454
  _globals['_SMAPSPACKET']._serialized_end=526
# @@protoc_insertion_point(module_scope)
