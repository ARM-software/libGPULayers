# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/chrome/chrome_trace_event.proto
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
    'protos/perfetto/trace/chrome/chrome_trace_event.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5protos/perfetto/trace/chrome/chrome_trace_event.proto\x12\x0fperfetto.protos\"\xd3\x02\n\x11\x43hromeTracedValue\x12\x42\n\x0bnested_type\x18\x01 \x01(\x0e\x32-.perfetto.protos.ChromeTracedValue.NestedType\x12\x11\n\tdict_keys\x18\x02 \x03(\t\x12\x37\n\x0b\x64ict_values\x18\x03 \x03(\x0b\x32\".perfetto.protos.ChromeTracedValue\x12\x38\n\x0c\x61rray_values\x18\x04 \x03(\x0b\x32\".perfetto.protos.ChromeTracedValue\x12\x11\n\tint_value\x18\x05 \x01(\x05\x12\x14\n\x0c\x64ouble_value\x18\x06 \x01(\x01\x12\x12\n\nbool_value\x18\x07 \x01(\x08\x12\x14\n\x0cstring_value\x18\x08 \x01(\t\"!\n\nNestedType\x12\x08\n\x04\x44ICT\x10\x00\x12\t\n\x05\x41RRAY\x10\x01\"6\n\x16\x43hromeStringTableEntry\x12\r\n\x05value\x18\x01 \x01(\t\x12\r\n\x05index\x18\x02 \x01(\x05\"\x81\x05\n\x10\x43hromeTraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x11\n\ttimestamp\x18\x02 \x01(\x03\x12\r\n\x05phase\x18\x03 \x01(\x05\x12\x11\n\tthread_id\x18\x04 \x01(\x05\x12\x10\n\x08\x64uration\x18\x05 \x01(\x03\x12\x17\n\x0fthread_duration\x18\x06 \x01(\x03\x12\r\n\x05scope\x18\x07 \x01(\t\x12\n\n\x02id\x18\x08 \x01(\x04\x12\r\n\x05\x66lags\x18\t \x01(\r\x12\x1b\n\x13\x63\x61tegory_group_name\x18\n \x01(\t\x12\x12\n\nprocess_id\x18\x0b \x01(\x05\x12\x18\n\x10thread_timestamp\x18\x0c \x01(\x03\x12\x0f\n\x07\x62ind_id\x18\r \x01(\x04\x12\x33\n\x04\x61rgs\x18\x0e \x03(\x0b\x32%.perfetto.protos.ChromeTraceEvent.Arg\x12\x12\n\nname_index\x18\x0f \x01(\r\x12!\n\x19\x63\x61tegory_group_name_index\x18\x10 \x01(\r\x1a\x8c\x02\n\x03\x41rg\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x14\n\nbool_value\x18\x02 \x01(\x08H\x00\x12\x14\n\nuint_value\x18\x03 \x01(\x04H\x00\x12\x13\n\tint_value\x18\x04 \x01(\x03H\x00\x12\x16\n\x0c\x64ouble_value\x18\x05 \x01(\x01H\x00\x12\x16\n\x0cstring_value\x18\x06 \x01(\tH\x00\x12\x17\n\rpointer_value\x18\x07 \x01(\x04H\x00\x12\x14\n\njson_value\x18\x08 \x01(\tH\x00\x12:\n\x0ctraced_value\x18\n \x01(\x0b\x32\".perfetto.protos.ChromeTracedValueH\x00\x12\x12\n\nname_index\x18\t \x01(\rB\x07\n\x05value\"\x80\x01\n\x0e\x43hromeMetadata\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x16\n\x0cstring_value\x18\x02 \x01(\tH\x00\x12\x14\n\nbool_value\x18\x03 \x01(\x08H\x00\x12\x13\n\tint_value\x18\x04 \x01(\x03H\x00\x12\x14\n\njson_value\x18\x05 \x01(\tH\x00\x42\x07\n\x05value\"\x94\x01\n\x15\x43hromeLegacyJsonTrace\x12>\n\x04type\x18\x01 \x01(\x0e\x32\x30.perfetto.protos.ChromeLegacyJsonTrace.TraceType\x12\x0c\n\x04\x64\x61ta\x18\x02 \x01(\t\"-\n\tTraceType\x12\x0e\n\nUSER_TRACE\x10\x00\x12\x10\n\x0cSYSTEM_TRACE\x10\x01\"\xa7\x02\n\x11\x43hromeEventBundle\x12;\n\x0ctrace_events\x18\x01 \x03(\x0b\x32!.perfetto.protos.ChromeTraceEventB\x02\x18\x01\x12\x31\n\x08metadata\x18\x02 \x03(\x0b\x32\x1f.perfetto.protos.ChromeMetadata\x12\x1c\n\x14legacy_ftrace_output\x18\x04 \x03(\t\x12\x41\n\x11legacy_json_trace\x18\x05 \x03(\x0b\x32&.perfetto.protos.ChromeLegacyJsonTrace\x12\x41\n\x0cstring_table\x18\x03 \x03(\x0b\x32\'.perfetto.protos.ChromeStringTableEntryB\x02\x18\x01')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.chrome.chrome_trace_event_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CHROMEEVENTBUNDLE'].fields_by_name['trace_events']._loaded_options = None
  _globals['_CHROMEEVENTBUNDLE'].fields_by_name['trace_events']._serialized_options = b'\030\001'
  _globals['_CHROMEEVENTBUNDLE'].fields_by_name['string_table']._loaded_options = None
  _globals['_CHROMEEVENTBUNDLE'].fields_by_name['string_table']._serialized_options = b'\030\001'
  _globals['_CHROMETRACEDVALUE']._serialized_start=75
  _globals['_CHROMETRACEDVALUE']._serialized_end=414
  _globals['_CHROMETRACEDVALUE_NESTEDTYPE']._serialized_start=381
  _globals['_CHROMETRACEDVALUE_NESTEDTYPE']._serialized_end=414
  _globals['_CHROMESTRINGTABLEENTRY']._serialized_start=416
  _globals['_CHROMESTRINGTABLEENTRY']._serialized_end=470
  _globals['_CHROMETRACEEVENT']._serialized_start=473
  _globals['_CHROMETRACEEVENT']._serialized_end=1114
  _globals['_CHROMETRACEEVENT_ARG']._serialized_start=846
  _globals['_CHROMETRACEEVENT_ARG']._serialized_end=1114
  _globals['_CHROMEMETADATA']._serialized_start=1117
  _globals['_CHROMEMETADATA']._serialized_end=1245
  _globals['_CHROMELEGACYJSONTRACE']._serialized_start=1248
  _globals['_CHROMELEGACYJSONTRACE']._serialized_end=1396
  _globals['_CHROMELEGACYJSONTRACE_TRACETYPE']._serialized_start=1351
  _globals['_CHROMELEGACYJSONTRACE_TRACETYPE']._serialized_end=1396
  _globals['_CHROMEEVENTBUNDLE']._serialized_start=1399
  _globals['_CHROMEEVENTBUNDLE']._serialized_end=1694
# @@protoc_insertion_point(module_scope)