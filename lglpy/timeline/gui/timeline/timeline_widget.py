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

from lglpy.timeline.drawable.world_drawable import WorldDrawableLabel
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
            menui.connect_object('activate', self.on_orc2, clicked)
            menu.append(menui)

            menui = Gtk.MenuItem('Highlight by FBO ID')
            menui.connect_object('activate', self.on_orc3, clicked)
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

            bookmarks = {}
            for time, name in self.bookmarks.items():
                # Keep bookmarks in active clamp range only
                if self.ws_clamp_min_x < time < self.ws_clamp_max_x:
                    bookmarks[time] = name

            if bookmarks:
                menui = Gtk.MenuItem('Jump to Bookmark')
                menu.append(menui)

                submenu = Gtk.Menu()
                menui.set_submenu(submenu)

                handler = self.on_jump_bookmark
                for bookmark in sorted(bookmarks.keys()):
                    key = bookmarks[bookmark]
                    menui = Gtk.MenuItem(key)
                    menui.connect_object('activate', handler, key)
                    submenu.append(menui)

            menu.show_all()
            menu.popup_at_pointer(event)

            return True

        # Is using control then show the grouping save/restore menu
        if mod == 'c':
            menu = Gtk.Menu()

            menui = Gtk.MenuItem('Save active objects')
            menui.connect_object('activate', self.on_norc5, clicked)
            menu.append(menui)

            if None is not self.active_objects_stash:
                menui = Gtk.MenuItem('Restore active objects')
                menui.connect_object('activate', self.on_norc6, clicked)
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

    def on_orc2(self, clicked_object):
        '''
        Right click menu handler -> highlight by EGL frame
        '''
        self.clear_active_objects()

        cf = lambda x: x.name in ['hw.js0', 'hw.js1']
        ef = lambda x: x.user_data

        # Check the incoming object is a frame object
        if not ef(clicked_object):
            return

        renderpasses = []
        drawables = []
        for drawable in self.drawable_trace.each_object(cf, ef):
            if drawable.user_data.frameId == clicked_object.user_data.frameId:
                if drawable.user_data not in renderpasses:
                    renderpasses.append(drawable.user_data)
                drawables.append(drawable)

        self.add_multiple_to_active_objects(drawables)
        self.parent.queue_draw()

    def on_orc3(self, clicked_object):
        '''
        Right click menu handler -> highlight by FBO ID
        '''
        user_data = clicked_object.user_data
        if not user_data:
            return

        # TODO: Fix this once real data exists
        is_fbo = isinstance(user_data, TimelineFBO)
        if not is_fbo:
            return

        def ch_filter(channel):
            return channel.name in ['hw.js0', 'hw.js1']

        self.clear_active_objects()

        rps = set()
        drawables = []

        for drawable in self.drawable_trace.each_object(ch_filter=ch_filter):
            search_user_data = drawable.user_data
            if (not search_user_data) or \
               (not isinstance(search_user_data, TimelineFBO)):
                continue

            if (search_user_data.fboId == user_data.fboId) and \
               (search_user_data not in rps):
                rps.add(drawable.user_data)
                drawables.append(drawable)

        self.add_multiple_to_active_objects(drawables)
        self.parent.queue_draw()

    def on_norc1(self, clicked_object):
        '''
        Right click menu handler -> clear range
        '''
        self.active_time_range = []
        self.parent.queue_draw()

    def on_norc2(self, clicked_object):
        '''
        Right click menu handler -> clear selection
        '''
        self.clear_active_objects()
        self.parent.queue_draw()

    def on_norc3(self, clicked_object):
        '''
        Right click menu handler -> clear clamp limits
        '''
        self.ws_clamp_min_x = self.original_trace_ws_min_x - 100
        self.trace_ws_min_x = self.ws_clamp_min_x
        self.ws_clamp_max_x = self.original_trace_ws_max_x + 100
        self.trace_ws_max_x = self.ws_clamp_max_x
        self.parent.queue_draw()

    def on_norc5(self, clicked_object):
        '''
        Right click menu handler -> save active objects
        '''
        self.active_objects_stash = self.active_objects.copy()

    def on_norc6(self, clicked_object):
        '''
        Right click menu handler -> restore active objects
        '''
        self.clear_active_objects()
        for drawable in self.active_objects_stash:
            self.add_to_active_objects(drawable)
        self.active_objects_stash = None
        self.parent.queue_draw()

    def on_jump_bookmark(self, name):
        '''
        Right click menu handler -> jump to bookmark
        '''
        for ws_target_x, value in self.bookmarks.items():
            if value == name:
                break
        else:
            return

        clamp_min_x = self.ws_clamp_min_x
        clamp_max_x = self.ws_clamp_max_x
        if not clamp_min_x <= ws_target_x <= clamp_max_x:
            print(f'WARNING: Bookmark {name} outside of clamped range')
            return

        # Put the bookmark in the middle of the screen, but handle clamps
        # gracefully, which may pull it off center
        ws_start_x = max(ws_target_x - (self.vp.ws.w / 2), clamp_min_x)
        ws_end_x = min(ws_target_x + (self.vp.ws.w / 2), clamp_max_x)

        # Finally we can update the viewport and render
        ws = self.vp.ws
        ws_pos_new = [ws_start_x, ws.min_y]
        ws_dim_new = [ws_end_x - ws_start_x, ws.max_y - ws.min_y]
        self.vp.update_ws(ws_pos_new, ws_dim_new)

        self.parent.queue_draw()

    def jump_one_frame(self, forward):
        '''
        Handle jump one frame forward or backwards.
        '''
        # Find the scene object in the config
        def ch_filter(channel):
            return channel.name in ['sw.frame']

        def obj_filter(event):
            return isinstance(event, WorldDrawableLine)

        # Find the frame either side of the first eglSwap in the viewport
        prev = None
        start = None
        end = None

        ws = self.vp.ws
        for drawable in self.drawable_trace.each_object(ch_filter, obj_filter):
            if drawable.ws.min_x >= ws.min_x:
                if not start:
                    start = drawable.ws.min_x
                else:
                    end = drawable.ws.min_x
                    break
            else:
                prev = drawable.ws.min_x

        if None is end:
            print('Warning: Unable to determine frame time')
            return

        # Use gap between N and N+1 when moving forwards
        if forward:
            ws_pos_new = [ws.min_x + end - start, ws.min_y]
        # Use gap between N-1 and N when moving backwards (if there is a
        # backwards). This ensures that toggling left and right is stable
        # without jitter
        elif prev:
            ws_pos_new = [ws.min_x - start + prev, ws.min_y]
        # Otherwise nothing to do, so return
        else:
            return

        # Clamp the start against the clamp ranges
        ws_pos_new = [max(self.ws_clamp_min_x, ws_pos_new[0]), ws_pos_new[1]]
        max_w = self.ws_clamp_max_x - ws_pos_new[0] - 5

        width = min(ws.max_x - ws.min_x, max_w)
        ws_dim_new = [width, ws.max_y - ws.min_y]

        self.vp.update_ws(ws_pos_new, ws_dim_new)
        self.parent.queue_draw()
