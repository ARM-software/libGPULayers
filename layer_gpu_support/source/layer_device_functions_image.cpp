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

#include <bit>
#include <mutex>

extern std::mutex g_vulkanLock;

/**
 * @brief Determine what compression bitrates are supported for this image.
 *
 * @param layer         The device context for the layer.
 * @param pCreateInfo   The image configuration to query.
 *
 * @return Bitmask of supported VkImageCompressionFixedRateFlagBitsEXT bits.
 */
static VkImageCompressionFixedRateFlagsEXT getSupportedCompressionLevels(Device* layer,
                                                                         const VkImageCreateInfo* pCreateInfo)
{
    VkImageCompressionControlEXT compressionInfo {
        .sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT,
        .pNext = nullptr,
        .flags = VK_IMAGE_COMPRESSION_FIXED_RATE_DEFAULT_EXT,
        .compressionControlPlaneCount = 0,
        .pFixedRateFlags = 0,
    };

    VkImageCompressionPropertiesEXT compressionProperties {
        .sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_PROPERTIES_EXT,
        .pNext = nullptr,
        .imageCompressionFlags = 0,
        .imageCompressionFixedRateFlags = 0,
    };

    VkPhysicalDeviceImageFormatInfo2 formatInfo {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2,
        .pNext = reinterpret_cast<const void*>(&compressionInfo),
        .format = pCreateInfo->format,
        .type = pCreateInfo->imageType,
        .tiling = pCreateInfo->tiling,
        .usage = pCreateInfo->usage,
        .flags = pCreateInfo->flags,
    };

    VkImageFormatProperties2 formatProperties {
        .sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2,
        .pNext = reinterpret_cast<void*>(&compressionProperties),
        .imageFormatProperties = {},
    };

    auto instance = layer->instance;
    auto physicalDevice = layer->physicalDevice;

    instance->driver.vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, &formatInfo, &formatProperties);

    return compressionProperties.imageCompressionFixedRateFlags;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateImage<user_tag>(VkDevice device,
                                                             const VkImageCreateInfo* pCreateInfo,
                                                             const VkAllocationCallbacks* pAllocator,
                                                             VkImage* pImage)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);
    const auto& config = layer->instance->config;

    bool forceDisable = config.framebuffer_disable_all_compression();
    bool forceDefault = config.framebuffer_force_default_compression();
    uint32_t allowedLevels = config.framebuffer_force_fixed_rate_compression();

    // Release the lock to call into the driver
    lock.unlock();

    // If we are forcing fixed rate then query the options available
    // Images we cannot change are left unmodified
    uint32_t selectedLevel = VK_IMAGE_COMPRESSION_FIXED_RATE_NONE_EXT;
    if (allowedLevels)
    {
        auto compressionLevels = getSupportedCompressionLevels(layer, pCreateInfo);
        uint32_t availableLevels = static_cast<uint32_t>(compressionLevels);
        uint32_t testableLevels = availableLevels & allowedLevels;

        // Extract the highest matching compression ratio
        if (testableLevels)
        {
            auto zeros = std::countr_zero(testableLevels);
            selectedLevel = 1 << zeros;
        }
    }

    VkImageCreateInfo newCreateInfo = *pCreateInfo;

    VkImageCompressionControlEXT newCompressionControl;
    // TODO: This currently relies on const_cast to make user struct writable
    //       We should replace this with a generic clone (issue #56)
    auto* userCompressionControl =
        searchNextList<VkImageCompressionControlEXT>(VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT,
                                                     pCreateInfo->pNext);

    VkImageCompressionControlEXT* compressionControl = &newCompressionControl;
    if (userCompressionControl)
    {
        compressionControl = userCompressionControl;
    }

    bool patchNeeded = compressionControl != userCompressionControl;

    if (forceDisable)
    {
        compressionControl->sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
        compressionControl->flags = VK_IMAGE_COMPRESSION_DISABLED_EXT;
        compressionControl->compressionControlPlaneCount = 0;
        compressionControl->pFixedRateFlags = nullptr;
    }
    else if (forceDefault)
    {
        compressionControl->sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
        compressionControl->flags = VK_IMAGE_COMPRESSION_DEFAULT_EXT;
        compressionControl->compressionControlPlaneCount = 0;
        compressionControl->pFixedRateFlags = nullptr;
    }
    else if (selectedLevel)
    {
        compressionControl->sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
        compressionControl->flags = VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT;
        compressionControl->compressionControlPlaneCount = 1;
        compressionControl->pFixedRateFlags = reinterpret_cast<VkImageCompressionFixedRateFlagsEXT*>(&selectedLevel);
    }
    else
    {
        patchNeeded = false;
    }

    // If this is new, patch it in to the pNext chain
    if (patchNeeded)
    {
        compressionControl->pNext = newCreateInfo.pNext;
        newCreateInfo.pNext = reinterpret_cast<const void*>(compressionControl);
    }

    return layer->driver.vkCreateImage(device, &newCreateInfo, pAllocator, pImage);
}
