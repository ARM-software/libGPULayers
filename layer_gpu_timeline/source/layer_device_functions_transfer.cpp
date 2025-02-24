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

#include "device.hpp"
#include "device_utils.hpp"
#include "framework/device_dispatch_table.hpp"
#include "trackers/layer_command_stream.hpp"

#include <memory>
#include <mutex>
#include <thread>

extern std::mutex g_vulkanLock;

/**
 * @brief Register a transfer to a buffer with the tracker.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param transferType    The type of transfer being performed.
 * @param byteCount       The number of bytes transferred.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerBufferTransfer(Device* layer,
                                       VkCommandBuffer commandBuffer,
                                       Tracker::LCSBufferTransfer::Type transferType,
                                       int64_t byteCount)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.bufferTransfer(transferType, byteCount);
}

/**
 * @brief Register a transfer to an image with the tracker.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param transferType    The type of transfer being performed.
 * @param pixelCount      The number of pixels transferred.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerImageTransfer(Device* layer,
                                      VkCommandBuffer commandBuffer,
                                      Tracker::LCSImageTransfer::Type transferType,
                                      int64_t pixelCount)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.imageTransfer(transferType, pixelCount);
}

/**
 * @brief Register a transfer to an image with the tracker.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param transferType    The type of transfer being performed.
 * @param byteCount       The number of bytes transferred.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerAccelerationStructureTransfer(Device* layer,
                                                      VkCommandBuffer commandBuffer,
                                                      Tracker::LCSAccelerationStructureTransfer::Type transferType,
                                                      int64_t byteCount)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.accelerationStructureTransfer(transferType, byteCount);
}

// Commands for transfers

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                           VkBuffer dstBuffer,
                                                           VkDeviceSize dstOffset,
                                                           VkDeviceSize size,
                                                           uint32_t data)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    // TODO: Add buffer tracking so we can turn VK_WHOLE_SIZE into bytes
    int64_t byteCount = static_cast<int64_t>(size);
    if (size == VK_WHOLE_SIZE)
    {
        byteCount = -2;
    }

    uint64_t tagID =
        registerBufferTransfer(layer, commandBuffer, Tracker::LCSBufferTransfer::Type::fill_buffer, byteCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                VkImage image,
                                                                VkImageLayout imageLayout,
                                                                const VkClearColorValue* pColor,
                                                                uint32_t rangeCount,
                                                                const VkImageSubresourceRange* pRanges)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    // TODO: Add image tracking so we can turn image and pRanges into pixels
    int64_t pixelCount = -1;

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::clear_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                       VkImage image,
                                                                       VkImageLayout imageLayout,
                                                                       const VkClearDepthStencilValue* pDepthStencil,
                                                                       uint32_t rangeCount,
                                                                       const VkImageSubresourceRange* pRanges)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    // TODO: Add image tracking so we can turn image and pRanges into pixels
    int64_t pixelCount = -1;

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::clear_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                           VkBuffer srcBuffer,
                                                           VkBuffer dstBuffer,
                                                           uint32_t regionCount,
                                                           const VkBufferCopy* pRegions)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t byteCount = 0;
    for (uint32_t i = 0; i < regionCount; i++)
    {
        byteCount += static_cast<int64_t>(pRegions[i].size);
    }

    uint64_t tagID =
        registerBufferTransfer(layer, commandBuffer, Tracker::LCSBufferTransfer::Type::copy_buffer, byteCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2<user_tag>(VkCommandBuffer commandBuffer,
                                                            const VkCopyBufferInfo2* pCopyBufferInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t byteCount = 0;
    for (uint32_t i = 0; i < pCopyBufferInfo->regionCount; i++)
    {
        byteCount += static_cast<int64_t>(pCopyBufferInfo->pRegions[i].size);
    }

    uint64_t tagID =
        registerBufferTransfer(layer, commandBuffer, Tracker::LCSBufferTransfer::Type::copy_buffer, byteCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                               const VkCopyBufferInfo2* pCopyBufferInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t byteCount = 0;
    for (uint32_t i = 0; i < pCopyBufferInfo->regionCount; i++)
    {
        byteCount += static_cast<int64_t>(pCopyBufferInfo->pRegions[i].size);
    }

    uint64_t tagID =
        registerBufferTransfer(layer, commandBuffer, Tracker::LCSBufferTransfer::Type::copy_buffer, byteCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage<user_tag>(VkCommandBuffer commandBuffer,
                                                                  VkBuffer srcBuffer,
                                                                  VkImage dstImage,
                                                                  VkImageLayout dstImageLayout,
                                                                  uint32_t regionCount,
                                                                  const VkBufferImageCopy* pRegions)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_buffer_to_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyBufferToImage2<user_tag>(VkCommandBuffer commandBuffer,
                                            const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyBufferToImageInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_buffer_to_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyBufferToImage2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                               const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyBufferToImageInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pCopyBufferToImageInfo->pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_buffer_to_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage<user_tag>(VkCommandBuffer commandBuffer,
                                                          VkImage srcImage,
                                                          VkImageLayout srcImageLayout,
                                                          VkImage dstImage,
                                                          VkImageLayout dstImageLayout,
                                                          uint32_t regionCount,
                                                          const VkImageCopy* pRegions)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pRegions[i].extent.width)
                            * static_cast<int64_t>(pRegions[i].extent.height)
                            * static_cast<int64_t>(pRegions[i].extent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver
        .vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2<user_tag>(VkCommandBuffer commandBuffer,
                                                           const VkCopyImageInfo2* pCopyImageInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyImageInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.width)
                            * static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.height)
                            * static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyImageInfo2* pCopyImageInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyImageInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.width)
                            * static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.height)
                            * static_cast<int64_t>(pCopyImageInfo->pRegions[i].extent.depth);
        pixelCount += rPixelCount;
    }

    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer<user_tag>(VkCommandBuffer commandBuffer,
                                                                  VkImage srcImage,
                                                                  VkImageLayout srcImageLayout,
                                                                  VkBuffer dstBuffer,
                                                                  uint32_t regionCount,
                                                                  const VkBufferImageCopy* pRegions)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    // TODO: Our usual convention is to mark the transfer using the destination
    // type, which means this should be a bufferTransfer reporting size in
    // bytes. Without image tracking we only have pixels, so for now we report
    // as "Copy image" and report size in pixels.
    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image_to_buffer, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyImageToBuffer2<user_tag>(VkCommandBuffer commandBuffer,
                                            const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyImageToBufferInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    // TODO: Our usual convention is to mark the transfer using the destination
    // type, which means this should be a bufferTransfer reporting size in
    // bytes. Without image tracking we only have pixels, so for now we report
    // as "Copy image" and report size in pixels.
    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image_to_buffer, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyImageToBuffer2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                               const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Compute the size of the transfer
    int64_t pixelCount = 0;
    for (uint32_t i = 0; i < pCopyImageToBufferInfo->regionCount; i++)
    {
        int64_t rPixelCount = static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.width)
                            * static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.height)
                            * static_cast<int64_t>(pCopyImageToBufferInfo->pRegions[i].imageExtent.depth);
        pixelCount += rPixelCount;
    }

    // TODO: Our usual convention is to mark the transfer using the destination
    // type, which means this should be a bufferTransfer reporting size in
    // bytes. Without image tracking we only have pixels, so for now we report
    // as "Copy image" and report size in pixels.
    uint64_t tagID =
        registerImageTransfer(layer, commandBuffer, Tracker::LCSImageTransfer::Type::copy_image_to_buffer, pixelCount);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyAccelerationStructureKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                      const VkCopyAccelerationStructureInfoKHR* pInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // TODO: We ideally want to track sizes of the transfers, but this requires
    // dispatching vkCmdWriteAccelerationStructuresPropertiesKHR() queries and
    // capturing the result "later" which we don't support yet.
    // We can approximate the size using vkGetAccelerationStructureBuildSizesKHR(),
    // but this returns the build size which may be larger than the size of the
    // AS itself which can be smaller (especially if later compacted).
    uint64_t tagID =
        registerAccelerationStructureTransfer(layer,
                                              commandBuffer,
                                              Tracker::LCSAccelerationStructureTransfer::Type::struct_to_struct,
                                              -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyAccelerationStructureToMemoryKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // TODO: We ideally want to track sizes of the transfers, but this requires
    // dispatching vkCmdWriteAccelerationStructuresPropertiesKHR() queries and
    // capturing the result "later" which we don't support yet.
    // We can approximate the size using vkGetAccelerationStructureBuildSizesKHR(),
    // but this returns the build size which may be larger than the size of the
    // AS itself which can be smaller (especially if later compacted).
    uint64_t tagID =
        registerAccelerationStructureTransfer(layer,
                                              commandBuffer,
                                              Tracker::LCSAccelerationStructureTransfer::Type::struct_to_mem,
                                              -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdCopyMemoryToAccelerationStructureKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                              const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // TODO: We ideally want to track sizes of the transfers, but this requires
    // dispatching vkCmdWriteAccelerationStructuresPropertiesKHR() queries and
    // capturing the result "later" which we don't support yet.
    // We can approximate the size using vkGetAccelerationStructureBuildSizesKHR(),
    // but this returns the build size which may be larger than the size of the
    // AS itself which can be smaller (especially if later compacted).
    uint64_t tagID =
        registerAccelerationStructureTransfer(layer,
                                              commandBuffer,
                                              Tracker::LCSAccelerationStructureTransfer::Type::mem_to_struct,
                                              -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}
