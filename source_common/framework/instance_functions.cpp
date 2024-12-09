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

#include <memory>
#include <mutex>
#include <thread>

// Include from per-layer code
#include "device.hpp"
#include "instance.hpp"

// Include from common code
#include "framework/instance_functions_manual.hpp"
#include "framework/instance_functions.hpp"
#include "framework/utils.hpp"

extern std::mutex g_vulkanLock;

#if defined(VK_USE_PLATFORM_ANDROID_KHR)

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateAndroidSurfaceKHR_default(
    VkInstance instance,
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

#endif

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugReportCallbackEXT_default(
    VkInstance instance,
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugReportCallbackEXT* pCallback
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDebugUtilsMessengerEXT_default(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pMessenger
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
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

    auto* chainInfo = getChainInfo(pCreateInfo, VK_LAYER_LINK_INFO);
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
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayModeKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    const VkDisplayModeCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDisplayModeKHR* pMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateDisplayPlaneSurfaceKHR_default(
    VkInstance instance,
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkSurfaceKHR* pSurface
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateInstance_default(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance
) {
    LAYER_TRACE(__func__);

    auto* chainInfo = getChainInfo(pCreateInfo, VK_LAYER_LINK_INFO);

    auto fpGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
    auto fpCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(fpGetInstanceProcAddr(nullptr, "vkCreateInstance"));
    if (!fpCreateInstance)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    auto res = fpCreateInstance(pCreateInfo, pAllocator, pInstance);
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
VKAPI_ATTR void VKAPI_CALL layer_vkDebugReportMessageEXT_default(
    VkInstance instance,
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugReportCallbackEXT_default(
    VkInstance instance,
    VkDebugReportCallbackEXT callback,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyDebugUtilsMessengerEXT_default(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
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
VKAPI_ATTR void VKAPI_CALL layer_vkDestroySurfaceKHR_default(
    VkInstance instance,
    VkSurfaceKHR surface,
    const VkAllocationCallbacks* pAllocator
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroySurfaceKHR(instance, surface, pAllocator);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumerateDeviceExtensionProperties_default(
    VkPhysicalDevice physicalDevice,
    const char* pLayerName,
    uint32_t* pPropertyCount,
    VkExtensionProperties* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroups_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceGroupsKHR_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    uint32_t* pCounterCount,
    VkPerformanceCounterKHR* pCounters,
    VkPerformanceCounterDescriptionKHR* pCounterDescriptions
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkEnumeratePhysicalDevices_default(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModeProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModeProperties2KHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDisplayModeProperties2KHR(physicalDevice, display, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayModePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display,
    uint32_t* pPropertyCount,
    VkDisplayModePropertiesKHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilities2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR* pCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDisplayPlaneCapabilities2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneCapabilitiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayModeKHR mode,
    uint32_t planeIndex,
    VkDisplayPlaneCapabilitiesKHR* pCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetDisplayPlaneSupportedDisplaysKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t planeIndex,
    uint32_t* pDisplayCount,
    VkDisplayKHR* pDisplays
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice, pTimeDomainCount, pTimeDomains);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pTimeDomainCount,
    VkTimeDomainKHR* pTimeDomains
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceCalibrateableTimeDomainsKHR(physicalDevice, pTimeDomainCount, pTimeDomains);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkCooperativeMatrixPropertiesKHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlaneProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlaneProperties2KHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPlanePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPlanePropertiesKHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayProperties2KHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceDisplayPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pPropertyCount,
    VkDisplayPropertiesKHR* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalBufferPropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFenceProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalFencePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphoreProperties_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures* pFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFeatures2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceFeatures2* pFeatures
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties* pFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkFormatProperties2* pFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceFragmentShadingRatesKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkImageTiling tiling,
    VkImageUsageFlags usage,
    VkImageCreateFlags flags,
    VkImageFormatProperties* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceImageFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
    VkImageFormatProperties2* pImageFormatProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties* pMemoryProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMemoryProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceMultisamplePropertiesEXT_default(
    VkPhysicalDevice physicalDevice,
    VkSampleCountFlagBits samples,
    VkMultisamplePropertiesEXT* pMultisampleProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDevicePresentRectanglesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pRectCount,
    VkRect2D* pRects
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR_default(
    VkPhysicalDevice physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,
    uint32_t* pNumPasses
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceQueueFamilyProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties_default(
    VkPhysicalDevice physicalDevice,
    VkFormat format,
    VkImageType type,
    VkSampleCountFlagBits samples,
    VkImageUsageFlags usage,
    VkImageTiling tiling,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkGetPhysicalDeviceSparseImageFormatProperties2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t* pPropertyCount,
    VkSparseImageFormatProperties2* pProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2EXT_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilities2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceCapabilitiesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormats2KHR_default(
    VkPhysicalDevice physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormat2KHR* pSurfaceFormats
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceFormatsKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pSurfaceFormatCount,
    VkSurfaceFormatKHR* pSurfaceFormats
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfacePresentModesKHR_default(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t* pPresentModeCount,
    VkPresentModeKHR* pPresentModes
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceSurfaceSupportKHR_default(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex,
    VkSurfaceKHR surface,
    VkBool32* pSupported
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolProperties_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceToolProperties(physicalDevice, pToolCount, pToolProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPhysicalDeviceToolPropertiesEXT_default(
    VkPhysicalDevice physicalDevice,
    uint32_t* pToolCount,
    VkPhysicalDeviceToolProperties* pToolProperties
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR VkResult VKAPI_CALL layer_vkReleaseDisplayEXT_default(
    VkPhysicalDevice physicalDevice,
    VkDisplayKHR display
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(physicalDevice);

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkReleaseDisplayEXT(physicalDevice, display);
}

/* See Vulkan API for documentation. */
VKAPI_ATTR void VKAPI_CALL layer_vkSubmitDebugUtilsMessageEXT_default(
    VkInstance instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Instance::retrieve(instance);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
}

