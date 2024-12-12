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

#include <memory>
#include <mutex>
#include <thread>

#include "device.hpp"
#include "layer_device_functions.hpp"

extern std::mutex g_vulkanLock;

static uint64_t registerBufferTransfer(
    Device* layer,
    VkCommandBuffer commandBuffer,
    const std::string& transferType,
    int64_t byteCount
) {
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.bufferTransfer(transferType, byteCount);
}

static uint64_t registerImageTransfer(
    Device* layer,
    VkCommandBuffer commandBuffer,
    const std::string& transferType,
    int64_t pixelCount
) {
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.imageTransfer(transferType, pixelCount);
}

static void emitStartTag(
    Device* layer,
    VkCommandBuffer commandBuffer,
    uint64_t tagID
) {
    // Emit the unique workload tag into the command stream
    std::string tagLabel = formatString("t%" PRIu64, tagID);
    VkDebugUtilsLabelEXT tagInfo {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pNext = nullptr,
        .pLabelName = tagLabel.c_str(),
        .color = { 0.0f, 0.0f, 0.0f, 0.0f }
    };

    layer->driver.vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &tagInfo);
}

// Commands for transfers

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdFillBuffer<user_tag>(
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

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Fill buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearColorImage<user_tag>(
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

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Clear image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdClearDepthStencilImage<user_tag>(
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

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Clear image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer<user_tag>(
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

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBuffer2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferInfo2* pCopyBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage<user_tag>(
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

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyBufferToImage2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage<user_tag>(
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

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImage2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageInfo2* pCopyImageInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerImageTransfer(
        layer,
        commandBuffer,
        "Copy image",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer<user_tag>(
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

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdCopyImageToBuffer2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerBufferTransfer(
        layer,
        commandBuffer,
        "Copy buffer",
        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}
