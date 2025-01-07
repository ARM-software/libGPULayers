# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/ipc/consumer_port.proto
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
    'protos/perfetto/ipc/consumer_port.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.common import observable_events_pb2 as protos_dot_perfetto_dot_common_dot_observable__events__pb2
from protos.perfetto.common import tracing_service_state_pb2 as protos_dot_perfetto_dot_common_dot_tracing__service__state__pb2
from protos.perfetto.common import tracing_service_capabilities_pb2 as protos_dot_perfetto_dot_common_dot_tracing__service__capabilities__pb2
from protos.perfetto.common import trace_stats_pb2 as protos_dot_perfetto_dot_common_dot_trace__stats__pb2
from protos.perfetto.config import trace_config_pb2 as protos_dot_perfetto_dot_config_dot_trace__config__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\'protos/perfetto/ipc/consumer_port.proto\x12\x0fperfetto.protos\x1a.protos/perfetto/common/observable_events.proto\x1a\x32protos/perfetto/common/tracing_service_state.proto\x1a\x39protos/perfetto/common/tracing_service_capabilities.proto\x1a(protos/perfetto/common/trace_stats.proto\x1a)protos/perfetto/config/trace_config.proto\"l\n\x14\x45nableTracingRequest\x12\x32\n\x0ctrace_config\x18\x01 \x01(\x0b\x32\x1c.perfetto.protos.TraceConfig\x12 \n\x18\x61ttach_notification_only\x18\x02 \x01(\x08\"C\n\x15\x45nableTracingResponse\x12\x12\n\x08\x64isabled\x18\x01 \x01(\x08H\x00\x12\r\n\x05\x65rror\x18\x03 \x01(\tB\x07\n\x05state\"\x15\n\x13StartTracingRequest\"\x16\n\x14StartTracingResponse\"N\n\x18\x43hangeTraceConfigRequest\x12\x32\n\x0ctrace_config\x18\x01 \x01(\x0b\x32\x1c.perfetto.protos.TraceConfig\"\x1b\n\x19\x43hangeTraceConfigResponse\"\x17\n\x15\x44isableTracingRequest\"\x18\n\x16\x44isableTracingResponse\"\x14\n\x12ReadBuffersRequest\"\x87\x01\n\x13ReadBuffersResponse\x12:\n\x06slices\x18\x02 \x03(\x0b\x32*.perfetto.protos.ReadBuffersResponse.Slice\x1a\x34\n\x05Slice\x12\x0c\n\x04\x64\x61ta\x18\x01 \x01(\x0c\x12\x1d\n\x15last_slice_for_packet\x18\x02 \x01(\x08\"(\n\x12\x46reeBuffersRequest\x12\x12\n\nbuffer_ids\x18\x01 \x03(\r\"\x15\n\x13\x46reeBuffersResponse\"1\n\x0c\x46lushRequest\x12\x12\n\ntimeout_ms\x18\x01 \x01(\r\x12\r\n\x05\x66lags\x18\x02 \x01(\x04\"\x0f\n\rFlushResponse\"\x1c\n\rDetachRequest\x12\x0b\n\x03key\x18\x01 \x01(\t\"\x10\n\x0e\x44\x65tachResponse\"\x1c\n\rAttachRequest\x12\x0b\n\x03key\x18\x01 \x01(\t\"D\n\x0e\x41ttachResponse\x12\x32\n\x0ctrace_config\x18\x01 \x01(\x0b\x32\x1c.perfetto.protos.TraceConfig\"\x16\n\x14GetTraceStatsRequest\"I\n\x15GetTraceStatsResponse\x12\x30\n\x0btrace_stats\x18\x01 \x01(\x0b\x32\x1b.perfetto.protos.TraceStats\"Y\n\x14ObserveEventsRequest\x12\x41\n\x11\x65vents_to_observe\x18\x01 \x03(\x0e\x32&.perfetto.protos.ObservableEvents.Type\"J\n\x15ObserveEventsResponse\x12\x31\n\x06\x65vents\x18\x01 \x01(\x0b\x32!.perfetto.protos.ObservableEvents\"1\n\x18QueryServiceStateRequest\x12\x15\n\rsessions_only\x18\x01 \x01(\x08\"X\n\x19QueryServiceStateResponse\x12;\n\rservice_state\x18\x01 \x01(\x0b\x32$.perfetto.protos.TracingServiceState\"\x1a\n\x18QueryCapabilitiesRequest\"^\n\x19QueryCapabilitiesResponse\x12\x41\n\x0c\x63\x61pabilities\x18\x01 \x01(\x0b\x32+.perfetto.protos.TracingServiceCapabilities\"\x1e\n\x1cSaveTraceForBugreportRequest\"=\n\x1dSaveTraceForBugreportResponse\x12\x0f\n\x07success\x18\x01 \x01(\x08\x12\x0b\n\x03msg\x18\x02 \x01(\t\"[\n\x13\x43loneSessionRequest\x12\x12\n\nsession_id\x18\x01 \x01(\x04\x12\x19\n\x11skip_trace_filter\x18\x02 \x01(\x08\x12\x15\n\rfor_bugreport\x18\x03 \x01(\x08\"Z\n\x14\x43loneSessionResponse\x12\x0f\n\x07success\x18\x01 \x01(\x08\x12\r\n\x05\x65rror\x18\x02 \x01(\t\x12\x10\n\x08uuid_msb\x18\x03 \x01(\x03\x12\x10\n\x08uuid_lsb\x18\x04 \x01(\x03\x32\xbd\x0b\n\x0c\x43onsumerPort\x12`\n\rEnableTracing\x12%.perfetto.protos.EnableTracingRequest\x1a&.perfetto.protos.EnableTracingResponse\"\x00\x12\x63\n\x0e\x44isableTracing\x12&.perfetto.protos.DisableTracingRequest\x1a\'.perfetto.protos.DisableTracingResponse\"\x00\x12\\\n\x0bReadBuffers\x12#.perfetto.protos.ReadBuffersRequest\x1a$.perfetto.protos.ReadBuffersResponse\"\x00\x30\x01\x12Z\n\x0b\x46reeBuffers\x12#.perfetto.protos.FreeBuffersRequest\x1a$.perfetto.protos.FreeBuffersResponse\"\x00\x12H\n\x05\x46lush\x12\x1d.perfetto.protos.FlushRequest\x1a\x1e.perfetto.protos.FlushResponse\"\x00\x12]\n\x0cStartTracing\x12$.perfetto.protos.StartTracingRequest\x1a%.perfetto.protos.StartTracingResponse\"\x00\x12l\n\x11\x43hangeTraceConfig\x12).perfetto.protos.ChangeTraceConfigRequest\x1a*.perfetto.protos.ChangeTraceConfigResponse\"\x00\x12K\n\x06\x44\x65tach\x12\x1e.perfetto.protos.DetachRequest\x1a\x1f.perfetto.protos.DetachResponse\"\x00\x12K\n\x06\x41ttach\x12\x1e.perfetto.protos.AttachRequest\x1a\x1f.perfetto.protos.AttachResponse\"\x00\x12`\n\rGetTraceStats\x12%.perfetto.protos.GetTraceStatsRequest\x1a&.perfetto.protos.GetTraceStatsResponse\"\x00\x12\x62\n\rObserveEvents\x12%.perfetto.protos.ObserveEventsRequest\x1a&.perfetto.protos.ObserveEventsResponse\"\x00\x30\x01\x12n\n\x11QueryServiceState\x12).perfetto.protos.QueryServiceStateRequest\x1a*.perfetto.protos.QueryServiceStateResponse\"\x00\x30\x01\x12l\n\x11QueryCapabilities\x12).perfetto.protos.QueryCapabilitiesRequest\x1a*.perfetto.protos.QueryCapabilitiesResponse\"\x00\x12x\n\x15SaveTraceForBugreport\x12-.perfetto.protos.SaveTraceForBugreportRequest\x1a..perfetto.protos.SaveTraceForBugreportResponse\"\x00\x12]\n\x0c\x43loneSession\x12$.perfetto.protos.CloneSessionRequest\x1a%.perfetto.protos.CloneSessionResponse\"\x00')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.ipc.consumer_port_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ENABLETRACINGREQUEST']._serialized_start=304
  _globals['_ENABLETRACINGREQUEST']._serialized_end=412
  _globals['_ENABLETRACINGRESPONSE']._serialized_start=414
  _globals['_ENABLETRACINGRESPONSE']._serialized_end=481
  _globals['_STARTTRACINGREQUEST']._serialized_start=483
  _globals['_STARTTRACINGREQUEST']._serialized_end=504
  _globals['_STARTTRACINGRESPONSE']._serialized_start=506
  _globals['_STARTTRACINGRESPONSE']._serialized_end=528
  _globals['_CHANGETRACECONFIGREQUEST']._serialized_start=530
  _globals['_CHANGETRACECONFIGREQUEST']._serialized_end=608
  _globals['_CHANGETRACECONFIGRESPONSE']._serialized_start=610
  _globals['_CHANGETRACECONFIGRESPONSE']._serialized_end=637
  _globals['_DISABLETRACINGREQUEST']._serialized_start=639
  _globals['_DISABLETRACINGREQUEST']._serialized_end=662
  _globals['_DISABLETRACINGRESPONSE']._serialized_start=664
  _globals['_DISABLETRACINGRESPONSE']._serialized_end=688
  _globals['_READBUFFERSREQUEST']._serialized_start=690
  _globals['_READBUFFERSREQUEST']._serialized_end=710
  _globals['_READBUFFERSRESPONSE']._serialized_start=713
  _globals['_READBUFFERSRESPONSE']._serialized_end=848
  _globals['_READBUFFERSRESPONSE_SLICE']._serialized_start=796
  _globals['_READBUFFERSRESPONSE_SLICE']._serialized_end=848
  _globals['_FREEBUFFERSREQUEST']._serialized_start=850
  _globals['_FREEBUFFERSREQUEST']._serialized_end=890
  _globals['_FREEBUFFERSRESPONSE']._serialized_start=892
  _globals['_FREEBUFFERSRESPONSE']._serialized_end=913
  _globals['_FLUSHREQUEST']._serialized_start=915
  _globals['_FLUSHREQUEST']._serialized_end=964
  _globals['_FLUSHRESPONSE']._serialized_start=966
  _globals['_FLUSHRESPONSE']._serialized_end=981
  _globals['_DETACHREQUEST']._serialized_start=983
  _globals['_DETACHREQUEST']._serialized_end=1011
  _globals['_DETACHRESPONSE']._serialized_start=1013
  _globals['_DETACHRESPONSE']._serialized_end=1029
  _globals['_ATTACHREQUEST']._serialized_start=1031
  _globals['_ATTACHREQUEST']._serialized_end=1059
  _globals['_ATTACHRESPONSE']._serialized_start=1061
  _globals['_ATTACHRESPONSE']._serialized_end=1129
  _globals['_GETTRACESTATSREQUEST']._serialized_start=1131
  _globals['_GETTRACESTATSREQUEST']._serialized_end=1153
  _globals['_GETTRACESTATSRESPONSE']._serialized_start=1155
  _globals['_GETTRACESTATSRESPONSE']._serialized_end=1228
  _globals['_OBSERVEEVENTSREQUEST']._serialized_start=1230
  _globals['_OBSERVEEVENTSREQUEST']._serialized_end=1319
  _globals['_OBSERVEEVENTSRESPONSE']._serialized_start=1321
  _globals['_OBSERVEEVENTSRESPONSE']._serialized_end=1395
  _globals['_QUERYSERVICESTATEREQUEST']._serialized_start=1397
  _globals['_QUERYSERVICESTATEREQUEST']._serialized_end=1446
  _globals['_QUERYSERVICESTATERESPONSE']._serialized_start=1448
  _globals['_QUERYSERVICESTATERESPONSE']._serialized_end=1536
  _globals['_QUERYCAPABILITIESREQUEST']._serialized_start=1538
  _globals['_QUERYCAPABILITIESREQUEST']._serialized_end=1564
  _globals['_QUERYCAPABILITIESRESPONSE']._serialized_start=1566
  _globals['_QUERYCAPABILITIESRESPONSE']._serialized_end=1660
  _globals['_SAVETRACEFORBUGREPORTREQUEST']._serialized_start=1662
  _globals['_SAVETRACEFORBUGREPORTREQUEST']._serialized_end=1692
  _globals['_SAVETRACEFORBUGREPORTRESPONSE']._serialized_start=1694
  _globals['_SAVETRACEFORBUGREPORTRESPONSE']._serialized_end=1755
  _globals['_CLONESESSIONREQUEST']._serialized_start=1757
  _globals['_CLONESESSIONREQUEST']._serialized_end=1848
  _globals['_CLONESESSIONRESPONSE']._serialized_start=1850
  _globals['_CLONESESSIONRESPONSE']._serialized_end=1940
  _globals['_CONSUMERPORT']._serialized_start=1943
  _globals['_CONSUMERPORT']._serialized_end=3412
# @@protoc_insertion_point(module_scope)
