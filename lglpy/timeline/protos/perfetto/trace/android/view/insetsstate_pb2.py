# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/insetsstate.proto
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
    'protos/perfetto/trace/android/view/insetsstate.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.graphics import rect_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics_dot_rect__pb2
from protos.perfetto.trace.android.view import displaycutout_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_displaycutout__pb2
from protos.perfetto.trace.android.view import insetssource_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_insetssource__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n4protos/perfetto/trace/android/view/insetsstate.proto\x12\x0fperfetto.protos\x1a\x31protos/perfetto/trace/android/graphics/rect.proto\x1a\x36protos/perfetto/trace/android/view/displaycutout.proto\x1a\x35protos/perfetto/trace/android/view/insetssource.proto\"\xb7\x01\n\x10InsetsStateProto\x12\x33\n\x07sources\x18\x01 \x03(\x0b\x32\".perfetto.protos.InsetsSourceProto\x12\x31\n\rdisplay_frame\x18\x02 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12;\n\x0e\x64isplay_cutout\x18\x03 \x01(\x0b\x32#.perfetto.protos.DisplayCutoutProto')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.insetsstate_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_INSETSSTATEPROTO']._serialized_start=236
  _globals['_INSETSSTATEPROTO']._serialized_end=419
# @@protoc_insertion_point(module_scope)
