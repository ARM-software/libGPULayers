# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/power/android_power_config.proto
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
    'protos/perfetto/config/power/android_power_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n7protos/perfetto/config/power/android_power_config.proto\x12\x0fperfetto.protos\"\xc0\x03\n\x12\x41ndroidPowerConfig\x12\x17\n\x0f\x62\x61ttery_poll_ms\x18\x01 \x01(\r\x12M\n\x10\x62\x61ttery_counters\x18\x02 \x03(\x0e\x32\x33.perfetto.protos.AndroidPowerConfig.BatteryCounters\x12\x1b\n\x13\x63ollect_power_rails\x18\x03 \x01(\x08\x12+\n#collect_energy_estimation_breakdown\x18\x04 \x01(\x08\x12&\n\x1e\x63ollect_entity_state_residency\x18\x05 \x01(\x08\"\xcf\x01\n\x0f\x42\x61tteryCounters\x12\x1f\n\x1b\x42\x41TTERY_COUNTER_UNSPECIFIED\x10\x00\x12\x1a\n\x16\x42\x41TTERY_COUNTER_CHARGE\x10\x01\x12$\n BATTERY_COUNTER_CAPACITY_PERCENT\x10\x02\x12\x1b\n\x17\x42\x41TTERY_COUNTER_CURRENT\x10\x03\x12\x1f\n\x1b\x42\x41TTERY_COUNTER_CURRENT_AVG\x10\x04\x12\x1b\n\x17\x42\x41TTERY_COUNTER_VOLTAGE\x10\x05')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.power.android_power_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDPOWERCONFIG']._serialized_start=77
  _globals['_ANDROIDPOWERCONFIG']._serialized_end=525
  _globals['_ANDROIDPOWERCONFIG_BATTERYCOUNTERS']._serialized_start=318
  _globals['_ANDROIDPOWERCONFIG_BATTERYCOUNTERS']._serialized_end=525
# @@protoc_insertion_point(module_scope)
