# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/io_metric.proto
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
    'protos/perfetto/metrics/android/io_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/protos/perfetto/metrics/android/io_metric.proto\x12\x0fperfetto.protos\"\xce\x03\n\tAndroidIo\x12G\n\x12\x66\x32\x66s_counter_stats\x18\x01 \x03(\x0b\x32+.perfetto.protos.AndroidIo.F2fsCounterStats\x12\x43\n\x10\x66\x32\x66s_write_stats\x18\x02 \x03(\x0b\x32).perfetto.protos.AndroidIo.F2fsWriteStats\x1ap\n\x10\x46\x32\x66sCounterStats\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0b\n\x03max\x18\x02 \x01(\x01\x12\x0b\n\x03sum\x18\x03 \x01(\x01\x12\x0b\n\x03min\x18\x05 \x01(\x01\x12\x0b\n\x03\x64ur\x18\x06 \x01(\x03\x12\r\n\x05\x63ount\x18\x07 \x01(\x03\x12\x0b\n\x03\x61vg\x18\x08 \x01(\x01\x1a\xc0\x01\n\x0e\x46\x32\x66sWriteStats\x12\x19\n\x11total_write_count\x18\x01 \x01(\x03\x12\x1a\n\x12\x64istinct_processes\x18\x02 \x01(\x03\x12\x1b\n\x13total_bytes_written\x18\x03 \x01(\x03\x12\x1d\n\x15\x64istinct_device_count\x18\x04 \x01(\x03\x12\x1c\n\x14\x64istinct_inode_count\x18\x05 \x01(\x03\x12\x1d\n\x15\x64istinct_thread_count\x18\x06 \x01(\x03')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.io_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDIO']._serialized_start=69
  _globals['_ANDROIDIO']._serialized_end=531
  _globals['_ANDROIDIO_F2FSCOUNTERSTATS']._serialized_start=224
  _globals['_ANDROIDIO_F2FSCOUNTERSTATS']._serialized_end=336
  _globals['_ANDROIDIO_F2FSWRITESTATS']._serialized_start=339
  _globals['_ANDROIDIO_F2FSWRITESTATS']._serialized_end=531
# @@protoc_insertion_point(module_scope)
