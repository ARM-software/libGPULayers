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
 * @brief Intercept vkAllocateMemory and hard-fail on external memory imports
 *        that could mandate external compression; otherwise pass through to the driver.
 *
 * @details Scans @p pAllocateInfo->pNext for import structs. If it finds
 *          VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID or
 *          VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR with
 *          VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT, it returns
 *          VK_ERROR_FEATURE_NOT_PRESENT to preserve the guarantee that
 *          external compression is not used. When no such imports are present, the
 *          call is forwarded unchanged.
 *
 * @param device         Logical device allocating the memory.
 * @param pAllocateInfo  Allocation parameters; its pNext chain is inspected
 *                       for import info.
 * @param pAllocator     Optional allocation callbacks.
 * @param pMemory        Receives the allocated device memory on success.
 *
 * @return VK_SUCCESS on success, or a VkResult propagated from the driver.
 *         Returns VK_ERROR_FEATURE_NOT_PRESENT when disallowed external
 *         import types are detected in the pNext chain.
 *
 * @note This is a strict policy check; additional import structures may be
 *       rejected in the future to maintain the compression-off guarantee.
 */

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkAllocateMemory<user_tag>(
    VkDevice device,
    const VkMemoryAllocateInfo* pAllocateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDeviceMemory* pMemory
) {
    LAYER_TRACE(__func__);
    
    std::unique_lock<std::mutex> lock{g_vulkanLock};
    auto* layer = Device::retrieve(device);
    const auto& config = layer->instance->config;

    const int disable_external_compression = config.disable_external_compression();

    // Absolute passthrough if feature is off
    if (disable_external_compression == 0) 
    {
        lock.unlock();
        return layer->driver.vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
    }

    // Scan pNext for imports that we cannot sanitize -> hard-fail to keep the 100% guarantee that we can disable external compression
    for (const auto* n = reinterpret_cast<const VkBaseInStructure*>(pAllocateInfo->pNext); n; n = n->pNext)
    {

        if (n->sType == VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID) 
        {
            LAYER_LOG("[libGPULayers] vkAllocateMemory: AHardwareBuffer IMPORT detected. "
                    "Cannot guarantee external compression is disabled (buffer created outside Vulkan). Failing by policy.");
            return VK_ERROR_FEATURE_NOT_PRESENT;
        }

        if (n->sType == VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR)
        {
            const auto* fdInfo = reinterpret_cast<const VkImportMemoryFdInfoKHR*>(n);

            if (fdInfo->handleType == VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT) 
            {
                LAYER_LOG("[libGPULayers] vkAllocateMemory: DMA-BUF memory IMPORT detected (fd=%d). "
                        "Cannot guarantee external compression (DRM modifier may imply compression). Failing by policy.",
                        fdInfo->fd);
                return VK_ERROR_FEATURE_NOT_PRESENT;
            }
        }
        
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}
