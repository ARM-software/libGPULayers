# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/insetssourceconsumer.proto
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
    'protos/perfetto/trace/android/view/insetssourceconsumer.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.view import insetssourcecontrol_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_insetssourcecontrol__pb2
from protos.perfetto.trace.android.graphics import rect_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics_dot_rect__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n=protos/perfetto/trace/android/view/insetssourceconsumer.proto\x12\x0fperfetto.protos\x1a<protos/perfetto/trace/android/view/insetssourcecontrol.proto\x1a\x31protos/perfetto/trace/android/graphics/rect.proto\"\xd4\x02\n\x19InsetsSourceConsumerProto\x12 \n\x14internal_insets_type\x18\x01 \x01(\tB\x02\x18\x01\x12\x18\n\x10has_window_focus\x18\x02 \x01(\x08\x12\x1c\n\x14is_requested_visible\x18\x03 \x01(\x08\x12\x41\n\x0esource_control\x18\x04 \x01(\x0b\x32).perfetto.protos.InsetsSourceControlProto\x12\x31\n\rpending_frame\x18\x05 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x39\n\x15pending_visible_frame\x18\x06 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x17\n\x0f\x61nimation_state\x18\x07 \x01(\x05\x12\x13\n\x0btype_number\x18\x08 \x01(\x05')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.insetssourceconsumer_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_INSETSSOURCECONSUMERPROTO'].fields_by_name['internal_insets_type']._loaded_options = None
  _globals['_INSETSSOURCECONSUMERPROTO'].fields_by_name['internal_insets_type']._serialized_options = b'\030\001'
  _globals['_INSETSSOURCECONSUMERPROTO']._serialized_start=196
  _globals['_INSETSSOURCECONSUMERPROTO']._serialized_end=536
# @@protoc_insertion_point(module_scope)