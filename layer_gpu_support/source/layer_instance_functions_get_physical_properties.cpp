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
#include <vulkan/utility/vk_safe_struct.hpp>
#include <vulkan/utility/vk_struct_helper.hpp>

#include "device.hpp"
#include "framework/device_dispatch_table.hpp"

#include <bit>
#include <mutex>

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties<user_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}

template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2<user_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);
    const auto& config = layer->config;  

    // Config gate
    int disable_external_compression = config.disable_external_compression();

    // Inspect query intent
    VkExternalMemoryHandleTypeFlagBits handle = (VkExternalMemoryHandleTypeFlagBits)0;
    bool has_external_info = false;
    bool saw_drm_modifier_info = false;

    for (const VkBaseInStructure* n = (const VkBaseInStructure*)pImageFormatInfo->pNext; n; n = n->pNext) {
        if (n->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO) {
            has_external_info = true;
            const auto* ext = (const VkPhysicalDeviceExternalImageFormatInfo*)n;
            handle = (VkExternalMemoryHandleTypeFlagBits)ext->handleType;
        }
        if (n->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT) {
            saw_drm_modifier_info = true;
        }
    }

    // Only act when we’re asked about DMA-BUF AND policy is enabled
    const bool wants_dma_buf = has_external_info && (handle == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT);

    if (!(disable_external_compression == 0 && wants_dma_buf)) {
        // Pass-through (nothing to strip)
        return layer->driver.vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    }

    // Build a filtered copy that removes modifier filters from the QUERY
    VkPhysicalDeviceImageFormatInfo2 local = *pImageFormatInfo;
    const VkBaseInStructure* src = (const VkBaseInStructure*)pImageFormatInfo->pNext;
    VkBaseOutStructure* head = nullptr;
    VkBaseOutStructure* tail = nullptr;

    auto append = [&](VkBaseOutStructure* node) {
        node->pNext = nullptr;
        if (!head) { head = node; tail = node; } else { tail->pNext = node; tail = node; }
    };
    auto clone_base = [](const VkBaseInStructure* node)->VkBaseOutStructure*{
        VkBaseOutStructure* out = (VkBaseOutStructure*)malloc(sizeof(VkBaseOutStructure));
        memcpy(out, node, sizeof(VkBaseOutStructure));
        out->pNext = nullptr;
        return out;
    };

    bool dropped_modifier = false;
    for (; src; src = src->pNext) {
        bool drop = false;
        if (src->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT) {
            drop = true; dropped_modifier = true;
        }
        if (!drop) append(clone_base(src));
    }

    if (local.tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        local.tiling = VK_IMAGE_TILING_OPTIMAL;
    }
    local.pNext = head;

    VkResult r = layer->driver.vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, &local, pImageFormatProperties);
    while (head) { auto* next = (VkBaseOutStructure*)head->pNext; free(head); head = next; }

    if (r != VK_SUCCESS) {
        fprintf(stderr, "[libGPULayers]   Driver returned %d after stripping modifiers.\n", r);
    }

    lock.unlock();
    return r;
}


/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR<user_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);
    const auto& config = layer->config;  

    //fprintf(stderr, "[libGPULayers] HIT %s (KHR alias)\n", __func__); fflush(stderr);

    // Config gate: only enforce policy for external exports when enabled.
    int disable_external_compression = config.disable_external_compression();

    // Inspect query intent
    VkExternalMemoryHandleTypeFlagBits handle = (VkExternalMemoryHandleTypeFlagBits)0;
    bool has_external_info = false;
    bool saw_drm_modifier_info = false;

    for (const VkBaseInStructure* n = (const VkBaseInStructure*)pImageFormatInfo->pNext; n; n = n->pNext) {
        if (n->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO) {
            has_external_info = true;
            const auto* ext = (const VkPhysicalDeviceExternalImageFormatInfo*)n;
            handle = (VkExternalMemoryHandleTypeFlagBits)ext->handleType;
        }
        if (n->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT) {
            saw_drm_modifier_info = true;
        }
    }

    if (has_external_info) {
        fprintf(stderr, "[libGPULayers] vkGetPhysicalDeviceImageFormatProperties2KHR: external handleType=0x%x\n", (unsigned)handle); fflush(stderr);
    } else {
        //fprintf(stderr, "[libGPULayers] vkGetPhysicalDeviceImageFormatProperties2KHR: no ExternalImageFormatInfo in query.\n"); fflush(stderr);
    }
    if (saw_drm_modifier_info) {
        fprintf(stderr, "[libGPULayers]Query includes PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT\n"); fflush(stderr);
    }

    // Only act when we’re asked about DMA-BUF AND policy is enabled
    const bool wants_dma_buf = has_external_info && (handle == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT);


    if (!(disable_external_compression == 0 && wants_dma_buf)) {
        // Pass-through (nothing to strip)
        return layer->driver.vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
    }

    // Build a filtered copy that removes modifier filters from the QUERY
    VkPhysicalDeviceImageFormatInfo2 local = *pImageFormatInfo;
    const VkBaseInStructure* src = (const VkBaseInStructure*)pImageFormatInfo->pNext;
    VkBaseOutStructure* head = nullptr;
    VkBaseOutStructure* tail = nullptr;

    auto append = [&](VkBaseOutStructure* node) {
        node->pNext = nullptr;
        if (!head) { head = node; tail = node; } else { tail->pNext = node; tail = node; }
    };
    auto clone_base = [](const VkBaseInStructure* node)->VkBaseOutStructure*{
        VkBaseOutStructure* out = (VkBaseOutStructure*)malloc(sizeof(VkBaseOutStructure));
        memcpy(out, node, sizeof(VkBaseOutStructure));
        out->pNext = nullptr;
        return out;
    };

    bool dropped_modifier = false;
    for (; src; src = src->pNext) {
        bool drop = false;
        if (src->sType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT) {
            drop = true; dropped_modifier = true;
        }
        if (!drop) append(clone_base(src));
    }

    if (local.tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        local.tiling = VK_IMAGE_TILING_OPTIMAL;
    }
    local.pNext = head;

    VkResult r = layer->driver.vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, &local, pImageFormatProperties);

    while (head) { auto* next = (VkBaseOutStructure*)head->pNext; free(head); head = next; }

    if (r != VK_SUCCESS) {
        fprintf(stderr, "[libGPULayers]   Driver (KHR) returned %d after stripping modifiers.\n", r); fflush(stderr);
    }

    lock.unlock();
    return r;

}