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

#pragma once

#include <vulkan/vulkan.h>

#if defined(VK_USE_PLATFORM_ANDROID_KHR)

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAndroidSurfaceKHR_default(
    VkInstance instance,
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAndroidSurfaceKHR(
    VkInstance instance,
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface
) {
    return layer_vkCreateAndroidSurfaceKHR_default(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugReportCallbackEXT_default(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT* pCallback);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugReportCallbackEXT(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT* pCallback
) {
    return layer_vkCreateDebugReportCallbackEXT_default(instance, pCreateInfo, pAllocator, pCallback);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugUtilsMessengerEXT_default(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger
) {
    return layer_vkCreateDebugUtilsMessengerEXT_default(instance, pCreateInfo, pAllocator, pMessenger);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice_default(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice
) {
    return layer_vkCreateDevice_default(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayModeKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    const VkDisplayModeCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDisplayModeKHR* pMode);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayModeKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    const VkDisplayModeCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDisplayModeKHR* pMode
) {
    return layer_vkCreateDisplayModeKHR_default(physicalDevice, display, pCreateInfo, pAllocator, pMode);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayPlaneSurfaceKHR_default(
    VkInstance instance,
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayPlaneSurfaceKHR(
    VkInstance instance,
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface
) {
    return layer_vkCreateDisplayPlaneSurfaceKHR_default(instance, pCreateInfo, pAllocator, pSurface);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance_default(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance
) {
    return layer_vkCreateInstance_default(pCreateInfo, pAllocator, pInstance);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDebugReportMessageEXT_default(
    VkInstance instance,
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDebugReportMessageEXT(
    VkInstance instance,
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage
) {
    layer_vkDebugReportMessageEXT_default(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugReportCallbackEXT_default(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugReportCallbackEXT(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDebugReportCallbackEXT_default(instance, callback, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugUtilsMessengerEXT_default(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyDebugUtilsMessengerEXT_default(instance, messenger, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance_default(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroyInstance_default(instance, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySurfaceKHR_default(
    VkInstance instance,
    VkSurfaceKHR surface,
    const VkAllocationCallbacks* pAllocator);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySurfaceKHR(
    VkInstance instance,
    VkSurfaceKHR surface,
    const VkAllocationCallbacks* pAllocator
) {
    layer_vkDestroySurfaceKHR_default(instance, surface, pAllocator);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroups_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroups(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    return layer_vkEnumeratePhysicalDeviceGroups_default(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroupsKHR_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroupsKHR(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    return layer_vkEnumeratePhysicalDeviceGroupsKHR_default(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    uint32_t* pCounterCount,
    VkPerformanceCounterKHR* pCounters,
    VkPerformanceCounterDescriptionKHR* pCounterDescriptions);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    uint32_t* pCounterCount,
    VkPerformanceCounterKHR* pCounters,
    VkPerformanceCounterDescriptionKHR* pCounterDescriptions
) {
    return layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR_default(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDevices_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDevices(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices
) {
    return layer_vkEnumeratePhysicalDevices_default(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModeProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModeProperties2KHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModeProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModeProperties2KHR* pProperties
) {
    return layer_vkGetDisplayModeProperties2KHR_default(physicalDevice, display, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModePropertiesKHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModePropertiesKHR* pProperties
) {
    return layer_vkGetDisplayModePropertiesKHR_default(physicalDevice, display, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilities2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR* pCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilities2KHR(
    VkPhysicalDevice physicalDevice,
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR* pCapabilities
) {
    return layer_vkGetDisplayPlaneCapabilities2KHR_default(physicalDevice, pDisplayPlaneInfo, pCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilitiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayModeKHR mode,
    uint32_t planeIndex,
    VkDisplayPlaneCapabilitiesKHR* pCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilitiesKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayModeKHR mode,
    uint32_t planeIndex,
    VkDisplayPlaneCapabilitiesKHR* pCapabilities
) {
    return layer_vkGetDisplayPlaneCapabilitiesKHR_default(physicalDevice, mode, planeIndex, pCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneSupportedDisplaysKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t planeIndex,
    uint32_t* pDisplayCount,
    VkDisplayKHR* pDisplays);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneSupportedDisplaysKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t planeIndex,
    uint32_t* pDisplayCount,
    VkDisplayKHR* pDisplays
) {
    return layer_vkGetDisplayPlaneSupportedDisplaysKHR_default(physicalDevice, planeIndex, pDisplayCount, pDisplays);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains
) {
    return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT_default(physicalDevice, pTimeDomainCount, pTimeDomains);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains
) {
    return layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR_default(physicalDevice, pTimeDomainCount, pTimeDomains);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkCooperativeMatrixPropertiesKHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkCooperativeMatrixPropertiesKHR* pProperties
) {
    return layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR_default(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlaneProperties2KHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlaneProperties2KHR* pProperties
) {
    return layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR_default(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlanePropertiesKHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlanePropertiesKHR* pProperties
) {
    return layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR_default(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayProperties2KHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayProperties2KHR* pProperties
) {
    return layer_vkGetPhysicalDeviceDisplayProperties2KHR_default(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPropertiesKHR* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPropertiesKHR* pProperties
) {
    return layer_vkGetPhysicalDeviceDisplayPropertiesKHR_default(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties
) {
    layer_vkGetPhysicalDeviceExternalBufferProperties_default(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties
) {
    layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR_default(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFenceProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFenceProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties
) {
    layer_vkGetPhysicalDeviceExternalFenceProperties_default(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFencePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFencePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties
) {
    layer_vkGetPhysicalDeviceExternalFencePropertiesKHR_default(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphoreProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphoreProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    layer_vkGetPhysicalDeviceExternalSemaphoreProperties_default(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR_default(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures* pFeatures);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures_default(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures2_default(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    layer_vkGetPhysicalDeviceFeatures2KHR_default(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties* pFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties_default(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties2_default(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties
) {
    layer_vkGetPhysicalDeviceFormatProperties2KHR_default(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceFragmentShadingRatesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates
) {
    return layer_vkGetPhysicalDeviceFragmentShadingRatesKHR_default(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties
) {
    return layer_vkGetPhysicalDeviceImageFormatProperties_default(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    return layer_vkGetPhysicalDeviceImageFormatProperties2_default(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    return layer_vkGetPhysicalDeviceImageFormatProperties2KHR_default(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties_default(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties2_default(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    layer_vkGetPhysicalDeviceMemoryProperties2KHR_default(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMultisamplePropertiesEXT_default(
    VkPhysicalDevice physicalDevice,
    VkSampleCountFlagBits samples,
    VkMultisamplePropertiesEXT* pMultisampleProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice physicalDevice,
    VkSampleCountFlagBits samples,
    VkMultisamplePropertiesEXT* pMultisampleProperties
) {
    layer_vkGetPhysicalDeviceMultisamplePropertiesEXT_default(physicalDevice, samples, pMultisampleProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDevicePresentRectanglesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pRectCount,
    VkRect2D* pRects);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDevicePresentRectanglesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pRectCount,
    VkRect2D* pRects
) {
    return layer_vkGetPhysicalDevicePresentRectanglesKHR_default(physicalDevice, surface, pRectCount, pRects);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties
) {
    layer_vkGetPhysicalDeviceProperties_default(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceProperties2_default(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceProperties2KHR_default(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
    uint32_t* pNumPasses);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
    uint32_t* pNumPasses
) {
    layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR_default(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties_default(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties2_default(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR_default(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkSampleCountFlagBits samples,
    VkImageUsageFlags usage,
    VkImageTiling tiling,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkSampleCountFlagBits samples,
    VkImageUsageFlags usage,
    VkImageTiling tiling,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties_default(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties2_default(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties
) {
    layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR_default(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities
) {
    return layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT_default(physicalDevice, surface, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities
) {
    return layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR_default(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities
) {
    return layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR_default(physicalDevice, surface, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormats2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormat2KHR* pSurfaceFormats);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormats2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormat2KHR* pSurfaceFormats
) {
    return layer_vkGetPhysicalDeviceSurfaceFormats2KHR_default(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormatsKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormatKHR* pSurfaceFormats);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormatsKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormatKHR* pSurfaceFormats
) {
    return layer_vkGetPhysicalDeviceSurfaceFormatsKHR_default(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfacePresentModesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pPresentModeCount,
    VkPresentModeKHR* pPresentModes);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfacePresentModesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pPresentModeCount,
    VkPresentModeKHR* pPresentModes
) {
    return layer_vkGetPhysicalDeviceSurfacePresentModesKHR_default(physicalDevice, surface, pPresentModeCount, pPresentModes);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceSupportKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    VkSurfaceKHR surface,
    VkBool32* pSupported);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceSupportKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    VkSurfaceKHR surface,
    VkBool32* pSupported
) {
    return layer_vkGetPhysicalDeviceSurfaceSupportKHR_default(physicalDevice, queueFamilyIndex, surface, pSupported);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolProperties_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties
) {
    return layer_vkGetPhysicalDeviceToolProperties_default(physicalDevice, pToolCount, pToolProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolPropertiesEXT_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolPropertiesEXT(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties
) {
    return layer_vkGetPhysicalDeviceToolPropertiesEXT_default(physicalDevice, pToolCount, pToolProperties);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseDisplayEXT_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseDisplayEXT(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display
) {
    return layer_vkReleaseDisplayEXT_default(physicalDevice, display);
}

/* See Vulkan API for documentation. */
/* Default common code pass-through implementation. */
VKAPI_ATTR void VKAPI_CALL layer_vkSubmitDebugUtilsMessageEXT_default(
    VkInstance instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

/* Match-all template to use default implementation. */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSubmitDebugUtilsMessageEXT(
    VkInstance instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
) {
    layer_vkSubmitDebugUtilsMessageEXT_default(instance, messageSeverity, messageTypes, pCallbackData);
}

