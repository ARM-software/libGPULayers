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


def get_open_filechoice(parent, filter_group, filter_patterns):
    r"""
    Synchronously pop up a file chooser dialog to select a file for opening.

    Args:
        parent: Parent window on which the dialog is centered.
        filter_group: Name of group for filtering files.
        filter_patterns: List of accepted file name patterns, e.g. '*.txt'.

    Return:
        The file path if selected, or None if cancelled by the user.
    """
    buttons = (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
               Gtk.STOCK_OPEN, Gtk.ResponseType.OK)

    file_chooser = Gtk.FileChooserDialog(
        "Open File ...",
        action=Gtk.FileChooserAction.OPEN,
        buttons=buttons,
        parent=parent)

    file_filter = Gtk.FileFilter()
    file_filter.set_name("All files")
    file_filter.add_pattern("*")
    file_chooser.add_filter(file_filter)

    file_filter = Gtk.FileFilter()
    file_filter.set_name(filter_group)
    for pattern in filter_patterns:
        file_filter.add_pattern(pattern)
    file_chooser.add_filter(file_filter)
    file_chooser.set_filter(file_filter)

    response = file_chooser.run()
    file_name = file_chooser.get_filename()
    file_chooser.destroy()

    # If the user hit cancel then do nothing here and return
    if response != Gtk.ResponseType.OK:
        return None

    return file_name
