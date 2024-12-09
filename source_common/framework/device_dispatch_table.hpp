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

#pragma once

#include <vulkan/vulkan.h>

#include "framework/device_functions.hpp"
#include "framework/utils.hpp"
#include "utils/misc.hpp"

#if __has_include ("layer_device_functions.hpp")
    #include "layer_device_functions.hpp"
#endif

/**
 * @brief Interception table lookup entry.
 */
struct DeviceInterceptTableEntry
{
    /**
     * @brief The function entrypoint name.
     */
    const char* name;

    /**
     * @brief The layer function pointer.
     */
    PFN_vkVoidFunction function;
};

#define ENTRY(fnc) { STR(fnc), reinterpret_cast<PFN_vkVoidFunction>(layer_##fnc<user_tag>) }

/**
 * @brief The device dispatch table used to call the driver.
 */
static const struct DeviceInterceptTableEntry deviceIntercepts[] = {
    ENTRY(vkAcquireNextImage2KHR),
    ENTRY(vkAcquireNextImageKHR),
    ENTRY(vkAcquireProfilingLockKHR),
    ENTRY(vkAllocateCommandBuffers),
    ENTRY(vkAllocateDescriptorSets),
    ENTRY(vkAllocateMemory),
    ENTRY(vkBeginCommandBuffer),
    ENTRY(vkBindBufferMemory),
    ENTRY(vkBindBufferMemory2),
    ENTRY(vkBindBufferMemory2KHR),
    ENTRY(vkBindImageMemory),
    ENTRY(vkBindImageMemory2),
    ENTRY(vkBindImageMemory2KHR),
    ENTRY(vkBuildAccelerationStructuresKHR),
    ENTRY(vkBuildMicromapsEXT),
    ENTRY(vkCmdBeginConditionalRenderingEXT),
    ENTRY(vkCmdBeginDebugUtilsLabelEXT),
    ENTRY(vkCmdBeginQuery),
    ENTRY(vkCmdBeginQueryIndexedEXT),
    ENTRY(vkCmdBeginRenderPass),
    ENTRY(vkCmdBeginRenderPass2),
    ENTRY(vkCmdBeginRenderPass2KHR),
    ENTRY(vkCmdBeginRendering),
    ENTRY(vkCmdBeginRenderingKHR),
    ENTRY(vkCmdBeginTransformFeedbackEXT),
    ENTRY(vkCmdBindDescriptorBufferEmbeddedSamplers2EXT),
    ENTRY(vkCmdBindDescriptorBufferEmbeddedSamplersEXT),
    ENTRY(vkCmdBindDescriptorBuffersEXT),
    ENTRY(vkCmdBindDescriptorSets),
    ENTRY(vkCmdBindDescriptorSets2KHR),
    ENTRY(vkCmdBindIndexBuffer),
    ENTRY(vkCmdBindIndexBuffer2KHR),
    ENTRY(vkCmdBindPipeline),
    ENTRY(vkCmdBindShadersEXT),
    ENTRY(vkCmdBindTransformFeedbackBuffersEXT),
    ENTRY(vkCmdBindVertexBuffers),
    ENTRY(vkCmdBindVertexBuffers2),
    ENTRY(vkCmdBindVertexBuffers2EXT),
    ENTRY(vkCmdBlitImage),
    ENTRY(vkCmdBlitImage2),
    ENTRY(vkCmdBlitImage2KHR),
    ENTRY(vkCmdBuildAccelerationStructuresIndirectKHR),
    ENTRY(vkCmdBuildAccelerationStructuresKHR),
    ENTRY(vkCmdBuildMicromapsEXT),
    ENTRY(vkCmdClearAttachments),
    ENTRY(vkCmdClearColorImage),
    ENTRY(vkCmdClearDepthStencilImage),
    ENTRY(vkCmdCopyAccelerationStructureKHR),
    ENTRY(vkCmdCopyAccelerationStructureToMemoryKHR),
    ENTRY(vkCmdCopyBuffer),
    ENTRY(vkCmdCopyBuffer2),
    ENTRY(vkCmdCopyBuffer2KHR),
    ENTRY(vkCmdCopyBufferToImage),
    ENTRY(vkCmdCopyBufferToImage2),
    ENTRY(vkCmdCopyBufferToImage2KHR),
    ENTRY(vkCmdCopyImage),
    ENTRY(vkCmdCopyImage2),
    ENTRY(vkCmdCopyImage2KHR),
    ENTRY(vkCmdCopyImageToBuffer),
    ENTRY(vkCmdCopyImageToBuffer2),
    ENTRY(vkCmdCopyImageToBuffer2KHR),
    ENTRY(vkCmdCopyMemoryToAccelerationStructureKHR),
    ENTRY(vkCmdCopyMemoryToMicromapEXT),
    ENTRY(vkCmdCopyMicromapEXT),
    ENTRY(vkCmdCopyMicromapToMemoryEXT),
    ENTRY(vkCmdCopyQueryPoolResults),
    ENTRY(vkCmdDebugMarkerBeginEXT),
    ENTRY(vkCmdDebugMarkerEndEXT),
    ENTRY(vkCmdDebugMarkerInsertEXT),
    ENTRY(vkCmdDispatch),
    ENTRY(vkCmdDispatchBase),
    ENTRY(vkCmdDispatchBaseKHR),
    ENTRY(vkCmdDispatchIndirect),
    ENTRY(vkCmdDraw),
    ENTRY(vkCmdDrawIndexed),
    ENTRY(vkCmdDrawIndexedIndirect),
    ENTRY(vkCmdDrawIndexedIndirectCount),
    ENTRY(vkCmdDrawIndexedIndirectCountKHR),
    ENTRY(vkCmdDrawIndirect),
    ENTRY(vkCmdDrawIndirectByteCountEXT),
    ENTRY(vkCmdDrawIndirectCount),
    ENTRY(vkCmdDrawIndirectCountKHR),
    ENTRY(vkCmdDrawMeshTasksEXT),
    ENTRY(vkCmdDrawMeshTasksIndirectCountEXT),
    ENTRY(vkCmdDrawMeshTasksIndirectEXT),
    ENTRY(vkCmdDrawMultiEXT),
    ENTRY(vkCmdDrawMultiIndexedEXT),
    ENTRY(vkCmdEndConditionalRenderingEXT),
    ENTRY(vkCmdEndDebugUtilsLabelEXT),
    ENTRY(vkCmdEndQuery),
    ENTRY(vkCmdEndQueryIndexedEXT),
    ENTRY(vkCmdEndRenderPass),
    ENTRY(vkCmdEndRenderPass2),
    ENTRY(vkCmdEndRenderPass2KHR),
    ENTRY(vkCmdEndRendering),
    ENTRY(vkCmdEndRenderingKHR),
    ENTRY(vkCmdEndTransformFeedbackEXT),
    ENTRY(vkCmdExecuteCommands),
    ENTRY(vkCmdFillBuffer),
    ENTRY(vkCmdInsertDebugUtilsLabelEXT),
    ENTRY(vkCmdNextSubpass),
    ENTRY(vkCmdNextSubpass2),
    ENTRY(vkCmdNextSubpass2KHR),
    ENTRY(vkCmdPipelineBarrier),
    ENTRY(vkCmdPipelineBarrier2),
    ENTRY(vkCmdPipelineBarrier2KHR),
    ENTRY(vkCmdPushConstants),
    ENTRY(vkCmdPushConstants2KHR),
    ENTRY(vkCmdPushDescriptorSet2KHR),
    ENTRY(vkCmdPushDescriptorSetKHR),
    ENTRY(vkCmdPushDescriptorSetWithTemplate2KHR),
    ENTRY(vkCmdPushDescriptorSetWithTemplateKHR),
    ENTRY(vkCmdResetEvent),
    ENTRY(vkCmdResetEvent2),
    ENTRY(vkCmdResetEvent2KHR),
    ENTRY(vkCmdResetQueryPool),
    ENTRY(vkCmdResolveImage),
    ENTRY(vkCmdResolveImage2),
    ENTRY(vkCmdResolveImage2KHR),
    ENTRY(vkCmdSetAlphaToCoverageEnableEXT),
    ENTRY(vkCmdSetAlphaToOneEnableEXT),
    ENTRY(vkCmdSetAttachmentFeedbackLoopEnableEXT),
    ENTRY(vkCmdSetBlendConstants),
    ENTRY(vkCmdSetColorBlendAdvancedEXT),
    ENTRY(vkCmdSetColorBlendEnableEXT),
    ENTRY(vkCmdSetColorBlendEquationEXT),
    ENTRY(vkCmdSetColorWriteEnableEXT),
    ENTRY(vkCmdSetColorWriteMaskEXT),
    ENTRY(vkCmdSetConservativeRasterizationModeEXT),
    ENTRY(vkCmdSetCoverageModulationModeNV),
    ENTRY(vkCmdSetCoverageModulationTableEnableNV),
    ENTRY(vkCmdSetCoverageModulationTableNV),
    ENTRY(vkCmdSetCoverageReductionModeNV),
    ENTRY(vkCmdSetCoverageToColorEnableNV),
    ENTRY(vkCmdSetCoverageToColorLocationNV),
    ENTRY(vkCmdSetCullMode),
    ENTRY(vkCmdSetCullModeEXT),
    ENTRY(vkCmdSetDepthBias),
    ENTRY(vkCmdSetDepthBias2EXT),
    ENTRY(vkCmdSetDepthBiasEnable),
    ENTRY(vkCmdSetDepthBiasEnableEXT),
    ENTRY(vkCmdSetDepthBounds),
    ENTRY(vkCmdSetDepthBoundsTestEnable),
    ENTRY(vkCmdSetDepthBoundsTestEnableEXT),
    ENTRY(vkCmdSetDepthClampEnableEXT),
    ENTRY(vkCmdSetDepthClipEnableEXT),
    ENTRY(vkCmdSetDepthClipNegativeOneToOneEXT),
    ENTRY(vkCmdSetDepthCompareOp),
    ENTRY(vkCmdSetDepthCompareOpEXT),
    ENTRY(vkCmdSetDepthTestEnable),
    ENTRY(vkCmdSetDepthTestEnableEXT),
    ENTRY(vkCmdSetDepthWriteEnable),
    ENTRY(vkCmdSetDepthWriteEnableEXT),
    ENTRY(vkCmdSetDescriptorBufferOffsets2EXT),
    ENTRY(vkCmdSetDescriptorBufferOffsetsEXT),
    ENTRY(vkCmdSetDeviceMask),
    ENTRY(vkCmdSetDeviceMaskKHR),
    ENTRY(vkCmdSetDiscardRectangleEXT),
    ENTRY(vkCmdSetDiscardRectangleEnableEXT),
    ENTRY(vkCmdSetDiscardRectangleModeEXT),
    ENTRY(vkCmdSetEvent),
    ENTRY(vkCmdSetEvent2),
    ENTRY(vkCmdSetEvent2KHR),
    ENTRY(vkCmdSetExtraPrimitiveOverestimationSizeEXT),
    ENTRY(vkCmdSetFragmentShadingRateKHR),
    ENTRY(vkCmdSetFrontFace),
    ENTRY(vkCmdSetFrontFaceEXT),
    ENTRY(vkCmdSetLineRasterizationModeEXT),
    ENTRY(vkCmdSetLineStippleEXT),
    ENTRY(vkCmdSetLineStippleEnableEXT),
    ENTRY(vkCmdSetLineStippleKHR),
    ENTRY(vkCmdSetLineWidth),
    ENTRY(vkCmdSetLogicOpEXT),
    ENTRY(vkCmdSetLogicOpEnableEXT),
    ENTRY(vkCmdSetPatchControlPointsEXT),
    ENTRY(vkCmdSetPolygonModeEXT),
    ENTRY(vkCmdSetPrimitiveRestartEnable),
    ENTRY(vkCmdSetPrimitiveRestartEnableEXT),
    ENTRY(vkCmdSetPrimitiveTopology),
    ENTRY(vkCmdSetPrimitiveTopologyEXT),
    ENTRY(vkCmdSetProvokingVertexModeEXT),
    ENTRY(vkCmdSetRasterizationSamplesEXT),
    ENTRY(vkCmdSetRasterizationStreamEXT),
    ENTRY(vkCmdSetRasterizerDiscardEnable),
    ENTRY(vkCmdSetRasterizerDiscardEnableEXT),
    ENTRY(vkCmdSetRayTracingPipelineStackSizeKHR),
    ENTRY(vkCmdSetRenderingAttachmentLocationsKHR),
    ENTRY(vkCmdSetRenderingInputAttachmentIndicesKHR),
    ENTRY(vkCmdSetRepresentativeFragmentTestEnableNV),
    ENTRY(vkCmdSetSampleLocationsEXT),
    ENTRY(vkCmdSetSampleLocationsEnableEXT),
    ENTRY(vkCmdSetSampleMaskEXT),
    ENTRY(vkCmdSetScissor),
    ENTRY(vkCmdSetScissorWithCount),
    ENTRY(vkCmdSetScissorWithCountEXT),
    ENTRY(vkCmdSetShadingRateImageEnableNV),
    ENTRY(vkCmdSetStencilCompareMask),
    ENTRY(vkCmdSetStencilOp),
    ENTRY(vkCmdSetStencilOpEXT),
    ENTRY(vkCmdSetStencilReference),
    ENTRY(vkCmdSetStencilTestEnable),
    ENTRY(vkCmdSetStencilTestEnableEXT),
    ENTRY(vkCmdSetStencilWriteMask),
    ENTRY(vkCmdSetTessellationDomainOriginEXT),
    ENTRY(vkCmdSetVertexInputEXT),
    ENTRY(vkCmdSetViewport),
    ENTRY(vkCmdSetViewportSwizzleNV),
    ENTRY(vkCmdSetViewportWScalingEnableNV),
    ENTRY(vkCmdSetViewportWithCount),
    ENTRY(vkCmdSetViewportWithCountEXT),
    ENTRY(vkCmdTraceRaysIndirect2KHR),
    ENTRY(vkCmdTraceRaysIndirectKHR),
    ENTRY(vkCmdTraceRaysKHR),
    ENTRY(vkCmdUpdateBuffer),
    ENTRY(vkCmdWaitEvents),
    ENTRY(vkCmdWaitEvents2),
    ENTRY(vkCmdWaitEvents2KHR),
    ENTRY(vkCmdWriteAccelerationStructuresPropertiesKHR),
    ENTRY(vkCmdWriteBufferMarker2AMD),
    ENTRY(vkCmdWriteMicromapsPropertiesEXT),
    ENTRY(vkCmdWriteTimestamp),
    ENTRY(vkCmdWriteTimestamp2),
    ENTRY(vkCmdWriteTimestamp2KHR),
    ENTRY(vkCopyAccelerationStructureKHR),
    ENTRY(vkCopyAccelerationStructureToMemoryKHR),
    ENTRY(vkCopyImageToImageEXT),
    ENTRY(vkCopyImageToMemoryEXT),
    ENTRY(vkCopyMemoryToAccelerationStructureKHR),
    ENTRY(vkCopyMemoryToImageEXT),
    ENTRY(vkCopyMemoryToMicromapEXT),
    ENTRY(vkCopyMicromapEXT),
    ENTRY(vkCopyMicromapToMemoryEXT),
    ENTRY(vkCreateAccelerationStructureKHR),
    ENTRY(vkCreateBuffer),
    ENTRY(vkCreateBufferView),
    ENTRY(vkCreateCommandPool),
    ENTRY(vkCreateComputePipelines),
    ENTRY(vkCreateDeferredOperationKHR),
    ENTRY(vkCreateDescriptorPool),
    ENTRY(vkCreateDescriptorSetLayout),
    ENTRY(vkCreateDescriptorUpdateTemplate),
    ENTRY(vkCreateDescriptorUpdateTemplateKHR),
    ENTRY(vkCreateEvent),
    ENTRY(vkCreateFence),
    ENTRY(vkCreateFramebuffer),
    ENTRY(vkCreateGraphicsPipelines),
    ENTRY(vkCreateImage),
    ENTRY(vkCreateImageView),
    ENTRY(vkCreateMicromapEXT),
    ENTRY(vkCreatePipelineBinariesKHR),
    ENTRY(vkCreatePipelineCache),
    ENTRY(vkCreatePipelineLayout),
    ENTRY(vkCreatePrivateDataSlot),
    ENTRY(vkCreatePrivateDataSlotEXT),
    ENTRY(vkCreateQueryPool),
    ENTRY(vkCreateRayTracingPipelinesKHR),
    ENTRY(vkCreateRenderPass),
    ENTRY(vkCreateRenderPass2),
    ENTRY(vkCreateRenderPass2KHR),
    ENTRY(vkCreateSampler),
    ENTRY(vkCreateSamplerYcbcrConversion),
    ENTRY(vkCreateSamplerYcbcrConversionKHR),
    ENTRY(vkCreateSemaphore),
    ENTRY(vkCreateShaderModule),
    ENTRY(vkCreateShadersEXT),
    ENTRY(vkCreateSharedSwapchainsKHR),
    ENTRY(vkCreateSwapchainKHR),
    ENTRY(vkCreateValidationCacheEXT),
    ENTRY(vkDebugMarkerSetObjectNameEXT),
    ENTRY(vkDebugMarkerSetObjectTagEXT),
    ENTRY(vkDeferredOperationJoinKHR),
    ENTRY(vkDestroyAccelerationStructureKHR),
    ENTRY(vkDestroyBuffer),
    ENTRY(vkDestroyBufferView),
    ENTRY(vkDestroyCommandPool),
    ENTRY(vkDestroyDeferredOperationKHR),
    ENTRY(vkDestroyDescriptorPool),
    ENTRY(vkDestroyDescriptorSetLayout),
    ENTRY(vkDestroyDescriptorUpdateTemplate),
    ENTRY(vkDestroyDescriptorUpdateTemplateKHR),
    ENTRY(vkDestroyDevice),
    ENTRY(vkDestroyEvent),
    ENTRY(vkDestroyFence),
    ENTRY(vkDestroyFramebuffer),
    ENTRY(vkDestroyImage),
    ENTRY(vkDestroyImageView),
    ENTRY(vkDestroyMicromapEXT),
    ENTRY(vkDestroyPipeline),
    ENTRY(vkDestroyPipelineBinaryKHR),
    ENTRY(vkDestroyPipelineCache),
    ENTRY(vkDestroyPipelineLayout),
    ENTRY(vkDestroyPrivateDataSlot),
    ENTRY(vkDestroyPrivateDataSlotEXT),
    ENTRY(vkDestroyQueryPool),
    ENTRY(vkDestroyRenderPass),
    ENTRY(vkDestroySampler),
    ENTRY(vkDestroySamplerYcbcrConversion),
    ENTRY(vkDestroySamplerYcbcrConversionKHR),
    ENTRY(vkDestroySemaphore),
    ENTRY(vkDestroyShaderEXT),
    ENTRY(vkDestroyShaderModule),
    ENTRY(vkDestroySwapchainKHR),
    ENTRY(vkDestroyValidationCacheEXT),
    ENTRY(vkDeviceWaitIdle),
    ENTRY(vkDisplayPowerControlEXT),
    ENTRY(vkEndCommandBuffer),
    ENTRY(vkFlushMappedMemoryRanges),
    ENTRY(vkFreeCommandBuffers),
    ENTRY(vkFreeDescriptorSets),
    ENTRY(vkFreeMemory),
    ENTRY(vkGetAccelerationStructureBuildSizesKHR),
    ENTRY(vkGetAccelerationStructureDeviceAddressKHR),
    ENTRY(vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT),
    ENTRY(vkGetBufferDeviceAddress),
    ENTRY(vkGetBufferDeviceAddressEXT),
    ENTRY(vkGetBufferDeviceAddressKHR),
    ENTRY(vkGetBufferMemoryRequirements),
    ENTRY(vkGetBufferMemoryRequirements2),
    ENTRY(vkGetBufferMemoryRequirements2KHR),
    ENTRY(vkGetBufferOpaqueCaptureAddress),
    ENTRY(vkGetBufferOpaqueCaptureAddressKHR),
    ENTRY(vkGetBufferOpaqueCaptureDescriptorDataEXT),
    ENTRY(vkGetCalibratedTimestampsEXT),
    ENTRY(vkGetCalibratedTimestampsKHR),
    ENTRY(vkGetDeferredOperationMaxConcurrencyKHR),
    ENTRY(vkGetDeferredOperationResultKHR),
    ENTRY(vkGetDescriptorEXT),
    ENTRY(vkGetDescriptorSetLayoutBindingOffsetEXT),
    ENTRY(vkGetDescriptorSetLayoutSizeEXT),
    ENTRY(vkGetDescriptorSetLayoutSupport),
    ENTRY(vkGetDescriptorSetLayoutSupportKHR),
    ENTRY(vkGetDeviceAccelerationStructureCompatibilityKHR),
    ENTRY(vkGetDeviceBufferMemoryRequirements),
    ENTRY(vkGetDeviceBufferMemoryRequirementsKHR),
    ENTRY(vkGetDeviceFaultInfoEXT),
    ENTRY(vkGetDeviceGroupPeerMemoryFeatures),
    ENTRY(vkGetDeviceGroupPeerMemoryFeaturesKHR),
    ENTRY(vkGetDeviceGroupPresentCapabilitiesKHR),
    ENTRY(vkGetDeviceGroupSurfacePresentModesKHR),
    ENTRY(vkGetDeviceImageMemoryRequirements),
    ENTRY(vkGetDeviceImageMemoryRequirementsKHR),
    ENTRY(vkGetDeviceImageSparseMemoryRequirements),
    ENTRY(vkGetDeviceImageSparseMemoryRequirementsKHR),
    ENTRY(vkGetDeviceImageSubresourceLayoutKHR),
    ENTRY(vkGetDeviceMemoryCommitment),
    ENTRY(vkGetDeviceMemoryOpaqueCaptureAddress),
    ENTRY(vkGetDeviceMemoryOpaqueCaptureAddressKHR),
    ENTRY(vkGetDeviceMicromapCompatibilityEXT),
    ENTRY(vkGetDeviceQueue),
    ENTRY(vkGetDeviceQueue2),
    ENTRY(vkGetEventStatus),
    ENTRY(vkGetFenceFdKHR),
    ENTRY(vkGetFenceStatus),
    ENTRY(vkGetImageDrmFormatModifierPropertiesEXT),
    ENTRY(vkGetImageMemoryRequirements),
    ENTRY(vkGetImageMemoryRequirements2),
    ENTRY(vkGetImageMemoryRequirements2KHR),
    ENTRY(vkGetImageOpaqueCaptureDescriptorDataEXT),
    ENTRY(vkGetImageSparseMemoryRequirements),
    ENTRY(vkGetImageSparseMemoryRequirements2),
    ENTRY(vkGetImageSparseMemoryRequirements2KHR),
    ENTRY(vkGetImageSubresourceLayout),
    ENTRY(vkGetImageSubresourceLayout2EXT),
    ENTRY(vkGetImageSubresourceLayout2KHR),
    ENTRY(vkGetImageViewOpaqueCaptureDescriptorDataEXT),
    ENTRY(vkGetMemoryFdKHR),
    ENTRY(vkGetMemoryFdPropertiesKHR),
    ENTRY(vkGetMemoryHostPointerPropertiesEXT),
    ENTRY(vkGetMicromapBuildSizesEXT),
    ENTRY(vkGetPipelineBinaryDataKHR),
    ENTRY(vkGetPipelineCacheData),
    ENTRY(vkGetPipelineExecutableInternalRepresentationsKHR),
    ENTRY(vkGetPipelineExecutablePropertiesKHR),
    ENTRY(vkGetPipelineExecutableStatisticsKHR),
    ENTRY(vkGetPipelineKeyKHR),
    ENTRY(vkGetPipelinePropertiesEXT),
    ENTRY(vkGetPrivateData),
    ENTRY(vkGetPrivateDataEXT),
    ENTRY(vkGetQueryPoolResults),
    ENTRY(vkGetQueueCheckpointData2NV),
    ENTRY(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR),
    ENTRY(vkGetRayTracingShaderGroupHandlesKHR),
    ENTRY(vkGetRayTracingShaderGroupStackSizeKHR),
    ENTRY(vkGetRenderAreaGranularity),
    ENTRY(vkGetRenderingAreaGranularityKHR),
    ENTRY(vkGetSamplerOpaqueCaptureDescriptorDataEXT),
    ENTRY(vkGetSemaphoreCounterValue),
    ENTRY(vkGetSemaphoreCounterValueKHR),
    ENTRY(vkGetSemaphoreFdKHR),
    ENTRY(vkGetShaderBinaryDataEXT),
    ENTRY(vkGetShaderModuleCreateInfoIdentifierEXT),
    ENTRY(vkGetShaderModuleIdentifierEXT),
    ENTRY(vkGetSwapchainCounterEXT),
    ENTRY(vkGetSwapchainImagesKHR),
    ENTRY(vkGetSwapchainStatusKHR),
    ENTRY(vkGetValidationCacheDataEXT),
    ENTRY(vkImportFenceFdKHR),
    ENTRY(vkImportSemaphoreFdKHR),
    ENTRY(vkInvalidateMappedMemoryRanges),
    ENTRY(vkMapMemory),
    ENTRY(vkMapMemory2KHR),
    ENTRY(vkMergePipelineCaches),
    ENTRY(vkMergeValidationCachesEXT),
    ENTRY(vkQueueBeginDebugUtilsLabelEXT),
    ENTRY(vkQueueBindSparse),
    ENTRY(vkQueueEndDebugUtilsLabelEXT),
    ENTRY(vkQueueInsertDebugUtilsLabelEXT),
    ENTRY(vkQueuePresentKHR),
    ENTRY(vkQueueSubmit),
    ENTRY(vkQueueSubmit2),
    ENTRY(vkQueueSubmit2KHR),
    ENTRY(vkQueueWaitIdle),
    ENTRY(vkRegisterDeviceEventEXT),
    ENTRY(vkRegisterDisplayEventEXT),
    ENTRY(vkReleaseCapturedPipelineDataKHR),
    ENTRY(vkReleaseProfilingLockKHR),
    ENTRY(vkReleaseSwapchainImagesEXT),
    ENTRY(vkResetCommandBuffer),
    ENTRY(vkResetCommandPool),
    ENTRY(vkResetDescriptorPool),
    ENTRY(vkResetEvent),
    ENTRY(vkResetFences),
    ENTRY(vkResetQueryPool),
    ENTRY(vkResetQueryPoolEXT),
    ENTRY(vkSetDebugUtilsObjectNameEXT),
    ENTRY(vkSetDebugUtilsObjectTagEXT),
    ENTRY(vkSetDeviceMemoryPriorityEXT),
    ENTRY(vkSetEvent),
    ENTRY(vkSetHdrMetadataEXT),
    ENTRY(vkSetPrivateData),
    ENTRY(vkSetPrivateDataEXT),
    ENTRY(vkSignalSemaphore),
    ENTRY(vkSignalSemaphoreKHR),
    ENTRY(vkTransitionImageLayoutEXT),
    ENTRY(vkTrimCommandPool),
    ENTRY(vkTrimCommandPoolKHR),
    ENTRY(vkUnmapMemory),
    ENTRY(vkUnmapMemory2KHR),
    ENTRY(vkUpdateDescriptorSetWithTemplate),
    ENTRY(vkUpdateDescriptorSetWithTemplateKHR),
    ENTRY(vkUpdateDescriptorSets),
    ENTRY(vkWaitForFences),
    ENTRY(vkWaitForPresentKHR),
    ENTRY(vkWaitSemaphores),
    ENTRY(vkWaitSemaphoresKHR),
    ENTRY(vkWriteAccelerationStructuresPropertiesKHR),
    ENTRY(vkWriteMicromapsPropertiesEXT),
};

