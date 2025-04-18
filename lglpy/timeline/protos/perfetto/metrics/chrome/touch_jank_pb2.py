# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/chrome/touch_jank.proto
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
    'protos/perfetto/metrics/chrome/touch_jank.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.metrics import custom_options_pb2 as protos_dot_perfetto_dot_metrics_dot_custom__options__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n/protos/perfetto/metrics/chrome/touch_jank.proto\x12\x0fperfetto.protos\x1a,protos/perfetto/metrics/custom_options.proto\"\x89\x03\n\tTouchJank\x12\x35\n\x15touch_jank_percentage\x18\x01 \x01(\x01\x42\x16\x8a\xb5\x18\x12n%_smallerIsBetter\x12\'\n\x08touch_ms\x18\x02 \x01(\x01\x42\x15\x8a\xb5\x18\x11ms_biggerIsBetter\x12\x32\n\x13touch_processing_ms\x18\x03 \x01(\x01\x42\x15\x8a\xb5\x18\x11ms_biggerIsBetter\x12\x38\n\x18touch_jank_processing_ms\x18\x04 \x01(\x01\x42\x16\x8a\xb5\x18\x12ms_smallerIsBetter\x12\x38\n\x16num_touch_update_count\x18\x05 \x01(\x03\x42\x18\x8a\xb5\x18\x14\x63ount_biggerIsBetter\x12>\n\x1bnum_touch_update_jank_count\x18\x06 \x01(\x03\x42\x19\x8a\xb5\x18\x15\x63ount_smallerIsBetter\x12\x34\n\x14touch_jank_budget_ms\x18\x07 \x01(\x01\x42\x16\x8a\xb5\x18\x12ms_smallerIsBetter')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.chrome.touch_jank_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_percentage']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_percentage']._serialized_options = b'\212\265\030\022n%_smallerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['touch_ms']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_ms']._serialized_options = b'\212\265\030\021ms_biggerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['touch_processing_ms']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_processing_ms']._serialized_options = b'\212\265\030\021ms_biggerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_processing_ms']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_processing_ms']._serialized_options = b'\212\265\030\022ms_smallerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['num_touch_update_count']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['num_touch_update_count']._serialized_options = b'\212\265\030\024count_biggerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['num_touch_update_jank_count']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['num_touch_update_jank_count']._serialized_options = b'\212\265\030\025count_smallerIsBetter'
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_budget_ms']._loaded_options = None
  _globals['_TOUCHJANK'].fields_by_name['touch_jank_budget_ms']._serialized_options = b'\212\265\030\022ms_smallerIsBetter'
  _globals['_TOUCHJANK']._serialized_start=115
  _globals['_TOUCHJANK']._serialized_end=508
# @@protoc_insertion_point(module_scope)
