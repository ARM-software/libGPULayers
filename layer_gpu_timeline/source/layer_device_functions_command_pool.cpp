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
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool<user_tag>(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    VkResult result = layer->driver.vkCreateCommandPool(
        device, pCreateInfo, pAllocator, pCommandPool);
    if (result != VK_SUCCESS)
    {
        return result;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto& tracker = layer->getStateTracker();
    tracker.createCommandPool(*pCommandPool);
    return result;
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    auto& tracker = layer->getStateTracker();
    tracker.getCommandPool(commandPool).reset();

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetCommandPool(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    auto& tracker = layer->getStateTracker();
    tracker.destroyCommandPool(commandPool);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyCommandPool(device, commandPool, pAllocator);
}
