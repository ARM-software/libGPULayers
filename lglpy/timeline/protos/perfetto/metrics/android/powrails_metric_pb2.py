# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/powrails_metric.proto
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
    'protos/perfetto/metrics/android/powrails_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n5protos/perfetto/metrics/android/powrails_metric.proto\x12\x0fperfetto.protos\"\xab\x02\n\x11\x41ndroidPowerRails\x12\x42\n\x0bpower_rails\x18\x01 \x03(\x0b\x32-.perfetto.protos.AndroidPowerRails.PowerRails\x12\x1f\n\x17\x61vg_total_used_power_mw\x18\x02 \x01(\x01\x1a\x36\n\nEnergyData\x12\x14\n\x0ctimestamp_ms\x18\x01 \x01(\x03\x12\x12\n\nenergy_uws\x18\x02 \x01(\x01\x1ay\n\nPowerRails\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x42\n\x0b\x65nergy_data\x18\x02 \x03(\x0b\x32-.perfetto.protos.AndroidPowerRails.EnergyData\x12\x19\n\x11\x61vg_used_power_mw\x18\x03 \x01(\x01')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.powrails_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDPOWERRAILS']._serialized_start=75
  _globals['_ANDROIDPOWERRAILS']._serialized_end=374
  _globals['_ANDROIDPOWERRAILS_ENERGYDATA']._serialized_start=197
  _globals['_ANDROIDPOWERRAILS_ENERGYDATA']._serialized_end=251
  _globals['_ANDROIDPOWERRAILS_POWERRAILS']._serialized_start=253
  _globals['_ANDROIDPOWERRAILS_POWERRAILS']._serialized_end=374
# @@protoc_insertion_point(module_scope)
