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

import os
import re
import shutil
import subprocess as sp
import sys
import tempfile
import unittest

from .adb import ADBConnect
from .utils import AndroidUtils, NamedTempFile
from .filesystem import AndroidFilesystem


SLOW_TESTS = True  # Set to True to enable slow tests, False to skip them


def get_script_relative_path(file_name: str) -> str:
    '''
    Get the host path of a script relative file.

    Args:
        file_name: The path of the file relative to this script.

    Returns:
        The path of the file on disk.
    '''
    dir_name = os.path.dirname(__file__)
    return os.path.join(dir_name, file_name)


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
        result = device.adb_run('echo', 'a | echo', quote=True)
        self.assertEqual(result, 'a | echo\n')

    @unittest.skipIf(os.name == 'nt', 'Not supported on Windows')
    def test_sync_shell_quote(self):
        '''
        Test host shell invocation of adb shell that needs host-side quoting.
        '''
        device = ADBConnect()
        result = device.adb_run('echo', 'a | echo', shell=True)
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


class AndroidTestDeviceUtil(unittest.TestCase):
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

    def test_util_package_debuggable(self):
        '''
        Test helper to get package debug status
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        all_packages = AndroidUtils.get_packages(conn, False, False)
        self.assertGreater(len(all_packages), 0)

        dbg_packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(dbg_packages), 0)

        ndbg_packages = list(set(all_packages) ^ set(dbg_packages))
        self.assertGreater(len(ndbg_packages), 0)

        # Test the package
        is_debug = AndroidUtils.is_package_debuggable(conn, ndbg_packages[0])
        self.assertFalse(is_debug)

        is_debug = AndroidUtils.is_package_debuggable(conn, dbg_packages[0])
        self.assertTrue(is_debug)

    def test_util_package_bitness(self):
        '''
        Test helper to get package ABI bitness.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)

        # Test the package
        is_32bit = AndroidUtils.is_package_32bit(conn, packages[0])
        self.assertTrue(isinstance(is_32bit, bool))

    def test_util_package_data_dir(self):
        '''
        Test helper to get package data directory on the device filesystem.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        # Test the package
        data_dir = AndroidUtils.get_package_data_dir(conn)
        self.assertTrue(data_dir)


class AndroidTestDeviceProps(unittest.TestCase):
    '''
    This set of tests validates modifications to device-level settings
    This require adb to have a valid implicit default device connected.
    '''

    def test_util_properties_modifiers(self):
        '''
        Test helper to set, get, or clear a property.
        '''
        conn = ADBConnect()
        prop = 'debug.vulkan.layers'

        # Ensure test device starts from a clear state
        success = AndroidUtils.clear_property(conn, prop)
        self.assertTrue(success)

        value = AndroidUtils.get_property(conn, prop)
        self.assertEqual(value, '')

        success = AndroidUtils.set_property(conn, prop, 'test_')
        self.assertTrue(success)

        value = AndroidUtils.get_property(conn, prop)
        self.assertEqual(value, 'test_')

        success = AndroidUtils.clear_property(conn, prop)
        self.assertTrue(success)

        value = AndroidUtils.get_property(conn, prop)
        self.assertEqual(value, '')

    def test_util_settings_modifiers(self):
        '''
        Test helper to set, get, or clear a setting.
        '''
        conn = ADBConnect()
        prop = 'enable_gpu_debug_layers'

        # Ensure test device starts from a clear state
        success = AndroidUtils.clear_setting(conn, prop)
        self.assertTrue(success)

        value = AndroidUtils.get_setting(conn, prop)
        self.assertEqual(value, None)

        success = AndroidUtils.set_setting(conn, prop, '1')
        self.assertTrue(success)

        value = AndroidUtils.get_setting(conn, prop)
        self.assertEqual(value, '1')

        success = AndroidUtils.clear_setting(conn, prop)
        self.assertTrue(success)

        value = AndroidUtils.get_setting(conn, prop)
        self.assertEqual(value, None)


class AndroidTestDeviceFilesystem(unittest.TestCase):
    '''
    This set of tests validates execution of device-level filesystem operations
    that require adb to have a valid implicit default device connected.
    '''

    HOST_DEST_DIR = 'x_test_tmp'

    def tearDown(self):
        '''
        Post-test cleanup.
        '''
        shutil.rmtree(self.HOST_DEST_DIR, True)

    def test_util_copy_to_device_tmp(self):
        '''
        Test filesystem copy to device temp directory.
        '''
        conn = ADBConnect()

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)
        device_file = f'/data/local/tmp/{test_file}'

        # Push the file
        success = AndroidFilesystem.push_file_to_tmp(conn, test_path, False)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_run('cat', device_file)
        self.assertEqual(data.strip(), 'test payload')

        # Cleanup
        success = AndroidFilesystem.delete_file_from_tmp(conn, test_file)
        self.assertTrue(success)

    def test_util_copy_to_device_tmp_exec(self):
        '''
        Test filesystem copy executable payload to device temp directory.
        '''
        conn = ADBConnect()

        test_file = 'test_data.sh'
        test_path = get_script_relative_path(test_file)
        device_file = f'/data/local/tmp/{test_file}'

        # Push the file with executable permissions
        success = AndroidFilesystem.push_file_to_tmp(conn, test_path, True)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_run(device_file)
        self.assertEqual(data.strip(), 'test payload exec')

        # Cleanup
        success = AndroidFilesystem.delete_file_from_tmp(conn, test_file)
        self.assertTrue(success)

    def test_util_copy_from_device_keep(self):
        '''
        Test filesystem copy executable payload from device temp directory.
        '''
        conn = ADBConnect()

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_tmp(conn, test_path, False)
        self.assertTrue(success)

        # Copy the file without deletion
        success = AndroidFilesystem.pull_file_from_tmp(
            conn, test_file, self.HOST_DEST_DIR, False)
        self.assertTrue(success)

        # Cleanup
        success = AndroidFilesystem.delete_file_from_tmp(conn, test_file)
        self.assertTrue(success)

    def test_util_copy_from_device_delete(self):
        '''
        Test filesystem copy executable payload from device temp directory.
        '''
        conn = ADBConnect()

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        device_path = f'/data/local/tmp/{test_file}'
        host_path = f'{self.HOST_DEST_DIR}/{test_file}'

        # Push the file
        success = AndroidFilesystem.push_file_to_tmp(conn, test_path, False)
        self.assertTrue(success)

        # Copy the file with deletion
        success = AndroidFilesystem.pull_file_from_tmp(
            conn, test_file, self.HOST_DEST_DIR, True)
        self.assertTrue(success)

        with open(host_path, 'r', encoding='utf-8') as handle:
            data = handle.read()
            self.assertEqual(data, 'test payload')

        # Check the file is deleted - this should fail
        with self.assertRaises(sp.CalledProcessError):
            conn.adb_run('ls', device_path)

    def test_util_copy_to_package(self):
        '''
        Test filesystem copy to package data directory.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas('ls', test_file)
        self.assertEqual(data.strip(), test_file)

        # Cleanup tmp - this should fail because the file does not exist
        success = AndroidFilesystem.delete_file_from_tmp(conn, test_file)
        self.assertFalse(success)

    def test_util_copy_to_package_exec(self):
        '''
        Test filesystem copy to package data directory.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = './test_data.sh'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path, True)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas(test_file)
        self.assertEqual(data.strip(), 'test payload exec')

        # Cleanup the file
        success = AndroidFilesystem.delete_file_from_package(conn, test_file)
        self.assertTrue(success)

    def test_util_rename_in_package(self):
        '''
        Test filesystem rename in package data directory.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas('ls', test_file)
        self.assertEqual(data.strip(), test_file)

        # Rename the file
        new_test_file = 'test_data_2.txt'
        success = AndroidFilesystem.rename_file_in_package(
            conn, test_file, new_test_file)
        self.assertTrue(success)

        # Validate it was moved - this should fail
        with self.assertRaises(sp.CalledProcessError):
            data = conn.adb_runas('ls', test_file)

        data = conn.adb_runas('ls', new_test_file)
        self.assertEqual(data.strip(), new_test_file)

        # Cleanup tmp - this should fail because the file does not exist
        success = AndroidFilesystem.delete_file_from_package(
            conn, new_test_file)
        self.assertTrue(success)

    def test_util_copy_from_package(self):
        '''
        Test filesystem copy from package data directory to host.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas('ls', test_file)
        self.assertEqual(data.strip(), test_file)

        # Copy the file
        with tempfile.TemporaryDirectory() as host_dir:
            host_file = os.path.join(host_dir, test_file)

            AndroidFilesystem.pull_file_from_package(
                conn, test_file, host_dir, False)

            # Read the file and validate that it is correct
            with open(host_file, 'r', encoding='utf-8') as handle:
                data = handle.read()

            self.assertEqual(data.strip(), 'test payload')

        # Cleanup the file
        success = AndroidFilesystem.delete_file_from_package(conn, test_file)
        self.assertTrue(success)

    def test_util_move_from_package(self):
        '''
        Test filesystem move from package data directory to host.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas('ls', test_file)
        self.assertEqual(data.strip(), test_file)

        # Copy the file
        with tempfile.TemporaryDirectory() as host_dir:
            host_file = os.path.join(host_dir, test_file)

            AndroidFilesystem.pull_file_from_package(
                conn, test_file, host_dir, True)

            # Read the file and validate that it is correct
            with open(host_file, 'r', encoding='utf-8') as handle:
                data = handle.read()

            self.assertEqual(data.strip(), 'test payload')

        # Cleanup the file - this should fail as we deleted the file earlier
        success = AndroidFilesystem.delete_file_from_package(conn, test_file)
        self.assertFalse(success)

    def test_util_delete_from_package(self):
        '''
        Test filesystem delete from package data directory.
        '''
        conn = ADBConnect()

        # Fetch some packages that we can use
        packages = AndroidUtils.get_packages(conn, True, False)
        self.assertGreater(len(packages), 0)
        conn.set_package(packages[0])

        test_file = 'test_data.txt'
        test_path = get_script_relative_path(test_file)

        # Push the file
        success = AndroidFilesystem.push_file_to_package(conn, test_path)
        self.assertTrue(success)

        # Validate it pushed OK
        data = conn.adb_runas('ls', test_file)
        self.assertEqual(data.strip(), test_file)

        # Cleanup the file
        success = AndroidFilesystem.delete_file_from_package(conn, test_file)
        self.assertTrue(success)

        # Validate it was deleted - this should fail
        with self.assertRaises(sp.CalledProcessError):
            data = conn.adb_runas('ls', test_file)


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
