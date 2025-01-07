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
This module contains a utility to popup a synchronous dialog with basic a
text entry prompt.
'''

import gi
gi.require_version('Gtk', '3.0')
# pylint: disable=wrong-import-position
from gi.repository import Gtk


def get_entry_dialog(parent, title):
    '''
    Synchronously pop up a text entry dialog and wait for a response.

    Args:
        parent: parent window.
        title: dialog title.

    Returns:
        User entered string, or None if they cancelled.
    '''
    buttons = ('OK', Gtk.ResponseType.OK)
    dialog = Gtk.Dialog(title, parent, Gtk.DialogFlags.MODAL, buttons)

    entry = Gtk.Entry()
    entry.connect('activate', lambda ent, dlg, resp: dlg.response(resp),
                  dialog, Gtk.ResponseType.OK)
    dialog.vbox.pack_end(entry, True, True, 0)  # pylint: disable=no-member
    entry.show()
    response = dialog.run()
    text = entry.get_text()
    dialog.destroy()

    # User entered a response ...
    if response == Gtk.ResponseType.OK:
        return text

    # User abandoned attempt ...
    return None
