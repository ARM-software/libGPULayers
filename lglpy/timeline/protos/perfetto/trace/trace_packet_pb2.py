# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: protos/perfetto/trace/trace_packet.proto
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
    'protos/perfetto/trace/trace_packet.proto'
)
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from protos.perfetto.common import trace_stats_pb2 as protos_dot_perfetto_dot_common_dot_trace__stats__pb2
from protos.perfetto.config import trace_config_pb2 as protos_dot_perfetto_dot_config_dot_trace__config__pb2
from protos.perfetto.trace import extension_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_extension__descriptor__pb2
from protos.perfetto.trace.android import android_game_intervention_list_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_android__game__intervention__list__pb2
from protos.perfetto.trace.android import android_log_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_android__log__pb2
from protos.perfetto.trace.android import android_system_property_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_android__system__property__pb2
from protos.perfetto.trace.android import camera_event_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_camera__event__pb2
from protos.perfetto.trace.android import frame_timeline_event_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_frame__timeline__event__pb2
from protos.perfetto.trace.android import gpu_mem_event_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_gpu__mem__event__pb2
from protos.perfetto.trace.android import graphics_frame_event_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_graphics__frame__event__pb2
from protos.perfetto.trace.android import initial_display_state_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_initial__display__state__pb2
from protos.perfetto.trace.android import network_trace_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_network__trace__pb2
from protos.perfetto.trace.android import packages_list_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_packages__list__pb2
from protos.perfetto.trace.android import pixel_modem_events_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_pixel__modem__events__pb2
from protos.perfetto.trace.android import protolog_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_protolog__pb2
from protos.perfetto.trace.android import shell_transition_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_shell__transition__pb2
from protos.perfetto.trace.android import surfaceflinger_layers_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_surfaceflinger__layers__pb2
from protos.perfetto.trace.android import surfaceflinger_transactions_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_surfaceflinger__transactions__pb2
from protos.perfetto.trace.android import winscope_extensions_pb2 as protos_dot_perfetto_dot_trace_dot_android_dot_winscope__extensions__pb2
from protos.perfetto.trace.chrome import chrome_benchmark_metadata_pb2 as protos_dot_perfetto_dot_trace_dot_chrome_dot_chrome__benchmark__metadata__pb2
from protos.perfetto.trace.chrome import chrome_metadata_pb2 as protos_dot_perfetto_dot_trace_dot_chrome_dot_chrome__metadata__pb2
from protos.perfetto.trace.chrome import chrome_trace_event_pb2 as protos_dot_perfetto_dot_trace_dot_chrome_dot_chrome__trace__event__pb2
from protos.perfetto.trace.chrome import chrome_trigger_pb2 as protos_dot_perfetto_dot_trace_dot_chrome_dot_chrome__trigger__pb2
from protos.perfetto.trace.chrome import v8_pb2 as protos_dot_perfetto_dot_trace_dot_chrome_dot_v8__pb2
from protos.perfetto.trace import clock_snapshot_pb2 as protos_dot_perfetto_dot_trace_dot_clock__snapshot__pb2
from protos.perfetto.trace.etw import etw_event_bundle_pb2 as protos_dot_perfetto_dot_trace_dot_etw_dot_etw__event__bundle__pb2
from protos.perfetto.trace.filesystem import inode_file_map_pb2 as protos_dot_perfetto_dot_trace_dot_filesystem_dot_inode__file__map__pb2
from protos.perfetto.trace.ftrace import ftrace_event_bundle_pb2 as protos_dot_perfetto_dot_trace_dot_ftrace_dot_ftrace__event__bundle__pb2
from protos.perfetto.trace.ftrace import ftrace_stats_pb2 as protos_dot_perfetto_dot_trace_dot_ftrace_dot_ftrace__stats__pb2
from protos.perfetto.trace.gpu import gpu_counter_event_pb2 as protos_dot_perfetto_dot_trace_dot_gpu_dot_gpu__counter__event__pb2
from protos.perfetto.trace.gpu import gpu_log_pb2 as protos_dot_perfetto_dot_trace_dot_gpu_dot_gpu__log__pb2
from protos.perfetto.trace.gpu import gpu_render_stage_event_pb2 as protos_dot_perfetto_dot_trace_dot_gpu_dot_gpu__render__stage__event__pb2
from protos.perfetto.trace.gpu import vulkan_memory_event_pb2 as protos_dot_perfetto_dot_trace_dot_gpu_dot_vulkan__memory__event__pb2
from protos.perfetto.trace.gpu import vulkan_api_event_pb2 as protos_dot_perfetto_dot_trace_dot_gpu_dot_vulkan__api__event__pb2
from protos.perfetto.trace.interned_data import interned_data_pb2 as protos_dot_perfetto_dot_trace_dot_interned__data_dot_interned__data__pb2
from protos.perfetto.trace import memory_graph_pb2 as protos_dot_perfetto_dot_trace_dot_memory__graph__pb2
from protos.perfetto.trace.perfetto import perfetto_metatrace_pb2 as protos_dot_perfetto_dot_trace_dot_perfetto_dot_perfetto__metatrace__pb2
from protos.perfetto.trace.perfetto import tracing_service_event_pb2 as protos_dot_perfetto_dot_trace_dot_perfetto_dot_tracing__service__event__pb2
from protos.perfetto.trace.power import android_energy_estimation_breakdown_pb2 as protos_dot_perfetto_dot_trace_dot_power_dot_android__energy__estimation__breakdown__pb2
from protos.perfetto.trace.power import android_entity_state_residency_pb2 as protos_dot_perfetto_dot_trace_dot_power_dot_android__entity__state__residency__pb2
from protos.perfetto.trace.power import battery_counters_pb2 as protos_dot_perfetto_dot_trace_dot_power_dot_battery__counters__pb2
from protos.perfetto.trace.power import power_rails_pb2 as protos_dot_perfetto_dot_trace_dot_power_dot_power__rails__pb2
from protos.perfetto.trace.statsd import statsd_atom_pb2 as protos_dot_perfetto_dot_trace_dot_statsd_dot_statsd__atom__pb2
from protos.perfetto.trace.profiling import deobfuscation_pb2 as protos_dot_perfetto_dot_trace_dot_profiling_dot_deobfuscation__pb2
from protos.perfetto.trace.profiling import heap_graph_pb2 as protos_dot_perfetto_dot_trace_dot_profiling_dot_heap__graph__pb2
try:
  protos_dot_perfetto_dot_trace_dot_profiling_dot_deobfuscation__pb2 = protos_dot_perfetto_dot_trace_dot_profiling_dot_heap__graph__pb2.protos_dot_perfetto_dot_trace_dot_profiling_dot_deobfuscation__pb2
