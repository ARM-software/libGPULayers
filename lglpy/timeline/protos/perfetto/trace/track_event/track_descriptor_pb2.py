# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/track_event/track_descriptor.proto
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
    'protos/perfetto/trace/track_event/track_descriptor.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.trace.track_event import chrome_process_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_chrome__process__descriptor__pb2
from protos.perfetto.trace.track_event import chrome_thread_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_chrome__thread__descriptor__pb2
from protos.perfetto.trace.track_event import process_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_process__descriptor__pb2
from protos.perfetto.trace.track_event import thread_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_thread__descriptor__pb2
from protos.perfetto.trace.track_event import counter_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_counter__descriptor__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n8protos/perfetto/trace/track_event/track_descriptor.proto\x12\x0fperfetto.protos\x1a\x41protos/perfetto/trace/track_event/chrome_process_descriptor.proto\x1a@protos/perfetto/trace/track_event/chrome_thread_descriptor.proto\x1a:protos/perfetto/trace/track_event/process_descriptor.proto\x1a\x39protos/perfetto/trace/track_event/thread_descriptor.proto\x1a:protos/perfetto/trace/track_event/counter_descriptor.proto\"\xc1\x03\n\x0fTrackDescriptor\x12\x0c\n\x04uuid\x18\x01 \x01(\x04\x12\x13\n\x0bparent_uuid\x18\x05 \x01(\x04\x12\x0e\n\x04name\x18\x02 \x01(\tH\x00\x12\x15\n\x0bstatic_name\x18\n \x01(\tH\x00\x12\x33\n\x07process\x18\x03 \x01(\x0b\x32\".perfetto.protos.ProcessDescriptor\x12@\n\x0e\x63hrome_process\x18\x06 \x01(\x0b\x32(.perfetto.protos.ChromeProcessDescriptor\x12\x31\n\x06thread\x18\x04 \x01(\x0b\x32!.perfetto.protos.ThreadDescriptor\x12>\n\rchrome_thread\x18\x07 \x01(\x0b\x32\'.perfetto.protos.ChromeThreadDescriptor\x12\x33\n\x07\x63ounter\x18\x08 \x01(\x0b\x32\".perfetto.protos.CounterDescriptor\x12+\n#disallow_merging_with_system_tracks\x18\t \x01(\x08\x42\x18\n\x16static_or_dynamic_name')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.track_event.track_descriptor_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TRACKDESCRIPTOR']._serialized_start=390
  _globals['_TRACKDESCRIPTOR']._serialized_end=839
# @@protoc_insertion_point(module_scope)
