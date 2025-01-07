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
This module contains a number of basic abstract rendering constants and
primitives.
'''

import sys
import math

import cairo


WHITE = (1.00, 1.00, 1.00, 1.00)
'''Constant code for opaque white'''

BLACK = (0.00, 0.00, 0.00, 1.00)
'''Constant code for opaque black'''

RED = (1.00, 0.00, 0.00, 1.00)
'''Constant code for opaque red'''

GREEN = (0.00, 1.00, 0.00, 1.00)
'''Constant code for opaque green'''

BLUE = (0.00, 0.00, 1.00, 1.00)
'''Constant code for opaque blue'''

if sys.platform == 'win32':
    FONT = ('Consolas', cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
    ''' Constant code for Windows font style'''
else:
    FONT = ('sans', cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
    ''' Constant code for Linux font style'''


class Drawable:
    '''
    An abstract base class for a drawable object.

    Attributes:
        style: Rendering style for this object.
    '''

    __slots__ = ('style',)

    def __init__(self, style):
        '''
        Create a new drawable.

        Args:
            style: Rendering style for this object.
        '''
        self.style = style

    def set_style(self, style) -> None:
        '''
        Change the style of this object.

        Args:
            style: Rendering style for this object.
        '''
        self.style = style

    def draw(self, gc):
        '''
        Render this object to a Cairo graphics context.

        Subclasses must provide an implementation of this function.

        Args:
            gc: Cairo graphics context
        '''
        del gc
        assert False, f'Draw function for {self.__class__.__name__} missing'

    @staticmethod
    def rt00(x: float) -> float:
        '''
        Round x down to an integer boundary.

        Args:
            x: The number to round.

        Returns:
            The rounded value.
        '''
        return float(int(x))

    @staticmethod
    def rt05(x: float) -> float:
        '''
        Round x to the nearest n.5 boundary.

        This is useful when placing pixel-width lines in Cairo, as you want to
        render down the middle of a pixel to ensure sharp lines that do not
        cross pixel boundaries.

        Args:
            x: The number to round.

        Returns:
            The rounded value.
        '''
        return float(int(x)) + 0.5


class DrawableLabel(Drawable):
    '''
    An abstract base class for a drawable with text label.

    To allow rendering to test labels for on-screen fit, each instance can
    store the canvas-space extents of the label when using the given style.
    Calculating extents needs a Cairo graphics context, so they are computed
    and cached when first drawn.

    TODO: Change to make this a single string and make parent store two labels?

    Attributes:
        label: List of lines making up the label.
        line_extents: List of width extents for each line.
        total_extents: Total extents for all lines.
    '''

    __slots__ = ('label', 'line_extents', 'line_height', 'total_extents')

    def __init__(self, style, label):
        '''
        Created a new drawable label.

        Args:
            style: Rendering style for this object.
            label: Full label text string, may be None
        '''
        super().__init__(style)

        self.label = []

        if label:
            self.label = label.split('\n')

        self.line_extents = None
        self.line_height = None
        self.total_extents = None

    def set_style(self, style):
        '''
        Change the style of this object.

        Args:
            style: Style`
                The rendering style to use for this object.
        '''
        # Invalidate the label extent cache if the font changed
        if self.style.font != style.font:
            self.line_extents = None
            self.total_extents = None

        super().set_style(style)

    def compute_label_extents(self, gc) -> None:
        '''
        Compute the canvas-space extents of the text label.

        Args:
            gc: Cairo graphics context.
        '''
        if self.total_extents is None:
            self.style.bind_font(gc)

            # Compute label height based on the font metrics line height to
            # ensure a stable baseline, independent of the label content
            asc, des = gc.font_extents()[0:2]
            self.line_height = math.ceil(asc - (des / 2) + 2)
            h = self.line_height * len(self.label)

            # Compute label width based on the content of the label
            self.line_extents = [gc.text_extents(x)[2] for x in self.label]
            self.total_extents = (max(self.line_extents), h)

    def fits_centered(self, gc, width, padding) -> bool:
        '''
        Test of the label that fits in the given on-screen width.

        Args:
            gc: Cairo graphics context
            width: Available width in pixels.
            padding: Desired padding in pixels.

        Returns:
            True if the label fits, False otherwise.
        '''
        target_width = width - 2 * padding
        self.compute_label_extents(gc)
        return self.total_extents[0] <= target_width

    def draw_centered(self, gc, pos, dim) -> None:
        '''
        Draw the label on the screen.

        Args:
            gc: Cairo graphics context
            pos: Origin on canvas pixels.
            dim: Space in canvas pixels.
        '''
        lh = self.line_height
        pad_y = (dim[1] - self.total_extents[1]) * 0.5 - 1

        for index, (text, lw) in enumerate(zip(self.label, self.line_extents)):
            label_x = pos[0] + dim[0] * 0.5 - lw * 0.5
            label_y = pos[1] + ((index + 1) * lh) + pad_y

            gc.move_to(label_x, label_y)
            gc.show_text(text)
