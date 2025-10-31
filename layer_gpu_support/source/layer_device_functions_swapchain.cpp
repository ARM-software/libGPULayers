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
 * @brief Intercept vkCreateSwapchainKHR and, when configured, disable external
 *        compression by forcing uncompressed swapchain images; otherwise pass through.
 *
 * @param device        Logical device creating the swapchain.
 * @param pCreateInfo   Swapchain creation parameters; the pNext chain is
 *                      sanitized (DRM modifier structs rejected, any
 *                      VkImageCompressionControlEXT removed) and augmented
 *                      with VK_IMAGE_COMPRESSION_DISABLED_EXT when compression
 *                      disablement is enabled in the layer config.
 * @param pAllocator    Optional allocation callbacks.
 * @param pSwapchain    Receives the created swapchain handle on success.
 *
 * @return VK_SUCCESS on success, or a VkResult propagated from the driver.
 *         Returns VK_ERROR_FEATURE_NOT_PRESENT if
 *         VK_EXT_image_compression_control is unavailable or if DRM modifier
 *         create-info is present in the pNext chain.
 */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateSwapchainKHR<user_tag>(
    VkDevice device,
    const VkSwapchainCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSwapchainKHR* pSwapchain
) {
    LAYER_TRACE(__func__);

    // --- Read config first, then IMMEDIATE passthrough if disabled ---
    Device* layer = nullptr;
    int disable_external_compression = 0;
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    layer = Device::retrieve(device);
    const auto& config = layer->instance->config;
    disable_external_compression = config.disable_external_compression();
    lock.unlock(); // ensure no lock is held for any Vulkan/loader calls below

    // 0) Absolute passthrough if feature is off — do nothing else
    if (disable_external_compression == 0) {
        VkResult ret = layer->driver.vkCreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
        return ret;
    }

    // 1) Require VK_EXT_image_compression_control (enumerate with DOWN-CHAIN dispatch; no lock held)
    bool have_image_compression_control = false;
    {
        uint32_t extCount = 0;
        layer->instance->driver.vkEnumerateDeviceExtensionProperties(
            layer->physicalDevice, nullptr, &extCount, nullptr);
        std::vector<VkExtensionProperties> exts(extCount);
        layer->instance->driver.vkEnumerateDeviceExtensionProperties(
            layer->physicalDevice, nullptr, &extCount, exts.data());

        for (const auto& e : exts) {
            if (strcmp(e.extensionName, VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME) == 0) {
                have_image_compression_control = true; break;
            }
        }
    }

    if (!have_image_compression_control) {
        fprintf(stderr, "[libGPULayers] layer_vkCreateSwapchainKHR<user_tag> ERROR: VK_EXT_image_compression_control not supported; returning VK_ERROR_FEATURE_NOT_PRESENT\n"); fflush(stderr);
        return VK_ERROR_FEATURE_NOT_PRESENT; // no lock held here
    }

    // 2) Refuse any DRM modifier nodes in pNext (they can mandate compression)
    {
        const VkBaseInStructure* node = reinterpret_cast<const VkBaseInStructure*>(pCreateInfo->pNext);
        for (; node; node = node->pNext) {
            if (node->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT ||
                node->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT) {
                fprintf(stderr, "[libGPULayers] layer_vkCreateSwapchainKHR<user_tag> ERROR: DRM modifier create-info present in swapchain pNext; returning VK_ERROR_FEATURE_NOT_PRESENT\n"); fflush(stderr);
                return VK_ERROR_FEATURE_NOT_PRESENT; // no lock held here
            }
        }
    }

    // 3) Rebuild pNext, filtering out any existing ImageCompressionControl nodes
    VkSwapchainCreateInfoKHR local = *pCreateInfo;
    const VkBaseInStructure* src = reinterpret_cast<const VkBaseInStructure*>(pCreateInfo->pNext);
    VkBaseOutStructure* head = nullptr;
    VkBaseOutStructure* tail = nullptr;

    auto append = [&](VkBaseOutStructure* n){
        n->pNext = nullptr;
        if (!head) { head = tail = n; } else { tail->pNext = n; tail = n; }
    };

    auto clone = [](const VkBaseInStructure* n)->VkBaseOutStructure* {
        size_t sz = sizeof(VkBaseOutStructure);
        if (n->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT)
            sz = sizeof(VkImageDrmFormatModifierListCreateInfoEXT);
        else if (n->sType == VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT)
            sz = sizeof(VkImageDrmFormatModifierExplicitCreateInfoEXT);
        else if (n->sType == VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT)
            sz = sizeof(VkImageCompressionControlEXT);

        auto* out = (VkBaseOutStructure*)malloc(sz);
        memcpy(out, n, sz);
        out->pNext = nullptr;

        return out;
    };

    for (; src; src = src->pNext) {
        const bool drop = (src->sType == VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT);
        if (!drop) append(clone(src));
    }

    VkImageCompressionControlEXT compression_ctl {
        VK_STRUCTURE_TYPE_IMAGE_COMPRESSION_CONTROL_EXT,
        head,                               // keep the rest of the chain
        VK_IMAGE_COMPRESSION_DISABLED_EXT,  // compression OFF for swapchain images
        0,
        nullptr
    };
    local.pNext = &compression_ctl;

    // 4) Call down-chain create (no lock held)
    VkResult r = layer->driver.vkCreateSwapchainKHR(device, &local, pAllocator, pSwapchain);

    // Free rebuilt nodes (do NOT free compression_ctl — it’s on the stack)
    while (head) { auto* next = (VkBaseOutStructure*)head->pNext; free(head); head = next; }
    return r;
}
