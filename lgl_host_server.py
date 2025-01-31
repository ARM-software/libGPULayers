#!/bin/env python3
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
This script implements a simple network server that provides services to
layer drivers running on the target device over a simple network protocol.

Android devices using layers can tunnel their connection using adb reverse
to forward a Unix domain socket on the device to a TCP socket on the host.
This is done automatically by the script.
'''

import argparse
import subprocess as sp
import sys
import threading
from typing import Any

from lglpy.android.adb import ADBConnect
from lglpy.comms import server
from lglpy.comms import service_gpu_timeline
from lglpy.comms import service_test
from lglpy.comms import service_log


def parse_cli() -> argparse.Namespace:
    '''
    Parse the command line.

    Returns:
        An argparse results object.
    '''
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--test', action='store_true', default=False,
        help='enable the communications unit test helper service')

    parser.add_argument(
        '--android-port', '-A', type=int, default=0,
        help='enable adb reverse on the specified port for network comms')

    parser.add_argument(
        '--timeline', '-T', type=str, default=None,
        help='file path to save timeline metadata to to after a run')

    return parser.parse_args()


def main() -> int:
    '''
    The script main function.

    Returns:
        The process exit code.
    '''
    args = parse_cli()

    # Create a server instance
    svr = server.CommsServer(args.android_port)
    print(f'Server using host port {svr.port}\n')

    # Register all the services with it
    print('Registering host services:')

    service: Any

    if args.test:
        service = service_test.TestService()
        endpoint_id = svr.register_endpoint(service)
        print(f'  - [{endpoint_id}] = {service.get_service_name()}')

    service = service_log.LogService()
    endpoint_id = svr.register_endpoint(service)
    print(f'  - [{endpoint_id}] = {service.get_service_name()}')

    if args.timeline:
        service = service_gpu_timeline.GPUTimelineService(args.timeline, True)
        endpoint_id = svr.register_endpoint(service)
        print(f'  - [{endpoint_id}] = {service.get_service_name()}')

    print()

    # Start it running
    svr_thread = threading.Thread(target=svr.run, daemon=True)
    svr_thread.start()

    # Configure Android adb reverse on the specified port
    conn = ADBConnect()
    try:
        conn.adb(
            'reverse',
            'localabstract:lglcomms',
            f'tcp:{svr.port}')

    except sp.CalledProcessError:
        print('ERROR: Could not setup Android network comms')
        return 1

    # Press to exit
    try:
        input('Press any key to exit ...\n\n')
    except KeyboardInterrupt:
        print('Exiting ...')
        return 0

    return 0


if __name__ == '__main__':
    sys.exit(main())
