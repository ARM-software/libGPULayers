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

from datetime import datetime
import os
import re
import sys
from typing import Optional, TextIO
import xml.etree.ElementTree as ET


# These functions are not part of the layer implementation
EXCLUDED_FUNCTIONS = {
    # Functions exposed by loader not the implementation
    'vkEnumerateInstanceVersion',
}

# These functions are excluded from generated dispatch tables
NO_DISPATCH_FUNCTIONS = {
    # Functions resolved by the loader not the implementation
    'vkCreateDevice',
    'vkCreateInstance',
    'vkEnumerateInstanceExtensionProperties',
    'vkGetDeviceProcAddr',
    'vkGetInstanceProcAddr',
}

# These functions are excluded from generated declarations
CUSTOM_FUNCTIONS = {
    'vkCreateDevice',
    'vkCreateInstance',
    'vkDestroyDevice',
    'vkDestroyInstance',
    'vkEnumerateDeviceExtensionProperties',
    'vkEnumerateDeviceLayerProperties',
    'vkEnumerateInstanceExtensionProperties',
    'vkEnumerateInstanceLayerProperties',
    'vkGetDeviceImageMemoryRequirementsKHR',
    'vkGetDeviceProcAddr',
    'vkGetInstanceProcAddr',
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


class VersionInfo(dict):
    '''
    Create a mapping of function => required version.

    The required version is a list of either:
      * An API version string ('1.0', '1.1', etc)
      * An extension string (e.g. 'VK_KHR_swapchain')

    The required version is a list because some APIs can be added by multiple
    possible extensions.
    '''

    def __init__(self, root: ET.Element):
        '''
        Load all functions that are defined in the XML.

        Args:
            root: The root of the Vulkan spec XML document.
        '''
        self.load_api_core_versions(root)
        self.load_api_extensions(root)

    def load_api_core_versions(self, root: ET.Element):
        '''
        Load all core API functions that should be added to the map.
        '''
        # Find all the formally supported API feature groups
        features = root.findall('.//feature')
        for feature in features:
            # Omit commands that are only used in VulkanSC
            apis = feature.get('api', 'vulkan').split(',')
            if 'vulkan' not in apis:
                continue

            # Get the API version
            api_version = feature.get('number')

            # Get the commands added in this API version
            parents = feature.findall(".//command/..")
            for parent in parents:
                # Skip functions in deprecated blocks
                if parent.tag == 'deprecate':
                    continue

                # Include all of the other blocks
                commands = parent.findall("command")
                for command in commands:
                    fname = command.get('name')
                    assert fname not in self, fname
                    self[fname] = [(api_version, None)]

    def load_api_extensions(self, root: ET.Element):
        '''
        Load all extension API functions that should be added to the map.

        Args:
            root: The root of the Vulkan spec XML document.
        '''
        # Find all the formally supported API feature groups
        extensions = root.findall('.//extension')
        for extension in extensions:
            ext_name = extension.get('name')
            assert ext_name is not None

            # Omit extensions that are specific to VulkanSC
            apis = extension.get('supported', 'vulkan').split(',')
            if 'vulkan' not in apis:
                continue

            # Omit extensions that are not on the Android platform
            platform = extension.get('platform', None)
            is_android = True
            platform_list = None
            if platform:
                platform_list = platform.split(',')
                is_android = 'android' in platform_list

            # TODO: Relax this and allow other operating systems
            if not is_android:
                continue

            # Omit extensions that are from other vendors
            vendor = ext_name.split('_')[1]
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

                self[fname].append((ext_name, platform_list))

    def get_platform_define(self, command: str) -> Optional[str]:
        '''
        Determine the platform define needed for a command mapping.

        Args:
            command: The name of the command to process.
        '''
        mappings = self[command]

        platforms = set()  # type: set[str]

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
    '''
    Parsed specification of a single Vulkan API entry point.

    Attributes:
        name: Name of this command.
        dispatch_type: Is this 'instance' or 'device' for dispatch?
        rtype: Function return type.
        params: Function parameter list.
        alias: Optional alias that provides the actual specification. For
           commands with an alias, the dispatch_type, return type, and params
           will be None until the alias is resolved.
    '''

    def __init__(self, mapping: VersionInfo, root: ET.Element):
        '''
        Create a new parsed Vulkan command entry.

        Args:
            mapping: The version information for that added this command.
            root: The XML node root for the command subtree.
        '''
        self.alias = None
        self.rtype = None
        self.params = None
        self.dispatch_type = None

        # Omit commands that are specific to VulkanSC
        apis = root.get('api', 'vulkan').split(',')
        if 'vulkan' not in apis:
            raise NotImplementedError

        # Function is an alias
        if len(root) == 0:
            self.name = root.get('name')
            assert self.name is not None

            self.alias = root.get('alias')
            assert self.alias is not None

        # Function is a standalone specification
        else:
            # Extract the basic function prototype
            proto = root[0]
            text = proto.text.strip() if proto.text else ''
            tail = proto.tail.strip() if proto.tail else ''
            assert proto.tag == 'proto', ET.tostring(proto)
            assert len(proto) == 2, ET.tostring(proto)
            assert text == '' and tail == '', f'`{text}`, `{tail}`'

            rtype = proto[0]
            assert rtype.text
            text = rtype.text.strip()
            tail = rtype.tail.strip() if rtype.tail else ''
            assert rtype.tag == 'type', ET.tostring(proto)
            assert text and tail == '', f'`{text}`, `{tail}`'
            self.rtype = text

            fname = proto[1]
            assert fname.text
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

                valid_tail = ('', '*', '**', '* const*')
                ptype = node[0]
                assert ptype.text
                text = ptype.text.strip()
                tail = ptype.tail.strip() if ptype.tail else ''
                assert ptype.tag == 'type', ET.tostring(proto)
                assert text and tail in valid_tail, f'`{text}`, `{tail}`'

                type_postfix = f'{tail}' if tail else ''

                ptype_str = f'{type_prefix}{text}{type_postfix}'

                pname = node[1]
                assert pname.text
                text = pname.text.strip()
                tail = pname.tail.strip() if pname.tail else ''
                assert pname.tag == 'name', ET.tostring(proto)
                assert text
                assert tail == '' or re.match(r'^\[\d+]$', tail)

                self.params.append((ptype_str, text, tail))

        # Filter out functions that are not dynamically dispatched
        if self.name in EXCLUDED_FUNCTIONS:
            raise NotImplementedError

        # Filter out functions that are not in our supported mapping
        if self.name not in mapping:
            raise NotImplementedError

        # Identify instance vs device functions
        if not self.alias:
            disp_type = self.params[0][0]
            if disp_type in INSTANCE_FUNCTION_PARAM_TYPE:
                self.dispatch_type = 'instance'
            elif disp_type in DEVICE_FUNCTION_PARAM_TYPE:
                self.dispatch_type = 'device'
            elif self.name.startswith('vkEnumerateInstance'):
                self.dispatch_type = 'instance'
            else:
                assert False, f'Unknown dispatch: {disp_type} {self.name}'


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


def write_copyright_header(file: TextIO) -> None:
    '''
    Write the standard license and copyright header to the file.

    Args:
        file: The file handle to write to.
    '''
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


def generate_instance_dispatch_table(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the instance dispatch table.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    data = load_template('instance_dispatch_table.txt')

    # Create a listing of API versions and API extensions
    itable_members = ['// Instance functions']
    dispatch_table_members = []
    dispatch_table_inits = []

    for command in commands:
        # Skip commands that are not instance commands
        if command.dispatch_type != 'instance':
            continue

        assert command.name
        plat_define = mapping.get_platform_define(command.name)
        ttype = f'PFN_{command.name}'

        if plat_define:
            itable_members.append(f'#if defined({plat_define})')

        itable_members.append(f'    ENTRY({command.name}),')

        if plat_define:
            itable_members.append('#endif')

        if command.name not in NO_DISPATCH_FUNCTIONS:
            if plat_define:
                dispatch_table_members.append(f'#if defined({plat_define})')
                dispatch_table_inits.append(f'#if defined({plat_define})')

            dispatch_table_members.append(f'    {ttype} {command.name};')
            dispatch_table_inits.append(f'    ENTRY({command.name});')

            if plat_define:
                dispatch_table_members.append('#endif')
                dispatch_table_inits.append('#endif')

    itable_members.append('\n// Device functions')

    for command in commands:
        if command.dispatch_type != 'device':
            continue

        assert command.name
        plat_define = mapping.get_platform_define(command.name)
        ttype = f'PFN_{command.name}'

        if plat_define:
            itable_members.append(f'#if defined({plat_define})')

        itable_members.append(f'    ENTRY({command.name}),')

        if plat_define:
            itable_members.append('#endif')

    data = data.replace('{ITABLE_MEMBERS}', '\n'.join(itable_members))
    data = data.replace('{DTABLE_MEMBERS}', '\n'.join(dispatch_table_members))
    data = data.replace('{DTABLE_INITS}', '\n'.join(dispatch_table_inits))
    file.write(data)


def generate_instance_decls(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the instance intercept declarations header.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    file.write('#pragma once\n')
    file.write('\n')

    file.write('// clang-format off\n')
    file.write('\n')

    file.write('#include <vulkan/vulkan.h>\n')
    file.write('\n')

    # Create a listing of API versions and API extensions
    for command in commands:
        if command.dispatch_type != 'instance':
            continue

        lines = []
        assert command.name

        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        # Explicitly delete the generic primary template
        lines.append('/* See Vulkan API for documentation. */')
        lines.append('/* Delete the generic match-all */')
        decl = f'template <typename T>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ') = delete;'
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)
        lines.append('')

        # Define the default_tag template
        lines.append('/* Default common code implementation. */')
        decl = f'template <>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}<default_tag>('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ');'
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)
        lines.append('')

        if plat_define:
            lines.append('#endif\n')

        file.write('\n'.join(lines))
        file.write('\n')

    file.write('// clang-format on\n')


