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

#include <mutex>

#include "framework/manual_functions.hpp"

#include "device.hpp"
#include "layer_instance_functions.hpp"

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice<user_tag>(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();

    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpGetDeviceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetDeviceProcAddr;

    auto extensions = getDeviceExtensionList(
        layer->instance, physicalDevice, pCreateInfo);

    auto fpCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(
        fpGetInstanceProcAddr(layer->instance, "vkCreateDevice"));
    if (!fpCreateDevice)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Advance the link info for the next element on the chain
    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto res = fpCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto device = std::make_unique<Device>(layer, physicalDevice, *pDevice, fpGetDeviceProcAddr);
    Device::store(*pDevice, std::move(device));

    return VK_SUCCESS;
}
