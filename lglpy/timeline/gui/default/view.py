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
The default view is the view shown when the tool first boots.
'''


from lglpy.timeline.gui.view import View
from lglpy.timeline.drawable.style import Style
from lglpy.timeline.drawable.text_pane_widget import TextPaneWidget


class DefaultView(View):
    '''
    This `View` is the view first shown when the tool boots. It is not
    intended to show any useful data, but a summary of the data loaded, and
    perhaps a visually interesting splash screen.
    '''

    MENU_NAME = "Homescreen"
    MENU_REQUIRES_DATA_FILE = False

    def __init__(self, window, css):
        '''
        Instantiate a new version of this view.
        '''
        super().__init__(window, css)
        text = "Select a data presentation from the Views menu\n\n"
        text += "Please raise any issues the GitHub issue tracker"
        style = Style.css_factory(css["homev-core"])
        self.info_widget = TextPaneWidget((0, 0), (600, 100), style, text)

    def draw_view(self, draw_pos, draw_dim):
        '''
        Render this view.

        See `View` superclass for documentation.
        '''
        gc = super().draw_view(draw_pos, draw_dim)
        self.info_widget.draw(gc)
