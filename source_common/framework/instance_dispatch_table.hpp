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

#include "framework/instance_functions.hpp"
#include "framework/utils.hpp"
#include "utils/misc.hpp"

#if __has_include ("layer_instance_functions.hpp")
    #include "layer_instance_functions.hpp"
#endif

/**
 * @brief Interception table lookup entry.
 */
struct InstanceInterceptTableEntry
{
    /**
     * @brief The function entrypoint name.
     */
    const char* name;

    /**
     * @brief The layer function pointer.
     */
    PFN_vkVoidFunction function;
};

#define ENTRY(fnc) { STR(fnc), reinterpret_cast<PFN_vkVoidFunction>(layer_##fnc<user_tag>) }

/**
 * @brief The instance dispatch table used to call the driver.
 */
static const struct InstanceInterceptTableEntry instanceIntercepts[] = {
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
   ENTRY(vkCreateAndroidSurfaceKHR),
#endif
   ENTRY(vkCreateDebugReportCallbackEXT),
   ENTRY(vkCreateDebugUtilsMessengerEXT),
   ENTRY(vkCreateDevice),
   ENTRY(vkCreateDisplayModeKHR),
   ENTRY(vkCreateDisplayPlaneSurfaceKHR),
   ENTRY(vkCreateInstance),
   ENTRY(vkDebugReportMessageEXT),
   ENTRY(vkDestroyDebugReportCallbackEXT),
   ENTRY(vkDestroyDebugUtilsMessengerEXT),
   ENTRY(vkDestroyInstance),
   ENTRY(vkDestroySurfaceKHR),
   ENTRY(vkEnumeratePhysicalDeviceGroups),
   ENTRY(vkEnumeratePhysicalDeviceGroupsKHR),
   ENTRY(vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR),
   ENTRY(vkEnumeratePhysicalDevices),
   ENTRY(vkGetDisplayModeProperties2KHR),
   ENTRY(vkGetDisplayModePropertiesKHR),
   ENTRY(vkGetDisplayPlaneCapabilities2KHR),
   ENTRY(vkGetDisplayPlaneCapabilitiesKHR),
   ENTRY(vkGetDisplayPlaneSupportedDisplaysKHR),
   ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT),
   ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsKHR),
   ENTRY(vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR),
   ENTRY(vkGetPhysicalDeviceDisplayPlaneProperties2KHR),
   ENTRY(vkGetPhysicalDeviceDisplayPlanePropertiesKHR),
   ENTRY(vkGetPhysicalDeviceDisplayProperties2KHR),
   ENTRY(vkGetPhysicalDeviceDisplayPropertiesKHR),
   ENTRY(vkGetPhysicalDeviceExternalBufferProperties),
   ENTRY(vkGetPhysicalDeviceExternalBufferPropertiesKHR),
   ENTRY(vkGetPhysicalDeviceExternalFenceProperties),
   ENTRY(vkGetPhysicalDeviceExternalFencePropertiesKHR),
   ENTRY(vkGetPhysicalDeviceExternalSemaphoreProperties),
   ENTRY(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR),
   ENTRY(vkGetPhysicalDeviceFeatures),
   ENTRY(vkGetPhysicalDeviceFeatures2),
   ENTRY(vkGetPhysicalDeviceFeatures2KHR),
   ENTRY(vkGetPhysicalDeviceFormatProperties),
   ENTRY(vkGetPhysicalDeviceFormatProperties2),
   ENTRY(vkGetPhysicalDeviceFormatProperties2KHR),
   ENTRY(vkGetPhysicalDeviceFragmentShadingRatesKHR),
   ENTRY(vkGetPhysicalDeviceImageFormatProperties),
   ENTRY(vkGetPhysicalDeviceImageFormatProperties2),
   ENTRY(vkGetPhysicalDeviceImageFormatProperties2KHR),
   ENTRY(vkGetPhysicalDeviceMemoryProperties),
   ENTRY(vkGetPhysicalDeviceMemoryProperties2),
   ENTRY(vkGetPhysicalDeviceMemoryProperties2KHR),
   ENTRY(vkGetPhysicalDeviceMultisamplePropertiesEXT),
   ENTRY(vkGetPhysicalDevicePresentRectanglesKHR),
   ENTRY(vkGetPhysicalDeviceProperties),
   ENTRY(vkGetPhysicalDeviceProperties2),
   ENTRY(vkGetPhysicalDeviceProperties2KHR),
   ENTRY(vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR),
   ENTRY(vkGetPhysicalDeviceQueueFamilyProperties),
   ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2),
   ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2KHR),
   ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties),
   ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2),
   ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2KHR),
   ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2EXT),
   ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2KHR),
   ENTRY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR),
   ENTRY(vkGetPhysicalDeviceSurfaceFormats2KHR),
   ENTRY(vkGetPhysicalDeviceSurfaceFormatsKHR),
   ENTRY(vkGetPhysicalDeviceSurfacePresentModesKHR),
   ENTRY(vkGetPhysicalDeviceSurfaceSupportKHR),
   ENTRY(vkGetPhysicalDeviceToolProperties),
   ENTRY(vkGetPhysicalDeviceToolPropertiesEXT),
   ENTRY(vkReleaseDisplayEXT),
   ENTRY(vkSubmitDebugUtilsMessageEXT),
};

#undef ENTRY

/**
 * @brief The instance dispatch table used to call the driver.
 */
