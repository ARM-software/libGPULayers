/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022-2024 Arm Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * ----------------------------------------------------------------------------
 */

/**
 * @file
 * This module implements miscellaneous utility functions.
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <string>

/**
 * @brief Macro to stringize a value.
 */
#define STR(x) #x

/**
 * @brief Macro to mark a variable as unused.
 */
#define UNUSED(x) ((void)x);

/**
 * @brief Format a string using printf formatting template strings.
 *
 * @param format   The template string.
 * @param args     The variadic values used to populate the template.
 */
template<typename ... Args>
std::string fmt_string(
    const std::string& format,
    Args ... args
) {
    // Determine size, adding one for the trailing nul
    int size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
    if (size <= 0)
    {
        assert(false);
        return "";
    }

    // Create the return string
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1);
}

/**
 * @brief Test if an element exists in an iterable container.
 *
 * @param elem   The element to search for.
 * @param cont   The container to search.
 *
 * @return @c true if the item was found, else @c false.
 */
template<typename E, typename C>
bool isIn(
    const E& elem,
    const C& cont
) {
    return std::find(std::begin(cont), std::end(cont), elem) != std::end(cont);
}

/**
 * @brief Test if an element exists in a mappable container.
 *
 * @param elem   The element to search for.
 * @param cont   The container to search.
 *
 * @return @c true if the item was found, else @c false.
 */
template<typename E, typename C>
bool isInMap(
    const E& elem,
    const C& cont
) {
    return cont.find(elem) != cont.end();
}

/**
 * @brief Get a displayable pointer.
 *
 * On 64-bit systems this strips the MTE tag.
 *
 * @return The displayable pointer
 */
static inline uintptr_t getDisplayPointer(
    void* pointer
) {
    uintptr_t dispPointer = reinterpret_cast<uintptr_t>(pointer);

    if constexpr(sizeof(uintptr_t) == 8)
    {
        dispPointer &= 0x00FFFFFFFFFFFFFFull;
    }

    return dispPointer;
}
