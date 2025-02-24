/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024-2025 Arm Limited
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
 * ============
 *
 * These trackers are used to monitor to submission of workloads inside a
 * command buffers in a way that they can be iterated by a queue tracker at
 * submit time, allowing us to associate workloads with per-queue state such
 * as the dynamic debug label stack.
 */

#pragma once

#include "trackers/render_pass.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <vulkan/vulkan.h>

namespace Tracker
{
/**
 * @brief Base class representing a GPU workload in the command stream.
 */
class LCSWorkload
{
public:
    /**
     * @brief Get this workload's tagID.
     *
     * @return The assigned ID.
     */
    uint64_t getTagID() const { return tagID; }

    /**
     * @brief Get a unique tagID to label a workload in a command buffer.
     *
     * @return The assigned ID.
     */
    static uint64_t assignTagID() { return nextTagID.fetch_add(1, std::memory_order_relaxed); }

protected:
    /**
     * @brief The assigned tagID for this workload.
     *
     * Render pass continuations are assigned tagID of zero.
     */
    uint64_t tagID;

    /**
     * @brief Create a new workload.
     *
     * @param tagID   The assigned tagID.
     */
    LCSWorkload(uint64_t tagID);

    /**
     * @brief Destroy a workload; this is protected since we should never really be dealing with workloads in the
     * abstract sense (or at least not deleting them as such)
     */
    ~LCSWorkload() noexcept = default;

private:
    /**
     * @brief The workload tagID allocator.
     */
    static std::atomic<uint64_t> nextTagID;
};

/**
 * @brief Common base class for classes representing render pass workload in the command stream.
 */
class LCSRenderPassBase : public LCSWorkload
{
public:
    /**
     * @brief Is this a suspending render pass?
     *
     * @return @c true if this instance suspends rather than ends.
     */
    bool isSuspending() const { return suspending; }

    /**
     * @brief Update this workload with the final draw count.
     *
     * @param count   The number of draw calls tracked by the command buffer.
     */
    void setDrawCallCount(uint64_t count) { drawCallCount = count; }

    /** @return The number of draw calls in this renderpass */
    uint64_t getDrawCallCount() const { return drawCallCount; }

protected:
    /**
     * @brief Construct the common renderbase workload
     *
     * @param tagID           The assigned tagID.
     * @param suspending      Is this a render pass part that suspends later?
     */
    LCSRenderPassBase(uint64_t tagID, bool suspending);

    /**
     * @brief The number of draw calls in the render pass.
     *
     * Note: This is updated by ther command buffer tracker when the render
     * pass is suspended or ended.
     */
    uint64_t drawCallCount {0};

    /**
     * @brief Is this workload suspending rather than ending?
     */
    bool suspending;
};

/**
 * @brief Class representing a render pass workload in the command stream.
 */
class LCSRenderPass : public LCSRenderPassBase
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
    LCSRenderPass(uint64_t tagID,
                  const RenderPass& renderPass,
                  uint32_t width,
                  uint32_t height,
                  bool suspending,
                  bool oneTimeSubmit);

    /** @return The width of the renderpass in pixels */
    uint32_t getWidth() const { return width; }

    /** @return The height of the renderpass in pixels */
    uint32_t getHeight() const { return height; }

    /** @return The number of subpasses */
    uint32_t getSubpassCount() const { return subpassCount; }

    /** @return True if it is a one-time submit renderpass */
    bool isOneTimeSubmit() const { return oneTimeSubmit; }

    /** @return The list of attachments */
    const std::vector<RenderPassAttachment>& getAttachments() const { return attachments; }

private:
    /**
     * @brief The attachments for this render pass.
     */
    std::vector<RenderPassAttachment> attachments;

    /**
     * @brief Width of this workload, in pixels.
     */
    uint32_t width;

    /**
     * @brief Height of this workload, in pixels.
     */
    uint32_t height;

    /**
     * @brief The number of subpasses in the render pass.
     */
    uint32_t subpassCount;

    /**
     * @brief Is this workload in a one-time-submit command buffer?
     */
    bool oneTimeSubmit;
};

