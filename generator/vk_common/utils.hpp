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
 * @file
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
 * @brief Convert a dispatchable API handle to the underlying dispatch key.
 *
 * @param ptr   The dispatchable handle from the API.
 *
 * \return The dispatch key.
 */
static inline void* getDispatchKey(
    void* ptr
) {
    return *static_cast<void**>(ptr);
}

/**
 * @brief Enable to enable API entrypoint tracing to the log/logcat.
 */
#define CONFIG_TRACE 0

/**
 * @brief Enable to enable layer logging to the log/logcat.
 */
#define CONFIG_LOG 1

#if CONFIG_TRACE
  #ifdef __ANDROID__
    #if !defined(LGL_LOG_TAG)
        #error "LGL_LOG_TAG not defined"
    #endif

    #define LAYER_TRACE(x) __android_log_print(ANDROID_LOG_INFO, LGL_LOG_TAG, "API Trace: %s", x)
  #else
    #define LAYER_TRACE(x) printf("API Trace: %s\n", x)
  #endif
#else
    #define LAYER_TRACE(x)
#endif

#if CONFIG_LOG
  #ifdef __ANDROID__
    #if !defined(LGL_LOG_TAG)
        #error "LGL_LOG_TAG not defined"
    #endif

    #define LAYER_LOG(...) __android_log_print(ANDROID_LOG_DEBUG, LGL_LOG_TAG, __VA_ARGS__)
    #define LAYER_ERR(...) __android_log_print(ANDROID_LOG_ERROR, LGL_LOG_TAG, __VA_ARGS__)
  #else
    #define LAYER_LOG(...) printf(__VA_ARGS__); printf("\n");
    #define LAYER_ERR(...) printf(__VA_ARGS__); printf("\n");
  #endif
#else
    #define LAYER_LOG(...)
    #define LAYER_ERR(...)
#endif
