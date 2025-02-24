# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/common/perf_events.proto
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
    'protos/perfetto/common/perf_events.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(protos/perfetto/common/perf_events.proto\x12\x0fperfetto.protos\"\xc7\x08\n\nPerfEvents\x1a\xc5\x02\n\x08Timebase\x12\x13\n\tfrequency\x18\x02 \x01(\x04H\x00\x12\x10\n\x06period\x18\x01 \x01(\x04H\x00\x12\x36\n\x07\x63ounter\x18\x04 \x01(\x0e\x32#.perfetto.protos.PerfEvents.CounterH\x01\x12<\n\ntracepoint\x18\x03 \x01(\x0b\x32&.perfetto.protos.PerfEvents.TracepointH\x01\x12\x39\n\traw_event\x18\x05 \x01(\x0b\x32$.perfetto.protos.PerfEvents.RawEventH\x01\x12>\n\x0ftimestamp_clock\x18\x0b \x01(\x0e\x32%.perfetto.protos.PerfEvents.PerfClock\x12\x0c\n\x04name\x18\n \x01(\tB\n\n\x08intervalB\x07\n\x05\x65vent\x1a*\n\nTracepoint\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0e\n\x06\x66ilter\x18\x02 \x01(\t\x1aJ\n\x08RawEvent\x12\x0c\n\x04type\x18\x01 \x01(\r\x12\x0e\n\x06\x63onfig\x18\x02 \x01(\x04\x12\x0f\n\x07\x63onfig1\x18\x03 \x01(\x04\x12\x0f\n\x07\x63onfig2\x18\x04 \x01(\x04\"\xe8\x03\n\x07\x43ounter\x12\x13\n\x0fUNKNOWN_COUNTER\x10\x00\x12\x10\n\x0cSW_CPU_CLOCK\x10\x01\x12\x12\n\x0eSW_PAGE_FAULTS\x10\x02\x12\x11\n\rSW_TASK_CLOCK\x10\x03\x12\x17\n\x13SW_CONTEXT_SWITCHES\x10\x04\x12\x15\n\x11SW_CPU_MIGRATIONS\x10\x05\x12\x16\n\x12SW_PAGE_FAULTS_MIN\x10\x06\x12\x16\n\x12SW_PAGE_FAULTS_MAJ\x10\x07\x12\x17\n\x13SW_ALIGNMENT_FAULTS\x10\x08\x12\x17\n\x13SW_EMULATION_FAULTS\x10\t\x12\x0c\n\x08SW_DUMMY\x10\x14\x12\x11\n\rHW_CPU_CYCLES\x10\n\x12\x13\n\x0fHW_INSTRUCTIONS\x10\x0b\x12\x17\n\x13HW_CACHE_REFERENCES\x10\x0c\x12\x13\n\x0fHW_CACHE_MISSES\x10\r\x12\x1a\n\x16HW_BRANCH_INSTRUCTIONS\x10\x0e\x12\x14\n\x10HW_BRANCH_MISSES\x10\x0f\x12\x11\n\rHW_BUS_CYCLES\x10\x10\x12\x1e\n\x1aHW_STALLED_CYCLES_FRONTEND\x10\x11\x12\x1d\n\x19HW_STALLED_CYCLES_BACKEND\x10\x12\x12\x15\n\x11HW_REF_CPU_CYCLES\x10\x13\"\x8d\x01\n\tPerfClock\x12\x16\n\x12UNKNOWN_PERF_CLOCK\x10\x00\x12\x17\n\x13PERF_CLOCK_REALTIME\x10\x01\x12\x18\n\x14PERF_CLOCK_MONOTONIC\x10\x02\x12\x1c\n\x18PERF_CLOCK_MONOTONIC_RAW\x10\x03\x12\x17\n\x13PERF_CLOCK_BOOTTIME\x10\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.common.perf_events_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PERFEVENTS']._serialized_start=62
  _globals['_PERFEVENTS']._serialized_end=1157
  _globals['_PERFEVENTS_TIMEBASE']._serialized_start=77
  _globals['_PERFEVENTS_TIMEBASE']._serialized_end=402
  _globals['_PERFEVENTS_TRACEPOINT']._serialized_start=404
  _globals['_PERFEVENTS_TRACEPOINT']._serialized_end=446
  _globals['_PERFEVENTS_RAWEVENT']._serialized_start=448
  _globals['_PERFEVENTS_RAWEVENT']._serialized_end=522
  _globals['_PERFEVENTS_COUNTER']._serialized_start=525
  _globals['_PERFEVENTS_COUNTER']._serialized_end=1013
  _globals['_PERFEVENTS_PERFCLOCK']._serialized_start=1016
  _globals['_PERFEVENTS_PERFCLOCK']._serialized_end=1157
# @@protoc_insertion_point(module_scope)
