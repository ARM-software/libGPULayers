# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/app_process_starts_metric.proto
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
    'protos/perfetto/metrics/android/app_process_starts_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?protos/perfetto/metrics/android/app_process_starts_metric.proto\x12\x0fperfetto.protos\"\xbe\x03\n\x1d\x41ndroidAppProcessStartsMetric\x12M\n\x08\x61ll_apps\x18\x01 \x03(\x0b\x32;.perfetto.protos.AndroidAppProcessStartsMetric.ProcessStart\x12Y\n\x14started_by_broadcast\x18\x02 \x03(\x0b\x32;.perfetto.protos.AndroidAppProcessStartsMetric.ProcessStart\x12W\n\x12started_by_service\x18\x03 \x03(\x0b\x32;.perfetto.protos.AndroidAppProcessStartsMetric.ProcessStart\x1a\x99\x01\n\x0cProcessStart\x12\x14\n\x0cprocess_name\x18\x01 \x01(\t\x12\x0e\n\x06intent\x18\x02 \x01(\t\x12\x0e\n\x06reason\x18\x03 \x01(\t\x12\x16\n\x0eproc_start_dur\x18\x04 \x01(\x03\x12\x14\n\x0c\x62ind_app_dur\x18\x05 \x01(\x03\x12\x12\n\nintent_dur\x18\x06 \x01(\x03\x12\x11\n\ttotal_dur\x18\x07 \x01(\x03')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.app_process_starts_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDAPPPROCESSSTARTSMETRIC']._serialized_start=85
  _globals['_ANDROIDAPPPROCESSSTARTSMETRIC']._serialized_end=531
  _globals['_ANDROIDAPPPROCESSSTARTSMETRIC_PROCESSSTART']._serialized_start=378
  _globals['_ANDROIDAPPPROCESSSTARTSMETRIC_PROCESSSTART']._serialized_end=531
# @@protoc_insertion_point(module_scope)