/**
 * @brief Class representing the continuation of a split render pass workload continuation in the command stream.
 */
class LCSRenderPassContinuation : public LCSRenderPassBase
{
public:
    /**
     * @brief Create a new workload representing a split render pass.
     *
     * @param _suspending      Is this a render pass part that suspends later?
     */
    LCSRenderPassContinuation(bool _suspending)
        : LCSRenderPassBase(0, _suspending)
    {
    }
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
    LCSDispatch(uint64_t tagID, int64_t xGroups, int64_t yGroups, int64_t zGroups);

    /** @return The number of work groups in the X dimension, or -1 if unknown. */
    int64_t getXGroups() const { return xGroups; }

    /** @return The number of work groups in the y dimension, or -1 if unknown. */
    int64_t getYGroups() const { return yGroups; }

    /** @return The number of work groups in the z dimension, or -1 if unknown. */
    int64_t getZGroups() const { return zGroups; }

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
    LCSTraceRays(uint64_t tagID, int64_t xItems, int64_t yItems, int64_t zItems);

    /** @return The number of work items in the X dimension, or -1 if unknown. */
    int64_t getXItems() const { return xItems; }

    /** @return The number of work items in the y dimension, or -1 if unknown. */
    int64_t getYItems() const { return yItems; }

    /** @return The number of work items in the z dimension, or -1 if unknown. */
    int64_t getZItems() const { return zItems; }

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
    /* Enumerates possible image transfer types */
    enum class Type
    {
        unknown,
        clear_image,
        copy_image,
        copy_buffer_to_image,
        copy_image_to_buffer,
    };

    /**
     * @brief Create a new image transfer workload.
     *
     * Workloads of unknown dimension should use @c pixelCount of -1.
     *
     * @param tagID          The assigned tagID.
     * @param transferType   The subtype of the transfer.
     * @param pixelCount     The size of the transfer, in pixels.
     */
    LCSImageTransfer(uint64_t tagID, Type transferType, int64_t pixelCount);

    /** @return The subtype of the transfer */
    Type getTransferType() const { return transferType; }

    /** @return The subtype of the transfer */
    std::string getTransferTypeStr() const;

    /** @return The size of the transfer, in pixels */
    int64_t getPixelCount() const { return pixelCount; }

private:
    /**
     * @brief The subtype of the transfer.
     */
    Type transferType;

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
    /* Enumerates possible buffer transfer types */
    enum class Type
    {
        unknown,
        fill_buffer,
        copy_buffer,
    };

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
    LCSBufferTransfer(uint64_t tagID, Type transferType, int64_t byteCount);

    /** @return The subtype of the transfer */
    Type getTransferType() const { return transferType; }

    /** @return The subtype of the transfer */
    std::string getTransferTypeStr() const;

    /** @return The size of the transfer, in bytes */
    int64_t getByteCount() const { return byteCount; }

private:
    /**
     * @brief The subtype of the transfer.
     */
    Type transferType;

    /**
     * @brief The number of bytes transferred, -1 if unknown, -2 if whole buffer.
     */
    int64_t byteCount;
};

/**
 * @brief Class representing an acceleration structure build workload in the command stream.
 */
class LCSAccelerationStructureBuild : public LCSWorkload
{
public:
    /* Enumerates possible acceleration structure build types */
    enum class Type
    {
        unknown,
        fast_build,
        fast_trace
    };

    /**
     * @brief Create a new acceleration structure build workload.
     *
     * Workloads of unknown dimension should use @c primitiveCount of -1.
     *
     * @param tagID            The assigned tagID.
     * @param buildType        The subtype of the build.
     * @param primitiveCount   The size of the build, in primitives.
     */
    LCSAccelerationStructureBuild(uint64_t tagID, Type buildType, int64_t primitiveCount);

    /** @return The subtype of the build */
    Type getBuildType() const { return buildType; }

    /** @return The subtype of the build */
    std::string getBuildTypeStr() const;

    /** @return The size of the build, in primitives */
    int64_t getPrimitiveCount() const { return primitiveCount; }

private:
    /**
     * @brief The subtype of the build.
     */
    Type buildType;

