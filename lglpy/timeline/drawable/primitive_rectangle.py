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
This module contains code for manipulating and interacting with basic
rectangular regions.
'''


class PrimitiveRectangle:
    '''
    Stores position and size of an axis-aligned rectangle.

    To enable efficient use in high-performance parts of the rendering code we
    store min and max, as well as the width and height.

    Attributes:
        min_x: minimum X coordinate (inclusive).
        min_y: minimum Y coordinate (inclusive).
        max_x: maximum X coordinate (inclusive).
        max_y: maximum Y coordinate (inclusive).
        w: width of the primitive.
        h: height of the primitive.
    '''

    __slots__ = ('min_x', 'max_x', 'min_y', 'max_y', 'w', 'h')

    def __init__(self, pos: list[int], dim: list[int]):
        '''
        Create a new primitive rectangle.

        Args:
            pos: position of the minimum corner of the rectangle.
            dim: width and height dimensions of this rectangle.
        '''
        self.min_x = float(pos[0])
        self.max_x = float(pos[0] + dim[0])

        self.min_y = float(pos[1])
        self.max_y = float(pos[1] + dim[1])

        self.w = float(dim[0])
        self.h = float(dim[1])

    def extend_rect(self, rect) -> None:
        '''
        Enlarge the size of this rectangle to enclose the passed rectangle.

        Args:
            rect: the rectangle to enclose.
        '''
        self.min_x = min(self.min_x, rect.min_x)
        self.max_x = max(self.max_x, rect.max_x)

        self.min_y = min(self.min_y, rect.min_y)
        self.max_y = max(self.max_y, rect.max_y)

        self.w = self.max_x - self.min_x
        self.h = self.max_y - self.min_y

    def intersects(self, other) -> bool:
        '''
        Test whether this rectangle intersects another.

        Args:
            other: the rectangle to intersect.

        Returns:
            True if there is an intersection, False otherwise.
        '''
        return (other.min_x <= self.max_x) and \
               (other.max_x >= self.min_x) and \
               (other.min_y <= self.max_y) and \
               (other.max_y >= self.min_y)

    def is_enclosed_by(self, other) -> bool:
        '''
        Test whether this rectangle is totally inside another.

        Args:
            other: the other rectangle to test.

        Returns:
            True if totally enclosed, False otherwise.
        '''
        return (other.min_x <= self.min_x) and \
               (other.max_x >= self.max_x) and \
               (other.min_y <= self.min_y) and \
               (other.max_y >= self.max_y)

    def is_hit_by(self, x: int, y: int) -> bool:
        '''
        Test whether the specified point is inside this rectangle.

        Args:
            x: test X coordinate.
            y: test Y coordinate.

        Returns:
            True if point is inside the rectangle, False otherwise.
        '''
        return (self.min_x <= x <= self.max_x) and \
               (self.min_y <= y <= self.max_y)

    def __str__(self) -> str:
        '''
        Return a debug string representation of this primitive box.

        Returns:
            A debug string.
        '''
        x_str = f'X: {self.min_x}:{self.max_x} [{self.w}]'
        y_str = f'Y: {self.min_y}:{self.max_y} [{self.h}]'
        return f'{x_str} {y_str}'
