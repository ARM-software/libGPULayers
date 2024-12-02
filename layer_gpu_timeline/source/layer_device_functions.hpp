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

#include <vulkan/vulkan.h>

#include "framework/utils.hpp"

// Functions for command pools

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateCommandPool<user_tag>(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandPool<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyCommandPool<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator);

// Functions for command buffers

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateCommandBuffers<user_tag>(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult layer_vkBeginCommandBuffer<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdExecuteCommands<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkResetCommandBuffer<user_tag>(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkFreeCommandBuffers<user_tag>(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers);

// Functions for render passes

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass<user_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2<user_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR<user_tag>(
    VkDevice device,
    const VkRenderPassCreateInfo2* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkRenderPass* pRenderPass);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass<user_tag>(
    VkDevice device,
    VkRenderPass renderPass,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<user_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL  layer_vkCmdEndRendering<user_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL  layer_vkCmdEndRenderingKHR<user_tag>(
    VkCommandBuffer commandBuffer);

// Functions for draw calls

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDraw<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t vertexCount,
    uint32_t instanceCount,
    uint32_t firstVertex,
    uint32_t firstInstance);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexed<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t indexCount,
    uint32_t instanceCount,
    uint32_t firstIndex,
    int32_t vertexOffset,
    uint32_t firstInstance);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirect<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCount<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndexedIndirectCountKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirect<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    uint32_t drawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectByteCountEXT<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t instanceCount,
    uint32_t firstInstance,
    VkBuffer counterBuffer,
    VkDeviceSize counterBufferOffset,
    uint32_t counterOffset,
    uint32_t vertexStride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCount<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDrawIndirectCountKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset,
    VkBuffer countBuffer,
    VkDeviceSize countBufferOffset,
    uint32_t maxDrawCount,
    uint32_t stride);

// Functions for compute dispatches

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t baseGroupX,
    uint32_t baseGroupY,
    uint32_t baseGroupZ,
    uint32_t groupCountX,
    uint32_t groupCountY,
    uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect<user_tag>(
    VkCommandBuffer commandBuffer,
    VkBuffer buffer,
    VkDeviceSize offset);

// Commands for trace rays

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth);

// Functions for debug

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT<user_tag>(
    VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo);

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT<user_tag>(
    VkCommandBuffer commandBuffer);

// Functions for queues

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueuePresentKHR<user_tag>(
    VkQueue queue,
    const VkPresentInfoKHR* pPresentInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo* pSubmits,
    VkFence fence);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR<user_tag>(
    VkQueue queue,
    uint32_t submitCount,
    const VkSubmitInfo2* pSubmits,
    VkFence fence);
