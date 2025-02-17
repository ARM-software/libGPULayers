#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024-2025 Arm Limited
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
'''
A generator for Vulkan layers.
'''

import argparse
import os
import re
import shutil
import sys
from typing import TextIO


def load_template(path: str) -> str:
    '''
    Load a template from the generator template directory.

    Args:
        path: The file name in the template directory.

    Returns:
        The loaded text template.
    '''
    base_dir = os.path.dirname(__file__)
    template_file = os.path.join(base_dir, 'vk_codegen', path)

    # Load the data from the file
    with open(template_file, 'r', encoding='utf-8') as handle:
        data = handle.read()

    return data


def get_layer_api_name(vendor: str, layer: str) -> str:
    '''
    Generate the layer string name for the new layer used by the loader.
    Names are of the form "VK_LAYER_<VENDOR>_<LAYER>" in upper case.

    Args:
        vendor: The layer vendor tag.
        layer: The name of the layer.

    Returns:
        The layer string name used by the loader.
    '''
    pattern = re.compile(r'^VkLayer(\w+)$')
    match = pattern.match(layer)
    assert match

    name_parts = ('VK_LAYER', vendor.upper(), match.group(1).upper())
    return '_'.join(name_parts)


def get_layer_api_description(vendor: str, layer: str) -> str:
    '''
    Generate the layer description placeholder to return from the layer
    enumeration query in the API. We expect developers to replace this with
    something more useful for long-lived layers.

    Args:
        vendor: The layer vendor tag.
        layer: The name of the layer.

    Returns:
        The layer string description returned by the API queries.
    '''
    return f'{layer} by {vendor}'


def generate_root_cmake(file: TextIO, project: str, layer: str) -> None:
    '''
    Generate the root CMake file for a new layer.

    Args:
        file: The file handle to write to.
        project: The name of the CMake project.
        layer: The name of the layer used as the Android log tag.
    '''
    data = load_template('root_CMakeLists.txt')
    data = data.replace('{PROJECT_NAME}', project)
    data = data.replace('{LAYER_NAME}', layer)
    file.write(data)


def generate_source_cmake(file: TextIO, vendor: str, layer: str) -> None:
    '''
    Generate the layer source directory CMake file for a new layer.

    Args:
        file: The file handle to write to.
        vendor: The layer vendor tag.
        layer: The name of the layer.
    '''
    data = load_template('source_CMakeLists.txt')
    data = data.replace('{LAYER_NAME}', layer)

    name = get_layer_api_name(vendor, layer)
    data = data.replace('{LGL_LAYER_NAME}', name)

    desc = get_layer_api_description(vendor, layer)
    data = data.replace('{LGL_LAYER_DESC}', desc)

    file.write(data)


def generate_install_manifest(file: TextIO, vendor: str, layer: str) -> None:
    '''
    Generate the layer manifest with placeholders replaced.

    Args:
        file: The file handle to write to.
        vendor: The layer vendor tag.
        layer: The name of the layer.
    '''
    data = load_template('manifest.json')
    data = data.replace('{LAYER_NAME}', layer)

    name = get_layer_api_name(vendor, layer)
    data = data.replace('{LGL_LAYER_NAME}', name)

    file.write(data)


def copy_resource(src_dir: str, dst_dir: str) -> None:
    '''
    Copy a directory of resources to another location.

    Args:
        src_dir: The source directory location.
        out_dir: The destination directory location.
    '''
    dst_dir = os.path.abspath(dst_dir)
    os.makedirs(dst_dir, exist_ok=True)
    shutil.copytree(src_dir, dst_dir, dirs_exist_ok=True)


def parse_command_line() -> argparse.Namespace:
    '''
    Parse the command line.

    Returns:
        The parsed command line container.
    '''
    parser = argparse.ArgumentParser()

    parser.add_argument('--project-name', required=True,
                        help='CMake project name')

    parser.add_argument('--vendor-name', default='LGL',
                        help='layer vendor name (optional)')

    parser.add_argument('--layer-name', default=None,
                        help='layer name (optional)')

    parser.add_argument('--output', metavar='DIR', required=True,
                        help='output directory for layer project')

    parser.add_argument('--overwrite', action='store_true', default=False,
                        help='overwrite an existing output directory')

    args = parser.parse_args()

    if not args.layer_name:
        args.layer_name = args.project_name

    return args


def main() -> int:
    '''
    Tool main function.

    Returns:
        The process exit code.
    '''
    args = parse_command_line()

    # Validate the layer name is well formed
    pattern = re.compile(r'^VkLayer\w+$')
    if not pattern.match(args.layer_name):
        print(f'ERROR: Layer name "{args.layer_name}" must start with VkLayer')
        return 1

    # Check that output directory is either empty or over-writable
    outdir = args.output
    if os.path.exists(outdir):
        if not os.path.isdir(outdir):
            print(f'ERROR: Output location "{outdir}" is not a directory')
            return 1

        if len(os.listdir(outdir)) != 0 and not args.overwrite:
            print(f'ERROR: Output directory "{outdir}" is not empty')
            return 1

    # Generate static resources
    base_dir = os.path.dirname(__file__)
    source_dir = os.path.join(base_dir, 'vk_layer')
    copy_resource(source_dir, outdir)

    # Generate templated resources
    outfile = os.path.join(outdir, 'CMakeLists.txt')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_root_cmake(handle, args.project_name, args.layer_name)

    outfile = os.path.join(outdir, 'source/CMakeLists.txt')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_source_cmake(handle, args.vendor_name, args.layer_name)

    outfile = os.path.join(outdir, 'android_install.json')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_install_manifest(handle, args.vendor_name, args.layer_name)

    return 0


if __name__ == '__main__':
    sys.exit(main())
