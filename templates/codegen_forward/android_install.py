#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024 Arm Limited
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
A simple installer for Android Vulkan layers.
'''

import argparse
import os
import shlex
import subprocess as sp
import sys

# Android temp directory
ANDROID_TMP_DIR = '/data/local/tmp/'

# Expected layer names
EXPECTED_VULKAN_LAYER_NAME = '{LGL_LAYER_NAME}'
EXPECTED_VULKAN_LAYER_FILE = 'lib{LAYER_NAME}.so'

class Device:
    '''
    A basic wrapper around adb, allowing a specific device to be registered.

    Attributes:
        device: The name of the device to call, or None for non-specific use.
    '''

    def adb_quiet(self, *args):
        '''
        Call `adb` to run a command, but ignore output and errors.

        Args:
            *args : List of command line parameters.
        '''
        commands = ['adb']
        commands.extend(args)
        sp.run(commands, stdout=sp.DEVNULL, stderr=sp.DEVNULL, check=False)

    def adb(self, *args, **kwargs):
        '''
        Call `adb` to run command, and capture output and results.

        Args:
            *args: List of command line parameters.
            **kwargs: text: Is output is text, or binary?
                      shell: Use the host shell?
                      quote: Quote arguments before forwarding

        Returns:
            The contents of stdout.

        Raises:
            CalledProcessError: The subprocess was not successfully executed.
        '''
        commands = ['adb']
        commands.extend(args)

        text = kwargs.get('text', True)
        shell = kwargs.get('shell', False)
        quote = kwargs.get('quote', False)

        # Run on the host shell
        if shell:
            # Unix shells need a flattened command for shell commands
            if os.name != 'nt':
                quotedCommands = []
                for command in commands:
                    if command != '>':
                        command = shlex.quote(command)
                    quotedCommands.append(command)
                commands = ' '.join(quotedCommands)

        # Run on the device but with shell argument quoting
        if quote:
            for i, command in enumerate(commands):
                commands[i] = shlex.quote(command)

        rep = sp.run(commands, check=True, shell=shell, stdout=sp.PIPE,
                     stderr=sp.PIPE, universal_newlines=text)

        return rep.stdout

    def adb_run_as(self, package, *args, quiet=False):
        '''
        Call `adb` to run command as a package using `run-as` or as root,
        if root is accessible. If command will be run as root, this function
        will change CWD to the package data directory before executing the command.

        Args:
            package: Package name to run-as or change CWD to.
            *args: List of command line parameters.
            quiet: If True, ignores output from adb.

        Returns:
            The contents of stdout or Nothing, if quiet=True.

        Raises:
            CalledProcessError: The subprocess was not successfully executed.
        '''
        command = ['shell', 'run-as', package]
        command.extend(args)

        if quiet:
            return self.adb_quiet(*command)

        return self.adb(*command)


def enable_vulkan_debug_layer(device, package, layer):
    '''
    Args:
        device: The device instance.
        package: The Android package name.
        layer: The layer file path name.
    '''

    print('\nInstalling Vulkan debug layer')

    layer = os.path.normpath(layer)
    layerBase = os.path.basename(os.path.normpath(layer))

    device.adb('push', layer, ANDROID_TMP_DIR)
    device.adb_run_as(package, 'cp', ANDROID_TMP_DIR + layerBase, '.')
    device.adb('shell', 'settings', 'put', 'global', 'enable_gpu_debug_layers', '1')
    device.adb('shell', 'settings', 'put', 'global', 'gpu_debug_app', package)
    device.adb('shell', 'settings', 'put', 'global', 'gpu_debug_layers', EXPECTED_VULKAN_LAYER_NAME)


def disable_vulkan_debug_layer(device, package, layer):
    '''
    Clean up the Vulkan layer installation.

    Args:
        device: The device instance.
        args: The command arguments.
    '''
    print('\nRemoving Vulkan debug layer')

    layerBase = os.path.basename(os.path.normpath(layer))

    device.adb('shell', 'settings', 'delete', 'global', 'enable_gpu_debug_layers')
    device.adb('shell', 'settings', 'delete', 'global gpu_debug_app')
    device.adb('shell', 'settings', 'delete', 'global gpu_debug_layers')
    device.adb_run_as(package, 'rm', layerBase, quiet=True)


def get_layer():
    '''
    Find the debug layer to use in the build directory.
    '''

    base_dir = './build_arm64/source/'

    sym_lib = None
    lib = None

    for path in os.listdir(base_dir):
        if path.endswith('_sym.so'):
            sym_lib = os.path.join(base_dir, path)
        elif path.endswith('.so'):
            lib = os.path.join(base_dir, path)

    # TODO: If we want to use symbolized layer we need to rename it
    return lib


def parse_command_line():
    '''
    Parse the command line.

    Returns:
        The parsed command line container.
    '''
    parser = argparse.ArgumentParser()

    parser.add_argument('--package', required=True,
                        help='Android package name')

    return parser.parse_args()


def main():
    '''
    Script main function.

    Returns:
        Process return code.
    '''
    args = parse_command_line()

    device = Device()
    layer = get_layer()

    enable_vulkan_debug_layer(device, args.package, layer)

    input('Press Enter to disable layers')

    disable_vulkan_debug_layer(device, args.package, layer)

if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print('\n\nERROR: User interrupted execution')
