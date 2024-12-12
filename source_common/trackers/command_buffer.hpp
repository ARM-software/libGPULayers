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
 * ============
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

#include "trackers/stats.hpp"
#include "trackers/layer_command_stream.hpp"

namespace Tracker
{

/**
 * @brief The state tracker for a single command buffer.
 */
class CommandBuffer
{
public:
    /**
     * @brief Construct a new command buffer wrapping a Vulkan allocation.
     *
     * @param handle   The Vulkan command buffer handle we are tracking.
     */
    CommandBuffer(
        VkCommandBuffer handle);

    /**
     * @brief Get the stats object for this command buffer;
     */
    Stats& getStats()
    {
        return stats;
    }

    /**
     * @brief Get the layer submit-time command stream for this command buffer.
     */
    const std::vector<LCSInstruction>& getSubmitCommandStream() const
    {
        return workloadCommandStream;
    }

    /**
     * @brief Begin recording a render pass.
     *
     * @param renderPass   Render pass creation info.
     * @param width        Render pass extent width in pixels.
     * @param height       Render pass extent height in pixels.
     * @param resuming     If @c true this recording starts with a resume.
     * @param suspending   If @c true this recording ends with a suspend.
     *
     * @return Returns the tagID assigned to this workload. Always returns 0
     *         if @c resuming an existing workload.
     */
    uint64_t renderPassBegin(
        const RenderPass& renderPass,
        uint32_t width,
        uint32_t height,
        bool resuming=false,
        bool suspending=false);

    /**
     * @brief End the current render pass workload recording.
     *
     * @return Returns @c true if this is a suspending dynamic render pass or
     *         @c false otherwise.
     */
    bool renderPassEnd();

    /**
     * @brief Capture a compute dispatch.
     *
     * @param xGroups   Number of groups in X dimension, or -1 if unknown.
     * @param yGroups   Number of groups in Y dimension, or -1 if unknown.
     * @param zGroups   Number of groups in Z dimension, or -1 if unknown.
     *
     * @return Returns the tagID assigned to this workload.
     */
    uint64_t dispatch(
        int64_t xGroups,
        int64_t yGroups,
        int64_t zGroups);

    /**
     * @brief Capture a trace rays dispatch.
     *
     * @param xItems   Number of work items in X dimension, or -1 if unknown.
     * @param yItems   Number of work items in Y dimension, or -1 if unknown.
     * @param zItems   Number of work items in Z dimension, or -1 if unknown.
     *
     * @return Returns the tagID assigned to this workload.
     */
    uint64_t traceRays(
        int64_t xItems,
        int64_t yItems,
        int64_t zItems);

    /**
     * @brief Capture a transfer where the destination is an image.
     *
     * @param transferType   The type of the transfer.
     * @param pixelCount     The number of pixels written.
     *
     * @return Returns the tagID assigned to this workload.
     */
    uint64_t imageTransfer(
        const std::string& transferType,
        int64_t pixelCount);

    /**
     * @brief Capture a transfer where the destination is a buffer.
     *
     * @param transferType   The type of the transfer.
     * @param byteCount      The number of pixels written.
     *
     * @return Returns the tagID assigned to this workload.
     */
    uint64_t bufferTransfer(
        const std::string& transferType,
        int64_t byteCount);

    /**
     * @brief Begin a user debug marker range.
     */
    void debugMarkerBegin(
        std::string marker);

    /**
     * @brief End a user debug marker range.
     */
    void debugMarkerEnd();

    /**
     * @brief Execute a secondary command buffer.
     */
    void executeCommands(
        CommandBuffer& secondary);

    /**
     * @brief Reset the command buffer back into the @a Initial state.
     */
    void reset();

    /**
     * @brief Begin recording back into the @a Recording state.
     *
     * @param oneTimeSubmit   Is this a one-time submit recording.
     */
    void begin(
        bool oneTimeSubmit);

private:
    /**
     * @brief The Vulkan API handle of this command buffer.
     */
    const VkCommandBuffer handle;

    /**
     * @brief Is this command buffer recording one-time-submit?
     */
    bool oneTimeSubmit { false };

    /**
     * @brief The command buffer draw count at the start of the render pass.
     */
    uint64_t renderPassStartDrawCount { 0 };

    /**
     * @brief The cumulative stats of the commands in this command buffer.
     */
    Stats stats;

    /**
     * @brief The current render pass if we are in one.
     */
    std::shared_ptr<LCSRenderPass> currentRenderPass;

    /**
     * @brief The recorded workloads.
     */
    std::vector<std::shared_ptr<LCSWorkload>> workloads;

    /**
     * @brief The recorded commands.
     */
    std::vector<LCSInstruction> workloadCommandStream;
};

/**
 * @brief The state tracker for a single command pool.
 */
class CommandPool
{
public:
    /**
     * @brief Construct a new command pool wrapping a Vulkan allocation.
     *
     * @param handle       The Vulkan pool buffer handle we are wrapping.
     */
    CommandPool(
        VkCommandPool handle);

    /**
     * @brief Allocate a command buffer in the pool with the given handle.
     *
     * @param commandBuffer   The Vulkan handle of the allocated command buffer.
     *
     * \return The layer wrapper object for the command buffer.
     */
    CommandBuffer& allocateCommandBuffer(VkCommandBuffer commandBuffer);

    /**
     * @brief Free the command buffer in the pool with the given handle.
     *
     * @param commandBuffer   The Vulkan handle of the command buffer to free.
     */
    void freeCommandBuffer(VkCommandBuffer commandBuffer);

    /**
     * @brief Reset all allocated command buffers into the @a Initial state.
     */
    void reset();

private:
    /**
     * @brief The Vulkan API handle of this command pool.
     */
    const VkCommandPool handle;

   /**
     * @brief The command buffers currently allocated in this command pool.
     */
    std::unordered_map<VkCommandBuffer, std::unique_ptr<CommandBuffer>> commandBuffers;
};

}
