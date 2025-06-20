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

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImage2KHR_default(
    VkDevice device,
    const VkAcquireNextImageInfoKHR* pAcquireInfo,
    uint32_t* pImageIndex);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImage2KHR(
    VkDevice device,
    const VkAcquireNextImageInfoKHR* pAcquireInfo,
    uint32_t* pImageIndex
) {
    return layer_vkAcquireNextImage2KHR_default(device, pAcquireInfo, pImageIndex);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImageKHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t timeout,
    VkSemaphore semaphore,
    VkFence fence,
    uint32_t* pImageIndex);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImageKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t timeout,
    VkSemaphore semaphore,
    VkFence fence,
    uint32_t* pImageIndex
) {
    return layer_vkAcquireNextImageKHR_default(device, swapchain, timeout, semaphore, fence, pImageIndex);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireProfilingLockKHR_default(
    VkDevice device,
    const VkAcquireProfilingLockInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireProfilingLockKHR(
    VkDevice device,
    const VkAcquireProfilingLockInfoKHR* pInfo
) {
    return layer_vkAcquireProfilingLockKHR_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers_default(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers
) {
    return layer_vkAllocateCommandBuffers_default(device, pAllocateInfo, pCommandBuffers);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateDescriptorSets_default(
    VkDevice device,
    const VkDescriptorSetAllocateInfo* pAllocateInfo,
    VkDescriptorSet* pDescriptorSets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateDescriptorSets(
    VkDevice device,
    const VkDescriptorSetAllocateInfo* pAllocateInfo,
    VkDescriptorSet* pDescriptorSets
) {
    return layer_vkAllocateDescriptorSets_default(device, pAllocateInfo, pDescriptorSets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory_default(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory
) {
    return layer_vkAllocateMemory_default(device, pAllocateInfo, pAllocator, pMemory);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBeginCommandBuffer_default(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBeginCommandBuffer(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo
) {
    return layer_vkBeginCommandBuffer_default(commandBuffer, pBeginInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory_default(
    VkDevice device,
    VkBuffer buffer,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory(
    VkDevice device,
    VkBuffer buffer,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset
) {
    return layer_vkBindBufferMemory_default(device, buffer, memory, memoryOffset);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2_default(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos
) {
    return layer_vkBindBufferMemory2_default(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2KHR_default(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2KHR(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos
) {
    return layer_vkBindBufferMemory2KHR_default(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory_default(
    VkDevice device,
    VkImage image,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory(
    VkDevice device,
    VkImage image,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset
) {
    return layer_vkBindImageMemory_default(device, image, memory, memoryOffset);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2_default(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos
) {
    return layer_vkBindImageMemory2_default(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2KHR_default(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2KHR(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos
) {
    return layer_vkBindImageMemory2KHR_default(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindTensorMemoryARM_default(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindTensorMemoryInfoARM* pBindInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindTensorMemoryARM(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindTensorMemoryInfoARM* pBindInfos
) {
    return layer_vkBindTensorMemoryARM_default(device, bindInfoCount, pBindInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildAccelerationStructuresKHR_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildAccelerationStructuresKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    return layer_vkBuildAccelerationStructuresKHR_default(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildMicromapsEXT_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildMicromapsEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos
) {
    return layer_vkBuildMicromapsEXT_default(device, deferredOperation, infoCount, pInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginConditionalRenderingEXT_default(
    VkCommandBuffer commandBuffer,
    const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginConditionalRenderingEXT(
    VkCommandBuffer commandBuffer,
    const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin
) {
    layer_vkCmdBeginConditionalRenderingEXT_default(commandBuffer, pConditionalRenderingBegin);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT_default(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkCmdBeginDebugUtilsLabelEXT_default(commandBuffer, pLabelInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQuery_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQuery(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags
) {
    layer_vkCmdBeginQuery_default(commandBuffer, queryPool, query, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQueryIndexedEXT_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags,
    uint32_t index);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQueryIndexedEXT(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags,
    uint32_t index
) {
    layer_vkCmdBeginQueryIndexedEXT_default(commandBuffer, queryPool, query, flags, index);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass_default(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents
) {
    layer_vkCmdBeginRenderPass_default(commandBuffer, pRenderPassBegin, contents);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2_default(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    layer_vkCmdBeginRenderPass2_default(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    layer_vkCmdBeginRenderPass2KHR_default(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    layer_vkCmdBeginRendering_default(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    layer_vkCmdBeginRenderingKHR_default(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginTransformFeedbackEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginTransformFeedbackEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets
) {
    layer_vkCmdBeginTransformFeedbackEXT_default(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT_default(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo
) {
    layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT_default(commandBuffer, pBindDescriptorBufferEmbeddedSamplersInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set
) {
    layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT_default(commandBuffer, pipelineBindPoint, layout, set);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBuffersEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t bufferCount,
    const VkDescriptorBufferBindingInfoEXT* pBindingInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBuffersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t bufferCount,
    const VkDescriptorBufferBindingInfoEXT* pBindingInfos
) {
    layer_vkCmdBindDescriptorBuffersEXT_default(commandBuffer, bufferCount, pBindingInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    const uint32_t* pDynamicOffsets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    const uint32_t* pDynamicOffsets
) {
    layer_vkCmdBindDescriptorSets_default(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2_default(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    layer_vkCmdBindDescriptorSets2_default(commandBuffer, pBindDescriptorSetsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2KHR(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo
) {
    layer_vkCmdBindDescriptorSets2KHR_default(commandBuffer, pBindDescriptorSetsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkIndexType indexType);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer_default(commandBuffer, buffer, offset, indexType);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer2_default(commandBuffer, buffer, offset, size, indexType);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2KHR_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2KHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType
) {
    layer_vkCmdBindIndexBuffer2KHR_default(commandBuffer, buffer, offset, size, indexType);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindPipeline_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipeline pipeline);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindPipeline(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipeline pipeline
) {
    layer_vkCmdBindPipeline_default(commandBuffer, pipelineBindPoint, pipeline);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindShadersEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t stageCount,
    const VkShaderStageFlagBits* pStages,
    const VkShaderEXT* pShaders);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindShadersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t stageCount,
    const VkShaderStageFlagBits* pStages,
    const VkShaderEXT* pShaders
) {
    layer_vkCmdBindShadersEXT_default(commandBuffer, stageCount, pStages, pShaders);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindTransformFeedbackBuffersEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindTransformFeedbackBuffersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes
) {
    layer_vkCmdBindTransformFeedbackBuffersEXT_default(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets
) {
    layer_vkCmdBindVertexBuffers_default(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides
) {
    layer_vkCmdBindVertexBuffers2_default(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2EXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2EXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides
) {
    layer_vkCmdBindVertexBuffers2EXT_default(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage_default(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageBlit* pRegions,
    VkFilter filter);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageBlit* pRegions,
    VkFilter filter
) {
    layer_vkCmdBlitImage_default(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2_default(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo
) {
    layer_vkCmdBlitImage2_default(commandBuffer, pBlitImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo
) {
    layer_vkCmdBlitImage2KHR_default(commandBuffer, pBlitImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts
) {
    layer_vkCmdBuildAccelerationStructuresIndirectKHR_default(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos
) {
    layer_vkCmdBuildAccelerationStructuresKHR_default(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildMicromapsEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildMicromapsEXT(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos
) {
    layer_vkCmdBuildMicromapsEXT_default(commandBuffer, infoCount, pInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearAttachments_default(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkClearAttachment* pAttachments,
    uint32_t rectCount,
    const VkClearRect* pRects);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearAttachments(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkClearAttachment* pAttachments,
    uint32_t rectCount,
    const VkClearRect* pRects
) {
    layer_vkCmdClearAttachments_default(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage_default(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearColorValue* pColor,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearColorValue* pColor,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges
) {
    layer_vkCmdClearColorImage_default(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage_default(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearDepthStencilValue* pDepthStencil,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearDepthStencilValue* pDepthStencil,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges
) {
    layer_vkCmdClearDepthStencilImage_default(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureKHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCmdCopyAccelerationStructureKHR_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureToMemoryKHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureToMemoryKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    layer_vkCmdCopyAccelerationStructureToMemoryKHR_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer_default(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferCopy* pRegions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferCopy* pRegions
) {
    layer_vkCmdCopyBuffer_default(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2_default(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    layer_vkCmdCopyBuffer2_default(commandBuffer, pCopyBufferInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    layer_vkCmdCopyBuffer2KHR_default(commandBuffer, pCopyBufferInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage_default(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions
) {
    layer_vkCmdCopyBufferToImage_default(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2_default(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    layer_vkCmdCopyBufferToImage2_default(commandBuffer, pCopyBufferToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    layer_vkCmdCopyBufferToImage2KHR_default(commandBuffer, pCopyBufferToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage_default(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageCopy* pRegions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageCopy* pRegions
) {
    layer_vkCmdCopyImage_default(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2_default(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    layer_vkCmdCopyImage2_default(commandBuffer, pCopyImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    layer_vkCmdCopyImage2KHR_default(commandBuffer, pCopyImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer_default(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions
) {
    layer_vkCmdCopyImageToBuffer_default(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2_default(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    layer_vkCmdCopyImageToBuffer2_default(commandBuffer, pCopyImageToBufferInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    layer_vkCmdCopyImageToBuffer2KHR_default(commandBuffer, pCopyImageToBufferInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToAccelerationStructureKHR_default(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToAccelerationStructureKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    layer_vkCmdCopyMemoryToAccelerationStructureKHR_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToMicromapEXT_default(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToMicromapEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    layer_vkCmdCopyMemoryToMicromapEXT_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapEXT_default(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapInfoEXT* pInfo
) {
    layer_vkCmdCopyMicromapEXT_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapToMemoryEXT_default(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapToMemoryEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    layer_vkCmdCopyMicromapToMemoryEXT_default(commandBuffer, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyQueryPoolResults_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize stride,
    VkQueryResultFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyQueryPoolResults(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize stride,
    VkQueryResultFlags flags
) {
    layer_vkCmdCopyQueryPoolResults_default(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyTensorARM_default(
    VkCommandBuffer commandBuffer,
    const VkCopyTensorInfoARM* pCopyTensorInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyTensorARM(
    VkCommandBuffer commandBuffer,
    const VkCopyTensorInfoARM* pCopyTensorInfo
) {
    layer_vkCmdCopyTensorARM_default(commandBuffer, pCopyTensorInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT_default(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    layer_vkCmdDebugMarkerBeginEXT_default(commandBuffer, pMarkerInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdDebugMarkerEndEXT_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerInsertEXT_default(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerInsertEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    layer_vkCmdDebugMarkerInsertEXT_default(commandBuffer, pMarkerInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch_default(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    layer_vkCmdDispatch_default(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase_default(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    layer_vkCmdDispatchBase_default(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    layer_vkCmdDispatchBaseKHR_default(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset
) {
    layer_vkCmdDispatchIndirect_default(commandBuffer, buffer, offset);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw_default(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance
) {
    layer_vkCmdDraw_default(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed_default(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance
) {
    layer_vkCmdDrawIndexed_default(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirect_default(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirectCount_default(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndexedIndirectCountKHR_default(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndirect_default(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride
) {
    layer_vkCmdDrawIndirectByteCountEXT_default(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndirectCount_default(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    layer_vkCmdDrawIndirectCountKHR_default(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksEXT(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ
) {
    layer_vkCmdDrawMeshTasksEXT_default(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectCountEXT_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectCountEXT(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride
) {
    layer_vkCmdDrawMeshTasksIndirectCountEXT_default(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectEXT_default(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectEXT(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride
) {
    layer_vkCmdDrawMeshTasksIndirectEXT_default(commandBuffer, buffer, offset, drawCount, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawInfoEXT* pVertexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiEXT(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawInfoEXT* pVertexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride
) {
    layer_vkCmdDrawMultiEXT_default(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiIndexedEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawIndexedInfoEXT* pIndexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride,
    const int32_t* pVertexOffset);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiIndexedEXT(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawIndexedInfoEXT* pIndexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride,
    const int32_t* pVertexOffset
) {
    layer_vkCmdDrawMultiIndexedEXT_default(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndConditionalRenderingEXT_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndConditionalRenderingEXT(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndConditionalRenderingEXT_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndDebugUtilsLabelEXT_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQuery_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQuery(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query
) {
    layer_vkCmdEndQuery_default(commandBuffer, queryPool, query);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQueryIndexedEXT_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    uint32_t index);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQueryIndexedEXT(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    uint32_t index
) {
    layer_vkCmdEndQueryIndexedEXT_default(commandBuffer, queryPool, query, index);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRenderPass_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2_default(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdEndRenderPass2_default(commandBuffer, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdEndRenderPass2KHR_default(commandBuffer, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRendering_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering2EXT_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingEndInfoEXT* pRenderingEndInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering2EXT(
    VkCommandBuffer commandBuffer,
    const VkRenderingEndInfoEXT* pRenderingEndInfo
) {
    layer_vkCmdEndRendering2EXT_default(commandBuffer, pRenderingEndInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR(
    VkCommandBuffer commandBuffer
) {
    layer_vkCmdEndRenderingKHR_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndTransformFeedbackEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndTransformFeedbackEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets
) {
    layer_vkCmdEndTransformFeedbackEXT_default(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands_default(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    layer_vkCmdExecuteCommands_default(commandBuffer, commandBufferCount, pCommandBuffers);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteGeneratedCommandsEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 isPreprocessed,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteGeneratedCommandsEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 isPreprocessed,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo
) {
    layer_vkCmdExecuteGeneratedCommandsEXT_default(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer_default(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize size,
    uint32_t data);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize size,
    uint32_t data
) {
    layer_vkCmdFillBuffer_default(commandBuffer, dstBuffer, dstOffset, size, data);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdInsertDebugUtilsLabelEXT_default(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkCmdInsertDebugUtilsLabelEXT_default(commandBuffer, pLabelInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass_default(
    VkCommandBuffer commandBuffer,
    VkSubpassContents contents);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass(
    VkCommandBuffer commandBuffer,
    VkSubpassContents contents
) {
    layer_vkCmdNextSubpass_default(commandBuffer, contents);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2_default(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdNextSubpass2_default(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2KHR(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo
) {
    layer_vkCmdNextSubpass2KHR_default(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier_default(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags srcStageMask,
    VkPipelineStageFlags dstStageMask,
    VkDependencyFlags dependencyFlags,
    uint32_t memoryBarrierCount,
    const VkMemoryBarrier* pMemoryBarriers,
    uint32_t bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier* pBufferMemoryBarriers,
    uint32_t imageMemoryBarrierCount,
    const VkImageMemoryBarrier* pImageMemoryBarriers);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier(
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
    layer_vkCmdPipelineBarrier_default(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2_default(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdPipelineBarrier2_default(commandBuffer, pDependencyInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2KHR(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdPipelineBarrier2KHR_default(commandBuffer, pDependencyInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPreprocessGeneratedCommandsEXT_default(
    VkCommandBuffer commandBuffer,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo,
    VkCommandBuffer stateCommandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPreprocessGeneratedCommandsEXT(
    VkCommandBuffer commandBuffer,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo,
    VkCommandBuffer stateCommandBuffer
) {
    layer_vkCmdPreprocessGeneratedCommandsEXT_default(commandBuffer, pGeneratedCommandsInfo, stateCommandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants_default(
    VkCommandBuffer commandBuffer,
    VkPipelineLayout layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    const void* pValues);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants(
    VkCommandBuffer commandBuffer,
    VkPipelineLayout layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    const void* pValues
) {
    layer_vkCmdPushConstants_default(commandBuffer, layout, stageFlags, offset, size, pValues);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2_default(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo
) {
    layer_vkCmdPushConstants2_default(commandBuffer, pPushConstantsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo
) {
    layer_vkCmdPushConstants2KHR_default(commandBuffer, pPushConstantsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites
) {
    layer_vkCmdPushDescriptorSet_default(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2_default(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    layer_vkCmdPushDescriptorSet2_default(commandBuffer, pPushDescriptorSetInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo
) {
    layer_vkCmdPushDescriptorSet2KHR_default(commandBuffer, pPushDescriptorSetInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetKHR_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetKHR(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites
) {
    layer_vkCmdPushDescriptorSetKHR_default(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate_default(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData
) {
    layer_vkCmdPushDescriptorSetWithTemplate_default(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2_default(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    layer_vkCmdPushDescriptorSetWithTemplate2_default(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo
) {
    layer_vkCmdPushDescriptorSetWithTemplate2KHR_default(commandBuffer, pPushDescriptorSetWithTemplateInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplateKHR_default(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplateKHR(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData
) {
    layer_vkCmdPushDescriptorSetWithTemplateKHR_default(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask
) {
    layer_vkCmdResetEvent_default(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask
) {
    layer_vkCmdResetEvent2_default(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2KHR_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2KHR(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask
) {
    layer_vkCmdResetEvent2KHR_default(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetQueryPool_default(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetQueryPool(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    layer_vkCmdResetQueryPool_default(commandBuffer, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage_default(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageResolve* pRegions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageResolve* pRegions
) {
    layer_vkCmdResolveImage_default(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2_default(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo
) {
    layer_vkCmdResolveImage2_default(commandBuffer, pResolveImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2KHR_default(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo
) {
    layer_vkCmdResolveImage2KHR_default(commandBuffer, pResolveImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToCoverageEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToCoverageEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToCoverageEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToCoverageEnable
) {
    layer_vkCmdSetAlphaToCoverageEnableEXT_default(commandBuffer, alphaToCoverageEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToOneEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToOneEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToOneEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToOneEnable
) {
    layer_vkCmdSetAlphaToOneEnableEXT_default(commandBuffer, alphaToOneEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAttachmentFeedbackLoopEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkImageAspectFlags aspectMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAttachmentFeedbackLoopEnableEXT(
    VkCommandBuffer commandBuffer,
    VkImageAspectFlags aspectMask
) {
    layer_vkCmdSetAttachmentFeedbackLoopEnableEXT_default(commandBuffer, aspectMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetBlendConstants_default(
    VkCommandBuffer commandBuffer,
    const float blendConstants[4]);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetBlendConstants(
    VkCommandBuffer commandBuffer,
    const float blendConstants[4]
) {
    layer_vkCmdSetBlendConstants_default(commandBuffer, blendConstants);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendAdvancedEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendAdvancedEXT* pColorBlendAdvanced);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendAdvancedEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendAdvancedEXT* pColorBlendAdvanced
) {
    layer_vkCmdSetColorBlendAdvancedEXT_default(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEnableEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkBool32* pColorBlendEnables);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEnableEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkBool32* pColorBlendEnables
) {
    layer_vkCmdSetColorBlendEnableEXT_default(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEquationEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendEquationEXT* pColorBlendEquations);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEquationEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendEquationEXT* pColorBlendEquations
) {
    layer_vkCmdSetColorBlendEquationEXT_default(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteEnableEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkBool32* pColorWriteEnables);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteEnableEXT(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkBool32* pColorWriteEnables
) {
    layer_vkCmdSetColorWriteEnableEXT_default(commandBuffer, attachmentCount, pColorWriteEnables);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteMaskEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorComponentFlags* pColorWriteMasks);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteMaskEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorComponentFlags* pColorWriteMasks
) {
    layer_vkCmdSetColorWriteMaskEXT_default(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetConservativeRasterizationModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkConservativeRasterizationModeEXT conservativeRasterizationMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetConservativeRasterizationModeEXT(
    VkCommandBuffer commandBuffer,
    VkConservativeRasterizationModeEXT conservativeRasterizationMode
) {
    layer_vkCmdSetConservativeRasterizationModeEXT_default(commandBuffer, conservativeRasterizationMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationModeNV_default(
    VkCommandBuffer commandBuffer,
    VkCoverageModulationModeNV coverageModulationMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationModeNV(
    VkCommandBuffer commandBuffer,
    VkCoverageModulationModeNV coverageModulationMode
) {
    layer_vkCmdSetCoverageModulationModeNV_default(commandBuffer, coverageModulationMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableEnableNV_default(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageModulationTableEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageModulationTableEnable
) {
    layer_vkCmdSetCoverageModulationTableEnableNV_default(commandBuffer, coverageModulationTableEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableNV_default(
    VkCommandBuffer commandBuffer,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableNV(
    VkCommandBuffer commandBuffer,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable
) {
    layer_vkCmdSetCoverageModulationTableNV_default(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageReductionModeNV_default(
    VkCommandBuffer commandBuffer,
    VkCoverageReductionModeNV coverageReductionMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageReductionModeNV(
    VkCommandBuffer commandBuffer,
    VkCoverageReductionModeNV coverageReductionMode
) {
    layer_vkCmdSetCoverageReductionModeNV_default(commandBuffer, coverageReductionMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorEnableNV_default(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageToColorEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageToColorEnable
) {
    layer_vkCmdSetCoverageToColorEnableNV_default(commandBuffer, coverageToColorEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorLocationNV_default(
    VkCommandBuffer commandBuffer,
    uint32_t coverageToColorLocation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorLocationNV(
    VkCommandBuffer commandBuffer,
    uint32_t coverageToColorLocation
) {
    layer_vkCmdSetCoverageToColorLocationNV_default(commandBuffer, coverageToColorLocation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode_default(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode
) {
    layer_vkCmdSetCullMode_default(commandBuffer, cullMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullModeEXT(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode
) {
    layer_vkCmdSetCullModeEXT_default(commandBuffer, cullMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias_default(
    VkCommandBuffer commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias(
    VkCommandBuffer commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor
) {
    layer_vkCmdSetDepthBias_default(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias2EXT_default(
    VkCommandBuffer commandBuffer,
    const VkDepthBiasInfoEXT* pDepthBiasInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias2EXT(
    VkCommandBuffer commandBuffer,
    const VkDepthBiasInfoEXT* pDepthBiasInfo
) {
    layer_vkCmdSetDepthBias2EXT_default(commandBuffer, pDepthBiasInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable
) {
    layer_vkCmdSetDepthBiasEnable_default(commandBuffer, depthBiasEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable
) {
    layer_vkCmdSetDepthBiasEnableEXT_default(commandBuffer, depthBiasEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBounds_default(
    VkCommandBuffer commandBuffer,
    float minDepthBounds,
    float maxDepthBounds);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBounds(
    VkCommandBuffer commandBuffer,
    float minDepthBounds,
    float maxDepthBounds
) {
    layer_vkCmdSetDepthBounds_default(commandBuffer, minDepthBounds, maxDepthBounds);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable
) {
    layer_vkCmdSetDepthBoundsTestEnable_default(commandBuffer, depthBoundsTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable
) {
    layer_vkCmdSetDepthBoundsTestEnableEXT_default(commandBuffer, depthBoundsTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClampEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClampEnable
) {
    layer_vkCmdSetDepthClampEnableEXT_default(commandBuffer, depthClampEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampRangeEXT_default(
    VkCommandBuffer commandBuffer,
    VkDepthClampModeEXT depthClampMode,
    const VkDepthClampRangeEXT* pDepthClampRange);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampRangeEXT(
    VkCommandBuffer commandBuffer,
    VkDepthClampModeEXT depthClampMode,
    const VkDepthClampRangeEXT* pDepthClampRange
) {
    layer_vkCmdSetDepthClampRangeEXT_default(commandBuffer, depthClampMode, pDepthClampRange);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClipEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClipEnable
) {
    layer_vkCmdSetDepthClipEnableEXT_default(commandBuffer, depthClipEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipNegativeOneToOneEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 negativeOneToOne);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipNegativeOneToOneEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 negativeOneToOne
) {
    layer_vkCmdSetDepthClipNegativeOneToOneEXT_default(commandBuffer, negativeOneToOne);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOp_default(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOp(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp
) {
    layer_vkCmdSetDepthCompareOp_default(commandBuffer, depthCompareOp);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOpEXT_default(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOpEXT(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp
) {
    layer_vkCmdSetDepthCompareOpEXT_default(commandBuffer, depthCompareOp);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable
) {
    layer_vkCmdSetDepthTestEnable_default(commandBuffer, depthTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable
) {
    layer_vkCmdSetDepthTestEnableEXT_default(commandBuffer, depthTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable
) {
    layer_vkCmdSetDepthWriteEnable_default(commandBuffer, depthWriteEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable
) {
    layer_vkCmdSetDepthWriteEnableEXT_default(commandBuffer, depthWriteEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsets2EXT_default(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsets2EXT(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo
) {
    layer_vkCmdSetDescriptorBufferOffsets2EXT_default(commandBuffer, pSetDescriptorBufferOffsetsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsetsEXT_default(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t setCount,
    const uint32_t* pBufferIndices,
    const VkDeviceSize* pOffsets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsetsEXT(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t setCount,
    const uint32_t* pBufferIndices,
    const VkDeviceSize* pOffsets
) {
    layer_vkCmdSetDescriptorBufferOffsetsEXT_default(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMask_default(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMask(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask
) {
    layer_vkCmdSetDeviceMask_default(commandBuffer, deviceMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMaskKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMaskKHR(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask
) {
    layer_vkCmdSetDeviceMaskKHR_default(commandBuffer, deviceMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstDiscardRectangle,
    uint32_t discardRectangleCount,
    const VkRect2D* pDiscardRectangles);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstDiscardRectangle,
    uint32_t discardRectangleCount,
    const VkRect2D* pDiscardRectangles
) {
    layer_vkCmdSetDiscardRectangleEXT_default(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 discardRectangleEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 discardRectangleEnable
) {
    layer_vkCmdSetDiscardRectangleEnableEXT_default(commandBuffer, discardRectangleEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkDiscardRectangleModeEXT discardRectangleMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleModeEXT(
    VkCommandBuffer commandBuffer,
    VkDiscardRectangleModeEXT discardRectangleMode
) {
    layer_vkCmdSetDiscardRectangleModeEXT_default(commandBuffer, discardRectangleMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask
) {
    layer_vkCmdSetEvent_default(commandBuffer, event, stageMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdSetEvent2_default(commandBuffer, event, pDependencyInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2KHR_default(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2KHR(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo
) {
    layer_vkCmdSetEvent2KHR_default(commandBuffer, event, pDependencyInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT_default(
    VkCommandBuffer commandBuffer,
    float extraPrimitiveOverestimationSize);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
    VkCommandBuffer commandBuffer,
    float extraPrimitiveOverestimationSize
) {
    layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT_default(commandBuffer, extraPrimitiveOverestimationSize);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFragmentShadingRateKHR_default(
    VkCommandBuffer commandBuffer,
    const VkExtent2D* pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFragmentShadingRateKHR(
    VkCommandBuffer commandBuffer,
    const VkExtent2D* pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR combinerOps[2]
) {
    layer_vkCmdSetFragmentShadingRateKHR_default(commandBuffer, pFragmentSize, combinerOps);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFace_default(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFace(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace
) {
    layer_vkCmdSetFrontFace_default(commandBuffer, frontFace);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFaceEXT_default(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFaceEXT(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace
) {
    layer_vkCmdSetFrontFaceEXT_default(commandBuffer, frontFace);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineRasterizationModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkLineRasterizationModeEXT lineRasterizationMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineRasterizationModeEXT(
    VkCommandBuffer commandBuffer,
    VkLineRasterizationModeEXT lineRasterizationMode
) {
    layer_vkCmdSetLineRasterizationModeEXT_default(commandBuffer, lineRasterizationMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStipple_default(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStipple(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStipple_default(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEXT(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStippleEXT_default(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 stippledLineEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 stippledLineEnable
) {
    layer_vkCmdSetLineStippleEnableEXT_default(commandBuffer, stippledLineEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleKHR(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern
) {
    layer_vkCmdSetLineStippleKHR_default(commandBuffer, lineStippleFactor, lineStipplePattern);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineWidth_default(
    VkCommandBuffer commandBuffer,
    float lineWidth);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineWidth(
    VkCommandBuffer commandBuffer,
    float lineWidth
) {
    layer_vkCmdSetLineWidth_default(commandBuffer, lineWidth);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEXT_default(
    VkCommandBuffer commandBuffer,
    VkLogicOp logicOp);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEXT(
    VkCommandBuffer commandBuffer,
    VkLogicOp logicOp
) {
    layer_vkCmdSetLogicOpEXT_default(commandBuffer, logicOp);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 logicOpEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 logicOpEnable
) {
    layer_vkCmdSetLogicOpEnableEXT_default(commandBuffer, logicOpEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPatchControlPointsEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t patchControlPoints);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPatchControlPointsEXT(
    VkCommandBuffer commandBuffer,
    uint32_t patchControlPoints
) {
    layer_vkCmdSetPatchControlPointsEXT_default(commandBuffer, patchControlPoints);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPolygonModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkPolygonMode polygonMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPolygonModeEXT(
    VkCommandBuffer commandBuffer,
    VkPolygonMode polygonMode
) {
    layer_vkCmdSetPolygonModeEXT_default(commandBuffer, polygonMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable
) {
    layer_vkCmdSetPrimitiveRestartEnable_default(commandBuffer, primitiveRestartEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable
) {
    layer_vkCmdSetPrimitiveRestartEnableEXT_default(commandBuffer, primitiveRestartEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopology_default(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopology(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology
) {
    layer_vkCmdSetPrimitiveTopology_default(commandBuffer, primitiveTopology);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopologyEXT_default(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopologyEXT(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology
) {
    layer_vkCmdSetPrimitiveTopologyEXT_default(commandBuffer, primitiveTopology);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetProvokingVertexModeEXT_default(
    VkCommandBuffer commandBuffer,
    VkProvokingVertexModeEXT provokingVertexMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetProvokingVertexModeEXT(
    VkCommandBuffer commandBuffer,
    VkProvokingVertexModeEXT provokingVertexMode
) {
    layer_vkCmdSetProvokingVertexModeEXT_default(commandBuffer, provokingVertexMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationSamplesEXT_default(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits rasterizationSamples);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationSamplesEXT(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits rasterizationSamples
) {
    layer_vkCmdSetRasterizationSamplesEXT_default(commandBuffer, rasterizationSamples);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationStreamEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t rasterizationStream);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationStreamEXT(
    VkCommandBuffer commandBuffer,
    uint32_t rasterizationStream
) {
    layer_vkCmdSetRasterizationStreamEXT_default(commandBuffer, rasterizationStream);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable
) {
    layer_vkCmdSetRasterizerDiscardEnable_default(commandBuffer, rasterizerDiscardEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable
) {
    layer_vkCmdSetRasterizerDiscardEnableEXT_default(commandBuffer, rasterizerDiscardEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRayTracingPipelineStackSizeKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t pipelineStackSize);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRayTracingPipelineStackSizeKHR(
    VkCommandBuffer commandBuffer,
    uint32_t pipelineStackSize
) {
    layer_vkCmdSetRayTracingPipelineStackSizeKHR_default(commandBuffer, pipelineStackSize);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocations_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocations(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    layer_vkCmdSetRenderingAttachmentLocations_default(commandBuffer, pLocationInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocationsKHR_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocationsKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo
) {
    layer_vkCmdSetRenderingAttachmentLocationsKHR_default(commandBuffer, pLocationInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndices_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndices(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    layer_vkCmdSetRenderingInputAttachmentIndices_default(commandBuffer, pInputAttachmentIndexInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndicesKHR_default(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndicesKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo
) {
    layer_vkCmdSetRenderingInputAttachmentIndicesKHR_default(commandBuffer, pInputAttachmentIndexInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRepresentativeFragmentTestEnableNV_default(
    VkCommandBuffer commandBuffer,
    VkBool32 representativeFragmentTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRepresentativeFragmentTestEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 representativeFragmentTestEnable
) {
    layer_vkCmdSetRepresentativeFragmentTestEnableNV_default(commandBuffer, representativeFragmentTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEXT_default(
    VkCommandBuffer commandBuffer,
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEXT(
    VkCommandBuffer commandBuffer,
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo
) {
    layer_vkCmdSetSampleLocationsEXT_default(commandBuffer, pSampleLocationsInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 sampleLocationsEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 sampleLocationsEnable
) {
    layer_vkCmdSetSampleLocationsEnableEXT_default(commandBuffer, sampleLocationsEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleMaskEXT_default(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits samples,
    const VkSampleMask* pSampleMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleMaskEXT(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits samples,
    const VkSampleMask* pSampleMask
) {
    layer_vkCmdSetSampleMaskEXT_default(commandBuffer, samples, pSampleMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissor_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissor(
    VkCommandBuffer commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    layer_vkCmdSetScissor_default(commandBuffer, firstScissor, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCount_default(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCount(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    layer_vkCmdSetScissorWithCount_default(commandBuffer, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCountEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors
) {
    layer_vkCmdSetScissorWithCountEXT_default(commandBuffer, scissorCount, pScissors);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetShadingRateImageEnableNV_default(
    VkCommandBuffer commandBuffer,
    VkBool32 shadingRateImageEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetShadingRateImageEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 shadingRateImageEnable
) {
    layer_vkCmdSetShadingRateImageEnableNV_default(commandBuffer, shadingRateImageEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilCompareMask_default(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t compareMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilCompareMask(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t compareMask
) {
    layer_vkCmdSetStencilCompareMask_default(commandBuffer, faceMask, compareMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOp_default(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOp(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
) {
    layer_vkCmdSetStencilOp_default(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOpEXT_default(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOpEXT(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp
) {
    layer_vkCmdSetStencilOpEXT_default(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilReference_default(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t reference);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilReference(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t reference
) {
    layer_vkCmdSetStencilReference_default(commandBuffer, faceMask, reference);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnable_default(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable
) {
    layer_vkCmdSetStencilTestEnable_default(commandBuffer, stencilTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnableEXT_default(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable
) {
    layer_vkCmdSetStencilTestEnableEXT_default(commandBuffer, stencilTestEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilWriteMask_default(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t writeMask);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilWriteMask(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t writeMask
) {
    layer_vkCmdSetStencilWriteMask_default(commandBuffer, faceMask, writeMask);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetTessellationDomainOriginEXT_default(
    VkCommandBuffer commandBuffer,
    VkTessellationDomainOrigin domainOrigin);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetTessellationDomainOriginEXT(
    VkCommandBuffer commandBuffer,
    VkTessellationDomainOrigin domainOrigin
) {
    layer_vkCmdSetTessellationDomainOriginEXT_default(commandBuffer, domainOrigin);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetVertexInputEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetVertexInputEXT(
    VkCommandBuffer commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions
) {
    layer_vkCmdSetVertexInputEXT_default(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewport_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewport(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    layer_vkCmdSetViewport_default(commandBuffer, firstViewport, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportSwizzleNV_default(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewportSwizzleNV* pViewportSwizzles);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportSwizzleNV(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewportSwizzleNV* pViewportSwizzles
) {
    layer_vkCmdSetViewportSwizzleNV_default(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWScalingEnableNV_default(
    VkCommandBuffer commandBuffer,
    VkBool32 viewportWScalingEnable);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWScalingEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 viewportWScalingEnable
) {
    layer_vkCmdSetViewportWScalingEnableNV_default(commandBuffer, viewportWScalingEnable);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCount_default(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCount(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    layer_vkCmdSetViewportWithCount_default(commandBuffer, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCountEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports
) {
    layer_vkCmdSetViewportWithCountEXT_default(commandBuffer, viewportCount, pViewports);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR_default(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress
) {
    layer_vkCmdTraceRaysIndirect2KHR_default(commandBuffer, indirectDeviceAddress);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR_default(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress
) {
    layer_vkCmdTraceRaysIndirectKHR_default(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR_default(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth
) {
    layer_vkCmdTraceRaysKHR_default(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdUpdateBuffer_default(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize dataSize,
    const void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdUpdateBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize dataSize,
    const void* pData
) {
    layer_vkCmdUpdateBuffer_default(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents_default(
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
    const VkImageMemoryBarrier* pImageMemoryBarriers);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents(
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
    layer_vkCmdWaitEvents_default(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2_default(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos
) {
    layer_vkCmdWaitEvents2_default(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2KHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2KHR(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos
) {
    layer_vkCmdWaitEvents2KHR_default(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteAccelerationStructuresPropertiesKHR_default(
    VkCommandBuffer commandBuffer,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteAccelerationStructuresPropertiesKHR(
    VkCommandBuffer commandBuffer,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery
) {
    layer_vkCmdWriteAccelerationStructuresPropertiesKHR_default(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteMicromapsPropertiesEXT_default(
    VkCommandBuffer commandBuffer,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteMicromapsPropertiesEXT(
    VkCommandBuffer commandBuffer,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery
) {
    layer_vkCmdWriteMicromapsPropertiesEXT_default(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp_default(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlagBits pipelineStage,
    VkQueryPool queryPool,
    uint32_t query);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlagBits pipelineStage,
    VkQueryPool queryPool,
    uint32_t query
) {
    layer_vkCmdWriteTimestamp_default(commandBuffer, pipelineStage, queryPool, query);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2_default(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query
) {
    layer_vkCmdWriteTimestamp2_default(commandBuffer, stage, queryPool, query);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2KHR_default(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2KHR(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query
) {
    layer_vkCmdWriteTimestamp2KHR_default(commandBuffer, stage, queryPool, query);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureKHR_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureInfoKHR* pInfo
) {
    return layer_vkCopyAccelerationStructureKHR_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureToMemoryKHR_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureToMemoryKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo
) {
    return layer_vkCopyAccelerationStructureToMemoryKHR_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImage_default(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImage(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    return layer_vkCopyImageToImage_default(device, pCopyImageToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImageEXT_default(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImageEXT(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo
) {
    return layer_vkCopyImageToImageEXT_default(device, pCopyImageToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemory_default(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemory(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    return layer_vkCopyImageToMemory_default(device, pCopyImageToMemoryInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemoryEXT_default(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemoryEXT(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo
) {
    return layer_vkCopyImageToMemoryEXT_default(device, pCopyImageToMemoryInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToAccelerationStructureKHR_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToAccelerationStructureKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo
) {
    return layer_vkCopyMemoryToAccelerationStructureKHR_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImage_default(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImage(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    return layer_vkCopyMemoryToImage_default(device, pCopyMemoryToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImageEXT_default(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImageEXT(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo
) {
    return layer_vkCopyMemoryToImageEXT_default(device, pCopyMemoryToImageInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToMicromapEXT_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToMicromapEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT* pInfo
) {
    return layer_vkCopyMemoryToMicromapEXT_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapEXT_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapInfoEXT* pInfo
) {
    return layer_vkCopyMicromapEXT_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapToMemoryEXT_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapToMemoryEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT* pInfo
) {
    return layer_vkCopyMicromapToMemoryEXT_default(device, deferredOperation, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAccelerationStructureKHR_default(
    VkDevice device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkAccelerationStructureKHR* pAccelerationStructure);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAccelerationStructureKHR(
    VkDevice device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkAccelerationStructureKHR* pAccelerationStructure
) {
    return layer_vkCreateAccelerationStructureKHR_default(device, pCreateInfo, pAllocator, pAccelerationStructure);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBuffer_default(
    VkDevice device,
    const VkBufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBuffer* pBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBuffer(
    VkDevice device,
    const VkBufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBuffer* pBuffer
) {
    return layer_vkCreateBuffer_default(device, pCreateInfo, pAllocator, pBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBufferView_default(
    VkDevice device,
    const VkBufferViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBufferView* pView);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBufferView(
    VkDevice device,
    const VkBufferViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBufferView* pView
) {
    return layer_vkCreateBufferView_default(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool_default(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool
) {
    return layer_vkCreateCommandPool_default(device, pCreateInfo, pAllocator, pCommandPool);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines_default(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkComputePipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkComputePipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    return layer_vkCreateComputePipelines_default(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDeferredOperationKHR_default(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator,
    VkDeferredOperationKHR* pDeferredOperation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDeferredOperationKHR(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator,
    VkDeferredOperationKHR* pDeferredOperation
) {
    return layer_vkCreateDeferredOperationKHR_default(device, pAllocator, pDeferredOperation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorPool_default(
    VkDevice device,
    const VkDescriptorPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorPool* pDescriptorPool);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorPool(
    VkDevice device,
    const VkDescriptorPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorPool* pDescriptorPool
) {
    return layer_vkCreateDescriptorPool_default(device, pCreateInfo, pAllocator, pDescriptorPool);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorSetLayout_default(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorSetLayout* pSetLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorSetLayout(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorSetLayout* pSetLayout
) {
    return layer_vkCreateDescriptorSetLayout_default(device, pCreateInfo, pAllocator, pSetLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplate_default(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplate(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    return layer_vkCreateDescriptorUpdateTemplate_default(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplateKHR_default(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplateKHR(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate
) {
    return layer_vkCreateDescriptorUpdateTemplateKHR_default(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateEvent_default(
    VkDevice device,
    const VkEventCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkEvent* pEvent);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateEvent(
    VkDevice device,
    const VkEventCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkEvent* pEvent
) {
    return layer_vkCreateEvent_default(device, pCreateInfo, pAllocator, pEvent);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFence_default(
    VkDevice device,
    const VkFenceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFence(
    VkDevice device,
    const VkFenceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    return layer_vkCreateFence_default(device, pCreateInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFramebuffer_default(
    VkDevice device,
    const VkFramebufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFramebuffer* pFramebuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFramebuffer(
    VkDevice device,
    const VkFramebufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFramebuffer* pFramebuffer
) {
    return layer_vkCreateFramebuffer_default(device, pCreateInfo, pAllocator, pFramebuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateGraphicsPipelines_default(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkGraphicsPipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateGraphicsPipelines(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkGraphicsPipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    return layer_vkCreateGraphicsPipelines_default(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage_default(
    VkDevice device,
    const VkImageCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImage* pImage);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage(
    VkDevice device,
    const VkImageCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImage* pImage
) {
    return layer_vkCreateImage_default(device, pCreateInfo, pAllocator, pImage);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImageView_default(
    VkDevice device,
    const VkImageViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImageView* pView);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImageView(
    VkDevice device,
    const VkImageViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImageView* pView
) {
    return layer_vkCreateImageView_default(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectCommandsLayoutEXT_default(
    VkDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectCommandsLayoutEXT(
    VkDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout
) {
    return layer_vkCreateIndirectCommandsLayoutEXT_default(device, pCreateInfo, pAllocator, pIndirectCommandsLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectExecutionSetEXT_default(
    VkDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectExecutionSetEXT* pIndirectExecutionSet);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectExecutionSetEXT(
    VkDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectExecutionSetEXT* pIndirectExecutionSet
) {
    return layer_vkCreateIndirectExecutionSetEXT_default(device, pCreateInfo, pAllocator, pIndirectExecutionSet);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateMicromapEXT_default(
    VkDevice device,
    const VkMicromapCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkMicromapEXT* pMicromap);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateMicromapEXT(
    VkDevice device,
    const VkMicromapCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkMicromapEXT* pMicromap
) {
    return layer_vkCreateMicromapEXT_default(device, pCreateInfo, pAllocator, pMicromap);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineBinariesKHR_default(
    VkDevice device,
    const VkPipelineBinaryCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineBinaryHandlesInfoKHR* pBinaries);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineBinariesKHR(
    VkDevice device,
    const VkPipelineBinaryCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineBinaryHandlesInfoKHR* pBinaries
) {
    return layer_vkCreatePipelineBinariesKHR_default(device, pCreateInfo, pAllocator, pBinaries);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineCache_default(
    VkDevice device,
    const VkPipelineCacheCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineCache* pPipelineCache);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineCache(
    VkDevice device,
    const VkPipelineCacheCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineCache* pPipelineCache
) {
    return layer_vkCreatePipelineCache_default(device, pCreateInfo, pAllocator, pPipelineCache);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineLayout_default(
    VkDevice device,
    const VkPipelineLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineLayout* pPipelineLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineLayout(
    VkDevice device,
    const VkPipelineLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineLayout* pPipelineLayout
) {
    return layer_vkCreatePipelineLayout_default(device, pCreateInfo, pAllocator, pPipelineLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlot_default(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlot(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot
) {
    return layer_vkCreatePrivateDataSlot_default(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlotEXT_default(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlotEXT(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot
) {
    return layer_vkCreatePrivateDataSlotEXT_default(device, pCreateInfo, pAllocator, pPrivateDataSlot);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateQueryPool_default(
    VkDevice device,
    const VkQueryPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkQueryPool* pQueryPool);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateQueryPool(
    VkDevice device,
    const VkQueryPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkQueryPool* pQueryPool
) {
    return layer_vkCreateQueryPool_default(device, pCreateInfo, pAllocator, pQueryPool);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRayTracingPipelinesKHR_default(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRayTracingPipelinesKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines
) {
    return layer_vkCreateRayTracingPipelinesKHR_default(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass_default(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    return layer_vkCreateRenderPass_default(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2_default(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    return layer_vkCreateRenderPass2_default(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR_default(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass
) {
    return layer_vkCreateRenderPass2KHR_default(device, pCreateInfo, pAllocator, pRenderPass);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSampler_default(
    VkDevice device,
    const VkSamplerCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSampler* pSampler);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSampler(
    VkDevice device,
    const VkSamplerCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSampler* pSampler
) {
    return layer_vkCreateSampler_default(device, pCreateInfo, pAllocator, pSampler);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversion_default(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversion(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion
) {
    return layer_vkCreateSamplerYcbcrConversion_default(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversionKHR_default(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversionKHR(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion
) {
    return layer_vkCreateSamplerYcbcrConversionKHR_default(device, pCreateInfo, pAllocator, pYcbcrConversion);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSemaphore_default(
    VkDevice device,
    const VkSemaphoreCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSemaphore* pSemaphore);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSemaphore(
    VkDevice device,
    const VkSemaphoreCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSemaphore* pSemaphore
) {
    return layer_vkCreateSemaphore_default(device, pCreateInfo, pAllocator, pSemaphore);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule_default(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkShaderModule* pShaderModule);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkShaderModule* pShaderModule
) {
    return layer_vkCreateShaderModule_default(device, pCreateInfo, pAllocator, pShaderModule);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT_default(
    VkDevice device,
    uint32_t createInfoCount,
    const VkShaderCreateInfoEXT* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkShaderEXT* pShaders);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT(
    VkDevice device,
    uint32_t createInfoCount,
    const VkShaderCreateInfoEXT* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkShaderEXT* pShaders
) {
    return layer_vkCreateShadersEXT_default(device, createInfoCount, pCreateInfos, pAllocator, pShaders);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSharedSwapchainsKHR_default(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchains);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSharedSwapchainsKHR(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchains
) {
    return layer_vkCreateSharedSwapchainsKHR_default(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR_default(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain
) {
    return layer_vkCreateSwapchainKHR_default(device, pCreateInfo, pAllocator, pSwapchain);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorARM_default(
    VkDevice device,
    const VkTensorCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorARM* pTensor);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorARM(
    VkDevice device,
    const VkTensorCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorARM* pTensor
) {
    return layer_vkCreateTensorARM_default(device, pCreateInfo, pAllocator, pTensor);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorViewARM_default(
    VkDevice device,
    const VkTensorViewCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorViewARM* pView);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorViewARM(
    VkDevice device,
    const VkTensorViewCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorViewARM* pView
) {
    return layer_vkCreateTensorViewARM_default(device, pCreateInfo, pAllocator, pView);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateValidationCacheEXT_default(
    VkDevice device,
    const VkValidationCacheCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkValidationCacheEXT* pValidationCache);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateValidationCacheEXT(
    VkDevice device,
    const VkValidationCacheCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkValidationCacheEXT* pValidationCache
) {
    return layer_vkCreateValidationCacheEXT_default(device, pCreateInfo, pAllocator, pValidationCache);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectNameEXT_default(
    VkDevice device,
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectNameEXT(
    VkDevice device,
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo
) {
    return layer_vkDebugMarkerSetObjectNameEXT_default(device, pNameInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectTagEXT_default(
    VkDevice device,
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectTagEXT(
    VkDevice device,
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo
) {
    return layer_vkDebugMarkerSetObjectTagEXT_default(device, pTagInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeferredOperationJoinKHR_default(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeferredOperationJoinKHR(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    return layer_vkDeferredOperationJoinKHR_default(device, operation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyAccelerationStructureKHR_default(
    VkDevice device,
    VkAccelerationStructureKHR accelerationStructure,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyAccelerationStructureKHR(
    VkDevice device,
    VkAccelerationStructureKHR accelerationStructure,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyAccelerationStructureKHR_default(device, accelerationStructure, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBuffer_default(
    VkDevice device,
    VkBuffer buffer,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBuffer(
    VkDevice device,
    VkBuffer buffer,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyBuffer_default(device, buffer, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBufferView_default(
    VkDevice device,
    VkBufferView bufferView,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBufferView(
    VkDevice device,
    VkBufferView bufferView,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyBufferView_default(device, bufferView, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool_default(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyCommandPool_default(device, commandPool, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDeferredOperationKHR_default(
    VkDevice device,
    VkDeferredOperationKHR operation,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDeferredOperationKHR(
    VkDevice device,
    VkDeferredOperationKHR operation,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDeferredOperationKHR_default(device, operation, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorPool_default(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorPool(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorPool_default(device, descriptorPool, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorSetLayout_default(
    VkDevice device,
    VkDescriptorSetLayout descriptorSetLayout,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorSetLayout(
    VkDevice device,
    VkDescriptorSetLayout descriptorSetLayout,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorSetLayout_default(device, descriptorSetLayout, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplate_default(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplate(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorUpdateTemplate_default(device, descriptorUpdateTemplate, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplateKHR_default(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplateKHR(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDescriptorUpdateTemplateKHR_default(device, descriptorUpdateTemplate, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice_default(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDevice_default(device, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyEvent_default(
    VkDevice device,
    VkEvent event,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyEvent(
    VkDevice device,
    VkEvent event,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyEvent_default(device, event, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFence_default(
    VkDevice device,
    VkFence fence,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFence(
    VkDevice device,
    VkFence fence,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyFence_default(device, fence, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFramebuffer_default(
    VkDevice device,
    VkFramebuffer framebuffer,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFramebuffer(
    VkDevice device,
    VkFramebuffer framebuffer,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyFramebuffer_default(device, framebuffer, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImage_default(
    VkDevice device,
    VkImage image,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImage(
    VkDevice device,
    VkImage image,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyImage_default(device, image, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImageView_default(
    VkDevice device,
    VkImageView imageView,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImageView(
    VkDevice device,
    VkImageView imageView,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyImageView_default(device, imageView, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectCommandsLayoutEXT_default(
    VkDevice device,
    VkIndirectCommandsLayoutEXT indirectCommandsLayout,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectCommandsLayoutEXT(
    VkDevice device,
    VkIndirectCommandsLayoutEXT indirectCommandsLayout,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyIndirectCommandsLayoutEXT_default(device, indirectCommandsLayout, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectExecutionSetEXT_default(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectExecutionSetEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyIndirectExecutionSetEXT_default(device, indirectExecutionSet, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyMicromapEXT_default(
    VkDevice device,
    VkMicromapEXT micromap,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyMicromapEXT(
    VkDevice device,
    VkMicromapEXT micromap,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyMicromapEXT_default(device, micromap, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipeline_default(
    VkDevice device,
    VkPipeline pipeline,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipeline(
    VkDevice device,
    VkPipeline pipeline,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipeline_default(device, pipeline, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineBinaryKHR_default(
    VkDevice device,
    VkPipelineBinaryKHR pipelineBinary,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineBinaryKHR(
    VkDevice device,
    VkPipelineBinaryKHR pipelineBinary,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineBinaryKHR_default(device, pipelineBinary, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineCache_default(
    VkDevice device,
    VkPipelineCache pipelineCache,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineCache(
    VkDevice device,
    VkPipelineCache pipelineCache,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineCache_default(device, pipelineCache, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineLayout_default(
    VkDevice device,
    VkPipelineLayout pipelineLayout,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineLayout(
    VkDevice device,
    VkPipelineLayout pipelineLayout,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPipelineLayout_default(device, pipelineLayout, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlot_default(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlot(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPrivateDataSlot_default(device, privateDataSlot, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlotEXT_default(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlotEXT(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyPrivateDataSlotEXT_default(device, privateDataSlot, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyQueryPool_default(
    VkDevice device,
    VkQueryPool queryPool,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyQueryPool(
    VkDevice device,
    VkQueryPool queryPool,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyQueryPool_default(device, queryPool, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass_default(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyRenderPass_default(device, renderPass, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySampler_default(
    VkDevice device,
    VkSampler sampler,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySampler(
    VkDevice device,
    VkSampler sampler,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySampler_default(device, sampler, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversion_default(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversion(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySamplerYcbcrConversion_default(device, ycbcrConversion, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversionKHR_default(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversionKHR(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySamplerYcbcrConversionKHR_default(device, ycbcrConversion, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySemaphore_default(
    VkDevice device,
    VkSemaphore semaphore,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySemaphore(
    VkDevice device,
    VkSemaphore semaphore,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySemaphore_default(device, semaphore, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderEXT_default(
    VkDevice device,
    VkShaderEXT shader,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderEXT(
    VkDevice device,
    VkShaderEXT shader,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyShaderEXT_default(device, shader, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderModule_default(
    VkDevice device,
    VkShaderModule shaderModule,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderModule(
    VkDevice device,
    VkShaderModule shaderModule,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyShaderModule_default(device, shaderModule, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySwapchainKHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySwapchainKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySwapchainKHR_default(device, swapchain, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorARM_default(
    VkDevice device,
    VkTensorARM tensor,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorARM(
    VkDevice device,
    VkTensorARM tensor,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyTensorARM_default(device, tensor, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorViewARM_default(
    VkDevice device,
    VkTensorViewARM tensorView,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorViewARM(
    VkDevice device,
    VkTensorViewARM tensorView,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyTensorViewARM_default(device, tensorView, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyValidationCacheEXT_default(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyValidationCacheEXT(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyValidationCacheEXT_default(device, validationCache, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeviceWaitIdle_default(
    VkDevice device);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeviceWaitIdle(
    VkDevice device
) {
    return layer_vkDeviceWaitIdle_default(device);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDisplayPowerControlEXT_default(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDisplayPowerControlEXT(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo
) {
    return layer_vkDisplayPowerControlEXT_default(device, display, pDisplayPowerInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEndCommandBuffer_default(
    VkCommandBuffer commandBuffer);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEndCommandBuffer(
    VkCommandBuffer commandBuffer
) {
    return layer_vkEndCommandBuffer_default(commandBuffer);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFlushMappedMemoryRanges_default(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFlushMappedMemoryRanges(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges
) {
    return layer_vkFlushMappedMemoryRanges_default(device, memoryRangeCount, pMemoryRanges);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers_default(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers
) {
    layer_vkFreeCommandBuffers_default(device, commandPool, commandBufferCount, pCommandBuffers);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFreeDescriptorSets_default(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFreeDescriptorSets(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets
) {
    return layer_vkFreeDescriptorSets_default(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkFreeMemory_default(
    VkDevice device,
    VkDeviceMemory memory,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeMemory(
    VkDevice device,
    VkDeviceMemory memory,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkFreeMemory_default(device, memory, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetAccelerationStructureBuildSizesKHR_default(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t* pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetAccelerationStructureBuildSizesKHR(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t* pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo
) {
    layer_vkGetAccelerationStructureBuildSizesKHR_default(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetAccelerationStructureDeviceAddressKHR_default(
    VkDevice device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetAccelerationStructureDeviceAddressKHR(
    VkDevice device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo
) {
    return layer_vkGetAccelerationStructureDeviceAddressKHR_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT_default(
    VkDevice device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    return layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddress_default(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddress(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    return layer_vkGetBufferDeviceAddress_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressEXT_default(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressEXT(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    return layer_vkGetBufferDeviceAddressEXT_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressKHR_default(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressKHR(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    return layer_vkGetBufferDeviceAddressKHR_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements_default(
    VkDevice device,
    VkBuffer buffer,
    VkMemoryRequirements* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements(
    VkDevice device,
    VkBuffer buffer,
    VkMemoryRequirements* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements_default(device, buffer, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2_default(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements2_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2KHR_default(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2KHR(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetBufferMemoryRequirements2KHR_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddress_default(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddress(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    return layer_vkGetBufferOpaqueCaptureAddress_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddressKHR_default(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddressKHR(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo
) {
    return layer_vkGetBufferOpaqueCaptureAddressKHR_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetBufferOpaqueCaptureDescriptorDataEXT_default(
    VkDevice device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetBufferOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    return layer_vkGetBufferOpaqueCaptureDescriptorDataEXT_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsEXT_default(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsEXT(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation
) {
    return layer_vkGetCalibratedTimestampsEXT_default(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsKHR_default(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsKHR(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation
) {
    return layer_vkGetCalibratedTimestampsKHR_default(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR uint32_t VKAPI_CALL layer_vkGetDeferredOperationMaxConcurrencyKHR_default(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR uint32_t VKAPI_CALL layer_vkGetDeferredOperationMaxConcurrencyKHR(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    return layer_vkGetDeferredOperationMaxConcurrencyKHR_default(device, operation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeferredOperationResultKHR_default(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeferredOperationResultKHR(
    VkDevice device,
    VkDeferredOperationKHR operation
) {
    return layer_vkGetDeferredOperationResultKHR_default(device, operation);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorEXT_default(
    VkDevice device,
    const VkDescriptorGetInfoEXT* pDescriptorInfo,
    size_t dataSize,
    void* pDescriptor);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorEXT(
    VkDevice device,
    const VkDescriptorGetInfoEXT* pDescriptorInfo,
    size_t dataSize,
    void* pDescriptor
) {
    layer_vkGetDescriptorEXT_default(device, pDescriptorInfo, dataSize, pDescriptor);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutBindingOffsetEXT_default(
    VkDevice device,
    VkDescriptorSetLayout layout,
    uint32_t binding,
    VkDeviceSize* pOffset);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutBindingOffsetEXT(
    VkDevice device,
    VkDescriptorSetLayout layout,
    uint32_t binding,
    VkDeviceSize* pOffset
) {
    layer_vkGetDescriptorSetLayoutBindingOffsetEXT_default(device, layout, binding, pOffset);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSizeEXT_default(
    VkDevice device,
    VkDescriptorSetLayout layout,
    VkDeviceSize* pLayoutSizeInBytes);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSizeEXT(
    VkDevice device,
    VkDescriptorSetLayout layout,
    VkDeviceSize* pLayoutSizeInBytes
) {
    layer_vkGetDescriptorSetLayoutSizeEXT_default(device, layout, pLayoutSizeInBytes);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupport_default(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupport(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport
) {
    layer_vkGetDescriptorSetLayoutSupport_default(device, pCreateInfo, pSupport);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupportKHR_default(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupportKHR(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport
) {
    layer_vkGetDescriptorSetLayoutSupportKHR_default(device, pCreateInfo, pSupport);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceAccelerationStructureCompatibilityKHR_default(
    VkDevice device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceAccelerationStructureCompatibilityKHR(
    VkDevice device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    layer_vkGetDeviceAccelerationStructureCompatibilityKHR_default(device, pVersionInfo, pCompatibility);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirements_default(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirements(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceBufferMemoryRequirements_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirementsKHR_default(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceBufferMemoryRequirementsKHR_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceFaultInfoEXT_default(
    VkDevice device,
    VkDeviceFaultCountsEXT* pFaultCounts,
    VkDeviceFaultInfoEXT* pFaultInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceFaultInfoEXT(
    VkDevice device,
    VkDeviceFaultCountsEXT* pFaultCounts,
    VkDeviceFaultInfoEXT* pFaultInfo
) {
    return layer_vkGetDeviceFaultInfoEXT_default(device, pFaultCounts, pFaultInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeatures_default(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeatures(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    layer_vkGetDeviceGroupPeerMemoryFeatures_default(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeaturesKHR_default(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeaturesKHR(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures
) {
    layer_vkGetDeviceGroupPeerMemoryFeaturesKHR_default(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupPresentCapabilitiesKHR_default(
    VkDevice device,
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupPresentCapabilitiesKHR(
    VkDevice device,
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities
) {
    return layer_vkGetDeviceGroupPresentCapabilitiesKHR_default(device, pDeviceGroupPresentCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupSurfacePresentModesKHR_default(
    VkDevice device,
    VkSurfaceKHR surface,
    VkDeviceGroupPresentModeFlagsKHR* pModes);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupSurfacePresentModesKHR(
    VkDevice device,
    VkSurfaceKHR surface,
    VkDeviceGroupPresentModeFlagsKHR* pModes
) {
    return layer_vkGetDeviceGroupSurfacePresentModesKHR_default(device, surface, pModes);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirements_default(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirements(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceImageMemoryRequirements_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR_default(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceImageMemoryRequirementsKHR_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirements_default(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirements(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetDeviceImageSparseMemoryRequirements_default(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirementsKHR_default(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetDeviceImageSparseMemoryRequirementsKHR_default(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayout_default(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayout(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout
) {
    layer_vkGetDeviceImageSubresourceLayout_default(device, pInfo, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayoutKHR_default(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayoutKHR(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout
) {
    layer_vkGetDeviceImageSubresourceLayoutKHR_default(device, pInfo, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMemoryCommitment_default(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize* pCommittedMemoryInBytes);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMemoryCommitment(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize* pCommittedMemoryInBytes
) {
    layer_vkGetDeviceMemoryCommitment_default(device, memory, pCommittedMemoryInBytes);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddress_default(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddress(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    return layer_vkGetDeviceMemoryOpaqueCaptureAddress_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR_default(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo
) {
    return layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR_default(device, pInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMicromapCompatibilityEXT_default(
    VkDevice device,
    const VkMicromapVersionInfoEXT* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMicromapCompatibilityEXT(
    VkDevice device,
    const VkMicromapVersionInfoEXT* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility
) {
    layer_vkGetDeviceMicromapCompatibilityEXT_default(device, pVersionInfo, pCompatibility);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetDeviceProcAddr_default(
    VkDevice device,
    const char* pName);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName
) {
    return layer_vkGetDeviceProcAddr_default(device, pName);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue_default(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue
) {
    layer_vkGetDeviceQueue_default(device, queueFamilyIndex, queueIndex, pQueue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue2_default(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue2(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue
) {
    layer_vkGetDeviceQueue2_default(device, pQueueInfo, pQueue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceTensorMemoryRequirementsARM_default(
    VkDevice device,
    const VkDeviceTensorMemoryRequirementsARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceTensorMemoryRequirementsARM(
    VkDevice device,
    const VkDeviceTensorMemoryRequirementsARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetDeviceTensorMemoryRequirementsARM_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetEventStatus_default(
    VkDevice device,
    VkEvent event);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetEventStatus(
    VkDevice device,
    VkEvent event
) {
    return layer_vkGetEventStatus_default(device, event);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceFdKHR_default(
    VkDevice device,
    const VkFenceGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceFdKHR(
    VkDevice device,
    const VkFenceGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    return layer_vkGetFenceFdKHR_default(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceStatus_default(
    VkDevice device,
    VkFence fence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceStatus(
    VkDevice device,
    VkFence fence
) {
    return layer_vkGetFenceStatus_default(device, fence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetGeneratedCommandsMemoryRequirementsEXT_default(
    VkDevice device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetGeneratedCommandsMemoryRequirementsEXT(
    VkDevice device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetGeneratedCommandsMemoryRequirementsEXT_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageDrmFormatModifierPropertiesEXT_default(
    VkDevice device,
    VkImage image,
    VkImageDrmFormatModifierPropertiesEXT* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageDrmFormatModifierPropertiesEXT(
    VkDevice device,
    VkImage image,
    VkImageDrmFormatModifierPropertiesEXT* pProperties
) {
    return layer_vkGetImageDrmFormatModifierPropertiesEXT_default(device, image, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements_default(
    VkDevice device,
    VkImage image,
    VkMemoryRequirements* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements(
    VkDevice device,
    VkImage image,
    VkMemoryRequirements* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements_default(device, image, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2_default(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements2_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2KHR_default(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2KHR(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetImageMemoryRequirements2KHR_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageOpaqueCaptureDescriptorDataEXT_default(
    VkDevice device,
    const VkImageCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkImageCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    return layer_vkGetImageOpaqueCaptureDescriptorDataEXT_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements_default(
    VkDevice device,
    VkImage image,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements(
    VkDevice device,
    VkImage image,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements_default(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2_default(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements2_default(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2KHR_default(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2KHR(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements
) {
    layer_vkGetImageSparseMemoryRequirements2KHR_default(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout_default(
    VkDevice device,
    VkImage image,
    const VkImageSubresource* pSubresource,
    VkSubresourceLayout* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout(
    VkDevice device,
    VkImage image,
    const VkImageSubresource* pSubresource,
    VkSubresourceLayout* pLayout
) {
    layer_vkGetImageSubresourceLayout_default(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2_default(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2_default(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2EXT_default(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2EXT(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2EXT_default(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2KHR_default(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2KHR(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout
) {
    layer_vkGetImageSubresourceLayout2KHR_default(device, image, pSubresource, pLayout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT_default(
    VkDevice device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    return layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdKHR_default(
    VkDevice device,
    const VkMemoryGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdKHR(
    VkDevice device,
    const VkMemoryGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    return layer_vkGetMemoryFdKHR_default(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdPropertiesKHR_default(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    int fd,
    VkMemoryFdPropertiesKHR* pMemoryFdProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdPropertiesKHR(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    int fd,
    VkMemoryFdPropertiesKHR* pMemoryFdProperties
) {
    return layer_vkGetMemoryFdPropertiesKHR_default(device, handleType, fd, pMemoryFdProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryHostPointerPropertiesEXT_default(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    const void* pHostPointer,
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryHostPointerPropertiesEXT(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    const void* pHostPointer,
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties
) {
    return layer_vkGetMemoryHostPointerPropertiesEXT_default(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetMicromapBuildSizesEXT_default(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkMicromapBuildInfoEXT* pBuildInfo,
    VkMicromapBuildSizesInfoEXT* pSizeInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetMicromapBuildSizesEXT(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkMicromapBuildInfoEXT* pBuildInfo,
    VkMicromapBuildSizesInfoEXT* pSizeInfo
) {
    layer_vkGetMicromapBuildSizesEXT_default(device, buildType, pBuildInfo, pSizeInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineBinaryDataKHR_default(
    VkDevice device,
    const VkPipelineBinaryDataInfoKHR* pInfo,
    VkPipelineBinaryKeyKHR* pPipelineBinaryKey,
    size_t* pPipelineBinaryDataSize,
    void* pPipelineBinaryData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineBinaryDataKHR(
    VkDevice device,
    const VkPipelineBinaryDataInfoKHR* pInfo,
    VkPipelineBinaryKeyKHR* pPipelineBinaryKey,
    size_t* pPipelineBinaryDataSize,
    void* pPipelineBinaryData
) {
    return layer_vkGetPipelineBinaryDataKHR_default(device, pInfo, pPipelineBinaryKey, pPipelineBinaryDataSize, pPipelineBinaryData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineCacheData_default(
    VkDevice device,
    VkPipelineCache pipelineCache,
    size_t* pDataSize,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineCacheData(
    VkDevice device,
    VkPipelineCache pipelineCache,
    size_t* pDataSize,
    void* pData
) {
    return layer_vkGetPipelineCacheData_default(device, pipelineCache, pDataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableInternalRepresentationsKHR_default(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableInternalRepresentationsKHR(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations
) {
    return layer_vkGetPipelineExecutableInternalRepresentationsKHR_default(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutablePropertiesKHR_default(
    VkDevice device,
    const VkPipelineInfoKHR* pPipelineInfo,
    uint32_t* pExecutableCount,
    VkPipelineExecutablePropertiesKHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutablePropertiesKHR(
    VkDevice device,
    const VkPipelineInfoKHR* pPipelineInfo,
    uint32_t* pExecutableCount,
    VkPipelineExecutablePropertiesKHR* pProperties
) {
    return layer_vkGetPipelineExecutablePropertiesKHR_default(device, pPipelineInfo, pExecutableCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableStatisticsKHR_default(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pStatisticCount,
    VkPipelineExecutableStatisticKHR* pStatistics);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableStatisticsKHR(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pStatisticCount,
    VkPipelineExecutableStatisticKHR* pStatistics
) {
    return layer_vkGetPipelineExecutableStatisticsKHR_default(device, pExecutableInfo, pStatisticCount, pStatistics);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR_default(
    VkDevice device,
    const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR* pPipelineKey);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR(
    VkDevice device,
    const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR* pPipelineKey
) {
    return layer_vkGetPipelineKeyKHR_default(device, pPipelineCreateInfo, pPipelineKey);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelinePropertiesEXT_default(
    VkDevice device,
    const VkPipelineInfoEXT* pPipelineInfo,
    VkBaseOutStructure* pPipelineProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelinePropertiesEXT(
    VkDevice device,
    const VkPipelineInfoEXT* pPipelineInfo,
    VkBaseOutStructure* pPipelineProperties
) {
    return layer_vkGetPipelinePropertiesEXT_default(device, pPipelineInfo, pPipelineProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateData_default(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateData(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData
) {
    layer_vkGetPrivateData_default(device, objectType, objectHandle, privateDataSlot, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateDataEXT_default(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateDataEXT(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData
) {
    layer_vkGetPrivateDataEXT_default(device, objectType, objectHandle, privateDataSlot, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetQueryPoolResults_default(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    size_t dataSize,
    void* pData,
    VkDeviceSize stride,
    VkQueryResultFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetQueryPoolResults(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    size_t dataSize,
    void* pData,
    VkDeviceSize stride,
    VkQueryResultFlags flags
) {
    return layer_vkGetQueryPoolResults_default(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR_default(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData
) {
    return layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR_default(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingShaderGroupHandlesKHR_default(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingShaderGroupHandlesKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData
) {
    return layer_vkGetRayTracingShaderGroupHandlesKHR_default(device, pipeline, firstGroup, groupCount, dataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkDeviceSize VKAPI_CALL layer_vkGetRayTracingShaderGroupStackSizeKHR_default(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t group,
    VkShaderGroupShaderKHR groupShader);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkDeviceSize VKAPI_CALL layer_vkGetRayTracingShaderGroupStackSizeKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t group,
    VkShaderGroupShaderKHR groupShader
) {
    return layer_vkGetRayTracingShaderGroupStackSizeKHR_default(device, pipeline, group, groupShader);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderAreaGranularity_default(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D* pGranularity);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderAreaGranularity(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D* pGranularity
) {
    layer_vkGetRenderAreaGranularity_default(device, renderPass, pGranularity);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularity_default(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularity(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity
) {
    layer_vkGetRenderingAreaGranularity_default(device, pRenderingAreaInfo, pGranularity);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularityKHR_default(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularityKHR(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity
) {
    layer_vkGetRenderingAreaGranularityKHR_default(device, pRenderingAreaInfo, pGranularity);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT_default(
    VkDevice device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void* pData
) {
    return layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValue_default(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValue(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue
) {
    return layer_vkGetSemaphoreCounterValue_default(device, semaphore, pValue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValueKHR_default(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValueKHR(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue
) {
    return layer_vkGetSemaphoreCounterValueKHR_default(device, semaphore, pValue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreFdKHR_default(
    VkDevice device,
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreFdKHR(
    VkDevice device,
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
    int* pFd
) {
    return layer_vkGetSemaphoreFdKHR_default(device, pGetFdInfo, pFd);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetShaderBinaryDataEXT_default(
    VkDevice device,
    VkShaderEXT shader,
    size_t* pDataSize,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetShaderBinaryDataEXT(
    VkDevice device,
    VkShaderEXT shader,
    size_t* pDataSize,
    void* pData
) {
    return layer_vkGetShaderBinaryDataEXT_default(device, shader, pDataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleCreateInfoIdentifierEXT_default(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    VkShaderModuleIdentifierEXT* pIdentifier);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleCreateInfoIdentifierEXT(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    VkShaderModuleIdentifierEXT* pIdentifier
) {
    layer_vkGetShaderModuleCreateInfoIdentifierEXT_default(device, pCreateInfo, pIdentifier);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleIdentifierEXT_default(
    VkDevice device,
    VkShaderModule shaderModule,
    VkShaderModuleIdentifierEXT* pIdentifier);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleIdentifierEXT(
    VkDevice device,
    VkShaderModule shaderModule,
    VkShaderModuleIdentifierEXT* pIdentifier
) {
    layer_vkGetShaderModuleIdentifierEXT_default(device, shaderModule, pIdentifier);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainCounterEXT_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSurfaceCounterFlagBitsEXT counter,
    uint64_t* pCounterValue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainCounterEXT(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSurfaceCounterFlagBitsEXT counter,
    uint64_t* pCounterValue
) {
    return layer_vkGetSwapchainCounterEXT_default(device, swapchain, counter, pCounterValue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainImagesKHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint32_t* pSwapchainImageCount,
    VkImage* pSwapchainImages);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainImagesKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint32_t* pSwapchainImageCount,
    VkImage* pSwapchainImages
) {
    return layer_vkGetSwapchainImagesKHR_default(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainStatusKHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainStatusKHR(
    VkDevice device,
    VkSwapchainKHR swapchain
) {
    return layer_vkGetSwapchainStatusKHR_default(device, swapchain);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetTensorMemoryRequirementsARM_default(
    VkDevice device,
    const VkTensorMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetTensorMemoryRequirementsARM(
    VkDevice device,
    const VkTensorMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    layer_vkGetTensorMemoryRequirementsARM_default(device, pInfo, pMemoryRequirements);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorOpaqueCaptureDescriptorDataARM_default(
    VkDevice device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorOpaqueCaptureDescriptorDataARM(
    VkDevice device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void* pData
) {
    return layer_vkGetTensorOpaqueCaptureDescriptorDataARM_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM_default(
    VkDevice device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM(
    VkDevice device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void* pData
) {
    return layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM_default(device, pInfo, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetValidationCacheDataEXT_default(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    size_t* pDataSize,
    void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetValidationCacheDataEXT(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    size_t* pDataSize,
    void* pData
) {
    return layer_vkGetValidationCacheDataEXT_default(device, validationCache, pDataSize, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportFenceFdKHR_default(
    VkDevice device,
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportFenceFdKHR(
    VkDevice device,
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo
) {
    return layer_vkImportFenceFdKHR_default(device, pImportFenceFdInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportSemaphoreFdKHR_default(
    VkDevice device,
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportSemaphoreFdKHR(
    VkDevice device,
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo
) {
    return layer_vkImportSemaphoreFdKHR_default(device, pImportSemaphoreFdInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkInvalidateMappedMemoryRanges_default(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkInvalidateMappedMemoryRanges(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges
) {
    return layer_vkInvalidateMappedMemoryRanges_default(device, memoryRangeCount, pMemoryRanges);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory_default(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkMemoryMapFlags flags,
    void** ppData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkMemoryMapFlags flags,
    void** ppData
) {
    return layer_vkMapMemory_default(device, memory, offset, size, flags, ppData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2_default(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData
) {
    return layer_vkMapMemory2_default(device, pMemoryMapInfo, ppData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2KHR_default(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2KHR(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData
) {
    return layer_vkMapMemory2KHR_default(device, pMemoryMapInfo, ppData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergePipelineCaches_default(
    VkDevice device,
    VkPipelineCache dstCache,
    uint32_t srcCacheCount,
    const VkPipelineCache* pSrcCaches);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergePipelineCaches(
    VkDevice device,
    VkPipelineCache dstCache,
    uint32_t srcCacheCount,
    const VkPipelineCache* pSrcCaches
) {
    return layer_vkMergePipelineCaches_default(device, dstCache, srcCacheCount, pSrcCaches);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergeValidationCachesEXT_default(
    VkDevice device,
    VkValidationCacheEXT dstCache,
    uint32_t srcCacheCount,
    const VkValidationCacheEXT* pSrcCaches);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergeValidationCachesEXT(
    VkDevice device,
    VkValidationCacheEXT dstCache,
    uint32_t srcCacheCount,
    const VkValidationCacheEXT* pSrcCaches
) {
    return layer_vkMergeValidationCachesEXT_default(device, dstCache, srcCacheCount, pSrcCaches);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkQueueBeginDebugUtilsLabelEXT_default(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueBeginDebugUtilsLabelEXT(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkQueueBeginDebugUtilsLabelEXT_default(queue, pLabelInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse_default(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence
) {
    return layer_vkQueueBindSparse_default(queue, bindInfoCount, pBindInfo, fence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkQueueEndDebugUtilsLabelEXT_default(
    VkQueue queue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueEndDebugUtilsLabelEXT(
    VkQueue queue
) {
    layer_vkQueueEndDebugUtilsLabelEXT_default(queue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkQueueInsertDebugUtilsLabelEXT_default(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueInsertDebugUtilsLabelEXT(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    layer_vkQueueInsertDebugUtilsLabelEXT_default(queue, pLabelInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR_default(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo
) {
    return layer_vkQueuePresentKHR_default(queue, pPresentInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit_default(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence
) {
    return layer_vkQueueSubmit_default(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2_default(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    return layer_vkQueueSubmit2_default(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR_default(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence
) {
    return layer_vkQueueSubmit2KHR_default(queue, submitCount, pSubmits, fence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueWaitIdle_default(
    VkQueue queue);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueWaitIdle(
    VkQueue queue
) {
    return layer_vkQueueWaitIdle_default(queue);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDeviceEventEXT_default(
    VkDevice device,
    const VkDeviceEventInfoEXT* pDeviceEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDeviceEventEXT(
    VkDevice device,
    const VkDeviceEventInfoEXT* pDeviceEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    return layer_vkRegisterDeviceEventEXT_default(device, pDeviceEventInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDisplayEventEXT_default(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayEventInfoEXT* pDisplayEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDisplayEventEXT(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayEventInfoEXT* pDisplayEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence
) {
    return layer_vkRegisterDisplayEventEXT_default(device, display, pDisplayEventInfo, pAllocator, pFence);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseCapturedPipelineDataKHR_default(
    VkDevice device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseCapturedPipelineDataKHR(
    VkDevice device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks* pAllocator
) {
    return layer_vkReleaseCapturedPipelineDataKHR_default(device, pInfo, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkReleaseProfilingLockKHR_default(
    VkDevice device);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkReleaseProfilingLockKHR(
    VkDevice device
) {
    layer_vkReleaseProfilingLockKHR_default(device);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesEXT_default(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesEXT(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo
) {
    return layer_vkReleaseSwapchainImagesEXT_default(device, pReleaseInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer_default(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags
) {
    return layer_vkResetCommandBuffer_default(commandBuffer, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool_default(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags
) {
    return layer_vkResetCommandPool_default(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetDescriptorPool_default(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    VkDescriptorPoolResetFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetDescriptorPool(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    VkDescriptorPoolResetFlags flags
) {
    return layer_vkResetDescriptorPool_default(device, descriptorPool, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetEvent_default(
    VkDevice device,
    VkEvent event);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetEvent(
    VkDevice device,
    VkEvent event
) {
    return layer_vkResetEvent_default(device, event);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetFences_default(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetFences(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences
) {
    return layer_vkResetFences_default(device, fenceCount, pFences);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPool_default(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPool(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    layer_vkResetQueryPool_default(device, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPoolEXT_default(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPoolEXT(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount
) {
    layer_vkResetQueryPoolEXT_default(device, queryPool, firstQuery, queryCount);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectNameEXT_default(
    VkDevice device,
    const VkDebugUtilsObjectNameInfoEXT* pNameInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectNameEXT(
    VkDevice device,
    const VkDebugUtilsObjectNameInfoEXT* pNameInfo
) {
    return layer_vkSetDebugUtilsObjectNameEXT_default(device, pNameInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectTagEXT_default(
    VkDevice device,
    const VkDebugUtilsObjectTagInfoEXT* pTagInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectTagEXT(
    VkDevice device,
    const VkDebugUtilsObjectTagInfoEXT* pTagInfo
) {
    return layer_vkSetDebugUtilsObjectTagEXT_default(device, pTagInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkSetDeviceMemoryPriorityEXT_default(
    VkDevice device,
    VkDeviceMemory memory,
    float priority);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSetDeviceMemoryPriorityEXT(
    VkDevice device,
    VkDeviceMemory memory,
    float priority
) {
    layer_vkSetDeviceMemoryPriorityEXT_default(device, memory, priority);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetEvent_default(
    VkDevice device,
    VkEvent event);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetEvent(
    VkDevice device,
    VkEvent event
) {
    return layer_vkSetEvent_default(device, event);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkSetHdrMetadataEXT_default(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainKHR* pSwapchains,
    const VkHdrMetadataEXT* pMetadata);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSetHdrMetadataEXT(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainKHR* pSwapchains,
    const VkHdrMetadataEXT* pMetadata
) {
    layer_vkSetHdrMetadataEXT_default(device, swapchainCount, pSwapchains, pMetadata);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateData_default(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateData(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data
) {
    return layer_vkSetPrivateData_default(device, objectType, objectHandle, privateDataSlot, data);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateDataEXT_default(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateDataEXT(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data
) {
    return layer_vkSetPrivateDataEXT_default(device, objectType, objectHandle, privateDataSlot, data);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphore_default(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphore(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo
) {
    return layer_vkSignalSemaphore_default(device, pSignalInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphoreKHR_default(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphoreKHR(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo
) {
    return layer_vkSignalSemaphoreKHR_default(device, pSignalInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayout_default(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayout(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions
) {
    return layer_vkTransitionImageLayout_default(device, transitionCount, pTransitions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayoutEXT_default(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayoutEXT(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions
) {
    return layer_vkTransitionImageLayoutEXT_default(device, transitionCount, pTransitions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPool_default(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags
) {
    layer_vkTrimCommandPool_default(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPoolKHR_default(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPoolKHR(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags
) {
    layer_vkTrimCommandPoolKHR_default(device, commandPool, flags);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUnmapMemory_default(
    VkDevice device,
    VkDeviceMemory memory);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUnmapMemory(
    VkDevice device,
    VkDeviceMemory memory
) {
    layer_vkUnmapMemory_default(device, memory);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2_default(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    return layer_vkUnmapMemory2_default(device, pMemoryUnmapInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2KHR_default(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2KHR(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo
) {
    return layer_vkUnmapMemory2KHR_default(device, pMemoryUnmapInfo);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplate_default(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplate(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData
) {
    layer_vkUpdateDescriptorSetWithTemplate_default(device, descriptorSet, descriptorUpdateTemplate, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplateKHR_default(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplateKHR(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData
) {
    layer_vkUpdateDescriptorSetWithTemplateKHR_default(device, descriptorSet, descriptorUpdateTemplate, pData);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSets_default(
    VkDevice device,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    const VkCopyDescriptorSet* pDescriptorCopies);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSets(
    VkDevice device,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    const VkCopyDescriptorSet* pDescriptorCopies
) {
    layer_vkUpdateDescriptorSets_default(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetPipelineEXT_default(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetPipelineEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites
) {
    layer_vkUpdateIndirectExecutionSetPipelineEXT_default(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetShaderEXT_default(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetShaderEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites
) {
    layer_vkUpdateIndirectExecutionSetShaderEXT_default(device, indirectExecutionSet, executionSetWriteCount, pExecutionSetWrites);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForFences_default(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences,
    VkBool32 waitAll,
    uint64_t timeout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForFences(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences,
    VkBool32 waitAll,
    uint64_t timeout
) {
    return layer_vkWaitForFences_default(device, fenceCount, pFences, waitAll, timeout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresent2KHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkPresentWait2InfoKHR* pPresentWait2Info);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresent2KHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkPresentWait2InfoKHR* pPresentWait2Info
) {
    return layer_vkWaitForPresent2KHR_default(device, swapchain, pPresentWait2Info);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresentKHR_default(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t presentId,
    uint64_t timeout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresentKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t presentId,
    uint64_t timeout
) {
    return layer_vkWaitForPresentKHR_default(device, swapchain, presentId, timeout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphores_default(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphores(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout
) {
    return layer_vkWaitSemaphores_default(device, pWaitInfo, timeout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphoresKHR_default(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphoresKHR(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout
) {
    return layer_vkWaitSemaphoresKHR_default(device, pWaitInfo, timeout);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteAccelerationStructuresPropertiesKHR_default(
    VkDevice device,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteAccelerationStructuresPropertiesKHR(
    VkDevice device,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride
) {
    return layer_vkWriteAccelerationStructuresPropertiesKHR_default(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteMicromapsPropertiesEXT_default(
    VkDevice device,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteMicromapsPropertiesEXT(
    VkDevice device,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride
) {
    return layer_vkWriteMicromapsPropertiesEXT_default(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride);
}

// clang-format on
