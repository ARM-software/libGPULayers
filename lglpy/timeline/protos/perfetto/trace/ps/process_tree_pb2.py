# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ps/process_tree.proto
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
    'protos/perfetto/trace/ps/process_tree.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n+protos/perfetto/trace/ps/process_tree.proto\x12\x0fperfetto.protos\"\xda\x02\n\x0bProcessTree\x12\x37\n\tprocesses\x18\x01 \x03(\x0b\x32$.perfetto.protos.ProcessTree.Process\x12\x34\n\x07threads\x18\x02 \x03(\x0b\x32#.perfetto.protos.ProcessTree.Thread\x12 \n\x18\x63ollection_end_timestamp\x18\x03 \x01(\x04\x1a@\n\x06Thread\x12\x0b\n\x03tid\x18\x01 \x01(\x05\x12\x0c\n\x04tgid\x18\x03 \x01(\x05\x12\x0c\n\x04name\x18\x02 \x01(\t\x12\r\n\x05nstid\x18\x04 \x03(\x05\x1ax\n\x07Process\x12\x0b\n\x03pid\x18\x01 \x01(\x05\x12\x0c\n\x04ppid\x18\x02 \x01(\x05\x12\x0f\n\x07\x63mdline\x18\x03 \x03(\t\x12\x0b\n\x03uid\x18\x05 \x01(\x05\x12\r\n\x05nspid\x18\x06 \x03(\x05\x12\x1f\n\x17process_start_from_boot\x18\x07 \x01(\x04J\x04\x08\x04\x10\x05')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ps.process_tree_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PROCESSTREE']._serialized_start=65
  _globals['_PROCESSTREE']._serialized_end=411
  _globals['_PROCESSTREE_THREAD']._serialized_start=225
  _globals['_PROCESSTREE_THREAD']._serialized_end=289
  _globals['_PROCESSTREE_PROCESS']._serialized_start=291
  _globals['_PROCESSTREE_PROCESS']._serialized_end=411
# @@protoc_insertion_point(module_scope)
