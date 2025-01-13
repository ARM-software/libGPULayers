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

#include "framework/manual_functions.hpp"

/**
 * @brief Shared globals.
 */
extern std::mutex g_vulkanLock;

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

/* See header for documentation. */
VkLayerInstanceCreateInfo* getChainInfo(
    const VkInstanceCreateInfo* pCreateInfo
) {
    auto* info = static_cast<const VkLayerInstanceCreateInfo*>(pCreateInfo->pNext);
    while (info)
    {
        bool isType = info->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO;
        bool isFunction = info->function == VK_LAYER_LINK_INFO;
        if (isType && isFunction)
        {
            break;
        }

        info = static_cast<const VkLayerInstanceCreateInfo*>(info->pNext);
    }

    return const_cast<VkLayerInstanceCreateInfo*>(info);
}

/* See header for documentation. */
VkLayerDeviceCreateInfo* getChainInfo(
    const VkDeviceCreateInfo* pCreateInfo
) {
    auto* info = static_cast<const VkLayerDeviceCreateInfo*>(pCreateInfo->pNext);
    while (info)
    {
        bool isType = info->sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO;
        bool isFunction = info->function == VK_LAYER_LINK_INFO;
        if (isType && isFunction)
        {
            break;
        }

        info = static_cast<const VkLayerDeviceCreateInfo*>(info->pNext);
    }

    return const_cast<VkLayerDeviceCreateInfo*>(info);
}

