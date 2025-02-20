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

#include "device.hpp"
#include "framework/device_dispatch_table.hpp"

#include <mutex>

extern std::mutex g_vulkanLock;

/**
 * @brief Pre-transfer code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void preTransfer(Device* layer, VkCommandBuffer commandBuffer)
{
    if (!layer->instance->config.serialize_cmdstream_transfer_pre())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(commandBuffer,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       0,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr);
}

/**
 * @brief Post-transfer code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void postTransfer(Device* layer, VkCommandBuffer commandBuffer)
{
    if (!layer->instance->config.serialize_cmdstream_transfer_post())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(commandBuffer,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       0,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver
        .vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();

    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();
    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
    postTransfer(layer, commandBuffer);
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

    // Release the lock to call into the driver
    lock.unlock();
    preTransfer(layer, commandBuffer);
    layer->driver.vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
    postTransfer(layer, commandBuffer);
}
