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
 * The declaration of Vulkan command pool and command buffer use trackers.
 *
 * Role summary
 * ============s
 *
 * These trackers are used to monitor the use of command buffers in a frame,
 * allowing us to monitor command buffer payloads submitted to a queue.
 *
 * Key properties
 * ==============
 *
 * Command pools and Command buffers are both lock-free from a single app
 * thread, relying on external synchronization above the API if multi-threaded
 * use is required.
 */

#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>

#include "trackers/render_pass.hpp"
#include "trackers/stats.hpp"
#include "utils/misc.hpp"

namespace Tracker
{

/**
 * @brief Enumeration of layer command stream opcodes.
 */
enum class LCSOpcode
{
    MARKER_BEGIN,
    MARKER_END,
    RENDER_PASS,
    DISPATCH,
    TRACE_RAYS,
    BUFFER_TRANSFER,
    IMAGE_TRANSFER
};

/**
 * @brief Baseclass representing a GPU workload in the command stream.
 */
class LCSWorkload
{
public:
    LCSWorkload(
        uint64_t tagID);

    virtual ~LCSWorkload() = default;

    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0,
        uint64_t submitID=0) const = 0;

    /**
     * @brief Get this workloads tagID.
     *
     * @return The assigned ID.
     */
    uint64_t getTagID() const
    {
        return tagID;
    }

    /**
     * @brief Get a unique tagID to label a workload in a command buffer.
     *
     * @return The assigned ID.
     */
    static uint64_t assignTagID()
    {
        return nextTagID.fetch_add(1, std::memory_order_relaxed);
    }

protected:
    /**
     * @brief The assigned tagID for this workload.
     *
     * Render pass continuations are assigned tagID of zero.
     */
    uint64_t tagID;

private:
    /**
     * @brief The workload tagID allocator.
     */
    static std::atomic<uint64_t> nextTagID;
};

/**
 * @brief Baseclass representing a GPU workload in the command stream.
 */
class LCSRenderPass : public LCSWorkload
{
public:
    LCSRenderPass(
        uint64_t tagID,
        const RenderPass& renderPass,
        uint32_t width,
        uint32_t height,
        bool suspending);

    virtual ~LCSRenderPass() = default;

    bool isSuspending() const
    {
        return suspending;
    };

    void setDrawCallCount(uint64_t count)
    {
        drawCallCount = count;
    };

    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0,
        uint64_t submitID=0) const;

private:
    std::string getBeginMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t submitID=0) const;

    std::string getContinuationMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0,
        uint64_t submitID=0) const;

    uint32_t width;

    uint32_t height;

    bool suspending;

    uint32_t subpassCount;

    uint64_t drawCallCount { 0 };

    std::vector<RenderPassAttachment> attachments;
};

/**
 * @brief Baseclass representing a GPU workload in the command stream.
 */
class LCSMarker : public LCSWorkload
{
public:
    LCSMarker(
        const std::string& label);

    virtual ~LCSMarker() = default;

    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0,
        uint64_t submitID=0) const
    {
        UNUSED(debugLabel);
        UNUSED(tagIDContinuation);
        UNUSED(submitID);
        return label;
    };

private:
    std::string label;
};

/**
 * @brief Instructions are an opcode with a data pointer.
 *
 * Data pointers may be null for some opcodes.
 */
using LCSInstruction = std::pair<LCSOpcode, std::shared_ptr<LCSWorkload>>;
}
