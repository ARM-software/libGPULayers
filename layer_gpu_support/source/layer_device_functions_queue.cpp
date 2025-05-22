/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited
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

#include "device.hpp"
#include "framework/device_dispatch_table.hpp"

#include <mutex>

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);

    // Serialize in the order submits are called
    // TODO: This assumes a forward progress guarantee which is no longer
    // guaranteed if the user is using timeline semaphores for syncs

    const uint64_t waitValue = layer->queueSerializationTimelineSemCount;
    layer->queueSerializationTimelineSemCount++;
    const uint64_t signalValue = layer->queueSerializationTimelineSemCount;

    VkPipelineStageFlags waitMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

    VkTimelineSemaphoreSubmitInfo timelineInfo {
        .sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreValueCount = 1,
        .pWaitSemaphoreValues = &waitValue,
        .signalSemaphoreValueCount = 1,
        .pSignalSemaphoreValues = &signalValue,
    };

    VkSubmitInfo submitInfoPre {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = &timelineInfo,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &(layer->queueSerializationTimelineSem),
        .pWaitDstStageMask = &waitMask,
        .commandBufferCount = 0,
        .pCommandBuffers = 0,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr,
    };

    VkSubmitInfo submitInfoPost {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = &timelineInfo,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = 0,
        .pWaitDstStageMask = 0,
        .commandBufferCount = 0,
        .pCommandBuffers = 0,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &(layer->queueSerializationTimelineSem),
    };

    // Release the lock to call into the driver
    lock.unlock();

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit(queue, 1, &submitInfoPre, VK_NULL_HANDLE);
    }

    auto result = layer->driver.vkQueueSubmit(queue, submitCount, pSubmits, fence);

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit(queue, 1, &submitInfoPost, VK_NULL_HANDLE);
    }

    if (layer->instance->config.serialize_queue_wait_idle())
    {
        layer->driver.vkDeviceWaitIdle(layer->device);
    }

    return result;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit2<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);

    // Serialize in the order submits are called
    // TODO: This assumes a forward progress guarantee which is no longer
    // guaranteed if the user is using timeline semaphores for syncs

    const uint64_t waitValue = layer->queueSerializationTimelineSemCount;
    layer->queueSerializationTimelineSemCount++;
    const uint64_t signalValue = layer->queueSerializationTimelineSemCount;

    VkSemaphoreSubmitInfo timelineInfoPre {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .semaphore = layer->queueSerializationTimelineSem,
        .value = waitValue,
        .stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        .deviceIndex = 0,
    };

    VkSemaphoreSubmitInfo timelineInfoPost {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .semaphore = layer->queueSerializationTimelineSem,
        .value = signalValue,
        .stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        .deviceIndex = 0,
    };

    VkSubmitInfo2 submitInfoPre {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .flags = 0,
        .waitSemaphoreInfoCount = 1,
        .pWaitSemaphoreInfos = &timelineInfoPre,
        .commandBufferInfoCount = 0,
        .pCommandBufferInfos = nullptr,
        .signalSemaphoreInfoCount = 0,
        .pSignalSemaphoreInfos = nullptr,
    };

    VkSubmitInfo2 submitInfoPost {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .flags = 0,
        .waitSemaphoreInfoCount = 0,
        .pWaitSemaphoreInfos = nullptr,
        .commandBufferInfoCount = 0,
        .pCommandBufferInfos = nullptr,
        .signalSemaphoreInfoCount = 1,
        .pSignalSemaphoreInfos = &timelineInfoPost,
    };

    // Release the lock to call into the driver
    lock.unlock();

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit2(queue, 1, &submitInfoPre, VK_NULL_HANDLE);
    }

    auto result = layer->driver.vkQueueSubmit2(queue, submitCount, pSubmits, fence);

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit2(queue, 1, &submitInfoPost, VK_NULL_HANDLE);
    }

    if (layer->instance->config.serialize_queue_wait_idle())
    {
        layer->driver.vkDeviceWaitIdle(layer->device);
    }

    return result;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit2KHR<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);

    // Serialize in the order submits are called
    // TODO: This assumes a forward progress guarantee which is no longer
    // guaranteed if the user is using timeline semaphores for syncs

    const uint64_t waitValue = layer->queueSerializationTimelineSemCount;
    layer->queueSerializationTimelineSemCount++;
    const uint64_t signalValue = layer->queueSerializationTimelineSemCount;

    VkSemaphoreSubmitInfo timelineInfoPre {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .semaphore = layer->queueSerializationTimelineSem,
        .value = waitValue,
        .stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        .deviceIndex = 0,
    };

    VkSemaphoreSubmitInfo timelineInfoPost {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .pNext = nullptr,
        .semaphore = layer->queueSerializationTimelineSem,
        .value = signalValue,
        .stageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        .deviceIndex = 0,
    };

    VkSubmitInfo2 submitInfoPre {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .flags = 0,
        .waitSemaphoreInfoCount = 1,
        .pWaitSemaphoreInfos = &timelineInfoPre,
        .commandBufferInfoCount = 0,
        .pCommandBufferInfos = nullptr,
        .signalSemaphoreInfoCount = 0,
        .pSignalSemaphoreInfos = nullptr,
    };

    VkSubmitInfo2 submitInfoPost {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .pNext = nullptr,
        .flags = 0,
        .waitSemaphoreInfoCount = 0,
        .pWaitSemaphoreInfos = nullptr,
        .commandBufferInfoCount = 0,
        .pCommandBufferInfos = nullptr,
        .signalSemaphoreInfoCount = 1,
        .pSignalSemaphoreInfos = &timelineInfoPost,
    };

    // Release the lock to call into the driver
    lock.unlock();

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit2KHR(queue, 1, &submitInfoPre, VK_NULL_HANDLE);
    }

    auto result = layer->driver.vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);

    if (layer->instance->config.serialize_queue())
    {
        layer->driver.vkQueueSubmit2KHR(queue, 1, &submitInfoPost, VK_NULL_HANDLE);
    }

    if (layer->instance->config.serialize_queue_wait_idle())
    {
        layer->driver.vkDeviceWaitIdle(layer->device);
    }

    return result;
}
