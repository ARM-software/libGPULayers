#!/bin/env python3
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
This script is a helper utility to install one or more Vulkan layers on to an
Android device for a given debuggable application package.
'''

import argparse
import sys
from typing import Optional

from lglpy.android.adb import ADBConnect
from lglpy.android.utils import AndroidUtils
from lglpy.ui import console


def get_device_name(
        conn: ADBConnect, device_param: Optional[str]) -> Optional[str]:
    '''
    Determine which connected device to use.

    If multiple devices are connected, and the user does not provide an
    unambiguous selection, then the user will be prompted to select.

    Args:
        conn: The adb connection.
        device_param: The user specified device name from the command line,
            or None for menu-driven selection.

    Returns:
        The selected device, or None if no device was selected.
    '''
    good_devices, bad_devices = AndroidUtils.get_devices()

    # Log bad devices
    if bad_devices:
        print('\nSearching for devices:')
        for device in bad_devices:
            print(f'    Device {device} is connected, but is not debuggable')

    # No devices found so early out
    if not good_devices:
        print('ERROR: No debuggable device is connected')
        return None

    # If user specified a name check it exists and is non-ambiguous
    if device_param:
        search = device_param.lower()
        match = [x for x in good_devices if x.lower().startswith(search)]

        # User device not found ...
        if not match:
            print(f'ERROR: Device {device_param} is not connected')
            return None

        # User device found too many times ...
        if len(match) > 1:
            print(f'ERROR: Device {device_param} is ambiguous')
            return None

        # Unambiguous match
        return match[0]

    # Build a more literate option list for the menu
    options = []
    for device in good_devices:
        conn.set_device(device)
        meta = AndroidUtils.get_device_model(conn)

        if meta:
            vendor = meta[0][0].upper() + meta[0][1:]
            model = meta[1][0].upper() + meta[1][1:]
            options.append(f'{vendor} {model} ({device})')

        else:
            options.append(f'Unknown device ({device})')

    conn.set_device(None)

    # Else match via the menu (will auto-select if only one option)
    selection = console.select_from_menu('device', options)
    if selection is None:
        return None

    return good_devices[selection]


def get_package_name(
        conn: ADBConnect, package_param: Optional[str],
        debuggable_only: bool = True) -> Optional[str]:
    '''
    Determine which application package to use.

    Currently only supports selecting launchable packages with a MAIN intent.

    Args:
        conn: The adb connection.
        package_param: The user specified package name from the command line.
            - May be the full package name (case-insensitive).
            - May be a package name prefix (case-insensitive).
            - May be auto-select from menu (set as None)
        debuggable_only: Show only debuggable packages if True.

    Returns:
        The selected package, or None if no package was selected.
    '''
    packages = AndroidUtils.get_packages(conn, debuggable_only, True)

    # No packages found so early out
    if not packages:
        print('ERROR: No packages detected')
        return None

    # If user specified a name check it exists and is non-ambiguous
    if package_param:
        search = package_param.lower()
        match = [x for x in packages if x.lower().startswith(search)]

        # User device not found ...
        if not match:
            print(f'ERROR: Package {package_param} not found')
            return None

        # User device found too many times ...
        if len(match) > 1:
            print(f'ERROR:  Package {package_param} is ambiguous')
            return None

        # Unambiguous match
        return match[0]

    # Else match via the menu (will auto-select if only one option)
    title = 'debuggable package' if debuggable_only else 'package'
    selection = console.select_from_menu(title, packages)

    if selection is None:
        return None

    return packages[selection]


def parse_cli() -> argparse.Namespace:
    '''
    Parse the command line.

    Returns:
        An argparse results object.
    '''
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--device', '-D', default=None,
        help='target device name or name prefix (default=auto-detected)')

    parser.add_argument(
        '--package', '-P', default=None,
        help='target package name or regex pattern (default=auto-detected)')

    parser.add_argument(
        '--layer', '-L', action='append', required=True,
        help='layer name to install (can be repeated)')

    return parser.parse_args()


def main() -> int:
    '''
    The script main function.

    Returns:
        The process exit code.
    '''
    args = parse_cli()

    conn = ADBConnect()

    # Select a device to connect to
    device = get_device_name(conn, args.device)
    if not device:
        return 1

    conn.set_device(device)

    # Select a package to instrument
    package = get_package_name(conn, args.package)
    if not package:
        return 2

    conn.set_package(package)

    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print("\n\nERROR: User interrupted execution")
