# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/cgroup.proto
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
    'protos/perfetto/trace/ftrace/cgroup.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)protos/perfetto/trace/ftrace/cgroup.proto\x12\x0fperfetto.protos\"\x8e\x01\n\x1b\x43groupAttachTaskFtraceEvent\x12\x10\n\x08\x64st_root\x18\x01 \x01(\x05\x12\x0e\n\x06\x64st_id\x18\x02 \x01(\x05\x12\x0b\n\x03pid\x18\x03 \x01(\x05\x12\x0c\n\x04\x63omm\x18\x04 \x01(\t\x12\r\n\x05\x63name\x18\x05 \x01(\t\x12\x11\n\tdst_level\x18\x06 \x01(\x05\x12\x10\n\x08\x64st_path\x18\x07 \x01(\t\"^\n\x16\x43groupMkdirFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\n\n\x02id\x18\x02 \x01(\x05\x12\r\n\x05\x63name\x18\x03 \x01(\t\x12\r\n\x05level\x18\x04 \x01(\x05\x12\x0c\n\x04path\x18\x05 \x01(\t\"G\n\x18\x43groupRemountFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\x0f\n\x07ss_mask\x18\x02 \x01(\r\x12\x0c\n\x04name\x18\x03 \x01(\t\"^\n\x16\x43groupRmdirFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\n\n\x02id\x18\x02 \x01(\x05\x12\r\n\x05\x63name\x18\x03 \x01(\t\x12\r\n\x05level\x18\x04 \x01(\x05\x12\x0c\n\x04path\x18\x05 \x01(\t\"\x91\x01\n\x1e\x43groupTransferTasksFtraceEvent\x12\x10\n\x08\x64st_root\x18\x01 \x01(\x05\x12\x0e\n\x06\x64st_id\x18\x02 \x01(\x05\x12\x0b\n\x03pid\x18\x03 \x01(\x05\x12\x0c\n\x04\x63omm\x18\x04 \x01(\t\x12\r\n\x05\x63name\x18\x05 \x01(\t\x12\x11\n\tdst_level\x18\x06 \x01(\x05\x12\x10\n\x08\x64st_path\x18\x07 \x01(\t\"K\n\x1c\x43groupDestroyRootFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\x0f\n\x07ss_mask\x18\x02 \x01(\r\x12\x0c\n\x04name\x18\x03 \x01(\t\"`\n\x18\x43groupReleaseFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\n\n\x02id\x18\x02 \x01(\x05\x12\r\n\x05\x63name\x18\x03 \x01(\t\x12\r\n\x05level\x18\x04 \x01(\x05\x12\x0c\n\x04path\x18\x05 \x01(\t\"_\n\x17\x43groupRenameFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\n\n\x02id\x18\x02 \x01(\x05\x12\r\n\x05\x63name\x18\x03 \x01(\t\x12\r\n\x05level\x18\x04 \x01(\x05\x12\x0c\n\x04path\x18\x05 \x01(\t\"I\n\x1a\x43groupSetupRootFtraceEvent\x12\x0c\n\x04root\x18\x01 \x01(\x05\x12\x0f\n\x07ss_mask\x18\x02 \x01(\r\x12\x0c\n\x04name\x18\x03 \x01(\t')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.cgroup_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CGROUPATTACHTASKFTRACEEVENT']._serialized_start=63
  _globals['_CGROUPATTACHTASKFTRACEEVENT']._serialized_end=205
  _globals['_CGROUPMKDIRFTRACEEVENT']._serialized_start=207
  _globals['_CGROUPMKDIRFTRACEEVENT']._serialized_end=301
  _globals['_CGROUPREMOUNTFTRACEEVENT']._serialized_start=303
  _globals['_CGROUPREMOUNTFTRACEEVENT']._serialized_end=374
  _globals['_CGROUPRMDIRFTRACEEVENT']._serialized_start=376
  _globals['_CGROUPRMDIRFTRACEEVENT']._serialized_end=470
  _globals['_CGROUPTRANSFERTASKSFTRACEEVENT']._serialized_start=473
  _globals['_CGROUPTRANSFERTASKSFTRACEEVENT']._serialized_end=618
  _globals['_CGROUPDESTROYROOTFTRACEEVENT']._serialized_start=620
  _globals['_CGROUPDESTROYROOTFTRACEEVENT']._serialized_end=695
  _globals['_CGROUPRELEASEFTRACEEVENT']._serialized_start=697
  _globals['_CGROUPRELEASEFTRACEEVENT']._serialized_end=793
  _globals['_CGROUPRENAMEFTRACEEVENT']._serialized_start=795
  _globals['_CGROUPRENAMEFTRACEEVENT']._serialized_end=890
  _globals['_CGROUPSETUPROOTFTRACEEVENT']._serialized_start=892
  _globals['_CGROUPSETUPROOTFTRACEEVENT']._serialized_end=965
# @@protoc_insertion_point(module_scope)
