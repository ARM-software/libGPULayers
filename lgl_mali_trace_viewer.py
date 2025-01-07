#!/usr/bin/env python3
# =============================================================================
#  This confidential and proprietary software may be used only as authorized by
#  a licensing agreement from Arm Limited.
#       (c) Copyright 2014-2024 Arm Limited
#  The entire notice above must be reproduced on all authorized copies and
#  copies may only be made to the extent permitted by a licensing agreement
#  from Arm Limited.
# =============================================================================
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
    sys.exit(main())
