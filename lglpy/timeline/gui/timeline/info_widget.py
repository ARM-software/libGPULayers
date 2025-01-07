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
        self.sort_type = self. VALIDSORTS[0]

    def get_frame_rate(self, start, end):
        '''
        Compute the frame rate for frames in the selected time range.

        Args:
            start: start of time range.
            end: end of time range.

        Returns:
            Compute frame rate or None if could not be determined.
        '''
        tl = self.timeline_widget
        try:
            channel = tl.drawable_trace.get_channel('sw.frame')
        except KeyError:
            return None

        frame_count = 0
        first_frame = None
        last_frame = None

        event_filter = lambda x: isinstance(x, WorldDrawableLine)
        for drawable in channel.each_object(event_filter):
            frame_time = drawable.ws.min_x
            if start <= frame_time < end:
                frame_count += 1
                if not first_frame:
                    first_frame = frame_time
                last_frame = frame_time

        # We need at least two frame markers to bracket an FPS metric
        if frame_count < 2:
            return None

        frame_count = float(frame_count - 1)
        duration = float(last_frame - first_frame) / 1000000000.0
        msf = (duration * 1000.0) / frame_count
        fps = frame_count / duration

        lines = [
            f'  Frames: {frame_count}'
            f'  Performance: {msf:0.2f} ms/F ({fps:0.2f} FPS)'
        ]

        return lines

    def get_gpu_utilization(self, start, end, slot=('Non-fragment', 'Fragment', 'Transfer')):
        '''
        Compute the hardware utilization over the active time range.

        Args:
            start: start of time range.
            end: end of time range.
            slot: the hardware queues to include (default all of them).

        Returns:
            Compute frame rate or None if could not be determined.
        '''
        usage = 0
        range_end = 0

        filt = lambda x: x.name in slot
        trace = self.timeline_widget.drawable_trace
        trace = [(x.ws.min_x, x.ws.max_x) for x in trace.each_object(filt)]
        trace.sort()

        for min_x, max_x in trace:
            # Skip drawables which are out of the range
            if max_x < start:
                continue

            if min_x > end:
                break

            # Clamp to the start range
            min_x = max(start, min_x)
            max_x = min(end, max_x)

            # Cut off the parts which we have already counted
            if range_end:
                min_x = max(range_end, min_x)
                max_x = max(range_end, max_x)

            # Now just store the new data ...
            usage += max_x - min_x
            range_end = max(range_end, max_x)

        util = (float(usage) / float(end - start)) * 100.0
        return f'{util:0.1f}%'

    def get_active_region_stats(self):
        '''
        Compute all metrics for the active time range.

        Returns:
            List of lines to be printed.
        '''
        active = self.timeline_widget.get_active_time_range(True)
        if not active:
            return ['Active Region: -', '']

        duration = active[1] - active[0]
        if duration < 0:
            return ['Active Region: -', '']

        # Convert to milliseconds
        duration = float(duration) / 1000000.0
        start = float(active[0]) / 1000000.0

        lines = [
            'Active Region:',
            f'  Start = {start:0.3f} ms'
            f'  Duration = {duration:0.3f} ms'
        ]

        fps = self.get_frame_rate(*active)
        if fps:
            lines.extend(fps)

        util = [
            '',
            'Utilization:',
            f'  Non-fragment: {self.get_gpu_utilization(*active, slot=("Non-fragment",))}',
            f'  Fragment: {self.get_gpu_utilization(*active, slot=("Fragment",))}',
            f'  Transfer: {self.get_gpu_utilization(*active, slot=("Transfer",))}',
            f'  GPU: {self.get_gpu_utilization(*active)}',
            ''
        ]

        lines.extend(util)
        return lines

    def draw(self, gc):
        '''
        Draw this widget.

        Args:
            gc: Cairo graphics context.
        '''
        lines = []

        # Top line: Active region size (optional)
        message = self.get_active_region_stats()
        lines.extend(message)

        active_objects = self.timeline_widget.get_active_objects(True)
        # If we have one object just print it out
        if 1 == len(active_objects):
            lines.extend(active_objects[0].getDescription())

        self.set_text('\n'.join(lines))
        super().draw(gc)
