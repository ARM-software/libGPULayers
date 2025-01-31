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

#include <mutex>
#include <nlohmann/json.hpp>
#include <time.h>

#include "utils/misc.hpp"

#include "device.hpp"
#include "layer_device_functions.hpp"

using json = nlohmann::json;

using namespace std::placeholders;

extern std::mutex g_vulkanLock;

/**
 * @brief Get the CLOCK_MONOTONIC_RAW timestamp in nanoseconds.
 *
 * CLOCK_MONOTONIC_RAW is clock source 5 in Perfetto.
 *
 * @returns Current time in nanoseconds.
 */
static uint64_t getClockMonotonicRaw()
{
    struct timespec ts;

    auto error = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if (error) {
        return 0;
    }

    // Accumulate the nanosecond value
    uint64_t sec = static_cast<uint64_t>(ts.tv_sec);
    uint64_t nsec = static_cast<uint64_t>(ts.tv_nsec);
    nsec += sec * 1000000000ull;

    return nsec;
}

/**
 * @brief Emit the queue submit time metadata.
 *
 * @param queue      The queue being submitted to.
 * @param callback   The data emit callback.
 */
static void emitQueueMetadata(
    VkDevice device,
    VkQueue queue,
    std::function<void(const std::string&)> callback
) {
    // Write the queue submit metadata
    json submitMetadata {
        { "type", "submit" },
        { "device", reinterpret_cast<uintptr_t>(device) },
        { "queue", reinterpret_cast<uintptr_t>(queue) },
        { "timestamp", getClockMonotonicRaw() }
    };

    callback(submitMetadata.dump());
}

/**
 * @brief Emit the command buffer submit time metadata.
 *
 * @param layer           The layer context.
 * @param queue           The queue being submitted to.
 * @param commandBuffer   The command buffer being submitted.
 * @param callback        The data emit callback.
 */
static void emitCommandBufferMetadata(
    Device& layer,
    VkQueue queue,
    VkCommandBuffer commandBuffer,
    std::function<void(const std::string&)> callback
) {
    // Fetch layer proxies for this workload
    auto& tracker = layer.getStateTracker();
    auto& trackQueue = tracker.getQueue(queue);
    auto& trackCB = tracker.getCommandBuffer(commandBuffer);

    // Play the layer command stream into the queue
    const auto& LCS = trackCB.getSubmitCommandStream();
    trackQueue.runSubmitCommandStream(LCS, callback);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<user_tag>(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    auto& tracker = layer->getStateTracker();
    tracker.queuePresent();

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially to the host tool
    json frame {
        { "type", "frame" },
        { "device", reinterpret_cast<uintptr_t>(layer->device) },
        { "fid", tracker.totalStats.getFrameCount() }
    };

    layer->onFrame(frame.dump());

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueuePresentKHR(queue, pPresentInfo);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    auto onSubmit = std::bind(&Device::onWorkloadSubmit, layer, _1);

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool

    // Add queue-level metadata
    emitQueueMetadata(layer->device, queue, onSubmit);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBuffers[j];
            emitCommandBufferMetadata(*layer, queue, commandBuffer, onSubmit);
        }
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    auto onSubmit = std::bind(&Device::onWorkloadSubmit, layer, _1);

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool

    // Add queue-level metadata
    emitQueueMetadata(layer->device, queue, onSubmit);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
            emitCommandBufferMetadata(*layer, queue, commandBuffer, onSubmit);
        }
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    auto onSubmit = std::bind(&Device::onWorkloadSubmit, layer, _1);

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool

    // Add queue-level metadata
    emitQueueMetadata(layer->device, queue, onSubmit);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
            emitCommandBufferMetadata(*layer, queue, commandBuffer, onSubmit);
        }
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
}
