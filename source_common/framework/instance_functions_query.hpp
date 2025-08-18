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

#pragma once

// clang-format off

#include <vulkan/vulkan.h>

#if defined(VK_USE_PLATFORM_ANDROID_KHR)

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateAndroidSurfaceKHR = requires(
    VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface
) {
    layer_vkCreateAndroidSurfaceKHR<T>(instance, pCreateInfo, pAllocator, pSurface);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateAndroidSurfaceKHR getLayerPtr_vkCreateAndroidSurfaceKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateAndroidSurfaceKHR<T>)
        {
            return layer_vkCreateAndroidSurfaceKHR<T>;
        }

        return layer_vkCreateAndroidSurfaceKHR<default_tag>;
    }.operator()<user_tag>();
}

#endif

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDebugReportCallbackEXT = requires(
    VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback
) {
    layer_vkCreateDebugReportCallbackEXT<T>(instance, pCreateInfo, pAllocator, pCallback);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDebugReportCallbackEXT getLayerPtr_vkCreateDebugReportCallbackEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDebugReportCallbackEXT<T>)
        {
            return layer_vkCreateDebugReportCallbackEXT<T>;
        }

        return layer_vkCreateDebugReportCallbackEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDebugUtilsMessengerEXT = requires(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger
) {
    layer_vkCreateDebugUtilsMessengerEXT<T>(instance, pCreateInfo, pAllocator, pMessenger);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDebugUtilsMessengerEXT getLayerPtr_vkCreateDebugUtilsMessengerEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDebugUtilsMessengerEXT<T>)
        {
            return layer_vkCreateDebugUtilsMessengerEXT<T>;
        }

        return layer_vkCreateDebugUtilsMessengerEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDevice = requires(
    VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice
) {
    layer_vkCreateDevice<T>(physicalDevice, pCreateInfo, pAllocator, pDevice);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDevice getLayerPtr_vkCreateDevice()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDevice<T>)
        {
            return layer_vkCreateDevice<T>;
        }

        return layer_vkCreateDevice<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDisplayModeKHR = requires(
    VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode
) {
    layer_vkCreateDisplayModeKHR<T>(physicalDevice, display, pCreateInfo, pAllocator, pMode);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDisplayModeKHR getLayerPtr_vkCreateDisplayModeKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDisplayModeKHR<T>)
        {
            return layer_vkCreateDisplayModeKHR<T>;
        }

        return layer_vkCreateDisplayModeKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateDisplayPlaneSurfaceKHR = requires(
    VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface
) {
    layer_vkCreateDisplayPlaneSurfaceKHR<T>(instance, pCreateInfo, pAllocator, pSurface);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateDisplayPlaneSurfaceKHR getLayerPtr_vkCreateDisplayPlaneSurfaceKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateDisplayPlaneSurfaceKHR<T>)
        {
            return layer_vkCreateDisplayPlaneSurfaceKHR<T>;
        }

        return layer_vkCreateDisplayPlaneSurfaceKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkCreateInstance = requires(
    const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance
) {
    layer_vkCreateInstance<T>(pCreateInfo, pAllocator, pInstance);
};

