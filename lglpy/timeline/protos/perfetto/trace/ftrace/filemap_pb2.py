# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/filemap.proto
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
    'protos/perfetto/trace/ftrace/filemap.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n*protos/perfetto/trace/ftrace/filemap.proto\x12\x0fperfetto.protos\"l\n\"MmFilemapAddToPageCacheFtraceEvent\x12\x0b\n\x03pfn\x18\x01 \x01(\x04\x12\r\n\x05i_ino\x18\x02 \x01(\x04\x12\r\n\x05index\x18\x03 \x01(\x04\x12\r\n\x05s_dev\x18\x04 \x01(\x04\x12\x0c\n\x04page\x18\x05 \x01(\x04\"q\n\'MmFilemapDeleteFromPageCacheFtraceEvent\x12\x0b\n\x03pfn\x18\x01 \x01(\x04\x12\r\n\x05i_ino\x18\x02 \x01(\x04\x12\r\n\x05index\x18\x03 \x01(\x04\x12\r\n\x05s_dev\x18\x04 \x01(\x04\x12\x0c\n\x04page\x18\x05 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.filemap_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_MMFILEMAPADDTOPAGECACHEFTRACEEVENT']._serialized_start=63
  _globals['_MMFILEMAPADDTOPAGECACHEFTRACEEVENT']._serialized_end=171
  _globals['_MMFILEMAPDELETEFROMPAGECACHEFTRACEEVENT']._serialized_start=173
  _globals['_MMFILEMAPDELETEFROMPAGECACHEFTRACEEVENT']._serialized_end=286
# @@protoc_insertion_point(module_scope)