def generate_instance_queries(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the instance intercept declarations header.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    file.write('#pragma once\n')
    file.write('\n')

    file.write('// clang-format off\n')
    file.write('\n')

    file.write('#include <vulkan/vulkan.h>\n')
    file.write('\n')

    # Create a listing of API versions and API extensions
    for command in commands:
        if command.dispatch_type != 'instance':
            continue

        lines = []
        assert command.name

        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        # Define the concept to test if user_tag specialization exists
        plist = []
        nlist = []
        for i, (ptype, pname, array) in enumerate(command.params):
            plist.append(f'{ptype} {pname}{array}')
            nlist.append(pname)
        plistStr = ', '.join(plist)
        nlistStr = ', '.join(nlist)

        lines.append('/* Test for user_tag availability. */')
        decl = f'template <typename T>\n' \
               f'concept hasLayerPtr_{command.name} = ' \
               f'requires(\n    {plistStr}\n) {{\n    layer_{command.name}<T>({nlistStr});\n}};'
        lines.append(decl)
        lines.append('')

        # Define the function pointer resolution
        lines.append('/* Function pointer resolution. */')
        decl = f'constexpr PFN_{command.name} getLayerPtr_{command.name}()\n' \
               f'{{\n' \
               f'    return [] <typename T>\n' \
               f'    {{\n' \
               f'        if constexpr(hasLayerPtr_{command.name}<T>)\n' \
               f'        {{\n' \
               f'            return layer_{command.name}<T>;\n' \
               f'        }}\n' \
               f'\n' \
               f'        return layer_{command.name}<default_tag>;\n' \
               f'    }}.operator()<user_tag>();\n' \
               f'}}'
        lines.append(decl)
        lines.append('')

        if plat_define:
            lines.append('#endif\n')

        file.write('\n'.join(lines))
        file.write('\n')

    file.write('// clang-format on\n')


def generate_instance_defs(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the instance intercept definitions.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    data = load_template('instance_defs.txt')

    # Create a listing of API versions and API extensions
    lines = []
    for command in commands:
        if command.dispatch_type != 'instance':
            continue

        assert command.name
        if command.name in CUSTOM_FUNCTIONS:
            continue

        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        lines.append('/* See Vulkan API for documentation. */')
        decl = f'template <>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}<default_tag>('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ''
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)

        dispatch = command.params[0][1]
        parmfwd = ', '.join([x[1] for x in command.params])
        retfwd = 'return ' if command.rtype != 'void' else ''

        lines.append(') {')
        lines.append('    LAYER_TRACE(__func__);\n')

        lines.append('    // Hold the lock to access layer-wide global store')
        lines.append('    std::unique_lock<std::mutex> lock { g_vulkanLock };')
        lines.append(f'    auto* layer = Instance::retrieve({dispatch});\n')

        lines.append('    // Release the lock to call into the driver')
        lines.append('    lock.unlock();')
        lines.append(f'    {retfwd}layer->driver.{command.name}({parmfwd});')

        lines.append('}\n')

        if plat_define:
            lines.append('#endif\n')

    data = data.replace('{FUNCTION_DEFS}', '\n'.join(lines))
    file.write(data)


def generate_device_dispatch_table(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the device dispatch table.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    data = load_template('device_dispatch_table.txt')

    # Create a listing of API versions and API extensions
    itable_members = []
    dispatch_table_members = []
    dispatch_table_inits = []

    for command in commands:
        if command.dispatch_type != 'device':
            continue

        assert command.name
        plat_define = mapping.get_platform_define(command.name)
        ttype = f'PFN_{command.name}'

        if plat_define:
            itable_members.append(f'#if defined({plat_define})')

        itable_members.append(f'    ENTRY({command.name}),')

        if plat_define:
            itable_members.append('#endif')

        if command.name not in NO_DISPATCH_FUNCTIONS:
            if plat_define:
                dispatch_table_members.append(f'#if defined({plat_define})')
                dispatch_table_inits.append(f'#if defined({plat_define})')

            dispatch_table_members.append(f'    {ttype} {command.name};')
            dispatch_table_inits.append(f'    ENTRY({command.name});')

            if plat_define:
                dispatch_table_members.append('#endif')
                dispatch_table_inits.append('#endif')

    data = data.replace('{ITABLE_MEMBERS}', '\n'.join(itable_members))
    data = data.replace('{DTABLE_MEMBERS}', '\n'.join(dispatch_table_members))
    data = data.replace('{DTABLE_INITS}', '\n'.join(dispatch_table_inits))
    file.write(data)


def generate_device_decls(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the device intercept declarations header.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''

    # Write the copyright header to the file
    write_copyright_header(file)

    file.write('#pragma once\n')
    file.write('\n')

    file.write('// clang-format off\n')
    file.write('\n')

    file.write('#include <vulkan/vulkan.h>\n\n')
    file.write('#include "framework/utils.hpp"\n')
    file.write('\n')

    # Create a listing of API versions and API extensions
    for command in commands:
        if command.dispatch_type != 'device':
            continue

        assert command.name

        lines = []
        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        # Explicitly delete the generic primary template
        lines.append('/* See Vulkan API for documentation. */')
        lines.append('/* Delete the generic match-all */')
        decl = f'template <typename T>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ') = delete;'
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)
        lines.append('')

        # Define the default_tag template
        lines.append('/* Default common code implementation. */')
        decl = f'template <>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}<default_tag>('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ');'
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)
        lines.append('')

        if plat_define:
            lines.append('#endif\n')

        file.write('\n'.join(lines))
        file.write('\n')

    file.write('// clang-format on\n')


