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

static bool heuristic_is_present_like_image(const VkImageCreateInfo* ci)
{
    if (!ci) return false;

    // Shape & sampling
    if (ci->imageType   != VK_IMAGE_TYPE_2D)        return false; // Guaranteed for presentable images
    if (ci->mipLevels   != 1)                       return false; // Guaranteed for presentable images
    if (ci->samples     != VK_SAMPLE_COUNT_1_BIT)   return false; // Guaranteed for presentable images
    if (ci->extent.depth != 1)                      return false; // Guaranteed for presentable images
    if (ci->arrayLayers != 1)                       return false; // Might introduce false negative, stereo images are excluded

    // Prefer common present-ish color formats.
    switch (ci->format) {
        case VK_FORMAT_B8G8R8A8_UNORM:
        case VK_FORMAT_B8G8R8A8_SRGB:
        case VK_FORMAT_R8G8B8A8_UNORM:
        case VK_FORMAT_R8G8B8A8_SRGB:
        case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
        case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
        case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
        case VK_FORMAT_R16G16B16A16_UNORM:
        case VK_FORMAT_R16G16B16A16_SFLOAT: // HDR paths
        case VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16: // HDR paths
            break; // allowed
        default:
            return false;
    }

    // Square images are likely not for present
    if (ci->extent.width == ci->extent.height) {
        return false;
    }

    // Usage & tiling
    const VkImageUsageFlags u = ci->usage;
    const bool color_rt  = (u & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) != 0; // Color image
    const bool xfer_src  = (u & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) || (u & VK_IMAGE_USAGE_SAMPLED_BIT);  // Needed for the final color image that gets blitted to the swapchain
    const bool til_ok    = (ci->tiling == VK_IMAGE_TILING_OPTIMAL) ||
                           (ci->tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT);

    return color_rt && xfer_src && til_ok;
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
    std::unique_lock<std::mutex> lock{g_vulkanLock};
    auto* layer = Device::retrieve(device);
    const auto& config = layer->instance->config;

    const bool forceDisable  = config.framebuffer_disable_all_compression();
    const bool forceDefault  = config.framebuffer_force_default_compression();
    const uint32_t allowedLevels = config.framebuffer_force_fixed_rate_compression();

    const int disable_external_compression = config.disable_external_compression();
    lock.unlock();


    uint32_t selectedLevel = VK_IMAGE_COMPRESSION_FIXED_RATE_NONE_EXT;
    if (allowedLevels) {
        auto compressionLevels = getSupportedCompressionLevels(layer, pCreateInfo);
        const uint32_t availableLevels = static_cast<uint32_t>(compressionLevels);
        const uint32_t testableLevels  = availableLevels & allowedLevels;
        if (testableLevels) {
            const auto zeros = std::countr_zero(testableLevels);
            selectedLevel = (1u << zeros); // highest matching ratio
        }
    }

    // --------------------------------------------
    // Heuristic + external export intent detection
    // --------------------------------------------
    const bool present_like = heuristic_is_present_like_image(pCreateInfo);

    bool wants_dma_buf    = false;
    bool wants_ahb_export = false;
    for (const VkBaseInStructure* n = reinterpret_cast<const VkBaseInStructure*>(pCreateInfo->pNext);
         n; n = n->pNext) {
        if (n->sType == VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO) {
            const auto* ext = reinterpret_cast<const VkExternalMemoryImageCreateInfo*>(n);
            if (ext->handleTypes & VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT)
                wants_dma_buf = true;
            if (ext->handleTypes & VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID)
                wants_ahb_export = true;
        }
    }

    // -------------------------------------------------
    // Rebuild the pNext chain (drop DRM modifier nodes)
    // -------------------------------------------------
    VkImageCreateInfo local = *pCreateInfo;

    const VkBaseInStructure* src = reinterpret_cast<const VkBaseInStructure*>(pCreateInfo->pNext);
    VkBaseOutStructure* rebuilt_head = nullptr;
    VkBaseOutStructure* rebuilt_tail = nullptr;

    auto append = [&](VkBaseOutStructure* n){
        n->pNext = nullptr;
        if (!rebuilt_head) rebuilt_head = rebuilt_tail = n;
        else { rebuilt_tail->pNext = n; rebuilt_tail = n; }
    };

    auto clone = [&](const VkBaseInStructure* n)->VkBaseOutStructure*{
        size_t sz = sizeof(VkBaseOutStructure);
        switch (n->sType) {
            case VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO:                        sz = sizeof(VkImageFormatListCreateInfo); break;
            case VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO:                      sz = sizeof(VkImageStencilUsageCreateInfo); break;
            case VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO:                         sz = sizeof(VkImageViewUsageCreateInfo); break;
            case VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO:                    sz = sizeof(VkExternalMemoryImageCreateInfo); break;
            case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT:       sz = sizeof(VkImageDrmFormatModifierListCreateInfoEXT); break;
            case VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT:   sz = sizeof(VkImageDrmFormatModifierExplicitCreateInfoEXT); break;
            case VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT:                        sz = sizeof(VkImageCompressionControlEXT); break;
            default: break;
        }
        auto* out = static_cast<VkBaseOutStructure*>(malloc(sz));
        memcpy(out, n, sz);
        out->pNext = nullptr;
        return out;
    };

    bool dropped_modifier = false;
    VkImageCompressionControlEXT* userICCClone = nullptr; // capture cloned ICC if app provided it
    for (; src; src = src->pNext) {
        bool drop = false;
        if (wants_dma_buf) {
            if (src->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT ||
                src->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT) {
                drop = true;
            }
        }
        if (drop) {
            dropped_modifier = true;
            continue;
        }
        VkBaseOutStructure* c = clone(src);
        if (c->sType == VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT) {
            userICCClone = reinterpret_cast<VkImageCompressionControlEXT*>(c);
        }
        append(c);
    }
    if (dropped_modifier && local.tiling == VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT) {
        local.tiling = VK_IMAGE_TILING_OPTIMAL;
    }

    // -----------------------------------------------------------------
    // Decide the final ICC state (apply BOTH policies in this order):
    //   1) framebuffer_* policy (disable/default/fixed-rate)
    //   2) disable_external_compression policy (may override to DISABLED)
    // -----------------------------------------------------------------
    VkImageCompressionControlEXT injectedICC{}; // used only if we need to inject
    VkImageCompressionControlEXT* icc = nullptr;

    // If app already supplied ICC, we’ll modify that one; otherwise we’ll inject ours if needed.
    if (userICCClone) {
        icc = userICCClone;
    } else {
        // We'll only chain this if we end up needing ICC at all.
        injectedICC.sType = VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT;
        injectedICC.pNext = nullptr;
        icc = &injectedICC;
    }

    bool needICC = false;

    // (1) High-priority framebuffer policy
    if (forceDisable) {
        icc->flags = VK_IMAGE_COMPRESSION_DISABLED_EXT;
        icc->compressionControlPlaneCount = 0;
        icc->pFixedRateFlags = nullptr;
        needICC = true;
    } else if (forceDefault) {
        icc->flags = VK_IMAGE_COMPRESSION_DEFAULT_EXT;
        icc->compressionControlPlaneCount = 0;
        icc->pFixedRateFlags = nullptr;
        needICC = true;
    } else if (selectedLevel != VK_IMAGE_COMPRESSION_FIXED_RATE_NONE_EXT) {
        icc->flags = VK_IMAGE_COMPRESSION_FIXED_RATE_EXPLICIT_EXT;
        icc->compressionControlPlaneCount = 1;
        icc->pFixedRateFlags = reinterpret_cast<VkImageCompressionFixedRateFlagsEXT*>(
            &const_cast<uint32_t&>(selectedLevel));
        needICC = true;
    }

    const bool need_icc_disable =
        (disable_external_compression == 1 && wants_ahb_export) ||
        (disable_external_compression == 2 && (wants_ahb_export || present_like));

    if (disable_external_compression == 0) {
        // passthrough of external compression policy; nothing extra here
    } else if (need_icc_disable) {
        // For a guarantee, ensure the device supports VK_EXT_image_compression_control
        bool have_icc_ext = false;
        {
            uint32_t extCount = 0;
            vkEnumerateDeviceExtensionProperties(layer->physicalDevice, nullptr, &extCount, nullptr);
            std::vector<VkExtensionProperties> exts(extCount);
            vkEnumerateDeviceExtensionProperties(layer->physicalDevice, nullptr, &extCount, exts.data());
            for (const auto& e : exts) {
                if (strcmp(e.extensionName, VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME) == 0) {
                    have_icc_ext = true; break;
                }
            }
        }
        if (!have_icc_ext) {
            // Strict behavior to preserve the guarantee; free and fail.
            while (rebuilt_head) { auto* next = (VkBaseOutStructure*)rebuilt_head->pNext; free(rebuilt_head); rebuilt_head = next; }
            return VK_ERROR_FEATURE_NOT_PRESENT;
        }

        // Override to DISABLED (this runs last by design)
        icc->flags = VK_IMAGE_COMPRESSION_DISABLED_EXT;
        icc->compressionControlPlaneCount = 0;
        icc->pFixedRateFlags = nullptr;
        needICC = true;

    }

    // If mode==1 and not an external export, leave original info (except DRM drop for DMA-BUF path which we didn’t do here)
    // NOTE: Your original code only did the passthrough exception for mode==1 && !external.
    if (disable_external_compression == 1 && !wants_dma_buf && !wants_ahb_export) {
        if (needICC) {
            if (!userICCClone) {
                // Prepend our injected ICC ahead of the rebuilt chain
                injectedICC.pNext = rebuilt_head;
                local.pNext = &injectedICC;
            } else {
                // ICC already in rebuilt chain; just attach the rebuilt chain
                local.pNext = rebuilt_head;
            }
            VkResult r = layer->driver.vkCreateImage(device, &local, pAllocator, pImage);
            while (rebuilt_head) { auto* next = (VkBaseOutStructure*)rebuilt_head->pNext; free(rebuilt_head); rebuilt_head = next; }
            return r;
        }
        while (rebuilt_head) { auto* next = (VkBaseOutStructure*)rebuilt_head->pNext; free(rebuilt_head); rebuilt_head = next; }
        return layer->driver.vkCreateImage(device, pCreateInfo, pAllocator, pImage);
    }

    // ---------------------------------------------
    // Stitch final pNext chain and call the driver
    // ---------------------------------------------
    if (needICC) {
        if (!userICCClone) {
            // Prepend our injected ICC ahead of the rebuilt chain
            injectedICC.pNext = rebuilt_head;
            local.pNext = &injectedICC;
        } else {
            // ICC already in rebuilt chain; just attach the rebuilt chain
            local.pNext = rebuilt_head;
        }
    } else {
        // No ICC needed; just attach the rebuilt chain (may be null)
        local.pNext = rebuilt_head;
    }

    VkResult r = layer->driver.vkCreateImage(device, &local, pAllocator, pImage);

    // Cleanup cloned nodes
    while (rebuilt_head) {
        auto* next = (VkBaseOutStructure*)rebuilt_head->pNext;
        free(rebuilt_head);
        rebuilt_head = next;
    }
    return r;
}

