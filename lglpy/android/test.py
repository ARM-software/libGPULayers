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
This module implements tests for the lglpy.android package. Running this
test suite requires an Android device with at least one debuggable application
installed to be connected to the host PC with an authorized adb connection.
'''

import contextlib
import os
import re
import sys
import tempfile
import unittest

from .adb import ADBConnect
from .utils import AndroidUtils

SLOW_TESTS = False  # Set to True to enable slot tests, False to skip them


@contextlib.contextmanager
def NamedTempFile():  # pylint: disable=invalid-name
    '''
    Creates a context managed temporary file that can be used with external
    subprocess.

    On context entry this yields the file name, on exit it deletes the file.

    Yields:
        The name of the temporary file.
    '''
    name = None

    try:
        f = tempfile.NamedTemporaryFile(delete=False)
        name = f.name
        f.close()
        yield name

    finally:
        if name:
            os.unlink(name)


class AndroidTestNoDevice(unittest.TestCase):
    '''
    This set of tests validates execution of global commands that can run
    without a specific device attached/nominated.
    '''
    DEVICES_RE = re.compile(r'^([A-Za-z0-9]+)\t(device|offline|unauthorized)$')

    def validate_devices(self, result):
        '''
        Validate a well formed `adb devices` response.
        '''
        lines = result.splitlines()

        # Validate fixed preamble and postamble
        self.assertEqual(lines[0], 'List of devices attached')
        self.assertEqual(lines[-1], '')

        # Validate that we have at least one connected device
        self.assertGreater(len(lines), 2)

        # Validate per-device fields are well formed
        for line in lines[1:-1]:
            self.assertIsNotNone(self.DEVICES_RE.match(line))

    def test_sync(self):
        '''
        Test direct invocation of adb devices.
        '''
        device = ADBConnect()
        result = device.adb('devices')
        self.validate_devices(result)

    def test_sync_shell(self):
        '''
        Test host shell invocation of adb devices.
        '''
        with NamedTempFile() as file_name:
            device = ADBConnect()
            result = device.adb('devices', '>', file_name, shell=True)

            # We used the shell to redirect to file so this should be empty
            self.assertEqual(result, '')

            # Read the file and validate that it is correct
            with open(file_name, 'r', encoding='utf-8') as handle:
                data = handle.read()
                self.validate_devices(data)

    def test_sync_quote(self):
        '''
        Test direct adb invocation that needs device-side quoting.
        '''
        device = ADBConnect()
        result = device.adb('shell', 'echo', 'a | echo', quote=True)
        self.assertEqual(result, 'a | echo\n')

    @unittest.skipIf(os.name == 'nt', 'Not supported on Windows')
    def test_sync_shell_quote(self):
        '''
        Test host shell invocation of adb shell that needs host-side quoting.
        '''
        device = ADBConnect()
        result = device.adb('shell', 'echo', 'a | echo', shell=True)
        self.assertEqual(result, 'a | echo\n')

    def test_async(self):
        '''
        Test direct invocation of adb devices.
        '''
        device = ADBConnect()
        process = device.adb_async('devices')

        # We didn't request pipe so these should be empty
        stdout, _ = process.communicate()
        self.assertIsNone(stdout)

    def test_async_quote(self):
        '''
        Test direct adb invocation that needs device-side quoting.
        '''
        device = ADBConnect()
        process = device.adb_async(
            'shell', 'touch', '/data/local/tmp/a b.txt', quote=True)

        # We used the shell to redirect to file so this should be empty
        stdout, _ = process.communicate()
        self.assertIsNone(stdout)

        # Assert that the file was correctly created by deleting it
        process = device.adb(
            'shell', 'rm', '/data/local/tmp/a b.txt', quote=True)

    def test_async_shell_pipe(self):
        '''
        Test host shell invocation of adb devices.
        '''
        with NamedTempFile() as file_name:
            device = ADBConnect()
            process = device.adb_async(
                'devices', '>', file_name, shell=True, pipe=True)

            # We used the shell to redirect to file so this should be empty
            stdout, _ = process.communicate()
            self.assertEqual(stdout, '')

            # Read the file and validate that it is correct
            with open(file_name, 'r', encoding='utf-8') as handle:
                data = handle.read()
                self.validate_devices(data)

    def test_async_pipe(self):
        '''
        Test direct invocation of adb devices.
        '''
        device = ADBConnect()
        process = device.adb_async('devices', pipe=True)

        # We requested pipe so validate output
        stdout, _ = process.communicate()
        self.validate_devices(stdout)

    def test_util_device_list(self):
        '''
        Test helper to list devices.
        '''
        devices = AndroidUtils.get_devices()

        # Test that we get at least one good device returned
        self.assertGreater(len(devices[0]), 0)
        self.assertGreaterEqual(len(devices[1]), 0)


class AndroidTestDefaultDevice(unittest.TestCase):
    '''
    This set of tests validates execution of device-level commands that
    require adb to have a valid implicit default device connected.
    '''

    @unittest.skipIf(not SLOW_TESTS, 'Slow tests not enabled')
    def test_util_package_list_full(self):
        '''
        Test helper to list packages
        '''
        conn = ADBConnect()

        packages = AndroidUtils.get_packages(conn, False, False)
        all_packages = len(packages)

        packages = AndroidUtils.get_packages(conn, False, True)
        main_packages = len(packages)

        packages = AndroidUtils.get_packages(conn, True, True)
        debug_main_packages = len(packages)

        # Test that we get at least one package returned for each case
        self.assertGreater(all_packages, 0)
        self.assertGreater(main_packages, 0)
        self.assertGreater(debug_main_packages, 0)

        # Test that list length reduces each time as we add filters
        self.assertGreater(all_packages, main_packages)
        self.assertGreater(main_packages, debug_main_packages)

    def test_util_package_list(self):
        '''
        Test helper to list packages
        '''
        conn = ADBConnect()

        packages = AndroidUtils.get_packages(conn, False, False)
        all_packages = len(packages)

        packages = AndroidUtils.get_packages(conn, True, True)
        debug_main_packages = len(packages)

        # Test that we get at least one package returned for each case
        self.assertGreater(all_packages, 0)
        self.assertGreater(debug_main_packages, 0)

        # Test that list length reduces each time as we add filters
        self.assertGreater(all_packages, debug_main_packages)

    def test_util_os_version(self):
        '''
        Test helper to get OS version.
        '''
        conn = ADBConnect()
        version = AndroidUtils.get_os_version(conn)
        self.assertIsNotNone(version)

    def test_util_os_sdk_version(self):
        '''
        Test helper to get OS SDK version.
        '''
        conn = ADBConnect()
        version = AndroidUtils.get_os_sdk_version(conn)
        self.assertGreater(version, 10)

    def test_util_device_model(self):
        '''
        Test helper to get device vendor and model version.
        '''
        conn = ADBConnect()
        version = AndroidUtils.get_device_model(conn)

        # Test that we have a tuple and both values are non-zero
        self.assertIsNotNone(version)
        self.assertTrue(version[0])
        self.assertTrue(version[1])


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
