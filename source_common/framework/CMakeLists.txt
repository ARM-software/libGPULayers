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

# Compiler accepts GNU-style command line options
set(is_gnu_fe1 "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>")

# Compiler accepts AppleClang-style command line options, which is also GNU-style
set(is_gnu_fe2 "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},AppleClang>")

# Compiler accepts GNU-style command line options
set(is_gnu_fe "$<OR:${is_gnu_fe1},${is_gnu_fe2}>")

# Compiler is upstream clang with the standard frontend
set(is_clang "$<AND:${is_gnu_fe},$<CXX_COMPILER_ID:Clang,AppleClang>>")

set(DIR_TARGET layer_common)

add_library(
    ${DIR_TARGET} STATIC
        device_functions.cpp
        device.cpp
        entry.cpp
        instance_functions.cpp
        instance.cpp)

target_include_directories(
    ${DIR_TARGET} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        .)

target_include_directories(
    ${DIR_TARGET} SYSTEM PRIVATE
        ../../khronos/vulkan/include)

target_compile_options(
    ${DIR_TARGET} PRIVATE
        -fvisibility=hidden
        -fvisibility-inlines-hidden
        -fno-exceptions
        -fno-rtti
        -fpic
        -Wall
        -Wextra
        -Wno-missing-field-initializers
        $<${is_clang}:-Wdocumentation>)

# TODO: Log tag needs to come from child project
target_compile_definitions(
    ${DIR_TARGET} PRIVATE
        $<$<PLATFORM_ID:Android>:VK_USE_PLATFORM_ANDROID_KHR=1>
        $<$<PLATFORM_ID:Android>:ARM_LOG_TAG="VkLayerFizzbuzz">)

# TODO: Remove this?
target_link_libraries(
    ${DIR_TARGET}
        $<$<PLATFORM_ID:Android>:log>)
