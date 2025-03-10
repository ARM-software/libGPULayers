# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/android/view/inputmethod/inputconnection.proto
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
    'protos/perfetto/trace/android/view/inputmethod/inputconnection.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\nDprotos/perfetto/trace/android/view/inputmethod/inputconnection.proto\x12\x0fperfetto.protos\"t\n\x14InputConnectionProto\x12\x1b\n\x13selected_text_start\x18\x03 \x01(\x05\x12\x19\n\x11selected_text_end\x18\x04 \x01(\x05\x12\x18\n\x10\x63ursor_caps_mode\x18\x05 \x01(\x05J\x04\x08\x01\x10\x02J\x04\x08\x02\x10\x03\"\xa9\n\n\x18InputConnectionCallProto\x12_\n\x16get_text_before_cursor\x18\x01 \x01(\x0b\x32=.perfetto.protos.InputConnectionCallProto.GetTextBeforeCursorH\x00\x12]\n\x15get_text_after_cursor\x18\x02 \x01(\x0b\x32<.perfetto.protos.InputConnectionCallProto.GetTextAfterCursorH\x00\x12V\n\x11get_selected_text\x18\x03 \x01(\x0b\x32\x39.perfetto.protos.InputConnectionCallProto.GetSelectedTextH\x00\x12\\\n\x14get_surrounding_text\x18\x04 \x01(\x0b\x32<.perfetto.protos.InputConnectionCallProto.GetSurroundingTextH\x00\x12[\n\x14get_cursor_caps_mode\x18\x05 \x01(\x0b\x32;.perfetto.protos.InputConnectionCallProto.GetCursorCapsModeH\x00\x12X\n\x12get_extracted_text\x18\x06 \x01(\x0b\x32:.perfetto.protos.InputConnectionCallProto.GetExtractedTextH\x00\x1a:\n\x13GetTextBeforeCursor\x12\x0e\n\x06length\x18\x01 \x01(\x05\x12\r\n\x05\x66lags\x18\x02 \x01(\x05J\x04\x08\x03\x10\x04\x1a\x39\n\x12GetTextAfterCursor\x12\x0e\n\x06length\x18\x01 \x01(\x05\x12\r\n\x05\x66lags\x18\x02 \x01(\x05J\x04\x08\x03\x10\x04\x1a&\n\x0fGetSelectedText\x12\r\n\x05\x66lags\x18\x01 \x01(\x05J\x04\x08\x02\x10\x03\x1a\x87\x02\n\x12GetSurroundingText\x12\x15\n\rbefore_length\x18\x01 \x01(\x05\x12\x14\n\x0c\x61\x66ter_length\x18\x02 \x01(\x05\x12\r\n\x05\x66lags\x18\x03 \x01(\x05\x12\\\n\x06result\x18\x04 \x01(\x0b\x32L.perfetto.protos.InputConnectionCallProto.GetSurroundingText.SurroundingText\x1aW\n\x0fSurroundingText\x12\x17\n\x0fselection_start\x18\x02 \x01(\x05\x12\x15\n\rselection_end\x18\x03 \x01(\x05\x12\x0e\n\x06offset\x18\x04 \x01(\x05J\x04\x08\x01\x10\x02\x1a\x36\n\x11GetCursorCapsMode\x12\x11\n\treq_modes\x18\x01 \x01(\x05\x12\x0e\n\x06result\x18\x02 \x01(\x05\x1a\xef\x01\n\x10GetExtractedText\x12`\n\x07request\x18\x01 \x01(\x0b\x32O.perfetto.protos.InputConnectionCallProto.GetExtractedText.ExtractedTextRequest\x12\r\n\x05\x66lags\x18\x02 \x01(\x05\x1a\x64\n\x14\x45xtractedTextRequest\x12\r\n\x05token\x18\x01 \x01(\x05\x12\r\n\x05\x66lags\x18\x02 \x01(\x05\x12\x16\n\x0ehint_max_lines\x18\x03 \x01(\x05\x12\x16\n\x0ehint_max_chars\x18\x04 \x01(\x05J\x04\x08\x03\x10\x04\x42\r\n\x0bmethod_call')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.android.view.inputmethod.inputconnection_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_INPUTCONNECTIONPROTO']._serialized_start=89
  _globals['_INPUTCONNECTIONPROTO']._serialized_end=205
  _globals['_INPUTCONNECTIONCALLPROTO']._serialized_start=208
  _globals['_INPUTCONNECTIONCALLPROTO']._serialized_end=1529
  _globals['_INPUTCONNECTIONCALLPROTO_GETTEXTBEFORECURSOR']._serialized_start=793
  _globals['_INPUTCONNECTIONCALLPROTO_GETTEXTBEFORECURSOR']._serialized_end=851
  _globals['_INPUTCONNECTIONCALLPROTO_GETTEXTAFTERCURSOR']._serialized_start=853
  _globals['_INPUTCONNECTIONCALLPROTO_GETTEXTAFTERCURSOR']._serialized_end=910
  _globals['_INPUTCONNECTIONCALLPROTO_GETSELECTEDTEXT']._serialized_start=912
  _globals['_INPUTCONNECTIONCALLPROTO_GETSELECTEDTEXT']._serialized_end=950
  _globals['_INPUTCONNECTIONCALLPROTO_GETSURROUNDINGTEXT']._serialized_start=953
  _globals['_INPUTCONNECTIONCALLPROTO_GETSURROUNDINGTEXT']._serialized_end=1216
  _globals['_INPUTCONNECTIONCALLPROTO_GETSURROUNDINGTEXT_SURROUNDINGTEXT']._serialized_start=1129
  _globals['_INPUTCONNECTIONCALLPROTO_GETSURROUNDINGTEXT_SURROUNDINGTEXT']._serialized_end=1216
  _globals['_INPUTCONNECTIONCALLPROTO_GETCURSORCAPSMODE']._serialized_start=1218
  _globals['_INPUTCONNECTIONCALLPROTO_GETCURSORCAPSMODE']._serialized_end=1272
  _globals['_INPUTCONNECTIONCALLPROTO_GETEXTRACTEDTEXT']._serialized_start=1275
  _globals['_INPUTCONNECTIONCALLPROTO_GETEXTRACTEDTEXT']._serialized_end=1514
  _globals['_INPUTCONNECTIONCALLPROTO_GETEXTRACTEDTEXT_EXTRACTEDTEXTREQUEST']._serialized_start=1408
  _globals['_INPUTCONNECTIONCALLPROTO_GETEXTRACTEDTEXT_EXTRACTEDTEXTREQUEST']._serialized_end=1508
# @@protoc_insertion_point(module_scope)
