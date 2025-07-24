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

# Compiler accepts MSVC-style command line options
set(is_msvc_fe "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},MSVC>")

# Compiler accepts GNU-style command line options
set(is_gnu_fe1 "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},GNU>")

# Compiler accepts AppleClang-style command line options, which is also GNU-style
set(is_gnu_fe2 "$<STREQUAL:${CMAKE_CXX_COMPILER_FRONTEND_VARIANT},AppleClang>")

# Compiler accepts GNU-style command line options
set(is_gnu_fe "$<OR:${is_gnu_fe1},${is_gnu_fe2}>")

# Compiler is Visual Studio cl.exe
set(is_msvccl "$<AND:${is_msvc_fe},$<CXX_COMPILER_ID:MSVC>>")

# Compiler is Visual Studio clangcl.exe
set(is_clangcl "$<AND:${is_msvc_fe},$<CXX_COMPILER_ID:Clang>>")

# Compiler is upstream clang with the standard frontend
set(is_clang "$<AND:${is_gnu_fe},$<CXX_COMPILER_ID:Clang,AppleClang>>")

# Utility macro to set standard compiler and linker options
macro(lgl_set_build_options BUILD_TARGET_NAME)

    # Layers are shared objects so must be position independent
    set_property(
        TARGET ${BUILD_TARGET_NAME}
        PROPERTY POSITION_INDEPENDENT_CODE ON)

    target_compile_options(
        ${BUILD_TARGET_NAME} PRIVATE
            # Minimize symbol visibility
            $<${is_gnu_fe}:-fvisibility=hidden>
            $<${is_gnu_fe}:-fvisibility-inlines-hidden>

            # Enable stricter warnings
            $<${is_gnu_fe}:-Wall>
            $<${is_gnu_fe}:-Wextra>
            $<${is_gnu_fe}:-Wpedantic>
            $<${is_gnu_fe}:-Werror>
            $<${is_gnu_fe}:-Wshadow>
            $<${is_gnu_fe}:-Wdouble-promotion>
            $<${is_clang}:-Wdocumentation>

            # Disable warnings we don't want
            $<${is_gnu_fe}:-Wno-unused-private-field>)

    target_compile_definitions(
        ${BUILD_TARGET_NAME} PRIVATE
            $<$<PLATFORM_ID:Android>:VK_USE_PLATFORM_ANDROID_KHR=1>
            $<$<PLATFORM_ID:Android>:LGL_LOG_TAG="${LGL_LOG_TAG}">
            CONFIG_TRACE=${LGL_CONFIG_TRACE}
            CONFIG_LOG=${LGL_CONFIG_LOG})
endmacro()
