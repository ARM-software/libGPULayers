# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/android_blocking_calls_cuj_metric.proto
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
    'protos/perfetto/metrics/android/android_blocking_calls_cuj_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.metrics.android import android_blocking_call_pb2 as protos_dot_perfetto_dot_metrics_dot_android_dot_android__blocking__call__pb2
from protos.perfetto.metrics.android import process_metadata_pb2 as protos_dot_perfetto_dot_metrics_dot_android_dot_process__metadata__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nGprotos/perfetto/metrics/android/android_blocking_calls_cuj_metric.proto\x12\x0fperfetto.protos\x1a;protos/perfetto/metrics/android/android_blocking_call.proto\x1a\x36protos/perfetto/metrics/android/process_metadata.proto\"\x93\x02\n\x1d\x41ndroidBlockingCallsCujMetric\x12?\n\x03\x63uj\x18\x01 \x03(\x0b\x32\x32.perfetto.protos.AndroidBlockingCallsCujMetric.Cuj\x1a\xb0\x01\n\x03\x43uj\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\x38\n\x07process\x18\x03 \x01(\x0b\x32\'.perfetto.protos.AndroidProcessMetadata\x12\n\n\x02ts\x18\x04 \x01(\x03\x12\x0b\n\x03\x64ur\x18\x05 \x01(\x03\x12<\n\x0e\x62locking_calls\x18\x06 \x03(\x0b\x32$.perfetto.protos.AndroidBlockingCall')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.android_blocking_calls_cuj_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDBLOCKINGCALLSCUJMETRIC']._serialized_start=210
  _globals['_ANDROIDBLOCKINGCALLSCUJMETRIC']._serialized_end=485
  _globals['_ANDROIDBLOCKINGCALLSCUJMETRIC_CUJ']._serialized_start=309
  _globals['_ANDROIDBLOCKINGCALLSCUJMETRIC_CUJ']._serialized_end=485
# @@protoc_insertion_point(module_scope)
