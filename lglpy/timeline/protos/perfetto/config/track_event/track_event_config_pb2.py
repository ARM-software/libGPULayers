# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/track_event/track_event_config.proto
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
    'protos/perfetto/config/track_event/track_event_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n;protos/perfetto/config/track_event/track_event_config.proto\x12\x0fperfetto.protos\"\xae\x02\n\x10TrackEventConfig\x12\x1b\n\x13\x64isabled_categories\x18\x01 \x03(\t\x12\x1a\n\x12\x65nabled_categories\x18\x02 \x03(\t\x12\x15\n\rdisabled_tags\x18\x03 \x03(\t\x12\x14\n\x0c\x65nabled_tags\x18\x04 \x03(\t\x12&\n\x1e\x64isable_incremental_timestamps\x18\x05 \x01(\x08\x12!\n\x19timestamp_unit_multiplier\x18\x06 \x01(\x04\x12 \n\x18\x66ilter_debug_annotations\x18\x07 \x01(\x08\x12#\n\x1b\x65nable_thread_time_sampling\x18\x08 \x01(\x08\x12\"\n\x1a\x66ilter_dynamic_event_names\x18\t \x01(\x08')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.track_event.track_event_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TRACKEVENTCONFIG']._serialized_start=81
  _globals['_TRACKEVENTCONFIG']._serialized_end=383
# @@protoc_insertion_point(module_scope)
