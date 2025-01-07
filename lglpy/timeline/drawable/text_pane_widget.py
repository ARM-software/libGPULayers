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
A simple multi-line text widget.
'''

from lglpy.timeline.drawable.primitive_rectangle import PrimitiveRectangle


class TextPaneWidget:
    '''
    A drawable widget which contains multiple lines of text.

    Attributes:
        cs: canvas-space position.
        style: visual style for the widget.
        text: current text string, or None if not set.
    '''

    def __init__(self, cs_pos, cs_dim, style, text=None):
        '''
        Create a new text pane widget.

        Args:
            cs_pos: position in canvas-space.
            cs_dim: width and height dimensions in canvas-space
            style: visual style to use for this widget.
            text: initial text string, or None if not set.
        '''
        self.cs = PrimitiveRectangle(cs_pos, cs_dim)
        self.text = text
        self.style = style

    def update_cs(self, cs_pos, cs_dim):
        '''
        Set the canvas-space coordinates of this object.

        Args:
            cs_pos: position in canvas-space.
            cs_dim: width and height dimensions in canvas-space
        '''
        self.cs = PrimitiveRectangle(cs_pos, cs_dim)

    def set_text(self, text):
        '''
        Set the text of this object.

        Args:
            text: user string, or a stringizable object.
        '''
        self.text = str(text)

    def draw(self, gc):
        '''
        Draw this widget.

        Args:
            gc: Cairo graphics context.
        '''
        cs = self.cs

        # Clip the rendering context to the extents of this widget
        gc.rectangle(cs.min_x, cs.min_y, cs.w, cs.h)
        gc.clip()

        # Perform generic configuration of the rendering context
        if self.style.bind_font(gc):
            # Get the line advance from the font specification
            line_height = gc.font_extents()[2]
            x = self.cs.min_x + 5
            y = self.cs.min_y + line_height

            lines = self.text.splitlines()
            for line in lines:
                gc.move_to(x, y)
                gc.show_text(line)
                y += line_height
