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
import xml.etree.ElementTree as ET

# These functions are manually created as fully exported entry points in the
# layer library, and are not part of the dynamic dispatch behavior
MANUAL_FUNCTIONS = {
    # Exposed by loader so not handled by the layer
    'vkEnumerateInstanceVersion',
    # Exposed as symbols managed by the loader so not handled by the layer
    'vkGetInstanceProcAddr',
    'vkGetDeviceProcAddr',
    # Exposed by layer as explicit entry points
    'vkEnumerateDeviceLayerProperties',
    'vkEnumerateInstanceExtensionProperties',
    'vkEnumerateInstanceLayerProperties',
}

# These functions are manually exported, but we can use driver forwarding
FORWARD_WITHOUT_INTERCEPT = {
    'vkEnumerateDeviceExtensionProperties',
    'vkEnumerateInstanceExtensionProperties',
}

# These functions are found via the loader-injected chain info
INTERCEPT_WITHOUT_FORWARD = {
    'vkCreateDevice',
    'vkCreateInstance',
}

# Filter out extensions from these vendors by default
EXTENSION_VENDOR_FILTER = {
    'AMD',
    'ANDROID',
    'GOOGLE',
    'HUAWEI',
    'IMG',
    'INTEL',
    'LUNARG',
    'MSFT',
    'NV',
    'NVX',
    'QCOM',
    'SEC',
    'VALVE',
}

# Filter out KHR and EXT extensions that we don't support or need on Android
EXTENSION_NAME_FILTER = {
    'VK_KHR_video_queue',
    'VK_KHR_video_decode_queue',
    'VK_KHR_video_encode_queue',
    'VK_EXT_acquire_drm_display',
    'VK_EXT_headless_surface',
}

INSTANCE_FUNCTION_PARAM_TYPE = {
    'const VkInstanceCreateInfo*',
    'VkInstance',
    'VkPhysicalDevice',
}

DEVICE_FUNCTION_PARAM_TYPE = {
    'VkCommandBuffer',
    'VkDevice',
    'VkQueue',
}

class VersionMapping(dict):
    '''
    Create a mapping of function => required version.

    The required version is a list of either:
      * An API version string ('1.0', '1.1', etc)
      * An extension string (e.g. 'VK_KHR_swapchain')

    The required version is a list because some APIs can be added by multiple
    possible extensions.
    '''

    def __init__(self, root):
        '''
        Load all functions that are defined in the XML.
        '''
        self.load_api_core_versions(root)
        self.load_api_extensions(root)

    def load_api_core_versions(self, root):
        '''
        Load all core API functions that should be added to the map.
        '''
        # Find all the formally supported API feature groups
        features = root.findall('.//feature')
        for feature in features:
            # Omit commands that are specific to VulkanSC
            apis = feature.get('api', 'vulkan').split(',')
            if 'vulkan' not in apis:
                continue

            # Get the API version
            api_version = feature.get('number')

            # Get the commands added in this API version
            commands = feature.findall('.//command')
            for command in commands:
                fname = command.get('name')
                assert fname not in self, fname
                self[fname] = [(api_version, None)]

    def load_api_extensions(self, root):
        '''
        Load all extension API functions that should be added to the map.
        '''
        # Find all the formally supported API feature groups
        extensions = root.findall('.//extension')
        for extension in extensions:
            ext_name = extension.get('name')

            # Omit extensions that are specific to VulkanSC
            apis = extension.get('supported', 'vulkan').split(',')
            if 'vulkan' not in apis:
                continue

            # Omit extensions that are not on the Android platform
            platforms = extension.get('platform', None)
            is_android = True
            if platforms:
                platforms = platforms.split(',')
                is_android = 'android' in platforms

            if not is_android:
                continue

            # Omit extensions that are from other vendors
            vendor = ext_name.split("_")[1]
            if vendor in EXTENSION_VENDOR_FILTER:
                continue

            # Omit extensions that are explicitly not supported e.g. video
            if ext_name in EXTENSION_NAME_FILTER:
                continue

            # Note, not all extensions have commands
            commands = extension.findall('.//command')
            for command in commands:
                fname = command.get('name')
                if fname not in self:
                    self[fname] = []

                self[fname].append((ext_name, platforms))

    def get_platform_define(self, command):
        '''
        Determine the platform define for a command mapping.
        '''
        mappings = self[command]

        platforms = set()

        for mapping in mappings:
            # No platform always takes precedence
            if mapping[1] is None:
                platforms = set()
                break

            # Limited platforms accumulate
            platforms.update(set(mapping[1]))

        # Currently only handle no define mapping or Android only
        if not platforms:
            return None

        if len(platforms) == 1 and 'android' in platforms:
            return 'VK_USE_PLATFORM_ANDROID_KHR'

        assert False, f'Unhandled mapping: {platforms}'


