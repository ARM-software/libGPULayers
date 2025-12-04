/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024-2025 Arm Limited
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

#include <vulkan/utility/vk_struct_helper.hpp>

#include "framework/manual_functions.hpp"
#include "utils/misc.hpp"

/**
 * @brief Shared globals.
 */
extern std::mutex g_vulkanLock;

/**
 * @brief The layer configuration.
 */
#define LGL_VERSION VK_MAKE_VERSION(LGL_VER_MAJOR, LGL_VER_MINOR, LGL_VER_PATCH)

static const std::array<VkLayerProperties, 1> layerProps = {
    {{LGL_LAYER_NAME, LGL_VERSION, 1, LGL_LAYER_DESC}},
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
#define VK_TABLE_ENTRY(func)                                                     \
    {                                                                            \
        STR(func), reinterpret_cast<PFN_vkVoidFunction>(layer_##func<user_tag>)  \
    }

/* See header for documentation. */
VkLayerInstanceCreateInfo* getChainInfo(const VkInstanceCreateInfo* pCreateInfo)
{
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
VkLayerDeviceCreateInfo* getChainInfo(const VkDeviceCreateInfo* pCreateInfo)
{
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
bool isFunctionAlwaysExported(const char* name)
{
    const std::array<const char*, 11> alwaysExportedFunctions {
        "vkGetInstanceProcAddr",
        "vkGetDeviceProcAddr",
        "vkEnumerateInstanceExtensionProperties",
        "vkEnumerateDeviceExtensionProperties",
        "vkEnumerateInstanceLayerProperties",
        "vkEnumerateDeviceLayerProperties",
        "vkCreateInstance",
        "vkDestroyInstance",
        "vkCreateDevice",
        "vkDestroyDevice",
        "vkGetDeviceImageMemoryRequirementsKHR",
    };

    for (const char* functionName : alwaysExportedFunctions)
    {
        if (!strcmp(functionName, name))
        {
            return true;
        }
    }

    return false;
}

/* See header for documentation. */
std::tuple<bool, PFN_vkVoidFunction, bool> getInstanceLayerFunction(const char* name)
{
    const std::array<const char*, 5> globalFunctions {
        // Supported since Vulkan 1.0
        "vkCreateInstance",
        "vkEnumerateInstanceExtensionProperties",
        "vkEnumerateInstanceLayerProperties",
        // Supported since Vulkan 1.1
        "vkEnumerateInstanceVersion",
        // Supported since Vulkan 1.2
        "vkGetInstanceProcAddr",
    };

    bool isGlobal {false};
    for (const char* globalName : globalFunctions)
    {
        if (!strcmp(globalName, name))
        {
            isGlobal = true;
            break;
        }
    }

    for (auto& function : instanceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return std::make_tuple(isGlobal, function.function, function.hasLayerSpecialization);
        }
    }

    return std::make_tuple(isGlobal, nullptr, false);
}

/* See header for documentation. */
std::pair<PFN_vkVoidFunction, bool> getDeviceLayerFunction(const char* name)
{
    for (auto& function : deviceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return {function.function, function.hasLayerSpecialization};
        }
    }

    return {nullptr, false};
}

/* See header for documentation. */
APIVersion getInstanceAPIVersion(PFN_vkGetInstanceProcAddr fpGetProcAddr)
{
    // TODO: This will crash in Khronos validation if we try to use this
    // with the validation layer beneath us due to Android loader v0 protocol.
#if 0
    return { 1, 3 };
#endif

    // Try to get vkEnumerateInstanceVersion, and assume this is a Vulkan 1.0
    // feature level if we don't get it ...
    auto fpFunctionRaw = fpGetProcAddr(nullptr, "vkEnumerateInstanceVersion");
    auto fpFunction = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(fpFunctionRaw);
    if (!fpFunction)
    {
        LAYER_ERR("Failed to get vkEnumerateInstanceVersion(), assuming Vulkan 1.0");
        return {1, 0};
    }

    uint32_t apiVersion = 0;
    auto result = fpFunction(&apiVersion);
    if (result != VK_SUCCESS)
    {
        LAYER_ERR("Failed to call vkEnumerateInstanceVersion()");
        return {0, 0};
    }

    uint32_t major = VK_API_VERSION_MAJOR(apiVersion);
    uint32_t minor = VK_API_VERSION_MINOR(apiVersion);
    return {major, minor};
}

/* See header for documentation. */
APIVersion getApplicationAPIVersion(const VkInstanceCreateInfo* pCreateInfo)
{
    uint32_t apiVersion = pCreateInfo->pApplicationInfo->apiVersion;
    uint32_t major = VK_API_VERSION_MAJOR(apiVersion);
    uint32_t minor = VK_API_VERSION_MINOR(apiVersion);
    return {major, minor};
}

/* See header for documentation. */
APIVersion getDeviceAPIVersion(Instance& instance,
                               VkPhysicalDevice physicalDevice)
{
    VkPhysicalDeviceProperties properties {};
    instance.driver.vkGetPhysicalDeviceProperties(physicalDevice, &properties);

    uint32_t major = VK_API_VERSION_MAJOR(properties.apiVersion);
    uint32_t minor = VK_API_VERSION_MINOR(properties.apiVersion);
    return {major, minor};
}

/**
 * @brief Is version A >= version B.
 */
static bool isVersionGreaterEqual(const APIVersion& a, const APIVersion& b)
{
    // Different major version
    if (a.first != b.first)
    {
        return a.first > b.first;
    }

    // Same major version, so test minor version
    return a.second >= b.second;
}

/**
 * @brief Is version A > version B.
 */
static bool isVersionGreater(const APIVersion& a, const APIVersion& b)
{
    // Different major version
    if (a.first != b.first)
    {
        return a.first > b.first;
    }

    // Same major version, so test minor version
    return a.second > b.second;
}

/* See header for documentation. */
APIVersion increaseAPIVersion(const APIVersion& userVersion,
                              const APIVersion& maxVersion,
                              const APIVersion& requiredVersion)
{
    // User version is good enough to support the layer, so stick with that
    if (isVersionGreaterEqual(userVersion, requiredVersion))
    {
        LAYER_LOG("Instance API version %u.%u (user setting meets layer minimum)",
                  userVersion.first,
                  userVersion.second);

        return userVersion;
    }

    // Required version is higher than the max version so log a warning
    // and try to continue using maxVersion but it may fail ...
    if (isVersionGreater(requiredVersion, maxVersion))
    {
        LAYER_ERR("Instance API version %u.%u (lower than layer minimum)", maxVersion.first, maxVersion.second);

        return maxVersion;
    }

    LAYER_LOG("Instance API version %u.%u (increased to layer minimum)", requiredVersion.first, requiredVersion.second);

    return requiredVersion;
}

/* See header for documentation. */
std::vector<std::string> getInstanceExtensionList(const VkInstanceCreateInfo* pCreateInfo)
{
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
std::vector<std::string> getDeviceExtensionList(Instance& instance,
                                                VkPhysicalDevice physicalDevice)
{
    // Query number of extensions
    uint32_t count;
    instance.driver.vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr);

    // Reserve memory for, and then query, the extensions
    std::vector<VkExtensionProperties> extensions;
    extensions.resize(count);
    instance.driver.vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, extensions.data());

    // Build the function return list
    std::vector<std::string> foundExtensions;
    foundExtensions.reserve(count);
    for (uint32_t i = 0; i < count; i++)
    {
        foundExtensions.emplace_back(extensions[i].extensionName);
    }

    return foundExtensions;
}

/* See header for documentation. */
std::vector<const char*> cloneExtensionList(uint32_t extensionCount, const char* const* extensionList)
{
    std::vector<const char*> data;
    data.reserve(extensionCount);
    for (uint32_t i = 0; i < extensionCount; i++)
    {
        data.emplace_back(extensionList[i]);
    }

    return data;
}

/**
 * Enable VK_EXT_debug_utils if not enabled.
 *
 * Enabling this requires passing the extension string to vkCreateInstance().
 *
 * @param createInfo   The createInfo we can search to find user config.
 * @param supported    The list of supported extension, or empty if unknown.
 */
static void enableInstanceVkExtDebugUtils(vku::safe_VkInstanceCreateInfo& createInfo,
                                          const std::vector<std::string>& supported)
{
    static const std::string target {VK_EXT_DEBUG_UTILS_EXTENSION_NAME};

    // Test if the desired extension is supported. If supported list is
    // empty then we didn't query and assume extension is supported.
    if (supported.size() && !isIn(target, supported))
    {
        LAYER_ERR("Instance extension not available: %s", target.c_str());
        return;
    }

    // Enable the extension - this will skip adding if already enabled
    if (vku::AddExtension(createInfo, target.c_str()))
    {
        LAYER_LOG("Instance extension added: %s", target.c_str());
    }
    else
    {
        LAYER_LOG("Instance extension already enabled: %s", target.c_str());
    }
}

/* See header for documentation. */
void enableDeviceVkKhrTimelineSemaphore(Instance& instance,
                                        VkPhysicalDevice physicalDevice,
                                        vku::safe_VkDeviceCreateInfo& createInfo,
                                        std::vector<std::string>& supported)
{
    UNUSED(instance);
    UNUSED(physicalDevice);

    static const std::string target {VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME};

    // We know we can const-cast here because createInfo is a safe-struct clone
    void* pNextBase = const_cast<void*>(createInfo.pNext);

    VkPhysicalDeviceTimelineSemaphoreFeatures newFeatures = vku::InitStructHelper();

    // Test if the desired extension is supported
    if (!isIn(target, supported))
    {
        LAYER_LOG("Device extension not available: %s", target.c_str());
        return;
    }

    // Enable the extension - this will skip adding if already enabled
    if (vku::AddExtension(createInfo, target.c_str()))
    {
        LAYER_LOG("Device extension added: %s", target.c_str());
    }

    // Check if user provided a VkPhysicalDeviceTimelineSemaphoreFeatures
    auto* config1 = vku::FindStructInPNextChain<VkPhysicalDeviceTimelineSemaphoreFeatures>(pNextBase);
    if (config1)
    {
        if (!config1->timelineSemaphore)
        {
            LAYER_LOG("Device extension force enabled: %s", target.c_str());
            config1->timelineSemaphore = true;
        }
        else
        {
            LAYER_LOG("Device extension already enabled: %s", target.c_str());
        }
    }

    // Check if user provided a VkPhysicalDeviceVulkan12Features
    auto* config2 = vku::FindStructInPNextChain<VkPhysicalDeviceVulkan12Features>(pNextBase);
    if (config2)
    {
        if (!config2->timelineSemaphore)
        {
            LAYER_LOG("Device extension force enabled: %s", target.c_str());
            config2->timelineSemaphore = true;
        }
        else
        {
            LAYER_LOG("Device extension already enabled: %s", target.c_str());
        }
    }

    // Add a config if not configured by the application
    if (!config1 && !config2)
    {
        newFeatures.timelineSemaphore = true;
        vku::AddToPnext(createInfo, newFeatures);
        LAYER_LOG("Device extension config added: %s", target.c_str());
    }
}

/* See header for documentation. */
void enableDeviceVkExtImageCompressionControl(Instance& instance,
                                              VkPhysicalDevice physicalDevice,
                                              vku::safe_VkDeviceCreateInfo& createInfo,
                                              std::vector<std::string>& supported)
{
    UNUSED(instance);
    UNUSED(physicalDevice);

    static const std::string target {VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME};

    // We know we can const-cast here because createInfo is a safe-struct clone
    void* pNextBase = const_cast<void*>(createInfo.pNext);

    VkPhysicalDeviceImageCompressionControlFeaturesEXT newFeatures = vku::InitStructHelper();

    // Test if the desired extension is supported
    if (!isIn(target, supported))
    {
        LAYER_LOG("Device extension not available: %s", target.c_str());
        return;
    }

    // Enable the extension - this will skip adding if already enabled
    if (vku::AddExtension(createInfo, target.c_str()))
    {
        LAYER_LOG("Device extension added: %s", target.c_str());
    }

    // Check if user provided a VkPhysicalDeviceImageCompressionControlFeaturesEXT
    auto* config = vku::FindStructInPNextChain<VkPhysicalDeviceImageCompressionControlFeaturesEXT>(pNextBase);
    if (config)
    {
        if (!config->imageCompressionControl)
        {
            LAYER_LOG("Device extension force enabled: %s", target.c_str());
            config->imageCompressionControl = true;
        }
        else
        {
            LAYER_LOG("Device extension already enabled: %s", target.c_str());
        }
    }

    // Add a config if not already configured by the application
    if (!config)
    {
        newFeatures.imageCompressionControl = true;
        vku::AddToPnext(createInfo, newFeatures);
        LAYER_LOG("Device extension config added: %s", target.c_str());
    }
}

/** See Vulkan API for documentation. */
template <>
PFN_vkVoidFunction layer_vkGetInstanceProcAddr<default_tag>(VkInstance instance, const char* pName)
{
    auto [isGlobal, layerFunction, hasSpecialization] = getInstanceLayerFunction(pName);

    // Global functions must be exposed and do not require the caller to pass
    // a valid instance pointer, although it is required to be nullptr in
    // Vulkan 1.2.193 or later
    if (isGlobal)
    {
        return layerFunction;
    }

    // Function is not exported because layer doesn't implement it at all
    bool exportLayerFunction { layerFunction != nullptr };

    // Function is not exported because layer doesn't specialize a user_tag version
    if constexpr(CONFIG_OPTIMIZE_DISPATCH)
    {
        if (!isFunctionAlwaysExported(pName) && !hasSpecialization)
        {
            exportLayerFunction = false;
        }
    }

    // For other functions, only expose functions that the driver exposes to
    // avoid changing queryable interface behavior seen by the application
    if (instance)
    {
        std::unique_lock<std::mutex> lock {g_vulkanLock};
        auto* layer = Instance::retrieve(instance);

        // Don't hold the lock while calling the driver
        lock.unlock();
        PFN_vkVoidFunction driverFunction = layer->nlayerGetProcAddress(instance, pName);

        // If driver exposes it and the layer has one, use the layer function
        if (driverFunction && exportLayerFunction)
        {
            return layerFunction;
        }

        // Otherwise just use the driver function, which may be nullptr
        return driverFunction;
    }

    return layerFunction;
}

/** See Vulkan API for documentation. */
template <>
PFN_vkVoidFunction layer_vkGetDeviceProcAddr<default_tag>(VkDevice device, const char* pName)
{
    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);
    lock.unlock();

    // Only expose functions that the driver exposes to avoid changing
    // queryable interface behavior seen by the application
    auto driverFunction = layer->driver.vkGetDeviceProcAddr(device, pName);
    auto [layerFunction, hasSpecialization] = getDeviceLayerFunction(pName);

    // Function is not exported because layer doesn't implement it at all
    bool exportLayerFunction { layerFunction != nullptr };

    // Function is not exported because layer doesn't specialize a user_tag version
    if constexpr(CONFIG_OPTIMIZE_DISPATCH)
    {
        if (!isFunctionAlwaysExported(pName) && !hasSpecialization)
        {
            exportLayerFunction = false;
        }
    }

    // If driver exposes it and the layer has one, use the layer function
    if (driverFunction && exportLayerFunction)
    {
        return layerFunction;
    }

    // Otherwise just use the driver function, which may be nullptr
    return driverFunction;
}

