/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited
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
 * This module implements device property query functions.
 */

#pragma once

#include <vulkan/vulkan.h>

#include "utils/misc.hpp"

/**
 * Test if VK_KHR_timeline_semaphore (or equivalent core feature) is enabled.
 *
 * @param createInfo   The device creation configuration.
 *
 * @return @c true if enabled, @c false otherwise.
 */
bool isEnabledVkKhrTimelineSemaphore(
    const VkDeviceCreateInfo& createInfo
) {
    // Check Vulkan 1.2 core feature first
    auto* coreFeature = searchNextList<VkPhysicalDeviceVulkan12Features>(
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
        createInfo.pNext);
    if (coreFeature)
    {
        return coreFeature->timelineSemaphore;
    }

    // Check the extension second
    bool extEnabled = isInExtensionList(
      VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME,
      createInfo.enabledExtensionCount,
      createInfo.ppEnabledExtensionNames);
    if (!extEnabled)
    {
        return false;
    }

    auto* extFeature = searchNextList<VkPhysicalDeviceTimelineSemaphoreFeatures>(
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES,
        createInfo.pNext);
    if (extFeature)
    {
        return extFeature->timelineSemaphore;
    }

    return false;
}
