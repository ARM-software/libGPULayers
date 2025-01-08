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

from lglpy.timeline.drawable.text_pane_widget import TextPaneWidget
from lglpy.timeline.drawable.world_drawable import WorldDrawableLine


class TimelineInfoWidget(TextPaneWidget):
    '''
    A widget which presents useful information about selected workloads or
    time ranges in the main timeline.
    '''

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
        in_frames = dict()

        for event in self.timeline_widget.drawable_trace.each_object():
            frame = event.user_data.frame

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
            return len(x)

        channels = [x.name for x in trace.each_channel(ch_filt)]
        label_len = max(len(x) for x in channels) + len(' stream:')

        metrics = ['']
        metrics.append('Utilization:')
        for channel in channels:
            util = self.get_utilization(start, end, [channel,])
            label = f'{channel} stream:'
            metrics.append(f'  {label:{label_len}} {util:>5.1f}%')

        util = self.get_utilization(start, end, channels)
        label = f'Any stream:'
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
            f'  Start:       {start:0.3f} s',
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


    def compute_active_event_stats_single(self, active):
        '''
        Get the metrics for the active time range.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Returns:
            List of lines to be printed.
        '''
        return ['One selected']


    def compute_active_event_stats_multi(self, active):
        '''
        Get the metrics for the active time range.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Returns:
            List of lines to be printed.
        '''
        active.sort(key=lambda x: x.start_time)

        lines = []
        for event in active:
            if event.label_stack:
                lines.append('|'.join(event.label_stack))
                print(lines[-1])
            else:
                lines.append('Unknown')

        return lines

    def get_active_event_stats(self):
        '''
        Get the metrics for the active time range.

        This function uses a cached lookup to avoid re-calculating every
        redraw, as the stats computation can be quite slow.

        Returns:
            List of lines to be printed.
        '''
        active = self.timeline_widget.get_active_objects(True)
        active.sort(key=lambda x: x.start_time)

        if self.cached_active_event == active:
            return self.cached_event_info

        elif len(active) == 0:
            info = None

        elif len(active) == 1:
            info = self.compute_active_event_stats_single(active)

        else:
            info = self.compute_active_event_stats_multi(active)
            import sys
            sys.exit(1)

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
