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
#include "framework/instance_functions.hpp"
#include "framework/utils.hpp"
#include "utils/misc.hpp"

#if __has_include ("layer_instance_functions.hpp")
    #include "layer_instance_functions.hpp"
#endif

/**
 * @brief Interception table lookup entry.
 */
struct InstanceInterceptTableEntry
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
 * @brief The instance dispatch table used to call the driver.
 */
static const struct InstanceInterceptTableEntry instanceIntercepts[] = {

// Device functions
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

/**
 * @brief The instance dispatch table used to call the driver.
 */
struct InstanceDispatchTable {
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif
    PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
    PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
    PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
    PFN_vkDestroyInstance vkDestroyInstance;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
    PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
    PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
    PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
    PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
    PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
    PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR;
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
    PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
    PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
    PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
    PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
    PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
    PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
    PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
    PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
    PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
};

#define ENTRY(fnc) table.fnc = (PFN_##fnc)getProcAddr(instance, STR(fnc))

/**
 * @brief Initialize the instance dispatch table with driver function pointers.
 *
 * @param instance      The instance handle.
 * @param getProcAddr   The function getter for the driver/next layer down.
 * @param table         The table to populate.
 */
static inline void initDriverInstanceDispatchTable(
    VkInstance instance,
    PFN_vkGetInstanceProcAddr getProcAddr,
    InstanceDispatchTable& table
) {
    table.vkGetInstanceProcAddr = getProcAddr;

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    ENTRY(vkCreateAndroidSurfaceKHR);
#endif
    ENTRY(vkCreateDebugReportCallbackEXT);
    ENTRY(vkCreateDebugUtilsMessengerEXT);
    ENTRY(vkCreateDisplayModeKHR);
    ENTRY(vkCreateDisplayPlaneSurfaceKHR);
    ENTRY(vkDebugReportMessageEXT);
    ENTRY(vkDestroyDebugReportCallbackEXT);
    ENTRY(vkDestroyDebugUtilsMessengerEXT);
    ENTRY(vkDestroyInstance);
    ENTRY(vkDestroySurfaceKHR);
    ENTRY(vkEnumerateDeviceExtensionProperties);
    ENTRY(vkEnumeratePhysicalDeviceGroups);
    ENTRY(vkEnumeratePhysicalDeviceGroupsKHR);
    ENTRY(vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    ENTRY(vkEnumeratePhysicalDevices);
    ENTRY(vkGetDisplayModeProperties2KHR);
    ENTRY(vkGetDisplayModePropertiesKHR);
    ENTRY(vkGetDisplayPlaneCapabilities2KHR);
    ENTRY(vkGetDisplayPlaneCapabilitiesKHR);
    ENTRY(vkGetDisplayPlaneSupportedDisplaysKHR);
    ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT);
    ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsKHR);
    ENTRY(vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceDisplayPlaneProperties2KHR);
    ENTRY(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceDisplayProperties2KHR);
    ENTRY(vkGetPhysicalDeviceDisplayPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalBufferProperties);
    ENTRY(vkGetPhysicalDeviceExternalBufferPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalFenceProperties);
    ENTRY(vkGetPhysicalDeviceExternalFencePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalSemaphoreProperties);
    ENTRY(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceFeatures);
    ENTRY(vkGetPhysicalDeviceFeatures2);
    ENTRY(vkGetPhysicalDeviceFeatures2KHR);
    ENTRY(vkGetPhysicalDeviceFormatProperties);
    ENTRY(vkGetPhysicalDeviceFormatProperties2);
    ENTRY(vkGetPhysicalDeviceFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceFragmentShadingRatesKHR);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties2);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceMemoryProperties);
    ENTRY(vkGetPhysicalDeviceMemoryProperties2);
    ENTRY(vkGetPhysicalDeviceMemoryProperties2KHR);
    ENTRY(vkGetPhysicalDeviceMultisamplePropertiesEXT);
    ENTRY(vkGetPhysicalDevicePresentRectanglesKHR);
    ENTRY(vkGetPhysicalDeviceProperties);
    ENTRY(vkGetPhysicalDeviceProperties2);
    ENTRY(vkGetPhysicalDeviceProperties2KHR);
    ENTRY(vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2KHR);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2EXT);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
    ENTRY(vkGetPhysicalDeviceSurfaceFormats2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceFormatsKHR);
    ENTRY(vkGetPhysicalDeviceSurfacePresentModesKHR);
    ENTRY(vkGetPhysicalDeviceSurfaceSupportKHR);
    ENTRY(vkGetPhysicalDeviceToolProperties);
    ENTRY(vkGetPhysicalDeviceToolPropertiesEXT);
    ENTRY(vkReleaseDisplayEXT);
    ENTRY(vkSubmitDebugUtilsMessageEXT);
}

#undef ENTRY
