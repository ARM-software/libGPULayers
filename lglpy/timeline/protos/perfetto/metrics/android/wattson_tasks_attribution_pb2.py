# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/wattson_tasks_attribution.proto
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
    'protos/perfetto/metrics/android/wattson_tasks_attribution.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n?protos/perfetto/metrics/android/wattson_tasks_attribution.proto\x12\x0fperfetto.protos\"z\n$AndroidWattsonTasksAttributionMetric\x12\x16\n\x0emetric_version\x18\x01 \x01(\x05\x12:\n\ttask_info\x18\x02 \x03(\x0b\x32\'.perfetto.protos.AndroidWattsonTaskInfo\"\xab\x01\n\x16\x41ndroidWattsonTaskInfo\x12\x13\n\x0b\x65stimate_mw\x18\x01 \x01(\x02\x12\x14\n\x0c\x65stimate_mws\x18\x02 \x01(\x02\x12\x13\n\x0bthread_name\x18\x03 \x01(\t\x12\x14\n\x0cprocess_name\x18\x04 \x01(\t\x12\x14\n\x0cpackage_name\x18\x05 \x01(\t\x12\x11\n\tthread_id\x18\x06 \x01(\x05\x12\x12\n\nprocess_id\x18\x07 \x01(\x05')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.wattson_tasks_attribution_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDWATTSONTASKSATTRIBUTIONMETRIC']._serialized_start=84
  _globals['_ANDROIDWATTSONTASKSATTRIBUTIONMETRIC']._serialized_end=206
  _globals['_ANDROIDWATTSONTASKINFO']._serialized_start=209
  _globals['_ANDROIDWATTSONTASKINFO']._serialized_end=380
# @@protoc_insertion_point(module_scope)
