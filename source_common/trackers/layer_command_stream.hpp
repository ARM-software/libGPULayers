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
 * The declaration of a replayable layer command stream.
 *
 * Role summary
 * ============s
 *
 * These trackers are used to monitor to submission of workloads inside a
 * command buffers in a way that they can be iterated by a queue tracker at
 * submit time, allowing us to associate workloads with per-queue state such
 * as the dynamic debug label stack.
 */

#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <vulkan/vulkan.h>

#include "trackers/render_pass.hpp"
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
 * @brief Base class representing a GPU workload in the command stream.
 */
class LCSWorkload
{
public:
    /**
     * @brief Create a new workload.
     *
     * @param tagID   The assigned tagID.
     */
    LCSWorkload(
        uint64_t tagID);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSWorkload() = default;

    /**
     * @brief Get the metadata for this workload
     *
     * @param debugLabel          The debug label state of the VkQueue at submit time.
     * @param tagIDContinuation   The ID of the workload if this is a continuation of it.
     */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const = 0;

    /**
     * @brief Get this workload's tagID.
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
 * @brief Class representing a render pass workload in the command stream.
 */
class LCSRenderPass : public LCSWorkload
{
public:
    /**
     * @brief Create a new workload representing a single render pass.
     *
     * @param tagID           The assigned tagID.
     * @param renderPass      The render pass creation information.
     * @param width           The width of this submit in pixels.
     * @param height          The height of this submit in pixels.
     * @param suspending      Is this a render pass part that suspends later?
     * @param oneTimeSubmit   Is this recorded into a one-time-submit command buffer?
     */
    LCSRenderPass(
        uint64_t tagID,
        const RenderPass& renderPass,
        uint32_t width,
        uint32_t height,
        bool suspending,
        bool oneTimeSubmit);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSRenderPass() = default;

    /**
     * @brief Is this a suspending render pass?
     *
     * @return @c true if this instance suspends rather than ends.
     */
    bool isSuspending() const
    {
        return suspending;
    };

    /**
     * @brief Update this workload with the final draw count.
     *
     * @param count   The number of draw calls tracked by the command buffer.
     */
    void setDrawCallCount(uint64_t count)
    {
        drawCallCount = count;
    };

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

private:
    /**
     * @brief Get the metadata for this workload if beginning a new render pass.
     *
     * @param debugLabel   The debug label state of the VkQueue at submit time.
     */
    std::string getBeginMetadata(
        const std::string* debugLabel=nullptr) const;

    /**
     * @brief Get the metadata for this workload if continuing an existing render pass.
     *
     * @param debugLabel          The debug label state of the VkQueue at submit time.
     * @param tagIDContinuation   The ID of the workload if this is a continuation of it.
     */
    std::string getContinuationMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

    /**
     * @brief Width of this workload, in pixels.
     */
    uint32_t width;

    /**
     * @brief Height of this workload, in pixels.
     */
    uint32_t height;

    /**
     * @brief Is this workload suspending rather than ending?
     */
    bool suspending;

    /**
     * @brief Is this workload in a one-time-submit command buffer?
     */
    bool oneTimeSubmit;

    /**
     * @brief The number of subpasses in the render pass.
     */
    uint32_t subpassCount;

    /**
     * @brief The number of draw calls in the render pass.
     *
     * Note: This is updated by ther command buffer tracker when the render
     * pass is suspended or ended.
     */
    uint64_t drawCallCount { 0 };

    /**
     * @brief The attachments for this render pass.
     */
    std::vector<RenderPassAttachment> attachments;
};

/**
 * @brief Class representing a compute dispatch workload in the command stream.
 */
class LCSDispatch : public LCSWorkload
{
public:
    /**
     * @brief Create a new dispatch workload.
     *
     * Workloads of unknown dimension (e.g. if indirect) should use -1.
     *
     * @param tagID     The assigned tagID.
     * @param xGroups   The number of work groups in the X dimension.
     * @param yGroups   The number of work groups in the Y dimension.
     * @param zGroups   The number of work groups in the Z dimension.
     */
    LCSDispatch(
        uint64_t tagID,
        int64_t xGroups,
        int64_t yGroups,
        int64_t zGroups);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSDispatch() = default;

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

private:
    /**
     * @brief The number of work groups in the X dimension, or -1 if unknown.
     */
    int64_t xGroups;

