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

#include "device.hpp"
#include "device_utils.hpp"
#include "submit_visitor.hpp"

#include "framework/device_dispatch_table.hpp"
#include "trackers/queue.hpp"

#include <nlohmann/json.hpp>

#include <mutex>
#include <time.h>

using json = nlohmann::json;

extern std::mutex g_vulkanLock;

/**
 * @brief Process the command buffer stream for events.
 *
 * @param layer             The layer context.
 * @param queue             The queue being submitted to.
 * @param commandBuffer     The command buffer being submitted.
 */
static void processLayerCommandStream(Device& layer,
                                      VkQueue queue,
                                      VkCommandBuffer commandBuffer)
{
    // Fetch layer proxies for this workload
    auto& tracker = layer.getStateTracker();
    auto& trackQueue = tracker.getQueue(queue);
    auto& trackCB = tracker.getCommandBuffer(commandBuffer);

    // Play the layer command stream
    ProfileSubmitVisitor workloadVisitor(layer);

    const auto& cbLCS = trackCB.getSubmitCommandStream();
    trackQueue.runSubmitCommandStream(cbLCS, workloadVisitor);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<user_tag>(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);

    auto& tracker = layer->getStateTracker();
    tracker.queuePresent();

    // End the previous frame if it was "of interest"
    if (layer->isFrameOfInterest)
    {
        json endFrameMessage {
            { "type", "end_frame" }
        };

        layer->txMessage(endFrameMessage.dump());
    }

    uint64_t frameID = tracker.totalStats.getFrameCount();
    layer->isFrameOfInterest = layer->instance->config.isFrameOfInterest(frameID);

    // Start the next frame if it is "of interest"
    if (layer->isFrameOfInterest)
    {
        json startFrameMessage {
            { "type", "start_frame" },
            { "frame", frameID },
        };

        layer->txMessage(startFrameMessage.dump());
    }

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!layer->isFrameOfInterest)
    {
        lock.unlock();
    }

    auto ret = layer->driver.vkQueuePresentKHR(queue, pPresentInfo);

    // If we are measuring performance ensure the previous frame has finished
    // and then take an initial sample to reset the counters
    if (layer->isFrameOfInterest)
    {
        layer->driver.vkDeviceWaitIdle(layer->device);
        workaroundDelay();
        auto ec = layer->lgcSampler->sample_now();
        if (ec)
        {
            LAYER_ERR("Failed to make libGPUCounters GPU counter sample");
        }
    }

    return ret;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!layer->isFrameOfInterest)
    {
        lock.unlock();
    }

    auto res = layer->driver.vkQueueSubmit(queue, submitCount, pSubmits, fence);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // If we are measuring performance then run the layer command stream with
    // the lock held to stop other submits perturbing the counter data
    if (layer->isFrameOfInterest)
    {
        for (uint32_t i = 0; i < submitCount; i++)
        {
            const auto& submit = pSubmits[i];
            for (uint32_t j = 0; j < submit.commandBufferCount; j++)
            {
                VkCommandBuffer commandBuffer = submit.pCommandBuffers[j];
                processLayerCommandStream(*layer, queue, commandBuffer);
            }
        }
    }

    return res;
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

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!layer->isFrameOfInterest)
    {
        lock.unlock();
    }

    auto res = layer->driver.vkQueueSubmit2(queue, submitCount, pSubmits, fence);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // If we are measuring performance then run the layer command stream with
    // the lock held to stop other submits perturbing the counter data
    if (layer->isFrameOfInterest)
    {
        for (uint32_t i = 0; i < submitCount; i++)
        {
            const auto& submit = pSubmits[i];
            for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
            {
                VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
                processLayerCommandStream(*layer, queue, commandBuffer);
            }
        }
    }

    return res;
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

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!layer->isFrameOfInterest)
    {
        lock.unlock();
    }

    auto res = layer->driver.vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
    if (res != VK_SUCCESS || !layer->isFrameOfInterest)
    {
        return res;
    }

    // If we are measuring performance then run the layer command stream with
    // the lock held to stop other submits perturbing the counter data
    if (layer->isFrameOfInterest)
    {
        for (uint32_t i = 0; i < submitCount; i++)
        {
            const auto& submit = pSubmits[i];
            for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
            {
                VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
                processLayerCommandStream(*layer, queue, commandBuffer);
            }
        }
    }

    return res;
}
