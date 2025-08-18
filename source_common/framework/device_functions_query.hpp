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

#pragma once

// clang-format off

#include <vulkan/vulkan.h>

#include "framework/utils.hpp"

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAcquireNextImage2KHR = requires(
    VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex
) {
    layer_vkAcquireNextImage2KHR<T>(device, pAcquireInfo, pImageIndex);
};

/* Function pointer resolution. */
constexpr PFN_vkAcquireNextImage2KHR getLayerPtr_vkAcquireNextImage2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAcquireNextImage2KHR<T>)
        {
            return layer_vkAcquireNextImage2KHR<T>;
        }

        return layer_vkAcquireNextImage2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAcquireNextImageKHR = requires(
    VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex
) {
    layer_vkAcquireNextImageKHR<T>(device, swapchain, timeout, semaphore, fence, pImageIndex);
};

/* Function pointer resolution. */
constexpr PFN_vkAcquireNextImageKHR getLayerPtr_vkAcquireNextImageKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAcquireNextImageKHR<T>)
        {
            return layer_vkAcquireNextImageKHR<T>;
        }

        return layer_vkAcquireNextImageKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAcquireProfilingLockKHR = requires(
    VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo
) {
    layer_vkAcquireProfilingLockKHR<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkAcquireProfilingLockKHR getLayerPtr_vkAcquireProfilingLockKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAcquireProfilingLockKHR<T>)
        {
            return layer_vkAcquireProfilingLockKHR<T>;
        }

        return layer_vkAcquireProfilingLockKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAllocateCommandBuffers = requires(
    VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers
) {
    layer_vkAllocateCommandBuffers<T>(device, pAllocateInfo, pCommandBuffers);
};

/* Function pointer resolution. */
constexpr PFN_vkAllocateCommandBuffers getLayerPtr_vkAllocateCommandBuffers()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAllocateCommandBuffers<T>)
        {
            return layer_vkAllocateCommandBuffers<T>;
        }

        return layer_vkAllocateCommandBuffers<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAllocateDescriptorSets = requires(
    VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets
) {
    layer_vkAllocateDescriptorSets<T>(device, pAllocateInfo, pDescriptorSets);
};

/* Function pointer resolution. */
constexpr PFN_vkAllocateDescriptorSets getLayerPtr_vkAllocateDescriptorSets()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAllocateDescriptorSets<T>)
        {
            return layer_vkAllocateDescriptorSets<T>;
        }

        return layer_vkAllocateDescriptorSets<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkAllocateMemory = requires(
    VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory
) {
    layer_vkAllocateMemory<T>(device, pAllocateInfo, pAllocator, pMemory);
};

