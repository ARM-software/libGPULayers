# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/ftrace/kvm.proto
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
    'protos/perfetto/trace/ftrace/kvm.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n&protos/perfetto/trace/ftrace/kvm.proto\x12\x0fperfetto.protos\"(\n\x19KvmAccessFaultFtraceEvent\x12\x0b\n\x03ipa\x18\x01 \x01(\x04\"4\n\x14KvmAckIrqFtraceEvent\x12\x0f\n\x07irqchip\x18\x01 \x01(\r\x12\x0b\n\x03pin\x18\x02 \x01(\r\"2\n\x14KvmAgeHvaFtraceEvent\x12\x0b\n\x03\x65nd\x18\x01 \x01(\x04\x12\r\n\x05start\x18\x02 \x01(\x04\"T\n\x15KvmAgePageFtraceEvent\x12\x0b\n\x03gfn\x18\x01 \x01(\x04\x12\x0b\n\x03hva\x18\x02 \x01(\x04\x12\r\n\x05level\x18\x03 \x01(\r\x12\x12\n\nreferenced\x18\x04 \x01(\r\"2\n\x1bKvmArmClearDebugFtraceEvent\x12\x13\n\x0bguest_debug\x18\x01 \x01(\r\"9\n\x1aKvmArmSetDreg32FtraceEvent\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\r\n\x05value\x18\x02 \x01(\r\"7\n\x1aKvmArmSetRegsetFtraceEvent\x12\x0b\n\x03len\x18\x01 \x01(\x05\x12\x0c\n\x04name\x18\x02 \x01(\t\"@\n\x1bKvmArmSetupDebugFtraceEvent\x12\x13\n\x0bguest_debug\x18\x01 \x01(\r\x12\x0c\n\x04vcpu\x18\x02 \x01(\x04\"&\n\x13KvmEntryFtraceEvent\x12\x0f\n\x07vcpu_pc\x18\x01 \x01(\x04\"B\n\x12KvmExitFtraceEvent\x12\x0e\n\x06\x65sr_ec\x18\x01 \x01(\r\x12\x0b\n\x03ret\x18\x02 \x01(\x05\x12\x0f\n\x07vcpu_pc\x18\x03 \x01(\x04\"!\n\x11KvmFpuFtraceEvent\x12\x0c\n\x04load\x18\x01 \x01(\r\"o\n\x19KvmGetTimerMapFtraceEvent\x12\x15\n\rdirect_ptimer\x18\x01 \x01(\x05\x12\x15\n\rdirect_vtimer\x18\x02 \x01(\x05\x12\x13\n\x0b\x65mul_ptimer\x18\x03 \x01(\x05\x12\x0f\n\x07vcpu_id\x18\x04 \x01(\x04\"T\n\x18KvmGuestFaultFtraceEvent\x12\x0b\n\x03hsr\x18\x01 \x01(\x04\x12\r\n\x05hxfar\x18\x02 \x01(\x04\x12\x0b\n\x03ipa\x18\x03 \x01(\x04\x12\x0f\n\x07vcpu_pc\x18\x04 \x01(\x04\")\n\x1aKvmHandleSysRegFtraceEvent\x12\x0b\n\x03hsr\x18\x01 \x01(\x04\"B\n\x16KvmHvcArm64FtraceEvent\x12\x0b\n\x03imm\x18\x01 \x01(\x04\x12\n\n\x02r0\x18\x02 \x01(\x04\x12\x0f\n\x07vcpu_pc\x18\x03 \x01(\x04\"W\n\x15KvmIrqLineFtraceEvent\x12\x0f\n\x07irq_num\x18\x01 \x01(\x05\x12\r\n\x05level\x18\x02 \x01(\x05\x12\x0c\n\x04type\x18\x03 \x01(\r\x12\x10\n\x08vcpu_idx\x18\x04 \x01(\x05\"I\n\x12KvmMmioFtraceEvent\x12\x0b\n\x03gpa\x18\x01 \x01(\x04\x12\x0b\n\x03len\x18\x02 \x01(\r\x12\x0c\n\x04type\x18\x03 \x01(\r\x12\x0b\n\x03val\x18\x04 \x01(\x04\"I\n\x19KvmMmioEmulateFtraceEvent\x12\x0c\n\x04\x63psr\x18\x01 \x01(\x04\x12\r\n\x05instr\x18\x02 \x01(\x04\x12\x0f\n\x07vcpu_pc\x18\x03 \x01(\x04\"@\n\x1bKvmSetGuestDebugFtraceEvent\x12\x13\n\x0bguest_debug\x18\x01 \x01(\r\x12\x0c\n\x04vcpu\x18\x02 \x01(\x04\"I\n\x14KvmSetIrqFtraceEvent\x12\x0b\n\x03gsi\x18\x01 \x01(\r\x12\x15\n\rirq_source_id\x18\x02 \x01(\x05\x12\r\n\x05level\x18\x03 \x01(\x05\"\'\n\x18KvmSetSpteHvaFtraceEvent\x12\x0b\n\x03hva\x18\x01 \x01(\x04\";\n\x19KvmSetWayFlushFtraceEvent\x12\r\n\x05\x63\x61\x63he\x18\x01 \x01(\r\x12\x0f\n\x07vcpu_pc\x18\x02 \x01(\x04\"\x8b\x01\n\x17KvmSysAccessFtraceEvent\x12\x0b\n\x03\x43Rm\x18\x01 \x01(\r\x12\x0b\n\x03\x43Rn\x18\x02 \x01(\r\x12\x0b\n\x03Op0\x18\x03 \x01(\r\x12\x0b\n\x03Op1\x18\x04 \x01(\r\x12\x0b\n\x03Op2\x18\x05 \x01(\r\x12\x10\n\x08is_write\x18\x06 \x01(\r\x12\x0c\n\x04name\x18\x07 \x01(\t\x12\x0f\n\x07vcpu_pc\x18\x08 \x01(\x04\"\'\n\x18KvmTestAgeHvaFtraceEvent\x12\x0b\n\x03hva\x18\x01 \x01(\x04\"D\n\x1aKvmTimerEmulateFtraceEvent\x12\x13\n\x0bshould_fire\x18\x01 \x01(\r\x12\x11\n\ttimer_idx\x18\x02 \x01(\x05\"5\n KvmTimerHrtimerExpireFtraceEvent\x12\x11\n\ttimer_idx\x18\x01 \x01(\x05\"O\n\x1fKvmTimerRestoreStateFtraceEvent\x12\x0b\n\x03\x63tl\x18\x01 \x01(\x04\x12\x0c\n\x04\x63val\x18\x02 \x01(\x04\x12\x11\n\ttimer_idx\x18\x03 \x01(\x05\"L\n\x1cKvmTimerSaveStateFtraceEvent\x12\x0b\n\x03\x63tl\x18\x01 \x01(\x04\x12\x0c\n\x04\x63val\x18\x02 \x01(\x04\x12\x11\n\ttimer_idx\x18\x03 \x01(\x05\"K\n\x1cKvmTimerUpdateIrqFtraceEvent\x12\x0b\n\x03irq\x18\x01 \x01(\r\x12\r\n\x05level\x18\x02 \x01(\x05\x12\x0f\n\x07vcpu_id\x18\x03 \x01(\x04\"F\n\x19KvmToggleCacheFtraceEvent\x12\x0b\n\x03now\x18\x01 \x01(\r\x12\x0f\n\x07vcpu_pc\x18\x02 \x01(\x04\x12\x0b\n\x03was\x18\x03 \x01(\r\"9\n\x1bKvmUnmapHvaRangeFtraceEvent\x12\x0b\n\x03\x65nd\x18\x01 \x01(\x04\x12\r\n\x05start\x18\x02 \x01(\x04\"-\n\x1bKvmUserspaceExitFtraceEvent\x12\x0e\n\x06reason\x18\x01 \x01(\r\"E\n\x18KvmVcpuWakeupFtraceEvent\x12\n\n\x02ns\x18\x01 \x01(\x04\x12\r\n\x05valid\x18\x02 \x01(\r\x12\x0e\n\x06waited\x18\x03 \x01(\r\"9\n\x16KvmWfxArm64FtraceEvent\x12\x0e\n\x06is_wfe\x18\x01 \x01(\r\x12\x0f\n\x07vcpu_pc\x18\x02 \x01(\x04\"T\n\x12TrapRegFtraceEvent\x12\n\n\x02\x66n\x18\x01 \x01(\t\x12\x10\n\x08is_write\x18\x02 \x01(\r\x12\x0b\n\x03reg\x18\x03 \x01(\x05\x12\x13\n\x0bwrite_value\x18\x04 \x01(\x04\"N\n\x1fVgicUpdateIrqPendingFtraceEvent\x12\x0b\n\x03irq\x18\x01 \x01(\r\x12\r\n\x05level\x18\x02 \x01(\r\x12\x0f\n\x07vcpu_id\x18\x03 \x01(\x04')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.ftrace.kvm_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_KVMACCESSFAULTFTRACEEVENT']._serialized_start=59
  _globals['_KVMACCESSFAULTFTRACEEVENT']._serialized_end=99
  _globals['_KVMACKIRQFTRACEEVENT']._serialized_start=101
  _globals['_KVMACKIRQFTRACEEVENT']._serialized_end=153
  _globals['_KVMAGEHVAFTRACEEVENT']._serialized_start=155
  _globals['_KVMAGEHVAFTRACEEVENT']._serialized_end=205
  _globals['_KVMAGEPAGEFTRACEEVENT']._serialized_start=207
  _globals['_KVMAGEPAGEFTRACEEVENT']._serialized_end=291
  _globals['_KVMARMCLEARDEBUGFTRACEEVENT']._serialized_start=293
  _globals['_KVMARMCLEARDEBUGFTRACEEVENT']._serialized_end=343
  _globals['_KVMARMSETDREG32FTRACEEVENT']._serialized_start=345
  _globals['_KVMARMSETDREG32FTRACEEVENT']._serialized_end=402
  _globals['_KVMARMSETREGSETFTRACEEVENT']._serialized_start=404
  _globals['_KVMARMSETREGSETFTRACEEVENT']._serialized_end=459
  _globals['_KVMARMSETUPDEBUGFTRACEEVENT']._serialized_start=461
  _globals['_KVMARMSETUPDEBUGFTRACEEVENT']._serialized_end=525
  _globals['_KVMENTRYFTRACEEVENT']._serialized_start=527
  _globals['_KVMENTRYFTRACEEVENT']._serialized_end=565
  _globals['_KVMEXITFTRACEEVENT']._serialized_start=567
  _globals['_KVMEXITFTRACEEVENT']._serialized_end=633
  _globals['_KVMFPUFTRACEEVENT']._serialized_start=635
  _globals['_KVMFPUFTRACEEVENT']._serialized_end=668
  _globals['_KVMGETTIMERMAPFTRACEEVENT']._serialized_start=670
  _globals['_KVMGETTIMERMAPFTRACEEVENT']._serialized_end=781
  _globals['_KVMGUESTFAULTFTRACEEVENT']._serialized_start=783
  _globals['_KVMGUESTFAULTFTRACEEVENT']._serialized_end=867
  _globals['_KVMHANDLESYSREGFTRACEEVENT']._serialized_start=869
  _globals['_KVMHANDLESYSREGFTRACEEVENT']._serialized_end=910
  _globals['_KVMHVCARM64FTRACEEVENT']._serialized_start=912
  _globals['_KVMHVCARM64FTRACEEVENT']._serialized_end=978
  _globals['_KVMIRQLINEFTRACEEVENT']._serialized_start=980
  _globals['_KVMIRQLINEFTRACEEVENT']._serialized_end=1067
  _globals['_KVMMMIOFTRACEEVENT']._serialized_start=1069
  _globals['_KVMMMIOFTRACEEVENT']._serialized_end=1142
  _globals['_KVMMMIOEMULATEFTRACEEVENT']._serialized_start=1144
  _globals['_KVMMMIOEMULATEFTRACEEVENT']._serialized_end=1217
  _globals['_KVMSETGUESTDEBUGFTRACEEVENT']._serialized_start=1219
  _globals['_KVMSETGUESTDEBUGFTRACEEVENT']._serialized_end=1283
  _globals['_KVMSETIRQFTRACEEVENT']._serialized_start=1285
  _globals['_KVMSETIRQFTRACEEVENT']._serialized_end=1358
  _globals['_KVMSETSPTEHVAFTRACEEVENT']._serialized_start=1360
  _globals['_KVMSETSPTEHVAFTRACEEVENT']._serialized_end=1399
  _globals['_KVMSETWAYFLUSHFTRACEEVENT']._serialized_start=1401
  _globals['_KVMSETWAYFLUSHFTRACEEVENT']._serialized_end=1460
  _globals['_KVMSYSACCESSFTRACEEVENT']._serialized_start=1463
  _globals['_KVMSYSACCESSFTRACEEVENT']._serialized_end=1602
  _globals['_KVMTESTAGEHVAFTRACEEVENT']._serialized_start=1604
  _globals['_KVMTESTAGEHVAFTRACEEVENT']._serialized_end=1643
  _globals['_KVMTIMEREMULATEFTRACEEVENT']._serialized_start=1645
  _globals['_KVMTIMEREMULATEFTRACEEVENT']._serialized_end=1713
  _globals['_KVMTIMERHRTIMEREXPIREFTRACEEVENT']._serialized_start=1715
  _globals['_KVMTIMERHRTIMEREXPIREFTRACEEVENT']._serialized_end=1768
  _globals['_KVMTIMERRESTORESTATEFTRACEEVENT']._serialized_start=1770
  _globals['_KVMTIMERRESTORESTATEFTRACEEVENT']._serialized_end=1849
  _globals['_KVMTIMERSAVESTATEFTRACEEVENT']._serialized_start=1851
  _globals['_KVMTIMERSAVESTATEFTRACEEVENT']._serialized_end=1927
  _globals['_KVMTIMERUPDATEIRQFTRACEEVENT']._serialized_start=1929
  _globals['_KVMTIMERUPDATEIRQFTRACEEVENT']._serialized_end=2004
  _globals['_KVMTOGGLECACHEFTRACEEVENT']._serialized_start=2006
  _globals['_KVMTOGGLECACHEFTRACEEVENT']._serialized_end=2076
  _globals['_KVMUNMAPHVARANGEFTRACEEVENT']._serialized_start=2078
  _globals['_KVMUNMAPHVARANGEFTRACEEVENT']._serialized_end=2135
  _globals['_KVMUSERSPACEEXITFTRACEEVENT']._serialized_start=2137
  _globals['_KVMUSERSPACEEXITFTRACEEVENT']._serialized_end=2182
  _globals['_KVMVCPUWAKEUPFTRACEEVENT']._serialized_start=2184
  _globals['_KVMVCPUWAKEUPFTRACEEVENT']._serialized_end=2253
  _globals['_KVMWFXARM64FTRACEEVENT']._serialized_start=2255
  _globals['_KVMWFXARM64FTRACEEVENT']._serialized_end=2312
  _globals['_TRAPREGFTRACEEVENT']._serialized_start=2314
  _globals['_TRAPREGFTRACEEVENT']._serialized_end=2398
  _globals['_VGICUPDATEIRQPENDINGFTRACEEVENT']._serialized_start=2400
  _globals['_VGICUPDATEIRQPENDINGFTRACEEVENT']._serialized_end=2478
# @@protoc_insertion_point(module_scope)
