# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024-2025 Arm Limited
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the 'Software'), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------
'''
The `TimelineInfoWidget` class implements a specialized version of the
`TextPaneWidget`, used to render informative messages about the current
timeline visualization.
'''

from collections import defaultdict

from ...data.raw_trace import GPUStreamID, GPUStageID
from ...data.processed_trace import GPUWorkload, LABEL_MAX_LEN
from ...drawable.text_pane_widget import TextPaneWidget


class TimelineInfoWidget(TextPaneWidget):
    '''
    A widget which presents useful information about selected workloads or
    time ranges in the main timeline.
    '''

    FULL_LABEL = True
    MAX_EVENTS = 5
    VALIDSORTS = ['flush', 'runtime']

    def __init__(self, timeline_widget, style):
        '''
        Create a new timeline information widget.

        TODO: Add args.
        '''
        super().__init__((0, 0), (1, 1), style, '')
        self.timeline_widget = timeline_widget
        self.sort_type = self.VALIDSORTS[0]

        # Initialize the text report caches
        self.cached_active_range = None
        self.cached_range_info = self.compute_active_region_stats(None)

        self.cached_active_event = None
        self.cached_event_info = None

    def get_frame_rate_report(self, start, end):
        '''
        Compute the frame rate for frames in the selected time range.

        Args:
            start: start of time range.
            end: end of time range.

        Returns:
            Compute frame rate or None if could not be determined.
        '''
        # Determine which frames are entirely in the active range
        out_frames = set()
        in_frames = {}

        def ch_filter(x):
            return x.name != 'Submit'

        trace = self.timeline_widget.drawable_trace
        for event in trace.each_object(ch_filter):
            frame = event.user_data.get_frame()

            # Event is not entirely in active range
            # - Work starts and/or ends before time range
            #   End before implies start before, so don't need to check it
            # - Work starts and/or ends after time range
            #   Start after implies end after, so don't need to check it
            if event.ws.min_x < start or event.ws.max_x > end:
                out_frames.add(frame)
                continue

            # Event is entirely inside active time range
            if frame not in in_frames:
                in_frames[frame] = [event.ws.min_x, event.ws.max_x]
            else:
                in_frames[frame][0] = min(in_frames[frame][0], event.ws.min_x)
                in_frames[frame][1] = max(in_frames[frame][1], event.ws.max_x)

        # Remove partial frames from the in_frames data
        keys = list(in_frames.keys())
        for key in keys:
            if key in out_frames:
                del in_frames[key]

        # No frames found
        if not in_frames:
            return None

        # Determine active frame min/max times
        min_time = min(in_frames.values(), key=lambda x: x[0])[0]
        max_time = max(in_frames.values(), key=lambda x: x[1])[1]
        frame_count = len(in_frames)

        frame_countf = float(frame_count)
        seconds = float(max_time - min_time) / 1000000000.0
        msf = (seconds * 1000.0) / frame_countf
        fps = frame_countf / seconds

        lines = [
            f'  Frames:      {int(frame_count)}',
            f'  Performance: {msf:0.2f} ms/frame ({fps:0.2f} FPS)'
        ]

        return lines

    def get_utilization(self, start: int, end: int, slot: list[str]) -> float:
        '''
        Compute the hardware utilization over the active time range.

        For analysis using multiple slots, time is considered active if any
        slot is active.

        Args:
            start: start of time range.
            end: end of time range.
            slot: the hardware queues to analyze.

        Returns:
            The computed utilization percentage.
        '''
        usage = 0
        cursor = start

        def ch_filter(x):
            return x.name in slot

        trace = self.timeline_widget.drawable_trace
        trace = [(x.ws.min_x, x.ws.max_x)
                 for x in trace.each_object(ch_filter)]

        trace.sort()

        for min_x, max_x in trace:
            # Skip drawables which do not intersect range
            if (max_x < cursor) or (min_x > end):
                continue

            # Trim end to fit active range
            max_x = min(end, max_x)

            # Trim start to exclude range already counted for earlier events
            min_x = max(cursor, min_x)

            # Now just store the new data ...
            usage += max_x - min_x
            cursor = max_x

        util = (float(usage) / float(end - start)) * 100.0
        return util

    def get_utilization_report(self, start, end):
        '''
        Compute the hardware utilization over the active time range.

        Args:
            start: start of time range.
            end: end of time range.
            slot: the hardware queues to include (default all of them).

        Returns:
            Compute frame rate or None if could not be determined.
        '''
        trace = self.timeline_widget.drawable_trace

        def ch_filt(x):
            return len(x) and x.name != 'Submit'

        channels = [x.name for x in trace.each_channel(ch_filt)]
        label_len = max(len(x) for x in channels) + len(' stream:')

        metrics = ['']
        metrics.append('Utilization:')
        for channel in channels:
            util = self.get_utilization(start, end, [channel,])
            if util == 0.0:
                continue

            label = f'{channel} stream:'
            metrics.append(f'  {label:{label_len}} {util:>5.1f}%')

        util = self.get_utilization(start, end, channels)
        label = 'Any stream:'
        metrics.append(f'  {label:{label_len}} {util:>5.1f}%')
        metrics.append('')
        return metrics

    def compute_active_region_stats(self, active):
        '''
        Compute all metrics for the active time range.

        Returns:
            List of lines to be printed.
        '''
        if not active or (active[1] - active[0]) <= 0:
            return ['Active region: -', '']

        # Convert start to seconds and duration to milliseconds
        start = float(active[0]) / 1000000000.0
        duration = float(active[1] - active[0]) / 1000000.0

        lines = [
            'Active region:',
            f'  Duration:    {duration:0.3f} ms'
        ]

        if fps_report := self.get_frame_rate_report(*active):
            lines.extend(fps_report)

        if util_report := self.get_utilization_report(*active):
            lines.extend(util_report)

        return lines

    def get_active_region_stats(self):
        '''
        Get the metrics for the active time range.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Returns:
            List of lines to be printed.
        '''
        active = self.timeline_widget.get_active_time_range(True)

        if self.cached_active_range != active:
            self.cached_active_range = active
            self.cached_range_info = self.compute_active_region_stats(active)

        return self.cached_range_info

    def compute_active_event_stats_single(self, event):
        '''
        Get the metrics for the active event.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Args:
            event: The active event.

        Returns:
            List of lines to be printed.
        '''
        # Skip non-workload types
        if not isinstance(event, GPUWorkload):
            return []

        stream_name = GPUStreamID.get_ui_name(event.stream)
        stage_name = GPUStageID.get_ui_name(event.stage)

        metrics = []

        # Report total runtime of the selected workloads
        other_names = [
            'API workloads:',
            'Hardware workloads:'
        ]

        metrics.append('Active workload runtime:')
        label_len = len(stream_name) + len(' stream:')
        label_len = max(max(len(x) for x in other_names), label_len)

        label = other_names[0]
        metrics.append(f'  {label:{label_len}} {1:>5}')

        label = other_names[1]
        metrics.append(f'  {label:{label_len}} {1:>5}')

        label = f'{stream_name} stream:'
        duration = float(event.duration) / 1000000.0
        metrics.append(f'  {label:{label_len}} {duration:>5.2f} ms')

        # Report total N workloads
        metrics.append('')
        metrics.append('Workload properties:')

        if self.FULL_LABEL:
            label = event.get_workload_name_full()
        else:
            label = event.get_workload_name()

        # Chunk a long label into line-width sections
        chunk_size = LABEL_MAX_LEN + 3
        next_chunk_size = chunk_size + 4
        chunks = []
        while label:
            part = label[0: chunk_size]
            chunks.append(part)

            label = label[chunk_size:]
            chunk_size = next_chunk_size

        # Print a label in chunks
        metrics.append(f'  Name: {chunks[0]}')
        for part in chunks[1:]:
            metrics.append(f'    {part}')

        metrics.append(f'  Stream: {stream_name}')
        metrics.append(f'  Stage: {stage_name}')
        metrics.append(f'  Start: {event.start_time / 1000000.0:0.2f} ms')
        metrics.append(f'  Duration: {event.duration / 1000000.0:0.2f} ms')

        for key, value in event.get_key_value_properties().items():
            key = key.capitalize()
            metrics.append(f'  {key}: {value}')

        metrics.append('')
        return metrics

    def compute_active_event_stats_multi(self, active):
        '''
        Get the metrics for the active events.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Args:
            active: List of active events.

        Returns:
            List of lines to be printed.
        '''
        active.sort(key=lambda x: x.start_time)

        # Per-stream time for a given submitted workload
        tag_stream_time = {}
        # Per-tag event mapping (keeps an arbitrary one)
        tag_event = {}
        # Per-work time for a submitted workload
        total_tag_time = defaultdict(int)
        # Per-steam time for all workloads
        total_stream_time = defaultdict(int)

        max_name_len = 0

        for event in active:
            # Skip things that are not GPU workloads
            if not isinstance(event, GPUWorkload):
                continue

            total_stream_time[event.stream] += event.duration
            total_tag_time[event.tag_id] += event.duration

            name_len = len(GPUStreamID.get_ui_name(event.stream))
            max_name_len = max(max_name_len, name_len)

            if event.tag_id not in tag_stream_time:
                tag_stream_time[event.tag_id] = defaultdict(int)
                tag_event[event.tag_id] = event

            tag_stream_time[event.tag_id][event.stream] += event.duration

        metrics = []
        # Report total runtime of the selected workloads
        other_names = [
            'API workloads:',
            'Hardware workloads:'
        ]

        metrics.append('Active workload runtime:')

        label_len = max_name_len + len(' stream:')
        label_len = max(max(len(x) for x in other_names), label_len)

        label = other_names[0]
        value = len(tag_event)
        metrics.append(f'  {label:{label_len}} {value:>5}')

        label = other_names[1]
        value = len(active)
        metrics.append(f'  {label:{label_len}} {value:>5}')

        active_streams = sorted(total_stream_time.keys())
        for stream in active_streams:
            label = f'{GPUStreamID.get_ui_name(stream)} stream:'
            duration = float(total_stream_time[stream]) / 1000000.0
            metrics.append(f'  {label:{label_len}} {duration:>5.2f} ms')

        # Report total N workloads
        metrics.append('')
        top_n_limit = min(self.MAX_EVENTS, len(total_tag_time))
        if top_n_limit > 1:
            metrics.append(f'Top {top_n_limit} workload runtimes:')
        else:
            metrics.append('Workload runtime:')

        tags_by_cost = sorted(
            total_tag_time, key=total_tag_time.get, reverse=True)

        for n_count, tag_id in enumerate(tags_by_cost):
            if n_count >= top_n_limit:
                break

            event = tag_event[tag_id]
            costs = tag_stream_time[tag_id]

            # Report total N workloads
            label = event.get_workload_name()
            metrics.append(f'  {label}')

            active_streams = sorted(costs.keys())
            label_len = max_name_len + len(' stream:')
            for stream in active_streams:
                label = f'{GPUStreamID.get_ui_name(stream)} stream:'
                duration = float(costs[stream]) / 1000000.0
                metrics.append(f'    {label:{label_len}} {duration:>5.2f} ms')

        metrics.append('')
        return metrics

    def get_active_event_stats(self):
        '''
        Get the metrics for the active event selection.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Returns:
            List of lines to be printed.
        '''
        active = self.timeline_widget.get_active_objects(True)
        active.sort(key=lambda x: x.start_time)

        if self.cached_active_event == active:
            return self.cached_event_info

        if len(active) == 0:
            info = None

        elif len(active) == 1:
            info = self.compute_active_event_stats_single(active[0])

        else:
            info = self.compute_active_event_stats_multi(active)

        self.cached_event_info = info
        return self.cached_event_info

    def draw(self, gc):
        '''
        Draw this widget.

        Args:
            gc: Cairo graphics context.
        '''
        lines = []

        # Top line: Active region statistics
        message = self.get_active_region_stats()
        lines.extend(message)

        # Bottom line: Active object statistics
        if message := self.get_active_event_stats():
            lines.extend(message)

        self.set_text('\n'.join(lines))
        super().draw(gc)
