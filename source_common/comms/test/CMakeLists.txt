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

# Build client_server unit test module
set(TEST_BINARY unittest_comms)

add_executable(
    ${TEST_BINARY}
        unittest_comms.cpp
        comms_test_server.cpp)

target_include_directories(
    ${TEST_BINARY} PRIVATE
        ../../
        ../../../source_third_party/
        ../../../source_third_party/khronos/vulkan/include
        ${gtest_SOURCE_DIR}/include)

target_link_libraries(
    ${TEST_BINARY} PRIVATE
        lib_layer_comms
        gtest_main)

add_test(
    NAME ${TEST_BINARY}
    COMMAND ${TEST_BINARY})

install(
    TARGETS ${TEST_BINARY}
    DESTINATION bin)

# Build client-only unit test module using external Python server
set(TEST_BINARY unittest_comms_client)

add_executable(
    ${TEST_BINARY}
        unittest_comms_client.cpp)

target_include_directories(
    ${TEST_BINARY} PRIVATE
        ../../
        ${gtest_SOURCE_DIR}/include)

target_link_libraries(
    ${TEST_BINARY} PRIVATE
        lib_layer_comms
        gtest_main)

# Exclude from ctest for now because it needs user to manually run the
# external server program before the test can pass
# add_test(
#     NAME ${TEST_BINARY}
#     COMMAND ${TEST_BINARY})

install(
    TARGETS ${TEST_BINARY}
    DESTINATION bin)

