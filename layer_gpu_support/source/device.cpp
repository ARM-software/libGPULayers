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

#include <vulkan/utility/vk_struct_helper.hpp>

#include "device.hpp"
#include "framework/manual_functions.hpp"
#include "framework/utils.hpp"
#include "instance.hpp"

/**
 * @brief The dispatch lookup for all of the created Vulkan instances.
 */
static std::unordered_map<void*, std::unique_ptr<Device>> g_devices;

/* Predeclare custom DeviceCreatePatch functions */
static void modifyDeviceRobustBufferAccess(Instance& instance,
                                           VkPhysicalDevice physicalDevice,
                                           vku::safe_VkDeviceCreateInfo& createInfo,
                                           std::vector<std::string>& supported);

/* See header for documentation. */
const std::vector<DeviceCreatePatchPtr> Device::createInfoPatches {
    enableDeviceVkKhrTimelineSemaphore,
    enableDeviceVkExtImageCompressionControl,
    modifyDeviceRobustBufferAccess
};

/* See header for documentation. */
void Device::store(VkDevice handle, std::unique_ptr<Device> device)
{
    void* key = getDispatchKey(handle);
    g_devices.insert({key, std::move(device)});
}

/* See header for documentation. */
Device* Device::retrieve(VkDevice handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
Device* Device::retrieve(VkQueue handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
Device* Device::retrieve(VkCommandBuffer handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
void Device::destroy(Device* device)
{
    g_devices.erase(getDispatchKey(device));
}

/* See header for documentation. */
Device::Device(Instance* _instance,
               VkPhysicalDevice _physicalDevice,
               VkDevice _device,
               PFN_vkGetDeviceProcAddr nlayerGetProcAddress,
               const VkDeviceCreateInfo& createInfo)
    : instance(_instance),
      physicalDevice(_physicalDevice),
      device(_device)
{
    UNUSED(createInfo);

    initDriverDeviceDispatchTable(device, nlayerGetProcAddress, driver);

    VkSemaphoreTypeCreateInfo timelineCreateInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .pNext = nullptr,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initialValue = queueSerializationTimelineSemCount,
    };

    VkSemaphoreCreateInfo semCreateInfo {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &timelineCreateInfo,
        .flags = 0,
    };

    auto result = driver.vkCreateSemaphore(device, &semCreateInfo, nullptr, &queueSerializationTimelineSem);
    if (result != VK_SUCCESS)
    {
        LAYER_ERR("Failed vkCreateSemaphore() for queue serialization");
        queueSerializationTimelineSem = nullptr;
    }
}

/**
 * Allow a force enable/disable of robustBufferAccess feature.
 *
 * @param instance         The layer instance we are running within.
 * @param physicalDevice   The physical device we are creating a device for.
 * @param createInfo       The createInfo we can search to find user config.
 * @param supported        The list of supported extensions.
 */
static void modifyDeviceRobustBufferAccess(Instance& instance,
                                           VkPhysicalDevice physicalDevice,
                                           vku::safe_VkDeviceCreateInfo& createInfo,
                                           std::vector<std::string>& supported)
{
    UNUSED(supported);

    // Only one of these can be set as an override
    // If neither are set then don't change the app settings
    bool enableRobustness = instance.config.feature_enable_robustBufferAccess();
    bool disableRobustness = instance.config.feature_disable_robustBufferAccess();

    // No patch to apply
    if (!enableRobustness && !disableRobustness)
    {
        return;
    }

    // Query if robustness is supported if we need to force enable
    VkPhysicalDeviceFeatures supportedFeatures;
    instance.driver.vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);
    if (enableRobustness && !supportedFeatures.robustBufferAccess)
    {
        LAYER_LOG("Device feature not available: robustBufferAccess");
        return;
    }

    // We know we can const_cast here because createInfo is a safe-struct clone
    // Option1 = legacy-style enable
    auto* config = const_cast<VkPhysicalDeviceFeatures*>(createInfo.pEnabledFeatures);

    // Option2 = modern-style enable
    void* pNextBase = const_cast<void*>(createInfo.pNext);
    auto* configNext = vku::FindStructInPNextChain<VkPhysicalDeviceFeatures2>(pNextBase);

    // Pick the feature struct from either of the valid options
    if (!config && configNext)
    {
        config = &configNext->features;
    }

    // User provided feature enable struct, so just change that directly
    if (config)
    {
        if (enableRobustness)
        {
            if(config->robustBufferAccess)
            {
                LAYER_LOG("Device feature already enabled: robustBufferAccess");
            }
            else
            {
                LAYER_LOG("Device feature enabled: robustBufferAccess");
                config->robustBufferAccess = VK_TRUE;
            }
        }
        if (disableRobustness)
        {
            if(!config->robustBufferAccess)
            {
                LAYER_LOG("Device feature already disabled: robustBufferAccess");
            }

            LAYER_LOG("Device feature disabled: robustBufferAccess");
            config->robustBufferAccess = VK_FALSE;
        }
    }
    // User provided no feature enables, so provide our own structure
    else if (enableRobustness)
    {
        LAYER_LOG("Device feature enabled: robustBufferAccess");

        // Create a dynamic copy and transfer ownership to the safe-struct
        auto* newFeatures = new VkPhysicalDeviceFeatures;
        memset(newFeatures, 0, sizeof(VkPhysicalDeviceFeatures));
        createInfo.pEnabledFeatures = newFeatures;
    }
    // User provided no feature enables, but we don't need one
    else if (disableRobustness)
    {
        LAYER_LOG("Device feature already disabled: robustBufferAccess");
    }
}
