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
#include <vulkan/utility/vk_safe_struct.hpp>
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
PFN_vkVoidFunction getInstanceLayerFunction(const char* name)
{
    for (auto& function : instanceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    return nullptr;
}

/* See header for documentation. */
PFN_vkVoidFunction getDeviceLayerFunction(const char* name)
{
    for (auto& function : deviceIntercepts)
    {
        if (!strcmp(function.name, name))
        {
            return function.function;
        }
    }

    return nullptr;
}

/* See header for documentation. */
APIVersion getInstanceAPIVersion(PFN_vkGetInstanceProcAddr fpGetProcAddr)
{
    // TODO: This will crash in Khronos validation if we try to use this
    // with the validation layer beneath us due to Android loader v0 protocol.
#if 0
    return { 1, 3 };
#endif

    auto fpFunctionRaw = fpGetProcAddr(nullptr, "vkEnumerateInstanceVersion");
    auto fpFunction = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(fpFunctionRaw);
    if (!fpFunction)
    {
        LAYER_ERR("Failed to get vkEnumerateInstanceVersion()");
        return {0, 0};
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
APIVersion getDeviceAPIVersion(PFN_vkGetInstanceProcAddr fpGetProcAddr,
                               VkInstance instance,
                               VkPhysicalDevice physicalDevice)
{
    auto fpFunctionRaw = fpGetProcAddr(instance, "vkGetPhysicalDeviceProperties");
    auto fpFunction = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(fpFunctionRaw);
    if (!fpFunction)
    {
        LAYER_ERR("Failed to get vkGetPhysicalDeviceProperties()");
        return {0, 0};
    }

    VkPhysicalDeviceProperties properties {};
    fpFunction(physicalDevice, &properties);

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
std::vector<std::string> getDeviceExtensionList(VkInstance instance,
                                                VkPhysicalDevice physicalDevice,
                                                const VkDeviceCreateInfo* pCreateInfo)
{
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
std::vector<const char*> cloneExtensionList(uint32_t extensionCount, const char* const* extensionList)
{
    std::vector<const char*> data;
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
 * @param supported   The list of supported extension, or empty if unknown.
 * @param active      The list of active extensions.
 */
static void enableInstanceVkExtDebugUtils(const std::vector<std::string>& supported, std::vector<const char*>& active)
{
    static const std::string target {VK_EXT_DEBUG_UTILS_EXTENSION_NAME};

    // Test if the desired extension is supported. If supported list is
    // empty then we didn't query and assume extension is supported.
    if (supported.size() && !isIn(target, supported))
    {
        LAYER_ERR("Instance extension not available: %s", target.c_str());
        return;
    }

    // If it is already enabled then do nothing
    if (isIn(target, active))
    {
        LAYER_LOG("Instance extension already enabled: %s", target.c_str());
        return;
    }

    // Else add it to the list of enable extensions
    LAYER_LOG("Instance extension added: %s", target.c_str());
    active.push_back(target.c_str());
}

/**
 * Enable VK_KHR_timeline_semaphore if not enabled.
 *
 * Enabling this requires passing the extension string to vkCreateDevice(),
 * and passing either VkPhysicalDeviceTimelineSemaphoreFeatures or
 * VkPhysicalDeviceVulkan12Features with the feature enabled.
 *
 * If the user has the extension enabled but the feature disabled we patch
 * their existing structures to enable it.
 *
 * @param createInfo    The createInfo we can search to find user config.
 * @param supported     The list of supported extensions.
 * @param newFeatures   Pre-allocated struct we can use if we need to add it.
 */
static void enableDeviceVkKhrTimelineSemaphore(vku::safe_VkDeviceCreateInfo& createInfo,
                                               std::vector<std::string>& supported,
                                               VkPhysicalDeviceTimelineSemaphoreFeatures& newFeatures)
{
    static const std::string target {VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME};

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
    auto* config1 = searchNextList<VkPhysicalDeviceTimelineSemaphoreFeatures>(
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES,
        createInfo.pNext);

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
    auto* config2 = searchNextList<VkPhysicalDeviceVulkan12Features>(
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        createInfo.pNext);

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

/**
 * Enable VK_EXT_image_compression_control if not enabled.
 *
 * Enabling this requires passing the extension string to vkCreateDevice(),
 * and passing VkPhysicalDeviceImageCompressionControlFeaturesEXT.
 *
 * If the user has the extension enabled but the feature disabled we patch
 * their existing structures to enable it.
 *
 * @param createInfo    The createInfo we can search to find user config.
 * @param supported     The list of supported extensions.
 * @param newFeatures   Pre-allocated struct we can use if we need to add it.
 */
static void enableDeviceVkExtImageCompressionControl(vku::safe_VkDeviceCreateInfo& createInfo,
                                                     std::vector<std::string>& supported,
                                                     VkPhysicalDeviceImageCompressionControlFeaturesEXT& newFeatures)
{
    static const std::string target {VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME};

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
    auto* config = searchNextList<VkPhysicalDeviceImageCompressionControlFeaturesEXT>(
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_COMPRESSION_CONTROL_FEATURES_EXT,
        createInfo.pNext);

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
PFN_vkVoidFunction layer_vkGetInstanceProcAddr_default(VkInstance instance, const char* pName)
{
    // Only expose functions that the driver exposes to avoid changing
    // queryable interface behavior seen by the application
    auto layerFunction = getInstanceLayerFunction(pName);
    if (instance)
    {
        std::unique_lock<std::mutex> lock {g_vulkanLock};
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
PFN_vkVoidFunction layer_vkGetDeviceProcAddr_default(VkDevice device, const char* pName)
{
    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
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
VkResult layer_vkEnumerateInstanceExtensionProperties_default(const char* pLayerName,
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
VkResult layer_vkEnumerateDeviceExtensionProperties_default(VkPhysicalDevice gpu,
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
VkResult layer_vkEnumerateInstanceLayerProperties_default(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
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
VkResult layer_vkEnumerateDeviceLayerProperties_default(VkPhysicalDevice gpu,
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
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance_default(const VkInstanceCreateInfo* pCreateInfo,
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

    // Create structure copies we can modify
    VkInstanceCreateInfo newCreateInfo = *pCreateInfo;
    VkApplicationInfo newAppInfo = *pCreateInfo->pApplicationInfo;

    // Write the new application info
    newAppInfo.apiVersion = VK_MAKE_API_VERSION(0, newVersion.first, newVersion.second, 0);
    newCreateInfo.pApplicationInfo = &newAppInfo;

    // Create a copy of the extension list we can patch
    std::vector<const char*> newExtensions;
    const auto start = pCreateInfo->ppEnabledExtensionNames;
    const auto end = pCreateInfo->ppEnabledExtensionNames + pCreateInfo->enabledExtensionCount;
    newExtensions.insert(newExtensions.end(), start, end);

    // Enable extra extensions
    for (const auto& newExt : Instance::extraExtensions)
    {
        if (newExt == VK_EXT_DEBUG_UTILS_EXTENSION_NAME)
        {
            enableInstanceVkExtDebugUtils(supportedExtensions, newExtensions);
        }
        else
        {
            LAYER_ERR("Unknown instance extension: %s", newExt.c_str());
        }
    }

    // Patch extension pointer and size after extending it
    newCreateInfo.enabledExtensionCount = newExtensions.size();
    newCreateInfo.ppEnabledExtensionNames = newExtensions.data();

    // Log it for debug purposes
    unsigned int i = 0;
    for (auto ext : newExtensions)
    {
        LAYER_LOG("Requested instance extension list: [%u] = %s", i, ext);
        i++;
    }

    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto result = fpCreateInstance(&newCreateInfo, pAllocator, pInstance);
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
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance_default(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Instance::retrieve(instance);

    // Layer proxy must be destroyed before the driver version
    // so we can clean up any layer-owned resources
    Instance::destroy(layer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyInstance(instance, pAllocator);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice_default(VkPhysicalDevice physicalDevice,
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
    auto supportedExtensions = getDeviceExtensionList(layer->instance, physicalDevice, pCreateInfo);

    // Query the supported Vulkan version
    auto* chainInfo = getChainInfo(pCreateInfo);
    auto fpGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpGetDeviceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetDeviceProcAddr;

    // Log this for support purposes ...
    APIVersion apiVersion = getDeviceAPIVersion(fpGetInstanceProcAddr, layer->instance, physicalDevice);
    LAYER_LOG("Device API version %u.%u", apiVersion.first, apiVersion.second);

    // Create a modifiable structure we can patch
    vku::safe_VkDeviceCreateInfo newCreateInfoSafe(pCreateInfo);
    auto* newCreateInfo = reinterpret_cast<VkDeviceCreateInfo*>(&newCreateInfoSafe);

    // Create structures we allocate here, but populate elsewhere
    VkPhysicalDeviceTimelineSemaphoreFeatures newTimelineFeatures = vku::InitStructHelper();
    VkPhysicalDeviceImageCompressionControlFeaturesEXT newCompressionControlFeatures = vku::InitStructHelper();

    // Enable extra extensions
    for (const auto& newExt : Device::extraExtensions)
    {
        if (newExt == VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME)
        {

            enableDeviceVkKhrTimelineSemaphore(newCreateInfoSafe,
                                               supportedExtensions,
                                               newTimelineFeatures);
        }
        else if (newExt == VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME)
        {
            enableDeviceVkExtImageCompressionControl(newCreateInfoSafe,
                                                     supportedExtensions,
                                                     newCompressionControlFeatures);
        }
        else
        {
            LAYER_ERR("Unknown instance extension: %s", newExt.c_str());
        }
    }

    // Log extensions for debug purposes
    for (uint32_t i = 0; i < newCreateInfo->enabledExtensionCount; i++)
    {
        LAYER_LOG("Requested device extension list: [%u] = %s", i, newCreateInfo->ppEnabledExtensionNames[i]);
    }

    auto fpCreateDeviceRaw = fpGetInstanceProcAddr(layer->instance, "vkCreateDevice");
    auto fpCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(fpCreateDeviceRaw);
    if (!fpCreateDevice)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

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
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDevice_default(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Layer proxy must be destroyed before the driver version
    // so we can clean up any layer-owned resources
    Device::destroy(layer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDevice(device, pAllocator);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL
    layer_vkGetDeviceImageMemoryRequirementsKHR_default(VkDevice device,
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
