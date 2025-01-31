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

#include "trackers/layer_command_stream.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace Tracker
{
/**
 * @brief Represents the interface to some workload visitor that can be passed to Queue::runSubmitCommandStream
 * and which will be called once per item within the submitted command stream for that queue.
 */
class SubmitCommandWorkloadVisitor
{
public:
    /** @brief Destructor for the visitor */
    virtual ~SubmitCommandWorkloadVisitor() noexcept = default;

    /**
     * @brief Visit a renderpass workload object
     *
     * @param renderpass The renderpass
     * @param debugStack The stack of debug labels that are associated with this renderpass
     */
    virtual void operator()(const LCSRenderPass& renderpass, const std::vector<std::string>& debugStack) = 0;

    /**
     * @brief Visit a renderpass continuation workload object
     *
     * @param continuation The renderpass continuation
     * @param debugStack The stack of debug labels that are associated with this renderpass
     * @param renderpassTagID The renderpass tag that the continuation was associated with
     */
    virtual void operator()(const LCSRenderPassContinuation& continuation,
                            const std::vector<std::string>& debugStack,
                            uint64_t renderpassTagID) = 0;

    /**
     * @brief Visit a dispatch workload object
     *
     * @param dispatch The dispatch
     * @param debugStack The stack of debug labels that are associated with this dispatch
     */
    virtual void operator()(const LCSDispatch& dispatch, const std::vector<std::string>& debugStack) = 0;

    /**
     * @brief Visit a trace rays workload object
     *
     * @param traceRays The trace rays
     * @param debugStack The stack of debug labels that are associated with this trace rays
     */
    virtual void operator()(const LCSTraceRays& traceRays, const std::vector<std::string>& debugStack) = 0;

    /**
     * @brief Visit an image transfer workload object
     *
     * @param imageTransfer The image transfer
     * @param debugStack The stack of debug labels that are associated with this image transfer
     */
    virtual void operator()(const LCSImageTransfer& imageTransfer, const std::vector<std::string>& debugStack) = 0;

    /**
     * @brief Visit a buffer transfer workload object
     *
     * @param bufferTransfer The buffer transfer
     * @param debugStack The stack of debug labels that are associated with this buffer transfer
     */
    virtual void operator()(const LCSBufferTransfer& bufferTransfer, const std::vector<std::string>& debugStack) = 0;
};

/**
 * Metadata tracked by the queue when it emits commands, that can be
 * shared with the LCSInstruction visitor object during instruction processing
 */
struct QueueState
{
    /**
     * @brief Construct the state object
     *
     * @param queue The queue which the state tracks
     */
    QueueState(VkQueue queue)
        : handle(queue)
    {
    }

    /**
     * The handle of the native queue we are wrapping.
     */
    VkQueue handle;

    /**
     * @brief The stack of user debug labels for this queue.
     */
    std::vector<std::string> debugStack {};

    /**
     * @brief The last non-zero render pass tagID submitted.
     */
    uint64_t lastRenderPassTagID {0};
};

/**
 * @brief The state tracker for a queue.
 */
class Queue
{
public:
    Queue(VkQueue handle);

    /**
     * @brief Execute a layer command stream.
     *
     * @param stream            The layer command stream to execute.
     * @param workload_visitor  The visitor to pass submitted workloads to.
     */
    void runSubmitCommandStream(const std::vector<LCSInstruction>& stream,
                                SubmitCommandWorkloadVisitor& workload_visitor);

private:
    QueueState state;
};

}
