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
A TimelineWidgetBase is a container for drawable world-space objects that can be
dynamically transformed from world-space to canvas-space for rendering. The
widget interface provides standard controls for updating the visible region,
with zoom and pan control. It also provides standard tools for making
selections in canvas-space and mapping that back a specific object.

A TimelineViewport is used to describe the currently visible subset of
world-space, and the region of canvas-space coordinates that is it being
projected on to. Viewports are designed to be updated from frame-to-frame,
allowing efficient changes to select the region of world-space being rendered.
'''

from lglpy.timeline.drawable.drawable import Drawable
from lglpy.timeline.drawable.style import Style
from lglpy.timeline.drawable.canvas_drawable import CanvasDrawableRect, \
    CanvasDrawableRectFill, CanvasDrawableLabel, CanvasDrawableLine
from lglpy.timeline.drawable.timeline_viewport import TimelineViewport
from lglpy.timeline.drawable.entry_dialog import get_entry_dialog


class TimelineWidgetBase:
    '''
    A container for drawable world-space objects that can be dynamically
    transformed from world-space to canvas-space for rendering.

    This widget is designed as a set of horizontal time-tracks plotted on the
    canvas, with some fixed-function control regions for making actions and
    setting navigation bookmarks running along the top of the widget.

    The underlying viewport behavior is generic, but the zoom and pan controls
    (by virtue of the viewport used) only modify the X axis. Using the mouse
    for zoom will center the zoom on the cursor. Using mouse drag for pan will
    sync the pan with the cursor.

    Trying to pan past the start or end of the trace in the X axis will result
    in a visual pan limiter being displayed on screen.

    Attributes:
        CLAMP_PIXELS: Width of the boundary clamp boxes, in pixels.
        ACTION_BAR_PIXELS: Height of the action bar region in pixels.
        BOOKMARK_BAR_PIXELS: Height of the action bar region in pixels.
        MAX_PIXELS_PER_US_MAX : Max number of pixels per nanosecond.
            Increase this to allow more zoomed in views.
        ZOOM_SCALE: Scaling rate per step of zoom on the mouse wheel.
            Increase this to speed up rate of change.

    Attributes:
        drawable_trace: DrawableTrace`
            The trace data we are rendering.
        vp: TimelineViewport`
            The current world-space to canvas-space mapping.
        active_time_range : [min, max]
            The current active time region selected by the user.
        active_objects: set`
            The current set of active objects selected by the user.
        active_objects_stash: set`
            The current set of saved active objects.
    '''
    CLAMP_PIXELS = 12
    ACTION_BAR_PIXELS = 10
    BOTTOM_PAD_PIXELS = 20
    BOOKMARK_BAR_PIXELS = 15
    MAX_PIXELS_PER_US = 0.15
    ZOOM_RATE = 0.2

    def __init__(self, trace, cs_pos, cs_dim, css, prefix):
        '''
        Create a new widget.

        Args:
            trace: drawable sequence to render.
            cs_pos: canvas-space position of this widget.
            cs_dim: canvas-space width and height of this widget.
            css: CSS stylesheet to load styles from.
            prefix: the widget prefix for the stylesheet.
        '''
        self.parent = None

        self.drawable_trace = trace

        # Initial bounds are the size of the whole trace, but may be no data
        if self.drawable_trace.ws_bounds:
            ws_pos = (trace.ws_bounds.min_x, trace.ws_bounds.min_y)
            ws_dim = (trace.ws_bounds.w, trace.ws_bounds.h)
        else:
            ws_pos = (0, 0)
            ws_dim = (1, 1)

        self.vp = TimelineViewport(ws_pos, ws_dim, cs_pos, cs_dim)

        # The absolute limits in the original trace data
        self.original_trace_ws_min_x = trace.ws_bounds.min_x
        self.original_trace_ws_max_x = trace.ws_bounds.max_x

        # The absolute limits in the trace data
        self.trace_ws_min_x = trace.ws_bounds.min_x
        self.trace_ws_max_x = trace.ws_bounds.max_x

        # Initialize some rough initial clamps
        self.ws_clamp_min_x = self.vp.ws.min_x - 100
        self.ws_clamp_max_x = self.vp.ws.max_x + 100

        # Store the highlighted region on the trace
        self.active_time_range = []
        self.active_objects = set()
        self.active_objects_stash = None

        # Store the drag highlight region
        self.left_drag_start = None
        self.left_drag_current = None

        # Are we rendering labels?
        self.show_labels = False

        name = f'{prefix}core'
        self.background_style = Style.css_factory(css[name])

        name = f'{prefix}dragbox'
        self.drag_style = Style.css_factory(css[name])

        name = f'{prefix}activitybar'
        self.activity_bar_style = Style.css_factory(css[name])

        name = f'{prefix}bookmarkbar'
        self.bookmark_bar_style = Style.css_factory(css[name])

        name = f'{prefix}activeregion'
        self.activity_region_style = Style.css_factory(css[name])

        name = f'{prefix}limitclamp'
        self.clamp_style = Style.css_factory(css[name])

        # Legend configuration
        self.show_legend = False
        self.legend_entries = []

        name = f'{prefix}legend'
        self.legend_style = Style.css_factory(css[name])

        # Bookmarks
        self.bookmarks = {}

        name = f'{prefix}bookmark'
        self.bookmark_style = Style.css_factory(css[name])

    def add_legend_entry(self, name, style):
        '''
        Add a legend entry.

        Args:
            name: name of the legend entry.
            style: visual style for rendering.
        '''
        label = CanvasDrawableLabel(self.legend_style, name)
        self.legend_entries.append((label, style))

    def update_cs(self, cs_pos, cs_dim):
        '''
        Update the canvas-space coverage of this widget.

        Args:
            cs_pos: position in canvas-space.
            cs_dim: width and height in canvas-space.
        '''
        self.vp.update_cs(cs_pos, cs_dim)

    def is_widget_active(self, x, y):
        '''
        Is this widget active at the given canvas-space coordinate.

        Args:
            x: X coordinate in canvas-space.
            y: Y coordinate in canvas-space.

        Returns:
            True if active at coordinate, False otherwise.
        '''
        cs = self.vp.cs
        return (cs.min_x <= x <= cs.max_x) and (cs.min_y <= y <= cs.max_y)

    def get_active_objects(self, user_data=False):
        '''
        Return the set of active objects.

        #TODO: Move user data handling out of this into caller.

        Args:
            user_data: should we return user data or raw objects?

        Returns:
            Return a list of active objects, or an empty list on error.
        '''
        if not user_data:
            return list(self.active_objects)

        objects = [x.user_data for x in self.active_objects if x.user_data]
        return list(set(objects))

    def add_to_active_objects(self, new_object):
        '''
        Add a new object to the set of active objects.

        Args:
            new_object: the object to add.
        '''
        # If this is the first selection then fade all the 'other' objects
        if not self.active_objects:
            for drawable in self.drawable_trace.each_object():
                style_set = drawable.style.style_set
                drawable.style = style_set.get_style('fade')

        # Update the style if this is a new user data
        user_data = [x.user_data for x in self.active_objects if x.user_data]

        if new_object.user_data and (new_object.user_data not in user_data):
            for drawable in self.drawable_trace.each_object():
                if drawable.user_data == new_object.user_data:
                    style_set = drawable.style.style_set
                    drawable.style = style_set.get_style('highlight')
        else:
            style_set = new_object.style.style_set
            new_object.style = style_set.get_style('highlight')

        self.active_objects.add(new_object)

    def add_multiple_to_active_objects(self, new_objects):
        '''
        Add multiple objects to the set of active objects.

        Args:
            new_objects: sequence of objects to add.
        '''
        # If this is the first selection then fade all the 'other' objects
        if not self.active_objects:
            for drawable in self.drawable_trace.each_object():
                style_set = drawable.style.style_set
                drawable.style = style_set.get_style('fade')

        for new_object in new_objects:
            self.active_objects.add(new_object)
            if not new_object.user_data:
                style_set = new_object.style.style_set
                new_object.style = style_set.get_style('highlight')

        # TODO: What's the point in this?
        user_data = {x.user_data for x in self.active_objects if x.user_data}
        for drawable in self.drawable_trace.each_object():
            if drawable.user_data in user_data:
                style_set = drawable.style.style_set
                drawable.style = style_set.get_style('highlight')

    def remove_from_active_objects(self, old_object):
        '''
        Remove an object from the set of active objects.

        Args:
            old_object: WorldDrawable`
                The object to remove.
        '''
        removed_objects = set()
        user_data = old_object.user_data

        if user_data:
            for drawable in self.active_objects:
                if drawable.user_data == user_data:
                    removed_objects.add(drawable)
            for drawable in removed_objects:
                self.active_objects.remove(drawable)
        else:
            self.active_objects.remove(old_object)
            removed_objects.add(old_object)

        # If nothing left then reset the active state
        if not self.active_objects:
            self.clear_active_objects()
            return

        # Update the style if this is a new user data
        user_data = {x.user_data for x in self.active_objects if x.user_data}

        # Update the style
        if old_object.user_data and (old_object.user_data not in user_data):
            for drawable in self.drawable_trace.each_object():
                if drawable.user_data == old_object.user_data:
                    drawable.style = drawable.style.style_set.get_style('fade')
        else:
            old_object.style = old_object.style.style_set.get_style('fade')

    def clear_active_objects(self):
        '''
        Clear the set of active objects.
        '''
        self.active_objects.clear()
        for drawable in self.drawable_trace.each_object():
            drawable.style = drawable.style.style_set.get_style('normal')

    def get_active_time_range(self, limits=False):
        '''
        Return the active time range in world-space units.

        Args:
            limits: If True return start/end limits, else return duration.

        Returns:
            Return the start/end or duration of the active range, or None if
            not active range is set.
        '''
        if (not self.active_time_range) or \
           (self.active_time_range[0] == self.active_time_range[1]):
            return None

        if limits:
            return (self.active_time_range[0], self.active_time_range[1])

        return self.active_time_range[1] - self.active_time_range[0]

    def clear_active_time_range(self):
        '''
        Clear the active time range
        '''
        del self.active_time_range[:]

    def set_label_visibility(self, labels):
        '''
        Toggle whether this widget shows labels or not.

        Args:
            labels: True if labels should be drawn for channels.
        '''
        self.show_labels = labels

    def set_legend_visibility(self, legend):
        '''
        Toggle whether this widget shows the legend or not.

        Args:
            legend: True if legend should be  drawn.
        '''
        self.show_legend = legend

    def on_mouse_scroll(self, scroll, x, y):
        '''
        Handle a mouse scroll event.

        Args:
            scroll: str
                String indicating direction of the scroll. Must be "up" or
                "down"; side scrolling mice are not supported!
            x: int
                X coordinate of the mouse pointer in canvas-space.
            y: int
                Y coordinate of the mouse pointer in canvas-space.

        Returns:
            Returns True if this function triggered some behavior which needs
            a redraw, False otherwise.
        '''
        cs = self.vp.cs
        ws = self.vp.ws

        # Are the bounds out of this widget's canvas area?
        if not ((cs.min_x <= x <= cs.max_x) and (cs.min_y <= y <= cs.max_y)):
            return None

        # Convert the X coordinate to relative to canvas offset
        x = float(x - cs.min_x)

        # Mouse down zooms out, so we scale up the amount of WS on screen
        if scroll == 'down':
            scale = 1.0 + self.ZOOM_RATE
        else:
            scale = 1.0 - self.ZOOM_RATE

        # Calculate the ratio of scale to apply to X.min and X.max bounds
        # The aim is to keep the diagram under the mouse pointer stationary
        ratio_left = x / float(cs.w)
        ratio_right = 1.0 - ratio_left

        # Calculate the change in the world visibility based on the up or down
        new_ws_width = ws.w * scale

        # Clamp the amount of zoom in
        new_ws_min_width = cs.w / self.MAX_PIXELS_PER_US
        new_ws_width = max(new_ws_width, new_ws_min_width)

        # Calculate new boundaries
        ws_delta_width = new_ws_width - ws.w
        new_ws_min_x = ws.min_x - (ws_delta_width * ratio_left)
        new_ws_max_x = ws.max_x + (ws_delta_width * ratio_right)

        # Calculate the clamp size, in WS, based on the position given
        ws_clamp_width = new_ws_width / cs.w
        ws_clamp_width = int(ws_clamp_width) * self.CLAMP_PIXELS

        # Calculate modified min_x and max_x in world-space based on clamp size
        self.ws_clamp_min_x = self.trace_ws_min_x - ws_clamp_width
        self.ws_clamp_max_x = self.trace_ws_max_x + ws_clamp_width

        # Clamp zoomed values based on new clamps ...
        new_ws_min_x = max(int(new_ws_min_x), self.ws_clamp_min_x)
        new_ws_max_x = min(int(new_ws_max_x), self.ws_clamp_max_x)

        # Create new bounds, but keep old y as that is provided by top level
        ws_pos_new = [new_ws_min_x, ws.min_y]
        ws_dim_new = [new_ws_max_x - new_ws_min_x, ws.max_y - ws.min_y]
        self.vp.update_ws(ws_pos_new, ws_dim_new)
        ws = self.vp.ws

        # We've probably moved stuff, so request a redraw
        return True

    def on_mouse_drag(self, button, drag):
        '''
        Handle a mouse drag event.

        Args:
            button: which button was clicked?
            drag: the state of the drag event.

        Returns:
            Returns True if this function triggered some behavior which needs
            a redraw, False otherwise.
        '''
        ws = self.vp.ws

        # Left is a 'click and drag' selection operation increment
        if button == 'left':
            self.on_mouse_drag_increment(drag)
            return True

        # Middle is a 'click and drag' scroll left / right operation
        if button != 'middle':
            return False

        cs_delta_x = drag.delta[0]
        ws_delta_x = int(self.vp.scale_cs_to_ws_x * float(abs(cs_delta_x)))

        # If we are dragging left we increase the world-space timeline
        if cs_delta_x < 0:
            ws_max_delta_x = self.ws_clamp_max_x - ws.max_x
            ws_delta_x = min(ws_max_delta_x, ws_delta_x)
            new_ws_min_x = ws.min_x + ws_delta_x
            new_ws_max_x = ws.max_x + ws_delta_x

        # If we are dragging right we decrease the world-space timeline
        else:
            ws_min_delta_x = ws.min_x - self.ws_clamp_min_x
            ws_delta_x = min(ws_min_delta_x, ws_delta_x)
            new_ws_min_x = ws.min_x - ws_delta_x
            new_ws_max_x = ws.max_x - ws_delta_x

        # Clamp zoomed values based on new clamps ...
        new_ws_min_x = max(int(new_ws_min_x), self.ws_clamp_min_x)
        new_ws_max_x = min(int(new_ws_max_x), self.ws_clamp_max_x)

        # Create new bounds, but keep old y as that is provided by top level
        ws_pos_new = [new_ws_min_x, ws.min_y]
        ws_dim_new = [new_ws_max_x - new_ws_min_x, ws.max_y - ws.min_y]
        self.vp.update_ws(ws_pos_new, ws_dim_new)

        # We've probably moved stuff, so request a redraw
        return True

    def on_mouse_drag_increment(self, drag):
        '''
        Handle a mouse drag event.

        Args:
            drag: the state of the drag event.
        '''
        # If we are starting a new drag then reset any rectangle state
        self.left_drag_start = drag.start
        self.left_drag_current = drag.end

    def on_mouse_drag_release(self, button, drag):
        '''
        Handle a mouse drag release event.

        TODO: Make button part of the drag state so it's self contained?

        Args:
            button: name of the button.
            drag: state of this mouse drag event.

        Returns:
            True if this function triggered some behavior which needs a redraw,
            False otherwise.
        '''
        # Left button is processed as a drag event
        if button != 'left':
            return False

        # Reset the drag rectangle state
        self.left_drag_start = None
        self.left_drag_current = None

        start_x, start_y = drag.start
        end_x, end_y = drag.end

        # Skip drags in active region
        if start_y < self.ACTION_BAR_PIXELS + self.BOOKMARK_BAR_PIXELS:
            return False

        # Convert canvas-space to world-space coordinates
        vp = self.vp
        x_ws1, y_ws1 = vp.transform_cs_to_ws(start_x, start_y)
        x_ws2, y_ws2 = vp.transform_cs_to_ws(end_x, end_y)

        # Canonicalize so (min < max) is true
        min_x = min(x_ws1, x_ws2)
        min_y = min(y_ws1, y_ws2)
        max_x = max(x_ws1, x_ws2)
        max_y = max(y_ws1, y_ws2)

        # Find the clicked objects
        dt = self.drawable_trace
        clicked_objects = dt.get_boxed_objects(min_x, min_y, max_x, max_y)
        if not clicked_objects:
            # Force a redraw if we were dragging, even if the click itself
            # didn't do anything.
            return True

        # If no modifier then create selection from highlighted region
        if drag.mod == '':
            self.active_objects.clear()
            for clicked_object in clicked_objects:
                self.add_to_active_objects(clicked_object)

        # If 'c' modifier then append selection to highlighted region
        elif drag.mod == 'c':
            for clicked_object in clicked_objects:
                if clicked_object not in self.active_objects:
                    self.add_to_active_objects(clicked_object)

        # If 's' modifier then append selection to highlighted region
        elif drag.mod == 's':
            for clicked_object in clicked_objects:
                if clicked_object in self.active_objects:
                    self.remove_from_active_objects(clicked_object)

        return True

    def on_mouse_single_click(self, button, x, y, mod):
        '''
        Handle a click event.

        Args:
            button: name of the button.
            x: X coordinate of the mouse pointer in canvas-space.
            y: Y coordinate of the mouse pointer in canvas-space.
            mod: active key modifiers.

        Returns:
            True if this function triggered some behavior which needs a redraw,
            False otherwise.
        '''
        # Get widget-relative CS coordinates and WS coordinates
        cs = self.vp.cs
        cs_rel_y = y - cs.min_y

        # If in the ACTIONBAR pixels process as a view highlight ...
        if cs_rel_y < self.ACTION_BAR_PIXELS:
            ws_x = self.vp.transform_cs_to_ws_x(x)
            if mod == '':
                self.set_active_region(button, ws_x)
            if mod == 'c':
                self.set_clip_region(button, ws_x)
            return True

        # If in the top 20 pixels process as a view highlight ...
        bar_start = self.ACTION_BAR_PIXELS
        bar_end = self.ACTION_BAR_PIXELS + self.BOOKMARK_BAR_PIXELS
        if bar_start <= cs_rel_y < bar_end:
            ws_x = self.vp.transform_cs_to_ws_x(x)
            if (button == 'left') and (mod == ''):
                self.set_bookmark(ws_x)
            elif (button == 'right') and (mod == ''):
                self.clear_bookmark(x)
            return True

        # Else process as a click event on an object ...
        vp = self.vp
        ws_x, ws_y = vp.transform_cs_to_ws(x, y)
        clicked_object = self.drawable_trace.get_clicked_object(ws_x, ws_y)

        if (button == 'left') and clicked_object:
            if mod == '':
                if clicked_object in self.active_objects:
                    self.remove_from_active_objects(clicked_object)
                else:
                    self.active_objects.clear()
                    self.add_to_active_objects(clicked_object)
                return True

            if mod == 'c':
                if clicked_object in self.active_objects:
                    self.remove_from_active_objects(clicked_object)
                else:
                    self.add_to_active_objects(clicked_object)
                return True

        return False

    def set_clip_region(self, button, ws_x):
        '''
        Set the left and right limit region based on mouse input.

        Args:
            button: name of the button.
            ws_x: float
                The world-space location of the click.
        '''
        ws = self.vp.ws

        if button == 'left':
            ws_min_x = ws_x
            ws_max_x = ws.max_x
            self.ws_clamp_min_x = ws_min_x - 100
        elif button == 'right':
            ws_min_x = ws.min_x
            ws_max_x = ws_x
            self.ws_clamp_max_x = ws_max_x + 100
        else:
            return False

        self.trace_ws_min_x = self.ws_clamp_min_x
        self.trace_ws_max_x = self.ws_clamp_max_x

        # Create new bounds, but keep old y as that is provided by top level
        ws_pos_new = [ws_min_x, ws.min_y]
        ws_dim_new = [ws_max_x - ws_min_x, ws.max_y - ws.min_y]
        self.vp.update_ws(ws_pos_new, ws_dim_new)
        return True

    def set_active_region(self, button, ws_x):
        '''
        Set the left and right active region based on mouse input.

        Args:
            button: str
                The button in use (left or right).
            ws_x: float
                The world-space location of the click.
        '''
        if button == 'left':
            if self.active_time_range:
                self.active_time_range[0] = ws_x
                self.active_time_range[1] = \
                    max(ws_x, self.active_time_range[1])
            else:
                self.active_time_range.append(ws_x)
                self.active_time_range.append(self.trace_ws_max_x)
        elif button == 'right':
            if self.active_time_range:
                self.active_time_range[0] = \
                    min(ws_x, self.active_time_range[0])
                self.active_time_range[1] = ws_x
            else:
                self.active_time_range.append(self.trace_ws_min_x)
                self.active_time_range.append(ws_x)
        else:
            return False

        return True

    def set_bookmark(self, ws_x):
        '''
        Set the a new bookmark at the world-space X coordinate.

        Args:
            ws_x: float
                The world-space location of the click.
        '''
        bookmark = get_entry_dialog(self.parent.window, 'Enter Bookmark')
        if None is not bookmark:
            bookmark = bookmark.strip()

        if not bookmark:
            print('Warning: Bookmark not specified in dialog')
            return

        # TODO: We probably want to avoid bookmarks which are too close to
        # other bookmarks here, so make this an abs(diff) > limit check
        if ws_x in self.bookmarks:
            print('Warning: Bookmark already specified at this location')
            return

        if bookmark in self.bookmarks.values():
            print(f'Warning: Bookmark "{bookmark}" already specified')
            return

        self.bookmarks[ws_x] = bookmark

        return

    def clear_bookmark(self, cs_x):
        '''
        Clear the a new bookmark at the canvas-space X coordinate.

        Args:
            cs_x: float
                The canvas-space location of the click.
        '''
        # Get the bounds of a 4 pixel widget in world-space
        ws_min_x = self.vp.transform_cs_to_ws_x(cs_x - 2)
        ws_max_x = self.vp.transform_cs_to_ws_x(cs_x + 2)

        # Remove any bookmarks in this range
        for ws in self.bookmarks:
            if ws_min_x <= ws < ws_max_x:
                del self.bookmarks[ws]
                return True

        return False

    def get_coord_str(self, cx, cy):
        '''
        Return a coordinate string for the given canvas-space coordinate.

        This is used as an informative mouse hover, and includes generally
        useful information, so doesn't follow any predefined format.

        Returns:
            Returns a coordinate-based string if there is a useful string to
            return under the given canvas coordinates. This may be an empty
            string to clear a previous string, in some cases.

            Returns None if nothing useful can be returned. In this case no
            change should be presented to the lglpy.timeline.
        '''
        # If in the ACTION BAR then no string
        start = 0
        end = self.ACTION_BAR_PIXELS
        if start <= cy < self.ACTION_BAR_PIXELS:
            return ''

        # If in the BOOKMARK BAR then only a string if hovering over a bookmark
        start = end
        end += self.BOOKMARK_BAR_PIXELS
        if start <= cy < end:
            for bookmark, value in self.bookmarks.items():
                bx = self.vp.transform_ws_to_cs_x(bookmark)
                start = bx - 3
                end = bx + 3
                if start < cx < end:
                    ms = bookmark / 1000000.0
                    label = f'{ms:0.2f} ms, Bookmark "{value}"'
                    return label

            # Clear the string if not over a bookmark
            return ''

        # Otherwise we are over the main timeline so provide timeline coords
        wx = self.vp.transform_cs_to_ws_x(cx)

        # Add time to the label
        ms = float(wx) / 1000000.0
        label = f'{ms:0.2f} ms'

        return label

    def set_draw_clip(self, gc):
        '''
        Render the clamp regions, if needed.

        Args:
            gc: Cairo graphics context.
        '''
        cs = self.vp.cs
        ws = self.vp.ws

        extra_h = self.ACTION_BAR_PIXELS \
                + self.BOOKMARK_BAR_PIXELS \
                + self.BOTTOM_PAD_PIXELS

        # Draw min_x clamp limits and mask off once drawn
        if ws.min_x < self.trace_ws_min_x < ws.max_x:
            clamp_x = (self.ws_clamp_min_x + self.trace_ws_min_x) / 2

            # We want to convert to a width not a position, so remove offset
            cs_w = int(self.vp.transform_ws_to_cs_x(clamp_x)) - cs.min_x
            cs_w = min(cs_w, self.CLAMP_PIXELS)
            cs_h = cs.h

            # Position one pixel off the edge to left, top, and bottom so
            # we only get a visible outline on the right-hand edge
            pos = (Drawable.rt05(cs.min_x - 1), Drawable.rt05(cs.min_y - 1))
            dim = (cs_w + 1, cs_h + extra_h)

            clamp = CanvasDrawableRect(pos, dim, self.clamp_style)
            clamp.draw(gc)

            gc.rectangle(cs.min_x + cs_w + 1, cs.min_y, cs.w, cs.h + extra_h)
            gc.clip()

        # Draw max_x clamp limits and mask off once drawn
        if ws.min_x < self.trace_ws_max_x < ws.max_x:
            clamp_x = (self.ws_clamp_max_x + self.trace_ws_max_x) / 2

            # We want to convert to a width not a position, so remove offset
            cs_x = int(self.vp.transform_ws_to_cs_x(clamp_x))
            cs_w = cs.max_x - cs_x
            cs_w = min(cs_w, self.CLAMP_PIXELS)
            cs_h = cs.h

            # Position one pixel off the edge to left, top, and bottom so
            # we only get a visible outline on the right-hand edge
            pos = (Drawable.rt05(cs_x), Drawable.rt05(cs.min_y - 1))
            dim = (cs_w, cs_h + extra_h)

            clamp = CanvasDrawableRect(pos, dim, self.clamp_style)
            clamp.draw(gc)

            gc.rectangle(cs.min_x, cs.min_y, cs_x - cs.min_x, cs.h + extra_h)
            gc.clip()

    def draw_active_bar(self, gc):
        '''
        Render the active region control bar, and the active region if needed.

        Args:
            gc: Cairo graphics context.
        '''
        cs = self.vp.cs

        # Draw active region interactable zone user hint
        style = self.activity_bar_style
        height = self.ACTION_BAR_PIXELS
        active = CanvasDrawableRectFill((cs.min_x, cs.min_y),
                                        (cs.w, height), style)
        active.draw(gc)

        line = Drawable.rt05(cs.min_y + height - 1)
        points = [(cs.min_x, line), (cs.max_x, line)]
        active = CanvasDrawableLine(points, style)
        active.draw(gc)

        # Draw highlighted active region, if any
        if self.active_time_range:
            ws_min_x = self.active_time_range[0]
            ws_max_x = self.active_time_range[1]

            cs_min_x = self.vp.transform_ws_to_cs_x(ws_min_x, 2)
            cs_max_x = self.vp.transform_ws_to_cs_x(ws_max_x, 2)
            cs_w = cs_max_x - cs_min_x

            style = self.activity_region_style
            active = CanvasDrawableRect((cs_min_x, cs.min_y),
                                        (cs_w, cs.h), style)
            active.draw(gc)

    def draw_bookmark_bar(self, gc):
        '''
        Render the bookmark control bar.

        Args:
            gc: Cairo graphics context.
        '''
        cs = self.vp.cs

        # Draw active region interactable zone user hint
        style = self.bookmark_bar_style
        min_y = cs.min_y + self.ACTION_BAR_PIXELS
        height = self.BOOKMARK_BAR_PIXELS
        active = CanvasDrawableRectFill((cs.min_x, min_y),
                                        (cs.w, height), style)
        active.draw(gc)

        line = Drawable.rt05(min_y + height - 1)
        points = [(cs.min_x, line), (cs.max_x, line)]
        active = CanvasDrawableLine(points, style)
        active.draw(gc)

        # Draw bookmark points
        style = self.bookmark_style
        min_y = min_y + 2 - 0.5
        height = height - 4
        width = 4
        for ws_x, _ in self.bookmarks.items():
            # Skip bookmarks out of the current viewport
            if not self.vp.ws.min_x < ws_x < self.vp.ws.max_x:
                continue

            # Render bookmarks inside the current viewport
            min_x = self.vp.transform_ws_to_cs_x(ws_x, 1) - 2
            active = CanvasDrawableRect((min_x, min_y), (width, height), style)
            active.draw(gc)

    def draw_active_drag(self, gc):
        '''
        Render the active region control bar, and the active region if needed.

        Args:
            gc: Cairo graphics context.
        '''
        if self.left_drag_start:
            # Don't draw the highlight for an active bar drag
            height = self.ACTION_BAR_PIXELS + self.BOOKMARK_BAR_PIXELS
            if self.left_drag_start[1] < height:
                return

            min_x = min(self.left_drag_start[0], self.left_drag_current[0])
            max_x = max(self.left_drag_start[0], self.left_drag_current[0])
            min_y = min(self.left_drag_start[1], self.left_drag_current[1])
            max_y = max(self.left_drag_start[1], self.left_drag_current[1])

            w = max(1, max_x - min_x)
            h = max(1, max_y - min_y)

            # Draw active region interactable zone user hint
            style = self.drag_style
            active = CanvasDrawableRect((min_x, min_y), (w, h), style)
            active.draw(gc)

    def draw_legend(self, gc):
        '''
        Render the legend.

        Args:
            gc: Cairo graphics context.
        '''
        if (not self.legend_entries) or (not self.show_legend):
            return

        borderpad = 10
        textpad = 5
        entrypad = 20
        cell = 10
        max_x = self.vp.cs.max_x - 10

        width = borderpad
        for label, _ in self.legend_entries:
            width += label.get_label_extents(gc)[0]
            width += textpad + cell + entrypad
        width -= entrypad
        width += borderpad

        # Draw legend border
        style = self.legend_style
        min_x = max_x - width + 0.5
        min_y = borderpad + 0.5
        height = borderpad + cell + borderpad
        legend = CanvasDrawableRect((min_x, min_y), (width, height), style)
        legend.draw(gc)

        # Draw entries
        min_x += borderpad
        min_y += borderpad
        label_y = min_y + cell - 2
        for label, style in self.legend_entries:
            legend = CanvasDrawableRect((min_x, min_y), (cell, cell), style)
            legend.draw(gc)
            min_x += cell + textpad
            label.draw(gc, min_x, label_y)
            min_x += label.get_label_extents(gc)[0]
            min_x += entrypad

    def draw(self, gc, ch_filter=None, ws_range=None):
        '''
        Draw this widget.

        Args:
            gc: Cairo graphics context.
            ch_filter: channel filter function, or None if no filtering.
            ws_range: world-space extents withing which objects should be
                returned, or None if no filtering. Note that this is just an
                optimization hint, and objects outside of this range may be
                returned.
        '''
        cs = self.vp.cs
        extra_h = self.ACTION_BAR_PIXELS \
                + self.BOOKMARK_BAR_PIXELS \
                + self.BOTTOM_PAD_PIXELS

        gc.rectangle(cs.min_x, cs.min_y, cs.w, cs.h + extra_h)
        gc.clip()

        pos = (cs.min_x, cs.min_y)
        dim = (cs.w, cs.h + extra_h)
        test = CanvasDrawableRect(pos, dim, self.background_style)
        test.draw(gc)

        # Stop the app drawing over the border
        gc.rectangle(cs.min_x, cs.min_y, cs.w - 1, cs.h + extra_h - 1)
        gc.clip()

        # Disable culling as we use the viewport to transform coordinates when
        # rendering the widget decorations. It gets re-enabled per eligible
        # channel when rendering the trace.
        self.vp.enable_coverage_culling(False)

        self.set_draw_clip(gc)
        self.draw_bookmark_bar(gc)
        self.draw_active_bar(gc)

        # Draw the trace
        vp = self.vp
        self.drawable_trace.draw(gc, vp, ch_filter, ws_range, self.show_labels)

        self.draw_active_drag(gc)
        self.draw_legend(gc)
