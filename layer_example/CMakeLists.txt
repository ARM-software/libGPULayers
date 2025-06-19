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

cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRES ON)

project(VkLayerExample VERSION 1.0.0)

# Common configuration
set(LGL_LOG_TAG "VkLayerExample")
set(LGL_CONFIG_TRACE 0)
set(LGL_CONFIG_LOG 1)

include(../source_common/compiler_helper.cmake)
include(../cmake/clang-tools.cmake)

# Build steps
add_subdirectory(source)
add_subdirectory(../source_common/framework source_common/framework)
