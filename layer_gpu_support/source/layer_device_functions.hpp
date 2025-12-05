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

#pragma once

#include <vulkan/vulkan.h>

// Functions for render passes

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<user_tag>(VkCommandBuffer commandBuffer,
                                                                const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                VkSubpassContents contents);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<user_tag>(VkCommandBuffer commandBuffer,
                                                                 const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                 const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                    const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                    const VkSubpassBeginInfo* pSubpassBeginInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<user_tag>(VkCommandBuffer commandBuffer,
                                                               const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                  const VkRenderingInfo* pRenderingInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<user_tag>(VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering<user_tag>(VkCommandBuffer commandBuffer);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR<user_tag>(VkCommandBuffer commandBuffer);

// Functions for compute dispatches

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch<user_tag>(VkCommandBuffer commandBuffer,
                                                         uint32_t groupCountX,
                                                         uint32_t groupCountY,
                                                         uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase<user_tag>(VkCommandBuffer commandBuffer,
                                                             uint32_t baseGroupX,
                                                             uint32_t baseGroupY,
                                                             uint32_t baseGroupZ,
                                                             uint32_t groupCountX,
                                                             uint32_t groupCountY,
                                                             uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                uint32_t baseGroupX,
                                                                uint32_t baseGroupY,
                                                                uint32_t baseGroupZ,
                                                                uint32_t groupCountX,
                                                                uint32_t groupCountY,
                                                                uint32_t groupCountZ);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect<user_tag>(VkCommandBuffer commandBuffer,
                                                                 VkBuffer buffer,
                                                                 VkDeviceSize offset);

// Commands for trace rays

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                      VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdTraceRaysIndirectKHR<user_tag>(VkCommandBuffer commandBuffer,
                                              const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
                                              VkDeviceAddress indirectDeviceAddress);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdTraceRaysKHR<user_tag>(VkCommandBuffer commandBuffer,
                                      const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
                                      uint32_t width,
                                      uint32_t height,
                                      uint32_t depth);

// Commands for acceleration structure builds

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts);

// Commands for transfers

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                           VkBuffer dstBuffer,
                                                           VkDeviceSize dstOffset,
                                                           VkDeviceSize size,
                                                           uint32_t data);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                VkImage image,
                                                                VkImageLayout imageLayout,
                                                                const VkClearColorValue* pColor,
                                                                uint32_t rangeCount,
                                                                const VkImageSubresourceRange* pRanges);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                       VkImage image,
                                                                       VkImageLayout imageLayout,
                                                                       const VkClearDepthStencilValue* pDepthStencil,
                                                                       uint32_t rangeCount,
                                                                       const VkImageSubresourceRange* pRanges);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                           VkBuffer srcBuffer,
                                                           VkBuffer dstBuffer,
                                                           uint32_t regionCount,
                                                           const VkBufferCopy* pRegions);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2<user_tag>(VkCommandBuffer commandBuffer,
                                                            const VkCopyBufferInfo2* pCopyBufferInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                               const VkCopyBufferInfo2* pCopyBufferInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                  VkBuffer srcBuffer,
                                                                  VkImage dstImage,
                                                                  VkImageLayout dstImageLayout,
                                                                  uint32_t regionCount,
                                                                  const VkBufferImageCopy* pRegions);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyBufferToImage2<user_tag>(VkCommandBuffer commandBuffer,
                                            const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyBufferToImage2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                               const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage<user_tag>(VkCommandBuffer commandBuffer,
                                                          VkImage srcImage,
                                                          VkImageLayout srcImageLayout,
                                                          VkImage dstImage,
                                                          VkImageLayout dstImageLayout,
                                                          uint32_t regionCount,
                                                          const VkImageCopy* pRegions);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2<user_tag>(VkCommandBuffer commandBuffer,
                                                           const VkCopyImageInfo2* pCopyImageInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyImageInfo2* pCopyImageInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                                  VkImage srcImage,
                                                                  VkImageLayout srcImageLayout,
                                                                  VkBuffer dstBuffer,
                                                                  uint32_t regionCount,
                                                                  const VkBufferImageCopy* pRegions);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyImageToBuffer2<user_tag>(VkCommandBuffer commandBuffer,
                                            const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyImageToBuffer2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                               const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyAccelerationStructureKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                      const VkCopyAccelerationStructureInfoKHR* pInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyAccelerationStructureToMemoryKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyMemoryToAccelerationStructureKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo);

// Functions for queues

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkQueueSubmit2<user_tag>(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkQueueSubmit2KHR<user_tag>(VkQueue queue,
                                                                 uint32_t submitCount,
                                                                 const VkSubmitInfo2* pSubmits,
                                                                 VkFence fence);

// Functions for pipelines

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule<user_tag>(VkDevice device,
                                                                    const VkShaderModuleCreateInfo* pCreateInfo,
                                                                    const VkAllocationCallbacks* pAllocator,
                                                                    VkShaderModule* pShaderModule);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT<user_tag>(VkDevice device,
                                                                  uint32_t createInfoCount,
                                                                  const VkShaderCreateInfoEXT* pCreateInfos,
                                                                  const VkAllocationCallbacks* pAllocator,
                                                                  VkShaderEXT* pShaders);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR<user_tag>(VkDevice device,
                                                                   const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
                                                                   VkPipelineBinaryKeyKHR* pPipelineKey);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines<user_tag>(VkDevice device,
                                                                        VkPipelineCache pipelineCache,
                                                                        uint32_t createInfoCount,
                                                                        const VkComputePipelineCreateInfo* pCreateInfos,
                                                                        const VkAllocationCallbacks* pAllocator,
                                                                        VkPipeline* pPipelines);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkCreateGraphicsPipelines<user_tag>(VkDevice device,
                                              VkPipelineCache pipelineCache,
                                              uint32_t createInfoCount,
                                              const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                              const VkAllocationCallbacks* pAllocator,
                                              VkPipeline* pPipelines);

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkCreateRayTracingPipelinesKHR<user_tag>(VkDevice device,
                                                   VkDeferredOperationKHR deferredOperation,
                                                   VkPipelineCache pipelineCache,
                                                   uint32_t createInfoCount,
                                                   const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
                                                   const VkAllocationCallbacks* pAllocator,
                                                   VkPipeline* pPipelines);

// Functions for images

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage<user_tag>(VkDevice device,
                                                             const VkImageCreateInfo* pCreateInfo,
                                                             const VkAllocationCallbacks* pAllocator,
                                                             VkImage* pImage);

// Functions for swapchains

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR<user_tag>(VkDevice device,
                                                                    const VkSwapchainCreateInfoKHR* pCreateInfo,
                                                                    const VkAllocationCallbacks* pAllocator,
                                                                    VkSwapchainKHR* pSwapchain);

// Functions for external DMA-buf

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory<user_tag>(VkDevice device,
                                                                const VkMemoryAllocateInfo* pAllocateInfo,
                                                                const VkAllocationCallbacks* pAllocator,
                                                                VkDeviceMemory* pMemory);