/* Function pointer resolution. */
constexpr PFN_vkCreateInstance getLayerPtr_vkCreateInstance()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkCreateInstance<T>)
        {
            return layer_vkCreateInstance<T>;
        }

        return layer_vkCreateInstance<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDebugReportMessageEXT = requires(
    VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage
) {
    layer_vkDebugReportMessageEXT<T>(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
};

/* Function pointer resolution. */
constexpr PFN_vkDebugReportMessageEXT getLayerPtr_vkDebugReportMessageEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDebugReportMessageEXT<T>)
        {
            return layer_vkDebugReportMessageEXT<T>;
        }

        return layer_vkDebugReportMessageEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDebugReportCallbackEXT = requires(
    VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDebugReportCallbackEXT<T>(instance, callback, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDebugReportCallbackEXT getLayerPtr_vkDestroyDebugReportCallbackEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDebugReportCallbackEXT<T>)
        {
            return layer_vkDestroyDebugReportCallbackEXT<T>;
        }

        return layer_vkDestroyDebugReportCallbackEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyDebugUtilsMessengerEXT = requires(
    VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDebugUtilsMessengerEXT<T>(instance, messenger, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyDebugUtilsMessengerEXT getLayerPtr_vkDestroyDebugUtilsMessengerEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyDebugUtilsMessengerEXT<T>)
        {
            return layer_vkDestroyDebugUtilsMessengerEXT<T>;
        }

        return layer_vkDestroyDebugUtilsMessengerEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroyInstance = requires(
    VkInstance instance, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyInstance<T>(instance, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroyInstance getLayerPtr_vkDestroyInstance()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroyInstance<T>)
        {
            return layer_vkDestroyInstance<T>;
        }

        return layer_vkDestroyInstance<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkDestroySurfaceKHR = requires(
    VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySurfaceKHR<T>(instance, surface, pAllocator);
};

/* Function pointer resolution. */
constexpr PFN_vkDestroySurfaceKHR getLayerPtr_vkDestroySurfaceKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkDestroySurfaceKHR<T>)
        {
            return layer_vkDestroySurfaceKHR<T>;
        }

        return layer_vkDestroySurfaceKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumerateDeviceExtensionProperties = requires(
    VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties
) {
    layer_vkEnumerateDeviceExtensionProperties<T>(physicalDevice, pLayerName, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumerateDeviceExtensionProperties getLayerPtr_vkEnumerateDeviceExtensionProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumerateDeviceExtensionProperties<T>)
        {
            return layer_vkEnumerateDeviceExtensionProperties<T>;
        }

        return layer_vkEnumerateDeviceExtensionProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumerateDeviceLayerProperties = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties
) {
    layer_vkEnumerateDeviceLayerProperties<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumerateDeviceLayerProperties getLayerPtr_vkEnumerateDeviceLayerProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumerateDeviceLayerProperties<T>)
        {
            return layer_vkEnumerateDeviceLayerProperties<T>;
        }

        return layer_vkEnumerateDeviceLayerProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumerateInstanceExtensionProperties = requires(
    const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties
) {
    layer_vkEnumerateInstanceExtensionProperties<T>(pLayerName, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumerateInstanceExtensionProperties getLayerPtr_vkEnumerateInstanceExtensionProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumerateInstanceExtensionProperties<T>)
        {
            return layer_vkEnumerateInstanceExtensionProperties<T>;
        }

        return layer_vkEnumerateInstanceExtensionProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumerateInstanceLayerProperties = requires(
    uint32_t* pPropertyCount, VkLayerProperties* pProperties
) {
    layer_vkEnumerateInstanceLayerProperties<T>(pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumerateInstanceLayerProperties getLayerPtr_vkEnumerateInstanceLayerProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumerateInstanceLayerProperties<T>)
        {
            return layer_vkEnumerateInstanceLayerProperties<T>;
        }

        return layer_vkEnumerateInstanceLayerProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumeratePhysicalDeviceGroups = requires(
    VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    layer_vkEnumeratePhysicalDeviceGroups<T>(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumeratePhysicalDeviceGroups getLayerPtr_vkEnumeratePhysicalDeviceGroups()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumeratePhysicalDeviceGroups<T>)
        {
            return layer_vkEnumeratePhysicalDeviceGroups<T>;
        }

        return layer_vkEnumeratePhysicalDeviceGroups<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumeratePhysicalDeviceGroupsKHR = requires(
    VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    layer_vkEnumeratePhysicalDeviceGroupsKHR<T>(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumeratePhysicalDeviceGroupsKHR getLayerPtr_vkEnumeratePhysicalDeviceGroupsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumeratePhysicalDeviceGroupsKHR<T>)
        {
            return layer_vkEnumeratePhysicalDeviceGroupsKHR<T>;
        }

        return layer_vkEnumeratePhysicalDeviceGroupsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterKHR* pCounters, VkPerformanceCounterDescriptionKHR* pCounterDescriptions
) {
    layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR<T>(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR getLayerPtr_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR<T>)
        {
            return layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR<T>;
        }

        return layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkEnumeratePhysicalDevices = requires(
    VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices
) {
    layer_vkEnumeratePhysicalDevices<T>(instance, pPhysicalDeviceCount, pPhysicalDevices);
};

/* Function pointer resolution. */
constexpr PFN_vkEnumeratePhysicalDevices getLayerPtr_vkEnumeratePhysicalDevices()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkEnumeratePhysicalDevices<T>)
        {
            return layer_vkEnumeratePhysicalDevices<T>;
        }

        return layer_vkEnumeratePhysicalDevices<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDisplayModeProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties
) {
    layer_vkGetDisplayModeProperties2KHR<T>(physicalDevice, display, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDisplayModeProperties2KHR getLayerPtr_vkGetDisplayModeProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDisplayModeProperties2KHR<T>)
        {
            return layer_vkGetDisplayModeProperties2KHR<T>;
        }

        return layer_vkGetDisplayModeProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDisplayModePropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties
) {
    layer_vkGetDisplayModePropertiesKHR<T>(physicalDevice, display, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDisplayModePropertiesKHR getLayerPtr_vkGetDisplayModePropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDisplayModePropertiesKHR<T>)
        {
            return layer_vkGetDisplayModePropertiesKHR<T>;
        }

        return layer_vkGetDisplayModePropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDisplayPlaneCapabilities2KHR = requires(
    VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities
) {
    layer_vkGetDisplayPlaneCapabilities2KHR<T>(physicalDevice, pDisplayPlaneInfo, pCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDisplayPlaneCapabilities2KHR getLayerPtr_vkGetDisplayPlaneCapabilities2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDisplayPlaneCapabilities2KHR<T>)
        {
            return layer_vkGetDisplayPlaneCapabilities2KHR<T>;
        }

        return layer_vkGetDisplayPlaneCapabilities2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDisplayPlaneCapabilitiesKHR = requires(
    VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities
) {
    layer_vkGetDisplayPlaneCapabilitiesKHR<T>(physicalDevice, mode, planeIndex, pCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDisplayPlaneCapabilitiesKHR getLayerPtr_vkGetDisplayPlaneCapabilitiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDisplayPlaneCapabilitiesKHR<T>)
        {
            return layer_vkGetDisplayPlaneCapabilitiesKHR<T>;
        }

        return layer_vkGetDisplayPlaneCapabilitiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetDisplayPlaneSupportedDisplaysKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays
) {
    layer_vkGetDisplayPlaneSupportedDisplaysKHR<T>(physicalDevice, planeIndex, pDisplayCount, pDisplays);
};

/* Function pointer resolution. */
constexpr PFN_vkGetDisplayPlaneSupportedDisplaysKHR getLayerPtr_vkGetDisplayPlaneSupportedDisplaysKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetDisplayPlaneSupportedDisplaysKHR<T>)
        {
            return layer_vkGetDisplayPlaneSupportedDisplaysKHR<T>;
        }

        return layer_vkGetDisplayPlaneSupportedDisplaysKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetInstanceProcAddr = requires(
    VkInstance instance, const char* pName
) {
    layer_vkGetInstanceProcAddr<T>(instance, pName);
};

/* Function pointer resolution. */
constexpr PFN_vkGetInstanceProcAddr getLayerPtr_vkGetInstanceProcAddr()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetInstanceProcAddr<T>)
        {
            return layer_vkGetInstanceProcAddr<T>;
        }

        return layer_vkGetInstanceProcAddr<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains
) {
    layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT<T>(physicalDevice, pTimeDomainCount, pTimeDomains);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT getLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT<T>)
        {
            return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT<T>;
        }

        return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains
) {
    layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR<T>(physicalDevice, pTimeDomainCount, pTimeDomains);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR getLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR<T>)
        {
            return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR<T>;
        }

        return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesKHR* pProperties
) {
    layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR getLayerPtr_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties
) {
    layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR getLayerPtr_vkGetPhysicalDeviceDisplayPlaneProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceDisplayPlaneProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties
) {
    layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR getLayerPtr_vkGetPhysicalDeviceDisplayPlanePropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceDisplayPlanePropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceDisplayProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties
) {
    layer_vkGetPhysicalDeviceDisplayProperties2KHR<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceDisplayProperties2KHR getLayerPtr_vkGetPhysicalDeviceDisplayProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceDisplayProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceDisplayProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceDisplayProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceDisplayPropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties
) {
    layer_vkGetPhysicalDeviceDisplayPropertiesKHR<T>(physicalDevice, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceDisplayPropertiesKHR getLayerPtr_vkGetPhysicalDeviceDisplayPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceDisplayPropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceDisplayPropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceDisplayPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalBufferProperties = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties
) {
    layer_vkGetPhysicalDeviceExternalBufferProperties<T>(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalBufferProperties getLayerPtr_vkGetPhysicalDeviceExternalBufferProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalBufferProperties<T>)
        {
            return layer_vkGetPhysicalDeviceExternalBufferProperties<T>;
        }

        return layer_vkGetPhysicalDeviceExternalBufferProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalBufferPropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties
) {
    layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR<T>(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR getLayerPtr_vkGetPhysicalDeviceExternalBufferPropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalBufferPropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalFenceProperties = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties
) {
    layer_vkGetPhysicalDeviceExternalFenceProperties<T>(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalFenceProperties getLayerPtr_vkGetPhysicalDeviceExternalFenceProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalFenceProperties<T>)
        {
            return layer_vkGetPhysicalDeviceExternalFenceProperties<T>;
        }

        return layer_vkGetPhysicalDeviceExternalFenceProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalFencePropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties
) {
    layer_vkGetPhysicalDeviceExternalFencePropertiesKHR<T>(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR getLayerPtr_vkGetPhysicalDeviceExternalFencePropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalFencePropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceExternalFencePropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceExternalFencePropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalSemaphoreProperties = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    layer_vkGetPhysicalDeviceExternalSemaphoreProperties<T>(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalSemaphoreProperties getLayerPtr_vkGetPhysicalDeviceExternalSemaphoreProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalSemaphoreProperties<T>)
        {
            return layer_vkGetPhysicalDeviceExternalSemaphoreProperties<T>;
        }

        return layer_vkGetPhysicalDeviceExternalSemaphoreProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR<T>(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR getLayerPtr_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceExternalTensorPropertiesARM = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo, VkExternalTensorPropertiesARM* pExternalTensorProperties
) {
    layer_vkGetPhysicalDeviceExternalTensorPropertiesARM<T>(physicalDevice, pExternalTensorInfo, pExternalTensorProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceExternalTensorPropertiesARM getLayerPtr_vkGetPhysicalDeviceExternalTensorPropertiesARM()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceExternalTensorPropertiesARM<T>)
        {
            return layer_vkGetPhysicalDeviceExternalTensorPropertiesARM<T>;
        }

        return layer_vkGetPhysicalDeviceExternalTensorPropertiesARM<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFeatures = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures<T>(physicalDevice, pFeatures);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFeatures getLayerPtr_vkGetPhysicalDeviceFeatures()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFeatures<T>)
        {
            return layer_vkGetPhysicalDeviceFeatures<T>;
        }

        return layer_vkGetPhysicalDeviceFeatures<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFeatures2 = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures2<T>(physicalDevice, pFeatures);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFeatures2 getLayerPtr_vkGetPhysicalDeviceFeatures2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFeatures2<T>)
        {
            return layer_vkGetPhysicalDeviceFeatures2<T>;
        }

        return layer_vkGetPhysicalDeviceFeatures2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFeatures2KHR = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures2KHR<T>(physicalDevice, pFeatures);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFeatures2KHR getLayerPtr_vkGetPhysicalDeviceFeatures2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFeatures2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceFeatures2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceFeatures2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFormatProperties = requires(
    VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties<T>(physicalDevice, format, pFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFormatProperties getLayerPtr_vkGetPhysicalDeviceFormatProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFormatProperties<T>)
        {
            return layer_vkGetPhysicalDeviceFormatProperties<T>;
        }

        return layer_vkGetPhysicalDeviceFormatProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFormatProperties2 = requires(
    VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties2<T>(physicalDevice, format, pFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFormatProperties2 getLayerPtr_vkGetPhysicalDeviceFormatProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFormatProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceFormatProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceFormatProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFormatProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties2KHR<T>(physicalDevice, format, pFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFormatProperties2KHR getLayerPtr_vkGetPhysicalDeviceFormatProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFormatProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceFormatProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceFormatProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceFragmentShadingRatesKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates
) {
    layer_vkGetPhysicalDeviceFragmentShadingRatesKHR<T>(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR getLayerPtr_vkGetPhysicalDeviceFragmentShadingRatesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceFragmentShadingRatesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceFragmentShadingRatesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceFragmentShadingRatesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties = requires(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties
) {
    layer_vkGetPhysicalDeviceImageFormatProperties<T>(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceImageFormatProperties getLayerPtr_vkGetPhysicalDeviceImageFormatProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties<T>)
        {
            return layer_vkGetPhysicalDeviceImageFormatProperties<T>;
        }

        return layer_vkGetPhysicalDeviceImageFormatProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties2 = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties
) {
    layer_vkGetPhysicalDeviceImageFormatProperties2<T>(physicalDevice, pImageFormatInfo, pImageFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceImageFormatProperties2 getLayerPtr_vkGetPhysicalDeviceImageFormatProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceImageFormatProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceImageFormatProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties
) {
    layer_vkGetPhysicalDeviceImageFormatProperties2KHR<T>(physicalDevice, pImageFormatInfo, pImageFormatProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceImageFormatProperties2KHR getLayerPtr_vkGetPhysicalDeviceImageFormatProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceImageFormatProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceImageFormatProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceImageFormatProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceMemoryProperties = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties<T>(physicalDevice, pMemoryProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceMemoryProperties getLayerPtr_vkGetPhysicalDeviceMemoryProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceMemoryProperties<T>)
        {
            return layer_vkGetPhysicalDeviceMemoryProperties<T>;
        }

        return layer_vkGetPhysicalDeviceMemoryProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceMemoryProperties2 = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties2<T>(physicalDevice, pMemoryProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceMemoryProperties2 getLayerPtr_vkGetPhysicalDeviceMemoryProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceMemoryProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceMemoryProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceMemoryProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceMemoryProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties2KHR<T>(physicalDevice, pMemoryProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceMemoryProperties2KHR getLayerPtr_vkGetPhysicalDeviceMemoryProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceMemoryProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceMemoryProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceMemoryProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceMultisamplePropertiesEXT = requires(
    VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties
) {
    layer_vkGetPhysicalDeviceMultisamplePropertiesEXT<T>(physicalDevice, samples, pMultisampleProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT getLayerPtr_vkGetPhysicalDeviceMultisamplePropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceMultisamplePropertiesEXT<T>)
        {
            return layer_vkGetPhysicalDeviceMultisamplePropertiesEXT<T>;
        }

        return layer_vkGetPhysicalDeviceMultisamplePropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDevicePresentRectanglesKHR = requires(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects
) {
    layer_vkGetPhysicalDevicePresentRectanglesKHR<T>(physicalDevice, surface, pRectCount, pRects);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDevicePresentRectanglesKHR getLayerPtr_vkGetPhysicalDevicePresentRectanglesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDevicePresentRectanglesKHR<T>)
        {
            return layer_vkGetPhysicalDevicePresentRectanglesKHR<T>;
        }

        return layer_vkGetPhysicalDevicePresentRectanglesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceProperties = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties
) {
    layer_vkGetPhysicalDeviceProperties<T>(physicalDevice, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceProperties getLayerPtr_vkGetPhysicalDeviceProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceProperties<T>)
        {
            return layer_vkGetPhysicalDeviceProperties<T>;
        }

        return layer_vkGetPhysicalDeviceProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceProperties2 = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceProperties2<T>(physicalDevice, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceProperties2 getLayerPtr_vkGetPhysicalDeviceProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceProperties2KHR<T>(physicalDevice, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceProperties2KHR getLayerPtr_vkGetPhysicalDeviceProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = requires(
    VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses
) {
    layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR<T>(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR getLayerPtr_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties<T>(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceQueueFamilyProperties getLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties<T>)
        {
            return layer_vkGetPhysicalDeviceQueueFamilyProperties<T>;
        }

        return layer_vkGetPhysicalDeviceQueueFamilyProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2 = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties2<T>(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceQueueFamilyProperties2 getLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceQueueFamilyProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceQueueFamilyProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR<T>(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR getLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceQueueFamilyProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties = requires(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties<T>(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSparseImageFormatProperties getLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties<T>)
        {
            return layer_vkGetPhysicalDeviceSparseImageFormatProperties<T>;
        }

        return layer_vkGetPhysicalDeviceSparseImageFormatProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2 = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties2<T>(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 getLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2<T>)
        {
            return layer_vkGetPhysicalDeviceSparseImageFormatProperties2<T>;
        }

        return layer_vkGetPhysicalDeviceSparseImageFormatProperties2<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR<T>(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR getLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSparseImageFormatProperties2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2EXT = requires(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities
) {
    layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT<T>(physicalDevice, surface, pSurfaceCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT getLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2EXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2EXT<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2KHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities
) {
    layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR<T>(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR getLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilities2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = requires(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities
) {
    layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR<T>(physicalDevice, surface, pSurfaceCapabilities);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR getLayerPtr_vkGetPhysicalDeviceSurfaceCapabilitiesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceCapabilitiesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceFormats2KHR = requires(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats
) {
    layer_vkGetPhysicalDeviceSurfaceFormats2KHR<T>(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceFormats2KHR getLayerPtr_vkGetPhysicalDeviceSurfaceFormats2KHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceFormats2KHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceFormats2KHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceFormats2KHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceFormatsKHR = requires(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats
) {
    layer_vkGetPhysicalDeviceSurfaceFormatsKHR<T>(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceFormatsKHR getLayerPtr_vkGetPhysicalDeviceSurfaceFormatsKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceFormatsKHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceFormatsKHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceFormatsKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfacePresentModesKHR = requires(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes
) {
    layer_vkGetPhysicalDeviceSurfacePresentModesKHR<T>(physicalDevice, surface, pPresentModeCount, pPresentModes);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfacePresentModesKHR getLayerPtr_vkGetPhysicalDeviceSurfacePresentModesKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfacePresentModesKHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfacePresentModesKHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfacePresentModesKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceSurfaceSupportKHR = requires(
    VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported
) {
    layer_vkGetPhysicalDeviceSurfaceSupportKHR<T>(physicalDevice, queueFamilyIndex, surface, pSupported);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceSurfaceSupportKHR getLayerPtr_vkGetPhysicalDeviceSurfaceSupportKHR()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceSurfaceSupportKHR<T>)
        {
            return layer_vkGetPhysicalDeviceSurfaceSupportKHR<T>;
        }

        return layer_vkGetPhysicalDeviceSurfaceSupportKHR<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceToolProperties = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties
) {
    layer_vkGetPhysicalDeviceToolProperties<T>(physicalDevice, pToolCount, pToolProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceToolProperties getLayerPtr_vkGetPhysicalDeviceToolProperties()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceToolProperties<T>)
        {
            return layer_vkGetPhysicalDeviceToolProperties<T>;
        }

        return layer_vkGetPhysicalDeviceToolProperties<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkGetPhysicalDeviceToolPropertiesEXT = requires(
    VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties
) {
    layer_vkGetPhysicalDeviceToolPropertiesEXT<T>(physicalDevice, pToolCount, pToolProperties);
};

/* Function pointer resolution. */
constexpr PFN_vkGetPhysicalDeviceToolPropertiesEXT getLayerPtr_vkGetPhysicalDeviceToolPropertiesEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkGetPhysicalDeviceToolPropertiesEXT<T>)
        {
            return layer_vkGetPhysicalDeviceToolPropertiesEXT<T>;
        }

        return layer_vkGetPhysicalDeviceToolPropertiesEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkReleaseDisplayEXT = requires(
    VkPhysicalDevice physicalDevice, VkDisplayKHR display
) {
    layer_vkReleaseDisplayEXT<T>(physicalDevice, display);
};

/* Function pointer resolution. */
constexpr PFN_vkReleaseDisplayEXT getLayerPtr_vkReleaseDisplayEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkReleaseDisplayEXT<T>)
        {
            return layer_vkReleaseDisplayEXT<T>;
        }

        return layer_vkReleaseDisplayEXT<default_tag>;
    }.operator()<user_tag>();
}

/* Test for user_tag availability. */
template <typename T>
concept hasLayerPtr_vkSubmitDebugUtilsMessageEXT = requires(
    VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
) {
    layer_vkSubmitDebugUtilsMessageEXT<T>(instance, messageSeverity, messageTypes, pCallbackData);
};

/* Function pointer resolution. */
constexpr PFN_vkSubmitDebugUtilsMessageEXT getLayerPtr_vkSubmitDebugUtilsMessageEXT()
{
    return [] <typename T>
    {
        if constexpr(hasLayerPtr_vkSubmitDebugUtilsMessageEXT<T>)
        {
            return layer_vkSubmitDebugUtilsMessageEXT<T>;
        }

        return layer_vkSubmitDebugUtilsMessageEXT<default_tag>;
    }.operator()<user_tag>();
}

// clang-format on
