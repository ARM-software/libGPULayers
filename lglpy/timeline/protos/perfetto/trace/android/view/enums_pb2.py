# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/enums.proto
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
    'protos/perfetto/trace/android/view/enums.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n.protos/perfetto/trace/android/view/enums.proto\x12\x0fperfetto.protos*\xc6\x01\n\x10\x44isplayStateEnum\x12\x19\n\x15\x44ISPLAY_STATE_UNKNOWN\x10\x00\x12\x15\n\x11\x44ISPLAY_STATE_OFF\x10\x01\x12\x14\n\x10\x44ISPLAY_STATE_ON\x10\x02\x12\x16\n\x12\x44ISPLAY_STATE_DOZE\x10\x03\x12\x1e\n\x1a\x44ISPLAY_STATE_DOZE_SUSPEND\x10\x04\x12\x14\n\x10\x44ISPLAY_STATE_VR\x10\x05\x12\x1c\n\x18\x44ISPLAY_STATE_ON_SUSPEND\x10\x06*\xb0\x02\n\x12\x44isplayStateReason\x12 \n\x1c\x44ISPLAY_STATE_REASON_UNKNOWN\x10\x00\x12\'\n#DISPLAY_STATE_REASON_DEFAULT_POLICY\x10\x01\x12\'\n#DISPLAY_STATE_REASON_DRAW_WAKE_LOCK\x10\x02\x12 \n\x1c\x44ISPLAY_STATE_REASON_OFFLOAD\x10\x03\x12\x1d\n\x19\x44ISPLAY_STATE_REASON_TILT\x10\x04\x12&\n\"DISPLAY_STATE_REASON_DREAM_MANAGER\x10\x05\x12\x1c\n\x18\x44ISPLAY_STATE_REASON_KEY\x10\x06\x12\x1f\n\x1b\x44ISPLAY_STATE_REASON_MOTION\x10\x07*\xdc\x05\n\x12TransitionTypeEnum\x12\x10\n\x0cTRANSIT_NONE\x10\x00\x12\x1a\n\rTRANSIT_UNSET\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01\x12\x19\n\x15TRANSIT_ACTIVITY_OPEN\x10\x06\x12\x1a\n\x16TRANSIT_ACTIVITY_CLOSE\x10\x07\x12\x15\n\x11TRANSIT_TASK_OPEN\x10\x08\x12\x16\n\x12TRANSIT_TASK_CLOSE\x10\t\x12\x19\n\x15TRANSIT_TASK_TO_FRONT\x10\n\x12\x18\n\x14TRANSIT_TASK_TO_BACK\x10\x0b\x12\x1b\n\x17TRANSIT_WALLPAPER_CLOSE\x10\x0c\x12\x1a\n\x16TRANSIT_WALLPAPER_OPEN\x10\r\x12 \n\x1cTRANSIT_WALLPAPER_INTRA_OPEN\x10\x0e\x12!\n\x1dTRANSIT_WALLPAPER_INTRA_CLOSE\x10\x0f\x12\x1c\n\x18TRANSIT_TASK_OPEN_BEHIND\x10\x10\x12\x19\n\x15TRANSIT_TASK_IN_PLACE\x10\x11\x12\x1d\n\x19TRANSIT_ACTIVITY_RELAUNCH\x10\x12\x12&\n\x1eTRANSIT_DOCK_TASK_FROM_RECENTS\x10\x13\x1a\x02\x08\x01\x12\x1f\n\x1bTRANSIT_KEYGUARD_GOING_AWAY\x10\x14\x12,\n(TRANSIT_KEYGUARD_GOING_AWAY_ON_WALLPAPER\x10\x15\x12\x1c\n\x18TRANSIT_KEYGUARD_OCCLUDE\x10\x16\x12\x1e\n\x1aTRANSIT_KEYGUARD_UNOCCLUDE\x10\x17\x12%\n!TRANSIT_TRANSLUCENT_ACTIVITY_OPEN\x10\x18\x12&\n\"TRANSIT_TRANSLUCENT_ACTIVITY_CLOSE\x10\x19\x12#\n\x1fTRANSIT_CRASHING_ACTIVITY_CLOSE\x10\x1a')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.enums_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TRANSITIONTYPEENUM'].values_by_name["TRANSIT_DOCK_TASK_FROM_RECENTS"]._loaded_options = None
  _globals['_TRANSITIONTYPEENUM'].values_by_name["TRANSIT_DOCK_TASK_FROM_RECENTS"]._serialized_options = b'\010\001'
  _globals['_DISPLAYSTATEENUM']._serialized_start=68
  _globals['_DISPLAYSTATEENUM']._serialized_end=266
  _globals['_DISPLAYSTATEREASON']._serialized_start=269
  _globals['_DISPLAYSTATEREASON']._serialized_end=573
  _globals['_TRANSITIONTYPEENUM']._serialized_start=576
  _globals['_TRANSITIONTYPEENUM']._serialized_end=1308
# @@protoc_insertion_point(module_scope)