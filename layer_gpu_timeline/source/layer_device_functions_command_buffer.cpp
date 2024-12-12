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

#include <memory>
#include <mutex>
#include <thread>

#include "device.hpp"
#include "layer_device_functions.hpp"

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers<user_tag>(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    VkResult result = layer->driver.vkAllocateCommandBuffers(
        device, pAllocateInfo, pCommandBuffers);
    if (result != VK_SUCCESS)
    {
        return result;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto& tracker = layer->getStateTracker();
    for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++)
    {
        tracker.allocateCommandBuffer(
            pAllocateInfo->commandPool, pCommandBuffers[i]);
    }

    return result;
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult layer_vkBeginCommandBuffer<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo
) {
    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cmdBuffer = tracker.getCommandBuffer(commandBuffer);
    cmdBuffer.reset();
    cmdBuffer.begin(pBeginInfo->flags & VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBeginCommandBuffer(commandBuffer, pBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer<user_tag>(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cmdBuffer = tracker.getCommandBuffer(commandBuffer);
    cmdBuffer.reset();

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetCommandBuffer(commandBuffer, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    auto& tracker = layer->getStateTracker();
    for (uint32_t i = 0; i < commandBufferCount; i++)
    {
        tracker.freeCommandBuffer(commandPool, pCommandBuffers[i]);
    }

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkFreeCommandBuffers(
        device, commandPool, commandBufferCount, pCommandBuffers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store and device-wide data
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& primary = tracker.getCommandBuffer(commandBuffer);

    for (uint32_t i = 0; i < commandBufferCount; i++)
    {
        auto& secondary = tracker.getCommandBuffer(pCommandBuffers[i]);
        primary.executeCommands(secondary);
    }

    // Release the lock to call into the main driver
    lock.unlock();
    layer->driver.vkCmdExecuteCommands(
        commandBuffer, commandBufferCount, pCommandBuffers);
}
