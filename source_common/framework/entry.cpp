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

/**
 * @file
 * This module exposes the entrypoints used by the layer loader.
 *
 * Note that the Android loader requires more functions to be exposed as
 * library symbols than other Vulkan loaders.
 */
#include "framework/device_functions.hpp"
#include "framework/instance_functions.hpp"
#include "framework/utils.hpp"

#include <mutex>

#if __has_include("layer_device_functions.hpp")
#  include "layer_device_functions.hpp"
#endif

#if __has_include("layer_instance_functions.hpp")
#  include "layer_instance_functions.hpp"
#endif

std::mutex g_vulkanLock;

extern "C"
{
/** See Vulkan API for documentation. */
VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    return layer_vkGetDeviceProcAddr<user_tag>(device, pName);
}

/** See Vulkan API for documentation. */
VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return layer_vkGetInstanceProcAddr<user_tag>(instance, pName);
}

/** See Vulkan API for documentation. */
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
    vkEnumerateInstanceExtensionProperties(const char* pLayerName,
                                           uint32_t* pPropertyCount,
                                           VkExtensionProperties* pProperties)
{
    return layer_vkEnumerateInstanceExtensionProperties<user_tag>(pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VK_LAYER_EXPORT_ANDROID VKAPI_ATTR VkResult VKAPI_CALL
    vkEnumerateDeviceExtensionProperties(VkPhysicalDevice gpu,
                                         const char* pLayerName,
                                         uint32_t* pPropertyCount,
                                         VkExtensionProperties* pProperties)
{
    return layer_vkEnumerateDeviceExtensionProperties<user_tag>(gpu, pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount,
                                                                                  VkLayerProperties* pProperties)
{
    return layer_vkEnumerateInstanceLayerProperties<user_tag>(pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VK_LAYER_EXPORT_ANDROID VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice gpu,
                                                                                        uint32_t* pPropertyCount,
                                                                                        VkLayerProperties* pProperties)
{
    return layer_vkEnumerateDeviceLayerProperties<user_tag>(gpu, pPropertyCount, pProperties);
}
}
