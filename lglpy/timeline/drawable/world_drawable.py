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
This module contains the base classes for drawable primitives onto a
Cairo-backed rendering canvas. The classes in this module are defined in terms
of world-space coordinates, so their position must be translated into
canvas-space using a viewport before they are rendered.
'''

from lglpy.timeline.drawable.drawable import DrawableLabel
from lglpy.timeline.drawable.primitive_rectangle import PrimitiveRectangle


class WorldDrawable:
    '''
    An abstract-base class for world-space objects.

    Attributes:
        ws: position and bounding size of this object in world-space.
        user_data: arbitrary user data reference.
    '''

    __slots__ = ('ws', 'style', 'user_data')

    def __init__(self, pos, dim, style):
        '''
        Initialize a new `WorldDrawable`.

        Args:
            pos: X and Y coordinate in world-space.
            dim: width and height dimensions in world-space.
            style: visual style.
        '''
        self.ws = PrimitiveRectangle(pos, dim)
        self.style = style

        self.user_data = None


class WorldDrawableRect(WorldDrawable):
    '''
    A world-space rectangle with fill, stroke, and label. Any of these
    may be skipped by setting its color to `None` in the style.
    '''

    __slots__ = ('label', 'label_short')

    def __init__(self, pos, dim, style, label, label_short):
        '''
        Initialize a new `WorldDrawable`.

        Args:
            pos: X and Y coordinate in world-space.
            dim: width and height dimensions in world-space.
            style: visual style.
        '''
        super().__init__(pos, dim, style)

        self.label = None
        if label:
            self.label = DrawableLabel(style, label)

        self.label_short = None
        if label_short:
            self.label_short = DrawableLabel(style, label_short)

    def draw(self, gc, vp):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
            vp: viewport configuration.
        '''
        if not vp.is_object_visible(self):
            return

        x, y = vp.transform_ws_to_cs(self.ws.min_x, self.ws.min_y, 2)

        # Round based on final WS position not on WS width
        max_x, max_y = vp.transform_ws_to_cs(self.ws.max_x, self.ws.max_y, 2)

        # Calculate canvas-space width and height
        w = max_x - x + 1
        h = max_y - y + 1

        # Next pixel should be two higher (i.e. leave a gap of one pixel)
        vp.update_coverage_culling(max_x + 2)

        # Draw fill if there is one
        if self.style.bind_fill(gc):
            gc.rectangle(x, y, w, h)
            gc.fill()

        # Draw outline
        if self.style.bind_line(gc):
            gc.rectangle(x + 0.5, y + 0.5, w - 1, h - 1)
            gc.stroke()

        # Draw label if present and above minimal size
        if self.style.bind_font(gc):
            # Try the full label
            if self.label.fits_centered(gc, w, 4):
                self.label.draw_centered(gc, (x, y), (w, h))
            elif self.label_short and self.label_short.fits_centered(gc, w, 4):
                self.label_short.draw_centered(gc, (x, y), (w, h))


class WorldDrawableLine(WorldDrawable):
    '''
    A world-space line-strip with a stroke.
    '''

    __slots__ = ("points",)

    def __init__(self, points, style):
        '''
        Args:
            points: list of point tuples.
            style: visual style.
        '''
        # Compute bounding box so we can perform intersection tests
        x_points = [i[0] for i in points]
        y_points = [i[1] for i in points]
        pos = (min(x_points), min(y_points))
        dim = (max(x_points) - pos[0], max(y_points) - pos[1])

        super().__init__(pos, dim, style)
        self.points = points

    def draw(self, gc, vp):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
            vp: viewport configuration.
        '''
        if (not vp.is_object_visible(self)) or (not self.style.line_color):
            return

        ws_positions = []
        for pos in self.points:
            ws_pos = vp.transform_ws_to_cs(pos[0], pos[1])
            ws_positions.append(ws_pos)

        # Draw line
        if self.style.bind_line(gc):
            for i in range(0, len(ws_positions) - 1):
                line_from = ws_positions[i]
                line_to = ws_positions[i + 1]
                gc.move_to(line_from[0], line_from[1])
                gc.line_to(line_to[0], line_to[1])
            gc.stroke()


class WorldDrawableLabel(WorldDrawable):
    '''
    A world-space label, drawn left-aligned.
    '''

    __slots__ = ("cs_offset_x",)

    def __init__(self, pos, style, label, cs_offset_x=0):
        '''
        Args:
            pos: X and Y coordinate in world-space.
            style: visual style.
            label: text label.
            cs_offset_x: canvas-space x offset, e.g. for padding.
        '''
        assert label
        dim = (200, 100)  # TODO this is a hack - needs improving
        super().__init__(pos, dim, style, label)
        self.cs_offset_x = cs_offset_x

    def draw(self, gc, vp):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
            vp: viewport configuration.
        '''
        if (not vp.is_object_visible(self)) or (not self.style.font_color):
            return

        x, y = vp.transform_ws_to_cs(self.ws.min_x, self.ws.min_y, 2)
        x = x + self.cs_offset_x

        if self.style.bind_font(gc):
            gc.move_to(x, y)
            gc.show_text(self.label)
