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

#include "device.hpp"
#include "layer_device_functions.hpp"

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerBeginEXT<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    // Increment the render pass counter in the tracker
    cb.debugMarkerBegin(pMarkerInfo->pMarkerName);

    // Note that we do not call the driver for user labels - they are
    // emitted via the comms side-channel for each workload to avoid
    // polluting the layer's use of the driver for tag labelling
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDebugMarkerEndEXT<user_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    // Increment the render pass counter in the tracker
    cb.debugMarkerEnd();

    // Note that we do not call the driver for user labels - they are
    // emitted via the comms side-channel for each workload to avoid
    // polluting the layer's use of the driver for tag labelling
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginDebugUtilsLabelEXT<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkDebugUtilsLabelEXT* pLabelInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    // Increment the render pass counter in the tracker
    cb.debugMarkerBegin(pLabelInfo->pLabelName);

    // Note that we do not call the driver for user labels - they are
    // emitted via the comms side-channel for each workload to avoid
    // polluting the layer's use of the driver for tag labelling
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndDebugUtilsLabelEXT<user_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    // Increment the render pass counter in the tracker
    cb.debugMarkerEnd();

    // Note that we do not call the driver for user labels - they are
    // emitted via the comms side-channel for each workload to avoid
    // polluting the layer's use of the driver for tag labelling
}
