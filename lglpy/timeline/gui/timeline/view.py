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

import time

import gi
gi.require_version('Gtk', '3.0')
# pylint: disable=wrong-import-position
from gi.repository import Gtk


from .info_widget import TimelineInfoWidget
from .timeline_widget import TimelineWidget
from ..view import View
from ...drawable.drawable_trace import DrawableTrace
from ...drawable.drawable_channel import DrawableChannel
from ...drawable.world_drawable import WorldDrawableRect
from ...drawable.style import Style, StyleSet, StyleSetLibrary


class FakeMouseDrag:
    '''
    Create a fake key drag event for simulating a mouse drag when pressing
    a key 'alternative' instead of dragging.
    '''

    def __init__(self, drag):
        '''
        Create a new fake mouse drag.

        Args:
            drag: The drag amount.
        '''
        if drag > 0:
            self.start = (0, 1)
            self.end = (drag, 1)
        else:
            self.start = (abs(drag), 1)
            self.end = (0, 1)

        self.delta = [drag]


class TLSpec:
    '''
    An instance of this class resembles the specification for the behavior of
    a single object class in the timeline widget. This effectively defines the
    behavior of a single drawable channel and all the objects it contains.

    To provide different coloring modes some channels simply overlap the
    same screen space.
    '''
    CHANNEL_START_Y = 55
    CHANNEL_BOX_Y = 50
    CHANNEL_GAP_Y = 30

    specMap = {}  # type: dict[str, TLSpec]

    def __init__(self, name, row, layer, cull, click, label):
        '''
        Create the specification of a new channel row.
        '''
        self.name = name
        self.row = row
        self.layer = layer
        self.cull = cull
        self.click = click
        self.label = label

        # Update the class state cache
        self.__class__.specMap[name] = self
        self.cached_start_y = None

    def get_y_start(self):
        '''
        Get the start of this channel in the world-coordinates.

        Returns:
            The start Y coordinate.
        '''
        if None is not self.cached_start_y:
            return self.cached_start_y

        y = self.CHANNEL_START_Y

        # Ready channel piggybacks on the back of its parent channel
        y += self.row * (self.CHANNEL_BOX_Y + self.CHANNEL_GAP_Y)

        self.cached_start_y = y
        return y

    def get_y_end(self):
        '''
        Get the end of this channel in the world-coordinates.

        Returns:
            The end Y coordinate.
        '''
        return self.get_y_start() + self.CHANNEL_BOX_Y

    @classmethod
    def get_channel(cls, channel):
        '''
        Get the channel matching the name.
        '''
        return cls.specMap[channel]

    @classmethod
    def get_channels(cls):
        '''
        Get all channels, sorted by name.
        '''
        return sorted(cls.specMap.keys())

    @classmethod
    def get_box(cls, channel, start, end, style, label, short, user_data=None):
        '''
        Build a drawable box to go into a channel.

        TODO: Move this to DrawableChannel?
        '''
        channel = cls.specMap[channel]
        pos = (start, channel.get_y_start())
        dim = (end - start, cls.CHANNEL_BOX_Y)
        short = None if short == label else short
        draw = WorldDrawableRect(pos, dim, style, label, short)
        draw.set_user_data(user_data)
        return draw


class TLColor:
    '''
    An instance of this class resembles the specification for the behavior of
    a single class of object and how it is colored (i.e. which StyleSet
    objects of this class uses).
    '''

    def __init__(self, channel, style_code, types, rotation):
        '''
        Create a new TLColor config entry.

        Args:
            channel: str
                The channel name for the objects to be colored.
            style_code: str
                The name of StyleSet to use.
            types: str
                The name of the object class which is to be colored.
            rotation: bool
                Whether objects of this class use a rotating set of styles to
                provide visual differentiation.
        '''
        self.channel = channel
        self.style_code = style_code
        self.types = types
        self.rotation = rotation


