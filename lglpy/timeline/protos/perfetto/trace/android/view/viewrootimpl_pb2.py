# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/viewrootimpl.proto
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
    'protos/perfetto/trace/android/view/viewrootimpl.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.graphics import rect_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics_dot_rect__pb2
from protos.perfetto.trace.android.view import displaycutout_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_displaycutout__pb2
from protos.perfetto.trace.android.view import windowlayoutparams_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_windowlayoutparams__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5protos/perfetto/trace/android/view/viewrootimpl.proto\x12\x0fperfetto.protos\x1a\x31protos/perfetto/trace/android/graphics/rect.proto\x1a\x36protos/perfetto/trace/android/view/displaycutout.proto\x1a;protos/perfetto/trace/android/view/windowlayoutparams.proto\"\xff\x03\n\x11ViewRootImplProto\x12\x0c\n\x04view\x18\x01 \x01(\t\x12\x12\n\ndisplay_id\x18\x02 \x01(\x05\x12\x13\n\x0b\x61pp_visible\x18\x03 \x01(\x08\x12\r\n\x05width\x18\x04 \x01(\x05\x12\x0e\n\x06height\x18\x05 \x01(\x05\x12\x14\n\x0cis_animating\x18\x06 \x01(\x08\x12\x30\n\x0cvisible_rect\x18\x07 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x12\n\nis_drawing\x18\x08 \x01(\x08\x12\r\n\x05\x61\x64\x64\x65\x64\x18\t \x01(\x08\x12-\n\twin_frame\x18\n \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12G\n\x16pending_display_cutout\x18\x0b \x01(\x0b\x32#.perfetto.protos.DisplayCutoutProtoB\x02\x18\x01\x12\x1a\n\x12last_window_insets\x18\x0c \x01(\t\x12\x17\n\x0fsoft_input_mode\x18\r \x01(\t\x12\x10\n\x08scroll_y\x18\x0e \x01(\x05\x12\x14\n\x0c\x63ur_scroll_y\x18\x0f \x01(\x05\x12\x0f\n\x07removed\x18\x10 \x01(\x08\x12\x43\n\x11window_attributes\x18\x11 \x01(\x0b\x32(.perfetto.protos.WindowLayoutParamsProto')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.viewrootimpl_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_VIEWROOTIMPLPROTO'].fields_by_name['pending_display_cutout']._loaded_options = None
  _globals['_VIEWROOTIMPLPROTO'].fields_by_name['pending_display_cutout']._serialized_options = b'\030\001'
  _globals['_VIEWROOTIMPLPROTO']._serialized_start=243
  _globals['_VIEWROOTIMPLPROTO']._serialized_end=754
# @@protoc_insertion_point(module_scope)