    /**
     * @brief The number of primitives in the build, or -1 if unknown.
     */
    int64_t primitiveCount;
};

/**
 * @brief Class representing an acceleration structure transfer workload in the command stream.
 */
class LCSAccelerationStructureTransfer : public LCSWorkload
{
public:
    /* Enumerates possible acceleration structure transfer types */
    enum class Type
    {
        unknown,
        struct_to_struct,
        struct_to_mem,
        mem_to_struct,
    };

    /**
     * @brief Create a new acceleration structure transfer workload.
     *
     * @param tagID          The assigned tagID.
     * @param transferType   The subtype of the transfer.
     */
    LCSAccelerationStructureTransfer(uint64_t tagID, Type transferType, int64_t byteCount);

    /** @return The subtype of the transfer */
    Type getTransferType() const { return transferType; }

    /** @return The subtype of the transfer */
    std::string getTransferTypeStr() const;

    /** @return The size of the transfer, in bytes */
    int64_t getByteCount() const { return byteCount; }

private:
    /**
     * @brief The subtype of the transfer.
     */
    Type transferType;

    /**
     * @brief The number of bytes transferred, -1 if unknown.
     */
    int64_t byteCount;
};

/**
 * @brief Class representing a marker instruction in the command stream that represents a debug label push operation.
 */
class LCSInstructionMarkerPush
{
public:
    /**
     * @brief Create a new debug marker workload.
     *
     * @param label   The application debug label.
     */
    LCSInstructionMarkerPush(const std::string& label);

    /**
     * @brief Get the stored debug label
     *
     * @return The label string
     */
    const std::string& getLabel() const { return *label; }

private:
    /**
     * @brief The application debug label.
     *
     * The label is stored in a shared pointer to avoid copying the actual string when it is shared between
     * subcommandbuffers
     */
    std::shared_ptr<std::string> label;
};

/**
 * @brief Class representing a marker instruction in the command stream that represents a debug label pop operation.
 */
class LCSInstructionMarkerPop
{
    // there are no members, as this type is just a marker within LCSInstruction variant
};

/**
 * @brief Class representing a workload instruction in the command stream.
 */
template<typename WorkloadType>
requires(std::is_base_of_v<LCSWorkload, WorkloadType>)
class LCSInstructionWorkload
{
public:
    /**
     * @brief Create a new workload instruction from a pre-made workload pointer.
     *
     * @param wrkload The workload object (must not be null)
     */
    LCSInstructionWorkload(std::shared_ptr<WorkloadType> wrkload)
        : workload(std::move(wrkload))
    {
    }

    /**
     * @brief Get the stored workload
     *
     * @return The workload
     */
    const WorkloadType& getWorkload() const { return *workload; }

private:
    /**
     * @brief The stored workload
     *
     * The workload is stored in a shared point to avoid copying the actual value when it is shared between
     * subcommandbuffers
     */
    std::shared_ptr<WorkloadType> workload;
};

/**
 * @brief Instructions are a variant representing the operation.
 */
using LCSInstruction = std::variant<
    // The instruction is a debug-label push operation
    LCSInstructionMarkerPush,
    // The instruction is a debug-label pop operation
    LCSInstructionMarkerPop,
    // The instruction represents a render pass workload operation
    LCSInstructionWorkload<LCSRenderPass>,
    // The instruction represents a continuation of a render pass workload operation
    LCSInstructionWorkload<LCSRenderPassContinuation>,
    // The instruction represents a dispatch workload operation
    LCSInstructionWorkload<LCSDispatch>,
    // The instruction represents a trace rays workload operation
    LCSInstructionWorkload<LCSTraceRays>,
    // The instruction represents an image transfer workload operation
    LCSInstructionWorkload<LCSImageTransfer>,
    // The instruction represents a buffer transfer workload operation
    LCSInstructionWorkload<LCSBufferTransfer>,
    // The instruction represents an acceleration structure buildworkload operation
    LCSInstructionWorkload<LCSAccelerationStructureBuild>,
    // The instruction represents an acceleration structure transfer workload operation
    LCSInstructionWorkload<LCSAccelerationStructureTransfer>>;
}
