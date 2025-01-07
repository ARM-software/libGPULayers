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
A simple status bar widget that will show messages for a limited time before
clearing them.
'''

import gi
gi.require_version('Gtk', '3.0')
# pylint: disable=wrong-import-position
from gi.repository import Gtk, GObject


class TimedStatusbar(Gtk.Alignment):
    '''
    Present informative single line messages to the user in a status bar
    widget, removing them after a time interval as passed (or they are
    overwritten by a newer message).

    Unlike the full Gtk.Statusbar implementation this class only supports a
    single string (no stack), and uses a global namespace (no contexts).
    '''

    def __init__(self):
        '''
        Create a new widget.
        '''
        super().__init__()
        self.label = Gtk.Label("")
        self.label.set_justify(Gtk.Justification.LEFT)
        self.label.set_alignment(0, 0)
        self.label.show()
        self.add(self.label)
        self.set_padding(2, 2, 5, 5)  # (t, b, l, r)
        self.timer = None

    def log(self, message, timeout=5000):
        '''
        Show a new status log entry.

        Args:
            message: text message to show.
            timeout: timeout (in milliseconds), or 0 to show indefinitely.
        '''
        # Clear any existing time belonging to the previous message
        if self.timer:
            GObject.source_remove(self.timer)
            self.timer = None

        # Update and set timers for the new message
        self.label.set_label(message)

        if timeout:
            self.timer = GObject.timeout_add(timeout, self.clear)

    def clear(self):
        '''
        Clear the status bar instantly.

        This function can be used as a GTK timer callback, and returns False to
        stop the timer after a single iteration.

        Returns:
            Always returns False to stop timer from looping.
        '''
        self.label.set_label("")
        self.timer = None
        return False
