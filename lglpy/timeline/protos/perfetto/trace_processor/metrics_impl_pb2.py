# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace_processor/metrics_impl.proto
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
    'protos/perfetto/trace_processor/metrics_impl.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n2protos/perfetto/trace_processor/metrics_impl.proto\x12\x0fperfetto.protos\"\xa7\x01\n\x12ProtoBuilderResult\x12\x13\n\x0bis_repeated\x18\x01 \x01(\x08\x12\x36\n\x06single\x18\x02 \x01(\x0b\x32$.perfetto.protos.SingleBuilderResultH\x00\x12:\n\x08repeated\x18\x03 \x01(\x0b\x32&.perfetto.protos.RepeatedBuilderResultH\x00\x42\x08\n\x06result\"v\n\x15RepeatedBuilderResult\x12\x16\n\nint_values\x18\x01 \x03(\x10\x42\x02\x10\x01\x12\x19\n\rdouble_values\x18\x02 \x03(\x01\x42\x02\x10\x01\x12\x15\n\rstring_values\x18\x03 \x03(\t\x12\x13\n\x0b\x62yte_values\x18\x04 \x03(\x0c\"H\n\x13SingleBuilderResult\x12\x0c\n\x04type\x18\x01 \x01(\r\x12\x11\n\ttype_name\x18\x02 \x01(\t\x12\x10\n\x08protobuf\x18\x03 \x01(\x0c')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace_processor.metrics_impl_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_REPEATEDBUILDERRESULT'].fields_by_name['int_values']._loaded_options = None
  _globals['_REPEATEDBUILDERRESULT'].fields_by_name['int_values']._serialized_options = b'\020\001'
  _globals['_REPEATEDBUILDERRESULT'].fields_by_name['double_values']._loaded_options = None
  _globals['_REPEATEDBUILDERRESULT'].fields_by_name['double_values']._serialized_options = b'\020\001'
  _globals['_PROTOBUILDERRESULT']._serialized_start=72
  _globals['_PROTOBUILDERRESULT']._serialized_end=239
  _globals['_REPEATEDBUILDERRESULT']._serialized_start=241
  _globals['_REPEATEDBUILDERRESULT']._serialized_end=359
  _globals['_SINGLEBUILDERRESULT']._serialized_start=361
  _globals['_SINGLEBUILDERRESULT']._serialized_end=433
# @@protoc_insertion_point(module_scope)
