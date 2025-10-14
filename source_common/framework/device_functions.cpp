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

// clang-format off

#include <mutex>

// Include from per-layer code
#include "utils.hpp"
#include "device.hpp"

// Include from common code
#include "framework/device_functions.hpp"

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImage2KHR<default_tag>(
    VkDevice device,
    const VkAcquireNextImageInfoKHR* pAcquireInfo,
    uint32_t* pImageIndex
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImageKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t timeout,
    VkSemaphore semaphore,
    VkFence fence,
    uint32_t* pImageIndex
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireProfilingLockKHR<default_tag>(
    VkDevice device,
    const VkAcquireProfilingLockInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAcquireProfilingLockKHR(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers<default_tag>(
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
    return layer->driver.vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateDescriptorSets<default_tag>(
    VkDevice device,
    const VkDescriptorSetAllocateInfo* pAllocateInfo,
    VkDescriptorSet* pDescriptorSets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory<default_tag>(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBeginCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBeginCommandBuffer(commandBuffer, pBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindBufferMemory(device, buffer, memory, memoryOffset);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindBufferMemory2(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2KHR<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindBufferMemory2KHR(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindDataGraphPipelineSessionMemoryARM<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindDataGraphPipelineSessionMemoryInfoARM* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindDataGraphPipelineSessionMemoryARM(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory<default_tag>(
    VkDevice device,
    VkImage image,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindImageMemory(device, image, memory, memoryOffset);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindImageMemory2(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2KHR<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindImageMemory2KHR(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindTensorMemoryARM<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindTensorMemoryInfoARM* pBindInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBindTensorMemoryARM(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildAccelerationStructuresKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBuildAccelerationStructuresKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildMicromapsEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkBuildMicromapsEXT(device, deferredOperation, infoCount, pInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginConditionalRenderingEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQuery<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQueryIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags,
    uint32_t index
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginRendering(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginTransformFeedbackEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorBufferEmbeddedSamplersEXT(commandBuffer, pipelineBindPoint, layout, set);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBuffersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t bufferCount,
    const VkDescriptorBufferBindingInfoEXT* pBindingInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorBuffersEXT(commandBuffer, bufferCount, pBindingInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    const uint32_t* pDynamicOffsets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorSets2(commandBuffer, pBindDescriptorSetsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindDescriptorSets2KHR(commandBuffer, pBindDescriptorSetsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkIndexType indexType
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindIndexBuffer2(commandBuffer, buffer, offset, size, indexType);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindIndexBuffer2KHR(commandBuffer, buffer, offset, size, indexType);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindPipeline<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipeline pipeline
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindShadersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t stageCount,
    const VkShaderStageFlagBits* pStages,
    const VkShaderEXT* pShaders
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindTransformFeedbackBuffersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindVertexBuffers2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageBlit* pRegions,
    VkFilter filter
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBlitImage2(commandBuffer, pBlitImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildMicromapsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdBuildMicromapsEXT(commandBuffer, infoCount, pInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearAttachments<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkClearAttachment* pAttachments,
    uint32_t rectCount,
    const VkClearRect* pRects
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearColorValue* pColor,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearDepthStencilValue* pDepthStencil,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureToMemoryKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferCopy* pRegions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageCopy* pRegions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryIndirectInfoKHR* pCopyMemoryIndirectInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMemoryIndirectKHR(commandBuffer, pCopyMemoryIndirectInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToAccelerationStructureKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToImageIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToImageIndirectInfoKHR* pCopyMemoryToImageIndirectInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMemoryToImageIndirectKHR(commandBuffer, pCopyMemoryToImageIndirectInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToMicromapEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMemoryToMicromapEXT(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMicromapEXT(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapToMemoryEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyMicromapToMemoryEXT(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyQueryPoolResults<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize stride,
    VkQueryResultFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyTensorARM<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyTensorInfoARM* pCopyTensorInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdCopyTensorARM(commandBuffer, pCopyTensorInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDebugMarkerEndEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerInsertEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchDataGraphARM<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDataGraphPipelineSessionARM session,
    const VkDataGraphPipelineDispatchInfoARM* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDispatchDataGraphARM(commandBuffer, session, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDispatchIndirect(commandBuffer, buffer, offset);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawMeshTasksEXT(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawMeshTasksIndirectCountEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawMeshTasksIndirectEXT(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawInfoEXT* pVertexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawMultiEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawIndexedInfoEXT* pIndexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride,
    const int32_t* pVertexOffset
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdDrawMultiIndexedEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndConditionalRenderingEXT<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndConditionalRenderingEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQuery<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndQuery(commandBuffer, queryPool, query);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQueryIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    uint32_t index
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRendering(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingEndInfoEXT* pRenderingEndInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRendering2EXT(commandBuffer, pRenderingEndInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderingKHR(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndTransformFeedbackEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteGeneratedCommandsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 isPreprocessed,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdExecuteGeneratedCommandsEXT(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize size,
    uint32_t data
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdInsertDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSubpassContents contents
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdNextSubpass(commandBuffer, contents);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask,
    VkDependencyFlags dependencyFlags,
    uint32_t memoryBarrierCount,
    const VkMemoryBarrier* pMemoryBarriers,
    uint32_t bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier* pBufferMemoryBarriers,
    uint32_t imageMemoryBarrierCount,
    const VkImageMemoryBarrier* pImageMemoryBarriers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPipelineBarrier2(commandBuffer, pDependencyInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPreprocessGeneratedCommandsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo,
    VkCommandBuffer stateCommandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPreprocessGeneratedCommandsEXT(commandBuffer, pGeneratedCommandsInfo, stateCommandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineLayout layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    const void* pValues
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushConstants2(commandBuffer, pPushConstantsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushConstants2KHR(commandBuffer, pPushConstantsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSet(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSet2(commandBuffer, pPushDescriptorSetInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSet2KHR(commandBuffer, pPushDescriptorSetInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSetWithTemplate(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSetWithTemplate2(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSetWithTemplate2KHR(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplateKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResetEvent(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResetEvent2(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResetEvent2KHR(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetQueryPool<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageResolve* pRegions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResolveImage2(commandBuffer, pResolveImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToCoverageEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToCoverageEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToOneEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToOneEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAttachmentFeedbackLoopEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImageAspectFlags aspectMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetAttachmentFeedbackLoopEnableEXT(commandBuffer, aspectMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetBlendConstants<default_tag>(
    VkCommandBuffer commandBuffer,
    const float blendConstants[4]
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetBlendConstants(commandBuffer, blendConstants);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendAdvancedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendAdvancedEXT* pColorBlendAdvanced
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkBool32* pColorBlendEnables
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEquationEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendEquationEXT* pColorBlendEquations
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkBool32* pColorWriteEnables
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteMaskEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorComponentFlags* pColorWriteMasks
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetConservativeRasterizationModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkConservativeRasterizationModeEXT conservativeRasterizationMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationModeNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCoverageModulationModeNV coverageModulationMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageModulationTableEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageReductionModeNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCoverageReductionModeNV coverageReductionMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageToColorEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorLocationNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t coverageToColorLocation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCullMode(commandBuffer, cullMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCullModeEXT(commandBuffer, cullMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias<default_tag>(
    VkCommandBuffer commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDepthBiasInfoEXT* pDepthBiasInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBias2EXT(commandBuffer, pDepthBiasInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBiasEnable(commandBuffer, depthBiasEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBounds<default_tag>(
    VkCommandBuffer commandBuffer,
    float minDepthBounds,
    float maxDepthBounds
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBoundsTestEnable(commandBuffer, depthBoundsTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClampEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampRangeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDepthClampModeEXT depthClampMode,
    const VkDepthClampRangeEXT* pDepthClampRange
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthClampRangeEXT(commandBuffer, depthClampMode, pDepthClampRange);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClipEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipNegativeOneToOneEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 negativeOneToOne
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthCompareOp(commandBuffer, depthCompareOp);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthTestEnable(commandBuffer, depthTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthWriteEnable(commandBuffer, depthWriteEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsets2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDescriptorBufferOffsets2EXT(commandBuffer, pSetDescriptorBufferOffsetsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsetsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t setCount,
    const uint32_t* pBufferIndices,
    const VkDeviceSize* pOffsets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMask<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDeviceMask(commandBuffer, deviceMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMaskKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstDiscardRectangle,
    uint32_t discardRectangleCount,
    const VkRect2D* pDiscardRectangles
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 discardRectangleEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDiscardRectangleModeEXT discardRectangleMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetEvent(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetEvent2(commandBuffer, event, pDependencyInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    float extraPrimitiveOverestimationSize
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFragmentShadingRateKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkExtent2D* pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR combinerOps[2]
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFace<default_tag>(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetFrontFace(commandBuffer, frontFace);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFaceEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetFrontFaceEXT(commandBuffer, frontFace);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineRasterizationModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkLineRasterizationModeEXT lineRasterizationMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStipple<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineStipple(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stippledLineEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineStippleKHR(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineWidth<default_tag>(
    VkCommandBuffer commandBuffer,
    float lineWidth
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLineWidth(commandBuffer, lineWidth);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkLogicOp logicOp
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLogicOpEXT(commandBuffer, logicOp);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 logicOpEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPatchControlPointsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t patchControlPoints
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPolygonModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPolygonMode polygonMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPolygonModeEXT(commandBuffer, polygonMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPrimitiveRestartEnable(commandBuffer, primitiveRestartEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopology<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPrimitiveTopology(commandBuffer, primitiveTopology);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopologyEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetProvokingVertexModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkProvokingVertexModeEXT provokingVertexMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationSamplesEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits rasterizationSamples
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationStreamEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t rasterizationStream
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRasterizerDiscardEnable(commandBuffer, rasterizerDiscardEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRayTracingPipelineStackSizeKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t pipelineStackSize
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRayTracingPipelineStackSizeKHR(commandBuffer, pipelineStackSize);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocations<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRenderingAttachmentLocations(commandBuffer, pLocationInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocationsKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRenderingAttachmentLocationsKHR(commandBuffer, pLocationInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndices<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRenderingInputAttachmentIndices(commandBuffer, pInputAttachmentIndexInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndicesKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRenderingInputAttachmentIndicesKHR(commandBuffer, pInputAttachmentIndexInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRepresentativeFragmentTestEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 representativeFragmentTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 sampleLocationsEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleMaskEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits samples,
    const VkSampleMask* pSampleMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissor<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCount<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetScissorWithCount(commandBuffer, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetShadingRateImageEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 shadingRateImageEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilCompareMask<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t compareMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilOp(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilReference<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t reference
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilReference(commandBuffer, faceMask, reference);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilTestEnable(commandBuffer, stencilTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilWriteMask<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t writeMask
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetTessellationDomainOriginEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkTessellationDomainOrigin domainOrigin
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetVertexInputEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewport<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportSwizzleNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewportSwizzleNV* pViewportSwizzles
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWScalingEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 viewportWScalingEnable
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCount<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetViewportWithCount(commandBuffer, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdTraceRaysKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdUpdateBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize dataSize,
    const void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask,
    uint32_t memoryBarrierCount,
    const VkMemoryBarrier* pMemoryBarriers,
    uint32_t bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier* pBufferMemoryBarriers,
    uint32_t imageMemoryBarrierCount,
    const VkImageMemoryBarrier* pImageMemoryBarriers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWaitEvents2(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteAccelerationStructuresPropertiesKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteMicromapsPropertiesEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWriteMicromapsPropertiesEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlagBits pipelineStage,
    VkQueryPool queryPool,
    uint32_t query
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWriteTimestamp2(commandBuffer, stage, queryPool, query);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyAccelerationStructureKHR(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureToMemoryKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyAccelerationStructureToMemoryKHR(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImage<default_tag>(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyImageToImage(device, pCopyImageToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImageEXT<default_tag>(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyImageToImageEXT(device, pCopyImageToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemory<default_tag>(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyImageToMemory(device, pCopyImageToMemoryInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemoryEXT<default_tag>(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyImageToMemoryEXT(device, pCopyImageToMemoryInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMemoryToAccelerationStructureKHR(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImage<default_tag>(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMemoryToImage(device, pCopyMemoryToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImageEXT<default_tag>(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMemoryToImageEXT(device, pCopyMemoryToImageInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToMicromapEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMemoryToMicromapEXT(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMicromapEXT(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapToMemoryEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCopyMicromapToMemoryEXT(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAccelerationStructureKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkAccelerationStructureKHR* pAccelerationStructure
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateAccelerationStructureKHR(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBuffer<default_tag>(
    VkDevice device,
    const VkBufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBuffer* pBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBufferView<default_tag>(
    VkDevice device,
    const VkBufferViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBufferView* pView
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateBufferView(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool<default_tag>(
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
    return layer->driver.vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkComputePipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDataGraphPipelineSessionARM<default_tag>(
    VkDevice device,
    const VkDataGraphPipelineSessionCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDataGraphPipelineSessionARM* pSession
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDataGraphPipelineSessionARM(device, pCreateInfo, pAllocator, pSession);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDataGraphPipelinesARM<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkDataGraphPipelineCreateInfoARM* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDataGraphPipelinesARM(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDeferredOperationKHR<default_tag>(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator,
    VkDeferredOperationKHR* pDeferredOperation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDeferredOperationKHR(device, pAllocator, pDeferredOperation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorPool<default_tag>(
    VkDevice device,
    const VkDescriptorPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorPool* pDescriptorPool
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorSetLayout<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorSetLayout* pSetLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplate<default_tag>(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplateKHR<default_tag>(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateEvent<default_tag>(
    VkDevice device,
    const VkEventCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkEvent* pEvent
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateEvent(device, pCreateInfo, pAllocator, pEvent);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFence<default_tag>(
    VkDevice device,
    const VkFenceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateFence(device, pCreateInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFramebuffer<default_tag>(
    VkDevice device,
    const VkFramebufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFramebuffer* pFramebuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateGraphicsPipelines<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkGraphicsPipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage<default_tag>(
    VkDevice device,
    const VkImageCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImage* pImage
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateImage(device, pCreateInfo, pAllocator, pImage);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImageView<default_tag>(
    VkDevice device,
    const VkImageViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImageView* pView
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateImageView(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectCommandsLayoutEXT<default_tag>(
    VkDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateIndirectCommandsLayoutEXT(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectExecutionSetEXT<default_tag>(
    VkDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectExecutionSetEXT* pIndirectExecutionSet
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateIndirectExecutionSetEXT(device, pCreateInfo, pAllocator, pIndirectExecutionSet);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateMicromapEXT<default_tag>(
    VkDevice device,
    const VkMicromapCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkMicromapEXT* pMicromap
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateMicromapEXT(device, pCreateInfo, pAllocator, pMicromap);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineBinariesKHR<default_tag>(
    VkDevice device,
    const VkPipelineBinaryCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineBinaryHandlesInfoKHR* pBinaries
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreatePipelineBinariesKHR(device, pCreateInfo, pAllocator, pBinaries);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineCache<default_tag>(
    VkDevice device,
    const VkPipelineCacheCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineCache* pPipelineCache
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineLayout<default_tag>(
    VkDevice device,
    const VkPipelineLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineLayout* pPipelineLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlot<default_tag>(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreatePrivateDataSlot(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlotEXT<default_tag>(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateQueryPool<default_tag>(
    VkDevice device,
    const VkQueryPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkQueryPool* pQueryPool
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRayTracingPipelinesKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateRayTracingPipelinesKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSampler<default_tag>(
    VkDevice device,
    const VkSamplerCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSampler* pSampler
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSampler(device, pCreateInfo, pAllocator, pSampler);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversion<default_tag>(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversionKHR<default_tag>(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSemaphore<default_tag>(
    VkDevice device,
    const VkSemaphoreCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSemaphore* pSemaphore
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule<default_tag>(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkShaderModule* pShaderModule
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT<default_tag>(
    VkDevice device,
    uint32_t createInfoCount,
    const VkShaderCreateInfoEXT* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkShaderEXT* pShaders
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSharedSwapchainsKHR<default_tag>(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchains
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR<default_tag>(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorARM<default_tag>(
    VkDevice device,
    const VkTensorCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorARM* pTensor
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateTensorARM(device, pCreateInfo, pAllocator, pTensor);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorViewARM<default_tag>(
    VkDevice device,
    const VkTensorViewCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorViewARM* pView
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateTensorViewARM(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateValidationCacheEXT<default_tag>(
    VkDevice device,
    const VkValidationCacheCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkValidationCacheEXT* pValidationCache
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectNameEXT<default_tag>(
    VkDevice device,
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkDebugMarkerSetObjectNameEXT(device, pNameInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectTagEXT<default_tag>(
    VkDevice device,
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkDebugMarkerSetObjectTagEXT(device, pTagInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeferredOperationJoinKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkDeferredOperationJoinKHR(device, operation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkAccelerationStructureKHR accelerationStructure,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyAccelerationStructureKHR(device, accelerationStructure, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBuffer<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyBuffer(device, buffer, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBufferView<default_tag>(
    VkDevice device,
    VkBufferView bufferView,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyBufferView(device, bufferView, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyCommandPool(device, commandPool, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDataGraphPipelineSessionARM<default_tag>(
    VkDevice device,
    VkDataGraphPipelineSessionARM session,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDataGraphPipelineSessionARM(device, session, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDeferredOperationKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDeferredOperationKHR(device, operation, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorPool<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorSetLayout<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout descriptorSetLayout,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplate<default_tag>(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplateKHR<default_tag>(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyEvent<default_tag>(
    VkDevice device,
    VkEvent event,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyEvent(device, event, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFence<default_tag>(
    VkDevice device,
    VkFence fence,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyFence(device, fence, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFramebuffer<default_tag>(
    VkDevice device,
    VkFramebuffer framebuffer,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyFramebuffer(device, framebuffer, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImage<default_tag>(
    VkDevice device,
    VkImage image,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyImage(device, image, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImageView<default_tag>(
    VkDevice device,
    VkImageView imageView,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyImageView(device, imageView, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectCommandsLayoutEXT<default_tag>(
    VkDevice device,
    VkIndirectCommandsLayoutEXT indirectCommandsLayout,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyIndirectCommandsLayoutEXT(device, indirectCommandsLayout, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectExecutionSetEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyIndirectExecutionSetEXT(device, indirectExecutionSet, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyMicromapEXT<default_tag>(
    VkDevice device,
    VkMicromapEXT micromap,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyMicromapEXT(device, micromap, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipeline<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPipeline(device, pipeline, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineBinaryKHR<default_tag>(
    VkDevice device,
    VkPipelineBinaryKHR pipelineBinary,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPipelineBinaryKHR(device, pipelineBinary, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineCache<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPipelineCache(device, pipelineCache, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineLayout<default_tag>(
    VkDevice device,
    VkPipelineLayout pipelineLayout,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlot<default_tag>(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPrivateDataSlot(device, privateDataSlot, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlotEXT<default_tag>(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyQueryPool<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyQueryPool(device, queryPool, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass<default_tag>(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyRenderPass(device, renderPass, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySampler<default_tag>(
    VkDevice device,
    VkSampler sampler,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySampler(device, sampler, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversion<default_tag>(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversionKHR<default_tag>(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySemaphore<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySemaphore(device, semaphore, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderEXT<default_tag>(
    VkDevice device,
    VkShaderEXT shader,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyShaderEXT(device, shader, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderModule<default_tag>(
    VkDevice device,
    VkShaderModule shaderModule,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyShaderModule(device, shaderModule, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySwapchainKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySwapchainKHR(device, swapchain, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorARM<default_tag>(
    VkDevice device,
    VkTensorARM tensor,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyTensorARM(device, tensor, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorViewARM<default_tag>(
    VkDevice device,
    VkTensorViewARM tensorView,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyTensorViewARM(device, tensorView, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyValidationCacheEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyValidationCacheEXT(device, validationCache, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeviceWaitIdle<default_tag>(
    VkDevice device
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkDeviceWaitIdle(device);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDisplayPowerControlEXT<default_tag>(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkDisplayPowerControlEXT(device, display, pDisplayPowerInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEndCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEndCommandBuffer(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFlushMappedMemoryRanges<default_tag>(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkFlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFreeDescriptorSets<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkFreeMemory(device, memory, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetAccelerationStructureBuildSizesKHR<default_tag>(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t* pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetAccelerationStructureBuildSizesKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetAccelerationStructureDeviceAddressKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetAccelerationStructureDeviceAddressKHR(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddress<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferDeviceAddress(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressEXT<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferDeviceAddressEXT(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressKHR<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferDeviceAddressKHR(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    VkMemoryRequirements* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddress<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferOpaqueCaptureAddress(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddressKHR<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferOpaqueCaptureAddressKHR(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetBufferOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetBufferOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsEXT<default_tag>(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsKHR<default_tag>(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetCalibratedTimestampsKHR(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDataGraphPipelineAvailablePropertiesARM<default_tag>(
    VkDevice device,
    const VkDataGraphPipelineInfoARM* pPipelineInfo,
    uint32_t* pPropertiesCount,
    VkDataGraphPipelinePropertyARM* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDataGraphPipelineAvailablePropertiesARM(device, pPipelineInfo, pPropertiesCount, pProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDataGraphPipelinePropertiesARM<default_tag>(
    VkDevice device,
    const VkDataGraphPipelineInfoARM* pPipelineInfo,
    uint32_t propertiesCount,
    VkDataGraphPipelinePropertyQueryResultARM* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDataGraphPipelinePropertiesARM(device, pPipelineInfo, propertiesCount, pProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDataGraphPipelineSessionBindPointRequirementsARM<default_tag>(
    VkDevice device,
    const VkDataGraphPipelineSessionBindPointRequirementsInfoARM* pInfo,
    uint32_t* pBindPointRequirementCount,
    VkDataGraphPipelineSessionBindPointRequirementARM* pBindPointRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDataGraphPipelineSessionBindPointRequirementsARM(device, pInfo, pBindPointRequirementCount, pBindPointRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDataGraphPipelineSessionMemoryRequirementsARM<default_tag>(
    VkDevice device,
    const VkDataGraphPipelineSessionMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDataGraphPipelineSessionMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR uint32_t VKAPI_CALL layer_vkGetDeferredOperationMaxConcurrencyKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeferredOperationMaxConcurrencyKHR(device, operation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeferredOperationResultKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeferredOperationResultKHR(device, operation);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorEXT<default_tag>(
    VkDevice device,
    const VkDescriptorGetInfoEXT* pDescriptorInfo,
    size_t dataSize,
    void* pDescriptor
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDescriptorEXT(device, pDescriptorInfo, dataSize, pDescriptor);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutBindingOffsetEXT<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout layout,
    uint32_t binding,
    VkDeviceSize* pOffset
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDescriptorSetLayoutBindingOffsetEXT(device, layout, binding, pOffset);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSizeEXT<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout layout,
    VkDeviceSize* pLayoutSizeInBytes
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDescriptorSetLayoutSizeEXT(device, layout, pLayoutSizeInBytes);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupport<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupportKHR<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceAccelerationStructureCompatibilityKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceAccelerationStructureCompatibilityKHR(device, pVersionInfo, pCompatibility);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceBufferMemoryRequirements(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirementsKHR<default_tag>(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceFaultInfoEXT<default_tag>(
    VkDevice device,
    VkDeviceFaultCountsEXT* pFaultCounts,
    VkDeviceFaultInfoEXT* pFaultInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeviceFaultInfoEXT(device, pFaultCounts, pFaultInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeatures<default_tag>(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeaturesKHR<default_tag>(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupPresentCapabilitiesKHR<default_tag>(
    VkDevice device,
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupSurfacePresentModesKHR<default_tag>(
    VkDevice device,
    VkSurfaceKHR surface,
    VkDeviceGroupPresentModeFlagsKHR* pModes
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageMemoryRequirements(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageSparseMemoryRequirements(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirementsKHR<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayout<default_tag>(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageSubresourceLayout(device, pInfo, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayoutKHR<default_tag>(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageSubresourceLayoutKHR(device, pInfo, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMemoryCommitment<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize* pCommittedMemoryInBytes
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddress<default_tag>(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR<default_tag>(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMicromapCompatibilityEXT<default_tag>(
    VkDevice device,
    const VkMicromapVersionInfoEXT* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceMicromapCompatibilityEXT(device, pVersionInfo, pCompatibility);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue<default_tag>(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue2<default_tag>(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceQueue2(device, pQueueInfo, pQueue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceTensorMemoryRequirementsARM<default_tag>(
    VkDevice device,
    const VkDeviceTensorMemoryRequirementsARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceTensorMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetEventStatus<default_tag>(
    VkDevice device,
    VkEvent event
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetEventStatus(device, event);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceFdKHR<default_tag>(
    VkDevice device,
    const VkFenceGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetFenceFdKHR(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceStatus<default_tag>(
    VkDevice device,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetFenceStatus(device, fence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetGeneratedCommandsMemoryRequirementsEXT<default_tag>(
    VkDevice device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetGeneratedCommandsMemoryRequirementsEXT(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageDrmFormatModifierPropertiesEXT<default_tag>(
    VkDevice device,
    VkImage image,
    VkImageDrmFormatModifierPropertiesEXT* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetImageDrmFormatModifierPropertiesEXT(device, image, pProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements<default_tag>(
    VkDevice device,
    VkImage image,
    VkMemoryRequirements* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkImageCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetImageOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements<default_tag>(
    VkDevice device,
    VkImage image,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource* pSubresource,
    VkSubresourceLayout* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSubresourceLayout2(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2EXT<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2KHR<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetImageSubresourceLayout2KHR(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetImageViewOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdKHR<default_tag>(
    VkDevice device,
    const VkMemoryGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetMemoryFdKHR(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdPropertiesKHR<default_tag>(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    int fd,
    VkMemoryFdPropertiesKHR* pMemoryFdProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryHostPointerPropertiesEXT<default_tag>(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    const void* pHostPointer,
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetMicromapBuildSizesEXT<default_tag>(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkMicromapBuildInfoEXT* pBuildInfo,
    VkMicromapBuildSizesInfoEXT* pSizeInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetMicromapBuildSizesEXT(device, buildType, pBuildInfo, pSizeInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineBinaryDataKHR<default_tag>(
    VkDevice device,
    const VkPipelineBinaryDataInfoKHR* pInfo,
    VkPipelineBinaryKeyKHR* pPipelineBinaryKey,
    size_t* pPipelineBinaryDataSize,
    void* pPipelineBinaryData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineBinaryDataKHR(device, pInfo, pPipelineBinaryKey, pPipelineBinaryDataSize, pPipelineBinaryData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineCacheData<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    size_t* pDataSize,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableInternalRepresentationsKHR<default_tag>(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutablePropertiesKHR<default_tag>(
    VkDevice device,
    const VkPipelineInfoKHR* pPipelineInfo,
    uint32_t* pExecutableCount,
    VkPipelineExecutablePropertiesKHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableStatisticsKHR<default_tag>(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pStatisticCount,
    VkPipelineExecutableStatisticKHR* pStatistics
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR<default_tag>(
    VkDevice device,
    const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR* pPipelineKey
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineKeyKHR(device, pPipelineCreateInfo, pPipelineKey);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelinePropertiesEXT<default_tag>(
    VkDevice device,
    const VkPipelineInfoEXT* pPipelineInfo,
    VkBaseOutStructure* pPipelineProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelinePropertiesEXT(device, pPipelineInfo, pPipelineProperties);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateData<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPrivateData(device, objectType, objectHandle, privateDataSlot, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateDataEXT<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetQueryPoolResults<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    size_t dataSize,
    void* pData,
    VkDeviceSize stride,
    VkQueryResultFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingShaderGroupHandlesKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetRayTracingShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkDeviceSize VKAPI_CALL layer_vkGetRayTracingShaderGroupStackSizeKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t group,
    VkShaderGroupShaderKHR groupShader
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetRayTracingShaderGroupStackSizeKHR(device, pipeline, group, groupShader);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderAreaGranularity<default_tag>(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D* pGranularity
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetRenderAreaGranularity(device, renderPass, pGranularity);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularity<default_tag>(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetRenderingAreaGranularity(device, pRenderingAreaInfo, pGranularity);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularityKHR<default_tag>(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetRenderingAreaGranularityKHR(device, pRenderingAreaInfo, pGranularity);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSamplerOpaqueCaptureDescriptorDataEXT(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValue<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSemaphoreCounterValue(device, semaphore, pValue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValueKHR<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSemaphoreCounterValueKHR(device, semaphore, pValue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreFdKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSemaphoreFdKHR(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetShaderBinaryDataEXT<default_tag>(
    VkDevice device,
    VkShaderEXT shader,
    size_t* pDataSize,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetShaderBinaryDataEXT(device, shader, pDataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleCreateInfoIdentifierEXT<default_tag>(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    VkShaderModuleIdentifierEXT* pIdentifier
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetShaderModuleCreateInfoIdentifierEXT(device, pCreateInfo, pIdentifier);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleIdentifierEXT<default_tag>(
    VkDevice device,
    VkShaderModule shaderModule,
    VkShaderModuleIdentifierEXT* pIdentifier
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetShaderModuleIdentifierEXT(device, shaderModule, pIdentifier);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainCounterEXT<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSurfaceCounterFlagBitsEXT counter,
    uint64_t* pCounterValue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainImagesKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint32_t* pSwapchainImageCount,
    VkImage* pSwapchainImages
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainStatusKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetSwapchainStatusKHR(device, swapchain);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetTensorMemoryRequirementsARM<default_tag>(
    VkDevice device,
    const VkTensorMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetTensorMemoryRequirementsARM(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorOpaqueCaptureDescriptorDataARM<default_tag>(
    VkDevice device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetTensorOpaqueCaptureDescriptorDataARM(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM<default_tag>(
    VkDevice device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetTensorViewOpaqueCaptureDescriptorDataARM(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetValidationCacheDataEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    size_t* pDataSize,
    void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetValidationCacheDataEXT(device, validationCache, pDataSize, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportFenceFdKHR<default_tag>(
    VkDevice device,
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkImportFenceFdKHR(device, pImportFenceFdInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportSemaphoreFdKHR<default_tag>(
    VkDevice device,
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkInvalidateMappedMemoryRanges<default_tag>(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkInvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkMemoryMapFlags flags,
    void** ppData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkMapMemory(device, memory, offset, size, flags, ppData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2<default_tag>(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkMapMemory2(device, pMemoryMapInfo, ppData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2KHR<default_tag>(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkMapMemory2KHR(device, pMemoryMapInfo, ppData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergePipelineCaches<default_tag>(
    VkDevice device,
    VkPipelineCache dstCache,
    uint32_t srcCacheCount,
    const VkPipelineCache* pSrcCaches
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergeValidationCachesEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT dstCache,
    uint32_t srcCacheCount,
    const VkValidationCacheEXT* pSrcCaches
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkMergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueBeginDebugUtilsLabelEXT<default_tag>(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse<default_tag>(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueEndDebugUtilsLabelEXT<default_tag>(
    VkQueue queue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkQueueEndDebugUtilsLabelEXT(queue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueInsertDebugUtilsLabelEXT<default_tag>(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<default_tag>(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueuePresentKHR(queue, pPresentInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueSubmit2KHR(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueWaitIdle<default_tag>(
    VkQueue queue
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(queue);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkQueueWaitIdle(queue);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDeviceEventEXT<default_tag>(
    VkDevice device,
    const VkDeviceEventInfoEXT* pDeviceEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkRegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDisplayEventEXT<default_tag>(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayEventInfoEXT* pDisplayEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkRegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseCapturedPipelineDataKHR<default_tag>(
    VkDevice device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkReleaseCapturedPipelineDataKHR(device, pInfo, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkReleaseProfilingLockKHR<default_tag>(
    VkDevice device
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkReleaseProfilingLockKHR(device);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesEXT<default_tag>(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkReleaseSwapchainImagesEXT(device, pReleaseInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesKHR<default_tag>(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkReleaseSwapchainImagesKHR(device, pReleaseInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetCommandBuffer(commandBuffer, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetCommandPool(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetDescriptorPool<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    VkDescriptorPoolResetFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetDescriptorPool(device, descriptorPool, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetEvent<default_tag>(
    VkDevice device,
    VkEvent event
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetEvent(device, event);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetFences<default_tag>(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkResetFences(device, fenceCount, pFences);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPool<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkResetQueryPool(device, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPoolEXT<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkResetQueryPoolEXT(device, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectNameEXT<default_tag>(
    VkDevice device,
    const VkDebugUtilsObjectNameInfoEXT* pNameInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectTagEXT<default_tag>(
    VkDevice device,
    const VkDebugUtilsObjectTagInfoEXT* pTagInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkSetDeviceMemoryPriorityEXT<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    float priority
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkSetDeviceMemoryPriorityEXT(device, memory, priority);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetEvent<default_tag>(
    VkDevice device,
    VkEvent event
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSetEvent(device, event);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkSetHdrMetadataEXT<default_tag>(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainKHR* pSwapchains,
    const VkHdrMetadataEXT* pMetadata
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkSetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateData<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSetPrivateData(device, objectType, objectHandle, privateDataSlot, data);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateDataEXT<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphore<default_tag>(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSignalSemaphore(device, pSignalInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphoreKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkSignalSemaphoreKHR(device, pSignalInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayout<default_tag>(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkTransitionImageLayout(device, transitionCount, pTransitions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayoutEXT<default_tag>(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkTransitionImageLayoutEXT(device, transitionCount, pTransitions);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkTrimCommandPool(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPoolKHR<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkTrimCommandPoolKHR(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUnmapMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUnmapMemory(device, memory);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2<default_tag>(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkUnmapMemory2(device, pMemoryUnmapInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2KHR<default_tag>(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkUnmapMemory2KHR(device, pMemoryUnmapInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplate<default_tag>(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplateKHR<default_tag>(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSets<default_tag>(
    VkDevice device,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    const VkCopyDescriptorSet* pDescriptorCopies
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetPipelineEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUpdateIndirectExecutionSetPipelineEXT(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetShaderEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkUpdateIndirectExecutionSetShaderEXT(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForFences<default_tag>(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences,
    VkBool32 waitAll,
    uint64_t timeout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWaitForFences(device, fenceCount, pFences, waitAll, timeout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresent2KHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkPresentWait2InfoKHR* pPresentWait2Info
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWaitForPresent2KHR(device, swapchain, pPresentWait2Info);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresentKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t presentId,
    uint64_t timeout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWaitForPresentKHR(device, swapchain, presentId, timeout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphores<default_tag>(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWaitSemaphores(device, pWaitInfo, timeout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphoresKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWaitSemaphoresKHR(device, pWaitInfo, timeout);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteAccelerationStructuresPropertiesKHR<default_tag>(
    VkDevice device,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWriteAccelerationStructuresPropertiesKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteMicromapsPropertiesEXT<default_tag>(
    VkDevice device,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkWriteMicromapsPropertiesEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
}

// clang-format on
