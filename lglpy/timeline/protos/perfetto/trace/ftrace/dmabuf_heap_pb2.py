# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/dmabuf_heap.proto
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
    'protos/perfetto/trace/ftrace/dmabuf_heap.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n.protos/perfetto/trace/ftrace/dmabuf_heap.proto\x12\x0fperfetto.protos\"M\n\x16\x44maHeapStatFtraceEvent\x12\r\n\x05inode\x18\x01 \x01(\x04\x12\x0b\n\x03len\x18\x02 \x01(\x03\x12\x17\n\x0ftotal_allocated\x18\x03 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.dmabuf_heap_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_DMAHEAPSTATFTRACEEVENT']._serialized_start=67
  _globals['_DMAHEAPSTATFTRACEEVENT']._serialized_end=144
# @@protoc_insertion_point(module_scope)
