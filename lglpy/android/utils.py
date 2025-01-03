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

# This module implements higher level calls around an established
# Android Debug Bridge command line connection.

import shlex
import subprocess as sp
from typing import Any, Optional

from .adb import ADBConnect


class AndroidUtils:
    '''
    A library of utility methods.
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
    def get_packages(conn: ADBConnect, debuggable_only: bool = True,
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