struct InstanceDispatchTable {
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif
    PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
    PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
    PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
    PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
    PFN_vkDestroyInstance vkDestroyInstance;
    PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
    PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
    PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
    PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR;
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
    PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
    PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
    PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR;
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;
    PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
    PFN_vkGetPhysicalDeviceFeatures2KHR vkGetPhysicalDeviceFeatures2KHR;
    PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
    PFN_vkGetPhysicalDeviceFormatProperties2KHR vkGetPhysicalDeviceFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
    PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR vkGetPhysicalDeviceImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR vkGetPhysicalDeviceMemoryProperties2KHR;
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
    PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
    PFN_vkGetPhysicalDeviceProperties2KHR vkGetPhysicalDeviceProperties2KHR;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR vkGetPhysicalDeviceQueueFamilyProperties2KHR;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties;
    PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
    PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
    PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
};

#define ENTRY(fnc) table.fnc = (PFN_##fnc)getProcAddr(instance, STR(fnc))

/**
 * @brief Initialize the instance dispatch table with driver function pointers.
 *
 * @param instance      The instance handle.
 * @param getProcAddr   The function getter for the driver/next layer down.
 * @param table         The table to populate.
 */
static inline void initDriverInstanceDispatchTable(
    VkInstance instance,
    PFN_vkGetInstanceProcAddr getProcAddr,
    InstanceDispatchTable& table
) {
    table.vkGetInstanceProcAddr = getProcAddr;

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    ENTRY(vkCreateAndroidSurfaceKHR);
#endif
    ENTRY(vkCreateDebugReportCallbackEXT);
    ENTRY(vkCreateDebugUtilsMessengerEXT);
    ENTRY(vkCreateDisplayModeKHR);
    ENTRY(vkCreateDisplayPlaneSurfaceKHR);
    ENTRY(vkDebugReportMessageEXT);
    ENTRY(vkDestroyDebugReportCallbackEXT);
    ENTRY(vkDestroyDebugUtilsMessengerEXT);
    ENTRY(vkDestroyInstance);
    ENTRY(vkDestroySurfaceKHR);
    ENTRY(vkEnumerateDeviceExtensionProperties);
    ENTRY(vkEnumeratePhysicalDeviceGroups);
    ENTRY(vkEnumeratePhysicalDeviceGroupsKHR);
    ENTRY(vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    ENTRY(vkEnumeratePhysicalDevices);
    ENTRY(vkGetDisplayModeProperties2KHR);
    ENTRY(vkGetDisplayModePropertiesKHR);
    ENTRY(vkGetDisplayPlaneCapabilities2KHR);
    ENTRY(vkGetDisplayPlaneCapabilitiesKHR);
    ENTRY(vkGetDisplayPlaneSupportedDisplaysKHR);
    ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT);
    ENTRY(vkGetPhysicalDeviceCalibrateableTimeDomainsKHR);
    ENTRY(vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceDisplayPlaneProperties2KHR);
    ENTRY(vkGetPhysicalDeviceDisplayPlanePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceDisplayProperties2KHR);
    ENTRY(vkGetPhysicalDeviceDisplayPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalBufferProperties);
    ENTRY(vkGetPhysicalDeviceExternalBufferPropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalFenceProperties);
    ENTRY(vkGetPhysicalDeviceExternalFencePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceExternalSemaphoreProperties);
    ENTRY(vkGetPhysicalDeviceExternalSemaphorePropertiesKHR);
    ENTRY(vkGetPhysicalDeviceFeatures);
    ENTRY(vkGetPhysicalDeviceFeatures2);
    ENTRY(vkGetPhysicalDeviceFeatures2KHR);
    ENTRY(vkGetPhysicalDeviceFormatProperties);
    ENTRY(vkGetPhysicalDeviceFormatProperties2);
    ENTRY(vkGetPhysicalDeviceFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceFragmentShadingRatesKHR);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties2);
    ENTRY(vkGetPhysicalDeviceImageFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceMemoryProperties);
    ENTRY(vkGetPhysicalDeviceMemoryProperties2);
    ENTRY(vkGetPhysicalDeviceMemoryProperties2KHR);
    ENTRY(vkGetPhysicalDeviceMultisamplePropertiesEXT);
    ENTRY(vkGetPhysicalDevicePresentRectanglesKHR);
    ENTRY(vkGetPhysicalDeviceProperties);
    ENTRY(vkGetPhysicalDeviceProperties2);
    ENTRY(vkGetPhysicalDeviceProperties2KHR);
    ENTRY(vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2);
    ENTRY(vkGetPhysicalDeviceQueueFamilyProperties2KHR);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2);
    ENTRY(vkGetPhysicalDeviceSparseImageFormatProperties2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2EXT);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilities2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
    ENTRY(vkGetPhysicalDeviceSurfaceFormats2KHR);
    ENTRY(vkGetPhysicalDeviceSurfaceFormatsKHR);
    ENTRY(vkGetPhysicalDeviceSurfacePresentModesKHR);
    ENTRY(vkGetPhysicalDeviceSurfaceSupportKHR);
    ENTRY(vkGetPhysicalDeviceToolProperties);
    ENTRY(vkGetPhysicalDeviceToolPropertiesEXT);
    ENTRY(vkReleaseDisplayEXT);
    ENTRY(vkSubmitDebugUtilsMessageEXT);
}

#undef ENTRY
