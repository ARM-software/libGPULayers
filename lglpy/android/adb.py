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
This module implements a simple wrapper around the Android Debug Bridge command
line tool which can be used to run commands on a connected Android device.
'''

from collections.abc import Iterable
import os
import shlex
import subprocess as sp
from typing import Optional


class ADBConnect:
    '''
    A wrapper around adb which can be used to connect to a specific device,
    and run commands as a specific package.

      - adb() runs a command using adb and waits for the result.
      - adb_async() runs a command using  adb and does not wait for the result.
      - adb_run() runs a device shell command as the "shell" user and waits for
        the result.
      - adb_runas() runs a device shell command as the current package user and
        waits for the result.

    The current device and package are attributes of the connection instance
    which can be set at construction, or via the set_device() and set_package()
    methods.

    Attributes:
        device: The name of the connected device, or None for generic use.
        package: The name of the debuggable package, or None for generic use.
    '''

    def __init__(self, device: Optional[str] = None,
                 package: Optional[str] = None):
        '''
        Create a new device, defaulting to non-specific use.

        Args:
            device: The device identifier, as returned by 'adb devices', or
                None for non-specific use.
            package: The package name, as returned by `adb shell pm list
                packages` or None for non-specific use.
        '''
        self.device = device
        self.package = package

    def set_device(self, device: Optional[str]) -> None:
        '''
        Set the device for this connection.

        Args:
            device: The device identifier, as returned by 'adb devices', or
                None for non-specific use.
        '''
        self.device = device

    def set_package(self, package: str) -> None:
        '''
        Set the package for this connection.

        Args:
            package: The package name, as returned by `adb shell pm list
                packages` or None for non-specific use.
        '''
        self.package = package

    def get_base_command(self, args: Iterable[str]) -> list[str]:
        '''
        Get the root of an adb command, injecting device selector if needed.

        Args:
            args: The user argument list, may be empty.

        Returns:
            The fully populated command list.
        '''
        commands = ['adb']
        if self.device:
            commands.extend(['-s', self.device])
        commands.extend(args)

        return commands

    def pack_commands(self, commands: list[str],
                      shell: bool, quote: bool) -> list[str] | str:
        '''
        Pack a set of command lines suitable for a subprocess call.

        Args:
            commands: List of command line parameters.
            shell: True if this should invoke the host shell.
            quote: True if arguments are quoted before forwarding.

        Return:
            Appropriated packed command line arguments for the host OS.
        '''
        # Run via the host shell
        if shell:
            # Unix shells need a flattened command for shell commands
            if os.name != 'nt':
                quoted_commands = []
                for command in commands:
                    if command != '>':
                        command = shlex.quote(command)
                    quoted_commands.append(command)

                return ' '.join(quoted_commands)

            # We do not currently quote on other host shells
            return commands

        # Run via direct invocation of adb with quoting for target shell
        if quote:
            return [shlex.quote(arg) for arg in commands]

        # Run via direct invocation of adb without any additional quoting
        return commands

    def adb(self, *args: str, text: bool = True, shell: bool = False,
            quote: bool = False, check: bool = True) -> str:
        '''
        Call adb to synchronously run a command, check its result, and capture
        its output if successful.

        Commands can invoke adb directly, or via the host shell if invoked with
        shell=True. When using shell=True on Unix hosts the arguments are
        always quoted unless the argument is a '>' redirect shell argument. On
        Windows beware of the security implications of the lack of quoting.

        Args:
            *args: List of command line parameters.
            text: True if output is text, False if binary
            shell: True if this should invoke via host shell, False if direct.
            quote: True if arguments are quoted, False if unquoted.
            check: True if result is checked, False if ignored.

        Returns:
            The stdout response written by adb.

        Raises:
            CalledProcessError: The invoked call failed.
        '''
        # Build the command list
        commands = self.get_base_command(args)
        packed_commands = self.pack_commands(commands, shell, quote)

        # Force UTF-8 for text output
        encoding = 'utf-8' if text else None

        # Invoke the command
        rep = sp.run(packed_commands, check=check, shell=shell,
                     text=text, encoding=encoding,
                     stdin=sp.DEVNULL, stdout=sp.PIPE, stderr=sp.PIPE)

        # Return the output
        return rep.stdout

    def adb_async(self, *args: str, text: bool = True, shell: bool = False,
                  quote: bool = False, pipe: bool = False,
                  filex=None) -> sp.Popen:
        '''
        Call adb to asynchronously run a command, without waiting for it to
        complete.

        Commands can invoke adb directly, or via the host shell if invoked with
        shell=True. When using shell=True on Unix hosts the arguments are
        always quoted unless the argument is a '>' redirect shell argument. On
        Windows beware of the security implications of the lack of quoting.

        By default, the adb stdout data is discarded. It can be kept by setting
        pipe=True, but in this case the caller must call communicate() on the
        returned object to avoid the child blocking indefinitely if the OS pipe
        buffer fills up.

        Args:
            *args: List of command line parameters.
            text: True if output is text, False if binary
            shell: True if this should invoke via host shell, False if direct.
            quote: True if arguments are quoted, False if unquoted.
            pipe: True if child stdout is collected to pipe, else False.
            filex: True if child stdout is collected to file, else False.

        Returns:
            The process handle.

        Raises:
            CalledProcessError: The invoked call failed.
        '''
        # Setup the configuration
        output = sp.DEVNULL

        if pipe:
            output = sp.PIPE

        if filex:
            output = filex

        # Build the command list
        commands = self.get_base_command(args)
        packed_commands = self.pack_commands(commands, shell, quote)

        # Force UTF-8 for text output
        encoding = 'utf-8' if text else None

        # Sink inputs to DEVNULL to stop the child process stealing keyboard
        # Sink outputs to DEVNULL to stop full output buffers blocking child
        # pylint: disable=consider-using-with
        process = sp.Popen(packed_commands,
                           text=text, encoding=encoding, shell=shell,
                           stdin=sp.DEVNULL, stdout=output, stderr=sp.DEVNULL)

        # Return the output process a user can use to wait, if needed.
        return process

    def adb_run(self, *args: str, text: bool = True, shell: bool = False,
                quote: bool = False, check: bool = True) -> str:
        '''
        Call adb to synchronously run a device shell command as the Android
        "shell" user, check its result, and capture its output if successful.

        Commands can invoke adb directly, or via the host shell if invoked with
        shell=True. When using shell=True on Unix hosts the arguments are
        always quoted unless the argument is a '>' redirect shell argument. On
        Windows beware of the security implications of the lack of quoting.

        Args:
            *args: List of command line parameters.
            text: True if output is text, False if binary
            shell: True if this should invoke via host shell, False if direct.
            quote: True if arguments are quoted, False if unquoted.
            check: True if result is checked, False if ignored.

        Returns:
            The stdout response written by adb.

        Raises:
            CalledProcessError: The invoked call failed.
        '''
        # Build the command list
        commands = self.get_base_command(['shell'])
        commands.extend(args)
        packed_commands = self.pack_commands(commands, shell, quote)

        # Force UTF-8 for text output
        encoding = 'utf-8' if text else None

        # Invoke the command
        rep = sp.run(packed_commands,
                     check=check, shell=shell, text=text, encoding=encoding,
                     stdin=sp.DEVNULL, stdout=sp.PIPE, stderr=sp.PIPE)

        # Return the output
        return rep.stdout

    def adb_runas(self, *args: str, text: bool = True, shell: bool = False,
                  quote: bool = False, check: bool = True) -> str:
        '''
        Call adb to synchronously run a device shell command as the package
        user, check its result, and capture its output if successful.

        Commands can invoke adb directly, or via the host shell if invoked with
        shell=True. When using shell=True on Unix hosts the arguments are
        always quoted unless the argument is a '>' redirect shell argument. On
        Windows beware of the security implications of the lack of quoting.

        Args:
            *args: List of command line parameters.
            text: True if output is text, False if binary
            shell: True if this should invoke via host shell, False if direct.
            quote: True if arguments are quoted, False if unquoted.
            check: True if result is checked, False if ignored.

        Returns:
            The stdout response written by adb.

        Raises:
            CalledProcessError: The invoked call failed.
        '''
        assert self.package, \
            'Cannot use adb_runas() without package'

        # Build the command list
        commands = self.get_base_command(['shell', 'run-as', self.package])
        commands.extend(args)
        packed_commands = self.pack_commands(commands, shell, quote)

        # Force UTF-8 for text output
        encoding = 'utf-8' if text else None

        # Invoke the command
        rep = sp.run(packed_commands,
                     check=check, shell=shell, text=text, encoding=encoding,
                     stdin=sp.DEVNULL, stdout=sp.PIPE, stderr=sp.PIPE)

        # Return the output
        return rep.stdout
