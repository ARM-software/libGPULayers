# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/metrics/android/network_metric.proto
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
    'protos/perfetto/metrics/android/network_metric.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n4protos/perfetto/metrics/android/network_metric.proto\x12\x0fperfetto.protos\"\xf3\x10\n\x14\x41ndroidNetworkMetric\x12\x44\n\x0bnet_devices\x18\x01 \x03(\x0b\x32/.perfetto.protos.AndroidNetworkMetric.NetDevice\x12H\n\rnet_rx_action\x18\x02 \x01(\x0b\x32\x31.perfetto.protos.AndroidNetworkMetric.NetRxAction\x12\x1b\n\x13retransmission_rate\x18\x03 \x01(\x01\x12\x16\n\x0ekfree_skb_rate\x18\x04 \x01(\x01\x12H\n\rnet_tx_action\x18\x05 \x01(\x0b\x32\x31.perfetto.protos.AndroidNetworkMetric.NetTxAction\x12\x43\n\nipi_action\x18\x06 \x01(\x0b\x32/.perfetto.protos.AndroidNetworkMetric.IpiAction\x1a\xa3\x01\n\x0fPacketStatistic\x12\x0f\n\x07packets\x18\x01 \x01(\x03\x12\r\n\x05\x62ytes\x18\x02 \x01(\x03\x12!\n\x19\x66irst_packet_timestamp_ns\x18\x03 \x01(\x03\x12 \n\x18last_packet_timestamp_ns\x18\x04 \x01(\x03\x12\x13\n\x0binterval_ns\x18\x05 \x01(\x03\x12\x16\n\x0e\x64\x61ta_rate_kbps\x18\x06 \x01(\x01\x1ar\n\x13\x43orePacketStatistic\x12\n\n\x02id\x18\x01 \x01(\r\x12O\n\x10packet_statistic\x18\x02 \x01(\x0b\x32\x35.perfetto.protos.AndroidNetworkMetric.PacketStatistic\x1a\xb2\x01\n\x02Rx\x12\x44\n\x05total\x18\x01 \x01(\x0b\x32\x35.perfetto.protos.AndroidNetworkMetric.PacketStatistic\x12G\n\x04\x63ore\x18\x02 \x03(\x0b\x32\x39.perfetto.protos.AndroidNetworkMetric.CorePacketStatistic\x12\x1d\n\x15gro_aggregation_ratio\x18\x03 \x01(\t\x1a\x93\x01\n\x02Tx\x12\x44\n\x05total\x18\x01 \x01(\x0b\x32\x35.perfetto.protos.AndroidNetworkMetric.PacketStatistic\x12G\n\x04\x63ore\x18\x02 \x03(\x0b\x32\x39.perfetto.protos.AndroidNetworkMetric.CorePacketStatistic\x1a\x85\x01\n\tNetDevice\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x34\n\x02rx\x18\x02 \x01(\x0b\x32(.perfetto.protos.AndroidNetworkMetric.Rx\x12\x34\n\x02tx\x18\x03 \x01(\x0b\x32(.perfetto.protos.AndroidNetworkMetric.Tx\x1ax\n\x14NetRxActionStatistic\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12\x12\n\nruntime_ms\x18\x02 \x01(\x01\x12\x16\n\x0e\x61vg_runtime_ms\x18\x03 \x01(\x01\x12\x0f\n\x07mcycles\x18\x04 \x01(\x03\x12\x14\n\x0c\x61vg_freq_khz\x18\x05 \x01(\x03\x1ax\n\x14NetTxActionStatistic\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12\x12\n\nruntime_ms\x18\x02 \x01(\x01\x12\x16\n\x0e\x61vg_runtime_ms\x18\x03 \x01(\x01\x12\x0f\n\x07mcycles\x18\x04 \x01(\x03\x12\x14\n\x0c\x61vg_freq_khz\x18\x05 \x01(\x03\x1aO\n\x12IpiActionStatistic\x12\r\n\x05\x63ount\x18\x01 \x01(\x03\x12\x12\n\nruntime_ms\x18\x02 \x01(\x01\x12\x16\n\x0e\x61vg_runtime_ms\x18\x03 \x01(\x01\x1a\x83\x01\n\x18\x43oreNetRxActionStatistic\x12\n\n\x02id\x18\x01 \x01(\r\x12[\n\x17net_rx_action_statistic\x18\x02 \x01(\x0b\x32:.perfetto.protos.AndroidNetworkMetric.NetRxActionStatistic\x1a\x83\x01\n\x18\x43oreNetTxActionStatistic\x12\n\n\x02id\x18\x01 \x01(\r\x12[\n\x17net_tx_action_statistic\x18\x02 \x01(\x0b\x32:.perfetto.protos.AndroidNetworkMetric.NetTxActionStatistic\x1a\xc9\x01\n\x0bNetRxAction\x12I\n\x05total\x18\x01 \x01(\x0b\x32:.perfetto.protos.AndroidNetworkMetric.NetRxActionStatistic\x12L\n\x04\x63ore\x18\x02 \x03(\x0b\x32>.perfetto.protos.AndroidNetworkMetric.CoreNetRxActionStatistic\x12!\n\x19\x61vg_interstack_latency_ms\x18\x03 \x01(\x01\x1a\xa6\x01\n\x0bNetTxAction\x12I\n\x05total\x18\x01 \x01(\x0b\x32:.perfetto.protos.AndroidNetworkMetric.NetTxActionStatistic\x12L\n\x04\x63ore\x18\x02 \x03(\x0b\x32>.perfetto.protos.AndroidNetworkMetric.CoreNetTxActionStatistic\x1aT\n\tIpiAction\x12G\n\x05total\x18\x01 \x01(\x0b\x32\x38.perfetto.protos.AndroidNetworkMetric.IpiActionStatistic')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.metrics.android.network_metric_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_ANDROIDNETWORKMETRIC']._serialized_start=74
  _globals['_ANDROIDNETWORKMETRIC']._serialized_end=2237
  _globals['_ANDROIDNETWORKMETRIC_PACKETSTATISTIC']._serialized_start=439
  _globals['_ANDROIDNETWORKMETRIC_PACKETSTATISTIC']._serialized_end=602
  _globals['_ANDROIDNETWORKMETRIC_COREPACKETSTATISTIC']._serialized_start=604
  _globals['_ANDROIDNETWORKMETRIC_COREPACKETSTATISTIC']._serialized_end=718
  _globals['_ANDROIDNETWORKMETRIC_RX']._serialized_start=721
  _globals['_ANDROIDNETWORKMETRIC_RX']._serialized_end=899
  _globals['_ANDROIDNETWORKMETRIC_TX']._serialized_start=902
  _globals['_ANDROIDNETWORKMETRIC_TX']._serialized_end=1049
  _globals['_ANDROIDNETWORKMETRIC_NETDEVICE']._serialized_start=1052
  _globals['_ANDROIDNETWORKMETRIC_NETDEVICE']._serialized_end=1185
  _globals['_ANDROIDNETWORKMETRIC_NETRXACTIONSTATISTIC']._serialized_start=1187
  _globals['_ANDROIDNETWORKMETRIC_NETRXACTIONSTATISTIC']._serialized_end=1307
  _globals['_ANDROIDNETWORKMETRIC_NETTXACTIONSTATISTIC']._serialized_start=1309
  _globals['_ANDROIDNETWORKMETRIC_NETTXACTIONSTATISTIC']._serialized_end=1429
  _globals['_ANDROIDNETWORKMETRIC_IPIACTIONSTATISTIC']._serialized_start=1431
  _globals['_ANDROIDNETWORKMETRIC_IPIACTIONSTATISTIC']._serialized_end=1510
  _globals['_ANDROIDNETWORKMETRIC_CORENETRXACTIONSTATISTIC']._serialized_start=1513
  _globals['_ANDROIDNETWORKMETRIC_CORENETRXACTIONSTATISTIC']._serialized_end=1644
  _globals['_ANDROIDNETWORKMETRIC_CORENETTXACTIONSTATISTIC']._serialized_start=1647
  _globals['_ANDROIDNETWORKMETRIC_CORENETTXACTIONSTATISTIC']._serialized_end=1778
  _globals['_ANDROIDNETWORKMETRIC_NETRXACTION']._serialized_start=1781
  _globals['_ANDROIDNETWORKMETRIC_NETRXACTION']._serialized_end=1982
  _globals['_ANDROIDNETWORKMETRIC_NETTXACTION']._serialized_start=1985
  _globals['_ANDROIDNETWORKMETRIC_NETTXACTION']._serialized_end=2151
  _globals['_ANDROIDNETWORKMETRIC_IPIACTION']._serialized_start=2153
  _globals['_ANDROIDNETWORKMETRIC_IPIACTION']._serialized_end=2237
# @@protoc_insertion_point(module_scope)
