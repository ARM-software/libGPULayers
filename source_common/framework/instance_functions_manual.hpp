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
 * This module exposes common functionality used by layer entrypoints,
 * implemented as library code which can be swapped for alternative
 * implementations on a per-layer basis if needed.
 */
#include <array>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "device.hpp"
#include "instance.hpp"
#include "version.hpp"


#include "framework/instance_functions.hpp"

#include "framework/device_dispatch_table.hpp"
#include "framework/device_functions.hpp"
#include "framework/utils.hpp"

/**
 * @brief Extract the layer chain info from the instance creation info.
 *
 * @param pCreateInfo   The instance creation data from the loader.
 *
 * @return The instance creation info, or @c nullptr if not found.
 */
VkLayerInstanceCreateInfo* getChainInfo(
    const VkInstanceCreateInfo* pCreateInfo);

/**
 * @brief Extract the layer chain info from the device creation info.
 *
 * @param pCreateInfo   The device creation data from the loader.
 *
 * @return The instance creation info, or @c nullptr if not found.
 */
VkLayerDeviceCreateInfo* getChainInfo(
    const VkDeviceCreateInfo* pCreateInfo);

/**
 * @brief Fetch the function for a given static instance entrypoint name.
 *
 * This function is used for finding the fixed entrypoints that must exist and
 * that can return a valid function pointer without needing a created instance.
 *
 * @param name   The Vulkan function name.
 *
 * @return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
PFN_vkVoidFunction getFixedInstanceLayerFunction(
    const char* name);

/**
 * @brief Fetch the function for a given dynamic instance entrypoint name.
 *
 * This function is used for finding the dynamic entrypoints that need a
 * created instance to return a valid function pointer.
 *
 * @param name   The Vulkan function name.
 *
 * @return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
PFN_vkVoidFunction getInstanceLayerFunction(
    const char* name);

/**
 * @brief Fetch the function for a given dynamic instance entrypoint name.
 *
 * This function is used for finding the dynamic entrypoints that need a
 * created device to return a valid function pointer.
 *
 * @param name   The Vulkan function name.
 *
 * @return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
PFN_vkVoidFunction getDeviceLayerFunction(
    const char* name);

/**
 * @brief Fetch the list of supported extensions from the instance.
 *
 * @param pCreateInfo   The instance creation data from the loader.
 *
 * @return The list of supported extensions; empty list on failure.
 */
std::vector<std::string> getInstanceExtensionList(
    const VkInstanceCreateInfo* pCreateInfo);

/**
 * @brief Is an extension in the passed extension list.
 *
 * @param target           The target extension to look for.
 * @param extensionCount   The number of extensions in the list.
 * @param extensionList    The list of extensions.
 *
 * @return @c true if @c target is found in @c extensionList.
 */
bool isInExtensionList(
    const std::string& target,
    uint32_t extensionCount,
    const char* const* extensionList);

/**
 * @brief Clone the target extension list.
 *
 * @param extensionCount   The number of extensions in the list.
 * @param extensionList    The list of extensions.
 *
 * @return the cloned list.
 */
std::vector<const char*> cloneExtensionList(
    uint32_t extensionCount,
    const char* const* extensionList);

/** See Vulkan API for documentation. */
PFN_vkVoidFunction layer_vkGetDeviceProcAddr_default(
    VkDevice device,
    const char* pName);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName
) {
    return layer_vkGetDeviceProcAddr_default(device, pName);
}

/** See Vulkan API for documentation. */
PFN_vkVoidFunction layer_vkGetInstanceProcAddr_default(
    VkInstance instance,
    const char* pName);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetInstanceProcAddr(
    VkInstance instance,
    const char* pName
) {
    return layer_vkGetInstanceProcAddr_default(instance, pName);
}

/** See Vulkan API for documentation. */
VkResult layer_vkEnumerateInstanceExtensionProperties_default(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceExtensionProperties(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties
) {
    return layer_vkEnumerateInstanceExtensionProperties_default(pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VkResult layer_vkEnumerateDeviceExtensionProperties_default(
    VkPhysicalDevice gpu,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceExtensionProperties(
    VkPhysicalDevice gpu,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties
) {
    return layer_vkEnumerateDeviceExtensionProperties_default(gpu, pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VkResult layer_vkEnumerateInstanceLayerProperties_default(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceLayerProperties(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties
) {
    return layer_vkEnumerateInstanceLayerProperties_default(pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
VkResult layer_vkEnumerateDeviceLayerProperties_default(
    VkPhysicalDevice gpu,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceLayerProperties(
    VkPhysicalDevice gpu,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties
) {
    return layer_vkEnumerateDeviceLayerProperties_default(gpu, pPropertyCount, pProperties);
}
