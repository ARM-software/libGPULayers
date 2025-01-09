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
This module define the base class interface for View plugins that is used by
the root Window and event system to interface with the implementation of Views.
'''

from typing import TYPE_CHECKING

import cairo
# pylint: disable=wrong-import-position
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

if TYPE_CHECKING:
    from .window import Window
from ..drawable.drawable import *
from ..drawable.css import CSSStylesheet
from ..drawable.mouse_button import MouseDrag
from ..data.processed_trace import GPUTrace


class View:
    '''
    The Mali Trace Viewer tool is based around a number of graphical
    visualizations called Views, which are plugins inside a larger framework.
    This class provides the base class for these plugins, defining the event
    handling interface and the bare-essential rendering support.

    This class acts as a sake sink for events which are not needed in a
    particular subclass, so subclasses only have to implement handlers for the
    events they actually want to process.

    Attributes:
        MENU_NAME: The name to use in the Views drop-down menu. Should be
            replaced by the subclass.
        MENU_REQUIRES_DATA_FILE: True if the menu is greyed out if there is no
            data file loaded.
        window: The parent window surface which we use to retrieve the canvas
            surface from when it is available. This canvas must be available
            via an attribute window.canvas during the first draw operation.
        canvas: The surface we can use with Cairo rendering operations
        width: The current width of the rendering canvas. This is automatically
            updated on window resize.
        height: The current height of the rendering canvas. This is
            automatically updated on window resize.
        menu_item: The GTK menu related to this view.
        css: The CSS-ish stylesheet instance for styling the GUI.
        background_color:q The view background color.
    '''

    MENU_NAME = "<<SubclassMe>>"
    MENU_REQUIRES_DATA_FILE = True

    def __init__(self, window: 'Window', css: CSSStylesheet):
        '''
        Create a new `View` inside the scope of the parent window.

        Args:
            window: The parent window surface which we use to retrieve the
                canvas surface from when it is available. This canvas must be
                available via an attribute window.canvas during the first
                draw operation, but can be None if not valid at that time.
            css: The CSS-ish style settings to use when styling this View.
        '''
        self.window = window
        self.css = css

        # These do not exist at init time (no window surface yet)
        self.canvas = None
        self.width = None
        self.height = None
        self.menu_item = None

        self.background_color = css['mtv-core']['fill-color']

    def load(self, trace_data: GPUTrace) -> None:
        '''
        Load data into this view.

        Args:
            trace_data: The parsed trace file.
        '''
        del trace_data
        if self.menu_item is not None:
            self.menu_item.set_sensitive(True)

    def unload(self) -> None:
        '''
        Load data into this view.
        '''
        if self.menu_item is not None and self.MENU_REQUIRES_DATA_FILE:
            self.menu_item.set_sensitive(False)

    def activate(self) -> None:
        '''
        Turn this view into an activated view.

        This function does nothing in the base class, but subclasses can use it
        to implement deferred behavior which is only triggered when the view is
        activated, rather than when it is initialized or data or loaded.
        '''

    def deactivate(self) -> None:
        '''
        Turn this view into an deactivated view.

        This function does nothing in the base class, but subclasses can use it
        to implement behavior which is triggered when the user switches away
        from this view, such as discarding transient caches in order to save
        memory.
        '''

    def get_view_menu_item(self) -> Gtk.MenuItem:
        '''
        Return the view menu for this.

        This will return a dummy menu if no menu is specified in the subclass.

        Returns:
            The menubar menu item for this view.
        '''
        if self.menu_item is None:
            self.menu_item = Gtk.MenuItem(self.MENU_NAME)
            assert self.menu_item is not None

            if self.MENU_REQUIRES_DATA_FILE:
                self.menu_item.set_sensitive(False)
            self.menu_item.show()

        return self.menu_item

    def resize(self) -> None:
        '''
        Handle a canvas resize event if we have a window surface active.
        '''
        if self.canvas is not None:
            size = self.canvas.get_allocation()
            self.width = size.width
            self.height = size.height

    def get_cairo_context(self) -> cairo.Context:
        '''
        Populate the necessary draw credentials of this drawing operation.
        Most of the GUI is statically configured, so only the Cairo rendering
        context needs regenerating each time.

        Returns:
            A Cairo rendering context which will remain valid for the duration
            of this draw operation.
        '''
        # If we do not have cached state then cache it
        if self.canvas is None:

            # Cache the window canvas state
            self.canvas = self.window.canvas

            # This is possibly the first time we have a surface so call resize
            # to force dynamic widgets to get the correct canvas-space size
            self.resize()

        # Always return the new cairo context
        assert self.canvas is not None
        return self.canvas.get_property('window').cairo_create()

    def set_draw_clip(
            self, gc: cairo.Context, draw_pos: list[int],
            draw_dim: list[int]) -> None:
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

    def draw_view(self, draw_pos: list[int], draw_dim: list[int]):
        '''
        Render this view within the given clip region.

        Args:
            draw_pos: The draw position (min x and y coordinate)
            draw_dim: The draw size (width and height)

        Returns:
            A Cairo rendering context which will remain valid for the duration
            of this draw operation.
        '''
        gc = self.get_cairo_context()

        self.set_draw_clip(gc, draw_pos, draw_dim)

        # Fill the background with a clear color
        assert self.width and self.height
        gc.rectangle(0, 0, self.width, self.height)
        gc.set_source_rgba(*self.background_color)
        gc.fill()

        return gc

    # Below this point all functions are defaults which must be subclassed but
    # which define the API to use. To avoid lots of messing about with Pylint
    # we just globally disable the checkers.

    # pylint: disable=unused-argument

    def on_key_press(self, key: str, mod: str) -> bool:
        '''
        Handle a key press event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            key: The ASCII character for the key press which has been detected.
                Note that this is canonicalized to be lower case, so modifiers
                which GTK normally pre-applies, like shift, are reverted before
                the call gets this far.
            mod: A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a"lt, "c"trl, or
                "s"hift, in that order.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_single_click(
            self, button: str, x: int, y: int, mod: str) -> bool:
        '''
        Handle a mouse single click event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            button: String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            x: X coordinate of the mouse pointer in canvas-space.
            y: Y coordinate of the mouse pointer in canvas-space.
            mod: A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a"lt, "c"trl, or
                "s"hift, in that order.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_double_click(
            self, button: str, x: int, y: int, mod: str) -> bool:
        '''
        Handle a mouse double click event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            button: String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            x: X coordinate of the mouse pointer in canvas-space.
            y: Y coordinate of the mouse pointer in canvas-space.
            mod: A modifier string listing the modifiers which are applied.
                Currently this may contain zero or more of "a"lt, "c"trl, or
                "s"hift, in that order.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_drag(self, button: str, drag: MouseDrag) -> bool:
        '''
        Handle a mouse drag event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            button: String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            drag: The state of this mouse drag event.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_drag_release(self, button: str, drag: MouseDrag) -> bool:
        '''
        Handle a mouse drag release event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            button: String indicating which button was clicked. Must be "left",
                "right", or "middle". Other mice buttons are are not supported!
            drag: The state of this mouse drag event.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_move(self, x: int, y: int) -> bool:
        '''
        Handle a mouse move event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            x: Mouse x coordinate in screen space.
            y: Mouse y coordinate in screen space.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_release(self, button: str) -> bool:
        '''
        Handle a mouse single click event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            button: String indicating which button was released. Must be
                "left", "right", or "middle". Other mice buttons are are not
                supported!

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False

    def on_mouse_scroll(self, scroll: str, x: int, y: int) -> bool:
        '''
        Handle a mouse scroll event.

        This is a stub function, a subclass must provide handling methods.

        Args:
            scroll: String indicating direction of the scroll. Must be "up" or
                "down"; side scrolling mice are not supported!
            x: X coordinate of the mouse pointer in canvas-space.
            y: Y coordinate of the mouse pointer in canvas-space.

        Returns:
            True if this function triggered some behavior which needs a redraw.
        '''
        return False
