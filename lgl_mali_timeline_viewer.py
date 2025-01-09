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
TODO
'''

import argparse
import sys

from lglpy.timeline.gui.window import Window


def parse_cli():
    '''
    Parse the command line.

    Returns:
        Return an argparse results object.
    '''
    parser = argparse.ArgumentParser()

    parser.add_argument('-s', '--style', dest='style',
                        choices=('light', 'dark'), default='dark',
                        help='GUI skin to use')

    parser.add_argument('input', nargs='?', metavar='PERFETTO_IN',
                        type=argparse.FileType('rb'), default=None,
                        help='input Perfetto file to load')

    parser.add_argument('input2', nargs='?', metavar='GPUTL_IN',
                        type=argparse.FileType('rb'), default=None,
                        help='input GPU timeline file to load')

    args = parser.parse_args()
    return args


def main():
    '''
    Generate a coverage report on stdout.
    '''
    args = parse_cli()

    # Start the GUI - this enters the GTK message loop
    trace_file_name = None
    if args.input:
        trace_file_name = args.input.name
        args.input.close()

    metadata_file_name = None
    if args.input2:
        metadata_file_name = args.input2.name
        args.input2.close()

    Window(args.style, trace_file_name, metadata_file_name)


if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        sys.exit(0)