class TLStyles(StyleSetLibrary):
    '''
    An instance of this class resembles the specification for the behavior of
    the drawable styles which are used by the rendering of the timeline.
    '''

    COLORS = ['frame']

    COLORS_ROTATE = ['frame', 'fbo', 'win']

    def __init__(self, css, color_map):
        '''
        Create a populated style set library.
        '''
        super().__init__()
        self.color_map = color_map
        self.cache = {}

        for color in self.COLORS:
            for variant in StyleSet.VARIANTS:
                self.add_style(css, color, variant)

        for color_base in self.COLORS_ROTATE:
            for i in range(0, 3):
                color = f'{color_base}{i}'
                for variant in StyleSet.VARIANTS:
                    self.add_style(css, color, variant)

    def add_style(self, css, style_name, variant):
        '''
        Add a new style to the timeline style library
        '''
        style_variant = f'tlv-x{style_name}.{variant}'

        # Try to load the CSSNode - skip if it didn't exist
        try:
            style_node = css[style_variant]
        except KeyError:
            return

        # Load the parent style set, creating if it doesn't exist
        if style_name not in self:
            style_set = StyleSet(style_name)
            self.add_style_set(style_set)

        # Create the style
        style = Style(variant)
        style.load_from_css(style_node)

        style_set = self.get_style_set(style_name)
        style_set.add_style(variant, style)

    def get_style(self, name, variant=0, types='all'):
        '''
        Add a new style to the timeline style library
        '''
        # Determining the correct style is quite slow and called frequently, so
        # build a hash table of styles matching requested keys and use that ...
        key = (name, variant, types)
        if key in self.cache:
            return self.cache[key]

        name = name.split('.')
        name = name[0:2]
        name = '.'.join(name)

        # Find the style specified for the given channel, object, and rotation
        def test(x):
            return x.channel == name and x.types == types

        cmap = [x for x in self.color_map if test(x)]
        assert len(cmap) == 1, f'{name}, {len(cmap)}'

        style = cmap[0].style_code
        if cmap[0].rotation:
            style = f'{style}{variant}'

        # Call the parent class method to fetch the correct style
        style = super().get_style(style)
        self.cache[key] = style
        return style


