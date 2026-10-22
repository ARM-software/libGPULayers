#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2024-2026 Arm Limited
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
import re
import shutil
import sys
from pathlib import Path
from typing import TextIO


COMMON_DIRECTORIES = (
    'cmake',
    'docs',
    'generator',
    'lglpy',
    'source_common',
)

THIRD_PARTY_DIRECTORIES = (
    'gtest',
    'khronos',
)

COMMON_FILES = (
    'CMakeLists.txt',
    'lgl_android_install.py',
    'lgl_host_server.py',
    'LICENSE.txt',
    'README.md',
)

COPY_IGNORE_PATTERNS = (
    '.git',
    '__pycache__',
    '*.pyc',
)

STANDALONE_EXCLUDE_START = '<!-- #if !defined(standalone) -->'
STANDALONE_EXCLUDE_END = '<!-- #endif -->'


def load_template(path: str) -> str:
    '''
    Load a template from the generator template directory.

    Args:
        path: The file name in the template directory.

    Returns:
        The loaded text template.
    '''
    base_dir = Path(__file__).parent
    template_file = base_dir / 'vk_codegen' / path

    # Load the data from the file
    with template_file.open('r', encoding='utf-8') as handle:
        data = handle.read()

    return data


def get_layer_api_name(vendor: str, layer: str) -> str:
    '''
    Generate the layer string name for the new layer used by the loader.
    Names are of the form "VK_LAYER_<VENDOR>_<layer>_<name>" where vendor
    is in upper case, and the layer name is in lower case.

    Args:
        vendor: The layer vendor tag.
        layer: The name of the layer.

    Returns:
        The layer string name used by the loader.
    '''
    pattern = re.compile(r'^VkLayer(\w+)$')
    match = pattern.match(layer)
    assert match

    name = match.group(1)
    parts = []
    part = None

    for char in name:
        is_uc = char.isupper()
        if part is None:
            is_last_uc = False
        else:
            is_last_uc = part[-1].isupper()

        if (is_uc and not is_last_uc) or not part:
            if part:
                parts.append(part.lower())
            part = char
        else:
            part += char

    if part:
        parts.append(part.lower())

    name_parts = ('VK_LAYER', vendor.upper(), *parts)
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


def copy_resource(src_dir: Path, dst_dir: Path) -> None:
    '''
    Copy a directory of resources to another location.

    Args:
        src_dir: The source directory location.
        out_dir: The destination directory location.
    '''
    dst_dir = dst_dir.resolve()
    dst_dir.mkdir(parents=True, exist_ok=True)
    shutil.copytree(
        src_dir,
        dst_dir,
        dirs_exist_ok=True,
        ignore=shutil.ignore_patterns(*COPY_IGNORE_PATTERNS))


def copy_standalone_readme(src_file: Path, dst_file: Path) -> None:
    '''
    Copy the project README, excluding non-standalone content blocks.

    Args:
        src_file: The source README file.
        dst_file: The destination README file.
    '''
    output = []
    excluding = False

    with src_file.open('r', encoding='utf-8') as handle:
        for line in handle:
            marker = line.strip()
            if marker == STANDALONE_EXCLUDE_START:
                if excluding:
                    raise ValueError('Nested standalone exclusion block')
                excluding = True
            elif marker == STANDALONE_EXCLUDE_END:
                if not excluding:
                    raise ValueError('Unmatched standalone exclusion end')
                excluding = False
            elif not excluding:
                output.append(line)

    if excluding:
        raise ValueError('Unterminated standalone exclusion block')

    with dst_file.open('w', encoding='utf-8', newline='\n') as handle:
        handle.writelines(output)


def copy_common_resources(src_dir: Path, dst_dir: Path) -> None:
    '''
    Copy common project resources for a standalone layer project.

    Args:
        src_dir: The source project root directory.
        dst_dir: The destination project root directory.
    '''
    for directory in COMMON_DIRECTORIES:
        source = src_dir / directory
        destination = dst_dir / directory
        copy_resource(source, destination)

    for directory in THIRD_PARTY_DIRECTORIES:
        source = src_dir / 'source_third_party' / directory
        destination = dst_dir / 'source_third_party' / directory
        copy_resource(source, destination)

    for filename in COMMON_FILES:
        source = src_dir / filename
        destination = dst_dir / filename
        if filename == 'README.md':
            copy_standalone_readme(source, destination)
        else:
            shutil.copy2(source, destination)


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

    parser.add_argument('--root-dir', metavar='DIR',
                        help='project root directory (optional)')

    parser.add_argument('--layer-dir', metavar='DIR', required=True,
                        help='layer directory within the project root')

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

    base_dir = Path(__file__).parent
    project_dir = base_dir.parent.resolve()

    # A root outside this checkout creates a standalone project. If no root is
    # specified, or this checkout is specified, generate a local layer.
    if args.root_dir:
        root_dir = Path(args.root_dir).resolve()
    else:
        root_dir = project_dir

    standalone = root_dir != project_dir
    if standalone and root_dir.is_relative_to(project_dir):
        print('ERROR: Standalone root dir must not be inside current project')
        return 1

    layer_dir = Path(args.layer_dir)
    if layer_dir.is_absolute():
        outdir = layer_dir.resolve()
    else:
        outdir = (root_dir / layer_dir).resolve()

    if outdir.parent != root_dir:
        print('ERROR: Layer dir must be a direct child of the root')
        return 1

    chk_dir = root_dir if standalone else outdir
    chk_dir_t = 'Root' if standalone else 'Layer'

    # Check that output directory is either empty or over-writable
    if chk_dir.exists():
        if not chk_dir.is_dir():
            print(f'ERROR: {chk_dir_t} location "{chk_dir}" is not a dir')
            return 1

        if any(chk_dir.iterdir()) and not args.overwrite:
            print(f'ERROR: {chk_dir_t} dir "{chk_dir}" is not empty')
            return 1

    # Copy project-wide resources for standalone output.
    if standalone:
        root_dir.mkdir(parents=True, exist_ok=True)
        copy_common_resources(project_dir, root_dir)

    # Generate static resources
    source_dir = base_dir / 'vk_layer'
    copy_resource(source_dir, outdir)

    # Generate templated resources
    outfile = outdir / 'CMakeLists.txt'
    with outfile.open('w', encoding='utf-8', newline='\n') as handle:
        generate_root_cmake(handle, args.project_name, args.layer_name)

    outfile = outdir / 'source' / 'CMakeLists.txt'
    with outfile.open('w', encoding='utf-8', newline='\n') as handle:
        generate_source_cmake(handle, args.vendor_name, args.layer_name)

    outfile = outdir / 'manifest.json'
    with outfile.open('w', encoding='utf-8', newline='\n') as handle:
        generate_install_manifest(handle, args.vendor_name, args.layer_name)

    return 0


if __name__ == '__main__':
    sys.exit(main())
