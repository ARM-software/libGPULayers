# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/track_event/chrome_frame_reporter.proto
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
    'protos/perfetto/trace/track_event/chrome_frame_reporter.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n=protos/perfetto/trace/track_event/chrome_frame_reporter.proto\x12\x0fperfetto.protos\"\x8f\x08\n\x13\x43hromeFrameReporter\x12\x39\n\x05state\x18\x01 \x01(\x0e\x32*.perfetto.protos.ChromeFrameReporter.State\x12\x44\n\x06reason\x18\x02 \x01(\x0e\x32\x34.perfetto.protos.ChromeFrameReporter.FrameDropReason\x12\x14\n\x0c\x66rame_source\x18\x03 \x01(\x04\x12\x16\n\x0e\x66rame_sequence\x18\x04 \x01(\x04\x12\x1a\n\x12\x61\x66\x66\x65\x63ts_smoothness\x18\x05 \x01(\x08\x12\x46\n\x0cscroll_state\x18\x06 \x01(\x0e\x32\x30.perfetto.protos.ChromeFrameReporter.ScrollState\x12\x1a\n\x12has_main_animation\x18\x07 \x01(\x08\x12 \n\x18has_compositor_animation\x18\x08 \x01(\x08\x12\x1d\n\x15has_smooth_input_main\x18\t \x01(\x08\x12\x1b\n\x13has_missing_content\x18\n \x01(\x08\x12\x1a\n\x12layer_tree_host_id\x18\x0b \x01(\x04\x12\x18\n\x10has_high_latency\x18\x0c \x01(\x08\x12\x42\n\nframe_type\x18\r \x01(\x0e\x32..perfetto.protos.ChromeFrameReporter.FrameType\x12\'\n\x1fhigh_latency_contribution_stage\x18\x0e \x03(\t\x12#\n\x1b\x63heckerboarded_needs_raster\x18\x0f \x01(\x08\x12#\n\x1b\x63heckerboarded_needs_record\x18\x10 \x01(\x08\"m\n\x05State\x12\x1b\n\x17STATE_NO_UPDATE_DESIRED\x10\x00\x12\x17\n\x13STATE_PRESENTED_ALL\x10\x01\x12\x1b\n\x17STATE_PRESENTED_PARTIAL\x10\x02\x12\x11\n\rSTATE_DROPPED\x10\x03\"~\n\x0f\x46rameDropReason\x12\x16\n\x12REASON_UNSPECIFIED\x10\x00\x12\x1d\n\x19REASON_DISPLAY_COMPOSITOR\x10\x01\x12\x16\n\x12REASON_MAIN_THREAD\x10\x02\x12\x1c\n\x18REASON_CLIENT_COMPOSITOR\x10\x03\"h\n\x0bScrollState\x12\x0f\n\x0bSCROLL_NONE\x10\x00\x12\x16\n\x12SCROLL_MAIN_THREAD\x10\x01\x12\x1c\n\x18SCROLL_COMPOSITOR_THREAD\x10\x02\x12\x12\n\x0eSCROLL_UNKNOWN\x10\x03\"%\n\tFrameType\x12\n\n\x06\x46ORKED\x10\x00\x12\x0c\n\x08\x42\x41\x43KFILL\x10\x01')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.track_event.chrome_frame_reporter_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CHROMEFRAMEREPORTER']._serialized_start=83
  _globals['_CHROMEFRAMEREPORTER']._serialized_end=1122
  _globals['_CHROMEFRAMEREPORTER_STATE']._serialized_start=740
  _globals['_CHROMEFRAMEREPORTER_STATE']._serialized_end=849
  _globals['_CHROMEFRAMEREPORTER_FRAMEDROPREASON']._serialized_start=851
  _globals['_CHROMEFRAMEREPORTER_FRAMEDROPREASON']._serialized_end=977
  _globals['_CHROMEFRAMEREPORTER_SCROLLSTATE']._serialized_start=979
  _globals['_CHROMEFRAMEREPORTER_SCROLLSTATE']._serialized_end=1083
  _globals['_CHROMEFRAMEREPORTER_FRAMETYPE']._serialized_start=1085
  _globals['_CHROMEFRAMEREPORTER_FRAMETYPE']._serialized_end=1122
# @@protoc_insertion_point(module_scope)