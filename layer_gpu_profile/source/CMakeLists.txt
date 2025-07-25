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

# Set output file names
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(VK_LAYER VkLayerGPUProfile_sym)
    set(VK_LAYER_STRIP libVkLayerGPUProfile.so)
else()
    set(VK_LAYER VkLayerGPUProfile)
endif()

# Set strings used by configure
set(LGL_LAYER_NAME_STR "VK_LAYER_LGL_gpu_profile")
set(LGL_LAYER_DESC_STR "VkLayerGPUProfile by LGL")

# Vulkan layer library
configure_file(
    version.hpp.in
    version.hpp
    ESCAPE_QUOTES @ONLY)

add_library(
    ${VK_LAYER} SHARED
        ../../source_common/framework/entry.cpp
        device.cpp
        instance.cpp
        layer_comms.cpp
        layer_config.cpp
        layer_device_functions_command_buffer.cpp
        layer_device_functions_command_pool.cpp
        layer_device_functions_debug.cpp
        layer_device_functions_dispatch.cpp
        layer_device_functions_queue.cpp
        layer_device_functions_render_pass.cpp
        layer_device_functions_trace_rays.cpp
        layer_device_functions_transfer.cpp
        submit_visitor.cpp)

target_include_directories(
    ${VK_LAYER} PRIVATE
        ./
        ../../source_common/
        ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(
    ${VK_LAYER} SYSTEM PRIVATE
        ../../source_third_party/
        ../../source_third_party/khronos/vulkan/include/
        ../../source_third_party/khronos/vulkan-utilities/include/
        ../../source_third_party/libGPUCounters/backend/device/include/
        ../../source_third_party/libGPUCounters/hwcpipe/include/
        ../../source_third_party/protopuf/include/)

# We use libGPUCounters in the device structure, so add to framework includes
target_include_directories(
    lib_layer_framework SYSTEM PRIVATE
        ../../source_third_party/libGPUCounters/backend/device/include/
        ../../source_third_party/libGPUCounters/hwcpipe/include/)

lgl_set_build_options(${VK_LAYER})

target_link_libraries(
    ${VK_LAYER}
        lib_layer_comms
        lib_layer_framework
        lib_layer_trackers
        device
        hwcpipe
        $<$<PLATFORM_ID:Android>:log>)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(
        TARGET "${VK_LAYER}" POST_BUILD
        COMMAND ${CMAKE_STRIP}
        ARGS --strip-all -o ${VK_LAYER_STRIP} $<TARGET_FILE:${VK_LAYER}>
        COMMENT "Stripped lib${VK_LAYER}.so to ${VK_LAYER_STRIP}")
endif()

add_clang_tools()
