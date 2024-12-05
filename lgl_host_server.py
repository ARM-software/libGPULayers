# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024 Arm Limited
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------

# This module implements a host server that provides services over the network
# to a layer running on a remote device.
#
# Run with ...
#    adb reverse localabstract:lglcomms tcp:63412
#

import sys
import threading

import lglpy.server
import lglpy.service_test
import lglpy.service_log

def main():
    # Create a server instance
    server = lglpy.server.CommsServer(63412)

    # Register all the services with it
    print(f'Registering host services:')
    test_service = lglpy.service_test.TestService()
    endpoint_id = server.register_endpoint(test_service)
    print(f'  - [{endpoint_id}] = {test_service.get_service_name()}')

    log_service = lglpy.service_log.LogService()
    endpoint_id = server.register_endpoint(log_service)
    print(f'  - [{endpoint_id}] = {log_service.get_service_name()}')
    print()

    # Start it running
    serverThread = threading.Thread(target=server.run)
    serverThread.start()

    # Press to exit
    input("Press any key to exit ...")
    server.stop()

    return 0


if __name__ == '__main__':
    sys.exit(main())
