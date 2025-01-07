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
A TimelineViewport defines a visible time-range of a 2D world-space,
and the corresponding region of canvas-space coordinates that it is mapped on
to. It provides a useful set of transform functions to convert between the
two coordinate spaces, given the current viewport configuration.

TODO: Move culling out of this somewhere else. It really belongs in the
DrawableChannel.
'''

from lglpy.timeline.drawable.primitive_rectangle import PrimitiveRectangle


class TimelineViewport:
    '''
    A visible region of world-space which is mapped on to a region of
    canvas-space coordinates.

    Attributes:
        ws: the world-space viewport.
        cs: the canvas-space viewport.
        coverage_cull_enabled: True if canvas coverage culling is allowed.
        coverage_cull_next_ws_x: next world-space X coordinate for cover cull.
        coverage_cull_next_cs_x: next canvas-space X coordinate for cover cull.
        scale_ws_to_cs_x: scaling factor to convert X WS to CS.
        scale_ws_to_cs_y: scaling factor to convert Y WS to CS.
        scale_cs_to_ws_x: scaling factor to convert X CS to WS.
        scale_cs_to_ws_y: scaling factor to convert Y CS to WS.
    '''

    __slots__ = (
        'ws', 'cs',
        'scale_ws_to_cs_x', 'scale_ws_to_cs_y',
        'scale_cs_to_ws_x', 'scale_cs_to_ws_y',
        'coverage_cull_enabled',
        'coverage_cull_next_ws_x', 'coverage_cull_next_cs_x'
    )

    def __init__(self, ws_pos, ws_dim, cs_pos, cs_dim):
        '''
        Create a new instance.

        Args:
            ws_pos: X and Y coordinate in world-space.
            ws_dim: width and height dimensions in world-space.
            cs_pos: X and Y coordinate in canvas-space.
            cs_dim: width and height dimensions in canvas-space.
        '''
        self.ws = PrimitiveRectangle(ws_pos, ws_dim)
        self.cs = PrimitiveRectangle(cs_pos, cs_dim)

        self.coverage_cull_enabled = False
        self.coverage_cull_next_ws_x = 0
        self.coverage_cull_next_cs_x = 0

        self.scale_ws_to_cs_x = None
        self.scale_ws_to_cs_y = None
        self.scale_cs_to_ws_x = None
        self.scale_cs_to_ws_y = None
        self.update_derived()

    def update_ws(self, ws_pos, ws_dim):
        '''
        Update the world-space viewport size, and any derived settings.

        Args:
            ws_pos: X and Y coordinate in world-space.
            ws_dim: width and height dimensions in world-space.
        '''
        self.ws = PrimitiveRectangle(ws_pos, ws_dim)
        self.update_derived()

    def update_cs(self, cs_pos, cs_dim):
        '''
        Update the canvas-space viewport size, and any derived settings.

        Args:
            cs_pos: X and Y coordinate in canvas-space.
            cs_dim: width and height dimensions in canvas-space.
        '''
        self.cs = PrimitiveRectangle(cs_pos, cs_dim)
        self.update_derived()

    def update_derived(self):
        '''
        Update any of the derived scaling factors after a position update.
        '''
        # Calculate scale multipliers for each axis
        self.scale_ws_to_cs_x = self.cs.w / self.ws.w
        self.scale_ws_to_cs_y = self.cs.h / self.ws.h

        self.scale_cs_to_ws_x = self.ws.w / self.cs.w
        self.scale_cs_to_ws_y = self.ws.h / self.cs.h

        # Reset canvas coverage culling
        self.coverage_cull_next_ws_x = 0
        self.coverage_cull_next_cs_x = 0

    def enable_coverage_culling(self, enable):
        '''
        Enable the coverage culling algorithm.

        This must be called whenever a drawable sequence with a new Y value
        is rendered, even if the scheme is already enabled, in order to reset
        the X value.

        Args:
            enable: True if coverage culling is enabled, False otherwise.
        '''
        self.coverage_cull_enabled = enable
        self.coverage_cull_next_ws_x = 0
        self.coverage_cull_next_cs_x = 0

    def update_coverage_culling(self, last_cs_x):
        '''
        Update the coverage of the canvas within the current channel.

        Args:
            last_cs_x: the max X extent of the previously object draw.
        '''
        if not self.coverage_cull_enabled:
            return

        # Save this to avoid overlap in canvas-space
        self.coverage_cull_next_cs_x = last_cs_x + 1

        # Save this to allow fast culling
        cs_delta_x = last_cs_x - self.cs.min_x + 1
        ws_delta_x = cs_delta_x * self.scale_cs_to_ws_x
        self.coverage_cull_next_ws_x = self.ws.min_x + int(ws_delta_x)

    def is_object_visible(self, drawable):
        '''
        Query if the drawable is visible, given the current settings.

        Settings include viewport and culling.

        Args:
            drawable: query if this object is visible or not.

        Returns: bool
            True if visible, another value otherwise.
        '''
        visible = (self.coverage_cull_next_ws_x <= drawable.ws.max_x) and \
                  (self.ws.intersects(drawable.ws))
        return visible

    def transform_ws_to_cs_x(self, x, snap=1):
        '''
        Compute canvas-space X corresponding to a world-space X value.

        Args:
            x: X coordinate in world-space.
            snap: snap mode:
                - 0: no snap.
                - 1: snap to nearest {n}.5 middle of pixel value.
                - 2: snap to nearest {n}.0 edge of pixel value.

        Returns:
            The canvas-space coordinate.
        '''
        cs_x = float(x - self.ws.min_x) * self.scale_ws_to_cs_x

        if snap == 1:
            cs_x = float(int(cs_x)) + 0.5
        elif snap == 2:
            cs_x = float(int(cs_x))

        # Offset by the current widget offsets
        cs_x = cs_x + self.cs.min_x

        # Jump to the next pixel in the CC culling scheme
        # TODO: This seems odd here - move elsewhere!
        if self.coverage_cull_enabled:
            cs_x = max(self.coverage_cull_next_cs_x, cs_x)

        return cs_x

    def transform_ws_to_cs(self, x, y, snap=1):
        '''
        Compute canvas-space corresponding to a world-space value.

        Args:
            x: X coordinate in world-space.
            y: Y coordinate in world-space.
            snap: snap mode:
                - 0: no snap.
                - 1: snap to nearest {n}.5 middle of pixel value.
                - 2: snap to nearest {n}.0 edge of pixel value.

        Returns:
            The canvas-space coordinate.
        '''
        cs_x = float(x - self.ws.min_x) * self.scale_ws_to_cs_x
        cs_y = y

        if snap == 1:
            cs_x = float(int(cs_x)) + 0.5
            cs_y = float(int(cs_y)) + 0.5
        elif snap == 2:
            cs_x = float(int(cs_x))
            cs_y = float(int(cs_y))

        # Offset by the current plugin offsets
        cs_x = cs_x + self.cs.min_x
        cs_y = cs_y + self.cs.min_y

        # Jump to the next pixel in the CC culling scheme
        # TODO: This seems odd here - move elsewhere!
        if self.coverage_cull_enabled:
            cs_x = max(self.coverage_cull_next_cs_x, cs_x)

        return (cs_x, cs_y)

    def transform_cs_to_ws_x(self, x):
        '''
        Compute world-space coordinates corresponding to a single X value.

        Args:
            x: X coordinate in canvas-space.

        Returns:
            The world-space coordinate.
        '''
        cs = self.cs
        ws = self.ws
        ws_x = int(float(x - cs.min_x) * self.scale_cs_to_ws_x) + ws.min_x
        return ws_x

    def transform_cs_to_ws(self, x, y):
        '''
        Compute world-space corresponding to a canvas-space value.

        Args:
            x: X coordinate in canvas-space.
            y: Y coordinate in canvas-space.

        Returns:
            The world-space coordinate.
        '''
        cs = self.cs
        ws = self.ws
        ws_x = int(float(x - cs.min_x) * self.scale_cs_to_ws_x) + ws.min_x
        ws_y = y
        return (ws_x, ws_y)

    def __str__(self):
        '''
        Return a debug string representation of this viewport.
        '''
        ret = (
            'Viewport:',
            f'    WS: {self.ws}',
            f'    CS: {self.cs}'
        )

        return '\n'.join(ret)
