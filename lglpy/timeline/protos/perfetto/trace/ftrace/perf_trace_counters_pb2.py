# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/perf_trace_counters.proto
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
    'protos/perfetto/trace/ftrace/perf_trace_counters.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n6protos/perfetto/trace/ftrace/perf_trace_counters.proto\x12\x0fperfetto.protos\"\xa1\x02\n\x1eSchedSwitchWithCtrsFtraceEvent\x12\x0f\n\x07old_pid\x18\x01 \x01(\x05\x12\x0f\n\x07new_pid\x18\x02 \x01(\x05\x12\x0c\n\x04\x63\x63tr\x18\x03 \x01(\r\x12\x0c\n\x04\x63tr0\x18\x04 \x01(\r\x12\x0c\n\x04\x63tr1\x18\x05 \x01(\r\x12\x0c\n\x04\x63tr2\x18\x06 \x01(\r\x12\x0c\n\x04\x63tr3\x18\x07 \x01(\r\x12\r\n\x05lctr0\x18\x08 \x01(\r\x12\r\n\x05lctr1\x18\t \x01(\r\x12\x0c\n\x04\x63tr4\x18\n \x01(\r\x12\x0c\n\x04\x63tr5\x18\x0b \x01(\r\x12\x11\n\tprev_comm\x18\x0c \x01(\t\x12\x10\n\x08prev_pid\x18\r \x01(\x05\x12\x0b\n\x03\x63yc\x18\x0e \x01(\r\x12\x0c\n\x04inst\x18\x0f \x01(\r\x12\x0f\n\x07stallbm\x18\x10 \x01(\r\x12\x0c\n\x04l3dm\x18\x11 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.perf_trace_counters_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_SCHEDSWITCHWITHCTRSFTRACEEVENT']._serialized_start=76
  _globals['_SCHEDSWITCHWITHCTRSFTRACEEVENT']._serialized_end=365
# @@protoc_insertion_point(module_scope)
