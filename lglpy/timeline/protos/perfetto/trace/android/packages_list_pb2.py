# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/packages_list.proto
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
    'protos/perfetto/trace/android/packages_list.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n1protos/perfetto/trace/android/packages_list.proto\x12\x0fperfetto.protos\"\xe8\x01\n\x0cPackagesList\x12;\n\x08packages\x18\x01 \x03(\x0b\x32).perfetto.protos.PackagesList.PackageInfo\x12\x13\n\x0bparse_error\x18\x02 \x01(\x08\x12\x12\n\nread_error\x18\x03 \x01(\x08\x1ar\n\x0bPackageInfo\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0b\n\x03uid\x18\x02 \x01(\x04\x12\x12\n\ndebuggable\x18\x03 \x01(\x08\x12\x1e\n\x16profileable_from_shell\x18\x04 \x01(\x08\x12\x14\n\x0cversion_code\x18\x05 \x01(\x03')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.packages_list_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_PACKAGESLIST']._serialized_start=71
  _globals['_PACKAGESLIST']._serialized_end=303
  _globals['_PACKAGESLIST_PACKAGEINFO']._serialized_start=189
  _globals['_PACKAGESLIST_PACKAGEINFO']._serialized_end=303
# @@protoc_insertion_point(module_scope)