def generate_device_defs(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the device intercept definitions.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''
    # Write the copyright header to the file
    write_copyright_header(file)

    data = load_template('device_defs.txt')

    # Create a listing of API versions and API extensions
    lines = []
    for command in commands:
        if command.dispatch_type != 'device':
            continue

        assert command.name
        if command.name in CUSTOM_FUNCTIONS:
            continue

        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        lines.append('/* See Vulkan API for documentation. */')
        decl = f'template <>\n' \
               f'VKAPI_ATTR {command.rtype} ' \
               f'VKAPI_CALL layer_{command.name}<default_tag>('
        lines.append(decl)

        for i, (ptype, pname, array) in enumerate(command.params):
            ending = ','
            if i == len(command.params) - 1:
                ending = ''
            parl = f'    {ptype} {pname}{array}{ending}'
            lines.append(parl)

        dispatch = command.params[0][1]
        parmfwd = ', '.join([x[1] for x in command.params])
        retfwd = 'return ' if command.rtype != 'void' else ''

        lines.append(') {')
        lines.append('    LAYER_TRACE(__func__);\n')

        lines.append('    // Hold the lock to access layer-wide global store')
        lines.append('    std::unique_lock<std::mutex> lock { g_vulkanLock };')
        lines.append(f'    auto* layer = Device::retrieve({dispatch});\n')

        lines.append('    // Release the lock to call into the driver')
        lines.append('    lock.unlock();')
        lines.append(f'    {retfwd}layer->driver.{command.name}({parmfwd});')

        lines.append('}\n')

        if plat_define:
            lines.append('#endif\n')

    data = data.replace('{FUNCTION_DEFS}', '\n'.join(lines))
    file.write(data)


def generate_device_queries(
        file: TextIO, mapping: VersionInfo, commands: list[Command]) -> None:
    '''
    Generate the device intercept queries header.

    Args:
        file: The file to write.
        mapping: The version mapping information for the commands.
        commands: The list of commands read from the spec.
    '''

    # Write the copyright header to the file
    write_copyright_header(file)

    file.write('#pragma once\n')
    file.write('\n')

    file.write('// clang-format off\n')
    file.write('\n')

    file.write('#include <vulkan/vulkan.h>\n\n')
    file.write('#include "framework/utils.hpp"\n')
    file.write('\n')

    # Create a listing of API versions and API extensions
    for command in commands:
        if command.dispatch_type != 'device':
            continue

        assert command.name

        lines = []
        plat_define = mapping.get_platform_define(command.name)
        if plat_define:
            lines.append(f'#if defined({plat_define})\n')

        # Define the concept to test if user_tag specialization exists
        plist = []
        nlist = []
        for i, (ptype, pname, array) in enumerate(command.params):
            plist.append(f'{ptype} {pname}{array}')
            nlist.append(pname)
        plistStr = ', '.join(plist)
        nlistStr = ', '.join(nlist)

        lines.append('/* Test for user_tag availability. */')
        decl = f'template <typename T>\n' \
               f'concept hasLayerPtr_{command.name} = ' \
               f'requires(\n    {plistStr}\n) {{\n    layer_{command.name}<T>({nlistStr});\n}};'
        lines.append(decl)
        lines.append('')

        # Define the function pointer resolution
        lines.append('/* Function pointer resolution. */')
        decl = f'constexpr PFN_{command.name} getLayerPtr_{command.name}()\n' \
               f'{{\n' \
               f'    return [] <typename T>\n' \
               f'    {{\n' \
               f'        if constexpr(hasLayerPtr_{command.name}<T>)\n' \
               f'        {{\n' \
               f'            return layer_{command.name}<T>;\n' \
               f'        }}\n' \
               f'\n' \
               f'        return layer_{command.name}<default_tag>;\n' \
               f'    }}.operator()<user_tag>();\n' \
               f'}}'
        lines.append(decl)
        lines.append('')

        if plat_define:
            lines.append('#endif\n')

        file.write('\n'.join(lines))
        file.write('\n')

    file.write('// clang-format on\n')


def main() -> int:
    '''
    Tool main function.

    Returns:
        The process exit code.
    '''
    # Determine output directory location
    base_dir = os.path.dirname(__file__)
    outdir = os.path.join(base_dir, '..', 'source_common', 'framework')

    # Parse the XML headers
    tree = ET.parse('./source_third_party/khronos/vulkan/registry/vk.xml')
    root = tree.getroot()

    # Parse function to API version or extension mapping
    mapping = VersionInfo(root)

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

    # Sort functions into alphabetical order
    commands.sort(key=lambda x: str(x.name))

    # Generate dynamic resources
    outfile = os.path.join(outdir, 'instance_dispatch_table.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_instance_dispatch_table(handle, mapping, commands)

    outfile = os.path.join(outdir, 'instance_functions.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_instance_decls(handle, mapping, commands)

    outfile = os.path.join(outdir, 'instance_functions_query.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_instance_queries(handle, mapping, commands)

    outfile = os.path.join(outdir, 'instance_functions.cpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_instance_defs(handle, mapping, commands)

    outfile = os.path.join(outdir, 'device_dispatch_table.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_device_dispatch_table(handle, mapping, commands)

    outfile = os.path.join(outdir, 'device_functions.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_device_decls(handle, mapping, commands)

    outfile = os.path.join(outdir, 'device_functions_query.hpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_device_queries(handle, mapping, commands)

    outfile = os.path.join(outdir, 'device_functions.cpp')
    with open(outfile, 'w', encoding='utf-8', newline='\n') as handle:
        generate_device_defs(handle, mapping, commands)

    return 0


if __name__ == '__main__':
    sys.exit(main())
