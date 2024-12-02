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

set(BUILD_TARGET lib_layer_framework)

add_library(
    ${BUILD_TARGET} STATIC
        device_functions.cpp
        instance_functions.cpp)

target_include_directories(
    ${BUILD_TARGET} PRIVATE
        # Note, this includes from the layer-specific tree
        ${PROJECT_SOURCE_DIR}/source
        ../)

target_include_directories(
    ${BUILD_TARGET} SYSTEM PRIVATE
        ../../khronos/vulkan/include)

lgl_set_build_options(${BUILD_TARGET})

# TODO: Log tag needs to come from child project
target_compile_definitions(
    ${BUILD_TARGET} PRIVATE
        $<$<PLATFORM_ID:Android>:VK_USE_PLATFORM_ANDROID_KHR=1>
        $<$<PLATFORM_ID:Android>:LGL_LOG_TAG="${LGL_LOG_TAG}">)

# TODO: Remove this?
target_link_libraries(
    ${BUILD_TARGET}
        $<$<PLATFORM_ID:Android>:log>)
