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
#include <vulkan/utility/vk_struct_helper.hpp>

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
    // Skip doing this if we are not doing per-workload profiling
    if (!layer.instance->config.isSamplingWorkloads())
    {
        return;
    }

    // Fetch layer proxies for this workload
    auto& tracker = layer.getStateTracker();
    auto& trackQueue = tracker.getQueue(queue);
    auto& trackCB = tracker.getCommandBuffer(commandBuffer);

    // Play the layer command stream
    ProfileSubmitVisitor workloadVisitor(layer);

    const auto& cbLCS = trackCB.getSubmitCommandStream();
    trackQueue.runSubmitCommandStream(cbLCS, workloadVisitor);
}

/**
 * @brief Process frame boundaries
 *
 * @param layer             The layer context.
 */
static void processFrameBoundaryPreSubmit(
    Device& layer
) {
    const auto& config = layer.instance->config;
    auto& tracker = layer.getStateTracker();
    tracker.queuePresent();

    // End the previous frame if it was "of interest"
    if (layer.isFrameOfInterest && config.isSamplingWorkloads())
    {
        json endFrameMessage {
            { "type", "end_frame" }
        };

        layer.txMessage(endFrameMessage.dump());
    }

    uint64_t frameID = tracker.totalStats.getFrameCount();
    layer.isFrameOfInterest = layer.instance->config.isFrameOfInterest(frameID);

    // Start the next frame if it is "of interest"
    if (layer.isFrameOfInterest && config.isSamplingWorkloads())
    {
        json startFrameMessage {
            { "type", "start_frame" },
            { "frame", frameID },
        };

        layer.txMessage(startFrameMessage.dump());
    }
}

/**
 * @brief Check a pNext chain for a manual frame boundary marker.
 *
 * Emits the necessary metadata to emulate a vkQueuePresent.
 *
 * @param layer   The layer context.
 * @param pNext   The submit pNext pointer.
 *
 * @returns @c true if end of frame detected, @c false otherwise.
 */
static bool processManualFrameBoundaryPreSubmit(
    Device& layer,
    const void* pNext
) {
    // Check for end of frame boundary
    auto* ext = vku::FindStructInPNextChain<VkFrameBoundaryEXT>(pNext);
    if (ext && (ext->flags & VK_FRAME_BOUNDARY_FRAME_END_BIT_EXT))
    {
        processFrameBoundaryPreSubmit(layer);
        return true;
    }

    return false;
}

/**
 * @brief Process frame boundaries
 *
 * @param layer         The layer context.
 * @param frameSample   @c true to emit frame sample, @c false just to reset.
 */