/** See Vulkan API for documentation. */
template <>
VkResult layer_vkEnumerateInstanceExtensionProperties<default_tag>(const char* pLayerName,
                                                                   uint32_t* pPropertyCount,
                                                                   VkExtensionProperties* pProperties)
{
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
template <>
VkResult layer_vkEnumerateDeviceExtensionProperties<default_tag>(VkPhysicalDevice gpu,
                                                                 const char* pLayerName,
                                                                 uint32_t* pPropertyCount,
                                                                 VkExtensionProperties* pProperties)
{
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
    assert(gpu);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Instance::retrieve(gpu);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumerateDeviceExtensionProperties(gpu, pLayerName, pPropertyCount, pProperties);
}

/** See Vulkan API for documentation. */
template <>
VkResult layer_vkEnumerateInstanceLayerProperties<default_tag>(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
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
template <>
VkResult layer_vkEnumerateDeviceLayerProperties<default_tag>(VkPhysicalDevice gpu,
                                                             uint32_t* pPropertyCount,
                                                             VkLayerProperties* pProperties)
{
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
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance<default_tag>(const VkInstanceCreateInfo* pCreateInfo,
                                                                   const VkAllocationCallbacks* pAllocator,
                                                                   VkInstance* pInstance)
{
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

    // Work out what version we should use, promoting to meet layer requirement
    APIVersion appVersion = getApplicationAPIVersion(pCreateInfo);
    APIVersion maxVersion = getInstanceAPIVersion(fpGetInstanceProcAddr);
    APIVersion reqVersion = Instance::minAPIVersion;
    APIVersion newVersion = increaseAPIVersion(appVersion, maxVersion, reqVersion);

    auto fpCreateInstanceRaw = fpGetInstanceProcAddr(nullptr, "vkCreateInstance");
    auto fpCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(fpCreateInstanceRaw);
    if (!fpCreateInstance)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Create modifiable structures we can patch
    vku::safe_VkInstanceCreateInfo newCreateInfoSafe(pCreateInfo);
    auto* newCreateInfo = reinterpret_cast<VkInstanceCreateInfo*>(&newCreateInfoSafe);

    // Patch updated application info
    newCreateInfoSafe.pApplicationInfo->apiVersion = VK_MAKE_API_VERSION(0, newVersion.first, newVersion.second, 0);

    // Enable extra extensions
    for (const auto& newExt : Instance::extraExtensions)
    {
        if (newExt == VK_EXT_DEBUG_UTILS_EXTENSION_NAME)
        {
            enableInstanceVkExtDebugUtils(newCreateInfoSafe, supportedExtensions);
        }
        else
        {
            LAYER_ERR("Unknown instance extension: %s", newExt.c_str());
        }
    }

    // Log extensions for debug purposes
    for (uint32_t i = 0; i < newCreateInfo->enabledExtensionCount; i++)
    {
        LAYER_LOG("Requested instance extension list: [%u] = %s", i, newCreateInfo->ppEnabledExtensionNames[i]);
    }

    // Get the new chain info so we modify our safe copy, not the original
    chainInfo = getChainInfo(newCreateInfo);

    // Advance the link info for the next element on the chain
    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto result = fpCreateInstance(newCreateInfo, pAllocator, pInstance);
    if (result != VK_SUCCESS)
    {
        return result;
    }

    // Retake the lock to access layer-wide global store
    auto instance = std::make_unique<Instance>(*pInstance, fpGetInstanceProcAddr);

    {
        std::lock_guard<std::mutex> lock {g_vulkanLock};
        Instance::store(*pInstance, instance);
    }

    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance<default_tag>(VkInstance instance,
                                                                const VkAllocationCallbacks* pAllocator)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};

    // Take local ownership of the Instance before calling the driver
    auto layer = Instance::destroy(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyInstance(instance, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice<default_tag>(VkPhysicalDevice physicalDevice,
                                                                 const VkDeviceCreateInfo* pCreateInfo,
                                                                 const VkAllocationCallbacks* pAllocator,
                                                                 VkDevice* pDevice)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();

    // Get the list is supported extensions
    auto supportedExtensions = getDeviceExtensionList(*layer, physicalDevice);

    // Query the supported Vulkan version
    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpGetDeviceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetDeviceProcAddr;

    // Log this for support purposes ...
    APIVersion apiVersion = getDeviceAPIVersion(*layer, physicalDevice);
    LAYER_LOG("Device API version %u.%u", apiVersion.first, apiVersion.second);

    // Create a modifiable structure we can patch
    vku::safe_VkDeviceCreateInfo newCreateInfoSafe(pCreateInfo);
    auto* newCreateInfo = reinterpret_cast<VkDeviceCreateInfo*>(&newCreateInfoSafe);

    // Apply all required patches to the VkDeviceCreateInfo
    for (const auto patch : Device::createInfoPatches)
    {
        patch(*layer, physicalDevice, newCreateInfoSafe, supportedExtensions);
    }

    // Log extensions after patching for debug purposes
    for (uint32_t i = 0; i < newCreateInfo->enabledExtensionCount; i++)
    {
        LAYER_LOG("Requested device extension list: [%u] = %s", i, newCreateInfo->ppEnabledExtensionNames[i]);
    }

    // This must be resolved here rather than via the instance tables because
    // the desktop loader sets this up on device creation, however now that
    // device-time layers are deprecated this may no longer be necessary
    auto fpCreateDeviceRaw = fpGetInstanceProcAddr(layer->instance, "vkCreateDevice");
    auto fpCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(fpCreateDeviceRaw);
    if (!fpCreateDevice)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Get the new chain info so we modify our safe copy, not the original
    chainInfo = getChainInfo(newCreateInfo);

    // Advance the link info for the next element on the chain
    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto res = fpCreateDevice(physicalDevice, newCreateInfo, pAllocator, pDevice);
    if (res != VK_SUCCESS)
    {
        return res;
    }

    auto device = std::make_unique<Device>(layer, physicalDevice, *pDevice, fpGetDeviceProcAddr, *newCreateInfo);

    // Retake the lock to access layer-wide global store
    lock.lock();
    Device::store(*pDevice, std::move(device));

    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice<default_tag>(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};

    // Take local ownership of the Device before calling the driver
    auto layer = Device::destroy(device);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDevice(device, pAllocator);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetDeviceImageMemoryRequirementsKHR<default_tag>(VkDevice device,
                                                                                    const VkDeviceImageMemoryRequirements* pInfo,
                                                                                    VkMemoryRequirements2* pMemoryRequirements)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
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
