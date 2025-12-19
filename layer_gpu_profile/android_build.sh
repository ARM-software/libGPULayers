#!/usr/bin/env bash
# SPDX-License-Identifier: MIT
# ----------------------------------------------------------------------------
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
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Configuration

# Exit immediately if any component command errors
set -e

BUILD_DIR_64=build_arm64
BUILD_DIR_PACK=build_package

# ----------------------------------------------------------------------------
# Process command line options
if [ "$#" -lt 1 ]; then
    BUILD_TYPE=Release
else
    BUILD_TYPE=$1
fi

# Process command line options
if [ "$#" -lt 2 ]; then
    PACKAGE=0
else
    PACKAGE=$2
fi

if [ "${PACKAGE}" -gt "0" ]; then
    echo "Building a ${BUILD_TYPE} build with packaging"
else
    echo "Building a ${BUILD_TYPE} build without packaging"
fi

# ----------------------------------------------------------------------------
# Build the 64-bit layer
mkdir -p ${BUILD_DIR_64}
pushd ${BUILD_DIR_64}

cmake \
    -DCMAKE_SYSTEM_NAME=Android \
    -DANDROID_PLATFORM=29 \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_TOOLCHAIN=clang \
    -DANDROID_STL=c++_static \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -DCMAKE_TOOLCHAIN_FILE="${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake" \
    -DCMAKE_WARN_DEPRECATED=OFF \
    ..

cmake --build . -j4

popd

# ----------------------------------------------------------------------------
# Build the release package
if [ "${PACKAGE}" -gt "0" ]; then
    # Setup the package directories
    mkdir -p ${BUILD_DIR_PACK}/bin/android/arm64

    # Install the 64-bit layer
    cp ${BUILD_DIR_64}/source/*.so ${BUILD_DIR_PACK}/bin/android/arm64
fi
