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
This module contains a number of basic rendering primitives which are defined
in terms of canvas-space coordinates. The classes are:

  - CanvasDrawable: Abstract base class
  - CanvasDrawableRect: Rectangle with fill, stroke, and label
  - CanvasDrawableRectFill: Rectangle with fill, and label
'''

from lglpy.timeline.drawable.drawable import DrawableLabel


class CanvasDrawable(DrawableLabel):
    '''
    An abstract base class for an object which can be rendered to a canvas.

    Attributes:
        x: object X coordinate.
        y: object Y coordinate.
        w: object width, in pixels.
        h: object height, in pixels.
    '''

    __slots__ = ('x', 'y', 'w', 'h')

    def __init__(self, pos, dim, style, label=None):
        '''
        Create a new CanvasDrawable.

        Args:
            pos: tuple containing X and Y canvas-space coordinate.
            dim: tuple containing X and Y canvas-space dimensions.
            style: visual style.
            label: text label, or None.
        '''
        super().__init__(style, label)

        self.x, self.y = pos
        self.w, self.h = dim


class CanvasDrawableRect(CanvasDrawable):
    '''
    A canvas-space rectangle with fill, stroke, and label. Any of these may be
    skipped by setting its color to None in the style.
    '''

    __slots__ = ()

    def draw(self, gc):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
        '''
        x, y = self.x, self.y
        w, h = self.w, self.h

        # Draw fill
        if self.style.bind_fill(gc):
            gc.rectangle(x, y, w, h)
            gc.fill()

        # Draw outline
        if self.style.bind_line(gc):
            gc.rectangle(x, y, w, h)
            gc.stroke()

        # Draw label, centered in object
        if self.label and self.style.bind_font(gc):
            lw, lh = self.get_label_extents(gc)
            gc.move_to(x + w * 0.5 - lw * 0.5, y + h * 0.5 + lh * 0.5)
            gc.show_text(self.label)


class CanvasDrawableRectFill(CanvasDrawable):
    '''
    A canvas-space rectangle with fill, and label. Any of these may be skipped
    by setting its color to None in the style.

    This is useful for uses rendering a composite shape that contains a mixture
    of fill-only rectangles as well as lines or full rectangles with a stroke.
    Fill-only rectangles allow a single CSS style to be used for the entire
    composite, without needing a None stroke style.
    '''

    __slots__ = ()

    def draw(self, gc):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
        '''
        x, y = self.x, self.y
        w, h = self.w, self.h

        # Draw fill
        if self.style.bind_fill(gc):
            gc.rectangle(x, y, w, h)
            gc.fill()

        # Draw label, centered in object
        if self.label and self.style.bind_font(gc):
            lw, lh = self.get_label_extents(gc)
            gc.move_to(x + w * 0.5 - lw * 0.5, y + h * 0.5 + lh * 0.5)
            gc.show_text(self.label)


class CanvasDrawableLine(CanvasDrawable):
    '''
    A canvas-space line-strip with a stroke.
    '''

    __slots__ = ('points',)

    def __init__(self, points, style):
        '''
        Create a new CanvasDrawableLine.

        Args:
            points: list of point tuples.
            style: visual style.
        '''
        # Compute bounding box so we can perform intersection tests
        x_points = [i[0] for i in points]
        y_points = [i[1] for i in points]
        pos = (min(x_points), min(y_points))
        dim = (max(x_points) - pos[0], max(y_points) - pos[1])

        super().__init__(pos, dim, style, None)
        self.points = points

    def draw(self, gc):
        '''
        Render this object.

        Args:
            gc: Cairo graphics context.
        '''
        # Only draw if we have a style and 2 or more points
        if self.style.bind_line(gc) and len(self.points) > 1:
            last_pos = (None, None)
            for pos in self.points:
                if last_pos[0] is not None:
                    gc.move_to(*last_pos)
                    gc.line_to(*pos)
                last_pos = pos
            gc.stroke()


class CanvasDrawableLabel(DrawableLabel):
    '''
    A canvas-space label, drawn left-aligned.
    '''

    __slots__ = ()

    def draw(self, gc, x, y):
        '''
        Render this object.

        TODO: Why is this using draw-time positions, unlike the others?

        Args:
            gc: Cairo graphics context.
            x: object X coordinate.
            y: object Y coordinate.
        '''
        # Draw label
        if self.label and self.style.bind_font(gc):
            gc.move_to(x, y)
            gc.show_text(self.label)
