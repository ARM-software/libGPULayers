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
This module implements higher level Android queries and utilities, built on top
of the low level Android Debug Bridge wrapper.
'''

import re
import shlex
import subprocess as sp
from typing import Optional

from .adb import ADBConnect


class AndroidUtils:
    '''
    A library of utility methods for querying device and package status.
    '''

    @staticmethod
    def get_devices() -> tuple[list[str], list[str]]:
        '''
        Get the list of devices that are connected to this host.

        Returns:
            Tuple of two elements.
              - A list of available devices that can be used.
              - A list of unavailable devices, e.g. with unauthorized abd.

            Empty lists are returned on error.
        '''
        good_devices = []  # typing: list[str]
        bad_devices = []   # typing: list[str]

        try:
            conn = ADBConnect()
            result = conn.adb('devices')

            for line in result.splitlines():
                # Match devices that are available for adb
                if line.endswith('device'):
                    good_devices.append(line.split()[0])
                # Match devices that are detectable, but not usable
                elif line.endswith(('offline', 'unauthorized')):
                    bad_devices.append(line.split()[0])

        except sp.CalledProcessError:
            pass

        return (good_devices, bad_devices)

    @staticmethod
    def get_packages(
            conn: ADBConnect, debuggable_only: bool = True,
            main_only: bool = True) -> list[str]:
        '''
        Get the list of packages on the target device.

        Note: listing non-debuggable packages with main_only enabled is quite
        slow due to the number of system packages that need testing.

        Args:
            conn: The adb connection.
            debuggable_only: True if show only debuggable packages, else all.
            main_only: True if show only packages with MAIN intent, else all.

        Returns:
            The list of packages, or an empty list on error.
        '''
        opt = '-3' if debuggable_only else ''
        command = f'pm list packages -e {opt} | sed "s/^package://" | sort'

        if debuggable_only:
            # Test if the package is debuggable on the device
            sub = 'if run-as $0 true ; then echo $0 ; fi'
            command += f' | xargs -n1 sh -c {shlex.quote(sub)} 2> /dev/null'

        if main_only:
            # Test if the package has a MAIN activity intent
            sub = 'dumpsys package $0 | ' \
                  'if grep -q "android.intent.action.MAIN" ; then echo $0 ; fi'
            command += f' | xargs -n1 sh -c {shlex.quote(sub)} 2> /dev/null'

        try:
            package_list = conn.adb('shell', command).splitlines()

        except sp.CalledProcessError:
            return []

        # Some shells (seen on Android 9/10) report sh as a valid package
        if 'sh' in package_list:
            package_list.remove('sh')

        return package_list

    @staticmethod
    def get_os_version(conn: ADBConnect) -> Optional[str]:
        '''
        Get the Android OS platform version of the target device.

        Args:
            conn: The adb connection.

        Returns:
            The Android platform version, or None on error.
        '''
        try:
            ver = conn.adb('shell', 'getprop', 'ro.build.version.release')
            return ver
        except sp.CalledProcessError:
            return None

    @staticmethod
    def get_os_sdk_version(conn: ADBConnect) -> Optional[int]:
        '''
        Get the Android OS SDK version of the target device.

        Args:
            conn: The adb connection.

        Returns:
            The Android SDK version number, or None on error.
        '''
        try:
            ver = conn.adb('shell', 'getprop', 'ro.build.version.sdk')
            return int(ver)
        except sp.CalledProcessError:
            return None

    @staticmethod
    def get_device_model(conn: ADBConnect) -> Optional[tuple[str, str]]:
        '''
        Get the vendor and model of the target device.

        Args:
            conn: The adb connection.

        Returns:
            The device vendor and model strings, or None on error.
        '''
        try:
            vendor = conn.adb('shell', 'getprop', 'ro.product.manufacturer')
            vendor = vendor.strip()

            model = conn.adb('shell', 'getprop', 'ro.product.model')
            model = model.strip()

            return (vendor, model)

        except sp.CalledProcessError:
            return None

    @staticmethod
    def is_package_debuggable(conn: ADBConnect, package: str) -> bool:
        '''
        Test if a package is debuggable.

        Args:
            conn: The adb connection.
            package: The name of the package to test.

        Returns:
            True if the package is debuggable, False otherwise.
        '''
        try:
            package = shlex.quote(package)
            command = f'if run-as {package} true ; then echo {package} ; fi'
            log = conn.adb('shell', command)
            return log.strip() == package

        except sp.CalledProcessError:
            return False

    @staticmethod
    def is_package_32bit(conn: ADBConnect, package: str) -> bool:
        '''
        Test if a package prefers 32-bit ABI on the target device.

        Args:
            conn: The adb connection.
            package: The name of the package to test.

        Returns:
            True if the package is 32-bit, False if 64-bit or on error.
        '''
        try:
            preferred_abi = None

            # Try to match the primary ABI loaded by the application
            package = shlex.quote(package)
            command = f'pm dump {package} | grep primaryCpuAbi'
            log = conn.adb('shell', command)
            pattern = re.compile('primaryCpuAbi=(\\S+)')
            match = pattern.search(log)

            if match:
                log_abi = match.group(1)
                if log_abi != 'null':
                    preferred_abi = log_abi

            # If that fails match against the default device ABI
            if preferred_abi is None:
                preferred_abi = conn.adb('shell', 'getprop ro.product.cpu.abi')

            return preferred_abi in ('armeabi-v7a', 'armeabi')

        except sp.CalledProcessError:
            return False

    @staticmethod
    def get_package_data_dir(conn: ADBConnect):
        '''
        Get the package data directory on the device filesystem.

        TODO: This currently only handles data directories for User 0. If a
        device has multiple user profiles configured, the dumpsys output will
        contain multiple dataDir records.

        Args:
            conn: The adb connection.

        Returns:
            The package data directory, or None on error.
        '''
        assert conn.package, \
            'Cannot use get_package_data_dir() without package'

        try:
            package = shlex.quote(conn.package)
            command = f'dumpsys package {package} | grep dataDir'
            log = conn.adb('shell', command)
            return log.replace('dataDir=', '').strip()

        except sp.CalledProcessError:
            return None

    @staticmethod
    def set_property(conn: ADBConnect, prop: str, value: str) -> bool:
        '''
        Set an Android system property to a value.

        Args:
            conn: The adb connection.
            prop: The name of the property to set.
            value: The desired value of the property.

        Returns:
            True on success, False otherwise.
        '''
        try:
            conn.adb('shell', 'setprop', prop, value)
            return True

        except sp.CalledProcessError:
            return False

    @staticmethod
    def get_property(conn: ADBConnect, prop: str) -> Optional[str]:
        '''
        Get an Android system property value.

        Args:
            conn: The adb connection.
            prop: The name of the property to get.

        Returns:
            The value of the property on success, None otherwise. Note that
            deleted settings that do not exist will also return None.
        '''
        try:
            value = conn.adb('shell', 'getprop', prop)
            return value.strip()

        except sp.CalledProcessError:
            return None

    @staticmethod
    def clear_property(conn: ADBConnect, prop: str) -> bool:
        '''
        Set an Android system property to an empty value.

        Args:
            conn: The adb connection.
            prop: The name of the property to clear.

        Returns:
            True on success, False otherwise.
        '''
        try:
            conn.adb('shell', 'setprop', prop, '""')
            return True

        except sp.CalledProcessError:
            return False

    @staticmethod
    def set_setting(conn: ADBConnect, setting: str, value: str) -> bool:
        '''
        Set an Android system setting to a value.

        Args:
            conn: The adb connection.
            setting: The name of the setting to set.
            value: The desired value of the setting.

        Returns:
            True on success, False otherwise.
        '''
        try:
            conn.adb('shell', 'settings', 'put', 'global', setting, value)
            return True

        except sp.CalledProcessError:
            return False

    @staticmethod
    def get_setting(conn: ADBConnect, setting: str) -> Optional[str]:
        '''
        Get an Android system property setting.

        Args:
            conn: The adb connection.
            setting: The name of the setting to get.

        Returns:
            The value of the setting on success, None otherwise.
        '''
        try:
            value = conn.adb('shell', 'settings', 'get', 'global', setting)
            value = value.strip()

            if value == 'null':
                return None

            return value

        except sp.CalledProcessError:
            return None

    @staticmethod
    def clear_setting(conn: ADBConnect, setting: str) -> bool:
        '''
        Clear an Android system setting.

        Args:
            conn: The adb connection.
            setting: The name of the setting to set.

        Returns:
            True on success, False otherwise.
        '''
        try:
            conn.adb('shell', 'settings', 'delete', 'global', setting)
            return True

        except sp.CalledProcessError:
            return False
