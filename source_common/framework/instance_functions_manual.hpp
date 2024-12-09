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

#include "utils.hpp"
#include "version.hpp"

#include "instance.hpp"
#include "instance_functions.hpp"
#include "device.hpp"
#include "device_dispatch_table.hpp"
#include "device_functions.hpp"

#define VK_LAYER_EXPORT __attribute__((visibility("default")))

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    #define VK_LAYER_EXPORT_ANDROID VK_LAYER_EXPORT
#else
    #define VK_LAYER_EXPORT_ANDROID
#endif

VkLayerInstanceCreateInfo* getChainInfo(
    const VkInstanceCreateInfo* pCreateInfo,
    VkLayerFunction func);

VkLayerDeviceCreateInfo* getChainInfo(
    const VkDeviceCreateInfo* pCreateInfo,
    VkLayerFunction func);

/**
 * @brief Fetch the layer function for a given instance entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
PFN_vkVoidFunction getFixedInstanceLayerFunction(
    const char* name);

/**
 * @brief Fetch the layer function for a given instance entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
PFN_vkVoidFunction getInstanceLayerFunction(
    const char* name);

/**
 * @brief Fetch the layer function for a given device entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't intercept the function.
 */
PFN_vkVoidFunction getDeviceLayerFunction(
    const char* name);

/* TODO. */
std::vector<std::string> getInstanceExtensionList(
    const VkInstanceCreateInfo* pCreateInfo);

/** See Vulkan API for documentation. */
PFN_vkVoidFunction vkGetDeviceProcAddr_default(
    VkDevice device,
    const char* pName);

/** See Vulkan API for documentation. */
PFN_vkVoidFunction vkGetInstanceProcAddr_default(
    VkInstance instance,
    const char* pName);

/** See Vulkan API for documentation. */
VkResult vkEnumerateInstanceExtensionProperties_default(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/** See Vulkan API for documentation. */
VkResult vkEnumerateDeviceExtensionProperties_default(
    VkPhysicalDevice gpu,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/** See Vulkan API for documentation. */
VkResult vkEnumerateInstanceLayerProperties_default(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);

/** See Vulkan API for documentation. */
VkResult vkEnumerateDeviceLayerProperties_default(
    VkPhysicalDevice gpu,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);
