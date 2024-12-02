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
 * This module implements basic tracking of Vulkan devices.
 *
 * Role summary
 * ============
 *
 * Trackers are used to monitor the use of a device and the various resources
 * that exist in the scope of a device. Primarily we use them to implement
 * counters that layers can to either emit statistics or be used to trigger
 * other layer behavior when a specific count is reached.
 */

#pragma once

#include <unordered_map>
#include <vulkan/vulkan.h>

#include "trackers/command_buffer.hpp"
#include "trackers/queue.hpp"
#include "trackers/render_pass.hpp"

namespace Tracker
{

/**
 * @brief The state tracker for a single device.
 */
class Device
{
public:
    /**
     * @brief Create a new command pool tracker within this device.
     *
     * @param commandPool   The native handle to track.
     */
    void createCommandPool(
        VkCommandPool commandPool);

    /**
     * @brief Get the tracker for a native command pool.
     *
     * @param commandPool   The native handle we are tracking.
     */
    CommandPool& getCommandPool(
        VkCommandPool commandPool);

    /**
     * @brief Create a new command buffer in a pool within this device.
     *
     * @param commandPool     The native parent command pool handle.
     * @param commandBuffer   The native handle to track.
     */
    void allocateCommandBuffer(
        VkCommandPool commandPool,
        VkCommandBuffer commandBuffer);

    /**
     * @brief Free a command buffer in a pool within this device.
     *
     * @param commandPool     The native parent command pool handle.
     * @param commandBuffer   The native handle to stop tracking.
     */
    void freeCommandBuffer(
        VkCommandPool commandPool,
        VkCommandBuffer commandBuffer);

    /**
     * @brief Get the tracker for native command buffer.
     *
     * @param commandBuffer   The native handle we are tracking.
     */
    CommandBuffer& getCommandBuffer(
        VkCommandBuffer commandBuffer);

    /**
     * @brief Destroy a command pool within this device.
     *
     * @param commandPool   The native handle to stop tracking.
     */
    void destroyCommandPool(
        VkCommandPool commandPool);

    /**
     * @brief Get the tracker for a native queue.
     *
     * Note that queue trackers are created on the fly when a native queue is
     * first used. We don't track queue creation as a distinct step.
     *
     * @param queue   The native handle we are tracking.
     */
    Queue& getQueue(
        VkQueue queue);

    /**
     * @brief Create a new render pass tracker within this device.
     *
     * @param renderPass   The native handle to track.
     * @param createInfo   The render pass configuration information.
     */
    void createRenderPass(
        VkRenderPass renderPass,
        const VkRenderPassCreateInfo& createInfo);

    /**
     * @brief Create a new render pass tracker within this device.
     *
     * @param renderPass   The native handle to track.
     * @param createInfo   The render pass configuration information.
     */
    void createRenderPass(
        VkRenderPass renderPass,
        const VkRenderPassCreateInfo2& createInfo);

    /**
     * @brief Get the tracker for a native render pass.
     *
     * @param renderPass   The native handle we are tracking.
     */
    RenderPass& getRenderPass(
        VkRenderPass renderPass);

    /**
     * @brief Destroy a render pass within this device.
     *
     * @param renderPass   The native handle to stop tracking.
     */
    void destroyRenderPass(
        VkRenderPass renderPass);

    /**
     * @brief Submit a command buffer to a queue within this device.
     *
     * @param commandBuffer   The native command buffer we are tracking.
     */
    void queueSubmit(
        VkCommandBuffer commandBuffer);

    /**
     * @brief Submit a display present command to a queue within this device.
     */
    void queuePresent();

public:
    /**
     * @brief The set of all queues allocated in this device.
     */
    std::unordered_map<VkQueue, std::unique_ptr<Queue>> queues;

    /**
     * @brief The set of all command pools allocated in this device.
     */
    std::unordered_map<VkCommandPool, std::unique_ptr<CommandPool>> commandPools;

    /**
     * @brief The set of all command buffers allocated in this device.
     *
     * Note - memory ownership is via the CommandPool, so dispatch references in this map
     * must be removed before deleting the command pool that owns the buffer.
     */
    std::unordered_map<VkCommandBuffer, CommandBuffer&> commandBuffers;

    /**
     * @brief The set of all render passes allocated in this device.
     */
    std::unordered_map<VkRenderPass, std::unique_ptr<RenderPass>> renderPasses;

    /**
     * @brief The cumulative statistics for this device.
     *
     * Only updated on submit to a present queue.
     */
    Stats totalStats;

    /**
     * @brief The current frame statistics for this device.
     *
     * Only updated on submit to a queue.
     */
    Stats frameStats;
};

}
