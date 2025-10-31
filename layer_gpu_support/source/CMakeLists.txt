# SPDX-License-Identifier: MIT
# -----------------------------------------------------------------------------
# Copyright (c) 2025 Arm Limited
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
    set(VK_LAYER VkLayerGPUSupport_sym)
    set(VK_LAYER_STRIP libVkLayerGPUSupport.so)
else()
    set(VK_LAYER VkLayerGPUSupport)
endif()

# Set strings used by configure
set(LGL_LAYER_NAME_STR "VK_LAYER_LGL_gpu_support")
set(LGL_LAYER_DESC_STR "VkLayerGPUSupport by LGL")

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
        layer_config.cpp
        layer_device_functions_dispatch.cpp
        layer_device_functions_image.cpp
        layer_device_functions_swapchain.cpp
        layer_device_functions_allocate_memory.cpp
        layer_device_functions_pipelines.cpp
        layer_device_functions_queue.cpp
        layer_device_functions_render_pass.cpp
        layer_device_functions_trace_rays.cpp
        layer_device_functions_transfer.cpp
        layer_instance_functions_get_physical_properties.cpp)

target_include_directories(
    ${VK_LAYER} PRIVATE
        ./
        ../../source_common/
        ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(
    ${VK_LAYER} SYSTEM PRIVATE
        ../../source_third_party/
        ../../source_third_party/khronos/vulkan/include/
        ../../source_third_party/khronos/vulkan-utilities/include/)

lgl_set_build_options(${VK_LAYER})

target_link_libraries(
    ${VK_LAYER}
        lib_layer_framework
        $<$<PLATFORM_ID:Android>:log>)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(
        TARGET "${VK_LAYER}" POST_BUILD
        COMMAND ${CMAKE_STRIP}
        ARGS --strip-all -o ${VK_LAYER_STRIP} $<TARGET_FILE:${VK_LAYER}>
        COMMENT "Stripped lib${VK_LAYER}.so to ${VK_LAYER_STRIP}")
endif()

add_clang_tools()
