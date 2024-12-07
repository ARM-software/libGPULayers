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
#include <thread>

#include "utils.hpp"
#include "version.hpp"

#include "instance.hpp"
#include "instance_functions.hpp"
#include "device.hpp"
#include "device_dispatch_table.hpp"
#include "device_functions.hpp"

extern std::mutex g_vulkanLock;

#define VK_LAYER_EXPORT __attribute__((visibility("default")))

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    #define VK_LAYER_EXPORT_ANDROID VK_LAYER_EXPORT
#else
    #define VK_LAYER_EXPORT_ANDROID
#endif

/**
 * @brief The layer configuration.
 */
#define LGL_VERSION VK_MAKE_VERSION(LGL_VER_MAJOR, LGL_VER_MINOR, LGL_VER_PATCH)

static const std::array<VkLayerProperties, 1> layerProps = {
    {{ LGL_LAYER_NAME, LGL_VERSION, 1, LGL_LAYER_DESC }},
};

/**
 * @brief Dispatch table lookup entry.
 */
struct DispatchTableEntry
{
    /**
     * @brief The function entrypoint name.
     */
    const char* name;

    /**
     * @brief The function pointer.
     */
    PFN_vkVoidFunction function;
};

/**
 * @brief Utility macro to define a lookup for a core function.
 */
#define VK_TABLE_ENTRY(func) \
    { STR(func), reinterpret_cast<PFN_vkVoidFunction>(func) }

/**
 * @brief Utility macro to define a lookup for a layer-dispatch-only function.
 */
#define VK_TABLE_ENTRYL(func) \
    { STR(func), reinterpret_cast<PFN_vkVoidFunction>(layer_##func) }

/**
 * @brief Fetch the layer function for a given instance entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
static PFN_vkVoidFunction get_fixed_instance_layer_function(
    const char* name
) {
    static const DispatchTableEntry layerFunctions[] = {
        VK_TABLE_ENTRY(vkGetInstanceProcAddr),
        VK_TABLE_ENTRY(vkEnumerateDeviceLayerProperties),
        VK_TABLE_ENTRY(vkEnumerateDeviceExtensionProperties),
        VK_TABLE_ENTRY(vkEnumerateInstanceLayerProperties),
        VK_TABLE_ENTRY(vkEnumerateInstanceExtensionProperties),
    };

    for (auto &function : layerFunctions)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    return nullptr;
}

/**
 * @brief Fetch the layer function for a given instance entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't
 *         intercept the function.
 */
static PFN_vkVoidFunction get_instance_layer_function(
    const char* name
) {
    for (auto &function : instanceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    return nullptr;
}

/**
 * @brief Fetch the layer function for a given device entrypoint name.
 *
 * @param name   The layer entry point name.
 *
 * \return The layer function pointer, or \c nullptr if the layer doesn't intercept the function.
 */
static PFN_vkVoidFunction get_device_layer_function(
    const char* name
) {
    static const DispatchTableEntry layerFunctions[] = {
        VK_TABLE_ENTRY(vkGetDeviceProcAddr),
        VK_TABLE_ENTRY(vkEnumerateDeviceExtensionProperties),
        VK_TABLE_ENTRY(vkEnumerateDeviceLayerProperties),
    };

    for (auto &function : layerFunctions)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    for (auto &function : deviceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    return nullptr;
}

/** See Vulkan API for documentation. */
static PFN_vkVoidFunction vkGetDeviceProcAddr_default(
    VkDevice device,
    const char* pName
) {
    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);
    lock.unlock();

    // Only expose functions that the driver exposes to avoid changing
    // queryable interface behavior seen by the application
    auto driver_function = layer->driver.vkGetDeviceProcAddr(device, pName);
    auto layer_function = get_device_layer_function(pName);

    // If driver exposes it and the layer has one, use the layer function
    if (driver_function && layer_function)
    {
        return layer_function;
    }

    // Otherwise just use the driver function, which may be nullptr
    return driver_function;
}

/** See Vulkan API for documentation. */
static PFN_vkVoidFunction vkGetInstanceProcAddr_default(
    VkInstance instance,
    const char* pName
) {
    // Always expose these functions ...
    PFN_vkVoidFunction layerFunction = get_fixed_instance_layer_function(pName);
    if (layerFunction)
    {
        return layerFunction;
    }

    // Otherwise, only expose functions that the driver exposes to avoid
    // changing queryable interface behavior seen by the application
    layerFunction = get_instance_layer_function(pName);
    if (instance) {
        std::unique_lock<std::mutex> lock { g_vulkanLock };
        auto* layer = Instance::retrieve(instance);

        // Don't hold the lock while calling the driver
        lock.unlock();
        PFN_vkVoidFunction driverFunction = layer->nlayerGetProcAddress(layer->instance, pName);

        // If driver exposes it and the layer has one, use the layer function
        if (driverFunction && layerFunction)
        {
            return layerFunction;
        }

        // Otherwise just use the driver function, which may be nullptr
        return driverFunction;
    }

    return layerFunction;
}

/** See Vulkan API for documentation. */
static VkResult vkEnumerateInstanceExtensionProperties_default(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties
) {
    LAYER_TRACE(__func__);

    UNUSED(pProperties);

    if (!pLayerName || strcmp(pLayerName, layerProps[0].layerName))
    {
        return VK_ERROR_LAYER_NOT_PRESENT;
    }

    *pPropertyCount = 0;
    return VK_SUCCESS;
}

/** See Vulkan API for documentation. */
static VkResult vkEnumerateDeviceExtensionProperties_default(
    VkPhysicalDevice gpu,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties
) {
    LAYER_TRACE(__func__);

    UNUSED(pProperties);

    // Android layer enumeration will always pass a nullptr for the device
    if (!gpu)
    {
        if (!pLayerName || strcmp(pLayerName, layerProps[0].layerName))
        {
            return VK_ERROR_LAYER_NOT_PRESENT;
        }

        *pPropertyCount = 0;
        return VK_SUCCESS;
    }

    // For other cases forward to the driver to handle it
    assert(!pLayerName);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(gpu);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumerateDeviceExtensionProperties(gpu, pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
static VkResult vkEnumerateInstanceLayerProperties_default(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties
) {
    LAYER_TRACE(__func__);

    if (pProperties)
    {
        size_t count = std::min(layerProps.size(), static_cast<size_t>(*pPropertyCount));
        if (count < layerProps.size())
        {
            return VK_INCOMPLETE;
        }

        memcpy(pProperties, layerProps.data(), count * sizeof(VkLayerProperties));
        *pPropertyCount = count;
        return VK_SUCCESS;
    }

    *pPropertyCount = layerProps.size();
    return VK_SUCCESS;
}

/** See Vulkan API for documentation. */
static VkResult vkEnumerateDeviceLayerProperties_default(
    VkPhysicalDevice gpu,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties
) {
    LAYER_TRACE(__func__);

    UNUSED(gpu);

    if (pProperties)
    {
        size_t count = std::min(layerProps.size(), static_cast<size_t>(*pPropertyCount));
        if (count < layerProps.size())
        {
            return VK_INCOMPLETE;
        }

        memcpy(pProperties, layerProps.data(), count * sizeof(VkLayerProperties));
        *pPropertyCount = count;
        return VK_SUCCESS;
    }

    *pPropertyCount = layerProps.size();
    return VK_SUCCESS;
}