#undef ENTRY


struct DeviceDispatchTable {
    PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;

    PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
    PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
    PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
    PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
    PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
    PFN_vkAllocateMemory vkAllocateMemory;
    PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
    PFN_vkBindBufferMemory vkBindBufferMemory;
    PFN_vkBindBufferMemory2 vkBindBufferMemory2;
    PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR;
    PFN_vkBindImageMemory vkBindImageMemory;
    PFN_vkBindImageMemory2 vkBindImageMemory2;
    PFN_vkBindImageMemory2KHR vkBindImageMemory2KHR;
    PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
    PFN_vkBuildMicromapsEXT vkBuildMicromapsEXT;
    PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
    PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdBeginQuery vkCmdBeginQuery;
    PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
    PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
    PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
    PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR;
    PFN_vkCmdBeginRendering vkCmdBeginRendering;
    PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR;
    PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT vkCmdBindDescriptorBufferEmbeddedSamplers2EXT;
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT vkCmdBindDescriptorBufferEmbeddedSamplersEXT;
    PFN_vkCmdBindDescriptorBuffersEXT vkCmdBindDescriptorBuffersEXT;
    PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
    PFN_vkCmdBindDescriptorSets2KHR vkCmdBindDescriptorSets2KHR;
    PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
    PFN_vkCmdBindIndexBuffer2KHR vkCmdBindIndexBuffer2KHR;
    PFN_vkCmdBindPipeline vkCmdBindPipeline;
    PFN_vkCmdBindShadersEXT vkCmdBindShadersEXT;
    PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
    PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
    PFN_vkCmdBindVertexBuffers2 vkCmdBindVertexBuffers2;
    PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
    PFN_vkCmdBlitImage vkCmdBlitImage;
    PFN_vkCmdBlitImage2 vkCmdBlitImage2;
    PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR;
    PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR;
    PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
    PFN_vkCmdBuildMicromapsEXT vkCmdBuildMicromapsEXT;
    PFN_vkCmdClearAttachments vkCmdClearAttachments;
    PFN_vkCmdClearColorImage vkCmdClearColorImage;
    PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
    PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
    PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
    PFN_vkCmdCopyBuffer2 vkCmdCopyBuffer2;
    PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR;
    PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
    PFN_vkCmdCopyBufferToImage2 vkCmdCopyBufferToImage2;
    PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR;
    PFN_vkCmdCopyImage vkCmdCopyImage;
    PFN_vkCmdCopyImage2 vkCmdCopyImage2;
    PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR;
    PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
    PFN_vkCmdCopyImageToBuffer2 vkCmdCopyImageToBuffer2;
    PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
    PFN_vkCmdCopyMemoryToMicromapEXT vkCmdCopyMemoryToMicromapEXT;
    PFN_vkCmdCopyMicromapEXT vkCmdCopyMicromapEXT;
    PFN_vkCmdCopyMicromapToMemoryEXT vkCmdCopyMicromapToMemoryEXT;
    PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
    PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
    PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
    PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
    PFN_vkCmdDispatch vkCmdDispatch;
    PFN_vkCmdDispatchBase vkCmdDispatchBase;
    PFN_vkCmdDispatchBaseKHR vkCmdDispatchBaseKHR;
    PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
    PFN_vkCmdDraw vkCmdDraw;
    PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
    PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
    PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
    PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR;
    PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
    PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
    PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
    PFN_vkCmdDrawIndirectCountKHR vkCmdDrawIndirectCountKHR;
    PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT;
    PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT;
    PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT;
    PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT;
    PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT;
    PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
    PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
    PFN_vkCmdEndQuery vkCmdEndQuery;
    PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
    PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
    PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
    PFN_vkCmdEndRenderPass2KHR vkCmdEndRenderPass2KHR;
    PFN_vkCmdEndRendering vkCmdEndRendering;
    PFN_vkCmdEndRenderingKHR vkCmdEndRenderingKHR;
    PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
    PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
    PFN_vkCmdFillBuffer vkCmdFillBuffer;
    PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
    PFN_vkCmdNextSubpass vkCmdNextSubpass;
    PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
    PFN_vkCmdNextSubpass2KHR vkCmdNextSubpass2KHR;
    PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
    PFN_vkCmdPipelineBarrier2 vkCmdPipelineBarrier2;
    PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR;
    PFN_vkCmdPushConstants vkCmdPushConstants;
    PFN_vkCmdPushConstants2KHR vkCmdPushConstants2KHR;
    PFN_vkCmdPushDescriptorSet2KHR vkCmdPushDescriptorSet2KHR;
    PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
    PFN_vkCmdPushDescriptorSetWithTemplate2KHR vkCmdPushDescriptorSetWithTemplate2KHR;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
    PFN_vkCmdResetEvent vkCmdResetEvent;
    PFN_vkCmdResetEvent2 vkCmdResetEvent2;
    PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR;
    PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
    PFN_vkCmdResolveImage vkCmdResolveImage;
    PFN_vkCmdResolveImage2 vkCmdResolveImage2;
    PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR;
    PFN_vkCmdSetAlphaToCoverageEnableEXT vkCmdSetAlphaToCoverageEnableEXT;
    PFN_vkCmdSetAlphaToOneEnableEXT vkCmdSetAlphaToOneEnableEXT;
    PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT;
    PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
    PFN_vkCmdSetColorBlendAdvancedEXT vkCmdSetColorBlendAdvancedEXT;
    PFN_vkCmdSetColorBlendEnableEXT vkCmdSetColorBlendEnableEXT;
    PFN_vkCmdSetColorBlendEquationEXT vkCmdSetColorBlendEquationEXT;
    PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT;
    PFN_vkCmdSetColorWriteMaskEXT vkCmdSetColorWriteMaskEXT;
    PFN_vkCmdSetConservativeRasterizationModeEXT vkCmdSetConservativeRasterizationModeEXT;
    PFN_vkCmdSetCoverageModulationModeNV vkCmdSetCoverageModulationModeNV;
    PFN_vkCmdSetCoverageModulationTableEnableNV vkCmdSetCoverageModulationTableEnableNV;
    PFN_vkCmdSetCoverageModulationTableNV vkCmdSetCoverageModulationTableNV;
    PFN_vkCmdSetCoverageReductionModeNV vkCmdSetCoverageReductionModeNV;
    PFN_vkCmdSetCoverageToColorEnableNV vkCmdSetCoverageToColorEnableNV;
    PFN_vkCmdSetCoverageToColorLocationNV vkCmdSetCoverageToColorLocationNV;
    PFN_vkCmdSetCullMode vkCmdSetCullMode;
    PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
    PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
    PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT;
    PFN_vkCmdSetDepthBiasEnable vkCmdSetDepthBiasEnable;
    PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT;
    PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
    PFN_vkCmdSetDepthBoundsTestEnable vkCmdSetDepthBoundsTestEnable;
    PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
    PFN_vkCmdSetDepthClampEnableEXT vkCmdSetDepthClampEnableEXT;
    PFN_vkCmdSetDepthClipEnableEXT vkCmdSetDepthClipEnableEXT;
    PFN_vkCmdSetDepthClipNegativeOneToOneEXT vkCmdSetDepthClipNegativeOneToOneEXT;
    PFN_vkCmdSetDepthCompareOp vkCmdSetDepthCompareOp;
    PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
    PFN_vkCmdSetDepthTestEnable vkCmdSetDepthTestEnable;
    PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
    PFN_vkCmdSetDepthWriteEnable vkCmdSetDepthWriteEnable;
    PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
    PFN_vkCmdSetDescriptorBufferOffsets2EXT vkCmdSetDescriptorBufferOffsets2EXT;
    PFN_vkCmdSetDescriptorBufferOffsetsEXT vkCmdSetDescriptorBufferOffsetsEXT;
    PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
    PFN_vkCmdSetDeviceMaskKHR vkCmdSetDeviceMaskKHR;
    PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
    PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT;
    PFN_vkCmdSetDiscardRectangleModeEXT vkCmdSetDiscardRectangleModeEXT;
    PFN_vkCmdSetEvent vkCmdSetEvent;
    PFN_vkCmdSetEvent2 vkCmdSetEvent2;
    PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR;
    PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT;
    PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR;
    PFN_vkCmdSetFrontFace vkCmdSetFrontFace;
    PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
    PFN_vkCmdSetLineRasterizationModeEXT vkCmdSetLineRasterizationModeEXT;
    PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
    PFN_vkCmdSetLineStippleEnableEXT vkCmdSetLineStippleEnableEXT;
    PFN_vkCmdSetLineStippleKHR vkCmdSetLineStippleKHR;
    PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
    PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT;
    PFN_vkCmdSetLogicOpEnableEXT vkCmdSetLogicOpEnableEXT;
    PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT;
    PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
    PFN_vkCmdSetPrimitiveRestartEnable vkCmdSetPrimitiveRestartEnable;
    PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT;
    PFN_vkCmdSetPrimitiveTopology vkCmdSetPrimitiveTopology;
    PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
    PFN_vkCmdSetProvokingVertexModeEXT vkCmdSetProvokingVertexModeEXT;
    PFN_vkCmdSetRasterizationSamplesEXT vkCmdSetRasterizationSamplesEXT;
    PFN_vkCmdSetRasterizationStreamEXT vkCmdSetRasterizationStreamEXT;
    PFN_vkCmdSetRasterizerDiscardEnable vkCmdSetRasterizerDiscardEnable;
    PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT;
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
    PFN_vkCmdSetRenderingAttachmentLocationsKHR vkCmdSetRenderingAttachmentLocationsKHR;
    PFN_vkCmdSetRenderingInputAttachmentIndicesKHR vkCmdSetRenderingInputAttachmentIndicesKHR;
    PFN_vkCmdSetRepresentativeFragmentTestEnableNV vkCmdSetRepresentativeFragmentTestEnableNV;
    PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
    PFN_vkCmdSetSampleLocationsEnableEXT vkCmdSetSampleLocationsEnableEXT;
    PFN_vkCmdSetSampleMaskEXT vkCmdSetSampleMaskEXT;
    PFN_vkCmdSetScissor vkCmdSetScissor;
    PFN_vkCmdSetScissorWithCount vkCmdSetScissorWithCount;
    PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
    PFN_vkCmdSetShadingRateImageEnableNV vkCmdSetShadingRateImageEnableNV;
    PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
    PFN_vkCmdSetStencilOp vkCmdSetStencilOp;
    PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
    PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
    PFN_vkCmdSetStencilTestEnable vkCmdSetStencilTestEnable;
    PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
    PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
    PFN_vkCmdSetTessellationDomainOriginEXT vkCmdSetTessellationDomainOriginEXT;
    PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT;
    PFN_vkCmdSetViewport vkCmdSetViewport;
    PFN_vkCmdSetViewportSwizzleNV vkCmdSetViewportSwizzleNV;
    PFN_vkCmdSetViewportWScalingEnableNV vkCmdSetViewportWScalingEnableNV;
    PFN_vkCmdSetViewportWithCount vkCmdSetViewportWithCount;
    PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
    PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR;
    PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
    PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
    PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
    PFN_vkCmdWaitEvents vkCmdWaitEvents;
    PFN_vkCmdWaitEvents2 vkCmdWaitEvents2;
    PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
    PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD;
    PFN_vkCmdWriteMicromapsPropertiesEXT vkCmdWriteMicromapsPropertiesEXT;
    PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
    PFN_vkCmdWriteTimestamp2 vkCmdWriteTimestamp2;
    PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR;
    PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
    PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
    PFN_vkCopyImageToImageEXT vkCopyImageToImageEXT;
    PFN_vkCopyImageToMemoryEXT vkCopyImageToMemoryEXT;
    PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
    PFN_vkCopyMemoryToImageEXT vkCopyMemoryToImageEXT;
    PFN_vkCopyMemoryToMicromapEXT vkCopyMemoryToMicromapEXT;
    PFN_vkCopyMicromapEXT vkCopyMicromapEXT;
    PFN_vkCopyMicromapToMemoryEXT vkCopyMicromapToMemoryEXT;
    PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
    PFN_vkCreateBuffer vkCreateBuffer;
    PFN_vkCreateBufferView vkCreateBufferView;
    PFN_vkCreateCommandPool vkCreateCommandPool;
    PFN_vkCreateComputePipelines vkCreateComputePipelines;
    PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
    PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
    PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
    PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
    PFN_vkCreateDescriptorUpdateTemplateKHR vkCreateDescriptorUpdateTemplateKHR;
    PFN_vkCreateEvent vkCreateEvent;
    PFN_vkCreateFence vkCreateFence;
    PFN_vkCreateFramebuffer vkCreateFramebuffer;
    PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
    PFN_vkCreateImage vkCreateImage;
    PFN_vkCreateImageView vkCreateImageView;
    PFN_vkCreateMicromapEXT vkCreateMicromapEXT;
    PFN_vkCreatePipelineBinariesKHR vkCreatePipelineBinariesKHR;
    PFN_vkCreatePipelineCache vkCreatePipelineCache;
    PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
    PFN_vkCreatePrivateDataSlot vkCreatePrivateDataSlot;
    PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
    PFN_vkCreateQueryPool vkCreateQueryPool;
    PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
    PFN_vkCreateRenderPass vkCreateRenderPass;
    PFN_vkCreateRenderPass2 vkCreateRenderPass2;
    PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR;
    PFN_vkCreateSampler vkCreateSampler;
    PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
    PFN_vkCreateSamplerYcbcrConversionKHR vkCreateSamplerYcbcrConversionKHR;
    PFN_vkCreateSemaphore vkCreateSemaphore;
    PFN_vkCreateShaderModule vkCreateShaderModule;
    PFN_vkCreateShadersEXT vkCreateShadersEXT;
    PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
    PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
    PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
    PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
    PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
    PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
    PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
    PFN_vkDestroyBuffer vkDestroyBuffer;
    PFN_vkDestroyBufferView vkDestroyBufferView;
    PFN_vkDestroyCommandPool vkDestroyCommandPool;
    PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
    PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
    PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
    PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
    PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR;
    PFN_vkDestroyDevice vkDestroyDevice;
    PFN_vkDestroyEvent vkDestroyEvent;
    PFN_vkDestroyFence vkDestroyFence;
    PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
    PFN_vkDestroyImage vkDestroyImage;
    PFN_vkDestroyImageView vkDestroyImageView;
    PFN_vkDestroyMicromapEXT vkDestroyMicromapEXT;
    PFN_vkDestroyPipeline vkDestroyPipeline;
    PFN_vkDestroyPipelineBinaryKHR vkDestroyPipelineBinaryKHR;
    PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
    PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
    PFN_vkDestroyPrivateDataSlot vkDestroyPrivateDataSlot;
    PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
    PFN_vkDestroyQueryPool vkDestroyQueryPool;
    PFN_vkDestroyRenderPass vkDestroyRenderPass;
    PFN_vkDestroySampler vkDestroySampler;
    PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
    PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR;
    PFN_vkDestroySemaphore vkDestroySemaphore;
    PFN_vkDestroyShaderEXT vkDestroyShaderEXT;
    PFN_vkDestroyShaderModule vkDestroyShaderModule;
    PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
    PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
    PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
    PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
    PFN_vkEndCommandBuffer vkEndCommandBuffer;
    PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
    PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
    PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
    PFN_vkFreeMemory vkFreeMemory;
    PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
    PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
    PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT;
    PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
    PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT;
    PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
    PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
    PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
    PFN_vkGetBufferMemoryRequirements2KHR vkGetBufferMemoryRequirements2KHR;
    PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
    PFN_vkGetBufferOpaqueCaptureAddressKHR vkGetBufferOpaqueCaptureAddressKHR;
    PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT vkGetBufferOpaqueCaptureDescriptorDataEXT;
    PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
    PFN_vkGetCalibratedTimestampsKHR vkGetCalibratedTimestampsKHR;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
    PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
    PFN_vkGetDescriptorEXT vkGetDescriptorEXT;
    PFN_vkGetDescriptorSetLayoutBindingOffsetEXT vkGetDescriptorSetLayoutBindingOffsetEXT;
    PFN_vkGetDescriptorSetLayoutSizeEXT vkGetDescriptorSetLayoutSizeEXT;
    PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
    PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
    PFN_vkGetDeviceBufferMemoryRequirements vkGetDeviceBufferMemoryRequirements;
    PFN_vkGetDeviceBufferMemoryRequirementsKHR vkGetDeviceBufferMemoryRequirementsKHR;
    PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT;
    PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
    PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
    PFN_vkGetDeviceImageMemoryRequirements vkGetDeviceImageMemoryRequirements;
    PFN_vkGetDeviceImageMemoryRequirementsKHR vkGetDeviceImageMemoryRequirementsKHR;
    PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements;
    PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR;
    PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR;
    PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR;
    PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT;
    PFN_vkGetDeviceQueue vkGetDeviceQueue;
    PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
    PFN_vkGetEventStatus vkGetEventStatus;
    PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
    PFN_vkGetFenceStatus vkGetFenceStatus;
    PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
    PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
    PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
    PFN_vkGetImageMemoryRequirements2KHR vkGetImageMemoryRequirements2KHR;
    PFN_vkGetImageOpaqueCaptureDescriptorDataEXT vkGetImageOpaqueCaptureDescriptorDataEXT;
    PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
    PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
    PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR;
    PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
    PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT;
    PFN_vkGetImageSubresourceLayout2KHR vkGetImageSubresourceLayout2KHR;
    PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT vkGetImageViewOpaqueCaptureDescriptorDataEXT;
    PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
    PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
    PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
    PFN_vkGetMicromapBuildSizesEXT vkGetMicromapBuildSizesEXT;
    PFN_vkGetPipelineBinaryDataKHR vkGetPipelineBinaryDataKHR;
    PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
    PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
    PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
    PFN_vkGetPipelineKeyKHR vkGetPipelineKeyKHR;
    PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT;
    PFN_vkGetPrivateData vkGetPrivateData;
    PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
    PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
    PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
    PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
    PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
    PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
    PFN_vkGetRenderingAreaGranularityKHR vkGetRenderingAreaGranularityKHR;
    PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT vkGetSamplerOpaqueCaptureDescriptorDataEXT;
    PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
    PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR;
    PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
    PFN_vkGetShaderBinaryDataEXT vkGetShaderBinaryDataEXT;
    PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT;
    PFN_vkGetShaderModuleIdentifierEXT vkGetShaderModuleIdentifierEXT;
    PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
    PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
    PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
    PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
    PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
    PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
    PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
    PFN_vkMapMemory vkMapMemory;
    PFN_vkMapMemory2KHR vkMapMemory2KHR;
    PFN_vkMergePipelineCaches vkMergePipelineCaches;
    PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
    PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
    PFN_vkQueueBindSparse vkQueueBindSparse;
    PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
    PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
    PFN_vkQueuePresentKHR vkQueuePresentKHR;
    PFN_vkQueueSubmit vkQueueSubmit;
    PFN_vkQueueSubmit2 vkQueueSubmit2;
    PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR;
    PFN_vkQueueWaitIdle vkQueueWaitIdle;
    PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
    PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
    PFN_vkReleaseCapturedPipelineDataKHR vkReleaseCapturedPipelineDataKHR;
    PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
    PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT;
    PFN_vkResetCommandBuffer vkResetCommandBuffer;
    PFN_vkResetCommandPool vkResetCommandPool;
    PFN_vkResetDescriptorPool vkResetDescriptorPool;
    PFN_vkResetEvent vkResetEvent;
    PFN_vkResetFences vkResetFences;
    PFN_vkResetQueryPool vkResetQueryPool;
    PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT;
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
    PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT;
    PFN_vkSetEvent vkSetEvent;
    PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
    PFN_vkSetPrivateData vkSetPrivateData;
    PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
    PFN_vkSignalSemaphore vkSignalSemaphore;
    PFN_vkSignalSemaphoreKHR vkSignalSemaphoreKHR;
    PFN_vkTransitionImageLayoutEXT vkTransitionImageLayoutEXT;
    PFN_vkTrimCommandPool vkTrimCommandPool;
    PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR;
    PFN_vkUnmapMemory vkUnmapMemory;
    PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR;
    PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
    PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR;
    PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
    PFN_vkWaitForFences vkWaitForFences;
    PFN_vkWaitForPresentKHR vkWaitForPresentKHR;
    PFN_vkWaitSemaphores vkWaitSemaphores;
    PFN_vkWaitSemaphoresKHR vkWaitSemaphoresKHR;
    PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
    PFN_vkWriteMicromapsPropertiesEXT vkWriteMicromapsPropertiesEXT;
};

