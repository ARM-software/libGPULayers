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
Android device and enable them for a selected debuggable application package.

Prerequisites
=============

* The Android Debug Bridge utility, adb, must be on your host environment PATH.
* Your test device must be accessible to adb on your host workstation, either
  over USB or a network connection.
* Your test application APK must be installed on to your target device.
* Your test application APK must be debuggable.
* Your selected layer binaries must be built.

Interactive use
===============

The default behavior of this script is designed for interactive use. It
can prompt you to select a device or package to instrument, and requires you
to press a key when you are finished using the layer so it knows when to clean
up.

If you do not specify a device or package to use, the script will prompt you
to select one using an interactive console menu. The script will auto-select
if only a single choice is available. To avoid the interactive menus you can
specify the device (--device/-D) and the package to use (--package/-P) on the
command line.

You must specify one or more layer directories in the repository using the
--layer option, e.g. "--layer layer_example". This option can be used multiple
times to specify the installation of multiple stacked layers.

Layers will be loaded by the Vulkan loader in the order that they are specified
on the command line, with the first layer specified being the top of the stack
closest to the application.

An android_install.json file in the layer directory informs the script of the
layer string identifier and shared object library name. Layers without this
file cannot be installed using this script.

Binary discoverability
======================

This installer will look for the layer binaries in standard build system
locations in the layer directory:

64-bit builds:

  * Stripped: <layer_dir>/build_arm64/source/<layer_binary.so>
  * Symbolized: <layer_dir>/build_arm64/source/<layer_binary_sym.so>

32-bit builds:

  * Stripped: <layer_dir>/build_arm32/source/<layer_binary.so>
  * Symbolized: <layer_dir>/build_arm32/source/<layer_binary_sym.so>

By default the installer will choose to install the stripped binaries. You can
optionally enable use of the symbolized binaries using the --symbols/-S command
line option.

Khronos validation layers
=========================

This installer can be used to install the Khronos validation layers. A dummy
layer directory, layer_khronos_validation, is provided for this purpose with a
pre-populated android_install.json config file.

Download the latest Khronos validation layer binaries from GitHub, and copy the
required Arm binaries into the appropriate build directory as described in the
Binary discoverability section above.

           https://github.com/KhronosGroup/Vulkan-ValidationLayers
