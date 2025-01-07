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

from lglpy.timeline.drawable.drawable import *


class View:
    '''
    The Mali Trace Viewer tool is based around a number of graphical
    visualizations called Views, which are plugins inside a larger framework.
    This class provides the base class for these plugins, defining the event
    handling interface and the bare-essential rendering support.

    This class acts as a sake sink for events which are not needed in a
    particular subclass, so subclasses only have to implement handlers for the
    events they actually want to process.

    :CVariables:
        MENU_NAME: str
            The name to use in the Views drop-down menu. Should be replaced by
            the subclass.
        MENU_REQUIRES_DATA_FILE: bool
            True if the menu is greyed out if there is no data file loaded.

    Attributes:
        window: window
            The parent window surface which we use to retrieve the canvas
            surface from when it is available. This canvas must be available
            via an attribute window.canvas during the first draw operation.
        canvas: GTK canvas
            The renderable surface we can use with Cairo rendering operations
        config: ConfigSection
            The configuration options loaded for this View from file.
        width: int
            The current width of the rendering canvas. This is automatically
            updated on window resize.
        height: int
            The current height of the rendering canvas. This is automatically
            updated on window resize.
        menu_item: GTK.menu_item
            The GTK menu related to this view.
        css: CSSStylesheet
            The CSS stylesheet instance for styling the GUI.
        background_color: (float, float, float, float)
            The view background color.
    '''

    MENU_NAME = "<<SubclassMe>>"
    MENU_REQUIRES_DATA_FILE = True

    def __init__(self, window, css):
        '''
        Create a new `View` inside the scope of the parent window and
        rendering config options.

        Args:
            window: window
                The parent window surface which we use to retrieve the canvas
                surface from when it is available. This canvas must be
                available via an attribute window.canvas during the first
                draw operation, but can be None if not valid at that time.
            css: CSSStylesheet
                The style settings to use when styling this View.
        '''
        self.window = window
        self.css = css

        # These do not exist at init time (no window surface yet)
        self.canvas = None
        self.width = None
        self.height = None
        self.menu_item = None

        self.background_color = css["mtv-core"]["fill-color"]

    def load(self, trace_data):
        '''
        Load data into this view.

        Args:
            trace_data: `MTVFileReader`
                The parsed trace file.
        '''
        del trace_data
        if self.menu_item is not None:
            self.menu_item.set_sensitive(True)

    def unload(self):
        '''
        Load data into this view.
        '''
        if (self.menu_item is not None) and self.MENU_REQUIRES_DATA_FILE:
            self.menu_item.set_sensitive(False)

    def activate(self):
        '''
        Turn this view into an activated view. This function does nothing in
        the base class, but subclasses can use it to implement deferred
        behavior which is only triggered when the view is activated, rather
        than when it is initialized or data or loaded.
        '''

    def deactivate(self):
        '''
        Turn this view into an deactivated view. This function does nothing in
        the base class, but subclasses can use it to implement behavior which
        is triggered when the user switches away from this view, such as
        discarding transient caches in order to save memory
        '''

    def get_view_menu_item(self):
        '''
        Return the menu for this. This will return a dummy menu if no specific
        menu is specified in the subclass.
        '''
        if self.menu_item is None:
            self.menu_item = Gtk.MenuItem(self.MENU_NAME)
            if self.MENU_REQUIRES_DATA_FILE:
                self.menu_item.set_sensitive(False)
            self.menu_item.show()

        return self.menu_item

    def resize(self):
        '''
        Handle a canvas resize event if we have a window surface active.
        '''
        if self.canvas is not None:
            size = self.canvas.get_allocation()
            self.width = size.width
            self.height = size.height

    def get_cairo_context(self):
        '''
        Populate the necessary draw credentials of this drawing operation.
        Most of the GUI is statically configured, so only the Cairo rendering
        context needs regenerating each time.

        Returns:
            Returns a Cairo rendering context which will remain valid for the
            duration of this draw operation.
        '''
        # If we do not have cached state then cache it
        if self.canvas is None:

            # Cache the window canvas state
            self.canvas = self.window.canvas

            # This is possibly the first time we have a surface so call resize
            # to force dynamic widgets to get the correct canvas-space size
            self.resize()

        # Always return the new cairo context
        return self.canvas.get_property('window').cairo_create()

    def set_draw_clip(self, gc, draw_pos, draw_dim):
        '''
        Clip the given rendering context to an axis-aligned rectangular region.

        Args:
            gc: Cairo graphics context.
            draw_pos: The draw position (min x and y coordinate)
            draw_dim: The draw size (width and height)
        '''
        gc.reset_clip()
        gc.rectangle(draw_pos[0], draw_pos[1], draw_dim[0], draw_dim[1])
        gc.clip()

    def draw_view(self, draw_pos, draw_dim):
        '''
        Render this view within the given clip region.

        Args:
            draw_pos: The draw position (min x and y coordinate)
            draw_dim: The draw size (width and height)

        Returns:
            Returns a Cairo rendering context which will remain valid for the
            duration of this draw operation.
        '''
        gc = self.get_cairo_context()

        self.set_draw_clip(gc, draw_pos, draw_dim)

        # Fill the background with a clear color
        gc.rectangle(0, 0, self.width, self.height)
        gc.set_source_rgba(*self.background_color)
        gc.fill()

        return gc

    # Below this point all functions are defaults which must be subclassed but
    # which define the API to use. To avoid lots of messing about with Pylint
    # we just globally disable the checkers.

    # pylint: disable=unused-argument

    def on_key_press(self, key, mod):
        '''
        Handle a key press event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            key: str
                The ASCII character for the key press which has been detected.
                Note that this is canonicalized to be lower case, so modifiers
                which GTK normally pre-applies, like shift, are reverted before
                the call gets this far.
            mod: str
                A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a", "c", or "s"
                (in that order).

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_single_click(self, button, x, y, mod):
        '''
        Handle a mouse single click event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            button: str
                String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            x: int
                X coordinate of the mouse pointer in canvas-space.
            y: int
                Y coordinate of the mouse pointer in canvas-space.
            mod: str
                A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a", "c", or "s"
                (in that order)..

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_double_click(self, button, x, y, mod):
        '''
        Handle a mouse single click event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            button: str
                String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            x: int
                X coordinate of the mouse pointer in canvas-space.
            y: int
                Y coordinate of the mouse pointer in canvas-space.
            mod: str
                A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a", "c", or "s"
                (in that order).

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_drag(self, button, drag):
        '''
        Handle a mouse drag event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            button: str
                String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            drag: MouseDrag`
                The composite state of this mouse drag event.

        Returns:
            Returns True if this function triggered some behavior which needs
            a redraw, False otherwise.
        '''
        return False

    def on_mouse_drag_release(self, button, drag):
        '''
        Handle a mouse drag release event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            button: str
                String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            drag: MouseDrag`
                The composite state of this mouse drag event.

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_move(self, x, y):
        '''
        Handle a mouse move event. This is a stub function, a subclass must
        provide the detailed handling methods.

        Args:
            x: int
                Mouse x coordinate in screen space.
            y: int
                Mouse y coordinate in screen space.

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_release(self, button):
        '''
        Handle a mouse single click event. This is a stub function, a subclass
        must provide the detailed handling methods.

        Args:
            button: str
                String indicating which button was released. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!

        Returns:
            Returns True if this function triggered some behavior which
            needs a redraw, False otherwise.
        '''
        return False

    def on_mouse_scroll(self, scroll, x, y):
        '''
        Handle a mouse scroll event. This is a stub function, a subclass must
        provide the detailed handling methods.

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
        return False
