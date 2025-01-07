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

import os
import sys
import time

import gi
gi.require_version('Gtk', '3.0')

# pylint: disable=wrong-import-position
from gi.repository import Gtk, Gdk, GObject

from lglpy.timeline.data.raw_trace import RawTrace
from lglpy.timeline.data.processed_trace import GPUTrace

from lglpy.timeline.drawable.mouse_button import MouseButton
from lglpy.timeline.drawable.css import CSSStylesheet
from lglpy.timeline.drawable.timed_statusbar import TimedStatusbar
from lglpy.timeline.drawable.filechooser_dialog import get_open_filechoice

from lglpy.timeline.gui.default.view import DefaultView
from lglpy.timeline.gui.timeline.view import TimelineView


class Window:
    '''
    The Window is the main framework for the Mali trace viewer, providing the
    root GTK window, event, and input handling functionality. This class
    provides no visualization functionality itself; specific logic for
    visualizing data from a trace is delegated to a number of `View` instances
    which are each designed to provide a specific interpretation of the data.
    '''

    DEFAULT_APP_TITLE = 'Arm GPU Trace Viewer'
    DEFAULT_VIEW = 'Homescreen'

    RAW_MOUSE_EVENT = None

    @classmethod
    def get_raw_mouse_event(cls):
        '''
        Get the raw mouse event.

        TODO: This is a nasty hack relying on Python being single threaded, and
        this class being a singleton.
        '''
        return cls.RAW_MOUSE_EVENT

    @classmethod
    def set_raw_mouse_event(cls, event):
        '''
        Set the raw mouse event.

        TODO: This is a nasty hack relying on Python being single threaded, and
        this class being a singleton.
        '''
        cls.RAW_MOUSE_EVENT = event

    def queue_draw(self):
        '''
        Force a global redraw.

        TODO: Move, not a global.
        '''
        self.canvas.queue_draw()

    def __init__(self, style, trace_file=None, metadata_file=None):
        '''
        '''
        # Load the style config
        source_dir = os.path.dirname(__file__)
        css_path = os.path.join(source_dir, 'resources', f'{style}.css')
        self.stylesheet = CSSStylesheet(css_path)

        # Remember the file we have open
        self.loaded_file_path = None
        self.trace_data = None

        # Open a window ...
        self.window = Gtk.Window()
        self.window.set_title(self.DEFAULT_APP_TITLE)
        self.window.connect('destroy', Gtk.main_quit)
        self.window.set_size_request(1024, 500)
        self.window.set_default_size(1600, 500)

        # These get populated by the size callback
        self.width = None
        self.height = None

        self.canvas = Gtk.DrawingArea()
        self.canvas.show()

        # ---- ----- ----- ----- -----
        # Build the menu
        self.menubar = Gtk.MenuBar()
        self.menubar.show()

        # File menu: create the menu items
        file_menu_root = Gtk.MenuItem('File')
        file_menu_root.show()
        self.menubar.append(file_menu_root)

        file_menu = Gtk.Menu()
        file_menu_root.set_submenu(file_menu)

        file_menu_item = Gtk.MenuItem('Open file')
        file_menu.append(file_menu_item)
        file_menu_item.show()
        file_menu_item.connect_object('activate', self.on_menu_file_open, '')
        self.file_menu_open = file_menu_item

        file_menu_item = Gtk.MenuItem('Close file')
        file_menu.append(file_menu_item)
        file_menu_item.show()
        file_menu_item.connect_object('activate', self.on_menu_file_close, '')
        self.file_menu_close = file_menu_item

        file_menu_item = Gtk.MenuItem('Exit')
        file_menu.append(file_menu_item)
        file_menu_item.show()
        file_menu_item.connect_object('activate', self.on_menu_file_exit, '')

        self.menus_needing_file = [
            self.file_menu_close
        ]

        for menu in self.menus_needing_file:
            menu.set_sensitive(False)

        # Views menu: create the menu items
        # Load the view plugins
        views_list = [
            DefaultView,
            TimelineView
        ]

        self.loaded_views = {}

        views_menu = Gtk.Menu()

        views_menu_root = Gtk.MenuItem('Views')
        views_menu_root.set_submenu(views_menu)
        views_menu_root.show()
        self.menubar.append(views_menu_root)

        for views_class in views_list:
            name = views_class.MENU_NAME
            assert name not in self.loaded_views
            view = views_class(self, self.stylesheet)
            self.loaded_views[name] = view
            view_menu = view.get_view_menu_item()
            views_menu.append(view_menu)
            view_menu.connect_object('activate', self.on_menu_view, name)

        # Select the starting view based on default
        self.view = None
        self.on_menu_view(self.DEFAULT_VIEW)

        # ---- ----- ----- ----- -----
        self.status = TimedStatusbar()
        self.status.log('Welcome to Arm GPU Trace Viewer!', 5000)
        self.status.show()

        # ---- ----- ----- ----- -----
        # Build a vbox to contain the menu
        self.vbox = Gtk.VBox(False, 0)
        self.window.add(self.vbox)
        self.vbox.pack_start(self.menubar, False, False, 0)
        self.vbox.pack_start(self.canvas, True, True, 0)
        self.vbox.pack_start(self.status, False, False, 0)
        self.vbox.show()

        # ---- ----- ----- ----- -----
        # Connect signal handlers
        self.canvas.connect('size-allocate', self.on_window_size)
        self.canvas.connect('draw', self.on_window_draw)
        self.window.connect('check-resize', self.on_window_resize)

        # Finally hook up the events we need
        self.window.connect('destroy', self.on_menu_file_exit)
        self.window.connect('key_press_event', self.on_key_press)

        # Note that POINTER_MOTION_MASK generates a lot of events, depending
        # on use requirements adding POINTER_MOTION_HINT_MASK may be more
        # suitable which should reduce some overhead ...
        self.canvas.add_events(Gdk.EventMask.POINTER_MOTION_MASK)
        self.canvas.add_events(Gdk.EventMask.POINTER_MOTION_HINT_MASK)
        self.canvas.add_events(Gdk.EventMask.BUTTON_PRESS_MASK)
        self.canvas.add_events(Gdk.EventMask.BUTTON_RELEASE_MASK)
        self.canvas.add_events(Gdk.EventMask.SCROLL_MASK)

        self.mouse_buttons = {}
        self.mouse_buttons['left'] = MouseButton('left')
        self.mouse_buttons['middle'] = MouseButton('middle')
        self.mouse_buttons['right'] = MouseButton('right')

        self.canvas.connect('motion-notify-event', self.on_mouse_move)
        self.canvas.connect('button_press_event', self.on_mouse_press)
        self.canvas.connect('button_release_event', self.on_mouse_release)
        self.canvas.connect('scroll-event', self.on_mouse_scroll)

        # If needed, queue a file load to start after a short delay to give
        # time for the window to appear on screen
        if trace_file:
            GObject.timeout_add(
                500, lambda: self.load_file(trace_file, metadata_file))

        # ---- ----- ----- ----- -----
        # Start rendering
        self.window.show()
        self.window.present()
        Gtk.main()

    def on_menu_file_open(self, menu):
        '''
        Handle a File->Open selection event from the menu bar.

        Args:
            menu: str
                The menu name to load
        '''
        file_name = get_open_filechoice(
            self.window, 'Trace files', ('*.perfetto',))

        if None is file_name:
            self.status.log('Open cancelled (user)')
            return

        if file_name == self.loaded_file_path:
            self.status.log('Open skipped (same file)')
            return

        # Deactivate all the plugins
        self.view.deactivate()
        for view in self.loaded_views.values():
            view.unload()
        self.view = None
        self.on_menu_view(self.DEFAULT_VIEW)

        self.loaded_file_path = None
        self.trace_data = None

        self.load_file(file_name)

    def on_menu_file_close(self, menu):
        '''
        Handle a File->Close selection event from the menu bar.

        Args:
            menu: str
                The menu name to load
        '''
        # Deactivate all the plugins
        self.view.deactivate()
        for view in self.loaded_views.values():
            view.unload()

        self.view = None

        self.on_menu_view(self.DEFAULT_VIEW)

        self.loaded_file_path = None
        self.trace_data = None

        # Make file-based options non-sensitive
        for menu in self.menus_needing_file:
            menu.set_sensitive(False)

        self.status.log('File closed')

    def on_menu_file_exit(self, menu):
        '''
        Handle a File->Exit selection event from the menu bar.

        Args:
            menu: str
                The menu name to load
        '''
        '''
        if self.fileLoaded:
            self.on_MenuFileClose(menu)
        '''
        Gtk.main_quit()

    def on_menu_view(self, menu):
        '''
        Handle a View selection event from the menu bar.

        Args:
            menu: str
                The menu name to load
        '''
        # Don't do anything if the old view is the new view ...
        if self.view == self.loaded_views[menu]:
            return

        # Deactivate the old one, if it was active
        if self.view:
            self.view.deactivate()

        # Activate the new one ...
        self.view = self.loaded_views[menu]
        self.view.activate()
        self.view.resize()
        self.canvas.queue_draw()

    def load_file(self, trace_file, metadata_file=None):
        '''
        Handle the underlying data processing related to opening a file.

        Args:
           file_name: The trace file to load.
        '''
        assert self.loaded_file_path is None
        assert self.trace_data is None

        self.status.log('File loading. Please wait ...', None)

        # Notify the plugin views - this may take some time so defer it; change
        # the cursor so the user knows that we're thinking ...
        watch_cursor = Gdk.Cursor(Gdk.CursorType.WATCH)
        self.window.get_root_window().set_cursor(watch_cursor)

        def deferred_load():
            '''
            Deferred load function to allow cursor to change ...
            '''
            start_time = time.time()

            # Parse the raw data file
            try:
                trace_data = RawTrace(trace_file, metadata_file)
                self.trace_data = GPUTrace(trace_data)

                self.loaded_file_path = trace_file
            except Exception:
                self.status.log('Open cancelled (failed to load)')
                import traceback
                traceback.print_exc()
                return

            parse_time = time.time() - start_time

            for view in self.loaded_views.values():
                view.load(self.trace_data)

            # Reactivate the current view
            self.view.activate()

            # Make file-based options which require data sensitive
            for menu in self.menus_needing_file:
                menu.set_sensitive(True)

            build_time = time.time() - parse_time - start_time
            msg_parse = f'{parse_time:1.2f} s to parse'
            msg_build = f'{build_time:1.2f} s to build views'
            self.status.log(f'File opened ({msg_parse} / {msg_build})')

            # Reset the cursor back to something normal ...
            self.window.get_root_window().set_cursor(None)

        # Queue the deferred load when GTK has some time (this gives the mouse
        # cursor time to change ...
        GObject.idle_add(deferred_load)

    def add_child_menus(self, child_menus):
        '''
        Add the activating view's menus to the menu bar.

        Args:
            child_menus: List of menus to add.
        '''
        for menu in child_menus:
            self.menubar.append(menu)

    def remove_child_menus(self, child_menus):
        '''
        Remove the deactivating view's menus from the menu bar.

        Args:
            child_menus: List of menus to remove.
        '''
        for menu in child_menus:
            self.menubar.remove(menu)

    @staticmethod
    def decode_key_modifiers(event):
        '''
        Utility method to decode keyboard modifier keys (shift, control, alt)
        for the current event.

        Args:
            event: Gtk.Event
                The action event from GTK

        Returns:
            Returns a string containing the characters 'a', 'c', and/or 's'
            if the relevant modifier is present. Modifier characters are
            always present in the string in alphabetical order.
        '''
        # Linux doesn't have a default mapping for Right Alt / AltGR
        mask_alt2 = 0
        if sys.platform == 'win32':
            mask_alt2 = Gdk.ModifierType.MOD2_MASK

        mod = []
        if (event.state & Gdk.ModifierType.MOD1_MASK) or \
           (event.state & mask_alt2):
            mod.append('a')

        if event.state & Gdk.ModifierType.CONTROL_MASK:
            mod.append('c')

        if event.state & Gdk.ModifierType.SHIFT_MASK:
            mod.append('s')

        return ''.join(mod)

    @classmethod
    def decode_mouse_event(cls, event):
        '''
        Utility method to decode a mouse event into parameters.

        Args:
            event: Gtk.Event
                The action event from GTK

        Returns:
            Returns a four element tuple containing the following elements:

              ( x-coord, y-coord, button, key-modifier)

            The button is one of 'left', 'right', or 'middle' (or None if
            the button is not supported). The key modifier is an 'acs' string
            containing the alt-control-shift modifier state.
        '''
        # Decode the mouse button
        if event.button == 1:
            click_button = 'left'

        elif event.button == 2:
            click_button = 'middle'

        elif event.button == 3:
            click_button = 'right'

        else:
            click_button = None

        # Decode the alt/ctrl/shift key states
        key_modifier = cls.decode_key_modifiers(event)

        return (event.x, event.y, click_button, key_modifier)

    def on_key_press(self, _unused, event):
        '''
        Handle a key press event on the top level window.

        The key press request is canonicalized before it is forwarded to the
        currently active `View` plugin for processing.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
            event: Gtk.Event
                The action event from GTK
        '''
        key_name = Gdk.keyval_name(event.keyval)

        # Filter out modifiers - we use these for other things so cannot use
        # them as normal key presses. Stop them before they hit the plug-in ...
        key_prefixes = ['Shift', 'Control', 'Alt', 'Meta']
        for prefix in key_prefixes:
            if key_name.startswith(prefix):
                return False

        # Decode the alt/ctrl/shift key states
        mod = self.decode_key_modifiers(event)

        # Revert shift modifier applied by GTK so the handler doesn't have to
        # worry about handling D and d separately - shift state is provided
        # via the modifiers list above ...
        if 1 == len(key_name):
            key_name = key_name.lower()

        change = self.view.on_key_press(key_name, mod)
        if change:
            self.canvas.queue_draw()

        return True

    def on_mouse_press(self, _unused, event):
        '''
        Handle a mouse button press event on the top level window.

        The key press request is canonicalized before it is forwarded to the
        currently active `View` plugin for processing.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
            event: Gtk.Event
                The action event from GTK
        '''
        self.set_raw_mouse_event(event)

        # Decode the common mouse event properties
        x, y, click, mod = self.decode_mouse_event(event)
        if click is None:
            return False

        # Decode the mouse click type
        # pylint: disable=protected-access
        if event.type == Gdk.EventType.BUTTON_PRESS:
            click_type = 'single'
        elif event.type == Gdk.EventType._2BUTTON_PRESS:
            click_type = 'double'
        else:
            return False
        # pylint: enable=protected-access

        # Update drag state
        self.mouse_buttons[click].mouse_press(x, y, mod)

        if click_type == 'single':
            change = self.view.on_mouse_single_click(click, x, y, mod)
        else:
            change = self.view.on_mouse_double_click(click, x, y, mod)

        if change:
            self.canvas.queue_draw()

        return True

    def on_mouse_release(self, _unused, event):
        '''
        Handle a mouse button release event on the top level window.

        The key press request is canonicalized before it is forwarded to the
        currently active `View` plugin for processing.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
            event: Gtk.Event
                The action event from GTK
        '''
        self.set_raw_mouse_event(event)

        # Decode the common mouse event properties
        x, y, click = self.decode_mouse_event(event)[0:3]
        if click is None:
            return False

        button = self.mouse_buttons[click]

        # Update drag state
        button.mouse_release(x, y)

        # Check for drag box state, and handle if needed
        change1 = False
        if button.has_drag_complete():
            change1 = self.view.on_mouse_drag_release(click, button.drag)
            button.clear_drag()

        change2 = self.view.on_mouse_release(click)

        if change1 or change2:
            self.canvas.queue_draw()

        return True

    def on_mouse_move(self, _unused, event):
        '''
        Handle a mouse move event on the top level window.

        The underlying plugin code does not support arbitrary mouse move
        events, only click-and-drag style user interactions. This code turns
        the move into a delta encoding for click-and-drag before passing this
        canonical form to the currently active `View`.

        Movements which occur outside of a drag, or movements which do not
        trigger a movement since the last update are filtered out and do not
        make it to the plugin.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
            event: Gtk.Event
                The action event from GTK
        '''
        self.set_raw_mouse_event(event)

        x, y = (event.x, event.y)
        cv = self.view

        # Handle the raw mouse move event
        change = cv.on_mouse_move(x, y)

        # Handle the parsed mouse drag event
        for click, button in self.mouse_buttons.items():
            if button.is_down:
                break
        else:
            return False

        button = self.mouse_buttons[click]
        button.mouse_move(x, y)
        if button.has_drag_increment():
            change = change or cv.on_mouse_drag(click, button.drag)

        # If something changed then queue a redraw
        if change:
            self.canvas.queue_draw()

        # Consume the event
        return True

    def on_mouse_scroll(self, _unused, event):
        '''
        Handle a mouse wheel scroll event on the top level window.

        We only support up and down scrolls, so no fancy side-scrolling mice
        hardware is supported.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
            event: Gtk.Event
                The action event from GTK
        '''
        self.set_raw_mouse_event(event)

        if event.direction == Gdk.ScrollDirection.UP:
            scroll = 'up'
        elif event.direction == Gdk.ScrollDirection.DOWN:
            scroll = 'down'
        else:
            # We don't handle side scrolling mice wheels ...
            return False

        change = self.view.on_mouse_scroll(scroll, event.x, event.y)
        if change:
            self.canvas.queue_draw()

        return True

    def on_window_size(self, _unused, allocation):
        '''
        Handle the initial window allocation size.
        '''
        self.width = allocation.width
        self.height = allocation.height

    def on_window_resize(self, window):
        '''
        Handle a window resize event.

        Args:
            _unused : N/A
                Unused; only provided for API compatibility for GTK callback
        '''
        self.view.resize()
        self.canvas.queue_draw()

    def on_window_draw(self, _unused, _unused2):
        '''
        Handle a window redraw event.
        '''
        # TODO: Possible to minimize redraw size with GTK3?
        redraw_pos = (0, 0)
        redraw_dim = (self.width, self.height)
        self.view.draw_view(redraw_pos, redraw_dim)
