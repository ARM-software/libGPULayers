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

#include "trackers/device.hpp"
#include "utils/misc.hpp"

namespace Tracker
{

/* See header for documentation. */
void Device::createCommandPool(
    VkCommandPool commandPool
) {
    commandPools.insert({
        commandPool,
        std::make_unique<CommandPool>(commandPool)
    });
}

/* See header for documentation. */
CommandPool& Device::getCommandPool(
    VkCommandPool commandPool
) {
    assert(isInMap(commandPool, commandPools));
    return *commandPools.at(commandPool);
}

/* See header for documentation. */
void Device::destroyCommandPool(
    VkCommandPool commandPool
) {
    commandPools.erase(commandPool);
}

/* See header for documentation. */
void Device::allocateCommandBuffer(
    VkCommandPool commandPool,
    VkCommandBuffer commandBuffer
) {
    // Allocate in the pool
    auto& pool = getCommandPool(commandPool);
    auto& buffer = pool.allocateCommandBuffer(commandBuffer);

    // Insert into the tracker lookup map
    commandBuffers.insert({
        commandBuffer,
        buffer
    });
}

/* See header for documentation. */
void Device::freeCommandBuffer(
    VkCommandPool commandPool,
    VkCommandBuffer commandBuffer
) {
    // Remove from the tracker lookup map
    commandBuffers.erase(commandBuffer);

    // Remove from the command pool
    auto& pool = getCommandPool(commandPool);
    pool.freeCommandBuffer(commandBuffer);
}

/* See header for documentation. */
CommandBuffer& Device::getCommandBuffer(
    VkCommandBuffer commandBuffer
) {
    assert(isInMap(commandBuffer, commandBuffers));
    return commandBuffers.at(commandBuffer);
}

/* See header for documentation. */
void Device::createRenderPass(
    VkRenderPass renderPass,
    const VkRenderPassCreateInfo& createInfo
) {
    renderPasses.insert({
        renderPass,
        std::make_unique<RenderPass>(renderPass, createInfo)
    });
}

/* See header for documentation. */
void Device::createRenderPass(
    VkRenderPass renderPass,
    const VkRenderPassCreateInfo2& createInfo
) {
    renderPasses.insert({
        renderPass,
        std::make_unique<RenderPass>(renderPass, createInfo)
    });
}

/* See header for documentation. */
RenderPass& Device::getRenderPass(
    VkRenderPass renderPass
) {
    assert(isInMap(renderPass, renderPasses));
    return *renderPasses.at(renderPass);
}

/* See header for documentation. */
void Device::destroyRenderPass(
    VkRenderPass renderPass
) {
    renderPasses.erase(renderPass);
}

/* See header for documentation. */
Queue& Device::getQueue(
    VkQueue queue
) {
    // Create a tracker for a queue on first use
    if (!isInMap(queue, queues))
    {
        queues.insert({
            queue,
            std::make_unique<Queue>(queue)
        });
    }

    return *queues.at(queue);
}

/* See header for documentation. */
void Device::queueSubmit(
    VkCommandBuffer commandBuffer
) {
    auto& cbStats = getCommandBuffer(commandBuffer).getStats();
    frameStats.mergeCounts(cbStats);
}


/* See header for documentation. */
void Device::queuePresent()
{
    // Update cumulative statistics with the frame statistics
    totalStats.incFrameCount();
    totalStats.mergeCounts(frameStats);

    // Reset the frame statistics ready for the next frame
    frameStats.reset();
}

}
