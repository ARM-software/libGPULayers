# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/config/statsd/statsd_tracing_config.proto
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
    'protos/perfetto/config/statsd/statsd_tracing_config.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.config.statsd import atom_ids_pb2 as protos_dot_perfetto_dot_config_dot_statsd_dot_atom__ids__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n9protos/perfetto/config/statsd/statsd_tracing_config.proto\x12\x0fperfetto.protos\x1a,protos/perfetto/config/statsd/atom_ids.proto\"\x9a\x01\n\x13StatsdTracingConfig\x12-\n\x0cpush_atom_id\x18\x01 \x03(\x0e\x32\x17.perfetto.protos.AtomId\x12\x18\n\x10raw_push_atom_id\x18\x02 \x03(\x05\x12:\n\x0bpull_config\x18\x03 \x03(\x0b\x32%.perfetto.protos.StatsdPullAtomConfig\"\x8c\x01\n\x14StatsdPullAtomConfig\x12-\n\x0cpull_atom_id\x18\x01 \x03(\x0e\x32\x17.perfetto.protos.AtomId\x12\x18\n\x10raw_pull_atom_id\x18\x02 \x03(\x05\x12\x19\n\x11pull_frequency_ms\x18\x03 \x01(\x05\x12\x10\n\x08packages\x18\x04 \x03(\t')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.config.statsd.statsd_tracing_config_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_STATSDTRACINGCONFIG']._serialized_start=125
  _globals['_STATSDTRACINGCONFIG']._serialized_end=279
  _globals['_STATSDPULLATOMCONFIG']._serialized_start=282
  _globals['_STATSDPULLATOMCONFIG']._serialized_end=422
# @@protoc_insertion_point(module_scope)
