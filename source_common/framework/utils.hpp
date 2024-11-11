/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024 Arm Limited
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
 * \file
 * This module implements miscellaneous utility functions.
 */

#pragma once

#include <cassert>
#include <memory>
#include <string>

#include <inttypes.h>
#include <sys/time.h>

#ifdef __ANDROID__
  #include <android/log.h>
#endif

/**
 * Tag type used for function dispatch;
 */
struct user_tag {};

/**
 * \brief Convert a dispatchable API handle to the underlying dispatch key.
 *
 * \param ptr   The dispatchable handle from the API.
 *
 * \return The dispatch key.
 */
static inline void* getDispatchKey(
    void* ptr
) {
    return *static_cast<void**>(ptr);
}

/**
 * \brief Macro to stringize a value.
 */
#define STR(x) #x

/**
 * \brief Macro to mark a variable as unused.
 */
#define UNUSED(x) ((void)x);

/**
 * \brief Enable to enable API entrypoint tracing to the log/logcat.
 */
#define CONFIG_TRACE 0

/**
 * \brief Enable to enable layer logging to the log/logcat.
 */
#define CONFIG_LOG 1

#if CONFIG_TRACE
  #ifdef __ANDROID__
    #if !defined(ARM_LOG_TAG)
        #error "ARM_LOG_TAG not defined"
    #endif

    #define LAYER_TRACE(x) __android_log_print(ANDROID_LOG_INFO, ARM_LOG_TAG, "API Trace: %s", x)
  #else
    #define LAYER_TRACE(x) printf("API Trace: %s\n", x)
  #endif
#else
    #define LAYER_TRACE(x)
#endif

#if CONFIG_LOG
  #ifdef __ANDROID__
    #if !defined(ARM_LOG_TAG)
        #error "ARM_LOG_TAG not defined"
    #endif

    #define LAYER_LOG(...) __android_log_print(ANDROID_LOG_DEBUG, ARM_LOG_TAG, __VA_ARGS__)
    #define LAYER_ERR(...) __android_log_print(ANDROID_LOG_ERROR, ARM_LOG_TAG, __VA_ARGS__)
  #else
    #define LAYER_LOG(...) printf(__VA_ARGS__); printf("\n");
    #define LAYER_ERR(...) printf(__VA_ARGS__); printf("\n");
  #endif
#else
    #define LAYER_LOG(...)
    #define LAYER_ERR(...)
#endif

/**
 * \brief Format a string using printf formatting template strings.
 *
 * \param format   The template string.
 * \param args     The variadic values used to populate the template.
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
 * \brief Test if an element exists in an iterable container.
 *
 * \param elem   The element to search for.
 * \param cont   The container to search.
 *
 * \return \c true if the item was found, else \c false.
 */
template<typename E, typename C>
bool isIn(const E& elem, const C& cont)
{
    return std::find(std::begin(cont), std::end(cont), elem) != std::end(cont);
}

/**
 * \brief Test if an element exists in a mappable container.
 *
 * \param elem   The element to search for.
 * \param cont   The container to search.
 *
 * \return \c true if the item was found, else \c false.
 */
template<typename E, typename C>
bool isInMap(const E& elem, const C& cont)
{
    return cont.find(elem) != cont.end();
}

/**
 * \brief Get the current time in seconds since an arbitrary epoch.
 *
 * \return The current time.
 */
static inline double getTime()
{
    timeval tv;
    gettimeofday(&tv, 0);
    return static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec) * 1.0e-6;
}

/**
 * \brief Get a displayable pointer.
 *
 * On 64-bit systems this strips the MTE tag.
 *
 * \return The displayable pointer
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