#define ENTRY(fnc) table.fnc = (PFN_##fnc)getProcAddr(device, STR(fnc))

/**
 * @brief Initialize the device dispatch table with driver function pointers.
 *
 * @param device        The device handle.
 * @param getProcAddr   The function getter for the driver/next layer down.
 * @param table         The table to populate.
 */
static inline void initDriverDeviceDispatchTable(
    VkDevice device,
    PFN_vkGetDeviceProcAddr getProcAddr,
    DeviceDispatchTable& table
) {
    table.vkGetDeviceProcAddr = getProcAddr;

    ENTRY(vkAcquireNextImage2KHR);
    ENTRY(vkAcquireNextImageKHR);
    ENTRY(vkAcquireProfilingLockKHR);
    ENTRY(vkAllocateCommandBuffers);
    ENTRY(vkAllocateDescriptorSets);
    ENTRY(vkAllocateMemory);
    ENTRY(vkBeginCommandBuffer);
    ENTRY(vkBindBufferMemory);
    ENTRY(vkBindBufferMemory2);
    ENTRY(vkBindBufferMemory2KHR);
    ENTRY(vkBindImageMemory);
    ENTRY(vkBindImageMemory2);
    ENTRY(vkBindImageMemory2KHR);
    ENTRY(vkBuildAccelerationStructuresKHR);
    ENTRY(vkBuildMicromapsEXT);
    ENTRY(vkCmdBeginConditionalRenderingEXT);
    ENTRY(vkCmdBeginDebugUtilsLabelEXT);
    ENTRY(vkCmdBeginQuery);
    ENTRY(vkCmdBeginQueryIndexedEXT);
    ENTRY(vkCmdBeginRenderPass);
    ENTRY(vkCmdBeginRenderPass2);
    ENTRY(vkCmdBeginRenderPass2KHR);
    ENTRY(vkCmdBeginRendering);
    ENTRY(vkCmdBeginRenderingKHR);
    ENTRY(vkCmdBeginTransformFeedbackEXT);
    ENTRY(vkCmdBindDescriptorBufferEmbeddedSamplers2EXT);
    ENTRY(vkCmdBindDescriptorBufferEmbeddedSamplersEXT);
    ENTRY(vkCmdBindDescriptorBuffersEXT);
    ENTRY(vkCmdBindDescriptorSets);
    ENTRY(vkCmdBindDescriptorSets2KHR);
    ENTRY(vkCmdBindIndexBuffer);
    ENTRY(vkCmdBindIndexBuffer2KHR);
    ENTRY(vkCmdBindPipeline);
    ENTRY(vkCmdBindShadersEXT);
    ENTRY(vkCmdBindTransformFeedbackBuffersEXT);
    ENTRY(vkCmdBindVertexBuffers);
    ENTRY(vkCmdBindVertexBuffers2);
    ENTRY(vkCmdBindVertexBuffers2EXT);
    ENTRY(vkCmdBlitImage);
    ENTRY(vkCmdBlitImage2);
    ENTRY(vkCmdBlitImage2KHR);
    ENTRY(vkCmdBuildAccelerationStructuresIndirectKHR);
    ENTRY(vkCmdBuildAccelerationStructuresKHR);
    ENTRY(vkCmdBuildMicromapsEXT);
    ENTRY(vkCmdClearAttachments);
    ENTRY(vkCmdClearColorImage);
    ENTRY(vkCmdClearDepthStencilImage);
    ENTRY(vkCmdCopyAccelerationStructureKHR);
    ENTRY(vkCmdCopyAccelerationStructureToMemoryKHR);
    ENTRY(vkCmdCopyBuffer);
    ENTRY(vkCmdCopyBuffer2);
    ENTRY(vkCmdCopyBuffer2KHR);
    ENTRY(vkCmdCopyBufferToImage);
    ENTRY(vkCmdCopyBufferToImage2);
    ENTRY(vkCmdCopyBufferToImage2KHR);
    ENTRY(vkCmdCopyImage);
    ENTRY(vkCmdCopyImage2);
    ENTRY(vkCmdCopyImage2KHR);
    ENTRY(vkCmdCopyImageToBuffer);
    ENTRY(vkCmdCopyImageToBuffer2);
    ENTRY(vkCmdCopyImageToBuffer2KHR);
    ENTRY(vkCmdCopyMemoryToAccelerationStructureKHR);
    ENTRY(vkCmdCopyMemoryToMicromapEXT);
    ENTRY(vkCmdCopyMicromapEXT);
    ENTRY(vkCmdCopyMicromapToMemoryEXT);
    ENTRY(vkCmdCopyQueryPoolResults);
    ENTRY(vkCmdDebugMarkerBeginEXT);
    ENTRY(vkCmdDebugMarkerEndEXT);
    ENTRY(vkCmdDebugMarkerInsertEXT);
    ENTRY(vkCmdDispatch);
    ENTRY(vkCmdDispatchBase);
    ENTRY(vkCmdDispatchBaseKHR);
    ENTRY(vkCmdDispatchIndirect);
    ENTRY(vkCmdDraw);
    ENTRY(vkCmdDrawIndexed);
    ENTRY(vkCmdDrawIndexedIndirect);
    ENTRY(vkCmdDrawIndexedIndirectCount);
    ENTRY(vkCmdDrawIndexedIndirectCountKHR);
    ENTRY(vkCmdDrawIndirect);
    ENTRY(vkCmdDrawIndirectByteCountEXT);
    ENTRY(vkCmdDrawIndirectCount);
    ENTRY(vkCmdDrawIndirectCountKHR);
    ENTRY(vkCmdDrawMeshTasksEXT);
    ENTRY(vkCmdDrawMeshTasksIndirectCountEXT);
    ENTRY(vkCmdDrawMeshTasksIndirectEXT);
    ENTRY(vkCmdDrawMultiEXT);
    ENTRY(vkCmdDrawMultiIndexedEXT);
    ENTRY(vkCmdEndConditionalRenderingEXT);
    ENTRY(vkCmdEndDebugUtilsLabelEXT);
    ENTRY(vkCmdEndQuery);
    ENTRY(vkCmdEndQueryIndexedEXT);
    ENTRY(vkCmdEndRenderPass);
    ENTRY(vkCmdEndRenderPass2);
    ENTRY(vkCmdEndRenderPass2KHR);
    ENTRY(vkCmdEndRendering);
    ENTRY(vkCmdEndRenderingKHR);
    ENTRY(vkCmdEndTransformFeedbackEXT);
    ENTRY(vkCmdExecuteCommands);
    ENTRY(vkCmdFillBuffer);
    ENTRY(vkCmdInsertDebugUtilsLabelEXT);
    ENTRY(vkCmdNextSubpass);
    ENTRY(vkCmdNextSubpass2);
    ENTRY(vkCmdNextSubpass2KHR);
    ENTRY(vkCmdPipelineBarrier);
    ENTRY(vkCmdPipelineBarrier2);
    ENTRY(vkCmdPipelineBarrier2KHR);
    ENTRY(vkCmdPushConstants);
    ENTRY(vkCmdPushConstants2KHR);
    ENTRY(vkCmdPushDescriptorSet2KHR);
    ENTRY(vkCmdPushDescriptorSetKHR);
    ENTRY(vkCmdPushDescriptorSetWithTemplate2KHR);
    ENTRY(vkCmdPushDescriptorSetWithTemplateKHR);
    ENTRY(vkCmdResetEvent);
    ENTRY(vkCmdResetEvent2);
    ENTRY(vkCmdResetEvent2KHR);
    ENTRY(vkCmdResetQueryPool);
    ENTRY(vkCmdResolveImage);
    ENTRY(vkCmdResolveImage2);
    ENTRY(vkCmdResolveImage2KHR);
    ENTRY(vkCmdSetAlphaToCoverageEnableEXT);
    ENTRY(vkCmdSetAlphaToOneEnableEXT);
    ENTRY(vkCmdSetAttachmentFeedbackLoopEnableEXT);
    ENTRY(vkCmdSetBlendConstants);
    ENTRY(vkCmdSetColorBlendAdvancedEXT);
    ENTRY(vkCmdSetColorBlendEnableEXT);
    ENTRY(vkCmdSetColorBlendEquationEXT);
    ENTRY(vkCmdSetColorWriteEnableEXT);
    ENTRY(vkCmdSetColorWriteMaskEXT);
    ENTRY(vkCmdSetConservativeRasterizationModeEXT);
    ENTRY(vkCmdSetCoverageModulationModeNV);
    ENTRY(vkCmdSetCoverageModulationTableEnableNV);
    ENTRY(vkCmdSetCoverageModulationTableNV);
    ENTRY(vkCmdSetCoverageReductionModeNV);
    ENTRY(vkCmdSetCoverageToColorEnableNV);
    ENTRY(vkCmdSetCoverageToColorLocationNV);
    ENTRY(vkCmdSetCullMode);
    ENTRY(vkCmdSetCullModeEXT);
    ENTRY(vkCmdSetDepthBias);
    ENTRY(vkCmdSetDepthBias2EXT);
    ENTRY(vkCmdSetDepthBiasEnable);
    ENTRY(vkCmdSetDepthBiasEnableEXT);
    ENTRY(vkCmdSetDepthBounds);
    ENTRY(vkCmdSetDepthBoundsTestEnable);
    ENTRY(vkCmdSetDepthBoundsTestEnableEXT);
    ENTRY(vkCmdSetDepthClampEnableEXT);
    ENTRY(vkCmdSetDepthClipEnableEXT);
    ENTRY(vkCmdSetDepthClipNegativeOneToOneEXT);
    ENTRY(vkCmdSetDepthCompareOp);
    ENTRY(vkCmdSetDepthCompareOpEXT);
    ENTRY(vkCmdSetDepthTestEnable);
    ENTRY(vkCmdSetDepthTestEnableEXT);
    ENTRY(vkCmdSetDepthWriteEnable);
    ENTRY(vkCmdSetDepthWriteEnableEXT);
    ENTRY(vkCmdSetDescriptorBufferOffsets2EXT);
    ENTRY(vkCmdSetDescriptorBufferOffsetsEXT);
    ENTRY(vkCmdSetDeviceMask);
    ENTRY(vkCmdSetDeviceMaskKHR);
    ENTRY(vkCmdSetDiscardRectangleEXT);
    ENTRY(vkCmdSetDiscardRectangleEnableEXT);
    ENTRY(vkCmdSetDiscardRectangleModeEXT);
    ENTRY(vkCmdSetEvent);
    ENTRY(vkCmdSetEvent2);
    ENTRY(vkCmdSetEvent2KHR);
    ENTRY(vkCmdSetExtraPrimitiveOverestimationSizeEXT);
    ENTRY(vkCmdSetFragmentShadingRateKHR);
    ENTRY(vkCmdSetFrontFace);
    ENTRY(vkCmdSetFrontFaceEXT);
    ENTRY(vkCmdSetLineRasterizationModeEXT);
    ENTRY(vkCmdSetLineStippleEXT);
    ENTRY(vkCmdSetLineStippleEnableEXT);
    ENTRY(vkCmdSetLineStippleKHR);
    ENTRY(vkCmdSetLineWidth);
    ENTRY(vkCmdSetLogicOpEXT);
    ENTRY(vkCmdSetLogicOpEnableEXT);
    ENTRY(vkCmdSetPatchControlPointsEXT);
    ENTRY(vkCmdSetPolygonModeEXT);
    ENTRY(vkCmdSetPrimitiveRestartEnable);
    ENTRY(vkCmdSetPrimitiveRestartEnableEXT);
    ENTRY(vkCmdSetPrimitiveTopology);
    ENTRY(vkCmdSetPrimitiveTopologyEXT);
    ENTRY(vkCmdSetProvokingVertexModeEXT);
    ENTRY(vkCmdSetRasterizationSamplesEXT);
    ENTRY(vkCmdSetRasterizationStreamEXT);
    ENTRY(vkCmdSetRasterizerDiscardEnable);
    ENTRY(vkCmdSetRasterizerDiscardEnableEXT);
    ENTRY(vkCmdSetRayTracingPipelineStackSizeKHR);
    ENTRY(vkCmdSetRenderingAttachmentLocationsKHR);
    ENTRY(vkCmdSetRenderingInputAttachmentIndicesKHR);
    ENTRY(vkCmdSetRepresentativeFragmentTestEnableNV);
    ENTRY(vkCmdSetSampleLocationsEXT);
    ENTRY(vkCmdSetSampleLocationsEnableEXT);
    ENTRY(vkCmdSetSampleMaskEXT);
    ENTRY(vkCmdSetScissor);
    ENTRY(vkCmdSetScissorWithCount);
    ENTRY(vkCmdSetScissorWithCountEXT);
    ENTRY(vkCmdSetShadingRateImageEnableNV);
    ENTRY(vkCmdSetStencilCompareMask);
    ENTRY(vkCmdSetStencilOp);
    ENTRY(vkCmdSetStencilOpEXT);
    ENTRY(vkCmdSetStencilReference);
    ENTRY(vkCmdSetStencilTestEnable);
    ENTRY(vkCmdSetStencilTestEnableEXT);
    ENTRY(vkCmdSetStencilWriteMask);
    ENTRY(vkCmdSetTessellationDomainOriginEXT);
    ENTRY(vkCmdSetVertexInputEXT);
    ENTRY(vkCmdSetViewport);
    ENTRY(vkCmdSetViewportSwizzleNV);
    ENTRY(vkCmdSetViewportWScalingEnableNV);
    ENTRY(vkCmdSetViewportWithCount);
    ENTRY(vkCmdSetViewportWithCountEXT);
    ENTRY(vkCmdTraceRaysIndirect2KHR);
    ENTRY(vkCmdTraceRaysIndirectKHR);
    ENTRY(vkCmdTraceRaysKHR);
    ENTRY(vkCmdUpdateBuffer);
    ENTRY(vkCmdWaitEvents);
    ENTRY(vkCmdWaitEvents2);
    ENTRY(vkCmdWaitEvents2KHR);
    ENTRY(vkCmdWriteAccelerationStructuresPropertiesKHR);
    ENTRY(vkCmdWriteBufferMarker2AMD);
    ENTRY(vkCmdWriteMicromapsPropertiesEXT);
    ENTRY(vkCmdWriteTimestamp);
    ENTRY(vkCmdWriteTimestamp2);
    ENTRY(vkCmdWriteTimestamp2KHR);
    ENTRY(vkCopyAccelerationStructureKHR);
    ENTRY(vkCopyAccelerationStructureToMemoryKHR);
    ENTRY(vkCopyImageToImageEXT);
    ENTRY(vkCopyImageToMemoryEXT);
    ENTRY(vkCopyMemoryToAccelerationStructureKHR);
    ENTRY(vkCopyMemoryToImageEXT);
    ENTRY(vkCopyMemoryToMicromapEXT);
    ENTRY(vkCopyMicromapEXT);
    ENTRY(vkCopyMicromapToMemoryEXT);
    ENTRY(vkCreateAccelerationStructureKHR);
    ENTRY(vkCreateBuffer);
    ENTRY(vkCreateBufferView);
    ENTRY(vkCreateCommandPool);
    ENTRY(vkCreateComputePipelines);
    ENTRY(vkCreateDeferredOperationKHR);
    ENTRY(vkCreateDescriptorPool);
    ENTRY(vkCreateDescriptorSetLayout);
    ENTRY(vkCreateDescriptorUpdateTemplate);
    ENTRY(vkCreateDescriptorUpdateTemplateKHR);
    ENTRY(vkCreateEvent);
    ENTRY(vkCreateFence);
    ENTRY(vkCreateFramebuffer);
    ENTRY(vkCreateGraphicsPipelines);
    ENTRY(vkCreateImage);
    ENTRY(vkCreateImageView);
    ENTRY(vkCreateMicromapEXT);
    ENTRY(vkCreatePipelineBinariesKHR);
    ENTRY(vkCreatePipelineCache);
    ENTRY(vkCreatePipelineLayout);
    ENTRY(vkCreatePrivateDataSlot);
    ENTRY(vkCreatePrivateDataSlotEXT);
    ENTRY(vkCreateQueryPool);
    ENTRY(vkCreateRayTracingPipelinesKHR);
    ENTRY(vkCreateRenderPass);
    ENTRY(vkCreateRenderPass2);
    ENTRY(vkCreateRenderPass2KHR);
    ENTRY(vkCreateSampler);
    ENTRY(vkCreateSamplerYcbcrConversion);
    ENTRY(vkCreateSamplerYcbcrConversionKHR);
    ENTRY(vkCreateSemaphore);
    ENTRY(vkCreateShaderModule);
    ENTRY(vkCreateShadersEXT);
    ENTRY(vkCreateSharedSwapchainsKHR);
    ENTRY(vkCreateSwapchainKHR);
    ENTRY(vkCreateValidationCacheEXT);
    ENTRY(vkDebugMarkerSetObjectNameEXT);
    ENTRY(vkDebugMarkerSetObjectTagEXT);
    ENTRY(vkDeferredOperationJoinKHR);
    ENTRY(vkDestroyAccelerationStructureKHR);
    ENTRY(vkDestroyBuffer);
    ENTRY(vkDestroyBufferView);
    ENTRY(vkDestroyCommandPool);
    ENTRY(vkDestroyDeferredOperationKHR);
    ENTRY(vkDestroyDescriptorPool);
    ENTRY(vkDestroyDescriptorSetLayout);
    ENTRY(vkDestroyDescriptorUpdateTemplate);
    ENTRY(vkDestroyDescriptorUpdateTemplateKHR);
    ENTRY(vkDestroyDevice);
    ENTRY(vkDestroyEvent);
    ENTRY(vkDestroyFence);
    ENTRY(vkDestroyFramebuffer);
    ENTRY(vkDestroyImage);
    ENTRY(vkDestroyImageView);
    ENTRY(vkDestroyMicromapEXT);
    ENTRY(vkDestroyPipeline);
    ENTRY(vkDestroyPipelineBinaryKHR);
    ENTRY(vkDestroyPipelineCache);
    ENTRY(vkDestroyPipelineLayout);
    ENTRY(vkDestroyPrivateDataSlot);
    ENTRY(vkDestroyPrivateDataSlotEXT);
    ENTRY(vkDestroyQueryPool);
    ENTRY(vkDestroyRenderPass);
    ENTRY(vkDestroySampler);
    ENTRY(vkDestroySamplerYcbcrConversion);
    ENTRY(vkDestroySamplerYcbcrConversionKHR);
    ENTRY(vkDestroySemaphore);
    ENTRY(vkDestroyShaderEXT);
    ENTRY(vkDestroyShaderModule);
    ENTRY(vkDestroySwapchainKHR);
    ENTRY(vkDestroyValidationCacheEXT);
    ENTRY(vkDeviceWaitIdle);
    ENTRY(vkDisplayPowerControlEXT);
    ENTRY(vkEndCommandBuffer);
    ENTRY(vkFlushMappedMemoryRanges);
    ENTRY(vkFreeCommandBuffers);
    ENTRY(vkFreeDescriptorSets);
    ENTRY(vkFreeMemory);
    ENTRY(vkGetAccelerationStructureBuildSizesKHR);
    ENTRY(vkGetAccelerationStructureDeviceAddressKHR);
    ENTRY(vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT);
    ENTRY(vkGetBufferDeviceAddress);
    ENTRY(vkGetBufferDeviceAddressEXT);
    ENTRY(vkGetBufferDeviceAddressKHR);
    ENTRY(vkGetBufferMemoryRequirements);
    ENTRY(vkGetBufferMemoryRequirements2);
    ENTRY(vkGetBufferMemoryRequirements2KHR);
    ENTRY(vkGetBufferOpaqueCaptureAddress);
    ENTRY(vkGetBufferOpaqueCaptureAddressKHR);
    ENTRY(vkGetBufferOpaqueCaptureDescriptorDataEXT);
    ENTRY(vkGetCalibratedTimestampsEXT);
    ENTRY(vkGetCalibratedTimestampsKHR);
    ENTRY(vkGetDeferredOperationMaxConcurrencyKHR);
    ENTRY(vkGetDeferredOperationResultKHR);
    ENTRY(vkGetDescriptorEXT);
    ENTRY(vkGetDescriptorSetLayoutBindingOffsetEXT);
    ENTRY(vkGetDescriptorSetLayoutSizeEXT);
    ENTRY(vkGetDescriptorSetLayoutSupport);
    ENTRY(vkGetDescriptorSetLayoutSupportKHR);
    ENTRY(vkGetDeviceAccelerationStructureCompatibilityKHR);
    ENTRY(vkGetDeviceBufferMemoryRequirements);
    ENTRY(vkGetDeviceBufferMemoryRequirementsKHR);
    ENTRY(vkGetDeviceFaultInfoEXT);
    ENTRY(vkGetDeviceGroupPeerMemoryFeatures);
    ENTRY(vkGetDeviceGroupPeerMemoryFeaturesKHR);
    ENTRY(vkGetDeviceGroupPresentCapabilitiesKHR);
    ENTRY(vkGetDeviceGroupSurfacePresentModesKHR);
    ENTRY(vkGetDeviceImageMemoryRequirements);
    ENTRY(vkGetDeviceImageMemoryRequirementsKHR);
    ENTRY(vkGetDeviceImageSparseMemoryRequirements);
    ENTRY(vkGetDeviceImageSparseMemoryRequirementsKHR);
    ENTRY(vkGetDeviceImageSubresourceLayoutKHR);
    ENTRY(vkGetDeviceMemoryCommitment);
    ENTRY(vkGetDeviceMemoryOpaqueCaptureAddress);
    ENTRY(vkGetDeviceMemoryOpaqueCaptureAddressKHR);
    ENTRY(vkGetDeviceMicromapCompatibilityEXT);
    ENTRY(vkGetDeviceQueue);
    ENTRY(vkGetDeviceQueue2);
    ENTRY(vkGetEventStatus);
    ENTRY(vkGetFenceFdKHR);
    ENTRY(vkGetFenceStatus);
    ENTRY(vkGetImageDrmFormatModifierPropertiesEXT);
    ENTRY(vkGetImageMemoryRequirements);
    ENTRY(vkGetImageMemoryRequirements2);
    ENTRY(vkGetImageMemoryRequirements2KHR);
    ENTRY(vkGetImageOpaqueCaptureDescriptorDataEXT);
    ENTRY(vkGetImageSparseMemoryRequirements);
    ENTRY(vkGetImageSparseMemoryRequirements2);
    ENTRY(vkGetImageSparseMemoryRequirements2KHR);
    ENTRY(vkGetImageSubresourceLayout);
    ENTRY(vkGetImageSubresourceLayout2EXT);
    ENTRY(vkGetImageSubresourceLayout2KHR);
    ENTRY(vkGetImageViewOpaqueCaptureDescriptorDataEXT);
    ENTRY(vkGetMemoryFdKHR);
    ENTRY(vkGetMemoryFdPropertiesKHR);
    ENTRY(vkGetMemoryHostPointerPropertiesEXT);
    ENTRY(vkGetMicromapBuildSizesEXT);
    ENTRY(vkGetPipelineBinaryDataKHR);
    ENTRY(vkGetPipelineCacheData);
    ENTRY(vkGetPipelineExecutableInternalRepresentationsKHR);
    ENTRY(vkGetPipelineExecutablePropertiesKHR);
    ENTRY(vkGetPipelineExecutableStatisticsKHR);
    ENTRY(vkGetPipelineKeyKHR);
    ENTRY(vkGetPipelinePropertiesEXT);
    ENTRY(vkGetPrivateData);
    ENTRY(vkGetPrivateDataEXT);
    ENTRY(vkGetQueryPoolResults);
    ENTRY(vkGetQueueCheckpointData2NV);
    ENTRY(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR);
    ENTRY(vkGetRayTracingShaderGroupHandlesKHR);
    ENTRY(vkGetRayTracingShaderGroupStackSizeKHR);
    ENTRY(vkGetRenderAreaGranularity);
    ENTRY(vkGetRenderingAreaGranularityKHR);
    ENTRY(vkGetSamplerOpaqueCaptureDescriptorDataEXT);
    ENTRY(vkGetSemaphoreCounterValue);
    ENTRY(vkGetSemaphoreCounterValueKHR);
    ENTRY(vkGetSemaphoreFdKHR);
    ENTRY(vkGetShaderBinaryDataEXT);
    ENTRY(vkGetShaderModuleCreateInfoIdentifierEXT);
    ENTRY(vkGetShaderModuleIdentifierEXT);
    ENTRY(vkGetSwapchainCounterEXT);
    ENTRY(vkGetSwapchainImagesKHR);
    ENTRY(vkGetSwapchainStatusKHR);
    ENTRY(vkGetValidationCacheDataEXT);
    ENTRY(vkImportFenceFdKHR);
    ENTRY(vkImportSemaphoreFdKHR);
    ENTRY(vkInvalidateMappedMemoryRanges);
    ENTRY(vkMapMemory);
    ENTRY(vkMapMemory2KHR);
    ENTRY(vkMergePipelineCaches);
    ENTRY(vkMergeValidationCachesEXT);
    ENTRY(vkQueueBeginDebugUtilsLabelEXT);
    ENTRY(vkQueueBindSparse);
    ENTRY(vkQueueEndDebugUtilsLabelEXT);
    ENTRY(vkQueueInsertDebugUtilsLabelEXT);
    ENTRY(vkQueuePresentKHR);
    ENTRY(vkQueueSubmit);
    ENTRY(vkQueueSubmit2);
    ENTRY(vkQueueSubmit2KHR);
    ENTRY(vkQueueWaitIdle);
    ENTRY(vkRegisterDeviceEventEXT);
    ENTRY(vkRegisterDisplayEventEXT);
    ENTRY(vkReleaseCapturedPipelineDataKHR);
    ENTRY(vkReleaseProfilingLockKHR);
    ENTRY(vkReleaseSwapchainImagesEXT);
    ENTRY(vkResetCommandBuffer);
    ENTRY(vkResetCommandPool);
    ENTRY(vkResetDescriptorPool);
    ENTRY(vkResetEvent);
    ENTRY(vkResetFences);
    ENTRY(vkResetQueryPool);
    ENTRY(vkResetQueryPoolEXT);
    ENTRY(vkSetDebugUtilsObjectNameEXT);
    ENTRY(vkSetDebugUtilsObjectTagEXT);
    ENTRY(vkSetDeviceMemoryPriorityEXT);
    ENTRY(vkSetEvent);
    ENTRY(vkSetHdrMetadataEXT);
    ENTRY(vkSetPrivateData);
    ENTRY(vkSetPrivateDataEXT);
    ENTRY(vkSignalSemaphore);
    ENTRY(vkSignalSemaphoreKHR);
    ENTRY(vkTransitionImageLayoutEXT);
    ENTRY(vkTrimCommandPool);
    ENTRY(vkTrimCommandPoolKHR);
    ENTRY(vkUnmapMemory);
    ENTRY(vkUnmapMemory2KHR);
    ENTRY(vkUpdateDescriptorSetWithTemplate);
    ENTRY(vkUpdateDescriptorSetWithTemplateKHR);
    ENTRY(vkUpdateDescriptorSets);
    ENTRY(vkWaitForFences);
    ENTRY(vkWaitForPresentKHR);
    ENTRY(vkWaitSemaphores);
    ENTRY(vkWaitSemaphoresKHR);
    ENTRY(vkWriteAccelerationStructuresPropertiesKHR);
    ENTRY(vkWriteMicromapsPropertiesEXT);
}

#undef ENTRY
