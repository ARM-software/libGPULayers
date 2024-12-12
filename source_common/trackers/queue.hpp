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
 * The declaration of Vulkan queue use trackers.
 *
 * Role summary
 * ============
 *
 * These trackers are used to monitor the use of a queue.
 *
 * Key properties
 * ==============
 *
 * Queues are lock-free from a single app thread, relying on external
 * synchronization above the API if multi-threaded use is required.
 */

#pragma once

#include <atomic>
#include <functional>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

#include "framework/utils.hpp"
#include "trackers/layer_command_stream.hpp"

namespace Tracker
{

/**
 * @brief The state tracker for a queue.
 */
class Queue
{
public:
    Queue(
        VkQueue handle);

    /**
     * @brief Execute a layer command stream.
     *
     * @param stream     The layer command stream to execute.
     * @param callback   The callback to pass submitted workloads to.
     */
    void runSubmitCommandStream(
        const std::vector<LCSInstruction>& stream,
        std::function<void(const std::string&)> callback);

    /**
     * @brief Get a unique submitID to label a command buffer submit.
     *
     * @return The assigned ID.
     */
    static uint64_t assignSubmitID()
    {
        return nextSubmitID.fetch_add(1, std::memory_order_relaxed);
    }

private:
    /**
     * The handle of the native queue we are wrapping.
     */
    VkQueue handle;

    /**
     * @brief The stack of user debug labels for this queue.
     */
    std::vector<std::string> debugStack;

    /**
     * @brief The last non-zero render pass tagID submitted.
     */
    uint64_t lastRenderPassTagID { 0 };

    /**
     * @brief The command buffer submitID allocator.
     */
    static std::atomic<uint64_t> nextSubmitID;
};

}