except AttributeError:
  protos_dot_perfetto_dot_trace_dot_profiling_dot_deobfuscation__pb2 = protos_dot_perfetto_dot_trace_dot_profiling_dot_heap__graph__pb2.protos.perfetto.trace.profiling.deobfuscation_pb2
from protos.perfetto.trace.profiling import profile_common_pb2 as protos_dot_perfetto_dot_trace_dot_profiling_dot_profile__common__pb2
from protos.perfetto.trace.profiling import profile_packet_pb2 as protos_dot_perfetto_dot_trace_dot_profiling_dot_profile__packet__pb2
from protos.perfetto.trace.profiling import smaps_pb2 as protos_dot_perfetto_dot_trace_dot_profiling_dot_smaps__pb2
from protos.perfetto.trace.ps import process_stats_pb2 as protos_dot_perfetto_dot_trace_dot_ps_dot_process__stats__pb2
from protos.perfetto.trace.ps import process_tree_pb2 as protos_dot_perfetto_dot_trace_dot_ps_dot_process__tree__pb2
from protos.perfetto.trace import remote_clock_sync_pb2 as protos_dot_perfetto_dot_trace_dot_remote__clock__sync__pb2
from protos.perfetto.trace.sys_stats import sys_stats_pb2 as protos_dot_perfetto_dot_trace_dot_sys__stats_dot_sys__stats__pb2
from protos.perfetto.trace import system_info_pb2 as protos_dot_perfetto_dot_trace_dot_system__info__pb2
from protos.perfetto.trace.system_info import cpu_info_pb2 as protos_dot_perfetto_dot_trace_dot_system__info_dot_cpu__info__pb2
from protos.perfetto.trace import trace_packet_defaults_pb2 as protos_dot_perfetto_dot_trace_dot_trace__packet__defaults__pb2
from protos.perfetto.trace.track_event import process_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_process__descriptor__pb2
from protos.perfetto.trace.track_event import range_of_interest_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_range__of__interest__pb2
from protos.perfetto.trace.track_event import thread_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_thread__descriptor__pb2
from protos.perfetto.trace.track_event import track_descriptor_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_track__descriptor__pb2
from protos.perfetto.trace.track_event import track_event_pb2 as protos_dot_perfetto_dot_trace_dot_track__event_dot_track__event__pb2
from protos.perfetto.trace.translation import translation_table_pb2 as protos_dot_perfetto_dot_trace_dot_translation_dot_translation__table__pb2
from protos.perfetto.trace import trace_uuid_pb2 as protos_dot_perfetto_dot_trace_dot_trace__uuid__pb2
from protos.perfetto.trace import trigger_pb2 as protos_dot_perfetto_dot_trace_dot_trigger__pb2
from protos.perfetto.trace import test_event_pb2 as protos_dot_perfetto_dot_trace_dot_test__event__pb2
from protos.perfetto.trace import ui_state_pb2 as protos_dot_perfetto_dot_trace_dot_ui__state__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n(protos/perfetto/trace/trace_packet.proto\x12\x0fperfetto.protos\x1a(protos/perfetto/common/trace_stats.proto\x1a)protos/perfetto/config/trace_config.proto\x1a\x30protos/perfetto/trace/extension_descriptor.proto\x1a\x42protos/perfetto/trace/android/android_game_intervention_list.proto\x1a/protos/perfetto/trace/android/android_log.proto\x1a;protos/perfetto/trace/android/android_system_property.proto\x1a\x30protos/perfetto/trace/android/camera_event.proto\x1a\x38protos/perfetto/trace/android/frame_timeline_event.proto\x1a\x31protos/perfetto/trace/android/gpu_mem_event.proto\x1a\x38protos/perfetto/trace/android/graphics_frame_event.proto\x1a\x39protos/perfetto/trace/android/initial_display_state.proto\x1a\x31protos/perfetto/trace/android/network_trace.proto\x1a\x31protos/perfetto/trace/android/packages_list.proto\x1a\x36protos/perfetto/trace/android/pixel_modem_events.proto\x1a,protos/perfetto/trace/android/protolog.proto\x1a\x34protos/perfetto/trace/android/shell_transition.proto\x1a\x39protos/perfetto/trace/android/surfaceflinger_layers.proto\x1a?protos/perfetto/trace/android/surfaceflinger_transactions.proto\x1a\x37protos/perfetto/trace/android/winscope_extensions.proto\x1a<protos/perfetto/trace/chrome/chrome_benchmark_metadata.proto\x1a\x32protos/perfetto/trace/chrome/chrome_metadata.proto\x1a\x35protos/perfetto/trace/chrome/chrome_trace_event.proto\x1a\x31protos/perfetto/trace/chrome/chrome_trigger.proto\x1a%protos/perfetto/trace/chrome/v8.proto\x1a*protos/perfetto/trace/clock_snapshot.proto\x1a\x30protos/perfetto/trace/etw/etw_event_bundle.proto\x1a\x35protos/perfetto/trace/filesystem/inode_file_map.proto\x1a\x36protos/perfetto/trace/ftrace/ftrace_event_bundle.proto\x1a/protos/perfetto/trace/ftrace/ftrace_stats.proto\x1a\x31protos/perfetto/trace/gpu/gpu_counter_event.proto\x1a\'protos/perfetto/trace/gpu/gpu_log.proto\x1a\x36protos/perfetto/trace/gpu/gpu_render_stage_event.proto\x1a\x33protos/perfetto/trace/gpu/vulkan_memory_event.proto\x1a\x30protos/perfetto/trace/gpu/vulkan_api_event.proto\x1a\x37protos/perfetto/trace/interned_data/interned_data.proto\x1a(protos/perfetto/trace/memory_graph.proto\x1a\x37protos/perfetto/trace/perfetto/perfetto_metatrace.proto\x1a:protos/perfetto/trace/perfetto/tracing_service_event.proto\x1a\x45protos/perfetto/trace/power/android_energy_estimation_breakdown.proto\x1a@protos/perfetto/trace/power/android_entity_state_residency.proto\x1a\x32protos/perfetto/trace/power/battery_counters.proto\x1a-protos/perfetto/trace/power/power_rails.proto\x1a.protos/perfetto/trace/statsd/statsd_atom.proto\x1a\x33protos/perfetto/trace/profiling/deobfuscation.proto\x1a\x30protos/perfetto/trace/profiling/heap_graph.proto\x1a\x34protos/perfetto/trace/profiling/profile_common.proto\x1a\x34protos/perfetto/trace/profiling/profile_packet.proto\x1a+protos/perfetto/trace/profiling/smaps.proto\x1a,protos/perfetto/trace/ps/process_stats.proto\x1a+protos/perfetto/trace/ps/process_tree.proto\x1a-protos/perfetto/trace/remote_clock_sync.proto\x1a/protos/perfetto/trace/sys_stats/sys_stats.proto\x1a\'protos/perfetto/trace/system_info.proto\x1a\x30protos/perfetto/trace/system_info/cpu_info.proto\x1a\x31protos/perfetto/trace/trace_packet_defaults.proto\x1a:protos/perfetto/trace/track_event/process_descriptor.proto\x1a\x39protos/perfetto/trace/track_event/range_of_interest.proto\x1a\x39protos/perfetto/trace/track_event/thread_descriptor.proto\x1a\x38protos/perfetto/trace/track_event/track_descriptor.proto\x1a\x33protos/perfetto/trace/track_event/track_event.proto\x1a\x39protos/perfetto/trace/translation/translation_table.proto\x1a&protos/perfetto/trace/trace_uuid.proto\x1a#protos/perfetto/trace/trigger.proto\x1a&protos/perfetto/trace/test_event.proto\x1a$protos/perfetto/trace/ui_state.proto\"\x90+\n\x0bTracePacket\x12\x11\n\ttimestamp\x18\x08 \x01(\x04\x12\x1a\n\x12timestamp_clock_id\x18: \x01(\r\x12\x34\n\x0cprocess_tree\x18\x02 \x01(\x0b\x32\x1c.perfetto.protos.ProcessTreeH\x00\x12\x36\n\rprocess_stats\x18\t \x01(\x0b\x32\x1d.perfetto.protos.ProcessStatsH\x00\x12\x37\n\x0einode_file_map\x18\x04 \x01(\x0b\x32\x1d.perfetto.protos.InodeFileMapH\x00\x12;\n\rchrome_events\x18\x05 \x01(\x0b\x32\".perfetto.protos.ChromeEventBundleH\x00\x12\x38\n\x0e\x63lock_snapshot\x18\x06 \x01(\x0b\x32\x1e.perfetto.protos.ClockSnapshotH\x00\x12.\n\tsys_stats\x18\x07 \x01(\x0b\x32\x19.perfetto.protos.SysStatsH\x00\x12\x32\n\x0btrack_event\x18\x0b \x01(\x0b\x32\x1b.perfetto.protos.TrackEventH\x00\x12\x30\n\ntrace_uuid\x18Y \x01(\x0b\x32\x1a.perfetto.protos.TraceUuidH\x00\x12\x34\n\x0ctrace_config\x18! \x01(\x0b\x32\x1c.perfetto.protos.TraceConfigH\x00\x12\x34\n\x0c\x66trace_stats\x18\" \x01(\x0b\x32\x1c.perfetto.protos.FtraceStatsH\x00\x12\x32\n\x0btrace_stats\x18# \x01(\x0b\x32\x1b.perfetto.protos.TraceStatsH\x00\x12\x38\n\x0eprofile_packet\x18% \x01(\x0b\x32\x1e.perfetto.protos.ProfilePacketH\x00\x12\x44\n\x14streaming_allocation\x18J \x01(\x0b\x32$.perfetto.protos.StreamingAllocationH\x00\x12\x38\n\x0estreaming_free\x18K \x01(\x0b\x32\x1e.perfetto.protos.StreamingFreeH\x00\x12\x33\n\x07\x62\x61ttery\x18& \x01(\x0b\x32 .perfetto.protos.BatteryCountersH\x00\x12\x32\n\x0bpower_rails\x18( \x01(\x0b\x32\x1b.perfetto.protos.PowerRailsH\x00\x12\x38\n\x0b\x61ndroid_log\x18\' \x01(\x0b\x32!.perfetto.protos.AndroidLogPacketH\x00\x12\x32\n\x0bsystem_info\x18- \x01(\x0b\x32\x1b.perfetto.protos.SystemInfoH\x00\x12+\n\x07trigger\x18. \x01(\x0b\x32\x18.perfetto.protos.TriggerH\x00\x12\x38\n\x0e\x63hrome_trigger\x18m \x01(\x0b\x32\x1e.perfetto.protos.ChromeTriggerH\x00\x12\x36\n\rpackages_list\x18/ \x01(\x0b\x32\x1d.perfetto.protos.PackagesListH\x00\x12M\n\x19\x63hrome_benchmark_metadata\x18\x30 \x01(\x0b\x32(.perfetto.protos.ChromeBenchmarkMetadataH\x00\x12@\n\x12perfetto_metatrace\x18\x31 \x01(\x0b\x32\".perfetto.protos.PerfettoMetatraceH\x00\x12@\n\x0f\x63hrome_metadata\x18\x33 \x01(\x0b\x32%.perfetto.protos.ChromeMetadataPacketH\x00\x12=\n\x11gpu_counter_event\x18\x34 \x01(\x0b\x32 .perfetto.protos.GpuCounterEventH\x00\x12\x46\n\x16gpu_render_stage_event\x18\x35 \x01(\x0b\x32$.perfetto.protos.GpuRenderStageEventH\x00\x12K\n\x18streaming_profile_packet\x18\x36 \x01(\x0b\x32\'.perfetto.protos.StreamingProfilePacketH\x00\x12\x30\n\nheap_graph\x18\x38 \x01(\x0b\x32\x1a.perfetto.protos.HeapGraphH\x00\x12\x43\n\x14graphics_frame_event\x18\x39 \x01(\x0b\x32#.perfetto.protos.GraphicsFrameEventH\x00\x12\x41\n\x13vulkan_memory_event\x18> \x01(\x0b\x32\".perfetto.protos.VulkanMemoryEventH\x00\x12*\n\x07gpu_log\x18? \x01(\x0b\x32\x17.perfetto.protos.GpuLogH\x00\x12;\n\x10vulkan_api_event\x18\x41 \x01(\x0b\x32\x1f.perfetto.protos.VulkanApiEventH\x00\x12\x32\n\x0bperf_sample\x18\x42 \x01(\x0b\x32\x1b.perfetto.protos.PerfSampleH\x00\x12,\n\x08\x63pu_info\x18\x43 \x01(\x0b\x32\x18.perfetto.protos.CpuInfoH\x00\x12\x34\n\x0csmaps_packet\x18\x44 \x01(\x0b\x32\x1c.perfetto.protos.SmapsPacketH\x00\x12=\n\rservice_event\x18\x45 \x01(\x0b\x32$.perfetto.protos.TracingServiceEventH\x00\x12\x45\n\x15initial_display_state\x18\x46 \x01(\x0b\x32$.perfetto.protos.InitialDisplayStateH\x00\x12@\n\x13gpu_mem_total_event\x18G \x01(\x0b\x32!.perfetto.protos.GpuMemTotalEventH\x00\x12I\n\x17memory_tracker_snapshot\x18I \x01(\x0b\x32&.perfetto.protos.MemoryTrackerSnapshotH\x00\x12\x43\n\x14\x66rame_timeline_event\x18L \x01(\x0b\x32#.perfetto.protos.FrameTimelineEventH\x00\x12`\n#android_energy_estimation_breakdown\x18M \x01(\x0b\x32\x31.perfetto.protos.AndroidEnergyEstimationBreakdownH\x00\x12,\n\x08ui_state\x18N \x01(\x0b\x32\x18.perfetto.protos.UiStateH\x00\x12N\n\x1a\x61ndroid_camera_frame_event\x18P \x01(\x0b\x32(.perfetto.protos.AndroidCameraFrameEventH\x00\x12R\n\x1c\x61ndroid_camera_session_stats\x18Q \x01(\x0b\x32*.perfetto.protos.AndroidCameraSessionStatsH\x00\x12>\n\x11translation_table\x18R \x01(\x0b\x32!.perfetto.protos.TranslationTableH\x00\x12V\n\x1e\x61ndroid_game_intervention_list\x18S \x01(\x0b\x32,.perfetto.protos.AndroidGameInterventionListH\x00\x12\x32\n\x0bstatsd_atom\x18T \x01(\x0b\x32\x1b.perfetto.protos.StatsdAtomH\x00\x12I\n\x17\x61ndroid_system_property\x18V \x01(\x0b\x32&.perfetto.protos.AndroidSystemPropertyH\x00\x12G\n\x16\x65ntity_state_residency\x18[ \x01(\x0b\x32%.perfetto.protos.EntityStateResidencyH\x00\x12G\n\x16profiled_frame_symbols\x18\x37 \x01(\x0b\x32%.perfetto.protos.ProfiledFrameSymbolsH\x00\x12\x38\n\x0emodule_symbols\x18= \x01(\x0b\x32\x1e.perfetto.protos.ModuleSymbolsH\x00\x12\x46\n\x15\x64\x65obfuscation_mapping\x18@ \x01(\x0b\x32%.perfetto.protos.DeobfuscationMappingH\x00\x12<\n\x10track_descriptor\x18< \x01(\x0b\x32 .perfetto.protos.TrackDescriptorH\x00\x12@\n\x12process_descriptor\x18+ \x01(\x0b\x32\".perfetto.protos.ProcessDescriptorH\x00\x12>\n\x11thread_descriptor\x18, \x01(\x0b\x32!.perfetto.protos.ThreadDescriptorH\x00\x12;\n\rftrace_events\x18\x01 \x01(\x0b\x32\".perfetto.protos.FtraceEventBundleH\x00\x12 \n\x16synchronization_marker\x18$ \x01(\x0cH\x00\x12\x1c\n\x12\x63ompressed_packets\x18\x32 \x01(\x0cH\x00\x12\x44\n\x14\x65xtension_descriptor\x18H \x01(\x0b\x32$.perfetto.protos.ExtensionDescriptorH\x00\x12=\n\x0enetwork_packet\x18X \x01(\x0b\x32#.perfetto.protos.NetworkPacketEventH\x00\x12\x45\n\x15network_packet_bundle\x18\\ \x01(\x0b\x32$.perfetto.protos.NetworkPacketBundleH\x00\x12S\n\x1dtrack_event_range_of_interest\x18Z \x01(\x0b\x32*.perfetto.protos.TrackEventRangeOfInterestH\x00\x12N\n\x1esurfaceflinger_layers_snapshot\x18] \x01(\x0b\x32$.perfetto.protos.LayersSnapshotProtoH\x00\x12M\n\x1bsurfaceflinger_transactions\x18^ \x01(\x0b\x32&.perfetto.protos.TransactionTraceEntryH\x00\x12<\n\x10shell_transition\x18` \x01(\x0b\x32 .perfetto.protos.ShellTransitionH\x00\x12G\n\x16shell_handler_mappings\x18\x61 \x01(\x0b\x32%.perfetto.protos.ShellHandlerMappingsH\x00\x12<\n\x10protolog_message\x18h \x01(\x0b\x32 .perfetto.protos.ProtoLogMessageH\x00\x12G\n\x16protolog_viewer_config\x18i \x01(\x0b\x32%.perfetto.protos.ProtoLogViewerConfigH\x00\x12\x42\n\x13winscope_extensions\x18p \x01(\x0b\x32#.perfetto.protos.WinscopeExtensionsH\x00\x12:\n\netw_events\x18_ \x01(\x0b\x32$.perfetto.protos.EtwTraceEventBundleH\x00\x12/\n\nv8_js_code\x18\x63 \x01(\x0b\x32\x19.perfetto.protos.V8JsCodeH\x00\x12;\n\x10v8_internal_code\x18\x64 \x01(\x0b\x32\x1f.perfetto.protos.V8InternalCodeH\x00\x12\x33\n\x0cv8_wasm_code\x18\x65 \x01(\x0b\x32\x1b.perfetto.protos.V8WasmCodeH\x00\x12\x38\n\x0fv8_reg_exp_code\x18\x66 \x01(\x0b\x32\x1d.perfetto.protos.V8RegExpCodeH\x00\x12\x33\n\x0cv8_code_move\x18g \x01(\x0b\x32\x1b.perfetto.protos.V8CodeMoveH\x00\x12=\n\x11remote_clock_sync\x18k \x01(\x0b\x32 .perfetto.protos.RemoteClockSyncH\x00\x12?\n\x12pixel_modem_events\x18n \x01(\x0b\x32!.perfetto.protos.PixelModemEventsH\x00\x12N\n\x1apixel_modem_token_database\x18o \x01(\x0b\x32(.perfetto.protos.PixelModemTokenDatabaseH\x00\x12\x32\n\x0b\x66or_testing\x18\x84\x07 \x01(\x0b\x32\x1a.perfetto.protos.TestEventH\x00\x12\x15\n\x0btrusted_uid\x18\x03 \x01(\x05H\x01\x12$\n\x1atrusted_packet_sequence_id\x18\n \x01(\rH\x02\x12\x13\n\x0btrusted_pid\x18O \x01(\x05\x12\x34\n\rinterned_data\x18\x0c \x01(\x0b\x32\x1d.perfetto.protos.InternedData\x12\x16\n\x0esequence_flags\x18\r \x01(\r\x12!\n\x19incremental_state_cleared\x18) \x01(\x08\x12\x43\n\x15trace_packet_defaults\x18; \x01(\x0b\x32$.perfetto.protos.TracePacketDefaults\x12\x1f\n\x17previous_packet_dropped\x18* \x01(\x08\x12 \n\x18\x66irst_packet_on_sequence\x18W \x01(\x08\x12\x12\n\nmachine_id\x18\x62 \x01(\r\"h\n\rSequenceFlags\x12\x13\n\x0fSEQ_UNSPECIFIED\x10\x00\x12!\n\x1dSEQ_INCREMENTAL_STATE_CLEARED\x10\x01\x12\x1f\n\x1bSEQ_NEEDS_INCREMENTAL_STATE\x10\x02\x42\x06\n\x04\x64\x61taB\x16\n\x14optional_trusted_uidB%\n#optional_trusted_packet_sequence_idJ\x04\x08j\x10k')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'protos.perfetto.trace.trace_packet_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_TRACEPACKET']._serialized_start=3442
  _globals['_TRACEPACKET']._serialized_end=8962
  _globals['_TRACEPACKET_SEQUENCEFLAGS']._serialized_start=8781
  _globals['_TRACEPACKET_SEQUENCEFLAGS']._serialized_end=8885
# @@protoc_insertion_point(module_scope)