/* See header for documentation. */
PFN_vkVoidFunction getFixedInstanceLayerFunction(
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

/* See header for documentation. */
PFN_vkVoidFunction getInstanceLayerFunction(
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

/* See header for documentation. */
PFN_vkVoidFunction getDeviceLayerFunction(
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

/* See header for documentation. */
std::vector<std::string> getInstanceExtensionList(
    const VkInstanceCreateInfo* pCreateInfo
) {
    std::vector<std::string> foundExtensions;

    // Fetch the functions needed to query extensions availability
    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpGetExtensionsRaw = fpGetProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");
    auto fpGetExtensions = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(fpGetExtensionsRaw);
    if (!fpGetExtensions)
    {
        return foundExtensions;
    }

    // Query number of extensions
    uint32_t count;
    fpGetExtensions(nullptr, &count, nullptr);

    // Reserve memory for, and then query, the extensions
    std::vector<VkExtensionProperties> extensions;
    extensions.resize(count);
    fpGetExtensions(nullptr, &count, extensions.data());

    // Build the function return list
    for (uint32_t i = 0; i < count; i++)
    {
        foundExtensions.emplace_back(extensions[i].extensionName);
    }

    return foundExtensions;
}

/* See header for documentation. */
std::vector<std::string> getDeviceExtensionList(
    VkInstance instance,
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo
) {
    std::vector<std::string> foundExtensions;

    // Fetch the functions needed to query extensions availability
    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpGetExtensionsRaw = fpGetProcAddr(instance, "vkEnumerateDeviceExtensionProperties");
    auto fpGetExtensions = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(fpGetExtensionsRaw);
    if (!fpGetExtensions)
    {
        return foundExtensions;
    }

    // Query number of extensions
    uint32_t count;
    fpGetExtensions(physicalDevice, nullptr, &count, nullptr);

    // Reserve memory for, and then query, the extensions
    std::vector<VkExtensionProperties> extensions;
    extensions.resize(count);
    fpGetExtensions(physicalDevice, nullptr, &count, extensions.data());

    // Build the function return list
    for (uint32_t i = 0; i < count; i++)
    {
        foundExtensions.emplace_back(extensions[i].extensionName);
    }

    return foundExtensions;
}

/* See header for documentation. */
bool isInExtensionList(
    const std::string& target,
    uint32_t extensionCount,
    const char* const* extensionList
) {
    for(uint32_t i = 0; i < extensionCount; i++)
    {
        if (target == extensionList[i])
        {
            return true;
        }
    }

    return false;
}

/* See header for documentation. */
std::vector<const char*> cloneExtensionList(
    uint32_t extensionCount,
    const char* const* extensionList
) {
    std::vector<const char*> data;
    for(uint32_t i = 0; i < extensionCount; i++)
    {
        data.emplace_back(extensionList[i]);
    }

    return data;
}

/** See Vulkan API for documentation. */
PFN_vkVoidFunction layer_vkGetInstanceProcAddr_default(
    VkInstance instance,
    const char* pName
) {
    // Always expose these functions ...
    PFN_vkVoidFunction layerFunction = getFixedInstanceLayerFunction(pName);
    if (layerFunction)
    {
        return layerFunction;
    }

    // Otherwise, only expose functions that the driver exposes to avoid
    // changing queryable interface behavior seen by the application
    layerFunction = getInstanceLayerFunction(pName);
    if (instance) {
        std::unique_lock<std::mutex> lock { g_vulkanLock };
        auto* layer = Instance::retrieve(instance);

        // Don't hold the lock while calling the driver
        lock.unlock();
        PFN_vkVoidFunction driverFunction = layer->nlayerGetProcAddress(instance, pName);

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
PFN_vkVoidFunction layer_vkGetDeviceProcAddr_default(
    VkDevice device,
    const char* pName
) {
    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);
    lock.unlock();

    // Only expose functions that the driver exposes to avoid changing
    // queryable interface behavior seen by the application
    auto driverFunction = layer->driver.vkGetDeviceProcAddr(device, pName);
    auto layerFunction = getDeviceLayerFunction(pName);

    // If driver exposes it and the layer has one, use the layer function
    if (driverFunction && layerFunction)
    {
        return layerFunction;
    }

    // Otherwise just use the driver function, which may be nullptr
    return driverFunction;
}

/** See Vulkan API for documentation. */
VkResult layer_vkEnumerateInstanceExtensionProperties_default(
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
VkResult layer_vkEnumerateDeviceExtensionProperties_default(
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
VkResult layer_vkEnumerateInstanceLayerProperties_default(
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
VkResult layer_vkEnumerateDeviceLayerProperties_default(
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

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance_default(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance
) {
    LAYER_TRACE(__func__);

    // We cannot reliably query the available instance extensions on Android if multiple layers are
    // installed, so we disable this by default. This occurs because Android only implements the v0
    // specification between the loader and the interceptor, and does not implement chainable
    // intercepts for vkEnumerateInstanceExtensionProperties().
    //
    // On Android if you call chainInfo getInstanceProcAddr() to get the function in the next layer
    // you will get the layer implementation of the function, and layer implementations of this
    // function will return the additional extensions that the layer itself provides. It does not
    // forward to the driver, and any query for anything other than the layer will just return
    // VK_ERROR_LAYER_NOT_PRESENT.
    //
    // If you are running with a single layer you can set this to true, and use proper queries.
    constexpr bool queryExtensions = false;

    std::vector<std::string> supportedExtensions;
    if (queryExtensions)
    {
        supportedExtensions = getInstanceExtensionList(pCreateInfo);
    }

    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpCreateInstanceRaw = fpGetInstanceProcAddr(nullptr, "vkCreateInstance");
    auto fpCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(fpCreateInstanceRaw);
    if (!fpCreateInstance)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Create a copy we can write
    VkInstanceCreateInfo newCreateInfo = *pCreateInfo;

    // Query extension state
    std::string targetExt("VK_EXT_debug_utils");
    // Assume common extensions are available (see comment at start of function)
    bool targetSupported = true;
    if (queryExtensions)
    {
        targetSupported = isIn(targetExt, supportedExtensions);
    }

    bool targetEnabled = isInExtensionList(
        targetExt,
        pCreateInfo->enabledExtensionCount,
        pCreateInfo->ppEnabledExtensionNames);

    if (!targetSupported)
    {
        LAYER_LOG("WARNING: Cannot enable additional extension: %s", targetExt.c_str());
    }

    // Enable the extension if we need to
    std::vector<const char*> newExtList;
    if (targetSupported && !targetEnabled)
    {
        LAYER_LOG("Enabling additional extension: %s", targetExt.c_str());
        newExtList = cloneExtensionList(
            pCreateInfo->enabledExtensionCount,
            pCreateInfo->ppEnabledExtensionNames);

        newExtList.push_back(targetExt.c_str());

        newCreateInfo.enabledExtensionCount = newExtList.size();
        newCreateInfo.ppEnabledExtensionNames = newExtList.data();
    }

    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto res = fpCreateInstance(&newCreateInfo, pAllocator, pInstance);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    // Retake the lock to access layer-wide global store
    auto instance = std::make_unique<Instance>(*pInstance, fpGetInstanceProcAddr);
    {
        std::lock_guard<std::mutex> lock { g_vulkanLock };
        Instance::store(*pInstance, instance);
    }

    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance_default(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Layer proxy must be destroyed before the driver version
    // so we can clean up any layer-owned resources
    Instance::destroy(layer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyInstance(instance, pAllocator);

}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice_default(
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
    auto fpCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(fpGetInstanceProcAddr(layer->instance, "vkCreateDevice"));
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

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice_default(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Layer proxy must be destroyed before the driver version
    // so we can clean up any layer-owned resources
    Device::destroy(layer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDevice(device, pAllocator);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR_default(
    VkDevice device,
    const VkDeviceImageMemoryRequirements* pInfo,
    VkMemoryRequirements2* pMemoryRequirements
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(device);

    // Workaround Unreal Engine trying to invoke this via a function pointer
    // queried from a Vulkan 1.1 instance with vkGetInstanceProcAddress() using
    // a device created from a later a Vulkan 1.0 context for which the
    // function is unavailable because VK_KHR_maintenance4 requires Vulkan 1.1
    if (!layer->driver.vkGetDeviceImageMemoryRequirementsKHR)
    {
        pMemoryRequirements->memoryRequirements.size = 0;
        pMemoryRequirements->memoryRequirements.alignment = 0;
        pMemoryRequirements->memoryRequirements.memoryTypeBits = 0;
        return;
    }

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}