class Command:

    def __init__(self, mapping, root):
        # Omit commands that are specific to VulkanSC
        apis = root.get('api', 'vulkan').split(',')
        if 'vulkan' not in apis:
            raise NotImplementedError

        # Function is an alias
        if len(root) == 0:
            self.name = root.get('name')
            self.alias = root.get('alias')

        # Function is a standalone specification
        else:
            self.alias = None

            # Extract the basic function prototype
            proto = root[0]
            text = proto.text.strip() if proto.text else ''
            tail = proto.tail.strip() if proto.tail else ''
            assert proto.tag == 'proto', ET.tostring(proto)
            assert len(proto) == 2, ET.tostring(proto)
            assert text == '' and tail == '', f'`{text}`, `{tail}`'

            rtype = proto[0]
            text = rtype.text.strip()
            tail = rtype.tail.strip() if rtype.tail else ''
            assert rtype.tag == 'type', ET.tostring(proto)
            assert text and tail == '', f'`{text}`, `{tail}`'
            self.rtype = text

            fname = proto[1]
            text = fname.text.strip()
            tail = fname.tail.strip() if fname.tail else ''
            assert fname.tag == 'name', ET.tostring(proto)
            assert text and tail == '', f'`{text}`, `{tail}`'
            self.name = text
            self.params = []

            # Extract the function parameters
            parameters = root.findall('./param')
            for node in parameters:
                assert len(node) == 2, ET.tostring(node)

                # Omit parameters that are specific to VulkanSC
                apis = node.get('api', 'vulkan').split(',')
                if 'vulkan' not in apis:
                    continue

                valid_text = ('', 'const', 'struct', 'const struct')
                text = node.text.strip() if node.text else ''
                tail = node.tail.strip() if node.tail else ''
                assert text in valid_text and tail == '', f'`{text}`, `{tail}`'

                type_prefix = f'{text} ' if text else ''

                ptype = node[0]
                valid_tail = ('', '*', '**', '* const*')
                text = ptype.text.strip()
                tail = ptype.tail.strip() if ptype.tail else ''
                assert ptype.tag == 'type', ET.tostring(proto)
                assert text and tail in valid_tail, f'`{text}`, `{tail}`'

                type_postfix = f'{tail}' if tail else ''

                ptype = f'{type_prefix}{text}{type_postfix}'

                pname = node[1]
                text = pname.text.strip()
                tail = pname.tail.strip() if pname.tail else ''
                assert pname.tag == 'name', ET.tostring(proto)
                assert text
                assert tail == '' or re.match(r'^\[\d+]$', tail)

                self.params.append((ptype, text, tail))

        # Filter out functions that are not dynamically dispatched
        if self.name in MANUAL_FUNCTIONS:
            raise NotImplementedError

        # Filter out functions that are not in our supported mapping
        if self.name not in mapping:
            raise NotImplementedError

        # Identify instance vs device functions
        if not self.alias:
            dispatch_type = self.params[0][0]
            if dispatch_type in INSTANCE_FUNCTION_PARAM_TYPE:
                self.dispatch_type = 'instance'
            elif dispatch_type in DEVICE_FUNCTION_PARAM_TYPE:
                self.dispatch_type = 'device'
            else:
                assert False, f'Unknown dispatch: {dispatch_type} {self.name}'


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
                        help='Layer vendor name (optional)')

    parser.add_argument('--layer-name', default=None,
                        help='Layer name (optional)')

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

    # Parse the XML headers
    tree = ET.parse('./khronos/vulkan/registry/vk.xml')
    root = tree.getroot()

    # Parse function to API version or extension mapping
    mapping = VersionMapping(root)

    # Parse function prototypes
    nodes = root.findall('.//commands/command')

    commands = []
    for node in nodes:
        # Parse, skipping commands for sibling APIs
        try:
            commands.append(Command(mapping, node))
        except NotImplementedError:
            pass

    # Flatten out command alias cross-references
    for command in commands:
        alias_name = command.alias
        if alias_name:
            aliases = [x for x in commands if x.name == alias_name]
            assert len(aliases) == 1

            command.rtype = aliases[0].rtype
            command.params = aliases[0].params
            command.dispatch_type = aliases[0].dispatch_type

        # Remove the alias to avoid confusion in future
        del command.alias

    # Sort functions into alphabetical order
    commands.sort(key=lambda x: x.name)

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
