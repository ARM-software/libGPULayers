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

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImage2KHR(
    VkDevice device,
    const VkAcquireNextImageInfoKHR* pAcquireInfo,
    uint32_t* pImageIndex) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImage2KHR<default_tag>(
    VkDevice device,
    const VkAcquireNextImageInfoKHR* pAcquireInfo,
    uint32_t* pImageIndex);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImageKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t timeout,
    VkSemaphore semaphore,
    VkFence fence,
    uint32_t* pImageIndex) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireNextImageKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t timeout,
    VkSemaphore semaphore,
    VkFence fence,
    uint32_t* pImageIndex);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireProfilingLockKHR(
    VkDevice device,
    const VkAcquireProfilingLockInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAcquireProfilingLockKHR<default_tag>(
    VkDevice device,
    const VkAcquireProfilingLockInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers<default_tag>(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateDescriptorSets(
    VkDevice device,
    const VkDescriptorSetAllocateInfo* pAllocateInfo,
    VkDescriptorSet* pDescriptorSets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateDescriptorSets<default_tag>(
    VkDevice device,
    const VkDescriptorSetAllocateInfo* pAllocateInfo,
    VkDescriptorSet* pDescriptorSets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory<default_tag>(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBeginCommandBuffer(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBeginCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory(
    VkDevice device,
    VkBuffer buffer,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2KHR(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindBufferMemory2KHR<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindBufferMemoryInfo* pBindInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory(
    VkDevice device,
    VkImage image,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory<default_tag>(
    VkDevice device,
    VkImage image,
    VkDeviceMemory memory,
    VkDeviceSize memoryOffset);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2KHR(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindImageMemory2KHR<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindImageMemoryInfo* pBindInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindTensorMemoryARM(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindTensorMemoryInfoARM* pBindInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBindTensorMemoryARM<default_tag>(
    VkDevice device,
    uint32_t bindInfoCount,
    const VkBindTensorMemoryInfoARM* pBindInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildAccelerationStructuresKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildAccelerationStructuresKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildMicromapsEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkBuildMicromapsEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginConditionalRenderingEXT(
    VkCommandBuffer commandBuffer,
    const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginConditionalRenderingEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQuery(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQuery<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQueryIndexedEXT(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags,
    uint32_t index) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginQueryIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    VkQueryControlFlags flags,
    uint32_t index);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginTransformFeedbackEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginTransformFeedbackEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBufferEmbeddedSamplersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBuffersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t bufferCount,
    const VkDescriptorBufferBindingInfoEXT* pBindingInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorBuffersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t bufferCount,
    const VkDescriptorBufferBindingInfoEXT* pBindingInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    const uint32_t* pDynamicOffsets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets,
    uint32_t dynamicOffsetCount,
    const uint32_t* pDynamicOffsets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2KHR(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindDescriptorSets2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBindDescriptorSetsInfo* pBindDescriptorSetsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkIndexType indexType) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkIndexType indexType);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2KHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindIndexBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkIndexType indexType);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindPipeline(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipeline pipeline) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindPipeline<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipeline pipeline);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindShadersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t stageCount,
    const VkShaderStageFlagBits* pStages,
    const VkShaderEXT* pShaders) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindShadersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t stageCount,
    const VkShaderStageFlagBits* pStages,
    const VkShaderEXT* pShaders);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindTransformFeedbackBuffersEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindTransformFeedbackBuffersEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2EXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBindVertexBuffers2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstBinding,
    uint32_t bindingCount,
    const VkBuffer* pBuffers,
    const VkDeviceSize* pOffsets,
    const VkDeviceSize* pSizes,
    const VkDeviceSize* pStrides);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageBlit* pRegions,
    VkFilter filter) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageBlit* pRegions,
    VkFilter filter);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBlitImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkBlitImageInfo2* pBlitImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildMicromapsEXT(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildMicromapsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkMicromapBuildInfoEXT* pInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearAttachments(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkClearAttachment* pAttachments,
    uint32_t rectCount,
    const VkClearRect* pRects) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearAttachments<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkClearAttachment* pAttachments,
    uint32_t rectCount,
    const VkClearRect* pRects);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearColorValue* pColor,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearColorValue* pColor,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearDepthStencilValue* pDepthStencil,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage image,
    VkImageLayout imageLayout,
    const VkClearDepthStencilValue* pDepthStencil,
    uint32_t rangeCount,
    const VkImageSubresourceRange* pRanges);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureToMemoryKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyAccelerationStructureToMemoryKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferCopy* pRegions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferCopy* pRegions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer srcBuffer,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageCopy* pRegions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageCopy* pRegions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkBuffer dstBuffer,
    uint32_t regionCount,
    const VkBufferImageCopy* pRegions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToAccelerationStructureKHR(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToAccelerationStructureKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToMicromapEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMemoryToMicromapEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMemoryToMicromapInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapToMemoryEXT(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyMicromapToMemoryEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyMicromapToMemoryInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyQueryPoolResults(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize stride,
    VkQueryResultFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyQueryPoolResults<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize stride,
    VkQueryResultFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyTensorARM(
    VkCommandBuffer commandBuffer,
    const VkCopyTensorInfoARM* pCopyTensorInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyTensorARM<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyTensorInfoARM* pCopyTensorInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerInsertEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerInsertEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksEXT(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectCountEXT(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectEXT(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMeshTasksIndirectEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiEXT(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawInfoEXT* pVertexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawInfoEXT* pVertexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiIndexedEXT(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawIndexedInfoEXT* pIndexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride,
    const int32_t* pVertexOffset) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawMultiIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t drawCount,
    const VkMultiDrawIndexedInfoEXT* pIndexInfo,
    uint32_t instanceCount,
    uint32_t firstInstance,
    uint32_t stride,
    const int32_t* pVertexOffset);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndConditionalRenderingEXT(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndConditionalRenderingEXT<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQuery(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQuery<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQueryIndexedEXT(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    uint32_t index) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndQueryIndexedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t query,
    uint32_t index);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering2EXT(
    VkCommandBuffer commandBuffer,
    const VkRenderingEndInfoEXT* pRenderingEndInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingEndInfoEXT* pRenderingEndInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndTransformFeedbackEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndTransformFeedbackEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstCounterBuffer,
    uint32_t counterBufferCount,
    const VkBuffer* pCounterBuffers,
    const VkDeviceSize* pCounterBufferOffsets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteGeneratedCommandsEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 isPreprocessed,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteGeneratedCommandsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 isPreprocessed,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize size,
    uint32_t data) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize size,
    uint32_t data);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdInsertDebugUtilsLabelEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass(
    VkCommandBuffer commandBuffer,
    VkSubpassContents contents) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSubpassContents contents);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2KHR(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdNextSubpass2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSubpassBeginInfo* pSubpassBeginInfo,
    const VkSubpassEndInfo* pSubpassEndInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
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
    const VkImageMemoryBarrier* pImageMemoryBarriers) = delete;

/* Default common code implementation. */
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
    const VkImageMemoryBarrier* pImageMemoryBarriers);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2KHR(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPipelineBarrier2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDependencyInfo* pDependencyInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPreprocessGeneratedCommandsEXT(
    VkCommandBuffer commandBuffer,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo,
    VkCommandBuffer stateCommandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPreprocessGeneratedCommandsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo,
    VkCommandBuffer stateCommandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants(
    VkCommandBuffer commandBuffer,
    VkPipelineLayout layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    const void* pValues) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineLayout layout,
    VkShaderStageFlags stageFlags,
    uint32_t offset,
    uint32_t size,
    const void* pValues);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushConstants2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushConstantsInfo* pPushConstantsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSet2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetInfo* pPushDescriptorSetInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetKHR(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t set,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2KHR(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplate2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplateKHR(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdPushDescriptorSetWithTemplateKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    VkPipelineLayout layout,
    uint32_t set,
    const void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2KHR(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetEvent2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags2 stageMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetQueryPool(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResetQueryPool<default_tag>(
    VkCommandBuffer commandBuffer,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageResolve* pRegions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImage srcImage,
    VkImageLayout srcImageLayout,
    VkImage dstImage,
    VkImageLayout dstImageLayout,
    uint32_t regionCount,
    const VkImageResolve* pRegions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2KHR(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdResolveImage2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkResolveImageInfo2* pResolveImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToCoverageEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToCoverageEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToCoverageEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToCoverageEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToOneEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToOneEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAlphaToOneEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 alphaToOneEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAttachmentFeedbackLoopEnableEXT(
    VkCommandBuffer commandBuffer,
    VkImageAspectFlags aspectMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetAttachmentFeedbackLoopEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkImageAspectFlags aspectMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetBlendConstants(
    VkCommandBuffer commandBuffer,
    const float blendConstants[4]) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetBlendConstants<default_tag>(
    VkCommandBuffer commandBuffer,
    const float blendConstants[4]);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendAdvancedEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendAdvancedEXT* pColorBlendAdvanced) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendAdvancedEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendAdvancedEXT* pColorBlendAdvanced);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEnableEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkBool32* pColorBlendEnables) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkBool32* pColorBlendEnables);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEquationEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendEquationEXT* pColorBlendEquations) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorBlendEquationEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorBlendEquationEXT* pColorBlendEquations);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteEnableEXT(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkBool32* pColorWriteEnables) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t attachmentCount,
    const VkBool32* pColorWriteEnables);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteMaskEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorComponentFlags* pColorWriteMasks) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetColorWriteMaskEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstAttachment,
    uint32_t attachmentCount,
    const VkColorComponentFlags* pColorWriteMasks);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetConservativeRasterizationModeEXT(
    VkCommandBuffer commandBuffer,
    VkConservativeRasterizationModeEXT conservativeRasterizationMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetConservativeRasterizationModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkConservativeRasterizationModeEXT conservativeRasterizationMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationModeNV(
    VkCommandBuffer commandBuffer,
    VkCoverageModulationModeNV coverageModulationMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationModeNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCoverageModulationModeNV coverageModulationMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageModulationTableEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageModulationTableEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableNV(
    VkCommandBuffer commandBuffer,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageModulationTableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t coverageModulationTableCount,
    const float* pCoverageModulationTable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageReductionModeNV(
    VkCommandBuffer commandBuffer,
    VkCoverageReductionModeNV coverageReductionMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageReductionModeNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCoverageReductionModeNV coverageReductionMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageToColorEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 coverageToColorEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorLocationNV(
    VkCommandBuffer commandBuffer,
    uint32_t coverageToColorLocation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCoverageToColorLocationNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t coverageToColorLocation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullModeEXT(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias(
    VkCommandBuffer commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias<default_tag>(
    VkCommandBuffer commandBuffer,
    float depthBiasConstantFactor,
    float depthBiasClamp,
    float depthBiasSlopeFactor);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias2EXT(
    VkCommandBuffer commandBuffer,
    const VkDepthBiasInfoEXT* pDepthBiasInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBias2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkDepthBiasInfoEXT* pDepthBiasInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBiasEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBiasEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBounds(
    VkCommandBuffer commandBuffer,
    float minDepthBounds,
    float maxDepthBounds) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBounds<default_tag>(
    VkCommandBuffer commandBuffer,
    float minDepthBounds,
    float maxDepthBounds);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthBoundsTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthBoundsTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClampEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClampEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampRangeEXT(
    VkCommandBuffer commandBuffer,
    VkDepthClampModeEXT depthClampMode,
    const VkDepthClampRangeEXT* pDepthClampRange) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClampRangeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDepthClampModeEXT depthClampMode,
    const VkDepthClampRangeEXT* pDepthClampRange);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClipEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthClipEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipNegativeOneToOneEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 negativeOneToOne) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthClipNegativeOneToOneEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 negativeOneToOne);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOp(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOpEXT(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthCompareOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCompareOp depthCompareOp);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDepthWriteEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 depthWriteEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsets2EXT(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsets2EXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsetsEXT(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t setCount,
    const uint32_t* pBufferIndices,
    const VkDeviceSize* pOffsets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDescriptorBufferOffsetsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineBindPoint pipelineBindPoint,
    VkPipelineLayout layout,
    uint32_t firstSet,
    uint32_t setCount,
    const uint32_t* pBufferIndices,
    const VkDeviceSize* pOffsets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMask(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMask<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMaskKHR(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDeviceMaskKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t deviceMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEXT(
    VkCommandBuffer commandBuffer,
    uint32_t firstDiscardRectangle,
    uint32_t discardRectangleCount,
    const VkRect2D* pDiscardRectangles) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstDiscardRectangle,
    uint32_t discardRectangleCount,
    const VkRect2D* pDiscardRectangles);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 discardRectangleEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 discardRectangleEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleModeEXT(
    VkCommandBuffer commandBuffer,
    VkDiscardRectangleModeEXT discardRectangleMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetDiscardRectangleModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDiscardRectangleModeEXT discardRectangleMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    VkPipelineStageFlags stageMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2KHR(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetEvent2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkEvent event,
    const VkDependencyInfo* pDependencyInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT(
    VkCommandBuffer commandBuffer,
    float extraPrimitiveOverestimationSize) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetExtraPrimitiveOverestimationSizeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    float extraPrimitiveOverestimationSize);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFragmentShadingRateKHR(
    VkCommandBuffer commandBuffer,
    const VkExtent2D* pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR combinerOps[2]) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFragmentShadingRateKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkExtent2D* pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR combinerOps[2]);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFace(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFace<default_tag>(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFaceEXT(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetFrontFaceEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkFrontFace frontFace);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineRasterizationModeEXT(
    VkCommandBuffer commandBuffer,
    VkLineRasterizationModeEXT lineRasterizationMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineRasterizationModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkLineRasterizationModeEXT lineRasterizationMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStipple(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStipple<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEXT(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 stippledLineEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stippledLineEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleKHR(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineStippleKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t lineStippleFactor,
    uint16_t lineStipplePattern);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineWidth(
    VkCommandBuffer commandBuffer,
    float lineWidth) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLineWidth<default_tag>(
    VkCommandBuffer commandBuffer,
    float lineWidth);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEXT(
    VkCommandBuffer commandBuffer,
    VkLogicOp logicOp) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkLogicOp logicOp);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 logicOpEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetLogicOpEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 logicOpEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPatchControlPointsEXT(
    VkCommandBuffer commandBuffer,
    uint32_t patchControlPoints) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPatchControlPointsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t patchControlPoints);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPolygonModeEXT(
    VkCommandBuffer commandBuffer,
    VkPolygonMode polygonMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPolygonModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPolygonMode polygonMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveRestartEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 primitiveRestartEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopology(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopology<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopologyEXT(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetPrimitiveTopologyEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPrimitiveTopology primitiveTopology);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetProvokingVertexModeEXT(
    VkCommandBuffer commandBuffer,
    VkProvokingVertexModeEXT provokingVertexMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetProvokingVertexModeEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkProvokingVertexModeEXT provokingVertexMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationSamplesEXT(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits rasterizationSamples) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationSamplesEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits rasterizationSamples);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationStreamEXT(
    VkCommandBuffer commandBuffer,
    uint32_t rasterizationStream) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizationStreamEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t rasterizationStream);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRasterizerDiscardEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 rasterizerDiscardEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRayTracingPipelineStackSizeKHR(
    VkCommandBuffer commandBuffer,
    uint32_t pipelineStackSize) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRayTracingPipelineStackSizeKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t pipelineStackSize);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocations(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocations<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocationsKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingAttachmentLocationsKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingAttachmentLocationInfo* pLocationInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndices(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndices<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndicesKHR(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRenderingInputAttachmentIndicesKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRepresentativeFragmentTestEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 representativeFragmentTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetRepresentativeFragmentTestEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 representativeFragmentTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEXT(
    VkCommandBuffer commandBuffer,
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 sampleLocationsEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleLocationsEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 sampleLocationsEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleMaskEXT(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits samples,
    const VkSampleMask* pSampleMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetSampleMaskEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkSampleCountFlagBits samples,
    const VkSampleMask* pSampleMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissor(
    VkCommandBuffer commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    const VkRect2D* pScissors) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissor<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstScissor,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCount(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCount<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetScissorWithCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t scissorCount,
    const VkRect2D* pScissors);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetShadingRateImageEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 shadingRateImageEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetShadingRateImageEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 shadingRateImageEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilCompareMask(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t compareMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilCompareMask<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t compareMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOp(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOpEXT(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilOpEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    VkStencilOp failOp,
    VkStencilOp passOp,
    VkStencilOp depthFailOp,
    VkCompareOp compareOp);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilReference(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t reference) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilReference<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t reference);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnable(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnable<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnableEXT(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilTestEnableEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 stencilTestEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilWriteMask(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t writeMask) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetStencilWriteMask<default_tag>(
    VkCommandBuffer commandBuffer,
    VkStencilFaceFlags faceMask,
    uint32_t writeMask);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetTessellationDomainOriginEXT(
    VkCommandBuffer commandBuffer,
    VkTessellationDomainOrigin domainOrigin) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetTessellationDomainOriginEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    VkTessellationDomainOrigin domainOrigin);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetVertexInputEXT(
    VkCommandBuffer commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetVertexInputEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions,
    uint32_t vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewport(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewport* pViewports) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewport<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportSwizzleNV(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewportSwizzleNV* pViewportSwizzles) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportSwizzleNV<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t firstViewport,
    uint32_t viewportCount,
    const VkViewportSwizzleNV* pViewportSwizzles);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWScalingEnableNV(
    VkCommandBuffer commandBuffer,
    VkBool32 viewportWScalingEnable) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWScalingEnableNV<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBool32 viewportWScalingEnable);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCount(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCount<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCountEXT(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetViewportWithCountEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t viewportCount,
    const VkViewport* pViewports);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdUpdateBuffer(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize dataSize,
    const void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdUpdateBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer dstBuffer,
    VkDeviceSize dstOffset,
    VkDeviceSize dataSize,
    const void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
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
    const VkImageMemoryBarrier* pImageMemoryBarriers) = delete;

/* Default common code implementation. */
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
    const VkImageMemoryBarrier* pImageMemoryBarriers);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2KHR(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWaitEvents2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t eventCount,
    const VkEvent* pEvents,
    const VkDependencyInfo* pDependencyInfos);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteAccelerationStructuresPropertiesKHR(
    VkCommandBuffer commandBuffer,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteAccelerationStructuresPropertiesKHR<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteMicromapsPropertiesEXT(
    VkCommandBuffer commandBuffer,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteMicromapsPropertiesEXT<default_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    VkQueryPool queryPool,
    uint32_t firstQuery);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlagBits pipelineStage,
    VkQueryPool queryPool,
    uint32_t query) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlagBits pipelineStage,
    VkQueryPool queryPool,
    uint32_t query);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2KHR(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdWriteTimestamp2KHR<default_tag>(
    VkCommandBuffer commandBuffer,
    VkPipelineStageFlags2 stage,
    VkQueryPool queryPool,
    uint32_t query);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureToMemoryKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyAccelerationStructureToMemoryKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImage(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImage<default_tag>(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImageEXT(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToImageEXT<default_tag>(
    VkDevice device,
    const VkCopyImageToImageInfo* pCopyImageToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemory(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemory<default_tag>(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemoryEXT(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyImageToMemoryEXT<default_tag>(
    VkDevice device,
    const VkCopyImageToMemoryInfo* pCopyImageToMemoryInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToAccelerationStructureKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImage(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImage<default_tag>(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImageEXT(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToImageEXT<default_tag>(
    VkDevice device,
    const VkCopyMemoryToImageInfo* pCopyMemoryToImageInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToMicromapEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMemoryToMicromapEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMemoryToMicromapInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapToMemoryEXT(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCopyMicromapToMemoryEXT<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    const VkCopyMicromapToMemoryInfoEXT* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAccelerationStructureKHR(
    VkDevice device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkAccelerationStructureKHR* pAccelerationStructure) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAccelerationStructureKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkAccelerationStructureKHR* pAccelerationStructure);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBuffer(
    VkDevice device,
    const VkBufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBuffer* pBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBuffer<default_tag>(
    VkDevice device,
    const VkBufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBuffer* pBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBufferView(
    VkDevice device,
    const VkBufferViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBufferView* pView) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateBufferView<default_tag>(
    VkDevice device,
    const VkBufferViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkBufferView* pView);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool<default_tag>(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkComputePipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkComputePipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDeferredOperationKHR(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator,
    VkDeferredOperationKHR* pDeferredOperation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDeferredOperationKHR<default_tag>(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator,
    VkDeferredOperationKHR* pDeferredOperation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorPool(
    VkDevice device,
    const VkDescriptorPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorPool* pDescriptorPool) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorPool<default_tag>(
    VkDevice device,
    const VkDescriptorPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorPool* pDescriptorPool);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorSetLayout(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorSetLayout* pSetLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorSetLayout<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorSetLayout* pSetLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplate(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplate<default_tag>(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplateKHR(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDescriptorUpdateTemplateKHR<default_tag>(
    VkDevice device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateEvent(
    VkDevice device,
    const VkEventCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkEvent* pEvent) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateEvent<default_tag>(
    VkDevice device,
    const VkEventCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkEvent* pEvent);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFence(
    VkDevice device,
    const VkFenceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFence<default_tag>(
    VkDevice device,
    const VkFenceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFramebuffer(
    VkDevice device,
    const VkFramebufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFramebuffer* pFramebuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateFramebuffer<default_tag>(
    VkDevice device,
    const VkFramebufferCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFramebuffer* pFramebuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateGraphicsPipelines(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkGraphicsPipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateGraphicsPipelines<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkGraphicsPipelineCreateInfo* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage(
    VkDevice device,
    const VkImageCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImage* pImage) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage<default_tag>(
    VkDevice device,
    const VkImageCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImage* pImage);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImageView(
    VkDevice device,
    const VkImageViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImageView* pView) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImageView<default_tag>(
    VkDevice device,
    const VkImageViewCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkImageView* pView);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectCommandsLayoutEXT(
    VkDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectCommandsLayoutEXT<default_tag>(
    VkDevice device,
    const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectExecutionSetEXT(
    VkDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectExecutionSetEXT* pIndirectExecutionSet) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateIndirectExecutionSetEXT<default_tag>(
    VkDevice device,
    const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkIndirectExecutionSetEXT* pIndirectExecutionSet);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateMicromapEXT(
    VkDevice device,
    const VkMicromapCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkMicromapEXT* pMicromap) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateMicromapEXT<default_tag>(
    VkDevice device,
    const VkMicromapCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkMicromapEXT* pMicromap);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineBinariesKHR(
    VkDevice device,
    const VkPipelineBinaryCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineBinaryHandlesInfoKHR* pBinaries) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineBinariesKHR<default_tag>(
    VkDevice device,
    const VkPipelineBinaryCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineBinaryHandlesInfoKHR* pBinaries);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineCache(
    VkDevice device,
    const VkPipelineCacheCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineCache* pPipelineCache) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineCache<default_tag>(
    VkDevice device,
    const VkPipelineCacheCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineCache* pPipelineCache);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineLayout(
    VkDevice device,
    const VkPipelineLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineLayout* pPipelineLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePipelineLayout<default_tag>(
    VkDevice device,
    const VkPipelineLayoutCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPipelineLayout* pPipelineLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlot(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlot<default_tag>(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlotEXT(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreatePrivateDataSlotEXT<default_tag>(
    VkDevice device,
    const VkPrivateDataSlotCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkPrivateDataSlot* pPrivateDataSlot);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateQueryPool(
    VkDevice device,
    const VkQueryPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkQueryPool* pQueryPool) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateQueryPool<default_tag>(
    VkDevice device,
    const VkQueryPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkQueryPool* pQueryPool);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRayTracingPipelinesKHR(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRayTracingPipelinesKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR deferredOperation,
    VkPipelineCache pipelineCache,
    uint32_t createInfoCount,
    const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkPipeline* pPipelines);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR<default_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSampler(
    VkDevice device,
    const VkSamplerCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSampler* pSampler) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSampler<default_tag>(
    VkDevice device,
    const VkSamplerCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSampler* pSampler);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversion(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversion<default_tag>(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversionKHR(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSamplerYcbcrConversionKHR<default_tag>(
    VkDevice device,
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSamplerYcbcrConversion* pYcbcrConversion);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSemaphore(
    VkDevice device,
    const VkSemaphoreCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSemaphore* pSemaphore) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSemaphore<default_tag>(
    VkDevice device,
    const VkSemaphoreCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSemaphore* pSemaphore);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkShaderModule* pShaderModule) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule<default_tag>(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkShaderModule* pShaderModule);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT(
    VkDevice device,
    uint32_t createInfoCount,
    const VkShaderCreateInfoEXT* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkShaderEXT* pShaders) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT<default_tag>(
    VkDevice device,
    uint32_t createInfoCount,
    const VkShaderCreateInfoEXT* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkShaderEXT* pShaders);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSharedSwapchainsKHR(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchains) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSharedSwapchainsKHR<default_tag>(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainCreateInfoKHR* pCreateInfos,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchains);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR<default_tag>(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorARM(
    VkDevice device,
    const VkTensorCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorARM* pTensor) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorARM<default_tag>(
    VkDevice device,
    const VkTensorCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorARM* pTensor);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorViewARM(
    VkDevice device,
    const VkTensorViewCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorViewARM* pView) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateTensorViewARM<default_tag>(
    VkDevice device,
    const VkTensorViewCreateInfoARM* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkTensorViewARM* pView);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateValidationCacheEXT(
    VkDevice device,
    const VkValidationCacheCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkValidationCacheEXT* pValidationCache) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateValidationCacheEXT<default_tag>(
    VkDevice device,
    const VkValidationCacheCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkValidationCacheEXT* pValidationCache);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectNameEXT(
    VkDevice device,
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectNameEXT<default_tag>(
    VkDevice device,
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectTagEXT(
    VkDevice device,
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDebugMarkerSetObjectTagEXT<default_tag>(
    VkDevice device,
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeferredOperationJoinKHR(
    VkDevice device,
    VkDeferredOperationKHR operation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeferredOperationJoinKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyAccelerationStructureKHR(
    VkDevice device,
    VkAccelerationStructureKHR accelerationStructure,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyAccelerationStructureKHR<default_tag>(
    VkDevice device,
    VkAccelerationStructureKHR accelerationStructure,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBuffer(
    VkDevice device,
    VkBuffer buffer,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBuffer<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBufferView(
    VkDevice device,
    VkBufferView bufferView,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyBufferView<default_tag>(
    VkDevice device,
    VkBufferView bufferView,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDeferredOperationKHR(
    VkDevice device,
    VkDeferredOperationKHR operation,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDeferredOperationKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorPool(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorPool<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorSetLayout(
    VkDevice device,
    VkDescriptorSetLayout descriptorSetLayout,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorSetLayout<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout descriptorSetLayout,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplate(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplate<default_tag>(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplateKHR(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDescriptorUpdateTemplateKHR<default_tag>(
    VkDevice device,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice<default_tag>(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyEvent(
    VkDevice device,
    VkEvent event,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyEvent<default_tag>(
    VkDevice device,
    VkEvent event,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFence(
    VkDevice device,
    VkFence fence,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFence<default_tag>(
    VkDevice device,
    VkFence fence,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFramebuffer(
    VkDevice device,
    VkFramebuffer framebuffer,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyFramebuffer<default_tag>(
    VkDevice device,
    VkFramebuffer framebuffer,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImage(
    VkDevice device,
    VkImage image,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImage<default_tag>(
    VkDevice device,
    VkImage image,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImageView(
    VkDevice device,
    VkImageView imageView,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyImageView<default_tag>(
    VkDevice device,
    VkImageView imageView,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectCommandsLayoutEXT(
    VkDevice device,
    VkIndirectCommandsLayoutEXT indirectCommandsLayout,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectCommandsLayoutEXT<default_tag>(
    VkDevice device,
    VkIndirectCommandsLayoutEXT indirectCommandsLayout,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectExecutionSetEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyIndirectExecutionSetEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyMicromapEXT(
    VkDevice device,
    VkMicromapEXT micromap,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyMicromapEXT<default_tag>(
    VkDevice device,
    VkMicromapEXT micromap,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipeline(
    VkDevice device,
    VkPipeline pipeline,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipeline<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineBinaryKHR(
    VkDevice device,
    VkPipelineBinaryKHR pipelineBinary,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineBinaryKHR<default_tag>(
    VkDevice device,
    VkPipelineBinaryKHR pipelineBinary,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineCache(
    VkDevice device,
    VkPipelineCache pipelineCache,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineCache<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineLayout(
    VkDevice device,
    VkPipelineLayout pipelineLayout,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPipelineLayout<default_tag>(
    VkDevice device,
    VkPipelineLayout pipelineLayout,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlot(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlot<default_tag>(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlotEXT(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyPrivateDataSlotEXT<default_tag>(
    VkDevice device,
    VkPrivateDataSlot privateDataSlot,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyQueryPool(
    VkDevice device,
    VkQueryPool queryPool,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyQueryPool<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass<default_tag>(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySampler(
    VkDevice device,
    VkSampler sampler,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySampler<default_tag>(
    VkDevice device,
    VkSampler sampler,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversion(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversion<default_tag>(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversionKHR(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySamplerYcbcrConversionKHR<default_tag>(
    VkDevice device,
    VkSamplerYcbcrConversion ycbcrConversion,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySemaphore(
    VkDevice device,
    VkSemaphore semaphore,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySemaphore<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderEXT(
    VkDevice device,
    VkShaderEXT shader,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderEXT<default_tag>(
    VkDevice device,
    VkShaderEXT shader,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderModule(
    VkDevice device,
    VkShaderModule shaderModule,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyShaderModule<default_tag>(
    VkDevice device,
    VkShaderModule shaderModule,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySwapchainKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySwapchainKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorARM(
    VkDevice device,
    VkTensorARM tensor,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorARM<default_tag>(
    VkDevice device,
    VkTensorARM tensor,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorViewARM(
    VkDevice device,
    VkTensorViewARM tensorView,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyTensorViewARM<default_tag>(
    VkDevice device,
    VkTensorViewARM tensorView,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyValidationCacheEXT(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyValidationCacheEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeviceWaitIdle(
    VkDevice device) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDeviceWaitIdle<default_tag>(
    VkDevice device);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDisplayPowerControlEXT(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkDisplayPowerControlEXT<default_tag>(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEndCommandBuffer(
    VkCommandBuffer commandBuffer) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEndCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFlushMappedMemoryRanges(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFlushMappedMemoryRanges<default_tag>(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFreeDescriptorSets(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkFreeDescriptorSets<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    uint32_t descriptorSetCount,
    const VkDescriptorSet* pDescriptorSets);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeMemory(
    VkDevice device,
    VkDeviceMemory memory,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetAccelerationStructureBuildSizesKHR(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t* pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetAccelerationStructureBuildSizesKHR<default_tag>(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo,
    const uint32_t* pMaxPrimitiveCounts,
    VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetAccelerationStructureDeviceAddressKHR(
    VkDevice device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetAccelerationStructureDeviceAddressKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureDeviceAddressInfoKHR* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddress(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddress<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressEXT(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressEXT<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressKHR(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkDeviceAddress VKAPI_CALL layer_vkGetBufferDeviceAddressKHR<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements(
    VkDevice device,
    VkBuffer buffer,
    VkMemoryRequirements* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements<default_tag>(
    VkDevice device,
    VkBuffer buffer,
    VkMemoryRequirements* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2KHR(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetBufferMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkBufferMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddress(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddress<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddressKHR(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetBufferOpaqueCaptureAddressKHR<default_tag>(
    VkDevice device,
    const VkBufferDeviceAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetBufferOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetBufferOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkBufferCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsEXT(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsEXT<default_tag>(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsKHR(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetCalibratedTimestampsKHR<default_tag>(
    VkDevice device,
    uint32_t timestampCount,
    const VkCalibratedTimestampInfoKHR* pTimestampInfos,
    uint64_t* pTimestamps,
    uint64_t* pMaxDeviation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR uint32_t VKAPI_CALL layer_vkGetDeferredOperationMaxConcurrencyKHR(
    VkDevice device,
    VkDeferredOperationKHR operation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR uint32_t VKAPI_CALL layer_vkGetDeferredOperationMaxConcurrencyKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeferredOperationResultKHR(
    VkDevice device,
    VkDeferredOperationKHR operation) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeferredOperationResultKHR<default_tag>(
    VkDevice device,
    VkDeferredOperationKHR operation);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorEXT(
    VkDevice device,
    const VkDescriptorGetInfoEXT* pDescriptorInfo,
    size_t dataSize,
    void* pDescriptor) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorEXT<default_tag>(
    VkDevice device,
    const VkDescriptorGetInfoEXT* pDescriptorInfo,
    size_t dataSize,
    void* pDescriptor);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutBindingOffsetEXT(
    VkDevice device,
    VkDescriptorSetLayout layout,
    uint32_t binding,
    VkDeviceSize* pOffset) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutBindingOffsetEXT<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout layout,
    uint32_t binding,
    VkDeviceSize* pOffset);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSizeEXT(
    VkDevice device,
    VkDescriptorSetLayout layout,
    VkDeviceSize* pLayoutSizeInBytes) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSizeEXT<default_tag>(
    VkDevice device,
    VkDescriptorSetLayout layout,
    VkDeviceSize* pLayoutSizeInBytes);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupport(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupport<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupportKHR(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDescriptorSetLayoutSupportKHR<default_tag>(
    VkDevice device,
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
    VkDescriptorSetLayoutSupport* pSupport);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceAccelerationStructureCompatibilityKHR(
    VkDevice device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceAccelerationStructureCompatibilityKHR<default_tag>(
    VkDevice device,
    const VkAccelerationStructureVersionInfoKHR* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirements(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceBufferMemoryRequirementsKHR<default_tag>(
    VkDevice device,
    const VkDeviceBufferMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceFaultInfoEXT(
    VkDevice device,
    VkDeviceFaultCountsEXT* pFaultCounts,
    VkDeviceFaultInfoEXT* pFaultInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceFaultInfoEXT<default_tag>(
    VkDevice device,
    VkDeviceFaultCountsEXT* pFaultCounts,
    VkDeviceFaultInfoEXT* pFaultInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeatures(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeatures<default_tag>(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeaturesKHR(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceGroupPeerMemoryFeaturesKHR<default_tag>(
    VkDevice device,
    uint32_t heapIndex,
    uint32_t localDeviceIndex,
    uint32_t remoteDeviceIndex,
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupPresentCapabilitiesKHR(
    VkDevice device,
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupPresentCapabilitiesKHR<default_tag>(
    VkDevice device,
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupSurfacePresentModesKHR(
    VkDevice device,
    VkSurfaceKHR surface,
    VkDeviceGroupPresentModeFlagsKHR* pModes) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDeviceGroupSurfacePresentModesKHR<default_tag>(
    VkDevice device,
    VkSurfaceKHR surface,
    VkDeviceGroupPresentModeFlagsKHR* pModes);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirements(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirements(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirements<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirementsKHR(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSparseMemoryRequirementsKHR<default_tag>(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayout(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayout<default_tag>(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayoutKHR(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageSubresourceLayoutKHR<default_tag>(
    VkDevice device,
    const VkDeviceImageSubresourceInfo* pInfo,
    VkSubresourceLayout2* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMemoryCommitment(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize* pCommittedMemoryInBytes) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMemoryCommitment<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize* pCommittedMemoryInBytes);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddress(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddress<default_tag>(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR uint64_t VKAPI_CALL layer_vkGetDeviceMemoryOpaqueCaptureAddressKHR<default_tag>(
    VkDevice device,
    const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMicromapCompatibilityEXT(
    VkDevice device,
    const VkMicromapVersionInfoEXT* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceMicromapCompatibilityEXT<default_tag>(
    VkDevice device,
    const VkMicromapVersionInfoEXT* pVersionInfo,
    VkAccelerationStructureCompatibilityKHR* pCompatibility);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetDeviceProcAddr<default_tag>(
    VkDevice device,
    const char* pName);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue<default_tag>(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue2(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceQueue2<default_tag>(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceTensorMemoryRequirementsARM(
    VkDevice device,
    const VkDeviceTensorMemoryRequirementsARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceTensorMemoryRequirementsARM<default_tag>(
    VkDevice device,
    const VkDeviceTensorMemoryRequirementsARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetEventStatus(
    VkDevice device,
    VkEvent event) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetEventStatus<default_tag>(
    VkDevice device,
    VkEvent event);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceFdKHR(
    VkDevice device,
    const VkFenceGetFdInfoKHR* pGetFdInfo,
    int* pFd) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceFdKHR<default_tag>(
    VkDevice device,
    const VkFenceGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceStatus(
    VkDevice device,
    VkFence fence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetFenceStatus<default_tag>(
    VkDevice device,
    VkFence fence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetGeneratedCommandsMemoryRequirementsEXT(
    VkDevice device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetGeneratedCommandsMemoryRequirementsEXT<default_tag>(
    VkDevice device,
    const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageDrmFormatModifierPropertiesEXT(
    VkDevice device,
    VkImage image,
    VkImageDrmFormatModifierPropertiesEXT* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageDrmFormatModifierPropertiesEXT<default_tag>(
    VkDevice device,
    VkImage image,
    VkImageDrmFormatModifierPropertiesEXT* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements(
    VkDevice device,
    VkImage image,
    VkMemoryRequirements* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements<default_tag>(
    VkDevice device,
    VkImage image,
    VkMemoryRequirements* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2KHR(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkImageMemoryRequirementsInfo2* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkImageCaptureDescriptorDataInfoEXT* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkImageCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements(
    VkDevice device,
    VkImage image,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements<default_tag>(
    VkDevice device,
    VkImage image,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2<default_tag>(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2KHR(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSparseMemoryRequirements2KHR<default_tag>(
    VkDevice device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t* pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout(
    VkDevice device,
    VkImage image,
    const VkImageSubresource* pSubresource,
    VkSubresourceLayout* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource* pSubresource,
    VkSubresourceLayout* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2EXT(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2EXT<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2KHR(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetImageSubresourceLayout2KHR<default_tag>(
    VkDevice device,
    VkImage image,
    const VkImageSubresource2* pSubresource,
    VkSubresourceLayout2* pLayout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetImageViewOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkImageViewCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdKHR(
    VkDevice device,
    const VkMemoryGetFdInfoKHR* pGetFdInfo,
    int* pFd) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdKHR<default_tag>(
    VkDevice device,
    const VkMemoryGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdPropertiesKHR(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    int fd,
    VkMemoryFdPropertiesKHR* pMemoryFdProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryFdPropertiesKHR<default_tag>(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    int fd,
    VkMemoryFdPropertiesKHR* pMemoryFdProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryHostPointerPropertiesEXT(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    const void* pHostPointer,
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetMemoryHostPointerPropertiesEXT<default_tag>(
    VkDevice device,
    VkExternalMemoryHandleTypeFlagBits handleType,
    const void* pHostPointer,
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetMicromapBuildSizesEXT(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkMicromapBuildInfoEXT* pBuildInfo,
    VkMicromapBuildSizesInfoEXT* pSizeInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetMicromapBuildSizesEXT<default_tag>(
    VkDevice device,
    VkAccelerationStructureBuildTypeKHR buildType,
    const VkMicromapBuildInfoEXT* pBuildInfo,
    VkMicromapBuildSizesInfoEXT* pSizeInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineBinaryDataKHR(
    VkDevice device,
    const VkPipelineBinaryDataInfoKHR* pInfo,
    VkPipelineBinaryKeyKHR* pPipelineBinaryKey,
    size_t* pPipelineBinaryDataSize,
    void* pPipelineBinaryData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineBinaryDataKHR<default_tag>(
    VkDevice device,
    const VkPipelineBinaryDataInfoKHR* pInfo,
    VkPipelineBinaryKeyKHR* pPipelineBinaryKey,
    size_t* pPipelineBinaryDataSize,
    void* pPipelineBinaryData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineCacheData(
    VkDevice device,
    VkPipelineCache pipelineCache,
    size_t* pDataSize,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineCacheData<default_tag>(
    VkDevice device,
    VkPipelineCache pipelineCache,
    size_t* pDataSize,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableInternalRepresentationsKHR(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableInternalRepresentationsKHR<default_tag>(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pInternalRepresentationCount,
    VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutablePropertiesKHR(
    VkDevice device,
    const VkPipelineInfoKHR* pPipelineInfo,
    uint32_t* pExecutableCount,
    VkPipelineExecutablePropertiesKHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutablePropertiesKHR<default_tag>(
    VkDevice device,
    const VkPipelineInfoKHR* pPipelineInfo,
    uint32_t* pExecutableCount,
    VkPipelineExecutablePropertiesKHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableStatisticsKHR(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pStatisticCount,
    VkPipelineExecutableStatisticKHR* pStatistics) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineExecutableStatisticsKHR<default_tag>(
    VkDevice device,
    const VkPipelineExecutableInfoKHR* pExecutableInfo,
    uint32_t* pStatisticCount,
    VkPipelineExecutableStatisticKHR* pStatistics);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR(
    VkDevice device,
    const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR* pPipelineKey) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR<default_tag>(
    VkDevice device,
    const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
    VkPipelineBinaryKeyKHR* pPipelineKey);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelinePropertiesEXT(
    VkDevice device,
    const VkPipelineInfoEXT* pPipelineInfo,
    VkBaseOutStructure* pPipelineProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelinePropertiesEXT<default_tag>(
    VkDevice device,
    const VkPipelineInfoEXT* pPipelineInfo,
    VkBaseOutStructure* pPipelineProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateData(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateData<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateDataEXT(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPrivateDataEXT<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetQueryPoolResults(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    size_t dataSize,
    void* pData,
    VkDeviceSize stride,
    VkQueryResultFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetQueryPoolResults<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount,
    size_t dataSize,
    void* pData,
    VkDeviceSize stride,
    VkQueryResultFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingShaderGroupHandlesKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetRayTracingShaderGroupHandlesKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t firstGroup,
    uint32_t groupCount,
    size_t dataSize,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkDeviceSize VKAPI_CALL layer_vkGetRayTracingShaderGroupStackSizeKHR(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t group,
    VkShaderGroupShaderKHR groupShader) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkDeviceSize VKAPI_CALL layer_vkGetRayTracingShaderGroupStackSizeKHR<default_tag>(
    VkDevice device,
    VkPipeline pipeline,
    uint32_t group,
    VkShaderGroupShaderKHR groupShader);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderAreaGranularity(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D* pGranularity) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderAreaGranularity<default_tag>(
    VkDevice device,
    VkRenderPass renderPass,
    VkExtent2D* pGranularity);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularity(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularity<default_tag>(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularityKHR(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetRenderingAreaGranularityKHR<default_tag>(
    VkDevice device,
    const VkRenderingAreaInfo* pRenderingAreaInfo,
    VkExtent2D* pGranularity);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT(
    VkDevice device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSamplerOpaqueCaptureDescriptorDataEXT<default_tag>(
    VkDevice device,
    const VkSamplerCaptureDescriptorDataInfoEXT* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValue(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValue<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValueKHR(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreCounterValueKHR<default_tag>(
    VkDevice device,
    VkSemaphore semaphore,
    uint64_t* pValue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreFdKHR(
    VkDevice device,
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
    int* pFd) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSemaphoreFdKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo,
    int* pFd);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetShaderBinaryDataEXT(
    VkDevice device,
    VkShaderEXT shader,
    size_t* pDataSize,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetShaderBinaryDataEXT<default_tag>(
    VkDevice device,
    VkShaderEXT shader,
    size_t* pDataSize,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleCreateInfoIdentifierEXT(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    VkShaderModuleIdentifierEXT* pIdentifier) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleCreateInfoIdentifierEXT<default_tag>(
    VkDevice device,
    const VkShaderModuleCreateInfo* pCreateInfo,
    VkShaderModuleIdentifierEXT* pIdentifier);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleIdentifierEXT(
    VkDevice device,
    VkShaderModule shaderModule,
    VkShaderModuleIdentifierEXT* pIdentifier) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetShaderModuleIdentifierEXT<default_tag>(
    VkDevice device,
    VkShaderModule shaderModule,
    VkShaderModuleIdentifierEXT* pIdentifier);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainCounterEXT(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSurfaceCounterFlagBitsEXT counter,
    uint64_t* pCounterValue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainCounterEXT<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    VkSurfaceCounterFlagBitsEXT counter,
    uint64_t* pCounterValue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainImagesKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint32_t* pSwapchainImageCount,
    VkImage* pSwapchainImages) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainImagesKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint32_t* pSwapchainImageCount,
    VkImage* pSwapchainImages);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainStatusKHR(
    VkDevice device,
    VkSwapchainKHR swapchain) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetSwapchainStatusKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetTensorMemoryRequirementsARM(
    VkDevice device,
    const VkTensorMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetTensorMemoryRequirementsARM<default_tag>(
    VkDevice device,
    const VkTensorMemoryRequirementsInfoARM* pInfo,
    VkMemoryRequirements2* pMemoryRequirements);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorOpaqueCaptureDescriptorDataARM(
    VkDevice device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorOpaqueCaptureDescriptorDataARM<default_tag>(
    VkDevice device,
    const VkTensorCaptureDescriptorDataInfoARM* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM(
    VkDevice device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetTensorViewOpaqueCaptureDescriptorDataARM<default_tag>(
    VkDevice device,
    const VkTensorViewCaptureDescriptorDataInfoARM* pInfo,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetValidationCacheDataEXT(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    size_t* pDataSize,
    void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetValidationCacheDataEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT validationCache,
    size_t* pDataSize,
    void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportFenceFdKHR(
    VkDevice device,
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportFenceFdKHR<default_tag>(
    VkDevice device,
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportSemaphoreFdKHR(
    VkDevice device,
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkImportSemaphoreFdKHR<default_tag>(
    VkDevice device,
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkInvalidateMappedMemoryRanges(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkInvalidateMappedMemoryRanges<default_tag>(
    VkDevice device,
    uint32_t memoryRangeCount,
    const VkMappedMemoryRange* pMemoryRanges);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkMemoryMapFlags flags,
    void** ppData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    VkDeviceSize offset,
    VkDeviceSize size,
    VkMemoryMapFlags flags,
    void** ppData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2<default_tag>(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2KHR(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMapMemory2KHR<default_tag>(
    VkDevice device,
    const VkMemoryMapInfo* pMemoryMapInfo,
    void** ppData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergePipelineCaches(
    VkDevice device,
    VkPipelineCache dstCache,
    uint32_t srcCacheCount,
    const VkPipelineCache* pSrcCaches) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergePipelineCaches<default_tag>(
    VkDevice device,
    VkPipelineCache dstCache,
    uint32_t srcCacheCount,
    const VkPipelineCache* pSrcCaches);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergeValidationCachesEXT(
    VkDevice device,
    VkValidationCacheEXT dstCache,
    uint32_t srcCacheCount,
    const VkValidationCacheEXT* pSrcCaches) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkMergeValidationCachesEXT<default_tag>(
    VkDevice device,
    VkValidationCacheEXT dstCache,
    uint32_t srcCacheCount,
    const VkValidationCacheEXT* pSrcCaches);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueBeginDebugUtilsLabelEXT(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueBeginDebugUtilsLabelEXT<default_tag>(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueBindSparse<default_tag>(
    VkQueue queue,
    uint32_t bindInfoCount,
    const VkBindSparseInfo* pBindInfo,
    VkFence fence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueEndDebugUtilsLabelEXT(
    VkQueue queue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueEndDebugUtilsLabelEXT<default_tag>(
    VkQueue queue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueInsertDebugUtilsLabelEXT(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkQueueInsertDebugUtilsLabelEXT<default_tag>(
    VkQueue queue,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<default_tag>(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR<default_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueWaitIdle(
    VkQueue queue) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueWaitIdle<default_tag>(
    VkQueue queue);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDeviceEventEXT(
    VkDevice device,
    const VkDeviceEventInfoEXT* pDeviceEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDeviceEventEXT<default_tag>(
    VkDevice device,
    const VkDeviceEventInfoEXT* pDeviceEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDisplayEventEXT(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayEventInfoEXT* pDisplayEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkRegisterDisplayEventEXT<default_tag>(
    VkDevice device,
    VkDisplayKHR display,
    const VkDisplayEventInfoEXT* pDisplayEventInfo,
    const VkAllocationCallbacks* pAllocator,
    VkFence* pFence);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseCapturedPipelineDataKHR(
    VkDevice device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseCapturedPipelineDataKHR<default_tag>(
    VkDevice device,
    const VkReleaseCapturedPipelineDataInfoKHR* pInfo,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkReleaseProfilingLockKHR(
    VkDevice device) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkReleaseProfilingLockKHR<default_tag>(
    VkDevice device);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesEXT(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseSwapchainImagesEXT<default_tag>(
    VkDevice device,
    const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer<default_tag>(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetDescriptorPool(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    VkDescriptorPoolResetFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetDescriptorPool<default_tag>(
    VkDevice device,
    VkDescriptorPool descriptorPool,
    VkDescriptorPoolResetFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetEvent(
    VkDevice device,
    VkEvent event) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetEvent<default_tag>(
    VkDevice device,
    VkEvent event);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetFences(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetFences<default_tag>(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPool(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPool<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPoolEXT(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkResetQueryPoolEXT<default_tag>(
    VkDevice device,
    VkQueryPool queryPool,
    uint32_t firstQuery,
    uint32_t queryCount);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectNameEXT(
    VkDevice device,
    const VkDebugUtilsObjectNameInfoEXT* pNameInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectNameEXT<default_tag>(
    VkDevice device,
    const VkDebugUtilsObjectNameInfoEXT* pNameInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectTagEXT(
    VkDevice device,
    const VkDebugUtilsObjectTagInfoEXT* pTagInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetDebugUtilsObjectTagEXT<default_tag>(
    VkDevice device,
    const VkDebugUtilsObjectTagInfoEXT* pTagInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSetDeviceMemoryPriorityEXT(
    VkDevice device,
    VkDeviceMemory memory,
    float priority) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkSetDeviceMemoryPriorityEXT<default_tag>(
    VkDevice device,
    VkDeviceMemory memory,
    float priority);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetEvent(
    VkDevice device,
    VkEvent event) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetEvent<default_tag>(
    VkDevice device,
    VkEvent event);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSetHdrMetadataEXT(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainKHR* pSwapchains,
    const VkHdrMetadataEXT* pMetadata) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkSetHdrMetadataEXT<default_tag>(
    VkDevice device,
    uint32_t swapchainCount,
    const VkSwapchainKHR* pSwapchains,
    const VkHdrMetadataEXT* pMetadata);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateData(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateData<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateDataEXT(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSetPrivateDataEXT<default_tag>(
    VkDevice device,
    VkObjectType objectType,
    uint64_t objectHandle,
    VkPrivateDataSlot privateDataSlot,
    uint64_t data);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphore(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphore<default_tag>(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphoreKHR(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkSignalSemaphoreKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreSignalInfo* pSignalInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayout(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayout<default_tag>(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayoutEXT(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkTransitionImageLayoutEXT<default_tag>(
    VkDevice device,
    uint32_t transitionCount,
    const VkHostImageLayoutTransitionInfo* pTransitions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPool<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPoolKHR(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkTrimCommandPoolKHR<default_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUnmapMemory(
    VkDevice device,
    VkDeviceMemory memory) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUnmapMemory<default_tag>(
    VkDevice device,
    VkDeviceMemory memory);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2<default_tag>(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2KHR(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkUnmapMemory2KHR<default_tag>(
    VkDevice device,
    const VkMemoryUnmapInfo* pMemoryUnmapInfo);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplate(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplate<default_tag>(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplateKHR(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSetWithTemplateKHR<default_tag>(
    VkDevice device,
    VkDescriptorSet descriptorSet,
    VkDescriptorUpdateTemplate descriptorUpdateTemplate,
    const void* pData);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSets(
    VkDevice device,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    const VkCopyDescriptorSet* pDescriptorCopies) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateDescriptorSets<default_tag>(
    VkDevice device,
    uint32_t descriptorWriteCount,
    const VkWriteDescriptorSet* pDescriptorWrites,
    uint32_t descriptorCopyCount,
    const VkCopyDescriptorSet* pDescriptorCopies);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetPipelineEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetPipelineEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetShaderEXT(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkUpdateIndirectExecutionSetShaderEXT<default_tag>(
    VkDevice device,
    VkIndirectExecutionSetEXT indirectExecutionSet,
    uint32_t executionSetWriteCount,
    const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForFences(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences,
    VkBool32 waitAll,
    uint64_t timeout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForFences<default_tag>(
    VkDevice device,
    uint32_t fenceCount,
    const VkFence* pFences,
    VkBool32 waitAll,
    uint64_t timeout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresent2KHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkPresentWait2InfoKHR* pPresentWait2Info) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresent2KHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    const VkPresentWait2InfoKHR* pPresentWait2Info);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresentKHR(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t presentId,
    uint64_t timeout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitForPresentKHR<default_tag>(
    VkDevice device,
    VkSwapchainKHR swapchain,
    uint64_t presentId,
    uint64_t timeout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphores(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphores<default_tag>(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphoresKHR(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWaitSemaphoresKHR<default_tag>(
    VkDevice device,
    const VkSemaphoreWaitInfo* pWaitInfo,
    uint64_t timeout);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteAccelerationStructuresPropertiesKHR(
    VkDevice device,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteAccelerationStructuresPropertiesKHR<default_tag>(
    VkDevice device,
    uint32_t accelerationStructureCount,
    const VkAccelerationStructureKHR* pAccelerationStructures,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteMicromapsPropertiesEXT(
    VkDevice device,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkWriteMicromapsPropertiesEXT<default_tag>(
    VkDevice device,
    uint32_t micromapCount,
    const VkMicromapEXT* pMicromaps,
    VkQueryType queryType,
    size_t dataSize,
    void* pData,
    size_t stride);

// clang-format on
