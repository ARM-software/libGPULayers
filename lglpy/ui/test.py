
# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2025 Arm Limited
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
This module implements tests for the lglpy.ui package.
'''

import sys
import unittest
from unittest import mock

from . import console


class ConsoleTestMenu(unittest.TestCase):
    '''
    Tests for the console UI for simple list item menu selection.
    '''

    @staticmethod
    def make_options(count: int) -> list[str]:
        '''
        Make a list of options ...
        '''
        return [f'Option {i + 1}' for i in range(0, count)]

    @mock.patch('lglpy.ui.console.get_input', side_effect='0')
    def test_menu_cancel(self, mock_get_input):
        '''
        Test the user cancelling an option in the menu.
        '''
        del mock_get_input
        options = self.make_options(3)
        selected_option = console.select_from_menu('Title', options)
        self.assertEqual(selected_option, None)

    @mock.patch('lglpy.ui.console.get_input', side_effect=['1'])
    def test_menu_select_1(self, mock_get_input):
        '''
        Test the user entering a valid value in the menu.
        '''
        del mock_get_input
        options = self.make_options(3)
        selected_option = console.select_from_menu('Title', options)
        self.assertEqual(selected_option, 0)

    @mock.patch('lglpy.ui.console.get_input', side_effect=['4', '2'])
    def test_menu_select_bad_range(self, mock_get_input):
        '''
        Test the user entering an out-of-bounds value in the menu.
        '''
        options = self.make_options(3)
        selected_option = console.select_from_menu('Title', options)

        self.assertEqual(mock_get_input.call_count, 2)
        self.assertEqual(selected_option, 1)

    @mock.patch('lglpy.ui.console.get_input', side_effect=['fox', '3'])
    def test_menu_select_bad_formnt(self, mock_get_input):
        '''
        Test the user entering a non-integer value in the menu.
        '''
        options = self.make_options(3)
        selected_option = console.select_from_menu('Title', options)
        self.assertEqual(mock_get_input.call_count, 2)
        self.assertEqual(selected_option, 2)


def main():
    '''
    The main function.

    Returns:
        int: The process return code.
    '''
    results = unittest.main(exit=False)
    return 0 if results.result.wasSuccessful() else 1


if __name__ == '__main__':
    sys.exit(main())