static void processFrameBoundaryPostSubmit(
    Device& layer,
    bool frameSample
) {
    // If we are measuring performance ensure the previous frame has finished
    // and then take an initial sample to reset the counters
    layer.driver.vkDeviceWaitIdle(layer.device);
    workaroundDelay();
    auto ec = layer.lgcSampler->sample_now();
    if (ec)
    {
        LAYER_ERR("Failed to make libGPUCounters GPU counter sample");
    }

    // No sample data needed - just use it to reset the counters
    if (!frameSample)
    {
        return;
    }

    // Otherwise emit a frame sample data packet
    auto& tracker = layer.getStateTracker();

    // Frame count has already been incremented for next frame so decrement
    // for reporting purposes
    uint64_t frameID = tracker.totalStats.getFrameCount() - 1;

    json message {
        { "type", "frame" },
        { "frame", frameID },
        { "counters", json::array() }
    };

    for (const auto& pair : layer.lgcActiveCounters)
    {
        hwcpipe::counter_sample sample;
        ec = layer.lgcSampler->get_counter_value(pair.first, sample);
        if (ec)
        {
            LAYER_ERR("Failed to get libGPUCounters GPU counter value");
            continue;
        }

        if (sample.type == hwcpipe::counter_sample::type::uint64)
        {
            json counter {
                { pair.second, sample.value.uint64 },
            };

            message["counters"].push_back(counter);

        }
        else
        {
            json counter {
                { pair.second, sample.value.float64 },
            };

            message["counters"].push_back(counter);

        }
    }

    layer.txMessage(message.dump());
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<user_tag>(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);
    const auto& config = layer->instance->config;

    bool sampleLastFrame = layer->isFrameOfInterest && config.isSamplingFrames();

    // Process frame boundary pre-flight handling for metadata
    processFrameBoundaryPreSubmit(*layer);

    bool resetThisFrame = layer->isFrameOfInterest && config.isSamplingAny();

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!sampleLastFrame && !resetThisFrame)
    {
        lock.unlock();
    }

    auto ret = layer->driver.vkQueuePresentKHR(queue, pPresentInfo);

    // Process frame boundary post-flight isolation of frames
    if (sampleLastFrame || resetThisFrame)
    {
        processFrameBoundaryPostSubmit(*layer, sampleLastFrame);
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
    const auto& config = layer->instance->config;

    bool sampleLastFrame = layer->isFrameOfInterest && config.isSamplingFrames();

    // TODO: Handling here does not split submits if a submit before the last
    // indicates that it's the end of a frame, but I've never seen it done
    bool isFrameEnd = processManualFrameBoundaryPreSubmit(*layer, pSubmits->pNext);

    sampleLastFrame = isFrameEnd && sampleLastFrame;
    bool resetThisFrame = isFrameEnd && layer->isFrameOfInterest && config.isSamplingAny();

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!sampleLastFrame && !resetThisFrame)
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
    if (layer->isFrameOfInterest && config.isSamplingWorkloads())
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

    if (sampleLastFrame || resetThisFrame)
    {
        processFrameBoundaryPostSubmit(*layer, sampleLastFrame);
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
    const auto& config = layer->instance->config;

    bool sampleLastFrame = layer->isFrameOfInterest && config.isSamplingFrames();

    // TODO: Handling here does not split submits if a submit before the last
    // indicates that it's the end of a frame, but I've never seen it done
    bool isFrameEnd = processManualFrameBoundaryPreSubmit(*layer, pSubmits->pNext);

    sampleLastFrame = isFrameEnd && sampleLastFrame;
    bool resetThisFrame = isFrameEnd && layer->isFrameOfInterest && config.isSamplingAny();

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!sampleLastFrame && !resetThisFrame)
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
    if (layer->isFrameOfInterest && config.isSamplingWorkloads())
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

    if (sampleLastFrame || resetThisFrame)
    {
        processFrameBoundaryPostSubmit(*layer, sampleLastFrame);
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
    const auto& config = layer->instance->config;

    bool sampleLastFrame = layer->isFrameOfInterest && config.isSamplingFrames();

    // TODO: Handling here does not split submits if a submit before the last
    // indicates that it's the end of a frame, but I've never seen it done
    bool isFrameEnd = processManualFrameBoundaryPreSubmit(*layer, pSubmits->pNext);

    sampleLastFrame = isFrameEnd && sampleLastFrame;
    bool resetThisFrame = isFrameEnd && layer->isFrameOfInterest && config.isSamplingAny();

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!sampleLastFrame && !resetThisFrame)
    {
        lock.unlock();
    }

    auto res = layer->driver.vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // If we are measuring performance then run the layer command stream with
    // the lock held to stop other submits perturbing the counter data
    if (layer->isFrameOfInterest && config.isSamplingWorkloads())
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

    if (sampleLastFrame || resetThisFrame)
    {
        processFrameBoundaryPostSubmit(*layer, sampleLastFrame);
    }

    return res;
}

/**
 * See Vulkan API for documentation.
 *
 * Note: Modelling of this function is only implemented to support manual frame
 * boundaries. There is no reporting of the workload associated with bind
 * sparse submissions in the Mali timeline driver data model.
 */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse<user_tag>(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(queue);
    const auto& config = layer->instance->config;

    bool sampleLastFrame = layer->isFrameOfInterest && config.isSamplingFrames();

    // Scan infos for frame boundaries
    bool isFrameEnd { false };
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        const auto& info = pBindInfo[i];
        isFrameEnd |= processManualFrameBoundaryPreSubmit(*layer, info.pNext);
    }

    sampleLastFrame = isFrameEnd && sampleLastFrame;
    bool resetThisFrame = isFrameEnd && layer->isFrameOfInterest && config.isSamplingAny();

    // If a "normal" frame then release the lock before calling in to the
    // driver, otherwise keep the lock to stop other threads using Vulkan
    // while we sync and reset the counter stream
    if (!sampleLastFrame && !resetThisFrame)
    {
        lock.unlock();
    }

    auto res = layer->driver.vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    if (sampleLastFrame || resetThisFrame)
    {
        processFrameBoundaryPostSubmit(*layer, sampleLastFrame);
    }

    return res;
}
