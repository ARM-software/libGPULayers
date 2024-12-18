#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024 Arm Limited
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
from datetime import datetime
import os
import re
import shutil
import sys


def load_template(path):
    base_dir = os.path.dirname(__file__)
    template_file = os.path.join(base_dir, 'vk_codegen', path)

    # Load the data from the file
    with open(template_file, 'r', encoding='utf-8') as handle:
        data = handle.read()

    return data


def write_copyright_header(file):
    data = load_template('header.txt')

    start_year = 2024
    end_year = datetime.now().year
    if start_year == end_year:
        date_string = f'{start_year}'
    else:
        date_string = f'{start_year}-{end_year}'

    data = data.replace('{COPYRIGHT_YEARS}', date_string)

    file.write(data)
    file.write('\n')


def generate_layer_root_cmake(file, project_name, layer_name):
    data = load_template('root_CMakeLists.txt')
    data = data.replace('{PROJECT_NAME}', project_name)
    data = data.replace('{LAYER_NAME}', layer_name)
    file.write(data)


def get_layer_api_name(vendor_name, layer_name):

    pattern = re.compile(r'^VkLayer(\w+)$')
    match = pattern.match(layer_name)
    assert match

    name_parts = ('VK_LAYER', vendor_name.upper(), match.group(1).upper())
    return '_'.join(name_parts)


def get_layer_api_description(vendor_name, layer_name):
    return f'{layer_name} by {vendor_name}'


def generate_layer_source_cmake(file, vendor_name, layer_name):

    data = load_template('source_CMakeLists.txt')
    data = data.replace('{LAYER_NAME}', layer_name)

    name = get_layer_api_name(vendor_name, layer_name)
    data = data.replace('{LGL_LAYER_NAME}', name)

    desc = get_layer_api_description(vendor_name, layer_name)
    data = data.replace('{LGL_LAYER_DESC}', desc)

    file.write(data)


def generate_layer_install_helper(file, vendor_name, layer_name):

    data = load_template('android_install.py')
    data = data.replace('{LAYER_NAME}', layer_name)

    name = get_layer_api_name(vendor_name, layer_name)
    data = data.replace('{LGL_LAYER_NAME}', name)

    file.write(data)


def copy_resource(src_dir, out_dir):
    out_dir = os.path.abspath(out_dir)
    os.makedirs(out_dir, exist_ok=True)
    shutil.copytree(src_dir, out_dir, dirs_exist_ok=True)


def parse_command_line():
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


def main():
    '''
    Tool main function.

    Returns:
        The process exit code.
    '''
    args = parse_command_line()

    # Validate the layer name is well formed
    pattern = re.compile(r'^VkLayer\w+$')
    if not pattern.match(args.layer_name):
        print(f'ERROR: Layer name "{args.layer_name}" is invalid')
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

    # Generate the layer skeleton
    outfile = os.path.join(outdir, 'CMakeLists.txt')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_layer_root_cmake(handle, args.project_name, args.layer_name)

    outfile = os.path.join(outdir, 'source/CMakeLists.txt')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_layer_source_cmake(handle, args.vendor_name, args.layer_name)

    outfile = os.path.join(outdir, 'android_install.py')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_layer_install_helper(handle, args.vendor_name, args.layer_name)

    return 0

if __name__ == '__main__':
    sys.exit(main())
