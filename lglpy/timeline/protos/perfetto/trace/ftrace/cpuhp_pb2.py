# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/cpuhp.proto
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
    'protos/perfetto/trace/ftrace/cpuhp.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(protos/perfetto/trace/ftrace/cpuhp.proto\x12\x0fperfetto.protos\"L\n\x14\x43puhpExitFtraceEvent\x12\x0b\n\x03\x63pu\x18\x01 \x01(\r\x12\x0b\n\x03idx\x18\x02 \x01(\x05\x12\x0b\n\x03ret\x18\x03 \x01(\x05\x12\r\n\x05state\x18\x04 \x01(\x05\"S\n\x1a\x43puhpMultiEnterFtraceEvent\x12\x0b\n\x03\x63pu\x18\x01 \x01(\r\x12\x0b\n\x03\x66un\x18\x02 \x01(\x04\x12\x0b\n\x03idx\x18\x03 \x01(\x05\x12\x0e\n\x06target\x18\x04 \x01(\x05\"N\n\x15\x43puhpEnterFtraceEvent\x12\x0b\n\x03\x63pu\x18\x01 \x01(\r\x12\x0b\n\x03\x66un\x18\x02 \x01(\x04\x12\x0b\n\x03idx\x18\x03 \x01(\x05\x12\x0e\n\x06target\x18\x04 \x01(\x05\"P\n\x17\x43puhpLatencyFtraceEvent\x12\x0b\n\x03\x63pu\x18\x01 \x01(\r\x12\x0b\n\x03ret\x18\x02 \x01(\x05\x12\r\n\x05state\x18\x03 \x01(\r\x12\x0c\n\x04time\x18\x04 \x01(\x04\"W\n\x15\x43puhpPauseFtraceEvent\x12\x13\n\x0b\x61\x63tive_cpus\x18\x01 \x01(\r\x12\x0c\n\x04\x63pus\x18\x02 \x01(\r\x12\r\n\x05pause\x18\x03 \x01(\r\x12\x0c\n\x04time\x18\x04 \x01(\r')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.cpuhp_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CPUHPEXITFTRACEEVENT']._serialized_start=61
  _globals['_CPUHPEXITFTRACEEVENT']._serialized_end=137
  _globals['_CPUHPMULTIENTERFTRACEEVENT']._serialized_start=139
  _globals['_CPUHPMULTIENTERFTRACEEVENT']._serialized_end=222
  _globals['_CPUHPENTERFTRACEEVENT']._serialized_start=224
  _globals['_CPUHPENTERFTRACEEVENT']._serialized_end=302
  _globals['_CPUHPLATENCYFTRACEEVENT']._serialized_start=304
  _globals['_CPUHPLATENCYFTRACEEVENT']._serialized_end=384
  _globals['_CPUHPPAUSEFTRACEEVENT']._serialized_start=386
  _globals['_CPUHPPAUSEFTRACEEVENT']._serialized_end=473
# @@protoc_insertion_point(module_scope)
