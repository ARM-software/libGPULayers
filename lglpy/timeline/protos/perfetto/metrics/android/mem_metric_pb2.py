# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/mem_metric.proto
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
    'protos/perfetto/metrics/android/mem_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n0protos/perfetto/metrics/android/mem_metric.proto\x12\x0fperfetto.protos\"\xc6\x06\n\x13\x41ndroidMemoryMetric\x12L\n\x0fprocess_metrics\x18\x01 \x03(\x0b\x32\x33.perfetto.protos.AndroidMemoryMetric.ProcessMetrics\x1a\xce\x01\n\x0eProcessMetrics\x12\x14\n\x0cprocess_name\x18\x01 \x01(\t\x12R\n\x0etotal_counters\x18\x02 \x01(\x0b\x32:.perfetto.protos.AndroidMemoryMetric.ProcessMemoryCounters\x12R\n\x12priority_breakdown\x18\x03 \x03(\x0b\x32\x36.perfetto.protos.AndroidMemoryMetric.PriorityBreakdown\x1as\n\x11PriorityBreakdown\x12\x10\n\x08priority\x18\x01 \x01(\t\x12L\n\x08\x63ounters\x18\x02 \x01(\x0b\x32:.perfetto.protos.AndroidMemoryMetric.ProcessMemoryCounters\x1a\xd9\x02\n\x15ProcessMemoryCounters\x12>\n\x08\x61non_rss\x18\x01 \x01(\x0b\x32,.perfetto.protos.AndroidMemoryMetric.Counter\x12>\n\x08\x66ile_rss\x18\x02 \x01(\x0b\x32,.perfetto.protos.AndroidMemoryMetric.Counter\x12:\n\x04swap\x18\x03 \x01(\x0b\x32,.perfetto.protos.AndroidMemoryMetric.Counter\x12\x43\n\ranon_and_swap\x18\x04 \x01(\x0b\x32,.perfetto.protos.AndroidMemoryMetric.Counter\x12?\n\tjava_heap\x18\x05 \x01(\x0b\x32,.perfetto.protos.AndroidMemoryMetric.Counter\x1a?\n\x07\x43ounter\x12\x0b\n\x03min\x18\x01 \x01(\x01\x12\x0b\n\x03max\x18\x02 \x01(\x01\x12\x0b\n\x03\x61vg\x18\x03 \x01(\x01\x12\r\n\x05\x64\x65lta\x18\x04 \x01(\x01')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.mem_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDMEMORYMETRIC']._serialized_start=70
  _globals['_ANDROIDMEMORYMETRIC']._serialized_end=908
  _globals['_ANDROIDMEMORYMETRIC_PROCESSMETRICS']._serialized_start=172
  _globals['_ANDROIDMEMORYMETRIC_PROCESSMETRICS']._serialized_end=378
  _globals['_ANDROIDMEMORYMETRIC_PRIORITYBREAKDOWN']._serialized_start=380
  _globals['_ANDROIDMEMORYMETRIC_PRIORITYBREAKDOWN']._serialized_end=495
  _globals['_ANDROIDMEMORYMETRIC_PROCESSMEMORYCOUNTERS']._serialized_start=498
  _globals['_ANDROIDMEMORYMETRIC_PROCESSMEMORYCOUNTERS']._serialized_end=843
  _globals['_ANDROIDMEMORYMETRIC_COUNTER']._serialized_start=845
  _globals['_ANDROIDMEMORYMETRIC_COUNTER']._serialized_end=908
# @@protoc_insertion_point(module_scope)
