# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/remote_animation_target.proto
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
    'protos/perfetto/trace/android/view/remote_animation_target.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.app import window_configuration_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_app_dot_window__configuration__pb2
from protos.perfetto.trace.android.graphics import point_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics_dot_point__pb2
from protos.perfetto.trace.android.graphics import rect_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics_dot_rect__pb2
from protos.perfetto.trace.android.view import surfacecontrol_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_surfacecontrol__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n@protos/perfetto/trace/android/view/remote_animation_target.proto\x12\x0fperfetto.protos\x1a<protos/perfetto/trace/android/app/window_configuration.proto\x1a\x32protos/perfetto/trace/android/graphics/point.proto\x1a\x31protos/perfetto/trace/android/graphics/rect.proto\x1a\x37protos/perfetto/trace/android/view/surfacecontrol.proto\"\x94\x05\n\x1aRemoteAnimationTargetProto\x12\x0f\n\x07task_id\x18\x01 \x01(\x05\x12\x0c\n\x04mode\x18\x02 \x01(\x05\x12\x33\n\x05leash\x18\x03 \x01(\x0b\x32$.perfetto.protos.SurfaceControlProto\x12\x16\n\x0eis_translucent\x18\x04 \x01(\x08\x12-\n\tclip_rect\x18\x05 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x32\n\x0e\x63ontent_insets\x18\x06 \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x1a\n\x12prefix_order_index\x18\x07 \x01(\x05\x12-\n\x08position\x18\x08 \x01(\x0b\x32\x1b.perfetto.protos.PointProto\x12;\n\x17source_container_bounds\x18\t \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12G\n\x14window_configuration\x18\n \x01(\x0b\x32).perfetto.protos.WindowConfigurationProto\x12\x39\n\x0bstart_leash\x18\x0b \x01(\x0b\x32$.perfetto.protos.SurfaceControlProto\x12\x30\n\x0cstart_bounds\x18\x0c \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x30\n\x0clocal_bounds\x18\r \x01(\x0b\x32\x1a.perfetto.protos.RectProto\x12\x37\n\x13screen_space_bounds\x18\x0e \x01(\x0b\x32\x1a.perfetto.protos.RectProto')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.remote_animation_target_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_REMOTEANIMATIONTARGETPROTO']._serialized_start=308
  _globals['_REMOTEANIMATIONTARGETPROTO']._serialized_end=968
# @@protoc_insertion_point(module_scope)