    /**
     * @brief The number of work groups in the Y dimension, or -1 if unknown.
     */
    int64_t yGroups;

    /**
     * @brief The number of work groups in the Z dimension, or -1 if unknown.
     */
    int64_t zGroups;
};

/**
 * @brief Class representing a trace rays workload in the command stream.
 */
class LCSTraceRays : public LCSWorkload
{
public:
    /**
     * @brief Create a new trace rays workload.
     *
     * Workloads of unknown dimension (e.g. if indirect) should use -1.
     *
     * @param tagID    The assigned tagID.
     * @param xItems   The number of work items in the X dimension.
     * @param yItems   The number of work items in the Y dimension.
     * @param zItems   The number of work items in the Z dimension.
     */
    LCSTraceRays(
        uint64_t tagID,
        int64_t xItems,
        int64_t yItems,
        int64_t zItems);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSTraceRays() = default;

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

private:
    /**
     * @brief The number of work items in the X dimension, or -1 if unknown.
     */
    int64_t xItems;

    /**
     * @brief The number of work items in the Y dimension, or -1 if unknown.
     */
    int64_t yItems;

    /**
     * @brief The number of work items in the Z dimension, or -1 if unknown.
     */
    int64_t zItems;
};

/**
 * @brief Class representing an image transfer workload in the command stream.
 */
class LCSImageTransfer : public LCSWorkload
{
public:
    /**
     * @brief Create a new image transfer workload.
     *
     * Workloads of unknown dimension should use @c pixelCount of -1.
     *
     * @param tagID          The assigned tagID.
     * @param transferType   The subtype of the transfer.
     * @param pixelCount     The size of the transfer, in pixels.
     */
    LCSImageTransfer(
        uint64_t tagID,
        const std::string& transferType,
        int64_t pixelCount);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSImageTransfer() = default;

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

private:
    /**
     * @brief The subtype of the transfer.
     */
    std::string transferType;

    /**
     * @brief The number of pixels transferred, or -1 if unknown.
     */
    int64_t pixelCount;
};

/**
 * @brief Class representing a buffer transfer workload in the command stream.
 */
class LCSBufferTransfer : public LCSWorkload
{
public:
    /**
     * @brief Create a new buffer transfer workload.
     *
     * Workloads of unknown dimension should use @c byteCount of -1. Workloads
     * using symbolic "whole buffer" dimension should use @c byteCount of -2.
     *
     * @param tagID          The assigned tagID.
     * @param transferType   The subtype of the transfer.
     * @param byteCount      The size of the transfer, in bytes.
     */
    LCSBufferTransfer(
        uint64_t tagID,
        const std::string& transferType,
        int64_t byteCount);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSBufferTransfer() = default;

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const;

private:
    /**
     * @brief The subtype of the transfer.
     */
    std::string transferType;

    /**
     * @brief The number of bytes transferred, -1 if unknown, -2 if whole buffer.
     */
    int64_t byteCount;
};

/**
 * @brief Class representing a marker workload in the command stream.
 *
 * Note there is no class for a marker end, as is has no payload and can use
 * just the opcode to indicate behavior.
 */
class LCSMarker : public LCSWorkload
{
public:
    /**
     * @brief Create a new debug marker workload.
     *
     * @param label   The application debug label.
     */
    LCSMarker(
        const std::string& label);

    /**
     * @brief Destroy a workload.
     */
    virtual ~LCSMarker() = default;

    /* See base class for documentation. */
    virtual std::string getMetadata(
        const std::string* debugLabel=nullptr,
        uint64_t tagIDContinuation=0) const
    {
        UNUSED(debugLabel);
        UNUSED(tagIDContinuation);
        return label;
    };

private:
    /**
     * @brief The application debug label.
     */
    std::string label;
};

/**
 * @brief Instructions are an opcode with a data pointer.
 *
 * Data pointers may be null for some opcodes.
 */
using LCSInstruction = std::pair<LCSOpcode, std::shared_ptr<LCSWorkload>>;
}
