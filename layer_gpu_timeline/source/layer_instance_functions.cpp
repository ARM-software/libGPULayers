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

#include "instance.hpp"
#include "device.hpp"

#include <mutex>
#include <vulkan/utility/vk_struct_helper.hpp>

extern std::mutex g_vulkanLock;

/* See header for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice<user_tag>(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice
) {
    LAYER_TRACE(__func__);

    // Use the default function for the heavy-lifting
    auto res = layer_vkCreateDevice<default_tag>(physicalDevice, pCreateInfo, pAllocator, pDevice);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // Cache flags indicating extension emulation
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(*pDevice);

    static const std::string target { VK_EXT_FRAME_BOUNDARY_EXTENSION_NAME };
    for (auto& ext : layer->instance->injectedDeviceExtensions)
    {
        if (ext.first == target)
        {
            layer->isEmulatingExtFrameBoundary = true;
        }
    }

    return res;
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2<user_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);

    // Patch the query response to show that it is supported
    // TODO: We should hide this when calling down to the driver, and then
    // copy results back to the user structure
    auto* ext = vku::FindStructInPNextChain<VkPhysicalDeviceFrameBoundaryFeaturesEXT>(pFeatures->pNext);
    if (ext)
    {
        ext->frameBoundary = VK_TRUE;
    }
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR<user_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);

    // Patch the query response to show that it is supported
    // TODO: We should hide this when calling down to the driver, and then
    // copy results back to the user structure
    auto* ext = vku::FindStructInPNextChain<VkPhysicalDeviceFrameBoundaryFeaturesEXT>(pFeatures->pNext);
    if (ext)
    {
        ext->frameBoundary = VK_TRUE;
    }
}
