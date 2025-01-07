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
TODO
'''

import gi
gi.require_version('Gtk', '3.0')
# pylint: disable=wrong-import-position
from gi.repository import Gtk

from lglpy.timeline.drawable.world_drawable import WorldDrawableLine
from lglpy.timeline.drawable.timeline_base import TimelineWidgetBase


class TimelineWidget(TimelineWidgetBase):
    '''
    TODO: Write documentation ...
    '''

    def __init__(self, parent, trace, css):
        '''
        TODO: Write documentation ...
        '''
        pos = (0, 0)
        dim = (1, 1)
        prefix = 'tlv-tlw-'
        super().__init__(trace, pos, dim, css, prefix)

        self.parent = parent

    def on_mouse_single_click(self, button, x, y, mod):
        '''
        Handle a click event.

        We follow the same convention as the `View` module API, so see that
        class for documentation.
        '''
        parent = super()
        if parent.on_mouse_single_click(button, x, y, mod):
            return True

        # The only extra options are right menu click options
        if button == 'left':
            return False

        # Try to find a clicked object, if there is one
        vp = self.vp
        ws_x, ws_y = vp.transform_cs_to_ws(x, y)

        clicked = self.drawable_trace.get_clicked_object(ws_x, ws_y)

        # Fetch the raw GTK event
        event = self.parent.get_raw_mouse_event()

        # If we are clicking on an object show the click menu
        if clicked:
            menu = Gtk.Menu()

            menui = Gtk.MenuItem('Highlight by Render Pass')
            menui.connect_object('activate', self.on_orc1, clicked)
            menu.append(menui)

            menui = Gtk.MenuItem('Highlight by Frame')
            # TODO: Implement this
            menu.append(menui)

            menu.show_all()
            menu.popup_at_pointer(event)

            return True

        # If we are not clicking on an object show the other click menu
        if mod == '':
            menu = Gtk.Menu()

            menui = Gtk.MenuItem('Clear Selected Time Range')
            menui.connect_object('activate', self.on_norc1, clicked)
            menu.append(menui)

            menui = Gtk.MenuItem('Clear Selected Objects')
            menui.connect_object('activate', self.on_norc2, clicked)
            menu.append(menui)

            menui = Gtk.MenuItem('Clear Timeline Clamps')
            menui.connect_object('activate', self.on_norc3, clicked)
            menu.append(menui)

            menu.show_all()
            menu.popup_at_pointer(event)

            return True

        return False

    def on_orc1(self, clicked_object):
        '''
        Right click menu handler -> highlight by single render pass
        '''
        self.clear_active_objects()
        self.add_to_active_objects(clicked_object)
        self.parent.queue_draw()

    def on_norc1(self, clicked_object):
        '''
        Right click menu handler -> clear range
        '''
        del clicked_object
        self.active_time_range = []
        self.parent.queue_draw()

    def on_norc2(self, clicked_object):
        '''
        Right click menu handler -> clear selection
        '''
        del clicked_object
        self.clear_active_objects()
        self.parent.queue_draw()

    def on_norc3(self, clicked_object):
        '''
        Right click menu handler -> clear clamp limits
        '''
        del clicked_object
        self.ws_clamp_min_x = self.original_trace_ws_min_x - 100
        self.trace_ws_min_x = self.ws_clamp_min_x
        self.ws_clamp_max_x = self.original_trace_ws_max_x + 100
        self.trace_ws_max_x = self.ws_clamp_max_x
        self.parent.queue_draw()
