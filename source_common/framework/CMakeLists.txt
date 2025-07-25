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

set(LIB_BINARY lib_layer_framework)

add_library(
    ${LIB_BINARY} STATIC
        device_functions.cpp
        instance_functions.cpp
        manual_functions.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_core.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_ext.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_khr.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_manual.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_utils.cpp
        ../../source_third_party/khronos/vulkan-utilities/src/vulkan/vk_safe_struct_vendor.cpp)

target_include_directories(
    ${LIB_BINARY} PRIVATE
        ../
        # Include from the layer-specific trees
        ${PROJECT_SOURCE_DIR}/source
        ${PROJECT_BINARY_DIR}/source)

target_include_directories(
    ${LIB_BINARY} SYSTEM PRIVATE
        ../
        ../../source_third_party/
        ../../source_third_party/khronos/vulkan/include/
        ../../source_third_party/khronos/vulkan-utilities/include/)

lgl_set_build_options(${LIB_BINARY})

add_clang_tools()
