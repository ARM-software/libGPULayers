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

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAndroidSurfaceKHR(
    VkInstance instance,
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAndroidSurfaceKHR<default_tag>(
    VkInstance instance,
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface);

#endif

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugReportCallbackEXT(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT* pCallback) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugReportCallbackEXT<default_tag>(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT* pCallback);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugUtilsMessengerEXT<default_tag>(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDevice<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayModeKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    const VkDisplayModeCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDisplayModeKHR* pMode) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayModeKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    const VkDisplayModeCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDisplayModeKHR* pMode);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayPlaneSurfaceKHR(
    VkInstance instance,
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayPlaneSurfaceKHR<default_tag>(
    VkInstance instance,
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance<default_tag>(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDebugReportMessageEXT(
    VkInstance instance,
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDebugReportMessageEXT<default_tag>(
    VkInstance instance,
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugReportCallbackEXT(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugReportCallbackEXT<default_tag>(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugUtilsMessengerEXT<default_tag>(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyInstance<default_tag>(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySurfaceKHR(
    VkInstance instance,
    VkSurfaceKHR surface,
    const VkAllocationCallbacks* pAllocator) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySurfaceKHR<default_tag>(
    VkInstance instance,
    VkSurfaceKHR surface,
    const VkAllocationCallbacks* pAllocator);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceExtensionProperties(
    VkPhysicalDevice physicalDevice,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceExtensionProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceLayerProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceLayerProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceExtensionProperties(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceExtensionProperties<default_tag>(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceLayerProperties(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateInstanceLayerProperties<default_tag>(
    uint32_t* pPropertyCount,
    VkLayerProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroups(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroups<default_tag>(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroupsKHR(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroupsKHR<default_tag>(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    uint32_t* pCounterCount,
    VkPerformanceCounterKHR* pCounters,
    VkPerformanceCounterDescriptionKHR* pCounterDescriptions) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    uint32_t* pCounterCount,
    VkPerformanceCounterKHR* pCounters,
    VkPerformanceCounterDescriptionKHR* pCounterDescriptions);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDevices(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDevices<default_tag>(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModeProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModeProperties2KHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModeProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModeProperties2KHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModePropertiesKHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModePropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModePropertiesKHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilities2KHR(
    VkPhysicalDevice physicalDevice,
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR* pCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilities2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR* pCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilitiesKHR(
    VkPhysicalDevice physicalDevice,
    VkDisplayModeKHR mode,
    uint32_t planeIndex,
    VkDisplayPlaneCapabilitiesKHR* pCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilitiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkDisplayModeKHR mode,
    uint32_t planeIndex,
    VkDisplayPlaneCapabilitiesKHR* pCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneSupportedDisplaysKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t planeIndex,
    uint32_t* pDisplayCount,
    VkDisplayKHR* pDisplays) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneSupportedDisplaysKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t planeIndex,
    uint32_t* pDisplayCount,
    VkDisplayKHR* pDisplays);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetInstanceProcAddr(
    VkInstance instance,
    const char* pName) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL layer_vkGetInstanceProcAddr<default_tag>(
    VkInstance instance,
    const char* pName);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkCooperativeMatrixPropertiesKHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkCooperativeMatrixPropertiesKHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlaneProperties2KHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlaneProperties2KHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlanePropertiesKHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlanePropertiesKHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayProperties2KHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayProperties2KHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPropertiesKHR* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPropertiesKHR* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFenceProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFenceProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFencePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFencePropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphoreProperties(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphoreProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalTensorPropertiesARM(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo,
    VkExternalTensorPropertiesARM* pExternalTensorProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalTensorPropertiesARM<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo,
    VkExternalTensorPropertiesARM* pExternalTensorProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures* pFeatures) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures* pFeatures);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties* pFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties* pFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceFragmentShadingRatesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice physicalDevice,
    VkSampleCountFlagBits samples,
    VkMultisamplePropertiesEXT* pMultisampleProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMultisamplePropertiesEXT<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSampleCountFlagBits samples,
    VkMultisamplePropertiesEXT* pMultisampleProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDevicePresentRectanglesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pRectCount,
    VkRect2D* pRects) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDevicePresentRectanglesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pRectCount,
    VkRect2D* pRects);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2KHR(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
    uint32_t* pNumPasses) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
    uint32_t* pNumPasses);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkSampleCountFlagBits samples,
    VkImageUsageFlags usage,
    VkImageTiling tiling,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkSampleCountFlagBits samples,
    VkImageUsageFlags usage,
    VkImageTiling tiling,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormats2KHR(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormat2KHR* pSurfaceFormats) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormats2KHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormat2KHR* pSurfaceFormats);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormatsKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormatKHR* pSurfaceFormats) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormatsKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormatKHR* pSurfaceFormats);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfacePresentModesKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pPresentModeCount,
    VkPresentModeKHR* pPresentModes) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfacePresentModesKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pPresentModeCount,
    VkPresentModeKHR* pPresentModes);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceSupportKHR(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    VkSurfaceKHR surface,
    VkBool32* pSupported) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceSupportKHR<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    VkSurfaceKHR surface,
    VkBool32* pSupported);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolProperties<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolPropertiesEXT(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolPropertiesEXT<default_tag>(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseDisplayEXT(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseDisplayEXT<default_tag>(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display);

/* See Vulkan API for documentation. */
/* Delete the generic match-all */
template <typename T>
VKAPI_ATTR void VKAPI_CALL layer_vkSubmitDebugUtilsMessageEXT(
    VkInstance instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData) = delete;

/* Default common code implementation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkSubmitDebugUtilsMessageEXT<default_tag>(
    VkInstance instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

// clang-format on
