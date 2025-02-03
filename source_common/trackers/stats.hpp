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
 * \file
 * This module implements basic counter tracking of Vulkan workloads.
 */

#pragma once

#include <cstdint>
#include <unordered_map>

#include <vulkan/vulkan.h>

namespace Tracker
{

/**
 * @brief Statistics counters for a single device.
 *
 * These counters are designed to be used hierarchically, so you can use the
 * API to aggregate counters into a parent tracker. Not all instances are
 * required to track all statistics.
 */
class Stats
{
public:
    /**
     * @brief Increment the frame counter.
     */
    void incFrameCount() { frameCount += 1; }

    /**
     * @brief Increment the render pass counter.
     */
    void incRenderPassCount() { renderPassCount += 1; }

    /**
     * @brief Increment the draw counter.
     */
    void incDrawCallCount() { drawCallCount += 1; }

    /**
     * @brief Increment the compute dispatch counter.
     */
    void incDispatchCount() { dispatchCount += 1; }

    /**
     * @brief Increment the trace rays counter.
     */
    void incTraceRaysCount() { traceRaysCount += 1; };

    /**
     * @brief Increment the buffer transfer counter.
     */
    void incBufferTransferCount() { bufferTransferCount += 1; }

    /**
     * @brief Increment the image transfer counter.
     */
    void incImageTransferCount() { imageTransferCount += 1; }

    /**
     * @brief Increment all counters with values from another stats object.
     */
    void mergeCounts(const Stats& other)
    {
        frameCount += other.frameCount;
        renderPassCount += other.renderPassCount;
        drawCallCount += other.drawCallCount;
        dispatchCount = other.dispatchCount;
        traceRaysCount = other.traceRaysCount;
        bufferTransferCount = other.bufferTransferCount;
        imageTransferCount = other.imageTransferCount;
    }

    /**
     * @brief Reset all counters to zero;
     */
    void reset()
    {
        frameCount = 0;
        renderPassCount = 0;
        drawCallCount = 0;
        dispatchCount = 0;
        traceRaysCount = 0;
        bufferTransferCount = 0;
        imageTransferCount = 0;
    }

    /**
     * @brief Get the frame counter.
     */
    uint64_t getFrameCount() const { return frameCount; }

    /**
     * @brief Increment the render pass counter.
     */
    uint64_t getRenderPassCount() const { return renderPassCount; }

    /**
     * @brief Increment the draw counter.
     */
    uint64_t getDrawCallCount() const { return drawCallCount; }

    /**
     * @brief Increment the compute dispatch counter.
     */
    uint64_t getDispatchCount() const { return dispatchCount; }

    /**
     * @brief Increment the trace rays counter.
     */
    uint64_t getTraceRaysCount() const { return traceRaysCount; };

    /**
     * @brief Increment the buffer transfer counter.
     */
    uint64_t getBufferTransferCount() const { return bufferTransferCount; }

    /**
     * @brief Increment the image transfer counter.
     */
    uint64_t getImageTransferCount() const
    {
        return imageTransferCount;
        ;
    }

private:
    /**
     * @brief The number of frames tracked.
     */
    uint64_t frameCount {0};

    /**
     * @brief The number of render passes tracked.
     */
    uint64_t renderPassCount {0};

    /**
     * @brief The number of draw calls tracked.
     */
    uint64_t drawCallCount {0};

    /**
     * @brief The number of compute dispatches tracked.
     */
    uint64_t dispatchCount {0};

    /**
     * @brief The number of trace rays calls tracked.
     */
    uint64_t traceRaysCount {0};

    /**
     * @brief The number of buffer transfers tracked.
     */
    uint64_t bufferTransferCount {0};

    /**
     * @brief The number of image transfers tracked.
     */
    uint64_t imageTransferCount {0};
};

}
