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
This module implements utility classes for helping manage mouse interactions.

The MouseButton class implements persistent state tracking for low-level GTK
mouse events, so it can convert them into high-level logical events such as
click and press-and-drag.

The MouseDrag class implements persistent state tracking for a single
press-and-drag event.
'''


class MouseDrag:
    '''
    The state of a single mouse drag event.

    Attributes:
        start: start coordinates of the drag.
        end: current, and finally end, coordinates of the drag.
        delta: position delta in the last drag increment.
        mod: modifier key pressed when the mouse click was made.
        type: the state of the drag:
            - NEW if this is the start of a new drag
            - ACTIVE if this is not new and still active drag
            - COMPLETE if this is a resolved drag
    '''
    NEW = 0
    ACTIVE = 1
    COMPLETE = 2

    def __init__(self, start, mod):
        '''
        Create a new drag state instance.
        '''
        self.start = start
        self.end = start
        self.mod = mod
        self.delta = (0, 0)
        self.type = self.NEW

    def increment(self, delta_x, delta_y):
        '''
        Update a drag instance based on a mouse move event
        '''
        self.end = (self.end[0] + delta_x, self.end[1] + delta_y)
        self.delta = (delta_x, delta_y)
        self.type = self.ACTIVE

    def complete(self):
        '''
        Mark this drag as complete.
        '''
        self.type = self.COMPLETE


class MouseButton:
    '''
    The current state of a single mouse button.

    State persists over multiple GTK events, allowing us to turn low-level
    events into high-level actions such as click-and-drag.

    Attributes:
        name: name string.
        is_down: True if is this button is pressed.
        mod: modifier key when button first pressed.
        start_pos: start position of a drag, None if not in a drag.
        last_pos: last position of a drag, None if not in a drag.
        drag: state of a mouse drag, or None if no drag is active.
    '''

    def __init__(self, name):
        '''
        Create a new button for state tracking.

        Args:
            name: name string.
        '''
        self.name = name
        self.is_down = False
        self.mod = None
        self.start_pos = None
        self.last_pos = None
        self.drag = None

    def mouse_press(self, x, y, mod):
        '''
        Update state based on a mouse press event.

        Args:
            x: mouse x coordinate.
            y: mouse y coordinate.
            mod: modifier key pressed when the mouse click was made.
        '''
        self.is_down = True
        self.mod = mod

        self.start_pos = (x, y)
        self.last_pos = (x, y)

        # Start a new drag state instance
        self.drag = MouseDrag(self.start_pos, self.mod)

    def mouse_move(self, x, y):
        '''
        Update state based on a mouse move event.

        Args:
            x: mouse x coordinate.
            y: mouse y coordinate.
        '''
        if self.last_pos:
            delta_x = x - self.last_pos[0]
            delta_y = y - self.last_pos[1]
            self.last_pos = (x, y)

            if self.is_down:
                self.drag.increment(delta_x, delta_y)

        self.last_pos = (x, y)

    def mouse_release(self, x, y):
        '''
        Update state based on a mouse release event.

        Args:
            x: mouse x coordinate.
            y: mouse y coordinate.
        '''
        # Ensure move reflects final position
        self.mouse_move(x, y)

        # Release the button state
        self.is_down = False

        # Finalize a drag state instance
        # Can be None if mouse pressed outside of window, but released inside
        if self.drag:
            self.drag.complete()

    def has_drag_increment(self):
        '''
        Return a True if we are in a drag and drag moved in the last event.
        '''
        return self.drag and (self.drag.delta[0] or self.drag.delta[1])

    def has_drag_complete(self):
        '''
        Return a True if we are in a drag that has completed.
        '''
        return self.drag and (self.drag.type == self.drag.COMPLETE)

    def clear_drag(self):
        '''
        Clear a drag.
        '''
        self.drag = None
