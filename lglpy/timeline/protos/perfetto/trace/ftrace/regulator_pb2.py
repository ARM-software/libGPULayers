# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/regulator.proto
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
    'protos/perfetto/trace/ftrace/regulator.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n,protos/perfetto/trace/ftrace/regulator.proto\x12\x0fperfetto.protos\"+\n\x1bRegulatorDisableFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\"3\n#RegulatorDisableCompleteFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\"*\n\x1aRegulatorEnableFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\"2\n\"RegulatorEnableCompleteFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\"/\n\x1fRegulatorEnableDelayFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\"H\n\x1eRegulatorSetVoltageFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0b\n\x03min\x18\x02 \x01(\x05\x12\x0b\n\x03max\x18\x03 \x01(\x05\"C\n&RegulatorSetVoltageCompleteFtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0b\n\x03val\x18\x02 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.regulator_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_REGULATORDISABLEFTRACEEVENT']._serialized_start=65
  _globals['_REGULATORDISABLEFTRACEEVENT']._serialized_end=108
  _globals['_REGULATORDISABLECOMPLETEFTRACEEVENT']._serialized_start=110
  _globals['_REGULATORDISABLECOMPLETEFTRACEEVENT']._serialized_end=161
  _globals['_REGULATORENABLEFTRACEEVENT']._serialized_start=163
  _globals['_REGULATORENABLEFTRACEEVENT']._serialized_end=205
  _globals['_REGULATORENABLECOMPLETEFTRACEEVENT']._serialized_start=207
  _globals['_REGULATORENABLECOMPLETEFTRACEEVENT']._serialized_end=257
  _globals['_REGULATORENABLEDELAYFTRACEEVENT']._serialized_start=259
  _globals['_REGULATORENABLEDELAYFTRACEEVENT']._serialized_end=306
  _globals['_REGULATORSETVOLTAGEFTRACEEVENT']._serialized_start=308
  _globals['_REGULATORSETVOLTAGEFTRACEEVENT']._serialized_end=380
  _globals['_REGULATORSETVOLTAGECOMPLETEFTRACEEVENT']._serialized_start=382
  _globals['_REGULATORSETVOLTAGECOMPLETEFTRACEEVENT']._serialized_end=449
# @@protoc_insertion_point(module_scope)