/* Function pointer resolution. */
constexpr PFN_vkAllocateMemory getLayerPtr_vkAllocateMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkAllocateMemory<T>)
        {
            return layer_vkAllocateMemory<T>;
        }

        return layer_vkAllocateMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBeginCommandBuffer = requires(
    VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo
) {
    layer_vkBeginCommandBuffer<T>(commandBuffer, pBeginInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkBeginCommandBuffer getLayerPtr_vkBeginCommandBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBeginCommandBuffer<T>)
        {
            return layer_vkBeginCommandBuffer<T>;
        }

        return layer_vkBeginCommandBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindBufferMemory = requires(
    VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset
) {
    layer_vkBindBufferMemory<T>(device, buffer, memory, memoryOffset);
};

/* Function pointer resolution. */
constexpr PFN_vkBindBufferMemory getLayerPtr_vkBindBufferMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindBufferMemory<T>)
        {
            return layer_vkBindBufferMemory<T>;
        }

        return layer_vkBindBufferMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindBufferMemory2 = requires(
    VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos
) {
    layer_vkBindBufferMemory2<T>(device, bindInfoCount, pBindInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBindBufferMemory2 getLayerPtr_vkBindBufferMemory2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindBufferMemory2<T>)
        {
            return layer_vkBindBufferMemory2<T>;
        }

        return layer_vkBindBufferMemory2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindBufferMemory2KHR = requires(
    VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos
) {
    layer_vkBindBufferMemory2KHR<T>(device, bindInfoCount, pBindInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBindBufferMemory2KHR getLayerPtr_vkBindBufferMemory2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindBufferMemory2KHR<T>)
        {
            return layer_vkBindBufferMemory2KHR<T>;
        }

        return layer_vkBindBufferMemory2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindImageMemory = requires(
    VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset
) {
    layer_vkBindImageMemory<T>(device, image, memory, memoryOffset);
};

/* Function pointer resolution. */
constexpr PFN_vkBindImageMemory getLayerPtr_vkBindImageMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindImageMemory<T>)
        {
            return layer_vkBindImageMemory<T>;
        }

        return layer_vkBindImageMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindImageMemory2 = requires(
    VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos
) {
    layer_vkBindImageMemory2<T>(device, bindInfoCount, pBindInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBindImageMemory2 getLayerPtr_vkBindImageMemory2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindImageMemory2<T>)
        {
            return layer_vkBindImageMemory2<T>;
        }

        return layer_vkBindImageMemory2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindImageMemory2KHR = requires(
    VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos
) {
    layer_vkBindImageMemory2KHR<T>(device, bindInfoCount, pBindInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBindImageMemory2KHR getLayerPtr_vkBindImageMemory2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindImageMemory2KHR<T>)
        {
            return layer_vkBindImageMemory2KHR<T>;
        }

        return layer_vkBindImageMemory2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBindTensorMemoryARM = requires(
    VkDevice device, uint32_t bindInfoCount, const VkBindTensorMemoryInfoARM* pBindInfos
) {
    layer_vkBindTensorMemoryARM<T>(device, bindInfoCount, pBindInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBindTensorMemoryARM getLayerPtr_vkBindTensorMemoryARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBindTensorMemoryARM<T>)
        {
            return layer_vkBindTensorMemoryARM<T>;
        }

        return layer_vkBindTensorMemoryARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBuildAccelerationStructuresKHR = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    layer_vkBuildAccelerationStructuresKHR<T>(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBuildAccelerationStructuresKHR getLayerPtr_vkBuildAccelerationStructuresKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBuildAccelerationStructuresKHR<T>)
        {
            return layer_vkBuildAccelerationStructuresKHR<T>;
        }

        return layer_vkBuildAccelerationStructuresKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkBuildMicromapsEXT = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos
) {
    layer_vkBuildMicromapsEXT<T>(device, deferredOperation, infoCount, pInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkBuildMicromapsEXT getLayerPtr_vkBuildMicromapsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkBuildMicromapsEXT<T>)
        {
            return layer_vkBuildMicromapsEXT<T>;
        }

        return layer_vkBuildMicromapsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginConditionalRenderingEXT = requires(
    VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin
) {
    layer_vkCmdBeginConditionalRenderingEXT<T>(commandBuffer, pConditionalRenderingBegin);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginConditionalRenderingEXT getLayerPtr_vkCmdBeginConditionalRenderingEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginConditionalRenderingEXT<T>)
        {
            return layer_vkCmdBeginConditionalRenderingEXT<T>;
        }

        return layer_vkCmdBeginConditionalRenderingEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginDebugUtilsLabelEXT = requires(
    VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkCmdBeginDebugUtilsLabelEXT<T>(commandBuffer, pLabelInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginDebugUtilsLabelEXT getLayerPtr_vkCmdBeginDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginDebugUtilsLabelEXT<T>)
        {
            return layer_vkCmdBeginDebugUtilsLabelEXT<T>;
        }

        return layer_vkCmdBeginDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginQuery = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags
) {
    layer_vkCmdBeginQuery<T>(commandBuffer, queryPool, query, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginQuery getLayerPtr_vkCmdBeginQuery()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginQuery<T>)
        {
            return layer_vkCmdBeginQuery<T>;
        }

        return layer_vkCmdBeginQuery<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginQueryIndexedEXT = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index
) {
    layer_vkCmdBeginQueryIndexedEXT<T>(commandBuffer, queryPool, query, flags, index);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginQueryIndexedEXT getLayerPtr_vkCmdBeginQueryIndexedEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginQueryIndexedEXT<T>)
        {
            return layer_vkCmdBeginQueryIndexedEXT<T>;
        }

        return layer_vkCmdBeginQueryIndexedEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginRenderPass = requires(
    VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents
) {
    layer_vkCmdBeginRenderPass<T>(commandBuffer, pRenderPassBegin, contents);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginRenderPass getLayerPtr_vkCmdBeginRenderPass()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginRenderPass<T>)
        {
            return layer_vkCmdBeginRenderPass<T>;
        }

        return layer_vkCmdBeginRenderPass<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginRenderPass2 = requires(
    VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    layer_vkCmdBeginRenderPass2<T>(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginRenderPass2 getLayerPtr_vkCmdBeginRenderPass2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginRenderPass2<T>)
        {
            return layer_vkCmdBeginRenderPass2<T>;
        }

        return layer_vkCmdBeginRenderPass2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginRenderPass2KHR = requires(
    VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    layer_vkCmdBeginRenderPass2KHR<T>(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginRenderPass2KHR getLayerPtr_vkCmdBeginRenderPass2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginRenderPass2KHR<T>)
        {
            return layer_vkCmdBeginRenderPass2KHR<T>;
        }

        return layer_vkCmdBeginRenderPass2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginRendering = requires(
    VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo
) {
    layer_vkCmdBeginRendering<T>(commandBuffer, pRenderingInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginRendering getLayerPtr_vkCmdBeginRendering()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginRendering<T>)
        {
            return layer_vkCmdBeginRendering<T>;
        }

        return layer_vkCmdBeginRendering<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginRenderingKHR = requires(
    VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo
) {
    layer_vkCmdBeginRenderingKHR<T>(commandBuffer, pRenderingInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginRenderingKHR getLayerPtr_vkCmdBeginRenderingKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginRenderingKHR<T>)
        {
            return layer_vkCmdBeginRenderingKHR<T>;
        }

        return layer_vkCmdBeginRenderingKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBeginTransformFeedbackEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets
) {
    layer_vkCmdBeginTransformFeedbackEXT<T>(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBeginTransformFeedbackEXT getLayerPtr_vkCmdBeginTransformFeedbackEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBeginTransformFeedbackEXT<T>)
        {
            return layer_vkCmdBeginTransformFeedbackEXT<T>;
        }

        return layer_vkCmdBeginTransformFeedbackEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = requires(
    VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo
) {
    layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<T>(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT getLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<T>)
        {
            return layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<T>;
        }

        return layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplersEXT = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set
) {
    layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<T>(commandBuffer, pipelineBindPoint, layout, set);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT getLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplersEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<T>)
        {
            return layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<T>;
        }

        return layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorBuffersEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos
) {
    layer_vkCmdBindDescriptorBuffersEXT<T>(commandBuffer, bufferCount, pBindingInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorBuffersEXT getLayerPtr_vkCmdBindDescriptorBuffersEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorBuffersEXT<T>)
        {
            return layer_vkCmdBindDescriptorBuffersEXT<T>;
        }

        return layer_vkCmdBindDescriptorBuffersEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorSets = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets
) {
    layer_vkCmdBindDescriptorSets<T>(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorSets getLayerPtr_vkCmdBindDescriptorSets()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorSets<T>)
        {
            return layer_vkCmdBindDescriptorSets<T>;
        }

        return layer_vkCmdBindDescriptorSets<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorSets2 = requires(
    VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    layer_vkCmdBindDescriptorSets2<T>(commandBuffer, pBindDescriptorSetsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorSets2 getLayerPtr_vkCmdBindDescriptorSets2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorSets2<T>)
        {
            return layer_vkCmdBindDescriptorSets2<T>;
        }

        return layer_vkCmdBindDescriptorSets2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindDescriptorSets2KHR = requires(
    VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    layer_vkCmdBindDescriptorSets2KHR<T>(commandBuffer, pBindDescriptorSetsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindDescriptorSets2KHR getLayerPtr_vkCmdBindDescriptorSets2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindDescriptorSets2KHR<T>)
        {
            return layer_vkCmdBindDescriptorSets2KHR<T>;
        }

        return layer_vkCmdBindDescriptorSets2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindIndexBuffer = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer<T>(commandBuffer, buffer, offset, indexType);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindIndexBuffer getLayerPtr_vkCmdBindIndexBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindIndexBuffer<T>)
        {
            return layer_vkCmdBindIndexBuffer<T>;
        }

        return layer_vkCmdBindIndexBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindIndexBuffer2 = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer2<T>(commandBuffer, buffer, offset, size, indexType);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindIndexBuffer2 getLayerPtr_vkCmdBindIndexBuffer2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindIndexBuffer2<T>)
        {
            return layer_vkCmdBindIndexBuffer2<T>;
        }

        return layer_vkCmdBindIndexBuffer2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindIndexBuffer2KHR = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer2KHR<T>(commandBuffer, buffer, offset, size, indexType);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindIndexBuffer2KHR getLayerPtr_vkCmdBindIndexBuffer2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindIndexBuffer2KHR<T>)
        {
            return layer_vkCmdBindIndexBuffer2KHR<T>;
        }

        return layer_vkCmdBindIndexBuffer2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindPipeline = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline
) {
    layer_vkCmdBindPipeline<T>(commandBuffer, pipelineBindPoint, pipeline);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindPipeline getLayerPtr_vkCmdBindPipeline()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindPipeline<T>)
        {
            return layer_vkCmdBindPipeline<T>;
        }

        return layer_vkCmdBindPipeline<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindShadersEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders
) {
    layer_vkCmdBindShadersEXT<T>(commandBuffer, stageCount, pStages, pShaders);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindShadersEXT getLayerPtr_vkCmdBindShadersEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindShadersEXT<T>)
        {
            return layer_vkCmdBindShadersEXT<T>;
        }

        return layer_vkCmdBindShadersEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindTransformFeedbackBuffersEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes
) {
    layer_vkCmdBindTransformFeedbackBuffersEXT<T>(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindTransformFeedbackBuffersEXT getLayerPtr_vkCmdBindTransformFeedbackBuffersEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindTransformFeedbackBuffersEXT<T>)
        {
            return layer_vkCmdBindTransformFeedbackBuffersEXT<T>;
        }

        return layer_vkCmdBindTransformFeedbackBuffersEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindVertexBuffers = requires(
    VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets
) {
    layer_vkCmdBindVertexBuffers<T>(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindVertexBuffers getLayerPtr_vkCmdBindVertexBuffers()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindVertexBuffers<T>)
        {
            return layer_vkCmdBindVertexBuffers<T>;
        }

        return layer_vkCmdBindVertexBuffers<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindVertexBuffers2 = requires(
    VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides
) {
    layer_vkCmdBindVertexBuffers2<T>(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindVertexBuffers2 getLayerPtr_vkCmdBindVertexBuffers2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindVertexBuffers2<T>)
        {
            return layer_vkCmdBindVertexBuffers2<T>;
        }

        return layer_vkCmdBindVertexBuffers2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBindVertexBuffers2EXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides
) {
    layer_vkCmdBindVertexBuffers2EXT<T>(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBindVertexBuffers2EXT getLayerPtr_vkCmdBindVertexBuffers2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBindVertexBuffers2EXT<T>)
        {
            return layer_vkCmdBindVertexBuffers2EXT<T>;
        }

        return layer_vkCmdBindVertexBuffers2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBlitImage = requires(
    VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter
) {
    layer_vkCmdBlitImage<T>(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBlitImage getLayerPtr_vkCmdBlitImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBlitImage<T>)
        {
            return layer_vkCmdBlitImage<T>;
        }

        return layer_vkCmdBlitImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBlitImage2 = requires(
    VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo
) {
    layer_vkCmdBlitImage2<T>(commandBuffer, pBlitImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBlitImage2 getLayerPtr_vkCmdBlitImage2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBlitImage2<T>)
        {
            return layer_vkCmdBlitImage2<T>;
        }

        return layer_vkCmdBlitImage2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBlitImage2KHR = requires(
    VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo
) {
    layer_vkCmdBlitImage2KHR<T>(commandBuffer, pBlitImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBlitImage2KHR getLayerPtr_vkCmdBlitImage2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBlitImage2KHR<T>)
        {
            return layer_vkCmdBlitImage2KHR<T>;
        }

        return layer_vkCmdBlitImage2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBuildAccelerationStructuresIndirectKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts
) {
    layer_vkCmdBuildAccelerationStructuresIndirectKHR<T>(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBuildAccelerationStructuresIndirectKHR getLayerPtr_vkCmdBuildAccelerationStructuresIndirectKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBuildAccelerationStructuresIndirectKHR<T>)
        {
            return layer_vkCmdBuildAccelerationStructuresIndirectKHR<T>;
        }

        return layer_vkCmdBuildAccelerationStructuresIndirectKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBuildAccelerationStructuresKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    layer_vkCmdBuildAccelerationStructuresKHR<T>(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBuildAccelerationStructuresKHR getLayerPtr_vkCmdBuildAccelerationStructuresKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBuildAccelerationStructuresKHR<T>)
        {
            return layer_vkCmdBuildAccelerationStructuresKHR<T>;
        }

        return layer_vkCmdBuildAccelerationStructuresKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdBuildMicromapsEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos
) {
    layer_vkCmdBuildMicromapsEXT<T>(commandBuffer, infoCount, pInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdBuildMicromapsEXT getLayerPtr_vkCmdBuildMicromapsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdBuildMicromapsEXT<T>)
        {
            return layer_vkCmdBuildMicromapsEXT<T>;
        }

        return layer_vkCmdBuildMicromapsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdClearAttachments = requires(
    VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects
) {
    layer_vkCmdClearAttachments<T>(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdClearAttachments getLayerPtr_vkCmdClearAttachments()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdClearAttachments<T>)
        {
            return layer_vkCmdClearAttachments<T>;
        }

        return layer_vkCmdClearAttachments<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdClearColorImage = requires(
    VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges
) {
    layer_vkCmdClearColorImage<T>(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdClearColorImage getLayerPtr_vkCmdClearColorImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdClearColorImage<T>)
        {
            return layer_vkCmdClearColorImage<T>;
        }

        return layer_vkCmdClearColorImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdClearDepthStencilImage = requires(
    VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges
) {
    layer_vkCmdClearDepthStencilImage<T>(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdClearDepthStencilImage getLayerPtr_vkCmdClearDepthStencilImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdClearDepthStencilImage<T>)
        {
            return layer_vkCmdClearDepthStencilImage<T>;
        }

        return layer_vkCmdClearDepthStencilImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyAccelerationStructureKHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCmdCopyAccelerationStructureKHR<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyAccelerationStructureKHR getLayerPtr_vkCmdCopyAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyAccelerationStructureKHR<T>)
        {
            return layer_vkCmdCopyAccelerationStructureKHR<T>;
        }

        return layer_vkCmdCopyAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyAccelerationStructureToMemoryKHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    layer_vkCmdCopyAccelerationStructureToMemoryKHR<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyAccelerationStructureToMemoryKHR getLayerPtr_vkCmdCopyAccelerationStructureToMemoryKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyAccelerationStructureToMemoryKHR<T>)
        {
            return layer_vkCmdCopyAccelerationStructureToMemoryKHR<T>;
        }

        return layer_vkCmdCopyAccelerationStructureToMemoryKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBuffer = requires(
    VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions
) {
    layer_vkCmdCopyBuffer<T>(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBuffer getLayerPtr_vkCmdCopyBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBuffer<T>)
        {
            return layer_vkCmdCopyBuffer<T>;
        }

        return layer_vkCmdCopyBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBuffer2 = requires(
    VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo
) {
    layer_vkCmdCopyBuffer2<T>(commandBuffer, pCopyBufferInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBuffer2 getLayerPtr_vkCmdCopyBuffer2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBuffer2<T>)
        {
            return layer_vkCmdCopyBuffer2<T>;
        }

        return layer_vkCmdCopyBuffer2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBuffer2KHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo
) {
    layer_vkCmdCopyBuffer2KHR<T>(commandBuffer, pCopyBufferInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBuffer2KHR getLayerPtr_vkCmdCopyBuffer2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBuffer2KHR<T>)
        {
            return layer_vkCmdCopyBuffer2KHR<T>;
        }

        return layer_vkCmdCopyBuffer2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBufferToImage = requires(
    VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions
) {
    layer_vkCmdCopyBufferToImage<T>(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBufferToImage getLayerPtr_vkCmdCopyBufferToImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBufferToImage<T>)
        {
            return layer_vkCmdCopyBufferToImage<T>;
        }

        return layer_vkCmdCopyBufferToImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBufferToImage2 = requires(
    VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    layer_vkCmdCopyBufferToImage2<T>(commandBuffer, pCopyBufferToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBufferToImage2 getLayerPtr_vkCmdCopyBufferToImage2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBufferToImage2<T>)
        {
            return layer_vkCmdCopyBufferToImage2<T>;
        }

        return layer_vkCmdCopyBufferToImage2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyBufferToImage2KHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    layer_vkCmdCopyBufferToImage2KHR<T>(commandBuffer, pCopyBufferToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyBufferToImage2KHR getLayerPtr_vkCmdCopyBufferToImage2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyBufferToImage2KHR<T>)
        {
            return layer_vkCmdCopyBufferToImage2KHR<T>;
        }

        return layer_vkCmdCopyBufferToImage2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImage = requires(
    VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions
) {
    layer_vkCmdCopyImage<T>(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImage getLayerPtr_vkCmdCopyImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImage<T>)
        {
            return layer_vkCmdCopyImage<T>;
        }

        return layer_vkCmdCopyImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImage2 = requires(
    VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo
) {
    layer_vkCmdCopyImage2<T>(commandBuffer, pCopyImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImage2 getLayerPtr_vkCmdCopyImage2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImage2<T>)
        {
            return layer_vkCmdCopyImage2<T>;
        }

        return layer_vkCmdCopyImage2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImage2KHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo
) {
    layer_vkCmdCopyImage2KHR<T>(commandBuffer, pCopyImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImage2KHR getLayerPtr_vkCmdCopyImage2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImage2KHR<T>)
        {
            return layer_vkCmdCopyImage2KHR<T>;
        }

        return layer_vkCmdCopyImage2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImageToBuffer = requires(
    VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions
) {
    layer_vkCmdCopyImageToBuffer<T>(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImageToBuffer getLayerPtr_vkCmdCopyImageToBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImageToBuffer<T>)
        {
            return layer_vkCmdCopyImageToBuffer<T>;
        }

        return layer_vkCmdCopyImageToBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImageToBuffer2 = requires(
    VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    layer_vkCmdCopyImageToBuffer2<T>(commandBuffer, pCopyImageToBufferInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImageToBuffer2 getLayerPtr_vkCmdCopyImageToBuffer2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImageToBuffer2<T>)
        {
            return layer_vkCmdCopyImageToBuffer2<T>;
        }

        return layer_vkCmdCopyImageToBuffer2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyImageToBuffer2KHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    layer_vkCmdCopyImageToBuffer2KHR<T>(commandBuffer, pCopyImageToBufferInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyImageToBuffer2KHR getLayerPtr_vkCmdCopyImageToBuffer2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyImageToBuffer2KHR<T>)
        {
            return layer_vkCmdCopyImageToBuffer2KHR<T>;
        }

        return layer_vkCmdCopyImageToBuffer2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyMemoryToAccelerationStructureKHR = requires(
    VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCmdCopyMemoryToAccelerationStructureKHR<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyMemoryToAccelerationStructureKHR getLayerPtr_vkCmdCopyMemoryToAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyMemoryToAccelerationStructureKHR<T>)
        {
            return layer_vkCmdCopyMemoryToAccelerationStructureKHR<T>;
        }

        return layer_vkCmdCopyMemoryToAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyMemoryToMicromapEXT = requires(
    VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    layer_vkCmdCopyMemoryToMicromapEXT<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyMemoryToMicromapEXT getLayerPtr_vkCmdCopyMemoryToMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyMemoryToMicromapEXT<T>)
        {
            return layer_vkCmdCopyMemoryToMicromapEXT<T>;
        }

        return layer_vkCmdCopyMemoryToMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyMicromapEXT = requires(
    VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo
) {
    layer_vkCmdCopyMicromapEXT<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyMicromapEXT getLayerPtr_vkCmdCopyMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyMicromapEXT<T>)
        {
            return layer_vkCmdCopyMicromapEXT<T>;
        }

        return layer_vkCmdCopyMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyMicromapToMemoryEXT = requires(
    VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    layer_vkCmdCopyMicromapToMemoryEXT<T>(commandBuffer, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyMicromapToMemoryEXT getLayerPtr_vkCmdCopyMicromapToMemoryEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyMicromapToMemoryEXT<T>)
        {
            return layer_vkCmdCopyMicromapToMemoryEXT<T>;
        }

        return layer_vkCmdCopyMicromapToMemoryEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyQueryPoolResults = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags
) {
    layer_vkCmdCopyQueryPoolResults<T>(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyQueryPoolResults getLayerPtr_vkCmdCopyQueryPoolResults()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyQueryPoolResults<T>)
        {
            return layer_vkCmdCopyQueryPoolResults<T>;
        }

        return layer_vkCmdCopyQueryPoolResults<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdCopyTensorARM = requires(
    VkCommandBuffer commandBuffer, const VkCopyTensorInfoARM* pCopyTensorInfo
) {
    layer_vkCmdCopyTensorARM<T>(commandBuffer, pCopyTensorInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdCopyTensorARM getLayerPtr_vkCmdCopyTensorARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdCopyTensorARM<T>)
        {
            return layer_vkCmdCopyTensorARM<T>;
        }

        return layer_vkCmdCopyTensorARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDebugMarkerBeginEXT = requires(
    VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    layer_vkCmdDebugMarkerBeginEXT<T>(commandBuffer, pMarkerInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDebugMarkerBeginEXT getLayerPtr_vkCmdDebugMarkerBeginEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDebugMarkerBeginEXT<T>)
        {
            return layer_vkCmdDebugMarkerBeginEXT<T>;
        }

        return layer_vkCmdDebugMarkerBeginEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDebugMarkerEndEXT = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdDebugMarkerEndEXT<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDebugMarkerEndEXT getLayerPtr_vkCmdDebugMarkerEndEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDebugMarkerEndEXT<T>)
        {
            return layer_vkCmdDebugMarkerEndEXT<T>;
        }

        return layer_vkCmdDebugMarkerEndEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDebugMarkerInsertEXT = requires(
    VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    layer_vkCmdDebugMarkerInsertEXT<T>(commandBuffer, pMarkerInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDebugMarkerInsertEXT getLayerPtr_vkCmdDebugMarkerInsertEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDebugMarkerInsertEXT<T>)
        {
            return layer_vkCmdDebugMarkerInsertEXT<T>;
        }

        return layer_vkCmdDebugMarkerInsertEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDispatch = requires(
    VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ
) {
    layer_vkCmdDispatch<T>(commandBuffer, groupCountX, groupCountY, groupCountZ);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDispatch getLayerPtr_vkCmdDispatch()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDispatch<T>)
        {
            return layer_vkCmdDispatch<T>;
        }

        return layer_vkCmdDispatch<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDispatchBase = requires(
    VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ
) {
    layer_vkCmdDispatchBase<T>(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDispatchBase getLayerPtr_vkCmdDispatchBase()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDispatchBase<T>)
        {
            return layer_vkCmdDispatchBase<T>;
        }

        return layer_vkCmdDispatchBase<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDispatchBaseKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ
) {
    layer_vkCmdDispatchBaseKHR<T>(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDispatchBaseKHR getLayerPtr_vkCmdDispatchBaseKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDispatchBaseKHR<T>)
        {
            return layer_vkCmdDispatchBaseKHR<T>;
        }

        return layer_vkCmdDispatchBaseKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDispatchIndirect = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset
) {
    layer_vkCmdDispatchIndirect<T>(commandBuffer, buffer, offset);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDispatchIndirect getLayerPtr_vkCmdDispatchIndirect()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDispatchIndirect<T>)
        {
            return layer_vkCmdDispatchIndirect<T>;
        }

        return layer_vkCmdDispatchIndirect<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDraw = requires(
    VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance
) {
    layer_vkCmdDraw<T>(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDraw getLayerPtr_vkCmdDraw()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDraw<T>)
        {
            return layer_vkCmdDraw<T>;
        }

        return layer_vkCmdDraw<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndexed = requires(
    VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance
) {
    layer_vkCmdDrawIndexed<T>(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndexed getLayerPtr_vkCmdDrawIndexed()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndexed<T>)
        {
            return layer_vkCmdDrawIndexed<T>;
        }

        return layer_vkCmdDrawIndexed<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndexedIndirect = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirect<T>(commandBuffer, buffer, offset, drawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndexedIndirect getLayerPtr_vkCmdDrawIndexedIndirect()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndexedIndirect<T>)
        {
            return layer_vkCmdDrawIndexedIndirect<T>;
        }

        return layer_vkCmdDrawIndexedIndirect<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndexedIndirectCount = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirectCount<T>(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndexedIndirectCount getLayerPtr_vkCmdDrawIndexedIndirectCount()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndexedIndirectCount<T>)
        {
            return layer_vkCmdDrawIndexedIndirectCount<T>;
        }

        return layer_vkCmdDrawIndexedIndirectCount<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndexedIndirectCountKHR = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirectCountKHR<T>(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndexedIndirectCountKHR getLayerPtr_vkCmdDrawIndexedIndirectCountKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndexedIndirectCountKHR<T>)
        {
            return layer_vkCmdDrawIndexedIndirectCountKHR<T>;
        }

        return layer_vkCmdDrawIndexedIndirectCountKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndirect = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride
) {
    layer_vkCmdDrawIndirect<T>(commandBuffer, buffer, offset, drawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndirect getLayerPtr_vkCmdDrawIndirect()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndirect<T>)
        {
            return layer_vkCmdDrawIndirect<T>;
        }

        return layer_vkCmdDrawIndirect<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndirectByteCountEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride
) {
    layer_vkCmdDrawIndirectByteCountEXT<T>(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndirectByteCountEXT getLayerPtr_vkCmdDrawIndirectByteCountEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndirectByteCountEXT<T>)
        {
            return layer_vkCmdDrawIndirectByteCountEXT<T>;
        }

        return layer_vkCmdDrawIndirectByteCountEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndirectCount = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride
) {
    layer_vkCmdDrawIndirectCount<T>(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndirectCount getLayerPtr_vkCmdDrawIndirectCount()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndirectCount<T>)
        {
            return layer_vkCmdDrawIndirectCount<T>;
        }

        return layer_vkCmdDrawIndirectCount<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawIndirectCountKHR = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride
) {
    layer_vkCmdDrawIndirectCountKHR<T>(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawIndirectCountKHR getLayerPtr_vkCmdDrawIndirectCountKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawIndirectCountKHR<T>)
        {
            return layer_vkCmdDrawIndirectCountKHR<T>;
        }

        return layer_vkCmdDrawIndirectCountKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawMeshTasksEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ
) {
    layer_vkCmdDrawMeshTasksEXT<T>(commandBuffer, groupCountX, groupCountY, groupCountZ);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawMeshTasksEXT getLayerPtr_vkCmdDrawMeshTasksEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawMeshTasksEXT<T>)
        {
            return layer_vkCmdDrawMeshTasksEXT<T>;
        }

        return layer_vkCmdDrawMeshTasksEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawMeshTasksIndirectCountEXT = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride
) {
    layer_vkCmdDrawMeshTasksIndirectCountEXT<T>(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawMeshTasksIndirectCountEXT getLayerPtr_vkCmdDrawMeshTasksIndirectCountEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawMeshTasksIndirectCountEXT<T>)
        {
            return layer_vkCmdDrawMeshTasksIndirectCountEXT<T>;
        }

        return layer_vkCmdDrawMeshTasksIndirectCountEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawMeshTasksIndirectEXT = requires(
    VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride
) {
    layer_vkCmdDrawMeshTasksIndirectEXT<T>(commandBuffer, buffer, offset, drawCount, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawMeshTasksIndirectEXT getLayerPtr_vkCmdDrawMeshTasksIndirectEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawMeshTasksIndirectEXT<T>)
        {
            return layer_vkCmdDrawMeshTasksIndirectEXT<T>;
        }

        return layer_vkCmdDrawMeshTasksIndirectEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawMultiEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride
) {
    layer_vkCmdDrawMultiEXT<T>(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawMultiEXT getLayerPtr_vkCmdDrawMultiEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawMultiEXT<T>)
        {
            return layer_vkCmdDrawMultiEXT<T>;
        }

        return layer_vkCmdDrawMultiEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdDrawMultiIndexedEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset
) {
    layer_vkCmdDrawMultiIndexedEXT<T>(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdDrawMultiIndexedEXT getLayerPtr_vkCmdDrawMultiIndexedEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdDrawMultiIndexedEXT<T>)
        {
            return layer_vkCmdDrawMultiIndexedEXT<T>;
        }

        return layer_vkCmdDrawMultiIndexedEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndConditionalRenderingEXT = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndConditionalRenderingEXT<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndConditionalRenderingEXT getLayerPtr_vkCmdEndConditionalRenderingEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndConditionalRenderingEXT<T>)
        {
            return layer_vkCmdEndConditionalRenderingEXT<T>;
        }

        return layer_vkCmdEndConditionalRenderingEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndDebugUtilsLabelEXT = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndDebugUtilsLabelEXT<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndDebugUtilsLabelEXT getLayerPtr_vkCmdEndDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndDebugUtilsLabelEXT<T>)
        {
            return layer_vkCmdEndDebugUtilsLabelEXT<T>;
        }

        return layer_vkCmdEndDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndQuery = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query
) {
    layer_vkCmdEndQuery<T>(commandBuffer, queryPool, query);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndQuery getLayerPtr_vkCmdEndQuery()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndQuery<T>)
        {
            return layer_vkCmdEndQuery<T>;
        }

        return layer_vkCmdEndQuery<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndQueryIndexedEXT = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index
) {
    layer_vkCmdEndQueryIndexedEXT<T>(commandBuffer, queryPool, query, index);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndQueryIndexedEXT getLayerPtr_vkCmdEndQueryIndexedEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndQueryIndexedEXT<T>)
        {
            return layer_vkCmdEndQueryIndexedEXT<T>;
        }

        return layer_vkCmdEndQueryIndexedEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRenderPass = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRenderPass<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRenderPass getLayerPtr_vkCmdEndRenderPass()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRenderPass<T>)
        {
            return layer_vkCmdEndRenderPass<T>;
        }

        return layer_vkCmdEndRenderPass<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRenderPass2 = requires(
    VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdEndRenderPass2<T>(commandBuffer, pSubpassEndInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRenderPass2 getLayerPtr_vkCmdEndRenderPass2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRenderPass2<T>)
        {
            return layer_vkCmdEndRenderPass2<T>;
        }

        return layer_vkCmdEndRenderPass2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRenderPass2KHR = requires(
    VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdEndRenderPass2KHR<T>(commandBuffer, pSubpassEndInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRenderPass2KHR getLayerPtr_vkCmdEndRenderPass2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRenderPass2KHR<T>)
        {
            return layer_vkCmdEndRenderPass2KHR<T>;
        }

        return layer_vkCmdEndRenderPass2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRendering = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRendering<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRendering getLayerPtr_vkCmdEndRendering()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRendering<T>)
        {
            return layer_vkCmdEndRendering<T>;
        }

        return layer_vkCmdEndRendering<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRendering2EXT = requires(
    VkCommandBuffer commandBuffer, const VkRenderingEndInfoEXT* pRenderingEndInfo
) {
    layer_vkCmdEndRendering2EXT<T>(commandBuffer, pRenderingEndInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRendering2EXT getLayerPtr_vkCmdEndRendering2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRendering2EXT<T>)
        {
            return layer_vkCmdEndRendering2EXT<T>;
        }

        return layer_vkCmdEndRendering2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndRenderingKHR = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRenderingKHR<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndRenderingKHR getLayerPtr_vkCmdEndRenderingKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndRenderingKHR<T>)
        {
            return layer_vkCmdEndRenderingKHR<T>;
        }

        return layer_vkCmdEndRenderingKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdEndTransformFeedbackEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets
) {
    layer_vkCmdEndTransformFeedbackEXT<T>(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdEndTransformFeedbackEXT getLayerPtr_vkCmdEndTransformFeedbackEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdEndTransformFeedbackEXT<T>)
        {
            return layer_vkCmdEndTransformFeedbackEXT<T>;
        }

        return layer_vkCmdEndTransformFeedbackEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdExecuteCommands = requires(
    VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers
) {
    layer_vkCmdExecuteCommands<T>(commandBuffer, commandBufferCount, pCommandBuffers);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdExecuteCommands getLayerPtr_vkCmdExecuteCommands()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdExecuteCommands<T>)
        {
            return layer_vkCmdExecuteCommands<T>;
        }

        return layer_vkCmdExecuteCommands<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdExecuteGeneratedCommandsEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo
) {
    layer_vkCmdExecuteGeneratedCommandsEXT<T>(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdExecuteGeneratedCommandsEXT getLayerPtr_vkCmdExecuteGeneratedCommandsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdExecuteGeneratedCommandsEXT<T>)
        {
            return layer_vkCmdExecuteGeneratedCommandsEXT<T>;
        }

        return layer_vkCmdExecuteGeneratedCommandsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdFillBuffer = requires(
    VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data
) {
    layer_vkCmdFillBuffer<T>(commandBuffer, dstBuffer, dstOffset, size, data);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdFillBuffer getLayerPtr_vkCmdFillBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdFillBuffer<T>)
        {
            return layer_vkCmdFillBuffer<T>;
        }

        return layer_vkCmdFillBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdInsertDebugUtilsLabelEXT = requires(
    VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkCmdInsertDebugUtilsLabelEXT<T>(commandBuffer, pLabelInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdInsertDebugUtilsLabelEXT getLayerPtr_vkCmdInsertDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdInsertDebugUtilsLabelEXT<T>)
        {
            return layer_vkCmdInsertDebugUtilsLabelEXT<T>;
        }

        return layer_vkCmdInsertDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdNextSubpass = requires(
    VkCommandBuffer commandBuffer, VkSubpassContents contents
) {
    layer_vkCmdNextSubpass<T>(commandBuffer, contents);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdNextSubpass getLayerPtr_vkCmdNextSubpass()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdNextSubpass<T>)
        {
            return layer_vkCmdNextSubpass<T>;
        }

        return layer_vkCmdNextSubpass<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdNextSubpass2 = requires(
    VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdNextSubpass2<T>(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdNextSubpass2 getLayerPtr_vkCmdNextSubpass2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdNextSubpass2<T>)
        {
            return layer_vkCmdNextSubpass2<T>;
        }

        return layer_vkCmdNextSubpass2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdNextSubpass2KHR = requires(
    VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdNextSubpass2KHR<T>(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdNextSubpass2KHR getLayerPtr_vkCmdNextSubpass2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdNextSubpass2KHR<T>)
        {
            return layer_vkCmdNextSubpass2KHR<T>;
        }

        return layer_vkCmdNextSubpass2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPipelineBarrier = requires(
    VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers
) {
    layer_vkCmdPipelineBarrier<T>(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPipelineBarrier getLayerPtr_vkCmdPipelineBarrier()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPipelineBarrier<T>)
        {
            return layer_vkCmdPipelineBarrier<T>;
        }

        return layer_vkCmdPipelineBarrier<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPipelineBarrier2 = requires(
    VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdPipelineBarrier2<T>(commandBuffer, pDependencyInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPipelineBarrier2 getLayerPtr_vkCmdPipelineBarrier2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPipelineBarrier2<T>)
        {
            return layer_vkCmdPipelineBarrier2<T>;
        }

        return layer_vkCmdPipelineBarrier2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPipelineBarrier2KHR = requires(
    VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdPipelineBarrier2KHR<T>(commandBuffer, pDependencyInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPipelineBarrier2KHR getLayerPtr_vkCmdPipelineBarrier2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPipelineBarrier2KHR<T>)
        {
            return layer_vkCmdPipelineBarrier2KHR<T>;
        }

        return layer_vkCmdPipelineBarrier2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPreprocessGeneratedCommandsEXT = requires(
    VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo, VkCommandBuffer stateCommandBuffer
) {
    layer_vkCmdPreprocessGeneratedCommandsEXT<T>(commandBuffer, pGeneratedCommandsInfo, stateCommandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPreprocessGeneratedCommandsEXT getLayerPtr_vkCmdPreprocessGeneratedCommandsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPreprocessGeneratedCommandsEXT<T>)
        {
            return layer_vkCmdPreprocessGeneratedCommandsEXT<T>;
        }

        return layer_vkCmdPreprocessGeneratedCommandsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushConstants = requires(
    VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues
) {
    layer_vkCmdPushConstants<T>(commandBuffer, layout, stageFlags, offset, size, pValues);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushConstants getLayerPtr_vkCmdPushConstants()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushConstants<T>)
        {
            return layer_vkCmdPushConstants<T>;
        }

        return layer_vkCmdPushConstants<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushConstants2 = requires(
    VkCommandBuffer commandBuffer, const VkPushConstantsInfo* pPushConstantsInfo
) {
    layer_vkCmdPushConstants2<T>(commandBuffer, pPushConstantsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushConstants2 getLayerPtr_vkCmdPushConstants2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushConstants2<T>)
        {
            return layer_vkCmdPushConstants2<T>;
        }

        return layer_vkCmdPushConstants2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushConstants2KHR = requires(
    VkCommandBuffer commandBuffer, const VkPushConstantsInfo* pPushConstantsInfo
) {
    layer_vkCmdPushConstants2KHR<T>(commandBuffer, pPushConstantsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushConstants2KHR getLayerPtr_vkCmdPushConstants2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushConstants2KHR<T>)
        {
            return layer_vkCmdPushConstants2KHR<T>;
        }

        return layer_vkCmdPushConstants2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSet = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites
) {
    layer_vkCmdPushDescriptorSet<T>(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSet getLayerPtr_vkCmdPushDescriptorSet()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSet<T>)
        {
            return layer_vkCmdPushDescriptorSet<T>;
        }

        return layer_vkCmdPushDescriptorSet<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSet2 = requires(
    VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    layer_vkCmdPushDescriptorSet2<T>(commandBuffer, pPushDescriptorSetInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSet2 getLayerPtr_vkCmdPushDescriptorSet2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSet2<T>)
        {
            return layer_vkCmdPushDescriptorSet2<T>;
        }

        return layer_vkCmdPushDescriptorSet2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSet2KHR = requires(
    VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    layer_vkCmdPushDescriptorSet2KHR<T>(commandBuffer, pPushDescriptorSetInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSet2KHR getLayerPtr_vkCmdPushDescriptorSet2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSet2KHR<T>)
        {
            return layer_vkCmdPushDescriptorSet2KHR<T>;
        }

        return layer_vkCmdPushDescriptorSet2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSetKHR = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites
) {
    layer_vkCmdPushDescriptorSetKHR<T>(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSetKHR getLayerPtr_vkCmdPushDescriptorSetKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSetKHR<T>)
        {
            return layer_vkCmdPushDescriptorSetKHR<T>;
        }

        return layer_vkCmdPushDescriptorSetKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSetWithTemplate = requires(
    VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData
) {
    layer_vkCmdPushDescriptorSetWithTemplate<T>(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSetWithTemplate getLayerPtr_vkCmdPushDescriptorSetWithTemplate()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSetWithTemplate<T>)
        {
            return layer_vkCmdPushDescriptorSetWithTemplate<T>;
        }

        return layer_vkCmdPushDescriptorSetWithTemplate<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSetWithTemplate2 = requires(
    VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    layer_vkCmdPushDescriptorSetWithTemplate2<T>(commandBuffer, pPushDescriptorSetWithTemplateInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSetWithTemplate2 getLayerPtr_vkCmdPushDescriptorSetWithTemplate2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSetWithTemplate2<T>)
        {
            return layer_vkCmdPushDescriptorSetWithTemplate2<T>;
        }

        return layer_vkCmdPushDescriptorSetWithTemplate2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSetWithTemplate2KHR = requires(
    VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    layer_vkCmdPushDescriptorSetWithTemplate2KHR<T>(commandBuffer, pPushDescriptorSetWithTemplateInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSetWithTemplate2KHR getLayerPtr_vkCmdPushDescriptorSetWithTemplate2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSetWithTemplate2KHR<T>)
        {
            return layer_vkCmdPushDescriptorSetWithTemplate2KHR<T>;
        }

        return layer_vkCmdPushDescriptorSetWithTemplate2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdPushDescriptorSetWithTemplateKHR = requires(
    VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData
) {
    layer_vkCmdPushDescriptorSetWithTemplateKHR<T>(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdPushDescriptorSetWithTemplateKHR getLayerPtr_vkCmdPushDescriptorSetWithTemplateKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdPushDescriptorSetWithTemplateKHR<T>)
        {
            return layer_vkCmdPushDescriptorSetWithTemplateKHR<T>;
        }

        return layer_vkCmdPushDescriptorSetWithTemplateKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResetEvent = requires(
    VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask
) {
    layer_vkCmdResetEvent<T>(commandBuffer, event, stageMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResetEvent getLayerPtr_vkCmdResetEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResetEvent<T>)
        {
            return layer_vkCmdResetEvent<T>;
        }

        return layer_vkCmdResetEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResetEvent2 = requires(
    VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask
) {
    layer_vkCmdResetEvent2<T>(commandBuffer, event, stageMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResetEvent2 getLayerPtr_vkCmdResetEvent2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResetEvent2<T>)
        {
            return layer_vkCmdResetEvent2<T>;
        }

        return layer_vkCmdResetEvent2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResetEvent2KHR = requires(
    VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask
) {
    layer_vkCmdResetEvent2KHR<T>(commandBuffer, event, stageMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResetEvent2KHR getLayerPtr_vkCmdResetEvent2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResetEvent2KHR<T>)
        {
            return layer_vkCmdResetEvent2KHR<T>;
        }

        return layer_vkCmdResetEvent2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResetQueryPool = requires(
    VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount
) {
    layer_vkCmdResetQueryPool<T>(commandBuffer, queryPool, firstQuery, queryCount);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResetQueryPool getLayerPtr_vkCmdResetQueryPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResetQueryPool<T>)
        {
            return layer_vkCmdResetQueryPool<T>;
        }

        return layer_vkCmdResetQueryPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResolveImage = requires(
    VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions
) {
    layer_vkCmdResolveImage<T>(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResolveImage getLayerPtr_vkCmdResolveImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResolveImage<T>)
        {
            return layer_vkCmdResolveImage<T>;
        }

        return layer_vkCmdResolveImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResolveImage2 = requires(
    VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo
) {
    layer_vkCmdResolveImage2<T>(commandBuffer, pResolveImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResolveImage2 getLayerPtr_vkCmdResolveImage2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResolveImage2<T>)
        {
            return layer_vkCmdResolveImage2<T>;
        }

        return layer_vkCmdResolveImage2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdResolveImage2KHR = requires(
    VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo
) {
    layer_vkCmdResolveImage2KHR<T>(commandBuffer, pResolveImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdResolveImage2KHR getLayerPtr_vkCmdResolveImage2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdResolveImage2KHR<T>)
        {
            return layer_vkCmdResolveImage2KHR<T>;
        }

        return layer_vkCmdResolveImage2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetAlphaToCoverageEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable
) {
    layer_vkCmdSetAlphaToCoverageEnableEXT<T>(commandBuffer, alphaToCoverageEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetAlphaToCoverageEnableEXT getLayerPtr_vkCmdSetAlphaToCoverageEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetAlphaToCoverageEnableEXT<T>)
        {
            return layer_vkCmdSetAlphaToCoverageEnableEXT<T>;
        }

        return layer_vkCmdSetAlphaToCoverageEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetAlphaToOneEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable
) {
    layer_vkCmdSetAlphaToOneEnableEXT<T>(commandBuffer, alphaToOneEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetAlphaToOneEnableEXT getLayerPtr_vkCmdSetAlphaToOneEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetAlphaToOneEnableEXT<T>)
        {
            return layer_vkCmdSetAlphaToOneEnableEXT<T>;
        }

        return layer_vkCmdSetAlphaToOneEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetAttachmentFeedbackLoopEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask
) {
    layer_vkCmdSetAttachmentFeedbackLoopEnableEXT<T>(commandBuffer, aspectMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT getLayerPtr_vkCmdSetAttachmentFeedbackLoopEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetAttachmentFeedbackLoopEnableEXT<T>)
        {
            return layer_vkCmdSetAttachmentFeedbackLoopEnableEXT<T>;
        }

        return layer_vkCmdSetAttachmentFeedbackLoopEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetBlendConstants = requires(
    VkCommandBuffer commandBuffer, const float blendConstants[4]
) {
    layer_vkCmdSetBlendConstants<T>(commandBuffer, blendConstants);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetBlendConstants getLayerPtr_vkCmdSetBlendConstants()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetBlendConstants<T>)
        {
            return layer_vkCmdSetBlendConstants<T>;
        }

        return layer_vkCmdSetBlendConstants<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetColorBlendAdvancedEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced
) {
    layer_vkCmdSetColorBlendAdvancedEXT<T>(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetColorBlendAdvancedEXT getLayerPtr_vkCmdSetColorBlendAdvancedEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetColorBlendAdvancedEXT<T>)
        {
            return layer_vkCmdSetColorBlendAdvancedEXT<T>;
        }

        return layer_vkCmdSetColorBlendAdvancedEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetColorBlendEnableEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables
) {
    layer_vkCmdSetColorBlendEnableEXT<T>(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetColorBlendEnableEXT getLayerPtr_vkCmdSetColorBlendEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetColorBlendEnableEXT<T>)
        {
            return layer_vkCmdSetColorBlendEnableEXT<T>;
        }

        return layer_vkCmdSetColorBlendEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetColorBlendEquationEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations
) {
    layer_vkCmdSetColorBlendEquationEXT<T>(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetColorBlendEquationEXT getLayerPtr_vkCmdSetColorBlendEquationEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetColorBlendEquationEXT<T>)
        {
            return layer_vkCmdSetColorBlendEquationEXT<T>;
        }

        return layer_vkCmdSetColorBlendEquationEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetColorWriteEnableEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables
) {
    layer_vkCmdSetColorWriteEnableEXT<T>(commandBuffer, attachmentCount, pColorWriteEnables);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetColorWriteEnableEXT getLayerPtr_vkCmdSetColorWriteEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetColorWriteEnableEXT<T>)
        {
            return layer_vkCmdSetColorWriteEnableEXT<T>;
        }

        return layer_vkCmdSetColorWriteEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetColorWriteMaskEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks
) {
    layer_vkCmdSetColorWriteMaskEXT<T>(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetColorWriteMaskEXT getLayerPtr_vkCmdSetColorWriteMaskEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetColorWriteMaskEXT<T>)
        {
            return layer_vkCmdSetColorWriteMaskEXT<T>;
        }

        return layer_vkCmdSetColorWriteMaskEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetConservativeRasterizationModeEXT = requires(
    VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode
) {
    layer_vkCmdSetConservativeRasterizationModeEXT<T>(commandBuffer, conservativeRasterizationMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetConservativeRasterizationModeEXT getLayerPtr_vkCmdSetConservativeRasterizationModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetConservativeRasterizationModeEXT<T>)
        {
            return layer_vkCmdSetConservativeRasterizationModeEXT<T>;
        }

        return layer_vkCmdSetConservativeRasterizationModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageModulationModeNV = requires(
    VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode
) {
    layer_vkCmdSetCoverageModulationModeNV<T>(commandBuffer, coverageModulationMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageModulationModeNV getLayerPtr_vkCmdSetCoverageModulationModeNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageModulationModeNV<T>)
        {
            return layer_vkCmdSetCoverageModulationModeNV<T>;
        }

        return layer_vkCmdSetCoverageModulationModeNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageModulationTableEnableNV = requires(
    VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable
) {
    layer_vkCmdSetCoverageModulationTableEnableNV<T>(commandBuffer, coverageModulationTableEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageModulationTableEnableNV getLayerPtr_vkCmdSetCoverageModulationTableEnableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageModulationTableEnableNV<T>)
        {
            return layer_vkCmdSetCoverageModulationTableEnableNV<T>;
        }

        return layer_vkCmdSetCoverageModulationTableEnableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageModulationTableNV = requires(
    VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable
) {
    layer_vkCmdSetCoverageModulationTableNV<T>(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageModulationTableNV getLayerPtr_vkCmdSetCoverageModulationTableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageModulationTableNV<T>)
        {
            return layer_vkCmdSetCoverageModulationTableNV<T>;
        }

        return layer_vkCmdSetCoverageModulationTableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageReductionModeNV = requires(
    VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode
) {
    layer_vkCmdSetCoverageReductionModeNV<T>(commandBuffer, coverageReductionMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageReductionModeNV getLayerPtr_vkCmdSetCoverageReductionModeNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageReductionModeNV<T>)
        {
            return layer_vkCmdSetCoverageReductionModeNV<T>;
        }

        return layer_vkCmdSetCoverageReductionModeNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageToColorEnableNV = requires(
    VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable
) {
    layer_vkCmdSetCoverageToColorEnableNV<T>(commandBuffer, coverageToColorEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageToColorEnableNV getLayerPtr_vkCmdSetCoverageToColorEnableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageToColorEnableNV<T>)
        {
            return layer_vkCmdSetCoverageToColorEnableNV<T>;
        }

        return layer_vkCmdSetCoverageToColorEnableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCoverageToColorLocationNV = requires(
    VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation
) {
    layer_vkCmdSetCoverageToColorLocationNV<T>(commandBuffer, coverageToColorLocation);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCoverageToColorLocationNV getLayerPtr_vkCmdSetCoverageToColorLocationNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCoverageToColorLocationNV<T>)
        {
            return layer_vkCmdSetCoverageToColorLocationNV<T>;
        }

        return layer_vkCmdSetCoverageToColorLocationNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCullMode = requires(
    VkCommandBuffer commandBuffer, VkCullModeFlags cullMode
) {
    layer_vkCmdSetCullMode<T>(commandBuffer, cullMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCullMode getLayerPtr_vkCmdSetCullMode()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCullMode<T>)
        {
            return layer_vkCmdSetCullMode<T>;
        }

        return layer_vkCmdSetCullMode<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetCullModeEXT = requires(
    VkCommandBuffer commandBuffer, VkCullModeFlags cullMode
) {
    layer_vkCmdSetCullModeEXT<T>(commandBuffer, cullMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetCullModeEXT getLayerPtr_vkCmdSetCullModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetCullModeEXT<T>)
        {
            return layer_vkCmdSetCullModeEXT<T>;
        }

        return layer_vkCmdSetCullModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBias = requires(
    VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor
) {
    layer_vkCmdSetDepthBias<T>(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBias getLayerPtr_vkCmdSetDepthBias()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBias<T>)
        {
            return layer_vkCmdSetDepthBias<T>;
        }

        return layer_vkCmdSetDepthBias<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBias2EXT = requires(
    VkCommandBuffer commandBuffer, const VkDepthBiasInfoEXT* pDepthBiasInfo
) {
    layer_vkCmdSetDepthBias2EXT<T>(commandBuffer, pDepthBiasInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBias2EXT getLayerPtr_vkCmdSetDepthBias2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBias2EXT<T>)
        {
            return layer_vkCmdSetDepthBias2EXT<T>;
        }

        return layer_vkCmdSetDepthBias2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBiasEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable
) {
    layer_vkCmdSetDepthBiasEnable<T>(commandBuffer, depthBiasEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBiasEnable getLayerPtr_vkCmdSetDepthBiasEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBiasEnable<T>)
        {
            return layer_vkCmdSetDepthBiasEnable<T>;
        }

        return layer_vkCmdSetDepthBiasEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBiasEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable
) {
    layer_vkCmdSetDepthBiasEnableEXT<T>(commandBuffer, depthBiasEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBiasEnableEXT getLayerPtr_vkCmdSetDepthBiasEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBiasEnableEXT<T>)
        {
            return layer_vkCmdSetDepthBiasEnableEXT<T>;
        }

        return layer_vkCmdSetDepthBiasEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBounds = requires(
    VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds
) {
    layer_vkCmdSetDepthBounds<T>(commandBuffer, minDepthBounds, maxDepthBounds);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBounds getLayerPtr_vkCmdSetDepthBounds()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBounds<T>)
        {
            return layer_vkCmdSetDepthBounds<T>;
        }

        return layer_vkCmdSetDepthBounds<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBoundsTestEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable
) {
    layer_vkCmdSetDepthBoundsTestEnable<T>(commandBuffer, depthBoundsTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBoundsTestEnable getLayerPtr_vkCmdSetDepthBoundsTestEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBoundsTestEnable<T>)
        {
            return layer_vkCmdSetDepthBoundsTestEnable<T>;
        }

        return layer_vkCmdSetDepthBoundsTestEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthBoundsTestEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable
) {
    layer_vkCmdSetDepthBoundsTestEnableEXT<T>(commandBuffer, depthBoundsTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthBoundsTestEnableEXT getLayerPtr_vkCmdSetDepthBoundsTestEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthBoundsTestEnableEXT<T>)
        {
            return layer_vkCmdSetDepthBoundsTestEnableEXT<T>;
        }

        return layer_vkCmdSetDepthBoundsTestEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthClampEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthClampEnable
) {
    layer_vkCmdSetDepthClampEnableEXT<T>(commandBuffer, depthClampEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthClampEnableEXT getLayerPtr_vkCmdSetDepthClampEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthClampEnableEXT<T>)
        {
            return layer_vkCmdSetDepthClampEnableEXT<T>;
        }

        return layer_vkCmdSetDepthClampEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthClampRangeEXT = requires(
    VkCommandBuffer commandBuffer, VkDepthClampModeEXT depthClampMode, const VkDepthClampRangeEXT* pDepthClampRange
) {
    layer_vkCmdSetDepthClampRangeEXT<T>(commandBuffer, depthClampMode, pDepthClampRange);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthClampRangeEXT getLayerPtr_vkCmdSetDepthClampRangeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthClampRangeEXT<T>)
        {
            return layer_vkCmdSetDepthClampRangeEXT<T>;
        }

        return layer_vkCmdSetDepthClampRangeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthClipEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthClipEnable
) {
    layer_vkCmdSetDepthClipEnableEXT<T>(commandBuffer, depthClipEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthClipEnableEXT getLayerPtr_vkCmdSetDepthClipEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthClipEnableEXT<T>)
        {
            return layer_vkCmdSetDepthClipEnableEXT<T>;
        }

        return layer_vkCmdSetDepthClipEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthClipNegativeOneToOneEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne
) {
    layer_vkCmdSetDepthClipNegativeOneToOneEXT<T>(commandBuffer, negativeOneToOne);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthClipNegativeOneToOneEXT getLayerPtr_vkCmdSetDepthClipNegativeOneToOneEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthClipNegativeOneToOneEXT<T>)
        {
            return layer_vkCmdSetDepthClipNegativeOneToOneEXT<T>;
        }

        return layer_vkCmdSetDepthClipNegativeOneToOneEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthCompareOp = requires(
    VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp
) {
    layer_vkCmdSetDepthCompareOp<T>(commandBuffer, depthCompareOp);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthCompareOp getLayerPtr_vkCmdSetDepthCompareOp()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthCompareOp<T>)
        {
            return layer_vkCmdSetDepthCompareOp<T>;
        }

        return layer_vkCmdSetDepthCompareOp<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthCompareOpEXT = requires(
    VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp
) {
    layer_vkCmdSetDepthCompareOpEXT<T>(commandBuffer, depthCompareOp);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthCompareOpEXT getLayerPtr_vkCmdSetDepthCompareOpEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthCompareOpEXT<T>)
        {
            return layer_vkCmdSetDepthCompareOpEXT<T>;
        }

        return layer_vkCmdSetDepthCompareOpEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthTestEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthTestEnable
) {
    layer_vkCmdSetDepthTestEnable<T>(commandBuffer, depthTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthTestEnable getLayerPtr_vkCmdSetDepthTestEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthTestEnable<T>)
        {
            return layer_vkCmdSetDepthTestEnable<T>;
        }

        return layer_vkCmdSetDepthTestEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthTestEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthTestEnable
) {
    layer_vkCmdSetDepthTestEnableEXT<T>(commandBuffer, depthTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthTestEnableEXT getLayerPtr_vkCmdSetDepthTestEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthTestEnableEXT<T>)
        {
            return layer_vkCmdSetDepthTestEnableEXT<T>;
        }

        return layer_vkCmdSetDepthTestEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthWriteEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable
) {
    layer_vkCmdSetDepthWriteEnable<T>(commandBuffer, depthWriteEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthWriteEnable getLayerPtr_vkCmdSetDepthWriteEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthWriteEnable<T>)
        {
            return layer_vkCmdSetDepthWriteEnable<T>;
        }

        return layer_vkCmdSetDepthWriteEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDepthWriteEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable
) {
    layer_vkCmdSetDepthWriteEnableEXT<T>(commandBuffer, depthWriteEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDepthWriteEnableEXT getLayerPtr_vkCmdSetDepthWriteEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDepthWriteEnableEXT<T>)
        {
            return layer_vkCmdSetDepthWriteEnableEXT<T>;
        }

        return layer_vkCmdSetDepthWriteEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDescriptorBufferOffsets2EXT = requires(
    VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo
) {
    layer_vkCmdSetDescriptorBufferOffsets2EXT<T>(commandBuffer, pSetDescriptorBufferOffsetsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDescriptorBufferOffsets2EXT getLayerPtr_vkCmdSetDescriptorBufferOffsets2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDescriptorBufferOffsets2EXT<T>)
        {
            return layer_vkCmdSetDescriptorBufferOffsets2EXT<T>;
        }

        return layer_vkCmdSetDescriptorBufferOffsets2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDescriptorBufferOffsetsEXT = requires(
    VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets
) {
    layer_vkCmdSetDescriptorBufferOffsetsEXT<T>(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDescriptorBufferOffsetsEXT getLayerPtr_vkCmdSetDescriptorBufferOffsetsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDescriptorBufferOffsetsEXT<T>)
        {
            return layer_vkCmdSetDescriptorBufferOffsetsEXT<T>;
        }

        return layer_vkCmdSetDescriptorBufferOffsetsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDeviceMask = requires(
    VkCommandBuffer commandBuffer, uint32_t deviceMask
) {
    layer_vkCmdSetDeviceMask<T>(commandBuffer, deviceMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDeviceMask getLayerPtr_vkCmdSetDeviceMask()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDeviceMask<T>)
        {
            return layer_vkCmdSetDeviceMask<T>;
        }

        return layer_vkCmdSetDeviceMask<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDeviceMaskKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t deviceMask
) {
    layer_vkCmdSetDeviceMaskKHR<T>(commandBuffer, deviceMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDeviceMaskKHR getLayerPtr_vkCmdSetDeviceMaskKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDeviceMaskKHR<T>)
        {
            return layer_vkCmdSetDeviceMaskKHR<T>;
        }

        return layer_vkCmdSetDeviceMaskKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDiscardRectangleEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles
) {
    layer_vkCmdSetDiscardRectangleEXT<T>(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDiscardRectangleEXT getLayerPtr_vkCmdSetDiscardRectangleEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDiscardRectangleEXT<T>)
        {
            return layer_vkCmdSetDiscardRectangleEXT<T>;
        }

        return layer_vkCmdSetDiscardRectangleEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDiscardRectangleEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable
) {
    layer_vkCmdSetDiscardRectangleEnableEXT<T>(commandBuffer, discardRectangleEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDiscardRectangleEnableEXT getLayerPtr_vkCmdSetDiscardRectangleEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDiscardRectangleEnableEXT<T>)
        {
            return layer_vkCmdSetDiscardRectangleEnableEXT<T>;
        }

        return layer_vkCmdSetDiscardRectangleEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetDiscardRectangleModeEXT = requires(
    VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode
) {
    layer_vkCmdSetDiscardRectangleModeEXT<T>(commandBuffer, discardRectangleMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetDiscardRectangleModeEXT getLayerPtr_vkCmdSetDiscardRectangleModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetDiscardRectangleModeEXT<T>)
        {
            return layer_vkCmdSetDiscardRectangleModeEXT<T>;
        }

        return layer_vkCmdSetDiscardRectangleModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetEvent = requires(
    VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask
) {
    layer_vkCmdSetEvent<T>(commandBuffer, event, stageMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetEvent getLayerPtr_vkCmdSetEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetEvent<T>)
        {
            return layer_vkCmdSetEvent<T>;
        }

        return layer_vkCmdSetEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetEvent2 = requires(
    VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdSetEvent2<T>(commandBuffer, event, pDependencyInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetEvent2 getLayerPtr_vkCmdSetEvent2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetEvent2<T>)
        {
            return layer_vkCmdSetEvent2<T>;
        }

        return layer_vkCmdSetEvent2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetEvent2KHR = requires(
    VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdSetEvent2KHR<T>(commandBuffer, event, pDependencyInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetEvent2KHR getLayerPtr_vkCmdSetEvent2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetEvent2KHR<T>)
        {
            return layer_vkCmdSetEvent2KHR<T>;
        }

        return layer_vkCmdSetEvent2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetExtraPrimitiveOverestimationSizeEXT = requires(
    VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize
) {
    layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT<T>(commandBuffer, extraPrimitiveOverestimationSize);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT getLayerPtr_vkCmdSetExtraPrimitiveOverestimationSizeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetExtraPrimitiveOverestimationSizeEXT<T>)
        {
            return layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT<T>;
        }

        return layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetFragmentShadingRateKHR = requires(
    VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2]
) {
    layer_vkCmdSetFragmentShadingRateKHR<T>(commandBuffer, pFragmentSize, combinerOps);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetFragmentShadingRateKHR getLayerPtr_vkCmdSetFragmentShadingRateKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetFragmentShadingRateKHR<T>)
        {
            return layer_vkCmdSetFragmentShadingRateKHR<T>;
        }

        return layer_vkCmdSetFragmentShadingRateKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetFrontFace = requires(
    VkCommandBuffer commandBuffer, VkFrontFace frontFace
) {
    layer_vkCmdSetFrontFace<T>(commandBuffer, frontFace);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetFrontFace getLayerPtr_vkCmdSetFrontFace()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetFrontFace<T>)
        {
            return layer_vkCmdSetFrontFace<T>;
        }

        return layer_vkCmdSetFrontFace<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetFrontFaceEXT = requires(
    VkCommandBuffer commandBuffer, VkFrontFace frontFace
) {
    layer_vkCmdSetFrontFaceEXT<T>(commandBuffer, frontFace);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetFrontFaceEXT getLayerPtr_vkCmdSetFrontFaceEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetFrontFaceEXT<T>)
        {
            return layer_vkCmdSetFrontFaceEXT<T>;
        }

        return layer_vkCmdSetFrontFaceEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineRasterizationModeEXT = requires(
    VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode
) {
    layer_vkCmdSetLineRasterizationModeEXT<T>(commandBuffer, lineRasterizationMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineRasterizationModeEXT getLayerPtr_vkCmdSetLineRasterizationModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineRasterizationModeEXT<T>)
        {
            return layer_vkCmdSetLineRasterizationModeEXT<T>;
        }

        return layer_vkCmdSetLineRasterizationModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineStipple = requires(
    VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStipple<T>(commandBuffer, lineStippleFactor, lineStipplePattern);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineStipple getLayerPtr_vkCmdSetLineStipple()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineStipple<T>)
        {
            return layer_vkCmdSetLineStipple<T>;
        }

        return layer_vkCmdSetLineStipple<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineStippleEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStippleEXT<T>(commandBuffer, lineStippleFactor, lineStipplePattern);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineStippleEXT getLayerPtr_vkCmdSetLineStippleEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineStippleEXT<T>)
        {
            return layer_vkCmdSetLineStippleEXT<T>;
        }

        return layer_vkCmdSetLineStippleEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineStippleEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable
) {
    layer_vkCmdSetLineStippleEnableEXT<T>(commandBuffer, stippledLineEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineStippleEnableEXT getLayerPtr_vkCmdSetLineStippleEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineStippleEnableEXT<T>)
        {
            return layer_vkCmdSetLineStippleEnableEXT<T>;
        }

        return layer_vkCmdSetLineStippleEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineStippleKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStippleKHR<T>(commandBuffer, lineStippleFactor, lineStipplePattern);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineStippleKHR getLayerPtr_vkCmdSetLineStippleKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineStippleKHR<T>)
        {
            return layer_vkCmdSetLineStippleKHR<T>;
        }

        return layer_vkCmdSetLineStippleKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLineWidth = requires(
    VkCommandBuffer commandBuffer, float lineWidth
) {
    layer_vkCmdSetLineWidth<T>(commandBuffer, lineWidth);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLineWidth getLayerPtr_vkCmdSetLineWidth()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLineWidth<T>)
        {
            return layer_vkCmdSetLineWidth<T>;
        }

        return layer_vkCmdSetLineWidth<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLogicOpEXT = requires(
    VkCommandBuffer commandBuffer, VkLogicOp logicOp
) {
    layer_vkCmdSetLogicOpEXT<T>(commandBuffer, logicOp);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLogicOpEXT getLayerPtr_vkCmdSetLogicOpEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLogicOpEXT<T>)
        {
            return layer_vkCmdSetLogicOpEXT<T>;
        }

        return layer_vkCmdSetLogicOpEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetLogicOpEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 logicOpEnable
) {
    layer_vkCmdSetLogicOpEnableEXT<T>(commandBuffer, logicOpEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetLogicOpEnableEXT getLayerPtr_vkCmdSetLogicOpEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetLogicOpEnableEXT<T>)
        {
            return layer_vkCmdSetLogicOpEnableEXT<T>;
        }

        return layer_vkCmdSetLogicOpEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPatchControlPointsEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t patchControlPoints
) {
    layer_vkCmdSetPatchControlPointsEXT<T>(commandBuffer, patchControlPoints);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPatchControlPointsEXT getLayerPtr_vkCmdSetPatchControlPointsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPatchControlPointsEXT<T>)
        {
            return layer_vkCmdSetPatchControlPointsEXT<T>;
        }

        return layer_vkCmdSetPatchControlPointsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPolygonModeEXT = requires(
    VkCommandBuffer commandBuffer, VkPolygonMode polygonMode
) {
    layer_vkCmdSetPolygonModeEXT<T>(commandBuffer, polygonMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPolygonModeEXT getLayerPtr_vkCmdSetPolygonModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPolygonModeEXT<T>)
        {
            return layer_vkCmdSetPolygonModeEXT<T>;
        }

        return layer_vkCmdSetPolygonModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPrimitiveRestartEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable
) {
    layer_vkCmdSetPrimitiveRestartEnable<T>(commandBuffer, primitiveRestartEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPrimitiveRestartEnable getLayerPtr_vkCmdSetPrimitiveRestartEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPrimitiveRestartEnable<T>)
        {
            return layer_vkCmdSetPrimitiveRestartEnable<T>;
        }

        return layer_vkCmdSetPrimitiveRestartEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPrimitiveRestartEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable
) {
    layer_vkCmdSetPrimitiveRestartEnableEXT<T>(commandBuffer, primitiveRestartEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPrimitiveRestartEnableEXT getLayerPtr_vkCmdSetPrimitiveRestartEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPrimitiveRestartEnableEXT<T>)
        {
            return layer_vkCmdSetPrimitiveRestartEnableEXT<T>;
        }

        return layer_vkCmdSetPrimitiveRestartEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPrimitiveTopology = requires(
    VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology
) {
    layer_vkCmdSetPrimitiveTopology<T>(commandBuffer, primitiveTopology);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPrimitiveTopology getLayerPtr_vkCmdSetPrimitiveTopology()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPrimitiveTopology<T>)
        {
            return layer_vkCmdSetPrimitiveTopology<T>;
        }

        return layer_vkCmdSetPrimitiveTopology<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetPrimitiveTopologyEXT = requires(
    VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology
) {
    layer_vkCmdSetPrimitiveTopologyEXT<T>(commandBuffer, primitiveTopology);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetPrimitiveTopologyEXT getLayerPtr_vkCmdSetPrimitiveTopologyEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetPrimitiveTopologyEXT<T>)
        {
            return layer_vkCmdSetPrimitiveTopologyEXT<T>;
        }

        return layer_vkCmdSetPrimitiveTopologyEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetProvokingVertexModeEXT = requires(
    VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode
) {
    layer_vkCmdSetProvokingVertexModeEXT<T>(commandBuffer, provokingVertexMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetProvokingVertexModeEXT getLayerPtr_vkCmdSetProvokingVertexModeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetProvokingVertexModeEXT<T>)
        {
            return layer_vkCmdSetProvokingVertexModeEXT<T>;
        }

        return layer_vkCmdSetProvokingVertexModeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRasterizationSamplesEXT = requires(
    VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples
) {
    layer_vkCmdSetRasterizationSamplesEXT<T>(commandBuffer, rasterizationSamples);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRasterizationSamplesEXT getLayerPtr_vkCmdSetRasterizationSamplesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRasterizationSamplesEXT<T>)
        {
            return layer_vkCmdSetRasterizationSamplesEXT<T>;
        }

        return layer_vkCmdSetRasterizationSamplesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRasterizationStreamEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t rasterizationStream
) {
    layer_vkCmdSetRasterizationStreamEXT<T>(commandBuffer, rasterizationStream);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRasterizationStreamEXT getLayerPtr_vkCmdSetRasterizationStreamEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRasterizationStreamEXT<T>)
        {
            return layer_vkCmdSetRasterizationStreamEXT<T>;
        }

        return layer_vkCmdSetRasterizationStreamEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRasterizerDiscardEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable
) {
    layer_vkCmdSetRasterizerDiscardEnable<T>(commandBuffer, rasterizerDiscardEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRasterizerDiscardEnable getLayerPtr_vkCmdSetRasterizerDiscardEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRasterizerDiscardEnable<T>)
        {
            return layer_vkCmdSetRasterizerDiscardEnable<T>;
        }

        return layer_vkCmdSetRasterizerDiscardEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRasterizerDiscardEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable
) {
    layer_vkCmdSetRasterizerDiscardEnableEXT<T>(commandBuffer, rasterizerDiscardEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRasterizerDiscardEnableEXT getLayerPtr_vkCmdSetRasterizerDiscardEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRasterizerDiscardEnableEXT<T>)
        {
            return layer_vkCmdSetRasterizerDiscardEnableEXT<T>;
        }

        return layer_vkCmdSetRasterizerDiscardEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRayTracingPipelineStackSizeKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t pipelineStackSize
) {
    layer_vkCmdSetRayTracingPipelineStackSizeKHR<T>(commandBuffer, pipelineStackSize);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRayTracingPipelineStackSizeKHR getLayerPtr_vkCmdSetRayTracingPipelineStackSizeKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRayTracingPipelineStackSizeKHR<T>)
        {
            return layer_vkCmdSetRayTracingPipelineStackSizeKHR<T>;
        }

        return layer_vkCmdSetRayTracingPipelineStackSizeKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRenderingAttachmentLocations = requires(
    VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    layer_vkCmdSetRenderingAttachmentLocations<T>(commandBuffer, pLocationInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRenderingAttachmentLocations getLayerPtr_vkCmdSetRenderingAttachmentLocations()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRenderingAttachmentLocations<T>)
        {
            return layer_vkCmdSetRenderingAttachmentLocations<T>;
        }

        return layer_vkCmdSetRenderingAttachmentLocations<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRenderingAttachmentLocationsKHR = requires(
    VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    layer_vkCmdSetRenderingAttachmentLocationsKHR<T>(commandBuffer, pLocationInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRenderingAttachmentLocationsKHR getLayerPtr_vkCmdSetRenderingAttachmentLocationsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRenderingAttachmentLocationsKHR<T>)
        {
            return layer_vkCmdSetRenderingAttachmentLocationsKHR<T>;
        }

        return layer_vkCmdSetRenderingAttachmentLocationsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRenderingInputAttachmentIndices = requires(
    VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    layer_vkCmdSetRenderingInputAttachmentIndices<T>(commandBuffer, pInputAttachmentIndexInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRenderingInputAttachmentIndices getLayerPtr_vkCmdSetRenderingInputAttachmentIndices()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRenderingInputAttachmentIndices<T>)
        {
            return layer_vkCmdSetRenderingInputAttachmentIndices<T>;
        }

        return layer_vkCmdSetRenderingInputAttachmentIndices<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRenderingInputAttachmentIndicesKHR = requires(
    VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    layer_vkCmdSetRenderingInputAttachmentIndicesKHR<T>(commandBuffer, pInputAttachmentIndexInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRenderingInputAttachmentIndicesKHR getLayerPtr_vkCmdSetRenderingInputAttachmentIndicesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRenderingInputAttachmentIndicesKHR<T>)
        {
            return layer_vkCmdSetRenderingInputAttachmentIndicesKHR<T>;
        }

        return layer_vkCmdSetRenderingInputAttachmentIndicesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetRepresentativeFragmentTestEnableNV = requires(
    VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable
) {
    layer_vkCmdSetRepresentativeFragmentTestEnableNV<T>(commandBuffer, representativeFragmentTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetRepresentativeFragmentTestEnableNV getLayerPtr_vkCmdSetRepresentativeFragmentTestEnableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetRepresentativeFragmentTestEnableNV<T>)
        {
            return layer_vkCmdSetRepresentativeFragmentTestEnableNV<T>;
        }

        return layer_vkCmdSetRepresentativeFragmentTestEnableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetSampleLocationsEXT = requires(
    VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo
) {
    layer_vkCmdSetSampleLocationsEXT<T>(commandBuffer, pSampleLocationsInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetSampleLocationsEXT getLayerPtr_vkCmdSetSampleLocationsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetSampleLocationsEXT<T>)
        {
            return layer_vkCmdSetSampleLocationsEXT<T>;
        }

        return layer_vkCmdSetSampleLocationsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetSampleLocationsEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable
) {
    layer_vkCmdSetSampleLocationsEnableEXT<T>(commandBuffer, sampleLocationsEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetSampleLocationsEnableEXT getLayerPtr_vkCmdSetSampleLocationsEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetSampleLocationsEnableEXT<T>)
        {
            return layer_vkCmdSetSampleLocationsEnableEXT<T>;
        }

        return layer_vkCmdSetSampleLocationsEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetSampleMaskEXT = requires(
    VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask
) {
    layer_vkCmdSetSampleMaskEXT<T>(commandBuffer, samples, pSampleMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetSampleMaskEXT getLayerPtr_vkCmdSetSampleMaskEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetSampleMaskEXT<T>)
        {
            return layer_vkCmdSetSampleMaskEXT<T>;
        }

        return layer_vkCmdSetSampleMaskEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetScissor = requires(
    VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors
) {
    layer_vkCmdSetScissor<T>(commandBuffer, firstScissor, scissorCount, pScissors);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetScissor getLayerPtr_vkCmdSetScissor()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetScissor<T>)
        {
            return layer_vkCmdSetScissor<T>;
        }

        return layer_vkCmdSetScissor<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetScissorWithCount = requires(
    VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors
) {
    layer_vkCmdSetScissorWithCount<T>(commandBuffer, scissorCount, pScissors);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetScissorWithCount getLayerPtr_vkCmdSetScissorWithCount()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetScissorWithCount<T>)
        {
            return layer_vkCmdSetScissorWithCount<T>;
        }

        return layer_vkCmdSetScissorWithCount<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetScissorWithCountEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors
) {
    layer_vkCmdSetScissorWithCountEXT<T>(commandBuffer, scissorCount, pScissors);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetScissorWithCountEXT getLayerPtr_vkCmdSetScissorWithCountEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetScissorWithCountEXT<T>)
        {
            return layer_vkCmdSetScissorWithCountEXT<T>;
        }

        return layer_vkCmdSetScissorWithCountEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetShadingRateImageEnableNV = requires(
    VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable
) {
    layer_vkCmdSetShadingRateImageEnableNV<T>(commandBuffer, shadingRateImageEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetShadingRateImageEnableNV getLayerPtr_vkCmdSetShadingRateImageEnableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetShadingRateImageEnableNV<T>)
        {
            return layer_vkCmdSetShadingRateImageEnableNV<T>;
        }

        return layer_vkCmdSetShadingRateImageEnableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilCompareMask = requires(
    VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask
) {
    layer_vkCmdSetStencilCompareMask<T>(commandBuffer, faceMask, compareMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilCompareMask getLayerPtr_vkCmdSetStencilCompareMask()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilCompareMask<T>)
        {
            return layer_vkCmdSetStencilCompareMask<T>;
        }

        return layer_vkCmdSetStencilCompareMask<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilOp = requires(
    VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp
) {
    layer_vkCmdSetStencilOp<T>(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilOp getLayerPtr_vkCmdSetStencilOp()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilOp<T>)
        {
            return layer_vkCmdSetStencilOp<T>;
        }

        return layer_vkCmdSetStencilOp<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilOpEXT = requires(
    VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp
) {
    layer_vkCmdSetStencilOpEXT<T>(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilOpEXT getLayerPtr_vkCmdSetStencilOpEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilOpEXT<T>)
        {
            return layer_vkCmdSetStencilOpEXT<T>;
        }

        return layer_vkCmdSetStencilOpEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilReference = requires(
    VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference
) {
    layer_vkCmdSetStencilReference<T>(commandBuffer, faceMask, reference);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilReference getLayerPtr_vkCmdSetStencilReference()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilReference<T>)
        {
            return layer_vkCmdSetStencilReference<T>;
        }

        return layer_vkCmdSetStencilReference<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilTestEnable = requires(
    VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable
) {
    layer_vkCmdSetStencilTestEnable<T>(commandBuffer, stencilTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilTestEnable getLayerPtr_vkCmdSetStencilTestEnable()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilTestEnable<T>)
        {
            return layer_vkCmdSetStencilTestEnable<T>;
        }

        return layer_vkCmdSetStencilTestEnable<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilTestEnableEXT = requires(
    VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable
) {
    layer_vkCmdSetStencilTestEnableEXT<T>(commandBuffer, stencilTestEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilTestEnableEXT getLayerPtr_vkCmdSetStencilTestEnableEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilTestEnableEXT<T>)
        {
            return layer_vkCmdSetStencilTestEnableEXT<T>;
        }

        return layer_vkCmdSetStencilTestEnableEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetStencilWriteMask = requires(
    VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask
) {
    layer_vkCmdSetStencilWriteMask<T>(commandBuffer, faceMask, writeMask);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetStencilWriteMask getLayerPtr_vkCmdSetStencilWriteMask()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetStencilWriteMask<T>)
        {
            return layer_vkCmdSetStencilWriteMask<T>;
        }

        return layer_vkCmdSetStencilWriteMask<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetTessellationDomainOriginEXT = requires(
    VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin
) {
    layer_vkCmdSetTessellationDomainOriginEXT<T>(commandBuffer, domainOrigin);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetTessellationDomainOriginEXT getLayerPtr_vkCmdSetTessellationDomainOriginEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetTessellationDomainOriginEXT<T>)
        {
            return layer_vkCmdSetTessellationDomainOriginEXT<T>;
        }

        return layer_vkCmdSetTessellationDomainOriginEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetVertexInputEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions
) {
    layer_vkCmdSetVertexInputEXT<T>(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetVertexInputEXT getLayerPtr_vkCmdSetVertexInputEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetVertexInputEXT<T>)
        {
            return layer_vkCmdSetVertexInputEXT<T>;
        }

        return layer_vkCmdSetVertexInputEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetViewport = requires(
    VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports
) {
    layer_vkCmdSetViewport<T>(commandBuffer, firstViewport, viewportCount, pViewports);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetViewport getLayerPtr_vkCmdSetViewport()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetViewport<T>)
        {
            return layer_vkCmdSetViewport<T>;
        }

        return layer_vkCmdSetViewport<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetViewportSwizzleNV = requires(
    VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles
) {
    layer_vkCmdSetViewportSwizzleNV<T>(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetViewportSwizzleNV getLayerPtr_vkCmdSetViewportSwizzleNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetViewportSwizzleNV<T>)
        {
            return layer_vkCmdSetViewportSwizzleNV<T>;
        }

        return layer_vkCmdSetViewportSwizzleNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetViewportWScalingEnableNV = requires(
    VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable
) {
    layer_vkCmdSetViewportWScalingEnableNV<T>(commandBuffer, viewportWScalingEnable);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetViewportWScalingEnableNV getLayerPtr_vkCmdSetViewportWScalingEnableNV()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetViewportWScalingEnableNV<T>)
        {
            return layer_vkCmdSetViewportWScalingEnableNV<T>;
        }

        return layer_vkCmdSetViewportWScalingEnableNV<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetViewportWithCount = requires(
    VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports
) {
    layer_vkCmdSetViewportWithCount<T>(commandBuffer, viewportCount, pViewports);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetViewportWithCount getLayerPtr_vkCmdSetViewportWithCount()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetViewportWithCount<T>)
        {
            return layer_vkCmdSetViewportWithCount<T>;
        }

        return layer_vkCmdSetViewportWithCount<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdSetViewportWithCountEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports
) {
    layer_vkCmdSetViewportWithCountEXT<T>(commandBuffer, viewportCount, pViewports);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdSetViewportWithCountEXT getLayerPtr_vkCmdSetViewportWithCountEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdSetViewportWithCountEXT<T>)
        {
            return layer_vkCmdSetViewportWithCountEXT<T>;
        }

        return layer_vkCmdSetViewportWithCountEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdTraceRaysIndirect2KHR = requires(
    VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress
) {
    layer_vkCmdTraceRaysIndirect2KHR<T>(commandBuffer, indirectDeviceAddress);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdTraceRaysIndirect2KHR getLayerPtr_vkCmdTraceRaysIndirect2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdTraceRaysIndirect2KHR<T>)
        {
            return layer_vkCmdTraceRaysIndirect2KHR<T>;
        }

        return layer_vkCmdTraceRaysIndirect2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdTraceRaysIndirectKHR = requires(
    VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress
) {
    layer_vkCmdTraceRaysIndirectKHR<T>(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdTraceRaysIndirectKHR getLayerPtr_vkCmdTraceRaysIndirectKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdTraceRaysIndirectKHR<T>)
        {
            return layer_vkCmdTraceRaysIndirectKHR<T>;
        }

        return layer_vkCmdTraceRaysIndirectKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdTraceRaysKHR = requires(
    VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth
) {
    layer_vkCmdTraceRaysKHR<T>(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdTraceRaysKHR getLayerPtr_vkCmdTraceRaysKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdTraceRaysKHR<T>)
        {
            return layer_vkCmdTraceRaysKHR<T>;
        }

        return layer_vkCmdTraceRaysKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdUpdateBuffer = requires(
    VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData
) {
    layer_vkCmdUpdateBuffer<T>(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdUpdateBuffer getLayerPtr_vkCmdUpdateBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdUpdateBuffer<T>)
        {
            return layer_vkCmdUpdateBuffer<T>;
        }

        return layer_vkCmdUpdateBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWaitEvents = requires(
    VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers
) {
    layer_vkCmdWaitEvents<T>(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWaitEvents getLayerPtr_vkCmdWaitEvents()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWaitEvents<T>)
        {
            return layer_vkCmdWaitEvents<T>;
        }

        return layer_vkCmdWaitEvents<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWaitEvents2 = requires(
    VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos
) {
    layer_vkCmdWaitEvents2<T>(commandBuffer, eventCount, pEvents, pDependencyInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWaitEvents2 getLayerPtr_vkCmdWaitEvents2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWaitEvents2<T>)
        {
            return layer_vkCmdWaitEvents2<T>;
        }

        return layer_vkCmdWaitEvents2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWaitEvents2KHR = requires(
    VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos
) {
    layer_vkCmdWaitEvents2KHR<T>(commandBuffer, eventCount, pEvents, pDependencyInfos);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWaitEvents2KHR getLayerPtr_vkCmdWaitEvents2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWaitEvents2KHR<T>)
        {
            return layer_vkCmdWaitEvents2KHR<T>;
        }

        return layer_vkCmdWaitEvents2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWriteAccelerationStructuresPropertiesKHR = requires(
    VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery
) {
    layer_vkCmdWriteAccelerationStructuresPropertiesKHR<T>(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWriteAccelerationStructuresPropertiesKHR getLayerPtr_vkCmdWriteAccelerationStructuresPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWriteAccelerationStructuresPropertiesKHR<T>)
        {
            return layer_vkCmdWriteAccelerationStructuresPropertiesKHR<T>;
        }

        return layer_vkCmdWriteAccelerationStructuresPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWriteMicromapsPropertiesEXT = requires(
    VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery
) {
    layer_vkCmdWriteMicromapsPropertiesEXT<T>(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWriteMicromapsPropertiesEXT getLayerPtr_vkCmdWriteMicromapsPropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWriteMicromapsPropertiesEXT<T>)
        {
            return layer_vkCmdWriteMicromapsPropertiesEXT<T>;
        }

        return layer_vkCmdWriteMicromapsPropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWriteTimestamp = requires(
    VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query
) {
    layer_vkCmdWriteTimestamp<T>(commandBuffer, pipelineStage, queryPool, query);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWriteTimestamp getLayerPtr_vkCmdWriteTimestamp()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWriteTimestamp<T>)
        {
            return layer_vkCmdWriteTimestamp<T>;
        }

        return layer_vkCmdWriteTimestamp<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWriteTimestamp2 = requires(
    VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query
) {
    layer_vkCmdWriteTimestamp2<T>(commandBuffer, stage, queryPool, query);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWriteTimestamp2 getLayerPtr_vkCmdWriteTimestamp2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWriteTimestamp2<T>)
        {
            return layer_vkCmdWriteTimestamp2<T>;
        }

        return layer_vkCmdWriteTimestamp2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCmdWriteTimestamp2KHR = requires(
    VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query
) {
    layer_vkCmdWriteTimestamp2KHR<T>(commandBuffer, stage, queryPool, query);
};

/* Function pointer resolution. */
constexpr PFN_vkCmdWriteTimestamp2KHR getLayerPtr_vkCmdWriteTimestamp2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCmdWriteTimestamp2KHR<T>)
        {
            return layer_vkCmdWriteTimestamp2KHR<T>;
        }

        return layer_vkCmdWriteTimestamp2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyAccelerationStructureKHR = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCopyAccelerationStructureKHR<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyAccelerationStructureKHR getLayerPtr_vkCopyAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyAccelerationStructureKHR<T>)
        {
            return layer_vkCopyAccelerationStructureKHR<T>;
        }

        return layer_vkCopyAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyAccelerationStructureToMemoryKHR = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    layer_vkCopyAccelerationStructureToMemoryKHR<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyAccelerationStructureToMemoryKHR getLayerPtr_vkCopyAccelerationStructureToMemoryKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyAccelerationStructureToMemoryKHR<T>)
        {
            return layer_vkCopyAccelerationStructureToMemoryKHR<T>;
        }

        return layer_vkCopyAccelerationStructureToMemoryKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyImageToImage = requires(
    VkDevice device, const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    layer_vkCopyImageToImage<T>(device, pCopyImageToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyImageToImage getLayerPtr_vkCopyImageToImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyImageToImage<T>)
        {
            return layer_vkCopyImageToImage<T>;
        }

        return layer_vkCopyImageToImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyImageToImageEXT = requires(
    VkDevice device, const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    layer_vkCopyImageToImageEXT<T>(device, pCopyImageToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyImageToImageEXT getLayerPtr_vkCopyImageToImageEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyImageToImageEXT<T>)
        {
            return layer_vkCopyImageToImageEXT<T>;
        }

        return layer_vkCopyImageToImageEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyImageToMemory = requires(
    VkDevice device, const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    layer_vkCopyImageToMemory<T>(device, pCopyImageToMemoryInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyImageToMemory getLayerPtr_vkCopyImageToMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyImageToMemory<T>)
        {
            return layer_vkCopyImageToMemory<T>;
        }

        return layer_vkCopyImageToMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyImageToMemoryEXT = requires(
    VkDevice device, const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    layer_vkCopyImageToMemoryEXT<T>(device, pCopyImageToMemoryInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyImageToMemoryEXT getLayerPtr_vkCopyImageToMemoryEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyImageToMemoryEXT<T>)
        {
            return layer_vkCopyImageToMemoryEXT<T>;
        }

        return layer_vkCopyImageToMemoryEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMemoryToAccelerationStructureKHR = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCopyMemoryToAccelerationStructureKHR<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMemoryToAccelerationStructureKHR getLayerPtr_vkCopyMemoryToAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMemoryToAccelerationStructureKHR<T>)
        {
            return layer_vkCopyMemoryToAccelerationStructureKHR<T>;
        }

        return layer_vkCopyMemoryToAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMemoryToImage = requires(
    VkDevice device, const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    layer_vkCopyMemoryToImage<T>(device, pCopyMemoryToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMemoryToImage getLayerPtr_vkCopyMemoryToImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMemoryToImage<T>)
        {
            return layer_vkCopyMemoryToImage<T>;
        }

        return layer_vkCopyMemoryToImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMemoryToImageEXT = requires(
    VkDevice device, const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    layer_vkCopyMemoryToImageEXT<T>(device, pCopyMemoryToImageInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMemoryToImageEXT getLayerPtr_vkCopyMemoryToImageEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMemoryToImageEXT<T>)
        {
            return layer_vkCopyMemoryToImageEXT<T>;
        }

        return layer_vkCopyMemoryToImageEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMemoryToMicromapEXT = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    layer_vkCopyMemoryToMicromapEXT<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMemoryToMicromapEXT getLayerPtr_vkCopyMemoryToMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMemoryToMicromapEXT<T>)
        {
            return layer_vkCopyMemoryToMicromapEXT<T>;
        }

        return layer_vkCopyMemoryToMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMicromapEXT = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo
) {
    layer_vkCopyMicromapEXT<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMicromapEXT getLayerPtr_vkCopyMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMicromapEXT<T>)
        {
            return layer_vkCopyMicromapEXT<T>;
        }

        return layer_vkCopyMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCopyMicromapToMemoryEXT = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    layer_vkCopyMicromapToMemoryEXT<T>(device, deferredOperation, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkCopyMicromapToMemoryEXT getLayerPtr_vkCopyMicromapToMemoryEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCopyMicromapToMemoryEXT<T>)
        {
            return layer_vkCopyMicromapToMemoryEXT<T>;
        }

        return layer_vkCopyMicromapToMemoryEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateAccelerationStructureKHR = requires(
    VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure
) {
    layer_vkCreateAccelerationStructureKHR<T>(device, pCreateInfo, pAllocator, pAccelerationStructure);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateAccelerationStructureKHR getLayerPtr_vkCreateAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateAccelerationStructureKHR<T>)
        {
            return layer_vkCreateAccelerationStructureKHR<T>;
        }

        return layer_vkCreateAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateBuffer = requires(
    VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer
) {
    layer_vkCreateBuffer<T>(device, pCreateInfo, pAllocator, pBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateBuffer getLayerPtr_vkCreateBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateBuffer<T>)
        {
            return layer_vkCreateBuffer<T>;
        }

        return layer_vkCreateBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateBufferView = requires(
    VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView
) {
    layer_vkCreateBufferView<T>(device, pCreateInfo, pAllocator, pView);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateBufferView getLayerPtr_vkCreateBufferView()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateBufferView<T>)
        {
            return layer_vkCreateBufferView<T>;
        }

        return layer_vkCreateBufferView<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateCommandPool = requires(
    VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool
) {
    layer_vkCreateCommandPool<T>(device, pCreateInfo, pAllocator, pCommandPool);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateCommandPool getLayerPtr_vkCreateCommandPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateCommandPool<T>)
        {
            return layer_vkCreateCommandPool<T>;
        }

        return layer_vkCreateCommandPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateComputePipelines = requires(
    VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines
) {
    layer_vkCreateComputePipelines<T>(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateComputePipelines getLayerPtr_vkCreateComputePipelines()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateComputePipelines<T>)
        {
            return layer_vkCreateComputePipelines<T>;
        }

        return layer_vkCreateComputePipelines<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDeferredOperationKHR = requires(
    VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation
) {
    layer_vkCreateDeferredOperationKHR<T>(device, pAllocator, pDeferredOperation);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDeferredOperationKHR getLayerPtr_vkCreateDeferredOperationKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDeferredOperationKHR<T>)
        {
            return layer_vkCreateDeferredOperationKHR<T>;
        }

        return layer_vkCreateDeferredOperationKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDescriptorPool = requires(
    VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool
) {
    layer_vkCreateDescriptorPool<T>(device, pCreateInfo, pAllocator, pDescriptorPool);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDescriptorPool getLayerPtr_vkCreateDescriptorPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDescriptorPool<T>)
        {
            return layer_vkCreateDescriptorPool<T>;
        }

        return layer_vkCreateDescriptorPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDescriptorSetLayout = requires(
    VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout
) {
    layer_vkCreateDescriptorSetLayout<T>(device, pCreateInfo, pAllocator, pSetLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDescriptorSetLayout getLayerPtr_vkCreateDescriptorSetLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDescriptorSetLayout<T>)
        {
            return layer_vkCreateDescriptorSetLayout<T>;
        }

        return layer_vkCreateDescriptorSetLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDescriptorUpdateTemplate = requires(
    VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    layer_vkCreateDescriptorUpdateTemplate<T>(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDescriptorUpdateTemplate getLayerPtr_vkCreateDescriptorUpdateTemplate()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDescriptorUpdateTemplate<T>)
        {
            return layer_vkCreateDescriptorUpdateTemplate<T>;
        }

        return layer_vkCreateDescriptorUpdateTemplate<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDescriptorUpdateTemplateKHR = requires(
    VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    layer_vkCreateDescriptorUpdateTemplateKHR<T>(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDescriptorUpdateTemplateKHR getLayerPtr_vkCreateDescriptorUpdateTemplateKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDescriptorUpdateTemplateKHR<T>)
        {
            return layer_vkCreateDescriptorUpdateTemplateKHR<T>;
        }

        return layer_vkCreateDescriptorUpdateTemplateKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateEvent = requires(
    VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent
) {
    layer_vkCreateEvent<T>(device, pCreateInfo, pAllocator, pEvent);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateEvent getLayerPtr_vkCreateEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateEvent<T>)
        {
            return layer_vkCreateEvent<T>;
        }

        return layer_vkCreateEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateFence = requires(
    VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence
) {
    layer_vkCreateFence<T>(device, pCreateInfo, pAllocator, pFence);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateFence getLayerPtr_vkCreateFence()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateFence<T>)
        {
            return layer_vkCreateFence<T>;
        }

        return layer_vkCreateFence<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateFramebuffer = requires(
    VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer
) {
    layer_vkCreateFramebuffer<T>(device, pCreateInfo, pAllocator, pFramebuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateFramebuffer getLayerPtr_vkCreateFramebuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateFramebuffer<T>)
        {
            return layer_vkCreateFramebuffer<T>;
        }

        return layer_vkCreateFramebuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateGraphicsPipelines = requires(
    VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines
) {
    layer_vkCreateGraphicsPipelines<T>(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateGraphicsPipelines getLayerPtr_vkCreateGraphicsPipelines()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateGraphicsPipelines<T>)
        {
            return layer_vkCreateGraphicsPipelines<T>;
        }

        return layer_vkCreateGraphicsPipelines<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateImage = requires(
    VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage
) {
    layer_vkCreateImage<T>(device, pCreateInfo, pAllocator, pImage);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateImage getLayerPtr_vkCreateImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateImage<T>)
        {
            return layer_vkCreateImage<T>;
        }

        return layer_vkCreateImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateImageView = requires(
    VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView
) {
    layer_vkCreateImageView<T>(device, pCreateInfo, pAllocator, pView);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateImageView getLayerPtr_vkCreateImageView()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateImageView<T>)
        {
            return layer_vkCreateImageView<T>;
        }

        return layer_vkCreateImageView<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateIndirectCommandsLayoutEXT = requires(
    VkDevice device, const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout
) {
    layer_vkCreateIndirectCommandsLayoutEXT<T>(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateIndirectCommandsLayoutEXT getLayerPtr_vkCreateIndirectCommandsLayoutEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateIndirectCommandsLayoutEXT<T>)
        {
            return layer_vkCreateIndirectCommandsLayoutEXT<T>;
        }

        return layer_vkCreateIndirectCommandsLayoutEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateIndirectExecutionSetEXT = requires(
    VkDevice device, const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectExecutionSetEXT* pIndirectExecutionSet
) {
    layer_vkCreateIndirectExecutionSetEXT<T>(device, pCreateInfo, pAllocator, pIndirectExecutionSet);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateIndirectExecutionSetEXT getLayerPtr_vkCreateIndirectExecutionSetEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateIndirectExecutionSetEXT<T>)
        {
            return layer_vkCreateIndirectExecutionSetEXT<T>;
        }

        return layer_vkCreateIndirectExecutionSetEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateMicromapEXT = requires(
    VkDevice device, const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap
) {
    layer_vkCreateMicromapEXT<T>(device, pCreateInfo, pAllocator, pMicromap);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateMicromapEXT getLayerPtr_vkCreateMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateMicromapEXT<T>)
        {
            return layer_vkCreateMicromapEXT<T>;
        }

        return layer_vkCreateMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreatePipelineBinariesKHR = requires(
    VkDevice device, const VkPipelineBinaryCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineBinaryHandlesInfoKHR* pBinaries
) {
    layer_vkCreatePipelineBinariesKHR<T>(device, pCreateInfo, pAllocator, pBinaries);
};

/* Function pointer resolution. */
constexpr PFN_vkCreatePipelineBinariesKHR getLayerPtr_vkCreatePipelineBinariesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreatePipelineBinariesKHR<T>)
        {
            return layer_vkCreatePipelineBinariesKHR<T>;
        }

        return layer_vkCreatePipelineBinariesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreatePipelineCache = requires(
    VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache
) {
    layer_vkCreatePipelineCache<T>(device, pCreateInfo, pAllocator, pPipelineCache);
};

/* Function pointer resolution. */
constexpr PFN_vkCreatePipelineCache getLayerPtr_vkCreatePipelineCache()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreatePipelineCache<T>)
        {
            return layer_vkCreatePipelineCache<T>;
        }

        return layer_vkCreatePipelineCache<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreatePipelineLayout = requires(
    VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout
) {
    layer_vkCreatePipelineLayout<T>(device, pCreateInfo, pAllocator, pPipelineLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkCreatePipelineLayout getLayerPtr_vkCreatePipelineLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreatePipelineLayout<T>)
        {
            return layer_vkCreatePipelineLayout<T>;
        }

        return layer_vkCreatePipelineLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreatePrivateDataSlot = requires(
    VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot
) {
    layer_vkCreatePrivateDataSlot<T>(device, pCreateInfo, pAllocator, pPrivateDataSlot);
};

/* Function pointer resolution. */
constexpr PFN_vkCreatePrivateDataSlot getLayerPtr_vkCreatePrivateDataSlot()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreatePrivateDataSlot<T>)
        {
            return layer_vkCreatePrivateDataSlot<T>;
        }

        return layer_vkCreatePrivateDataSlot<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreatePrivateDataSlotEXT = requires(
    VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot
) {
    layer_vkCreatePrivateDataSlotEXT<T>(device, pCreateInfo, pAllocator, pPrivateDataSlot);
};

/* Function pointer resolution. */
constexpr PFN_vkCreatePrivateDataSlotEXT getLayerPtr_vkCreatePrivateDataSlotEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreatePrivateDataSlotEXT<T>)
        {
            return layer_vkCreatePrivateDataSlotEXT<T>;
        }

        return layer_vkCreatePrivateDataSlotEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateQueryPool = requires(
    VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool
) {
    layer_vkCreateQueryPool<T>(device, pCreateInfo, pAllocator, pQueryPool);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateQueryPool getLayerPtr_vkCreateQueryPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateQueryPool<T>)
        {
            return layer_vkCreateQueryPool<T>;
        }

        return layer_vkCreateQueryPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateRayTracingPipelinesKHR = requires(
    VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines
) {
    layer_vkCreateRayTracingPipelinesKHR<T>(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateRayTracingPipelinesKHR getLayerPtr_vkCreateRayTracingPipelinesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateRayTracingPipelinesKHR<T>)
        {
            return layer_vkCreateRayTracingPipelinesKHR<T>;
        }

        return layer_vkCreateRayTracingPipelinesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateRenderPass = requires(
    VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass
) {
    layer_vkCreateRenderPass<T>(device, pCreateInfo, pAllocator, pRenderPass);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateRenderPass getLayerPtr_vkCreateRenderPass()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateRenderPass<T>)
        {
            return layer_vkCreateRenderPass<T>;
        }

        return layer_vkCreateRenderPass<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateRenderPass2 = requires(
    VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass
) {
    layer_vkCreateRenderPass2<T>(device, pCreateInfo, pAllocator, pRenderPass);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateRenderPass2 getLayerPtr_vkCreateRenderPass2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateRenderPass2<T>)
        {
            return layer_vkCreateRenderPass2<T>;
        }

        return layer_vkCreateRenderPass2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateRenderPass2KHR = requires(
    VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass
) {
    layer_vkCreateRenderPass2KHR<T>(device, pCreateInfo, pAllocator, pRenderPass);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateRenderPass2KHR getLayerPtr_vkCreateRenderPass2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateRenderPass2KHR<T>)
        {
            return layer_vkCreateRenderPass2KHR<T>;
        }

        return layer_vkCreateRenderPass2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSampler = requires(
    VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler
) {
    layer_vkCreateSampler<T>(device, pCreateInfo, pAllocator, pSampler);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSampler getLayerPtr_vkCreateSampler()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSampler<T>)
        {
            return layer_vkCreateSampler<T>;
        }

        return layer_vkCreateSampler<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSamplerYcbcrConversion = requires(
    VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion
) {
    layer_vkCreateSamplerYcbcrConversion<T>(device, pCreateInfo, pAllocator, pYcbcrConversion);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSamplerYcbcrConversion getLayerPtr_vkCreateSamplerYcbcrConversion()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSamplerYcbcrConversion<T>)
        {
            return layer_vkCreateSamplerYcbcrConversion<T>;
        }

        return layer_vkCreateSamplerYcbcrConversion<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSamplerYcbcrConversionKHR = requires(
    VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion
) {
    layer_vkCreateSamplerYcbcrConversionKHR<T>(device, pCreateInfo, pAllocator, pYcbcrConversion);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSamplerYcbcrConversionKHR getLayerPtr_vkCreateSamplerYcbcrConversionKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSamplerYcbcrConversionKHR<T>)
        {
            return layer_vkCreateSamplerYcbcrConversionKHR<T>;
        }

        return layer_vkCreateSamplerYcbcrConversionKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSemaphore = requires(
    VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore
) {
    layer_vkCreateSemaphore<T>(device, pCreateInfo, pAllocator, pSemaphore);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSemaphore getLayerPtr_vkCreateSemaphore()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSemaphore<T>)
        {
            return layer_vkCreateSemaphore<T>;
        }

        return layer_vkCreateSemaphore<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateShaderModule = requires(
    VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule
) {
    layer_vkCreateShaderModule<T>(device, pCreateInfo, pAllocator, pShaderModule);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateShaderModule getLayerPtr_vkCreateShaderModule()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateShaderModule<T>)
        {
            return layer_vkCreateShaderModule<T>;
        }

        return layer_vkCreateShaderModule<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateShadersEXT = requires(
    VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders
) {
    layer_vkCreateShadersEXT<T>(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateShadersEXT getLayerPtr_vkCreateShadersEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateShadersEXT<T>)
        {
            return layer_vkCreateShadersEXT<T>;
        }

        return layer_vkCreateShadersEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSharedSwapchainsKHR = requires(
    VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains
) {
    layer_vkCreateSharedSwapchainsKHR<T>(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSharedSwapchainsKHR getLayerPtr_vkCreateSharedSwapchainsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSharedSwapchainsKHR<T>)
        {
            return layer_vkCreateSharedSwapchainsKHR<T>;
        }

        return layer_vkCreateSharedSwapchainsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateSwapchainKHR = requires(
    VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain
) {
    layer_vkCreateSwapchainKHR<T>(device, pCreateInfo, pAllocator, pSwapchain);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateSwapchainKHR getLayerPtr_vkCreateSwapchainKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateSwapchainKHR<T>)
        {
            return layer_vkCreateSwapchainKHR<T>;
        }

        return layer_vkCreateSwapchainKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateTensorARM = requires(
    VkDevice device, const VkTensorCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorARM* pTensor
) {
    layer_vkCreateTensorARM<T>(device, pCreateInfo, pAllocator, pTensor);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateTensorARM getLayerPtr_vkCreateTensorARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateTensorARM<T>)
        {
            return layer_vkCreateTensorARM<T>;
        }

        return layer_vkCreateTensorARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateTensorViewARM = requires(
    VkDevice device, const VkTensorViewCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorViewARM* pView
) {
    layer_vkCreateTensorViewARM<T>(device, pCreateInfo, pAllocator, pView);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateTensorViewARM getLayerPtr_vkCreateTensorViewARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateTensorViewARM<T>)
        {
            return layer_vkCreateTensorViewARM<T>;
        }

        return layer_vkCreateTensorViewARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateValidationCacheEXT = requires(
    VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache
) {
    layer_vkCreateValidationCacheEXT<T>(device, pCreateInfo, pAllocator, pValidationCache);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateValidationCacheEXT getLayerPtr_vkCreateValidationCacheEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateValidationCacheEXT<T>)
        {
            return layer_vkCreateValidationCacheEXT<T>;
        }

        return layer_vkCreateValidationCacheEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDebugMarkerSetObjectNameEXT = requires(
    VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo
) {
    layer_vkDebugMarkerSetObjectNameEXT<T>(device, pNameInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkDebugMarkerSetObjectNameEXT getLayerPtr_vkDebugMarkerSetObjectNameEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDebugMarkerSetObjectNameEXT<T>)
        {
            return layer_vkDebugMarkerSetObjectNameEXT<T>;
        }

        return layer_vkDebugMarkerSetObjectNameEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDebugMarkerSetObjectTagEXT = requires(
    VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo
) {
    layer_vkDebugMarkerSetObjectTagEXT<T>(device, pTagInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkDebugMarkerSetObjectTagEXT getLayerPtr_vkDebugMarkerSetObjectTagEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDebugMarkerSetObjectTagEXT<T>)
        {
            return layer_vkDebugMarkerSetObjectTagEXT<T>;
        }

        return layer_vkDebugMarkerSetObjectTagEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDeferredOperationJoinKHR = requires(
    VkDevice device, VkDeferredOperationKHR operation
) {
    layer_vkDeferredOperationJoinKHR<T>(device, operation);
};

/* Function pointer resolution. */
constexpr PFN_vkDeferredOperationJoinKHR getLayerPtr_vkDeferredOperationJoinKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDeferredOperationJoinKHR<T>)
        {
            return layer_vkDeferredOperationJoinKHR<T>;
        }

        return layer_vkDeferredOperationJoinKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyAccelerationStructureKHR = requires(
    VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyAccelerationStructureKHR<T>(device, accelerationStructure, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyAccelerationStructureKHR getLayerPtr_vkDestroyAccelerationStructureKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyAccelerationStructureKHR<T>)
        {
            return layer_vkDestroyAccelerationStructureKHR<T>;
        }

        return layer_vkDestroyAccelerationStructureKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyBuffer = requires(
    VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyBuffer<T>(device, buffer, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyBuffer getLayerPtr_vkDestroyBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyBuffer<T>)
        {
            return layer_vkDestroyBuffer<T>;
        }

        return layer_vkDestroyBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyBufferView = requires(
    VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyBufferView<T>(device, bufferView, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyBufferView getLayerPtr_vkDestroyBufferView()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyBufferView<T>)
        {
            return layer_vkDestroyBufferView<T>;
        }

        return layer_vkDestroyBufferView<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyCommandPool = requires(
    VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyCommandPool<T>(device, commandPool, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyCommandPool getLayerPtr_vkDestroyCommandPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyCommandPool<T>)
        {
            return layer_vkDestroyCommandPool<T>;
        }

        return layer_vkDestroyCommandPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDeferredOperationKHR = requires(
    VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDeferredOperationKHR<T>(device, operation, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDeferredOperationKHR getLayerPtr_vkDestroyDeferredOperationKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDeferredOperationKHR<T>)
        {
            return layer_vkDestroyDeferredOperationKHR<T>;
        }

        return layer_vkDestroyDeferredOperationKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDescriptorPool = requires(
    VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorPool<T>(device, descriptorPool, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDescriptorPool getLayerPtr_vkDestroyDescriptorPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDescriptorPool<T>)
        {
            return layer_vkDestroyDescriptorPool<T>;
        }

        return layer_vkDestroyDescriptorPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDescriptorSetLayout = requires(
    VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorSetLayout<T>(device, descriptorSetLayout, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDescriptorSetLayout getLayerPtr_vkDestroyDescriptorSetLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDescriptorSetLayout<T>)
        {
            return layer_vkDestroyDescriptorSetLayout<T>;
        }

        return layer_vkDestroyDescriptorSetLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDescriptorUpdateTemplate = requires(
    VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorUpdateTemplate<T>(device, descriptorUpdateTemplate, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDescriptorUpdateTemplate getLayerPtr_vkDestroyDescriptorUpdateTemplate()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDescriptorUpdateTemplate<T>)
        {
            return layer_vkDestroyDescriptorUpdateTemplate<T>;
        }

        return layer_vkDestroyDescriptorUpdateTemplate<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDescriptorUpdateTemplateKHR = requires(
    VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorUpdateTemplateKHR<T>(device, descriptorUpdateTemplate, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDescriptorUpdateTemplateKHR getLayerPtr_vkDestroyDescriptorUpdateTemplateKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDescriptorUpdateTemplateKHR<T>)
        {
            return layer_vkDestroyDescriptorUpdateTemplateKHR<T>;
        }

        return layer_vkDestroyDescriptorUpdateTemplateKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDevice = requires(
    VkDevice device, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDevice<T>(device, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDevice getLayerPtr_vkDestroyDevice()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDevice<T>)
        {
            return layer_vkDestroyDevice<T>;
        }

        return layer_vkDestroyDevice<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyEvent = requires(
    VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyEvent<T>(device, event, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyEvent getLayerPtr_vkDestroyEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyEvent<T>)
        {
            return layer_vkDestroyEvent<T>;
        }

        return layer_vkDestroyEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyFence = requires(
    VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyFence<T>(device, fence, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyFence getLayerPtr_vkDestroyFence()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyFence<T>)
        {
            return layer_vkDestroyFence<T>;
        }

        return layer_vkDestroyFence<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyFramebuffer = requires(
    VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyFramebuffer<T>(device, framebuffer, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyFramebuffer getLayerPtr_vkDestroyFramebuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyFramebuffer<T>)
        {
            return layer_vkDestroyFramebuffer<T>;
        }

        return layer_vkDestroyFramebuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyImage = requires(
    VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyImage<T>(device, image, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyImage getLayerPtr_vkDestroyImage()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyImage<T>)
        {
            return layer_vkDestroyImage<T>;
        }

        return layer_vkDestroyImage<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyImageView = requires(
    VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyImageView<T>(device, imageView, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyImageView getLayerPtr_vkDestroyImageView()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyImageView<T>)
        {
            return layer_vkDestroyImageView<T>;
        }

        return layer_vkDestroyImageView<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyIndirectCommandsLayoutEXT = requires(
    VkDevice device, VkIndirectCommandsLayoutEXT indirectCommandsLayout, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyIndirectCommandsLayoutEXT<T>(device, indirectCommandsLayout, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyIndirectCommandsLayoutEXT getLayerPtr_vkDestroyIndirectCommandsLayoutEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyIndirectCommandsLayoutEXT<T>)
        {
            return layer_vkDestroyIndirectCommandsLayoutEXT<T>;
        }

        return layer_vkDestroyIndirectCommandsLayoutEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyIndirectExecutionSetEXT = requires(
    VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyIndirectExecutionSetEXT<T>(device, indirectExecutionSet, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyIndirectExecutionSetEXT getLayerPtr_vkDestroyIndirectExecutionSetEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyIndirectExecutionSetEXT<T>)
        {
            return layer_vkDestroyIndirectExecutionSetEXT<T>;
        }

        return layer_vkDestroyIndirectExecutionSetEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyMicromapEXT = requires(
    VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyMicromapEXT<T>(device, micromap, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyMicromapEXT getLayerPtr_vkDestroyMicromapEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyMicromapEXT<T>)
        {
            return layer_vkDestroyMicromapEXT<T>;
        }

        return layer_vkDestroyMicromapEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPipeline = requires(
    VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipeline<T>(device, pipeline, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPipeline getLayerPtr_vkDestroyPipeline()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPipeline<T>)
        {
            return layer_vkDestroyPipeline<T>;
        }

        return layer_vkDestroyPipeline<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPipelineBinaryKHR = requires(
    VkDevice device, VkPipelineBinaryKHR pipelineBinary, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineBinaryKHR<T>(device, pipelineBinary, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPipelineBinaryKHR getLayerPtr_vkDestroyPipelineBinaryKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPipelineBinaryKHR<T>)
        {
            return layer_vkDestroyPipelineBinaryKHR<T>;
        }

        return layer_vkDestroyPipelineBinaryKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPipelineCache = requires(
    VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineCache<T>(device, pipelineCache, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPipelineCache getLayerPtr_vkDestroyPipelineCache()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPipelineCache<T>)
        {
            return layer_vkDestroyPipelineCache<T>;
        }

        return layer_vkDestroyPipelineCache<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPipelineLayout = requires(
    VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineLayout<T>(device, pipelineLayout, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPipelineLayout getLayerPtr_vkDestroyPipelineLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPipelineLayout<T>)
        {
            return layer_vkDestroyPipelineLayout<T>;
        }

        return layer_vkDestroyPipelineLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPrivateDataSlot = requires(
    VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPrivateDataSlot<T>(device, privateDataSlot, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPrivateDataSlot getLayerPtr_vkDestroyPrivateDataSlot()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPrivateDataSlot<T>)
        {
            return layer_vkDestroyPrivateDataSlot<T>;
        }

        return layer_vkDestroyPrivateDataSlot<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyPrivateDataSlotEXT = requires(
    VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPrivateDataSlotEXT<T>(device, privateDataSlot, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyPrivateDataSlotEXT getLayerPtr_vkDestroyPrivateDataSlotEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyPrivateDataSlotEXT<T>)
        {
            return layer_vkDestroyPrivateDataSlotEXT<T>;
        }

        return layer_vkDestroyPrivateDataSlotEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyQueryPool = requires(
    VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyQueryPool<T>(device, queryPool, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyQueryPool getLayerPtr_vkDestroyQueryPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyQueryPool<T>)
        {
            return layer_vkDestroyQueryPool<T>;
        }

        return layer_vkDestroyQueryPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyRenderPass = requires(
    VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyRenderPass<T>(device, renderPass, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyRenderPass getLayerPtr_vkDestroyRenderPass()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyRenderPass<T>)
        {
            return layer_vkDestroyRenderPass<T>;
        }

        return layer_vkDestroyRenderPass<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySampler = requires(
    VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySampler<T>(device, sampler, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySampler getLayerPtr_vkDestroySampler()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySampler<T>)
        {
            return layer_vkDestroySampler<T>;
        }

        return layer_vkDestroySampler<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySamplerYcbcrConversion = requires(
    VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySamplerYcbcrConversion<T>(device, ycbcrConversion, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySamplerYcbcrConversion getLayerPtr_vkDestroySamplerYcbcrConversion()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySamplerYcbcrConversion<T>)
        {
            return layer_vkDestroySamplerYcbcrConversion<T>;
        }

        return layer_vkDestroySamplerYcbcrConversion<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySamplerYcbcrConversionKHR = requires(
    VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySamplerYcbcrConversionKHR<T>(device, ycbcrConversion, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySamplerYcbcrConversionKHR getLayerPtr_vkDestroySamplerYcbcrConversionKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySamplerYcbcrConversionKHR<T>)
        {
            return layer_vkDestroySamplerYcbcrConversionKHR<T>;
        }

        return layer_vkDestroySamplerYcbcrConversionKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySemaphore = requires(
    VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySemaphore<T>(device, semaphore, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySemaphore getLayerPtr_vkDestroySemaphore()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySemaphore<T>)
        {
            return layer_vkDestroySemaphore<T>;
        }

        return layer_vkDestroySemaphore<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyShaderEXT = requires(
    VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyShaderEXT<T>(device, shader, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyShaderEXT getLayerPtr_vkDestroyShaderEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyShaderEXT<T>)
        {
            return layer_vkDestroyShaderEXT<T>;
        }

        return layer_vkDestroyShaderEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyShaderModule = requires(
    VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyShaderModule<T>(device, shaderModule, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyShaderModule getLayerPtr_vkDestroyShaderModule()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyShaderModule<T>)
        {
            return layer_vkDestroyShaderModule<T>;
        }

        return layer_vkDestroyShaderModule<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySwapchainKHR = requires(
    VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySwapchainKHR<T>(device, swapchain, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySwapchainKHR getLayerPtr_vkDestroySwapchainKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySwapchainKHR<T>)
        {
            return layer_vkDestroySwapchainKHR<T>;
        }

        return layer_vkDestroySwapchainKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyTensorARM = requires(
    VkDevice device, VkTensorARM tensor, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyTensorARM<T>(device, tensor, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyTensorARM getLayerPtr_vkDestroyTensorARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyTensorARM<T>)
        {
            return layer_vkDestroyTensorARM<T>;
        }

        return layer_vkDestroyTensorARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyTensorViewARM = requires(
    VkDevice device, VkTensorViewARM tensorView, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyTensorViewARM<T>(device, tensorView, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyTensorViewARM getLayerPtr_vkDestroyTensorViewARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyTensorViewARM<T>)
        {
            return layer_vkDestroyTensorViewARM<T>;
        }

        return layer_vkDestroyTensorViewARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyValidationCacheEXT = requires(
    VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyValidationCacheEXT<T>(device, validationCache, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyValidationCacheEXT getLayerPtr_vkDestroyValidationCacheEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyValidationCacheEXT<T>)
        {
            return layer_vkDestroyValidationCacheEXT<T>;
        }

        return layer_vkDestroyValidationCacheEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDeviceWaitIdle = requires(
    VkDevice device
) {
    layer_vkDeviceWaitIdle<T>(device);
};

/* Function pointer resolution. */
constexpr PFN_vkDeviceWaitIdle getLayerPtr_vkDeviceWaitIdle()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDeviceWaitIdle<T>)
        {
            return layer_vkDeviceWaitIdle<T>;
        }

        return layer_vkDeviceWaitIdle<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDisplayPowerControlEXT = requires(
    VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo
) {
    layer_vkDisplayPowerControlEXT<T>(device, display, pDisplayPowerInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkDisplayPowerControlEXT getLayerPtr_vkDisplayPowerControlEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDisplayPowerControlEXT<T>)
        {
            return layer_vkDisplayPowerControlEXT<T>;
        }

        return layer_vkDisplayPowerControlEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEndCommandBuffer = requires(
    VkCommandBuffer commandBuffer
) {
    layer_vkEndCommandBuffer<T>(commandBuffer);
};

/* Function pointer resolution. */
constexpr PFN_vkEndCommandBuffer getLayerPtr_vkEndCommandBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEndCommandBuffer<T>)
        {
            return layer_vkEndCommandBuffer<T>;
        }

        return layer_vkEndCommandBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkFlushMappedMemoryRanges = requires(
    VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges
) {
    layer_vkFlushMappedMemoryRanges<T>(device, memoryRangeCount, pMemoryRanges);
};

/* Function pointer resolution. */
constexpr PFN_vkFlushMappedMemoryRanges getLayerPtr_vkFlushMappedMemoryRanges()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkFlushMappedMemoryRanges<T>)
        {
            return layer_vkFlushMappedMemoryRanges<T>;
        }

        return layer_vkFlushMappedMemoryRanges<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkFreeCommandBuffers = requires(
    VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers
) {
    layer_vkFreeCommandBuffers<T>(device, commandPool, commandBufferCount, pCommandBuffers);
};

/* Function pointer resolution. */
constexpr PFN_vkFreeCommandBuffers getLayerPtr_vkFreeCommandBuffers()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkFreeCommandBuffers<T>)
        {
            return layer_vkFreeCommandBuffers<T>;
        }

        return layer_vkFreeCommandBuffers<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkFreeDescriptorSets = requires(
    VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets
) {
    layer_vkFreeDescriptorSets<T>(device, descriptorPool, descriptorSetCount, pDescriptorSets);
};

/* Function pointer resolution. */
constexpr PFN_vkFreeDescriptorSets getLayerPtr_vkFreeDescriptorSets()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkFreeDescriptorSets<T>)
        {
            return layer_vkFreeDescriptorSets<T>;
        }

        return layer_vkFreeDescriptorSets<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkFreeMemory = requires(
    VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator
) {
    layer_vkFreeMemory<T>(device, memory, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkFreeMemory getLayerPtr_vkFreeMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkFreeMemory<T>)
        {
            return layer_vkFreeMemory<T>;
        }

        return layer_vkFreeMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetAccelerationStructureBuildSizesKHR = requires(
    VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo
) {
    layer_vkGetAccelerationStructureBuildSizesKHR<T>(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetAccelerationStructureBuildSizesKHR getLayerPtr_vkGetAccelerationStructureBuildSizesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetAccelerationStructureBuildSizesKHR<T>)
        {
            return layer_vkGetAccelerationStructureBuildSizesKHR<T>;
        }

        return layer_vkGetAccelerationStructureBuildSizesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetAccelerationStructureDeviceAddressKHR = requires(
    VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo
) {
    layer_vkGetAccelerationStructureDeviceAddressKHR<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetAccelerationStructureDeviceAddressKHR getLayerPtr_vkGetAccelerationStructureDeviceAddressKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetAccelerationStructureDeviceAddressKHR<T>)
        {
            return layer_vkGetAccelerationStructureDeviceAddressKHR<T>;
        }

        return layer_vkGetAccelerationStructureDeviceAddressKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = requires(
    VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData
) {
    layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT getLayerPtr_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<T>)
        {
            return layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<T>;
        }

        return layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferDeviceAddress = requires(
    VkDevice device, const VkBufferDeviceAddressInfo* pInfo
) {
    layer_vkGetBufferDeviceAddress<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferDeviceAddress getLayerPtr_vkGetBufferDeviceAddress()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferDeviceAddress<T>)
        {
            return layer_vkGetBufferDeviceAddress<T>;
        }

        return layer_vkGetBufferDeviceAddress<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferDeviceAddressEXT = requires(
    VkDevice device, const VkBufferDeviceAddressInfo* pInfo
) {
    layer_vkGetBufferDeviceAddressEXT<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferDeviceAddressEXT getLayerPtr_vkGetBufferDeviceAddressEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferDeviceAddressEXT<T>)
        {
            return layer_vkGetBufferDeviceAddressEXT<T>;
        }

        return layer_vkGetBufferDeviceAddressEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferDeviceAddressKHR = requires(
    VkDevice device, const VkBufferDeviceAddressInfo* pInfo
) {
    layer_vkGetBufferDeviceAddressKHR<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferDeviceAddressKHR getLayerPtr_vkGetBufferDeviceAddressKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferDeviceAddressKHR<T>)
        {
            return layer_vkGetBufferDeviceAddressKHR<T>;
        }

        return layer_vkGetBufferDeviceAddressKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferMemoryRequirements = requires(
    VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements<T>(device, buffer, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferMemoryRequirements getLayerPtr_vkGetBufferMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferMemoryRequirements<T>)
        {
            return layer_vkGetBufferMemoryRequirements<T>;
        }

        return layer_vkGetBufferMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferMemoryRequirements2 = requires(
    VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements2<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferMemoryRequirements2 getLayerPtr_vkGetBufferMemoryRequirements2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferMemoryRequirements2<T>)
        {
            return layer_vkGetBufferMemoryRequirements2<T>;
        }

        return layer_vkGetBufferMemoryRequirements2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferMemoryRequirements2KHR = requires(
    VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements2KHR<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferMemoryRequirements2KHR getLayerPtr_vkGetBufferMemoryRequirements2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferMemoryRequirements2KHR<T>)
        {
            return layer_vkGetBufferMemoryRequirements2KHR<T>;
        }

        return layer_vkGetBufferMemoryRequirements2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferOpaqueCaptureAddress = requires(
    VkDevice device, const VkBufferDeviceAddressInfo* pInfo
) {
    layer_vkGetBufferOpaqueCaptureAddress<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferOpaqueCaptureAddress getLayerPtr_vkGetBufferOpaqueCaptureAddress()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferOpaqueCaptureAddress<T>)
        {
            return layer_vkGetBufferOpaqueCaptureAddress<T>;
        }

        return layer_vkGetBufferOpaqueCaptureAddress<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferOpaqueCaptureAddressKHR = requires(
    VkDevice device, const VkBufferDeviceAddressInfo* pInfo
) {
    layer_vkGetBufferOpaqueCaptureAddressKHR<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferOpaqueCaptureAddressKHR getLayerPtr_vkGetBufferOpaqueCaptureAddressKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferOpaqueCaptureAddressKHR<T>)
        {
            return layer_vkGetBufferOpaqueCaptureAddressKHR<T>;
        }

        return layer_vkGetBufferOpaqueCaptureAddressKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetBufferOpaqueCaptureDescriptorDataEXT = requires(
    VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData
) {
    layer_vkGetBufferOpaqueCaptureDescriptorDataEXT<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT getLayerPtr_vkGetBufferOpaqueCaptureDescriptorDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetBufferOpaqueCaptureDescriptorDataEXT<T>)
        {
            return layer_vkGetBufferOpaqueCaptureDescriptorDataEXT<T>;
        }

        return layer_vkGetBufferOpaqueCaptureDescriptorDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetCalibratedTimestampsEXT = requires(
    VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation
) {
    layer_vkGetCalibratedTimestampsEXT<T>(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
};

/* Function pointer resolution. */
constexpr PFN_vkGetCalibratedTimestampsEXT getLayerPtr_vkGetCalibratedTimestampsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetCalibratedTimestampsEXT<T>)
        {
            return layer_vkGetCalibratedTimestampsEXT<T>;
        }

        return layer_vkGetCalibratedTimestampsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetCalibratedTimestampsKHR = requires(
    VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation
) {
    layer_vkGetCalibratedTimestampsKHR<T>(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
};

/* Function pointer resolution. */
constexpr PFN_vkGetCalibratedTimestampsKHR getLayerPtr_vkGetCalibratedTimestampsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetCalibratedTimestampsKHR<T>)
        {
            return layer_vkGetCalibratedTimestampsKHR<T>;
        }

        return layer_vkGetCalibratedTimestampsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeferredOperationMaxConcurrencyKHR = requires(
    VkDevice device, VkDeferredOperationKHR operation
) {
    layer_vkGetDeferredOperationMaxConcurrencyKHR<T>(device, operation);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeferredOperationMaxConcurrencyKHR getLayerPtr_vkGetDeferredOperationMaxConcurrencyKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeferredOperationMaxConcurrencyKHR<T>)
        {
            return layer_vkGetDeferredOperationMaxConcurrencyKHR<T>;
        }

        return layer_vkGetDeferredOperationMaxConcurrencyKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeferredOperationResultKHR = requires(
    VkDevice device, VkDeferredOperationKHR operation
) {
    layer_vkGetDeferredOperationResultKHR<T>(device, operation);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeferredOperationResultKHR getLayerPtr_vkGetDeferredOperationResultKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeferredOperationResultKHR<T>)
        {
            return layer_vkGetDeferredOperationResultKHR<T>;
        }

        return layer_vkGetDeferredOperationResultKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDescriptorEXT = requires(
    VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor
) {
    layer_vkGetDescriptorEXT<T>(device, pDescriptorInfo, dataSize, pDescriptor);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDescriptorEXT getLayerPtr_vkGetDescriptorEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDescriptorEXT<T>)
        {
            return layer_vkGetDescriptorEXT<T>;
        }

        return layer_vkGetDescriptorEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDescriptorSetLayoutBindingOffsetEXT = requires(
    VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset
) {
    layer_vkGetDescriptorSetLayoutBindingOffsetEXT<T>(device, layout, binding, pOffset);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDescriptorSetLayoutBindingOffsetEXT getLayerPtr_vkGetDescriptorSetLayoutBindingOffsetEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDescriptorSetLayoutBindingOffsetEXT<T>)
        {
            return layer_vkGetDescriptorSetLayoutBindingOffsetEXT<T>;
        }

        return layer_vkGetDescriptorSetLayoutBindingOffsetEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDescriptorSetLayoutSizeEXT = requires(
    VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes
) {
    layer_vkGetDescriptorSetLayoutSizeEXT<T>(device, layout, pLayoutSizeInBytes);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDescriptorSetLayoutSizeEXT getLayerPtr_vkGetDescriptorSetLayoutSizeEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDescriptorSetLayoutSizeEXT<T>)
        {
            return layer_vkGetDescriptorSetLayoutSizeEXT<T>;
        }

        return layer_vkGetDescriptorSetLayoutSizeEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDescriptorSetLayoutSupport = requires(
    VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport
) {
    layer_vkGetDescriptorSetLayoutSupport<T>(device, pCreateInfo, pSupport);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDescriptorSetLayoutSupport getLayerPtr_vkGetDescriptorSetLayoutSupport()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDescriptorSetLayoutSupport<T>)
        {
            return layer_vkGetDescriptorSetLayoutSupport<T>;
        }

        return layer_vkGetDescriptorSetLayoutSupport<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDescriptorSetLayoutSupportKHR = requires(
    VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport
) {
    layer_vkGetDescriptorSetLayoutSupportKHR<T>(device, pCreateInfo, pSupport);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDescriptorSetLayoutSupportKHR getLayerPtr_vkGetDescriptorSetLayoutSupportKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDescriptorSetLayoutSupportKHR<T>)
        {
            return layer_vkGetDescriptorSetLayoutSupportKHR<T>;
        }

        return layer_vkGetDescriptorSetLayoutSupportKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceAccelerationStructureCompatibilityKHR = requires(
    VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    layer_vkGetDeviceAccelerationStructureCompatibilityKHR<T>(device, pVersionInfo, pCompatibility);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceAccelerationStructureCompatibilityKHR getLayerPtr_vkGetDeviceAccelerationStructureCompatibilityKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceAccelerationStructureCompatibilityKHR<T>)
        {
            return layer_vkGetDeviceAccelerationStructureCompatibilityKHR<T>;
        }

        return layer_vkGetDeviceAccelerationStructureCompatibilityKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceBufferMemoryRequirements = requires(
    VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceBufferMemoryRequirements<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceBufferMemoryRequirements getLayerPtr_vkGetDeviceBufferMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceBufferMemoryRequirements<T>)
        {
            return layer_vkGetDeviceBufferMemoryRequirements<T>;
        }

        return layer_vkGetDeviceBufferMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceBufferMemoryRequirementsKHR = requires(
    VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceBufferMemoryRequirementsKHR<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceBufferMemoryRequirementsKHR getLayerPtr_vkGetDeviceBufferMemoryRequirementsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceBufferMemoryRequirementsKHR<T>)
        {
            return layer_vkGetDeviceBufferMemoryRequirementsKHR<T>;
        }

        return layer_vkGetDeviceBufferMemoryRequirementsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceFaultInfoEXT = requires(
    VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo
) {
    layer_vkGetDeviceFaultInfoEXT<T>(device, pFaultCounts, pFaultInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceFaultInfoEXT getLayerPtr_vkGetDeviceFaultInfoEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceFaultInfoEXT<T>)
        {
            return layer_vkGetDeviceFaultInfoEXT<T>;
        }

        return layer_vkGetDeviceFaultInfoEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceGroupPeerMemoryFeatures = requires(
    VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    layer_vkGetDeviceGroupPeerMemoryFeatures<T>(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceGroupPeerMemoryFeatures getLayerPtr_vkGetDeviceGroupPeerMemoryFeatures()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceGroupPeerMemoryFeatures<T>)
        {
            return layer_vkGetDeviceGroupPeerMemoryFeatures<T>;
        }

        return layer_vkGetDeviceGroupPeerMemoryFeatures<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceGroupPeerMemoryFeaturesKHR = requires(
    VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    layer_vkGetDeviceGroupPeerMemoryFeaturesKHR<T>(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR getLayerPtr_vkGetDeviceGroupPeerMemoryFeaturesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceGroupPeerMemoryFeaturesKHR<T>)
        {
            return layer_vkGetDeviceGroupPeerMemoryFeaturesKHR<T>;
        }

        return layer_vkGetDeviceGroupPeerMemoryFeaturesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceGroupPresentCapabilitiesKHR = requires(
    VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities
) {
    layer_vkGetDeviceGroupPresentCapabilitiesKHR<T>(device, pDeviceGroupPresentCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceGroupPresentCapabilitiesKHR getLayerPtr_vkGetDeviceGroupPresentCapabilitiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceGroupPresentCapabilitiesKHR<T>)
        {
            return layer_vkGetDeviceGroupPresentCapabilitiesKHR<T>;
        }

        return layer_vkGetDeviceGroupPresentCapabilitiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceGroupSurfacePresentModesKHR = requires(
    VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes
) {
    layer_vkGetDeviceGroupSurfacePresentModesKHR<T>(device, surface, pModes);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceGroupSurfacePresentModesKHR getLayerPtr_vkGetDeviceGroupSurfacePresentModesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceGroupSurfacePresentModesKHR<T>)
        {
            return layer_vkGetDeviceGroupSurfacePresentModesKHR<T>;
        }

        return layer_vkGetDeviceGroupSurfacePresentModesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageMemoryRequirements = requires(
    VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceImageMemoryRequirements<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageMemoryRequirements getLayerPtr_vkGetDeviceImageMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageMemoryRequirements<T>)
        {
            return layer_vkGetDeviceImageMemoryRequirements<T>;
        }

        return layer_vkGetDeviceImageMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageMemoryRequirementsKHR = requires(
    VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceImageMemoryRequirementsKHR<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageMemoryRequirementsKHR getLayerPtr_vkGetDeviceImageMemoryRequirementsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageMemoryRequirementsKHR<T>)
        {
            return layer_vkGetDeviceImageMemoryRequirementsKHR<T>;
        }

        return layer_vkGetDeviceImageMemoryRequirementsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageSparseMemoryRequirements = requires(
    VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetDeviceImageSparseMemoryRequirements<T>(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageSparseMemoryRequirements getLayerPtr_vkGetDeviceImageSparseMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageSparseMemoryRequirements<T>)
        {
            return layer_vkGetDeviceImageSparseMemoryRequirements<T>;
        }

        return layer_vkGetDeviceImageSparseMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageSparseMemoryRequirementsKHR = requires(
    VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetDeviceImageSparseMemoryRequirementsKHR<T>(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageSparseMemoryRequirementsKHR getLayerPtr_vkGetDeviceImageSparseMemoryRequirementsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageSparseMemoryRequirementsKHR<T>)
        {
            return layer_vkGetDeviceImageSparseMemoryRequirementsKHR<T>;
        }

        return layer_vkGetDeviceImageSparseMemoryRequirementsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageSubresourceLayout = requires(
    VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout
) {
    layer_vkGetDeviceImageSubresourceLayout<T>(device, pInfo, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageSubresourceLayout getLayerPtr_vkGetDeviceImageSubresourceLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageSubresourceLayout<T>)
        {
            return layer_vkGetDeviceImageSubresourceLayout<T>;
        }

        return layer_vkGetDeviceImageSubresourceLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceImageSubresourceLayoutKHR = requires(
    VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout
) {
    layer_vkGetDeviceImageSubresourceLayoutKHR<T>(device, pInfo, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceImageSubresourceLayoutKHR getLayerPtr_vkGetDeviceImageSubresourceLayoutKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceImageSubresourceLayoutKHR<T>)
        {
            return layer_vkGetDeviceImageSubresourceLayoutKHR<T>;
        }

        return layer_vkGetDeviceImageSubresourceLayoutKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceMemoryCommitment = requires(
    VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes
) {
    layer_vkGetDeviceMemoryCommitment<T>(device, memory, pCommittedMemoryInBytes);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceMemoryCommitment getLayerPtr_vkGetDeviceMemoryCommitment()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceMemoryCommitment<T>)
        {
            return layer_vkGetDeviceMemoryCommitment<T>;
        }

        return layer_vkGetDeviceMemoryCommitment<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddress = requires(
    VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    layer_vkGetDeviceMemoryOpaqueCaptureAddress<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceMemoryOpaqueCaptureAddress getLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddress()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddress<T>)
        {
            return layer_vkGetDeviceMemoryOpaqueCaptureAddress<T>;
        }

        return layer_vkGetDeviceMemoryOpaqueCaptureAddress<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddressKHR = requires(
    VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR<T>(device, pInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR getLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddressKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceMemoryOpaqueCaptureAddressKHR<T>)
        {
            return layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR<T>;
        }

        return layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceMicromapCompatibilityEXT = requires(
    VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    layer_vkGetDeviceMicromapCompatibilityEXT<T>(device, pVersionInfo, pCompatibility);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceMicromapCompatibilityEXT getLayerPtr_vkGetDeviceMicromapCompatibilityEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceMicromapCompatibilityEXT<T>)
        {
            return layer_vkGetDeviceMicromapCompatibilityEXT<T>;
        }

        return layer_vkGetDeviceMicromapCompatibilityEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceProcAddr = requires(
    VkDevice device, const char* pName
) {
    layer_vkGetDeviceProcAddr<T>(device, pName);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceProcAddr getLayerPtr_vkGetDeviceProcAddr()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceProcAddr<T>)
        {
            return layer_vkGetDeviceProcAddr<T>;
        }

        return layer_vkGetDeviceProcAddr<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceQueue = requires(
    VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue
) {
    layer_vkGetDeviceQueue<T>(device, queueFamilyIndex, queueIndex, pQueue);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceQueue getLayerPtr_vkGetDeviceQueue()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceQueue<T>)
        {
            return layer_vkGetDeviceQueue<T>;
        }

        return layer_vkGetDeviceQueue<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceQueue2 = requires(
    VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue
) {
    layer_vkGetDeviceQueue2<T>(device, pQueueInfo, pQueue);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceQueue2 getLayerPtr_vkGetDeviceQueue2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceQueue2<T>)
        {
            return layer_vkGetDeviceQueue2<T>;
        }

        return layer_vkGetDeviceQueue2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDeviceTensorMemoryRequirementsARM = requires(
    VkDevice device, const VkDeviceTensorMemoryRequirementsARM* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceTensorMemoryRequirementsARM<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDeviceTensorMemoryRequirementsARM getLayerPtr_vkGetDeviceTensorMemoryRequirementsARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDeviceTensorMemoryRequirementsARM<T>)
        {
            return layer_vkGetDeviceTensorMemoryRequirementsARM<T>;
        }

        return layer_vkGetDeviceTensorMemoryRequirementsARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetEventStatus = requires(
    VkDevice device, VkEvent event
) {
    layer_vkGetEventStatus<T>(device, event);
};

/* Function pointer resolution. */
constexpr PFN_vkGetEventStatus getLayerPtr_vkGetEventStatus()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetEventStatus<T>)
        {
            return layer_vkGetEventStatus<T>;
        }

        return layer_vkGetEventStatus<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetFenceFdKHR = requires(
    VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd
) {
    layer_vkGetFenceFdKHR<T>(device, pGetFdInfo, pFd);
};

/* Function pointer resolution. */
constexpr PFN_vkGetFenceFdKHR getLayerPtr_vkGetFenceFdKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetFenceFdKHR<T>)
        {
            return layer_vkGetFenceFdKHR<T>;
        }

        return layer_vkGetFenceFdKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetFenceStatus = requires(
    VkDevice device, VkFence fence
) {
    layer_vkGetFenceStatus<T>(device, fence);
};

/* Function pointer resolution. */
constexpr PFN_vkGetFenceStatus getLayerPtr_vkGetFenceStatus()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetFenceStatus<T>)
        {
            return layer_vkGetFenceStatus<T>;
        }

        return layer_vkGetFenceStatus<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetGeneratedCommandsMemoryRequirementsEXT = requires(
    VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetGeneratedCommandsMemoryRequirementsEXT<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetGeneratedCommandsMemoryRequirementsEXT getLayerPtr_vkGetGeneratedCommandsMemoryRequirementsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetGeneratedCommandsMemoryRequirementsEXT<T>)
        {
            return layer_vkGetGeneratedCommandsMemoryRequirementsEXT<T>;
        }

        return layer_vkGetGeneratedCommandsMemoryRequirementsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageDrmFormatModifierPropertiesEXT = requires(
    VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties
) {
    layer_vkGetImageDrmFormatModifierPropertiesEXT<T>(device, image, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageDrmFormatModifierPropertiesEXT getLayerPtr_vkGetImageDrmFormatModifierPropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageDrmFormatModifierPropertiesEXT<T>)
        {
            return layer_vkGetImageDrmFormatModifierPropertiesEXT<T>;
        }

        return layer_vkGetImageDrmFormatModifierPropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageMemoryRequirements = requires(
    VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements<T>(device, image, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageMemoryRequirements getLayerPtr_vkGetImageMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageMemoryRequirements<T>)
        {
            return layer_vkGetImageMemoryRequirements<T>;
        }

        return layer_vkGetImageMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageMemoryRequirements2 = requires(
    VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements2<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageMemoryRequirements2 getLayerPtr_vkGetImageMemoryRequirements2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageMemoryRequirements2<T>)
        {
            return layer_vkGetImageMemoryRequirements2<T>;
        }

        return layer_vkGetImageMemoryRequirements2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageMemoryRequirements2KHR = requires(
    VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements2KHR<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageMemoryRequirements2KHR getLayerPtr_vkGetImageMemoryRequirements2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageMemoryRequirements2KHR<T>)
        {
            return layer_vkGetImageMemoryRequirements2KHR<T>;
        }

        return layer_vkGetImageMemoryRequirements2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageOpaqueCaptureDescriptorDataEXT = requires(
    VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData
) {
    layer_vkGetImageOpaqueCaptureDescriptorDataEXT<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageOpaqueCaptureDescriptorDataEXT getLayerPtr_vkGetImageOpaqueCaptureDescriptorDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageOpaqueCaptureDescriptorDataEXT<T>)
        {
            return layer_vkGetImageOpaqueCaptureDescriptorDataEXT<T>;
        }

        return layer_vkGetImageOpaqueCaptureDescriptorDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSparseMemoryRequirements = requires(
    VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements<T>(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSparseMemoryRequirements getLayerPtr_vkGetImageSparseMemoryRequirements()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSparseMemoryRequirements<T>)
        {
            return layer_vkGetImageSparseMemoryRequirements<T>;
        }

        return layer_vkGetImageSparseMemoryRequirements<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSparseMemoryRequirements2 = requires(
    VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements2<T>(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSparseMemoryRequirements2 getLayerPtr_vkGetImageSparseMemoryRequirements2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSparseMemoryRequirements2<T>)
        {
            return layer_vkGetImageSparseMemoryRequirements2<T>;
        }

        return layer_vkGetImageSparseMemoryRequirements2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSparseMemoryRequirements2KHR = requires(
    VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements2KHR<T>(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSparseMemoryRequirements2KHR getLayerPtr_vkGetImageSparseMemoryRequirements2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSparseMemoryRequirements2KHR<T>)
        {
            return layer_vkGetImageSparseMemoryRequirements2KHR<T>;
        }

        return layer_vkGetImageSparseMemoryRequirements2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSubresourceLayout = requires(
    VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout
) {
    layer_vkGetImageSubresourceLayout<T>(device, image, pSubresource, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSubresourceLayout getLayerPtr_vkGetImageSubresourceLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSubresourceLayout<T>)
        {
            return layer_vkGetImageSubresourceLayout<T>;
        }

        return layer_vkGetImageSubresourceLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSubresourceLayout2 = requires(
    VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2<T>(device, image, pSubresource, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSubresourceLayout2 getLayerPtr_vkGetImageSubresourceLayout2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSubresourceLayout2<T>)
        {
            return layer_vkGetImageSubresourceLayout2<T>;
        }

        return layer_vkGetImageSubresourceLayout2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSubresourceLayout2EXT = requires(
    VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2EXT<T>(device, image, pSubresource, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSubresourceLayout2EXT getLayerPtr_vkGetImageSubresourceLayout2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSubresourceLayout2EXT<T>)
        {
            return layer_vkGetImageSubresourceLayout2EXT<T>;
        }

        return layer_vkGetImageSubresourceLayout2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageSubresourceLayout2KHR = requires(
    VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2KHR<T>(device, image, pSubresource, pLayout);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageSubresourceLayout2KHR getLayerPtr_vkGetImageSubresourceLayout2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageSubresourceLayout2KHR<T>)
        {
            return layer_vkGetImageSubresourceLayout2KHR<T>;
        }

        return layer_vkGetImageSubresourceLayout2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetImageViewOpaqueCaptureDescriptorDataEXT = requires(
    VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData
) {
    layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT getLayerPtr_vkGetImageViewOpaqueCaptureDescriptorDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetImageViewOpaqueCaptureDescriptorDataEXT<T>)
        {
            return layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT<T>;
        }

        return layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetMemoryFdKHR = requires(
    VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd
) {
    layer_vkGetMemoryFdKHR<T>(device, pGetFdInfo, pFd);
};

/* Function pointer resolution. */
constexpr PFN_vkGetMemoryFdKHR getLayerPtr_vkGetMemoryFdKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetMemoryFdKHR<T>)
        {
            return layer_vkGetMemoryFdKHR<T>;
        }

        return layer_vkGetMemoryFdKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetMemoryFdPropertiesKHR = requires(
    VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties
) {
    layer_vkGetMemoryFdPropertiesKHR<T>(device, handleType, fd, pMemoryFdProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetMemoryFdPropertiesKHR getLayerPtr_vkGetMemoryFdPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetMemoryFdPropertiesKHR<T>)
        {
            return layer_vkGetMemoryFdPropertiesKHR<T>;
        }

        return layer_vkGetMemoryFdPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetMemoryHostPointerPropertiesEXT = requires(
    VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties
) {
    layer_vkGetMemoryHostPointerPropertiesEXT<T>(device, handleType, pHostPointer, pMemoryHostPointerProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetMemoryHostPointerPropertiesEXT getLayerPtr_vkGetMemoryHostPointerPropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetMemoryHostPointerPropertiesEXT<T>)
        {
            return layer_vkGetMemoryHostPointerPropertiesEXT<T>;
        }

        return layer_vkGetMemoryHostPointerPropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetMicromapBuildSizesEXT = requires(
    VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo
) {
    layer_vkGetMicromapBuildSizesEXT<T>(device, buildType, pBuildInfo, pSizeInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkGetMicromapBuildSizesEXT getLayerPtr_vkGetMicromapBuildSizesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetMicromapBuildSizesEXT<T>)
        {
            return layer_vkGetMicromapBuildSizesEXT<T>;
        }

        return layer_vkGetMicromapBuildSizesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineBinaryDataKHR = requires(
    VkDevice device, const VkPipelineBinaryDataInfoKHR* pInfo, VkPipelineBinaryKeyKHR* pPipelineBinaryKey, size_t* pPipelineBinaryDataSize, void* pPipelineBinaryData
) {
    layer_vkGetPipelineBinaryDataKHR<T>(device, pInfo, pPipelineBinaryKey, pPipelineBinaryDataSize, pPipelineBinaryData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineBinaryDataKHR getLayerPtr_vkGetPipelineBinaryDataKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineBinaryDataKHR<T>)
        {
            return layer_vkGetPipelineBinaryDataKHR<T>;
        }

        return layer_vkGetPipelineBinaryDataKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineCacheData = requires(
    VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData
) {
    layer_vkGetPipelineCacheData<T>(device, pipelineCache, pDataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineCacheData getLayerPtr_vkGetPipelineCacheData()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineCacheData<T>)
        {
            return layer_vkGetPipelineCacheData<T>;
        }

        return layer_vkGetPipelineCacheData<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineExecutableInternalRepresentationsKHR = requires(
    VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations
) {
    layer_vkGetPipelineExecutableInternalRepresentationsKHR<T>(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineExecutableInternalRepresentationsKHR getLayerPtr_vkGetPipelineExecutableInternalRepresentationsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineExecutableInternalRepresentationsKHR<T>)
        {
            return layer_vkGetPipelineExecutableInternalRepresentationsKHR<T>;
        }

        return layer_vkGetPipelineExecutableInternalRepresentationsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineExecutablePropertiesKHR = requires(
    VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties
) {
    layer_vkGetPipelineExecutablePropertiesKHR<T>(device, pPipelineInfo, pExecutableCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineExecutablePropertiesKHR getLayerPtr_vkGetPipelineExecutablePropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineExecutablePropertiesKHR<T>)
        {
            return layer_vkGetPipelineExecutablePropertiesKHR<T>;
        }

        return layer_vkGetPipelineExecutablePropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineExecutableStatisticsKHR = requires(
    VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics
) {
    layer_vkGetPipelineExecutableStatisticsKHR<T>(device, pExecutableInfo, pStatisticCount, pStatistics);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineExecutableStatisticsKHR getLayerPtr_vkGetPipelineExecutableStatisticsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineExecutableStatisticsKHR<T>)
        {
            return layer_vkGetPipelineExecutableStatisticsKHR<T>;
        }

        return layer_vkGetPipelineExecutableStatisticsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelineKeyKHR = requires(
    VkDevice device, const VkPipelineCreateInfoKHR* pPipelineCreateInfo, VkPipelineBinaryKeyKHR* pPipelineKey
) {
    layer_vkGetPipelineKeyKHR<T>(device, pPipelineCreateInfo, pPipelineKey);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelineKeyKHR getLayerPtr_vkGetPipelineKeyKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelineKeyKHR<T>)
        {
            return layer_vkGetPipelineKeyKHR<T>;
        }

        return layer_vkGetPipelineKeyKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPipelinePropertiesEXT = requires(
    VkDevice device, const VkPipelineInfoEXT* pPipelineInfo, VkBaseOutStructure* pPipelineProperties
) {
    layer_vkGetPipelinePropertiesEXT<T>(device, pPipelineInfo, pPipelineProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPipelinePropertiesEXT getLayerPtr_vkGetPipelinePropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPipelinePropertiesEXT<T>)
        {
            return layer_vkGetPipelinePropertiesEXT<T>;
        }

        return layer_vkGetPipelinePropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPrivateData = requires(
    VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData
) {
    layer_vkGetPrivateData<T>(device, objectType, objectHandle, privateDataSlot, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPrivateData getLayerPtr_vkGetPrivateData()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPrivateData<T>)
        {
            return layer_vkGetPrivateData<T>;
        }

        return layer_vkGetPrivateData<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPrivateDataEXT = requires(
    VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData
) {
    layer_vkGetPrivateDataEXT<T>(device, objectType, objectHandle, privateDataSlot, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPrivateDataEXT getLayerPtr_vkGetPrivateDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPrivateDataEXT<T>)
        {
            return layer_vkGetPrivateDataEXT<T>;
        }

        return layer_vkGetPrivateDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetQueryPoolResults = requires(
    VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags
) {
    layer_vkGetQueryPoolResults<T>(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkGetQueryPoolResults getLayerPtr_vkGetQueryPoolResults()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetQueryPoolResults<T>)
        {
            return layer_vkGetQueryPoolResults<T>;
        }

        return layer_vkGetQueryPoolResults<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = requires(
    VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData
) {
    layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<T>(device, pipeline, firstGroup, groupCount, dataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR getLayerPtr_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<T>)
        {
            return layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<T>;
        }

        return layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRayTracingShaderGroupHandlesKHR = requires(
    VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData
) {
    layer_vkGetRayTracingShaderGroupHandlesKHR<T>(device, pipeline, firstGroup, groupCount, dataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRayTracingShaderGroupHandlesKHR getLayerPtr_vkGetRayTracingShaderGroupHandlesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRayTracingShaderGroupHandlesKHR<T>)
        {
            return layer_vkGetRayTracingShaderGroupHandlesKHR<T>;
        }

        return layer_vkGetRayTracingShaderGroupHandlesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRayTracingShaderGroupStackSizeKHR = requires(
    VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader
) {
    layer_vkGetRayTracingShaderGroupStackSizeKHR<T>(device, pipeline, group, groupShader);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRayTracingShaderGroupStackSizeKHR getLayerPtr_vkGetRayTracingShaderGroupStackSizeKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRayTracingShaderGroupStackSizeKHR<T>)
        {
            return layer_vkGetRayTracingShaderGroupStackSizeKHR<T>;
        }

        return layer_vkGetRayTracingShaderGroupStackSizeKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRenderAreaGranularity = requires(
    VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity
) {
    layer_vkGetRenderAreaGranularity<T>(device, renderPass, pGranularity);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRenderAreaGranularity getLayerPtr_vkGetRenderAreaGranularity()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRenderAreaGranularity<T>)
        {
            return layer_vkGetRenderAreaGranularity<T>;
        }

        return layer_vkGetRenderAreaGranularity<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRenderingAreaGranularity = requires(
    VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity
) {
    layer_vkGetRenderingAreaGranularity<T>(device, pRenderingAreaInfo, pGranularity);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRenderingAreaGranularity getLayerPtr_vkGetRenderingAreaGranularity()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRenderingAreaGranularity<T>)
        {
            return layer_vkGetRenderingAreaGranularity<T>;
        }

        return layer_vkGetRenderingAreaGranularity<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetRenderingAreaGranularityKHR = requires(
    VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity
) {
    layer_vkGetRenderingAreaGranularityKHR<T>(device, pRenderingAreaInfo, pGranularity);
};

/* Function pointer resolution. */
constexpr PFN_vkGetRenderingAreaGranularityKHR getLayerPtr_vkGetRenderingAreaGranularityKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetRenderingAreaGranularityKHR<T>)
        {
            return layer_vkGetRenderingAreaGranularityKHR<T>;
        }

        return layer_vkGetRenderingAreaGranularityKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSamplerOpaqueCaptureDescriptorDataEXT = requires(
    VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData
) {
    layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT getLayerPtr_vkGetSamplerOpaqueCaptureDescriptorDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSamplerOpaqueCaptureDescriptorDataEXT<T>)
        {
            return layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT<T>;
        }

        return layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSemaphoreCounterValue = requires(
    VkDevice device, VkSemaphore semaphore, uint64_t* pValue
) {
    layer_vkGetSemaphoreCounterValue<T>(device, semaphore, pValue);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSemaphoreCounterValue getLayerPtr_vkGetSemaphoreCounterValue()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSemaphoreCounterValue<T>)
        {
            return layer_vkGetSemaphoreCounterValue<T>;
        }

        return layer_vkGetSemaphoreCounterValue<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSemaphoreCounterValueKHR = requires(
    VkDevice device, VkSemaphore semaphore, uint64_t* pValue
) {
    layer_vkGetSemaphoreCounterValueKHR<T>(device, semaphore, pValue);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSemaphoreCounterValueKHR getLayerPtr_vkGetSemaphoreCounterValueKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSemaphoreCounterValueKHR<T>)
        {
            return layer_vkGetSemaphoreCounterValueKHR<T>;
        }

        return layer_vkGetSemaphoreCounterValueKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSemaphoreFdKHR = requires(
    VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd
) {
    layer_vkGetSemaphoreFdKHR<T>(device, pGetFdInfo, pFd);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSemaphoreFdKHR getLayerPtr_vkGetSemaphoreFdKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSemaphoreFdKHR<T>)
        {
            return layer_vkGetSemaphoreFdKHR<T>;
        }

        return layer_vkGetSemaphoreFdKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetShaderBinaryDataEXT = requires(
    VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData
) {
    layer_vkGetShaderBinaryDataEXT<T>(device, shader, pDataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetShaderBinaryDataEXT getLayerPtr_vkGetShaderBinaryDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetShaderBinaryDataEXT<T>)
        {
            return layer_vkGetShaderBinaryDataEXT<T>;
        }

        return layer_vkGetShaderBinaryDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetShaderModuleCreateInfoIdentifierEXT = requires(
    VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier
) {
    layer_vkGetShaderModuleCreateInfoIdentifierEXT<T>(device, pCreateInfo, pIdentifier);
};

/* Function pointer resolution. */
constexpr PFN_vkGetShaderModuleCreateInfoIdentifierEXT getLayerPtr_vkGetShaderModuleCreateInfoIdentifierEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetShaderModuleCreateInfoIdentifierEXT<T>)
        {
            return layer_vkGetShaderModuleCreateInfoIdentifierEXT<T>;
        }

        return layer_vkGetShaderModuleCreateInfoIdentifierEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetShaderModuleIdentifierEXT = requires(
    VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier
) {
    layer_vkGetShaderModuleIdentifierEXT<T>(device, shaderModule, pIdentifier);
};

/* Function pointer resolution. */
constexpr PFN_vkGetShaderModuleIdentifierEXT getLayerPtr_vkGetShaderModuleIdentifierEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetShaderModuleIdentifierEXT<T>)
        {
            return layer_vkGetShaderModuleIdentifierEXT<T>;
        }

        return layer_vkGetShaderModuleIdentifierEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSwapchainCounterEXT = requires(
    VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue
) {
    layer_vkGetSwapchainCounterEXT<T>(device, swapchain, counter, pCounterValue);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSwapchainCounterEXT getLayerPtr_vkGetSwapchainCounterEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSwapchainCounterEXT<T>)
        {
            return layer_vkGetSwapchainCounterEXT<T>;
        }

        return layer_vkGetSwapchainCounterEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSwapchainImagesKHR = requires(
    VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages
) {
    layer_vkGetSwapchainImagesKHR<T>(device, swapchain, pSwapchainImageCount, pSwapchainImages);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSwapchainImagesKHR getLayerPtr_vkGetSwapchainImagesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSwapchainImagesKHR<T>)
        {
            return layer_vkGetSwapchainImagesKHR<T>;
        }

        return layer_vkGetSwapchainImagesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetSwapchainStatusKHR = requires(
    VkDevice device, VkSwapchainKHR swapchain
) {
    layer_vkGetSwapchainStatusKHR<T>(device, swapchain);
};

/* Function pointer resolution. */
constexpr PFN_vkGetSwapchainStatusKHR getLayerPtr_vkGetSwapchainStatusKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetSwapchainStatusKHR<T>)
        {
            return layer_vkGetSwapchainStatusKHR<T>;
        }

        return layer_vkGetSwapchainStatusKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetTensorMemoryRequirementsARM = requires(
    VkDevice device, const VkTensorMemoryRequirementsInfoARM* pInfo, VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetTensorMemoryRequirementsARM<T>(device, pInfo, pMemoryRequirements);
};

/* Function pointer resolution. */
constexpr PFN_vkGetTensorMemoryRequirementsARM getLayerPtr_vkGetTensorMemoryRequirementsARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetTensorMemoryRequirementsARM<T>)
        {
            return layer_vkGetTensorMemoryRequirementsARM<T>;
        }

        return layer_vkGetTensorMemoryRequirementsARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetTensorOpaqueCaptureDescriptorDataARM = requires(
    VkDevice device, const VkTensorCaptureDescriptorDataInfoARM* pInfo, void* pData
) {
    layer_vkGetTensorOpaqueCaptureDescriptorDataARM<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetTensorOpaqueCaptureDescriptorDataARM getLayerPtr_vkGetTensorOpaqueCaptureDescriptorDataARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetTensorOpaqueCaptureDescriptorDataARM<T>)
        {
            return layer_vkGetTensorOpaqueCaptureDescriptorDataARM<T>;
        }

        return layer_vkGetTensorOpaqueCaptureDescriptorDataARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetTensorViewOpaqueCaptureDescriptorDataARM = requires(
    VkDevice device, const VkTensorViewCaptureDescriptorDataInfoARM* pInfo, void* pData
) {
    layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM<T>(device, pInfo, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetTensorViewOpaqueCaptureDescriptorDataARM getLayerPtr_vkGetTensorViewOpaqueCaptureDescriptorDataARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetTensorViewOpaqueCaptureDescriptorDataARM<T>)
        {
            return layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM<T>;
        }

        return layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetValidationCacheDataEXT = requires(
    VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData
) {
    layer_vkGetValidationCacheDataEXT<T>(device, validationCache, pDataSize, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkGetValidationCacheDataEXT getLayerPtr_vkGetValidationCacheDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetValidationCacheDataEXT<T>)
        {
            return layer_vkGetValidationCacheDataEXT<T>;
        }

        return layer_vkGetValidationCacheDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkImportFenceFdKHR = requires(
    VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo
) {
    layer_vkImportFenceFdKHR<T>(device, pImportFenceFdInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkImportFenceFdKHR getLayerPtr_vkImportFenceFdKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkImportFenceFdKHR<T>)
        {
            return layer_vkImportFenceFdKHR<T>;
        }

        return layer_vkImportFenceFdKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkImportSemaphoreFdKHR = requires(
    VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo
) {
    layer_vkImportSemaphoreFdKHR<T>(device, pImportSemaphoreFdInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkImportSemaphoreFdKHR getLayerPtr_vkImportSemaphoreFdKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkImportSemaphoreFdKHR<T>)
        {
            return layer_vkImportSemaphoreFdKHR<T>;
        }

        return layer_vkImportSemaphoreFdKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkInvalidateMappedMemoryRanges = requires(
    VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges
) {
    layer_vkInvalidateMappedMemoryRanges<T>(device, memoryRangeCount, pMemoryRanges);
};

/* Function pointer resolution. */
constexpr PFN_vkInvalidateMappedMemoryRanges getLayerPtr_vkInvalidateMappedMemoryRanges()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkInvalidateMappedMemoryRanges<T>)
        {
            return layer_vkInvalidateMappedMemoryRanges<T>;
        }

        return layer_vkInvalidateMappedMemoryRanges<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkMapMemory = requires(
    VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData
) {
    layer_vkMapMemory<T>(device, memory, offset, size, flags, ppData);
};

/* Function pointer resolution. */
constexpr PFN_vkMapMemory getLayerPtr_vkMapMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkMapMemory<T>)
        {
            return layer_vkMapMemory<T>;
        }

        return layer_vkMapMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkMapMemory2 = requires(
    VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData
) {
    layer_vkMapMemory2<T>(device, pMemoryMapInfo, ppData);
};

/* Function pointer resolution. */
constexpr PFN_vkMapMemory2 getLayerPtr_vkMapMemory2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkMapMemory2<T>)
        {
            return layer_vkMapMemory2<T>;
        }

        return layer_vkMapMemory2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkMapMemory2KHR = requires(
    VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData
) {
    layer_vkMapMemory2KHR<T>(device, pMemoryMapInfo, ppData);
};

/* Function pointer resolution. */
constexpr PFN_vkMapMemory2KHR getLayerPtr_vkMapMemory2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkMapMemory2KHR<T>)
        {
            return layer_vkMapMemory2KHR<T>;
        }

        return layer_vkMapMemory2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkMergePipelineCaches = requires(
    VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches
) {
    layer_vkMergePipelineCaches<T>(device, dstCache, srcCacheCount, pSrcCaches);
};

/* Function pointer resolution. */
constexpr PFN_vkMergePipelineCaches getLayerPtr_vkMergePipelineCaches()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkMergePipelineCaches<T>)
        {
            return layer_vkMergePipelineCaches<T>;
        }

        return layer_vkMergePipelineCaches<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkMergeValidationCachesEXT = requires(
    VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches
) {
    layer_vkMergeValidationCachesEXT<T>(device, dstCache, srcCacheCount, pSrcCaches);
};

/* Function pointer resolution. */
constexpr PFN_vkMergeValidationCachesEXT getLayerPtr_vkMergeValidationCachesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkMergeValidationCachesEXT<T>)
        {
            return layer_vkMergeValidationCachesEXT<T>;
        }

        return layer_vkMergeValidationCachesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueBeginDebugUtilsLabelEXT = requires(
    VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkQueueBeginDebugUtilsLabelEXT<T>(queue, pLabelInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueBeginDebugUtilsLabelEXT getLayerPtr_vkQueueBeginDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueBeginDebugUtilsLabelEXT<T>)
        {
            return layer_vkQueueBeginDebugUtilsLabelEXT<T>;
        }

        return layer_vkQueueBeginDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueBindSparse = requires(
    VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence
) {
    layer_vkQueueBindSparse<T>(queue, bindInfoCount, pBindInfo, fence);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueBindSparse getLayerPtr_vkQueueBindSparse()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueBindSparse<T>)
        {
            return layer_vkQueueBindSparse<T>;
        }

        return layer_vkQueueBindSparse<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueEndDebugUtilsLabelEXT = requires(
    VkQueue queue
) {
    layer_vkQueueEndDebugUtilsLabelEXT<T>(queue);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueEndDebugUtilsLabelEXT getLayerPtr_vkQueueEndDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueEndDebugUtilsLabelEXT<T>)
        {
            return layer_vkQueueEndDebugUtilsLabelEXT<T>;
        }

        return layer_vkQueueEndDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueInsertDebugUtilsLabelEXT = requires(
    VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkQueueInsertDebugUtilsLabelEXT<T>(queue, pLabelInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueInsertDebugUtilsLabelEXT getLayerPtr_vkQueueInsertDebugUtilsLabelEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueInsertDebugUtilsLabelEXT<T>)
        {
            return layer_vkQueueInsertDebugUtilsLabelEXT<T>;
        }

        return layer_vkQueueInsertDebugUtilsLabelEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueuePresentKHR = requires(
    VkQueue queue, const VkPresentInfoKHR* pPresentInfo
) {
    layer_vkQueuePresentKHR<T>(queue, pPresentInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkQueuePresentKHR getLayerPtr_vkQueuePresentKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueuePresentKHR<T>)
        {
            return layer_vkQueuePresentKHR<T>;
        }

        return layer_vkQueuePresentKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueSubmit = requires(
    VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence
) {
    layer_vkQueueSubmit<T>(queue, submitCount, pSubmits, fence);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueSubmit getLayerPtr_vkQueueSubmit()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueSubmit<T>)
        {
            return layer_vkQueueSubmit<T>;
        }

        return layer_vkQueueSubmit<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueSubmit2 = requires(
    VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence
) {
    layer_vkQueueSubmit2<T>(queue, submitCount, pSubmits, fence);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueSubmit2 getLayerPtr_vkQueueSubmit2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueSubmit2<T>)
        {
            return layer_vkQueueSubmit2<T>;
        }

        return layer_vkQueueSubmit2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueSubmit2KHR = requires(
    VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence
) {
    layer_vkQueueSubmit2KHR<T>(queue, submitCount, pSubmits, fence);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueSubmit2KHR getLayerPtr_vkQueueSubmit2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueSubmit2KHR<T>)
        {
            return layer_vkQueueSubmit2KHR<T>;
        }

        return layer_vkQueueSubmit2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkQueueWaitIdle = requires(
    VkQueue queue
) {
    layer_vkQueueWaitIdle<T>(queue);
};

/* Function pointer resolution. */
constexpr PFN_vkQueueWaitIdle getLayerPtr_vkQueueWaitIdle()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkQueueWaitIdle<T>)
        {
            return layer_vkQueueWaitIdle<T>;
        }

        return layer_vkQueueWaitIdle<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkRegisterDeviceEventEXT = requires(
    VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence
) {
    layer_vkRegisterDeviceEventEXT<T>(device, pDeviceEventInfo, pAllocator, pFence);
};

/* Function pointer resolution. */
constexpr PFN_vkRegisterDeviceEventEXT getLayerPtr_vkRegisterDeviceEventEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkRegisterDeviceEventEXT<T>)
        {
            return layer_vkRegisterDeviceEventEXT<T>;
        }

        return layer_vkRegisterDeviceEventEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkRegisterDisplayEventEXT = requires(
    VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence
) {
    layer_vkRegisterDisplayEventEXT<T>(device, display, pDisplayEventInfo, pAllocator, pFence);
};

/* Function pointer resolution. */
constexpr PFN_vkRegisterDisplayEventEXT getLayerPtr_vkRegisterDisplayEventEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkRegisterDisplayEventEXT<T>)
        {
            return layer_vkRegisterDisplayEventEXT<T>;
        }

        return layer_vkRegisterDisplayEventEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkReleaseCapturedPipelineDataKHR = requires(
    VkDevice device, const VkReleaseCapturedPipelineDataInfoKHR* pInfo, const VkAllocationCallbacks* pAllocator
) {
    layer_vkReleaseCapturedPipelineDataKHR<T>(device, pInfo, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkReleaseCapturedPipelineDataKHR getLayerPtr_vkReleaseCapturedPipelineDataKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkReleaseCapturedPipelineDataKHR<T>)
        {
            return layer_vkReleaseCapturedPipelineDataKHR<T>;
        }

        return layer_vkReleaseCapturedPipelineDataKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkReleaseProfilingLockKHR = requires(
    VkDevice device
) {
    layer_vkReleaseProfilingLockKHR<T>(device);
};

/* Function pointer resolution. */
constexpr PFN_vkReleaseProfilingLockKHR getLayerPtr_vkReleaseProfilingLockKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkReleaseProfilingLockKHR<T>)
        {
            return layer_vkReleaseProfilingLockKHR<T>;
        }

        return layer_vkReleaseProfilingLockKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkReleaseSwapchainImagesEXT = requires(
    VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo
) {
    layer_vkReleaseSwapchainImagesEXT<T>(device, pReleaseInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkReleaseSwapchainImagesEXT getLayerPtr_vkReleaseSwapchainImagesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkReleaseSwapchainImagesEXT<T>)
        {
            return layer_vkReleaseSwapchainImagesEXT<T>;
        }

        return layer_vkReleaseSwapchainImagesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetCommandBuffer = requires(
    VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags
) {
    layer_vkResetCommandBuffer<T>(commandBuffer, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkResetCommandBuffer getLayerPtr_vkResetCommandBuffer()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetCommandBuffer<T>)
        {
            return layer_vkResetCommandBuffer<T>;
        }

        return layer_vkResetCommandBuffer<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetCommandPool = requires(
    VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags
) {
    layer_vkResetCommandPool<T>(device, commandPool, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkResetCommandPool getLayerPtr_vkResetCommandPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetCommandPool<T>)
        {
            return layer_vkResetCommandPool<T>;
        }

        return layer_vkResetCommandPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetDescriptorPool = requires(
    VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags
) {
    layer_vkResetDescriptorPool<T>(device, descriptorPool, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkResetDescriptorPool getLayerPtr_vkResetDescriptorPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetDescriptorPool<T>)
        {
            return layer_vkResetDescriptorPool<T>;
        }

        return layer_vkResetDescriptorPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetEvent = requires(
    VkDevice device, VkEvent event
) {
    layer_vkResetEvent<T>(device, event);
};

/* Function pointer resolution. */
constexpr PFN_vkResetEvent getLayerPtr_vkResetEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetEvent<T>)
        {
            return layer_vkResetEvent<T>;
        }

        return layer_vkResetEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetFences = requires(
    VkDevice device, uint32_t fenceCount, const VkFence* pFences
) {
    layer_vkResetFences<T>(device, fenceCount, pFences);
};

/* Function pointer resolution. */
constexpr PFN_vkResetFences getLayerPtr_vkResetFences()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetFences<T>)
        {
            return layer_vkResetFences<T>;
        }

        return layer_vkResetFences<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetQueryPool = requires(
    VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount
) {
    layer_vkResetQueryPool<T>(device, queryPool, firstQuery, queryCount);
};

/* Function pointer resolution. */
constexpr PFN_vkResetQueryPool getLayerPtr_vkResetQueryPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetQueryPool<T>)
        {
            return layer_vkResetQueryPool<T>;
        }

        return layer_vkResetQueryPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkResetQueryPoolEXT = requires(
    VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount
) {
    layer_vkResetQueryPoolEXT<T>(device, queryPool, firstQuery, queryCount);
};

/* Function pointer resolution. */
constexpr PFN_vkResetQueryPoolEXT getLayerPtr_vkResetQueryPoolEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkResetQueryPoolEXT<T>)
        {
            return layer_vkResetQueryPoolEXT<T>;
        }

        return layer_vkResetQueryPoolEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetDebugUtilsObjectNameEXT = requires(
    VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo
) {
    layer_vkSetDebugUtilsObjectNameEXT<T>(device, pNameInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkSetDebugUtilsObjectNameEXT getLayerPtr_vkSetDebugUtilsObjectNameEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetDebugUtilsObjectNameEXT<T>)
        {
            return layer_vkSetDebugUtilsObjectNameEXT<T>;
        }

        return layer_vkSetDebugUtilsObjectNameEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetDebugUtilsObjectTagEXT = requires(
    VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo
) {
    layer_vkSetDebugUtilsObjectTagEXT<T>(device, pTagInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkSetDebugUtilsObjectTagEXT getLayerPtr_vkSetDebugUtilsObjectTagEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetDebugUtilsObjectTagEXT<T>)
        {
            return layer_vkSetDebugUtilsObjectTagEXT<T>;
        }

        return layer_vkSetDebugUtilsObjectTagEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetDeviceMemoryPriorityEXT = requires(
    VkDevice device, VkDeviceMemory memory, float priority
) {
    layer_vkSetDeviceMemoryPriorityEXT<T>(device, memory, priority);
};

/* Function pointer resolution. */
constexpr PFN_vkSetDeviceMemoryPriorityEXT getLayerPtr_vkSetDeviceMemoryPriorityEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetDeviceMemoryPriorityEXT<T>)
        {
            return layer_vkSetDeviceMemoryPriorityEXT<T>;
        }

        return layer_vkSetDeviceMemoryPriorityEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetEvent = requires(
    VkDevice device, VkEvent event
) {
    layer_vkSetEvent<T>(device, event);
};

/* Function pointer resolution. */
constexpr PFN_vkSetEvent getLayerPtr_vkSetEvent()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetEvent<T>)
        {
            return layer_vkSetEvent<T>;
        }

        return layer_vkSetEvent<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetHdrMetadataEXT = requires(
    VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata
) {
    layer_vkSetHdrMetadataEXT<T>(device, swapchainCount, pSwapchains, pMetadata);
};

/* Function pointer resolution. */
constexpr PFN_vkSetHdrMetadataEXT getLayerPtr_vkSetHdrMetadataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetHdrMetadataEXT<T>)
        {
            return layer_vkSetHdrMetadataEXT<T>;
        }

        return layer_vkSetHdrMetadataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetPrivateData = requires(
    VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data
) {
    layer_vkSetPrivateData<T>(device, objectType, objectHandle, privateDataSlot, data);
};

/* Function pointer resolution. */
constexpr PFN_vkSetPrivateData getLayerPtr_vkSetPrivateData()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetPrivateData<T>)
        {
            return layer_vkSetPrivateData<T>;
        }

        return layer_vkSetPrivateData<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSetPrivateDataEXT = requires(
    VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data
) {
    layer_vkSetPrivateDataEXT<T>(device, objectType, objectHandle, privateDataSlot, data);
};

/* Function pointer resolution. */
constexpr PFN_vkSetPrivateDataEXT getLayerPtr_vkSetPrivateDataEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSetPrivateDataEXT<T>)
        {
            return layer_vkSetPrivateDataEXT<T>;
        }

        return layer_vkSetPrivateDataEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSignalSemaphore = requires(
    VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo
) {
    layer_vkSignalSemaphore<T>(device, pSignalInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkSignalSemaphore getLayerPtr_vkSignalSemaphore()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSignalSemaphore<T>)
        {
            return layer_vkSignalSemaphore<T>;
        }

        return layer_vkSignalSemaphore<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSignalSemaphoreKHR = requires(
    VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo
) {
    layer_vkSignalSemaphoreKHR<T>(device, pSignalInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkSignalSemaphoreKHR getLayerPtr_vkSignalSemaphoreKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSignalSemaphoreKHR<T>)
        {
            return layer_vkSignalSemaphoreKHR<T>;
        }

        return layer_vkSignalSemaphoreKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkTransitionImageLayout = requires(
    VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo* pTransitions
) {
    layer_vkTransitionImageLayout<T>(device, transitionCount, pTransitions);
};

/* Function pointer resolution. */
constexpr PFN_vkTransitionImageLayout getLayerPtr_vkTransitionImageLayout()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkTransitionImageLayout<T>)
        {
            return layer_vkTransitionImageLayout<T>;
        }

        return layer_vkTransitionImageLayout<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkTransitionImageLayoutEXT = requires(
    VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo* pTransitions
) {
    layer_vkTransitionImageLayoutEXT<T>(device, transitionCount, pTransitions);
};

/* Function pointer resolution. */
constexpr PFN_vkTransitionImageLayoutEXT getLayerPtr_vkTransitionImageLayoutEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkTransitionImageLayoutEXT<T>)
        {
            return layer_vkTransitionImageLayoutEXT<T>;
        }

        return layer_vkTransitionImageLayoutEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkTrimCommandPool = requires(
    VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags
) {
    layer_vkTrimCommandPool<T>(device, commandPool, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkTrimCommandPool getLayerPtr_vkTrimCommandPool()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkTrimCommandPool<T>)
        {
            return layer_vkTrimCommandPool<T>;
        }

        return layer_vkTrimCommandPool<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkTrimCommandPoolKHR = requires(
    VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags
) {
    layer_vkTrimCommandPoolKHR<T>(device, commandPool, flags);
};

/* Function pointer resolution. */
constexpr PFN_vkTrimCommandPoolKHR getLayerPtr_vkTrimCommandPoolKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkTrimCommandPoolKHR<T>)
        {
            return layer_vkTrimCommandPoolKHR<T>;
        }

        return layer_vkTrimCommandPoolKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUnmapMemory = requires(
    VkDevice device, VkDeviceMemory memory
) {
    layer_vkUnmapMemory<T>(device, memory);
};

/* Function pointer resolution. */
constexpr PFN_vkUnmapMemory getLayerPtr_vkUnmapMemory()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUnmapMemory<T>)
        {
            return layer_vkUnmapMemory<T>;
        }

        return layer_vkUnmapMemory<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUnmapMemory2 = requires(
    VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    layer_vkUnmapMemory2<T>(device, pMemoryUnmapInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkUnmapMemory2 getLayerPtr_vkUnmapMemory2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUnmapMemory2<T>)
        {
            return layer_vkUnmapMemory2<T>;
        }

        return layer_vkUnmapMemory2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUnmapMemory2KHR = requires(
    VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    layer_vkUnmapMemory2KHR<T>(device, pMemoryUnmapInfo);
};

/* Function pointer resolution. */
constexpr PFN_vkUnmapMemory2KHR getLayerPtr_vkUnmapMemory2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUnmapMemory2KHR<T>)
        {
            return layer_vkUnmapMemory2KHR<T>;
        }

        return layer_vkUnmapMemory2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUpdateDescriptorSetWithTemplate = requires(
    VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData
) {
    layer_vkUpdateDescriptorSetWithTemplate<T>(device, descriptorSet, descriptorUpdateTemplate, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkUpdateDescriptorSetWithTemplate getLayerPtr_vkUpdateDescriptorSetWithTemplate()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUpdateDescriptorSetWithTemplate<T>)
        {
            return layer_vkUpdateDescriptorSetWithTemplate<T>;
        }

        return layer_vkUpdateDescriptorSetWithTemplate<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUpdateDescriptorSetWithTemplateKHR = requires(
    VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData
) {
    layer_vkUpdateDescriptorSetWithTemplateKHR<T>(device, descriptorSet, descriptorUpdateTemplate, pData);
};

/* Function pointer resolution. */
constexpr PFN_vkUpdateDescriptorSetWithTemplateKHR getLayerPtr_vkUpdateDescriptorSetWithTemplateKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUpdateDescriptorSetWithTemplateKHR<T>)
        {
            return layer_vkUpdateDescriptorSetWithTemplateKHR<T>;
        }

        return layer_vkUpdateDescriptorSetWithTemplateKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUpdateDescriptorSets = requires(
    VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies
) {
    layer_vkUpdateDescriptorSets<T>(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
};

/* Function pointer resolution. */
constexpr PFN_vkUpdateDescriptorSets getLayerPtr_vkUpdateDescriptorSets()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUpdateDescriptorSets<T>)
        {
            return layer_vkUpdateDescriptorSets<T>;
        }

        return layer_vkUpdateDescriptorSets<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUpdateIndirectExecutionSetPipelineEXT = requires(
    VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites
) {
    layer_vkUpdateIndirectExecutionSetPipelineEXT<T>(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
};

/* Function pointer resolution. */
constexpr PFN_vkUpdateIndirectExecutionSetPipelineEXT getLayerPtr_vkUpdateIndirectExecutionSetPipelineEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUpdateIndirectExecutionSetPipelineEXT<T>)
        {
            return layer_vkUpdateIndirectExecutionSetPipelineEXT<T>;
        }

        return layer_vkUpdateIndirectExecutionSetPipelineEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkUpdateIndirectExecutionSetShaderEXT = requires(
    VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites
) {
    layer_vkUpdateIndirectExecutionSetShaderEXT<T>(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
};

/* Function pointer resolution. */
constexpr PFN_vkUpdateIndirectExecutionSetShaderEXT getLayerPtr_vkUpdateIndirectExecutionSetShaderEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkUpdateIndirectExecutionSetShaderEXT<T>)
        {
            return layer_vkUpdateIndirectExecutionSetShaderEXT<T>;
        }

        return layer_vkUpdateIndirectExecutionSetShaderEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWaitForFences = requires(
    VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout
) {
    layer_vkWaitForFences<T>(device, fenceCount, pFences, waitAll, timeout);
};

/* Function pointer resolution. */
constexpr PFN_vkWaitForFences getLayerPtr_vkWaitForFences()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWaitForFences<T>)
        {
            return layer_vkWaitForFences<T>;
        }

        return layer_vkWaitForFences<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWaitForPresent2KHR = requires(
    VkDevice device, VkSwapchainKHR swapchain, const VkPresentWait2InfoKHR* pPresentWait2Info
) {
    layer_vkWaitForPresent2KHR<T>(device, swapchain, pPresentWait2Info);
};

/* Function pointer resolution. */
constexpr PFN_vkWaitForPresent2KHR getLayerPtr_vkWaitForPresent2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWaitForPresent2KHR<T>)
        {
            return layer_vkWaitForPresent2KHR<T>;
        }

        return layer_vkWaitForPresent2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWaitForPresentKHR = requires(
    VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout
) {
    layer_vkWaitForPresentKHR<T>(device, swapchain, presentId, timeout);
};

/* Function pointer resolution. */
constexpr PFN_vkWaitForPresentKHR getLayerPtr_vkWaitForPresentKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWaitForPresentKHR<T>)
        {
            return layer_vkWaitForPresentKHR<T>;
        }

        return layer_vkWaitForPresentKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWaitSemaphores = requires(
    VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout
) {
    layer_vkWaitSemaphores<T>(device, pWaitInfo, timeout);
};

/* Function pointer resolution. */
constexpr PFN_vkWaitSemaphores getLayerPtr_vkWaitSemaphores()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWaitSemaphores<T>)
        {
            return layer_vkWaitSemaphores<T>;
        }

        return layer_vkWaitSemaphores<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWaitSemaphoresKHR = requires(
    VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout
) {
    layer_vkWaitSemaphoresKHR<T>(device, pWaitInfo, timeout);
};

/* Function pointer resolution. */
constexpr PFN_vkWaitSemaphoresKHR getLayerPtr_vkWaitSemaphoresKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWaitSemaphoresKHR<T>)
        {
            return layer_vkWaitSemaphoresKHR<T>;
        }

        return layer_vkWaitSemaphoresKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWriteAccelerationStructuresPropertiesKHR = requires(
    VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride
) {
    layer_vkWriteAccelerationStructuresPropertiesKHR<T>(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkWriteAccelerationStructuresPropertiesKHR getLayerPtr_vkWriteAccelerationStructuresPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWriteAccelerationStructuresPropertiesKHR<T>)
        {
            return layer_vkWriteAccelerationStructuresPropertiesKHR<T>;
        }

        return layer_vkWriteAccelerationStructuresPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkWriteMicromapsPropertiesEXT = requires(
    VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride
) {
    layer_vkWriteMicromapsPropertiesEXT<T>(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
};

/* Function pointer resolution. */
constexpr PFN_vkWriteMicromapsPropertiesEXT getLayerPtr_vkWriteMicromapsPropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkWriteMicromapsPropertiesEXT<T>)
        {
            return layer_vkWriteMicromapsPropertiesEXT<T>;
        }

        return layer_vkWriteMicromapsPropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

// clang-format on
