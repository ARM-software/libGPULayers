# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/inputmethodservice/inputmethodservice.proto
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
    'protos/perfetto/trace/android/inputmethodservice/inputmethodservice.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.android.inputmethodservice import softinputwindow_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_inputmethodservice_dot_softinputwindow__pb2
from protos.perfetto.trace.android.view.inputmethod import editorinfo_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_inputmethod_dot_editorinfo__pb2
from protos.perfetto.trace.android.view.inputmethod import inputconnection_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_view_dot_inputmethod_dot_inputconnection__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nIprotos/perfetto/trace/android/inputmethodservice/inputmethodservice.proto\x12\x0fperfetto.protos\x1a\x46protos/perfetto/trace/android/inputmethodservice/softinputwindow.proto\x1a?protos/perfetto/trace/android/view/inputmethod/editorinfo.proto\x1a\x44protos/perfetto/trace/android/view/inputmethod/inputconnection.proto\"\x81\x08\n\x17InputMethodServiceProto\x12@\n\x11soft_input_window\x18\x01 \x01(\x0b\x32%.perfetto.protos.SoftInputWindowProto\x12\x15\n\rviews_created\x18\x02 \x01(\x08\x12\x1a\n\x12\x64\x65\x63or_view_visible\x18\x03 \x01(\x08\x12\x1e\n\x16\x64\x65\x63or_view_was_visible\x18\x04 \x01(\x08\x12\x16\n\x0ewindow_visible\x18\x05 \x01(\x08\x12\x16\n\x0ein_show_window\x18\x06 \x01(\x08\x12\x15\n\rconfiguration\x18\x07 \x01(\t\x12\r\n\x05token\x18\x08 \x01(\t\x12\x15\n\rinput_binding\x18\t \x01(\t\x12\x15\n\rinput_started\x18\n \x01(\x08\x12\x1a\n\x12input_view_started\x18\x0b \x01(\x08\x12\x1f\n\x17\x63\x61ndidates_view_started\x18\x0c \x01(\x08\x12;\n\x11input_editor_info\x18\r \x01(\x0b\x32 .perfetto.protos.EditorInfoProto\x12\x1c\n\x14show_input_requested\x18\x0e \x01(\x08\x12!\n\x19last_show_input_requested\x18\x0f \x01(\x08\x12\x18\n\x10show_input_flags\x18\x12 \x01(\x05\x12\x1d\n\x15\x63\x61ndidates_visibility\x18\x13 \x01(\x05\x12\x1a\n\x12\x66ullscreen_applied\x18\x14 \x01(\x08\x12\x15\n\ris_fullscreen\x18\x15 \x01(\x08\x12\x1b\n\x13\x65xtract_view_hidden\x18\x16 \x01(\x08\x12\x17\n\x0f\x65xtracted_token\x18\x17 \x01(\x05\x12\x1b\n\x13is_input_view_shown\x18\x18 \x01(\x08\x12\x13\n\x0bstatus_icon\x18\x19 \x01(\x05\x12R\n\x14last_computed_insets\x18\x1a \x01(\x0b\x32\x34.perfetto.protos.InputMethodServiceProto.InsetsProto\x12\x19\n\x11settings_observer\x18\x1b \x01(\t\x12H\n\x15input_connection_call\x18\x1c \x01(\x0b\x32).perfetto.protos.InputConnectionCallProto\x1ay\n\x0bInsetsProto\x12\x1a\n\x12\x63ontent_top_insets\x18\x01 \x01(\x05\x12\x1a\n\x12visible_top_insets\x18\x02 \x01(\x05\x12\x18\n\x10touchable_insets\x18\x03 \x01(\x05\x12\x18\n\x10touchable_region\x18\x04 \x01(\tJ\x04\x08\x10\x10\x11J\x04\x08\x11\x10\x12')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.inputmethodservice.inputmethodservice_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_INPUTMETHODSERVICEPROTO']._serialized_start=302
  _globals['_INPUTMETHODSERVICEPROTO']._serialized_end=1327
  _globals['_INPUTMETHODSERVICEPROTO_INSETSPROTO']._serialized_start=1194
  _globals['_INPUTMETHODSERVICEPROTO_INSETSPROTO']._serialized_end=1315
# @@protoc_insertion_point(module_scope)
