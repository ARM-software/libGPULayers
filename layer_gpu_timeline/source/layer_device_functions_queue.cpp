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
#include "framework/device_dispatch_table.hpp"
#include "timeline_protobuf_encoder.hpp"
#include "trackers/queue.hpp"

#include <mutex>
#include <time.h>
#include <vulkan/utility/vk_struct_helper.hpp>

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
    if (error)
    {
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
 * @param queue             The queue being submitted to.
 * @param workloadVisitor   The data emit callback.
 */
static void emitQueueMetadata(VkQueue queue, TimelineProtobufEncoder& workloadVisitor)
{
    workloadVisitor.emitSubmit(queue, getClockMonotonicRaw());
}

/**
 * @brief Emit the command buffer submit time metadata.
 *
 * @param layer             The layer context.
 * @param queue             The queue being submitted to.
 * @param commandBuffer     The command buffer being submitted.
 * @param workloadVisitor   The data emit callback.
 */
static void emitCommandBufferMetadata(Device& layer,
                                      VkQueue queue,
                                      VkCommandBuffer commandBuffer,
                                      Tracker::SubmitCommandWorkloadVisitor& workloadVisitor)
{
    // Fetch layer proxies for this workload
    auto& tracker = layer.getStateTracker();
    auto& trackQueue = tracker.getQueue(queue);
    auto& trackCB = tracker.getCommandBuffer(commandBuffer);

    // Play the layer command stream into the queue
    const auto& LCS = trackCB.getSubmitCommandStream();
    trackQueue.runSubmitCommandStream(LCS, workloadVisitor);
}

/**
 * @brief Check a pNext chain for a manual frame boundary marker.
 *
 * Emits the necessary metadata to emulate a vkQueuePresent. Note that this
 * will generate a second metadata submit to be a container for any commands
 * if there are submits remaining after the one tagged as end-of-frame.
 *
 * @param layer             The layer context.
 * @param queue             The queue.
 * @param pNext             The submit pNext pointer.
 * @param isLastSubmit      Is this the last submit in the API call?
 * @param workloadVisitor   Visitor for the protobuf encoder.
 */
static void checkManualFrameBoundary(
    Device* layer,
    VkQueue queue,
    const void* pNext,
    bool isLastSubmit,
    TimelineProtobufEncoder& workloadVisitor
) {
    // Check for end of frame boundary
    auto* ext = vku::FindStructInPNextChain<VkFrameBoundaryEXT>(pNext);
    if (ext && (ext->flags & VK_FRAME_BOUNDARY_FRAME_END_BIT_EXT))
    {
        // Emulate a queue present to indicate end of frame
        auto& tracker = layer->getStateTracker();
        tracker.queuePresent();

        TimelineProtobufEncoder::emitFrame(*layer, tracker.totalStats.getFrameCount(), getClockMonotonicRaw());

        // Emulate a new queue submit if work remains to submit
        if (!isLastSubmit)
        {
            emitQueueMetadata(queue, workloadVisitor);
        }
    }
}

/**
 * @brief Remove emulated frame boundaries from the pNext chain.
 *
 * @param layer             The layer context.
 * @param pSubmits          The list of user-supplied submits.
 * @param submitCount       The number of submits in the list.
 * @param safeSubmits       Storage for allocated copies if we need to patch.
 * @param pSubmitsForCall   Pointer passed to the API call.
 */
template <typename T, typename U>
static void stripManualFrameBoundary(
    Device* layer,
    const T* pSubmits,
    uint32_t submitCount,
    std::vector<U>& safeSubmits,
    const T** pSubmitsForCall
) {
    if (layer->isEmulatingExtFrameBoundary)
    {
        safeSubmits.reserve(submitCount);

        for (uint32_t i = 0; i < submitCount; i++)
        {
            safeSubmits.emplace_back(pSubmits + i);
            vku::RemoveFromPnext(safeSubmits[i], VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT);
        }

        *pSubmitsForCall = reinterpret_cast<T*>(safeSubmits.data());
    }
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

    // Create a modifiable structure we can patch
    vku::safe_VkPresentInfoKHR safePresentInfo(pPresentInfo);
    auto* newPresentInfo = reinterpret_cast<VkPresentInfoKHR*>(&safePresentInfo);

    // Remove emulated frame boundaries
    if (layer->isEmulatingExtFrameBoundary)
    {
        vku::RemoveFromPnext(safePresentInfo, VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT);
    }

    // Note that we assume QueuePresent is _always_ the end of a frame.
    // This is run with the lock held to ensure that all queue submit messages
    // are sent sequentially to the host tool
    TimelineProtobufEncoder::emitFrame(*layer, tracker.totalStats.getFrameCount(), getClockMonotonicRaw());

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueuePresentKHR(queue, newPresentInfo);
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

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool
    TimelineProtobufEncoder workloadVisitor {*layer};

    // Add queue-level metadata
    emitQueueMetadata(queue, workloadVisitor);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBuffers[j];
            emitCommandBufferMetadata(*layer, queue, commandBuffer, workloadVisitor);
        }

        // Check for end of frame boundary
        bool isLast = i == submitCount - 1;
        checkManualFrameBoundary(layer, queue, submit.pNext, isLast, workloadVisitor);
    }

    // Remove emulated frame boundaries
    const VkSubmitInfo* newSubmits = pSubmits;
    std::vector<vku::safe_VkSubmitInfo> safeSubmits;

    stripManualFrameBoundary<VkSubmitInfo, vku::safe_VkSubmitInfo>(
        layer, pSubmits, submitCount,
        safeSubmits, &newSubmits);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit(queue, submitCount, newSubmits, fence);
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

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool
    TimelineProtobufEncoder workloadVisitor {*layer};

    // Add queue-level metadata
    emitQueueMetadata(queue, workloadVisitor);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
            emitCommandBufferMetadata(*layer, queue, commandBuffer, workloadVisitor);
        }

        // Check for end of frame boundary
        bool isLast = i == submitCount - 1;
        checkManualFrameBoundary(layer, queue, submit.pNext, isLast, workloadVisitor);
    }

    // Remove emulated frame boundaries
    const VkSubmitInfo2* newSubmits = pSubmits;
    std::vector<vku::safe_VkSubmitInfo2> safeSubmits;

    stripManualFrameBoundary<VkSubmitInfo2, vku::safe_VkSubmitInfo2>(
        layer, pSubmits, submitCount,
        safeSubmits, &newSubmits);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2(queue, submitCount, newSubmits, fence);
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

    // This is run with the lock held to ensure that all queue submit
    // messages are sent sequentially and contiguously to the host tool
    TimelineProtobufEncoder workloadVisitor {*layer};

    // Add queue-level metadata
    emitQueueMetadata(queue, workloadVisitor);

    // Add per-command buffer metadata
    for (uint32_t i = 0; i < submitCount; i++)
    {
        const auto& submit = pSubmits[i];
        for (uint32_t j = 0; j < submit.commandBufferInfoCount; j++)
        {
            VkCommandBuffer commandBuffer = submit.pCommandBufferInfos[j].commandBuffer;
            emitCommandBufferMetadata(*layer, queue, commandBuffer, workloadVisitor);
        }

        // Check for end of frame boundary
        bool isLast = i == submitCount - 1;
        checkManualFrameBoundary(layer, queue, submit.pNext, isLast, workloadVisitor);
    }

    // Remove emulated frame boundaries
    const VkSubmitInfo2* newSubmits = pSubmits;
    std::vector<vku::safe_VkSubmitInfo2> safeSubmits;
    stripManualFrameBoundary<VkSubmitInfo2, vku::safe_VkSubmitInfo2>(
        layer, pSubmits, submitCount,
        safeSubmits, &newSubmits);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2KHR(queue, submitCount, newSubmits, fence);
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

    // Scan infos for frame boundaries
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        const auto& info = pBindInfo[i];

        auto* ext = vku::FindStructInPNextChain<VkFrameBoundaryEXT>(info.pNext);
        if (ext && (ext->flags & VK_FRAME_BOUNDARY_FRAME_END_BIT_EXT))
        {
            // Emulate a queue present to indicate end of frame
            auto& tracker = layer->getStateTracker();
            tracker.queuePresent();
            TimelineProtobufEncoder::emitFrame(*layer, tracker.totalStats.getFrameCount(), getClockMonotonicRaw());
        }
    }

    // Remove emulated frame boundaries
    const VkBindSparseInfo* newBindInfo = pBindInfo;
    std::vector<vku::safe_VkBindSparseInfo> safeInfos;
    stripManualFrameBoundary<VkBindSparseInfo, vku::safe_VkBindSparseInfo>(
        layer, pBindInfo, bindInfoCount,
        safeInfos, &newBindInfo);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueBindSparse(queue, bindInfoCount, newBindInfo, fence);
}