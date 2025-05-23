# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/binder_metric.proto
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
    'protos/perfetto/metrics/android/binder_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n3protos/perfetto/metrics/android/binder_metric.proto\x12\x0fperfetto.protos\"\x9e\x0c\n\x13\x41ndroidBinderMetric\x12S\n\x11process_breakdown\x18\x01 \x03(\x0b\x32\x38.perfetto.protos.AndroidBinderMetric.PerProcessBreakdown\x12\x61\n\x1aunaggregated_txn_breakdown\x18\x02 \x03(\x0b\x32=.perfetto.protos.AndroidBinderMetric.UnaggregatedTxnBreakdown\x1a[\n\x13PerProcessBreakdown\x12\x14\n\x0cprocess_name\x18\x01 \x01(\t\x12\x0b\n\x03pid\x18\x02 \x01(\r\x12\x12\n\nslice_name\x18\x03 \x01(\t\x12\r\n\x05\x63ount\x18\x04 \x01(\r\x1a\x89\x07\n\x18UnaggregatedTxnBreakdown\x12\x11\n\taidl_name\x18\x01 \x01(\t\x12\x0f\n\x07\x61idl_ts\x18\x16 \x01(\x03\x12\x10\n\x08\x61idl_dur\x18\x17 \x01(\x03\x12\x0f\n\x07is_sync\x18\x15 \x01(\x08\x12\x16\n\x0e\x63lient_process\x18\x03 \x01(\t\x12\x15\n\rclient_thread\x18\x04 \x01(\t\x12\x16\n\x0eis_main_thread\x18\x05 \x01(\x08\x12\x11\n\tclient_ts\x18\x06 \x01(\x03\x12\x12\n\nclient_dur\x18\x07 \x01(\x03\x12\x1c\n\x14\x63lient_monotonic_dur\x18\x1c \x01(\x03\x12\x18\n\x10\x63lient_oom_score\x18\x13 \x01(\x03\x12#\n\x1b\x63lient_package_version_code\x18\x18 \x01(\x03\x12$\n\x1cis_client_package_debuggable\x18\x19 \x01(\x08\x12\x16\n\x0eserver_process\x18\t \x01(\t\x12\x15\n\rserver_thread\x18\n \x01(\t\x12\x11\n\tserver_ts\x18\x0b \x01(\x03\x12\x12\n\nserver_dur\x18\x0c \x01(\x03\x12\x1c\n\x14server_monotonic_dur\x18\x1d \x01(\x03\x12\x18\n\x10server_oom_score\x18\x14 \x01(\x03\x12#\n\x1bserver_package_version_code\x18\x1a \x01(\x03\x12$\n\x1cis_server_package_debuggable\x18\x1b \x01(\x08\x12P\n\rthread_states\x18\r \x03(\x0b\x32\x39.perfetto.protos.AndroidBinderMetric.ThreadStateBreakdown\x12X\n\x11\x62locked_functions\x18\x0e \x03(\x0b\x32=.perfetto.protos.AndroidBinderMetric.BlockedFunctionBreakdown\x12T\n\x0flogical_reasons\x18\x1f \x03(\x0b\x32;.perfetto.protos.AndroidBinderMetric.LogicalReasonBreakdown\x12\x12\n\nclient_tid\x18\x0f \x01(\r\x12\x12\n\nserver_tid\x18\x10 \x01(\r\x12\x12\n\nclient_pid\x18\x11 \x01(\r\x12\x12\n\nserver_pid\x18\x12 \x01(\rJ\x04\x08\x02\x10\x03J\x04\x08\x08\x10\t\x1a}\n\x14ThreadStateBreakdown\x12\x19\n\x11thread_state_type\x18\x01 \x01(\t\x12\x14\n\x0cthread_state\x18\x02 \x01(\t\x12\x18\n\x10thread_state_dur\x18\x03 \x01(\x03\x12\x1a\n\x12thread_state_count\x18\x04 \x01(\x03\x1a\x8d\x01\n\x18\x42lockedFunctionBreakdown\x12\x19\n\x11thread_state_type\x18\x01 \x01(\t\x12\x18\n\x10\x62locked_function\x18\x02 \x01(\t\x12\x1c\n\x14\x62locked_function_dur\x18\x03 \x01(\x03\x12\x1e\n\x16\x62locked_function_count\x18\x04 \x01(\x03\x1aW\n\x16LogicalReasonBreakdown\x12\x19\n\x11thread_state_type\x18\x01 \x01(\t\x12\x0e\n\x06reason\x18\x02 \x01(\t\x12\x12\n\nreason_dur\x18\x03 \x01(\x03')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.binder_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDBINDERMETRIC']._serialized_start=73
  _globals['_ANDROIDBINDERMETRIC']._serialized_end=1639
  _globals['_ANDROIDBINDERMETRIC_PERPROCESSBREAKDOWN']._serialized_start=280
  _globals['_ANDROIDBINDERMETRIC_PERPROCESSBREAKDOWN']._serialized_end=371
  _globals['_ANDROIDBINDERMETRIC_UNAGGREGATEDTXNBREAKDOWN']._serialized_start=374
  _globals['_ANDROIDBINDERMETRIC_UNAGGREGATEDTXNBREAKDOWN']._serialized_end=1279
  _globals['_ANDROIDBINDERMETRIC_THREADSTATEBREAKDOWN']._serialized_start=1281
  _globals['_ANDROIDBINDERMETRIC_THREADSTATEBREAKDOWN']._serialized_end=1406
  _globals['_ANDROIDBINDERMETRIC_BLOCKEDFUNCTIONBREAKDOWN']._serialized_start=1409
  _globals['_ANDROIDBINDERMETRIC_BLOCKEDFUNCTIONBREAKDOWN']._serialized_end=1550
  _globals['_ANDROIDBINDERMETRIC_LOGICALREASONBREAKDOWN']._serialized_start=1552
  _globals['_ANDROIDBINDERMETRIC_LOGICALREASONBREAKDOWN']._serialized_end=1639
# @@protoc_insertion_point(module_scope)