class TimelineView(View):
    '''
    This `View` is the hardware-centric time-based event trace, showing the
    flow of GPU workloads through the combined software and hardware stack.
    '''

    MENU_NAME = 'Timeline'
    DEBUG_DRAW_TIME = False
    MENU_REQUIRES_DATA_FILE = True
    INFO_PANEL_W = 450

    def __init__(self, window, css):
        '''
        Create a new timeline view.
        '''
        super().__init__(window, css)
        self.background_color = css['tlv-core']['fill-color']

        self.parent = window
        self.css = css
        self.trace_data = None

        self.timeline_widget = None
        self.timeline_trace = None
        self.info_widget = None

        # Spec includes lanes that collide, but only one exists at a time
        self.timeline_spec = (
            TLSpec('Submit', 0, 1, True, True, True),
            TLSpec('Compute', 1, 1, True, True, True),
            TLSpec('Non-fragment', 2, 1, True, True, True),
            TLSpec('Binning', 2, 1, True, True, True),
            TLSpec('Fragment', 3, 1, True, True, True),
            TLSpec('Main', 3, 1, True, True, True),
            TLSpec('Transfer', 4, 1, True, True, True),
        )

        self.timeline_colors = (
            TLColor('Submit', 'win', 'window', True),
            TLColor('Submit', 'fbo', 'fbo', True),
            TLColor('Compute', 'win', 'window', True),
            TLColor('Compute', 'fbo', 'fbo', True),
            TLColor('Non-fragment', 'win', 'window', True),
            TLColor('Non-fragment', 'fbo', 'fbo', True),
            TLColor('Binning', 'win', 'window', True),
            TLColor('Binning', 'fbo', 'fbo', True),
            TLColor('Fragment', 'win', 'window', True),
            TLColor('Fragment', 'fbo', 'fbo', True),
            TLColor('Main', 'win', 'window', True),
            TLColor('Main', 'fbo', 'fbo', True),
            TLColor('Transfer', 'win', 'window', True),
            TLColor('Transfer', 'fbo', 'fbo', True),
        )

        self.timeline_styles = TLStyles(self.css, self.timeline_colors)

        self.menu_visibility_spec = (
            [1, 'Show labels', True, self.on_visibility_other, 'labels'],
            [1, 'Show info panel', True, self.on_visibility_other, 'info']
        )

        self.config_visibility = {
            'channel': {},
            'other': {}
        }

        # Everything defaults to visible (we use the menuVisibilitySpec to
        # turn off the few things which are not enabled by default).
        for channel in TLSpec.get_channels():
            self.config_visibility['channel'][channel] = True

        for item in self.menu_visibility_spec:
            self.config_visibility['other'][item[4]] = item[2]

        # Local menu: create the menu items
        self.menu_bar = Gtk.MenuItem('Timeline')

        menu_root = Gtk.Menu()
        self.menu_bar.set_submenu(menu_root)

        for item in self.menu_visibility_spec:
            menu_item = Gtk.CheckMenuItem(item[1])
            menu_root.append(menu_item)
            menu_item.connect_object('activate', item[3], item)
            item[0] = menu_item
            menu_item.set_active(item[2])

        self.menu_bar.show_all()

    def on_visibility_other(self, item):
        '''
        Event handler for visibility menu actions.
        '''
        state = item[0].get_active()
        self.config_visibility['other'][item[4]] = state
        # Resize to force repartioning of space if panel changed ...
        if (item[4] == 'labels') and self.timeline_widget:
            self.timeline_widget.set_label_visibility(state)
        if item[4] == 'info':
            self.resize()
        self.parent.queue_draw()

    def load(self, trace_data=None):
        '''
        Populate this view with a loaded data file.

        See the base class `View` for the documentation.
        '''
        super().load(None)

        # Build the empty drawable skeleton for the view to use
        style = Style.css_factory(self.css['tlv-tlw-labels'])
        trace = DrawableTrace(style)
        self.timeline_trace = trace

        if not trace_data:
            return

        # TODO: Channel names need to be made dynamic
        for tl in self.timeline_spec:
            channel = DrawableChannel(
                tl.name, trace, tl.layer, tl.cull, tl.click)
            channel.label_visible = tl.label

        # Add submits
        seen_submits = set()
        channel = trace.get_channel('Submit')
        for name, stream in trace_data.streams.items():

            for event in stream:

                # Skip if no submit, or we've already processed it
                if not event.submit or event.submit in seen_submits:
                    continue

                submit = event.submit
                seen_submits.add(submit)

                stime = submit.start_time
                etime = stime + 50

                workload = 'fbo'
                style = self.timeline_styles.get_style('Submit', 0, workload)
                draw = TLSpec.get_box(
                    'Submit', stime, etime, style, '', '', submit)
                channel.add_object(draw)

        # Add presents
        seen_submits = set()
        seen_presents = set()
        channel = trace.get_channel('Submit')
        for name, stream in trace_data.streams.items():

            for event in stream:

                # Skip if no submit, or we've already processed it
                if not event.submit or event.submit in seen_submits:
                    continue

                submit = event.submit

                # Skip if no present, or we've already processed it
                if not submit.present or submit.present in seen_presents:
                    continue

                present = submit.present

                seen_submits.add(submit)
                seen_presents.add(present)

                stime = present.start_time
                etime = stime + 50

                workload = 'window'
                style = self.timeline_styles.get_style('Submit', 0, workload)
                draw = TLSpec.get_box(
                    'Submit', stime, etime, style, '', '', present)
                channel.add_object(draw)

        # Add scheduling channels
        for name, stream in trace_data.streams.items():
            name = name.get_ui_name(name)
            channel = trace.get_channel(name)

            for event in stream:
                llabel = event.get_long_label()
                slabel = event.get_short_label()

                stime = event.start_time
                etime = event.start_time + event.duration

                workload = 'fbo'  # TODO: Identify swapchain
                style = self.timeline_styles.get_style(name, 0, workload)

                draw = TLSpec.get_box(name, stime, etime, style,
                                      llabel, slabel, event)
                channel.add_object(draw)

        # Compile the trace to improve performance
        for channel in trace:
            channel.compile()

        trace.ws_bounds.min_y = 0
        trace.ws_bounds.h = trace.ws_bounds.max_y
        self.timeline_widget = TimelineWidget(self.parent, trace, self.css)
        labels = self.config_visibility['other']['labels']
        self.timeline_widget.set_label_visibility(labels)

        style = Style.css_factory(self.css['tlv-info'])
        self.info_widget = TimelineInfoWidget(self.timeline_widget, style)

    def activate(self):
        '''
        Activate this view.
        '''
        self.parent.add_child_menus([self.menu_bar])

    def deactivate(self):
        '''
        Deactivate this view.
        '''
        self.parent.remove_child_menus([self.menu_bar])

    def resize(self):
        '''
        Process a resize event to scale the canvas appropriately.

        For this view the world-space mapping to canvas Y axis is a constant
        size, irrespective of window size, so we have to clamp that here.
        '''
        super().resize()

        # If we don't have a draw state yet then we have no canvas size
        if self.canvas is None:
            return

        # Calculate new widget sizes
        if self.config_visibility["other"]["info"]:
            pos = (0, 0)
            dim = (self.width - self.INFO_PANEL_W,
                   self.height)
            self.timeline_widget.update_cs(pos, dim)

            pos = (self.width - self.INFO_PANEL_W, 0)
            dim = (self.INFO_PANEL_W,
                   self.height)
            self.info_widget.update_cs(pos, dim)

        else:
            pos = (0, 0)
            dim = (self.width, self.height)
            self.timeline_widget.update_cs(pos, dim)

    def on_key_press(self, key, mod):
        '''
        Handle a key press event.

        See the base class `View` for the documentation.
        '''
        if not self.timeline_widget:
            return False

        # Provide basic keyboard navigation with arrow keys
        if (key == 'Up') and (mod == ''):
            width = self.width / 2
            return self.on_mouse_scroll('up', width, 50)

        if (key == 'Down') and (mod == ''):
            width = self.width / 2
            return self.on_mouse_scroll('down', width, 50)

        if (key == 'Left') and (mod == ''):
            drag = self.width / 15
            drag = FakeMouseDrag(drag)
            return self.on_mouse_drag('middle', drag)

        if (key == 'Right') and (mod == ''):
            drag = -self.width / 15
            drag = FakeMouseDrag(drag)
            return self.on_mouse_drag('middle', drag)

        # No valid key was detected, so don't update any rendering
        return False

    def on_mouse_scroll(self, scroll, x, y):
        '''
        Handle a mouse scroll event.

        See the base class `View` for the documentation.
        '''
        # Test widgets until we find one ...
        if not self.timeline_widget.is_widget_active(x, y):
            return False

        return self.timeline_widget.on_mouse_scroll(scroll, x, y)

    def on_mouse_single_click(self, button, x, y, mod):
        '''
        Handle a mouse single click event.

        See the base class `View` for the documentation.
        '''
        # Only handle left and right clicks
        if button not in ['left', 'right']:
            return False

        # Test widgets until we find one ...
        if not self.timeline_widget.is_widget_active(x, y):
            return False

        return self.timeline_widget.on_mouse_single_click(button, x, y, mod)

    def on_mouse_move(self, x, y):
        '''
        Handle a mouse move event.

        See the base class `View` for the documentation.
        '''
        # Test widgets until we find one ...
        if self.timeline_widget.is_widget_active(x, y):
            coord = self.timeline_widget.get_coord_str(x, y)
            if coord is not None:
                self.parent.status.log(coord)

        # Nothing here requires a canvas redraw
        return False

    def on_mouse_drag(self, button, drag):
        '''
        Handle a mouse drag event.

        See the base class `View` for the documentation.
        '''
        # We only handle drag events for the middle mouse button in X axis.
        # Bail early if nothing needs doing ...

        if button not in ['left', 'middle']:
            return False

        # Is this drag inside the world-space widget
        start_active = self.timeline_widget.is_widget_active(*drag.start)
        end_active = self.timeline_widget.is_widget_active(*drag.end)
        if start_active and end_active:
            return self.timeline_widget.on_mouse_drag(button, drag)

        return False

    def on_mouse_drag_release(self, button, drag):
        '''
        Handle a mouse drag and release event.

        See the base class `View` for the documentation.
        '''
        # We only handle drag+release events for the left mouse button.
        # Bail early if nothing needs doing ...
        if button != 'left':
            return False

        # Is this drag inside the world-space widget
        start_active = self.timeline_widget.is_widget_active(*drag.start)
        end_active = self.timeline_widget.is_widget_active(*drag.end)
        if start_active and end_active:
            return self.timeline_widget.on_mouse_drag_release(button, drag)

        return False

    def draw_channel_filter(self, channel):
        '''
        Callback to determine if the given channel should be visible or not.
        '''
        return self.config_visibility['channel'][channel.name]

    def draw_view(self, draw_pos, draw_dim):
        '''
        Render this view based on the current render state.

        See the base class `View` for the documentation.
        '''
        gc = super().draw_view(draw_pos, draw_dim)

        start_time = time.time()

        self.set_draw_clip(gc, draw_pos, draw_dim)
        self.timeline_widget.draw(gc, self.draw_channel_filter)

        if self.config_visibility['other']['info']:
            self.set_draw_clip(gc, draw_pos, draw_dim)
            self.info_widget.draw(gc)

        end_time = time.time()

        if self.DEBUG_DRAW_TIME:
            time_ms = (end_time - start_time) * 1000.0
            print(f'Rendering took {time_ms:0.2f} ms')
