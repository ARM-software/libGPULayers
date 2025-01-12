# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2019-2025 Arm Limited
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
This module implements a simple interactive command line menu that can
present a list of options and prompt the user to select one.
'''

import math
from typing import Optional


def get_input(text: str) -> str:
    '''
    Wrapper around input() so that it can be mocked for testing.

    Args:
       text: The text to display as a prompt.
    '''
    return input(text)


def select_from_menu(title: str, options: list[str]) -> Optional[int]:
    '''
    Prompt user to select from an on-screen menu.

    If the option list contains only a single option it will be auto-selected.

    Args:
        title: The title string.
        options: The list of options to present.

    Returns:
        The selected list index, or None if no selection made.
    '''
    assert len(options) > 0, 'No menu options provided'

    if len(options) == 1:
        print(f'Select a {title}')
        print(f'    Auto-selected {options[0]}\n')
        return 0

    selection = None
    while True:
        try:
            # Print the menu
            print(f'Select a {title}')
            chars = int(math.log10(len(options))) + 1
            for i, entry in enumerate(options):
                print(f'    {i+1:{chars}}) {entry}')

            print(f'    {0:{chars}}) Exit menu')

            # Process the response
            response = int(get_input('\n    Select entry: '))
            if response == 0:
                return None

            if 0 < response <= len(options):
                selection = response - 1
                break

            raise ValueError()

        except ValueError:
            print(f'\n    Enter a value between 0 and {len(options)}\n')

    print('')
    return selection