'''

import argparse
import atexit
import json
import os
import shutil
import subprocess as sp
import sys
from typing import Optional

from lglpy.android.adb import ADBConnect
from lglpy.android.utils import AndroidUtils, NamedTempFile
from lglpy.android.filesystem import AndroidFilesystem
from lglpy.ui import console

# Android 9 is the minimum version supported for our method of enabling layers
ANDROID_MIN_VULKAN_SDK = 28


class LayerMeta:
    '''
    Config data for a single layer to install.

    Attributes:
        name: The Vulkan name of the layer, e.g. VK_LAYER_LGL_EXAMPLE.
        host_path: The full file path on the host filesystem.
        device_file: The file name to use on the device. May be different to
            the host_path file name.
    '''

    def __init__(self, name: str, host_path: str, device_file: str):
        '''
        Create a new layer metadata object.

        Args:
            name: The Vulkan name of the layer, e.g. VK_LAYER_LGL_EXAMPLE.
            host_path: The full file path on the host filesystem.
            device_file: The file name to use on the device.
        '''
        self.name = name
        self.host_path = host_path
        self.device_file = device_file


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
    # Fast test - return all packages (ignoring debuggability)
    # If user has specified a package this avoids checking all of them ...
    packages = AndroidUtils.get_packages(conn, False, False)

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

        # Check it is actually debuggable if user asked for that
        if debuggable_only:
            if not AndroidUtils.is_package_debuggable(conn, match[0]):
                print(f'ERROR:  Package {package_param} is not debuggable')
                return None

        # Unambiguous match
        return match[0]

    # Slower query if we need the full debuggable only list
    if debuggable_only:
        packages = AndroidUtils.get_packages(conn, True, False)

    # Now  match via the menu (will auto-select if only one option)
    title = 'debuggable package' if debuggable_only else 'package'
    selection = console.select_from_menu(title, packages)

    if selection is None:
        return None

    return packages[selection]


def get_layer_metadata(
        layer_dirs: list[str],
        need_32bit: bool, need_symbols: bool) -> Optional[list[LayerMeta]]:
    '''
    Get the layer metadata for all of the selected layers.

    Args:
        layer_dirs: Host directories to search for layers.
        need_32bit: True if need 32-bit, False if 64-bit.
        need_symbols: True if need symbolized build, False if stripped.

    Returns:
        Loaded metadata for all of the layers, or None on error.
    '''
    layer_metadata = []

    for layer_dir in layer_dirs:
        # Parse the JSON metadata file
        metadata_path = os.path.join(layer_dir, 'android_install.json')
        if not os.path.isfile(metadata_path):
            print(f'ERROR: {layer_dir} has no android_install.json')
            return None

        with open(metadata_path, 'r', encoding='utf-8') as handle:
            config = json.load(handle)

        try:
            layer_name = config['layer_name']
            layer_binary = config['layer_binary']
        except KeyError:
            print(f'ERROR: {layer_dir} has invalid android_install.json')
            return None

        # Check that the binary exists
        build_dir = 'build_arm32' if need_32bit else 'build_arm64'

        host_binary = layer_binary
        if need_symbols:
            host_binary = host_binary.replace('.so', '_sym.so')

        host_path = os.path.join(layer_dir, build_dir, 'source', host_binary)
        if not os.path.isfile(host_path):
            print(f'ERROR: layer binary {host_path} is not built')
            return None

        # Build the metadata
        meta = LayerMeta(layer_name, host_path, layer_binary)
        layer_metadata.append(meta)

    return layer_metadata


def install_layer_binary(conn: ADBConnect, layer: LayerMeta) -> bool:
    '''
    Transfer layer binary file to the device.

    Args:
        conn: The adb connection.
        layer: The loaded layer metadata configuration.

    Returns:
        True on success, False otherwise.
    '''
    res = AndroidFilesystem.push_file_to_package(conn, layer.host_path, True)
    if not res:
        return False

    # Rename the file if we loaded the symbolized library from the host
    host_file = os.path.basename(layer.host_path)
    if host_file != layer.device_file:
        res = AndroidFilesystem.rename_file_in_package(
                conn, host_file, layer.device_file)
        if not res:
            return False

    return True


def uninstall_layer_binary(conn: ADBConnect, layer: LayerMeta) -> bool:
    '''
    Remove layer binary file from the device.

    Args:
        conn: The adb connection.
        layer: The loaded layer metadata configuration.

    Returns:
        True on success, False otherwise.
    '''
    return AndroidFilesystem.delete_file_from_package(conn, layer.device_file)


def enable_layers(conn: ADBConnect, layers: list[LayerMeta]) -> bool:
    '''
    Enable the selected layer drivers on the target device.

    Args:
        conn: The adb connection.
        layers: The loaded layer metadata configurations.

    Returns:
        True on success, False otherwise.
    '''
    assert conn.package, 'Enabling layers requires conn.package to be set'

    layer_names = ':'.join([x.name for x in layers])

    s1 = AndroidUtils.set_setting(conn, 'enable_gpu_debug_layers', '1')
    s2 = AndroidUtils.set_setting(conn, 'gpu_debug_app', conn.package)
    s3 = AndroidUtils.set_setting(conn, 'gpu_debug_layers', layer_names)

    return s1 and s2 and s3


def disable_layers(conn: ADBConnect) -> bool:
    '''
    Disable all layer drivers on the target device.

    Args:
        conn: The adb connection.

    Returns:
        True on success, False otherwise.
    '''
    assert conn.package, 'Disabling layers requires conn.package to be set'

    s1 = AndroidUtils.clear_setting(conn, 'enable_gpu_debug_layers')
    s2 = AndroidUtils.clear_setting(conn, 'gpu_debug_app')
    s3 = AndroidUtils.clear_setting(conn, 'gpu_debug_layers')

    return s1 and s2 and s3


def configure_logcat(conn: ADBConnect, output_path: str) -> None:
    '''
    Clear logcat and then pipe new logs to a file.

    Does not error on failure, but will print a warning.

    Args:
        conn: The adb connection.
        output_path: The desired output file path.
    '''
    # Delete the file to avoid user reading stale logs
    if os.path.exists(output_path):
        os.remove(output_path)

    # Pipe adb to file using an async command to avoid losing logs
    # Do NOT use shell=True with a > redirect for this - you cannot easily kill
    # the child on Windows and the log file ends up with an active reference
    try:
        conn.adb('logcat', '-c')
        handle = open(output_path, 'w', encoding='utf-8')
        child = conn.adb_async('logcat', filex=handle)

        # Register a cleanup handler to kill the child
        def cleanup(child_process):
            child_process.kill()

        atexit.register(cleanup, child)

    except sp.CalledProcessError:
        print('WARNING: Cannot enable logcat recording')


def configure_perfetto(
        conn: ADBConnect, output_path: str) -> Optional[tuple[str, str]]:
    '''
    Configure Perfetto traced recording for the given ADB connection.

    Args:
        conn: The adb connection, requires package to be set.
        output_path: The desired output file path.

    Returns:
        PID of the Perfetto process and config file name on success, None on
        failure.
    '''
    assert conn.package, \
        'Cannot use configure_perfetto() without package'

    # Populate the Perfetto template file
    output_file = os.path.basename(output_path)

    base_dir = os.path.dirname(__file__)
    template_path = os.path.join(base_dir, 'lglpy', 'android', 'perfetto.cfg')

    with open(template_path, 'r', encoding='utf-8') as handle:
        template = handle.read()
        template = template.replace('{{PACKAGE}}', conn.package)

    try:
        with NamedTempFile('.cfg') as config_path:
            # Write a file we can push
            with open(config_path, 'w', encoding='utf-8') as handle:
                handle.write(template)

            # Push the file where Perfetto traced can access it
            config_file = os.path.basename(config_path)
            conn.adb('push', config_path, '/data/misc/perfetto-configs/')

            # Enable Perfetto traced and the render stages profiler
            AndroidUtils.set_property(
                conn, 'persist.traced.enable', '1')
            AndroidUtils.set_property(
                conn, 'debug.graphics.gpu.profiler.perfetto', '1')

            # Start Perfetto traced
            output = conn.adb_run(
                        'perfetto',
                        '--background', '--txt',
                        '-c', f'/data/misc/perfetto-configs/{config_file}',
                        '-o', f'/data/misc/perfetto-traces/{output_file}')

            pid = output.strip()
            return (pid, config_file)

    except sp.CalledProcessError:
        print('ERROR: Cannot enable Perfetto recording')
        return None


def cleanup_perfetto(
        conn: ADBConnect, output_path: str, pid: str,
        config_file: str) -> None:
    '''
    Cleanup Perfetto traced recording for the given ADB connection.

    Args:
        conn: The adb connection, requires package to be set.
        output_path: The desired output file path.
        pid: The Perfetto process pid.
        config_file: The Perfetto config path on the device.

    Returns:
        PID of the Perfetto process and config file name on success, None on
        failure.
    '''
    # Compute the various paths we need
    output_file = os.path.basename(output_path)
    output_dir = os.path.dirname(output_path)
    if not output_dir:
        output_dir = '.'

    data_file = f'/data/misc/perfetto-traces/{output_file}'
    config_file = f'/data/misc/perfetto-configs/{config_file}'

    try:
        # Stop Perfetto recording
        # TODO: This doesn't work on a user build phone, is there another way?
        # conn.adb_run('kill', '-TERM', pid)

        # Download the recording data file
        conn.adb('pull', data_file, output_dir)

        # Remove the device-side files
        conn.adb_run('rm', data_file)
        conn.adb_run('rm', config_file)

        # Disable Perfetto traced and the render stages profiler
        AndroidUtils.set_property(
            conn, 'persist.traced.enable', '0')
        AndroidUtils.set_property(
            conn, 'debug.graphics.gpu.profiler.perfetto', '0')

    except sp.CalledProcessError:
        print('ERROR: Cannot disable Perfetto recording')


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
        help='layer name to install (required, can be repeated)')

    parser.add_argument(
        '--symbols', '-S', action='store_true', default=False,
        help='use to install layers with unstripped symbols')

    parser.add_argument(
        '--logcat', type=str, default=None,
        help='file path to save logcat to after a run')

    parser.add_argument(
        '--perfetto', type=str, default=None,
        help='file path to save Perfetto trace to after run')

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

    # Test the device supports Vulkan layers
    sdk_version = AndroidUtils.get_os_sdk_version(conn)
    if not sdk_version or sdk_version < ANDROID_MIN_VULKAN_SDK:
        print('ERROR: Device must support Android 9.0 or newer')
        return 2

    # Select a package to instrument
    package = get_package_name(conn, args.package)
    if not package:
        return 3

    conn.set_package(package)

    # Select layers to install
    need_32bit = AndroidUtils.is_package_32bit(conn, package)
    layers = get_layer_metadata(args.layer, need_32bit, args.symbols)
    if not layers:
        return 4

    # Install files
    for layer in layers:
        if not install_layer_binary(conn, layer):
            print('ERROR: Layer install on device failed')
            return 5

    # Enable layers
    if not enable_layers(conn, layers):
        print('ERROR: Layer enable on device failed')
        return 6

    print('Layers are installed and ready for use:')
    for layer in layers:
        print(f'    - {layer.name}')
    print()

    # Enable logcat
    if args.logcat:
        configure_logcat(conn, args.logcat)

    # Enable Perfetto trace
    if args.perfetto:
        perfetto_conf = configure_perfetto(conn, args.perfetto)

    input('Press any key when finished to uninstall all layers')

    # Disable Perfetto trace
    if args.perfetto and perfetto_conf:
        cleanup_perfetto(conn, args.perfetto, *perfetto_conf)

    # Disable layers
    if not disable_layers(conn):
        print('ERROR: Layer disable on device failed')
        return 10

    # Remove files
    for layer in layers:
        if not uninstall_layer_binary(conn, layer):
            print('ERROR: Layer uninstall from device failed')
            return 11

    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print("\n\nERROR: User interrupted execution")
