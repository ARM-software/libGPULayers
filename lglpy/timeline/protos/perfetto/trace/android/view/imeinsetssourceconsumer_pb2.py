# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/imeinsetssourceconsumer.proto
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
    'protos/perfetto/trace/android/view/imeinsetssourceconsumer.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.view import insetssourceconsumer_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_insetssourceconsumer__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@protos/perfetto/trace/android/view/imeinsetssourceconsumer.proto\x12\x0fperfetto.protos\x1a=protos/perfetto/trace/android/view/insetssourceconsumer.proto\"\x98\x02\n\x1cImeInsetsSourceConsumerProto\x12J\n\x16insets_source_consumer\x18\x01 \x01(\x0b\x32*.perfetto.protos.InsetsSourceConsumerProto\x12-\n%is_requested_visible_awaiting_control\x18\x03 \x01(\x08\x12%\n\x19is_hide_animation_running\x18\x04 \x01(\x08\x42\x02\x18\x01\x12\x33\n\'is_show_requested_during_hide_animation\x18\x05 \x01(\x08\x42\x02\x18\x01\x12\x1b\n\x13has_pending_request\x18\x06 \x01(\x08J\x04\x08\x02\x10\x03')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.imeinsetssourceconsumer_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_IMEINSETSSOURCECONSUMERPROTO'].fields_by_name['is_hide_animation_running']._loaded_options = None
  _globals['_IMEINSETSSOURCECONSUMERPROTO'].fields_by_name['is_hide_animation_running']._serialized_options = b'\030\001'
  _globals['_IMEINSETSSOURCECONSUMERPROTO'].fields_by_name['is_show_requested_during_hide_animation']._loaded_options = None
  _globals['_IMEINSETSSOURCECONSUMERPROTO'].fields_by_name['is_show_requested_during_hide_animation']._serialized_options = b'\030\001'
  _globals['_IMEINSETSSOURCECONSUMERPROTO']._serialized_start=149
  _globals['_IMEINSETSSOURCECONSUMERPROTO']._serialized_end=429
# @@protoc_insertion_point(module_scope)
