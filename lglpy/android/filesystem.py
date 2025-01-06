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

import os
import posixpath
import subprocess as sp

from .adb import ADBConnect


class AndroidFilesystem:
    '''
    A library of utility methods for transferring files to/from a device.
    '''

    TEMP_DIR = '/data/local/tmp'
    DATA_PERM = '0666'
    EXEC_PERM = '0777'

    @classmethod
    def push_file_to_tmp(
            cls, conn: ADBConnect, host_path: str,
            executable: bool = False) -> bool:
        '''
        Push a file to the device temp directory.

        File will be copied to: /data/local/tmp/<file>.

        Args:
            conn: The adb connection.
            host_path: The path of the file on the host file system.
            executable: True if the file should be configured as executable.

        Returns:
            True if the file was copied, False otherwise.
        '''
        file_name = os.path.basename(host_path)

        device_path = posixpath.join(cls.TEMP_DIR, file_name)

        try:
            # Remove old file to prevent false success
            conn.adb('shell', 'rm', '-f', device_path)

            # Push new file
            conn.adb('push', host_path, device_path)

            # Check it actually copied
            conn.adb('shell', 'ls', device_path)

            permission = cls.EXEC_PERM if executable else cls.DATA_PERM
            conn.adb('shell', 'chmod', permission, device_path)
        except sp.CalledProcessError:
            return False

        return True

    @classmethod
    def pull_file_from_tmp(
            cls, conn: ADBConnect, file_name: str,
            host_dir: str, delete: bool = False) -> bool:
        '''
        Pull a file from the device temp directory to a host directory.

        File will be copied to: <host_dir>/<file>.

        Args:
            conn: The adb connection.
            file_name: The name of the file in the tmp directory.
            host_path: The destination directory on the host file system.
               Host directory will be created if it doesn't exist.
            delete: Delete the file on the device after copying it.

        Returns:
            True if the file was copied, False otherwise.
        '''
        host_dir = os.path.abspath(host_dir)
        os.makedirs(host_dir, exist_ok=True)

        device_path = posixpath.join(cls.TEMP_DIR, file_name)

        try:
            conn.adb('pull', device_path, host_dir)

            if delete:
                cls.delete_file_from_tmp(conn, file_name)
        except sp.CalledProcessError:
            return False

        return True

    @classmethod
    def delete_file_from_tmp(
            cls, conn: ADBConnect, file_name: str,
            error_ok: bool = False) -> bool:
        '''
        Delete a file from the device temp directory.

        File will be deleted from: /data/local/tmp/<file>.

        Args:
            conn: The adb connection.
            file_name: The name of the file to delete.
            error_ok: Ignore errors if the file doesn't exist.

        Returns:
            True if the file was deleted, False otherwise.
        '''
        device_path = posixpath.join(cls.TEMP_DIR, file_name)

        try:
            if error_ok:
                conn.adb('shell', 'rm', '-f', device_path)
            else:
                conn.adb('shell', 'rm', device_path)
        except sp.CalledProcessError:
            return False

        return True

    @classmethod
    def push_file_to_package(
            cls, conn: ADBConnect, host_path: str,
            executable: bool = False) -> bool:
        '''
        Push a file to the connection package directory.

        File will be copied to, e.g.: /data/user/0/<package>/<file>

        Args:
            conn: The adb connection.
            host_path: The path of the file on the host file system.
            executable: True if the file should be configured as executable.

        Returns:
            True if the file was copied, False otherwise.
        '''
        assert conn.package, \
            'Cannot use push_file_to_package() without package'

        # Determine the paths that we need
        file_name = os.path.basename(host_path)
        tmp_path = posixpath.join(cls.TEMP_DIR, file_name)

        # Copy file to the temp directory
        success = cls.push_file_to_tmp(conn, host_path, executable)
        if not success:
            return False

        # Copy file to the package directory
        try:
            conn.adb_runas('cp', tmp_path, '.')
        except sp.CalledProcessError:
            return False

        # Delete the temp file copy
        cls.delete_file_from_tmp(conn, file_name)

        return True

    @classmethod
    def pull_file_from_package(
            cls, conn: ADBConnect, src_file: str, host_dir: str,
            delete: bool = False) -> bool:
        '''
        Pull a file from the connection package directory to a host directory.

        File will be copied to: <host_dir>/<file>.

        Args:
            conn: The adb connection.
            src_file: The name of the file in the tmp directory.
            host_path: The destination directory on the host file system.
               Host directory will be created if it doesn't exist.
            delete: Delete the file on the device after copying it.

        Returns:
            True if the file was copied, False otherwise.
        '''
        assert conn.package, \
            'Cannot use pull_file_from_package() without package'

        host_dir = os.path.abspath(host_dir)
        os.makedirs(host_dir, exist_ok=True)

        # You cannot adb pull from a package, even if it's debuggable, so
        # this is the non-obvious solution ...
        host_file = os.path.join(host_dir, src_file)
        try:
            conn.adb('exec-out', 'run-as', conn.package,
                     'cat', src_file, '>', host_file,
                     text=False, shell=True)

            if delete:
                cls.delete_file_from_package(conn, src_file)
        except sp.SubprocessError:
            return False

        return True

    @classmethod
    def delete_file_from_package(
            cls, conn: ADBConnect, file_name: str,
            error_ok: bool = False) -> bool:
        '''
        Delete a file from the package directory.

        File will be deleted from, e.g.: /data/user/0/<package>/<file>

        Args:
            conn: The adb connection.
            file_name: The name of the file to delete.
            error_ok: Ignore errors if the file doesn't exist.

        Returns:
            True if the file was deleted, False otherwise.
        '''
        try:
            if error_ok:
                conn.adb_runas('rm', '-f', file_name)
            else:
                conn.adb_runas('rm', file_name)
        except sp.CalledProcessError:
            return False

        return True
