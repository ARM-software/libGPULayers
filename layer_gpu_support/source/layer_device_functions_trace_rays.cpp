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

#include <mutex>

#include "device.hpp"
#include "layer_device_functions.hpp"

extern std::mutex g_vulkanLock;

/**
 * @brief Pre-trace-rays code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void preTraceRays(
    Device* layer,
    VkCommandBuffer commandBuffer
) {
    if (!layer->instance->config.serialize_cmdstream_trace_rays_pre())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(
        commandBuffer,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        0,
        0, nullptr,
        0, nullptr,
        0, nullptr);
}

/**
 * @brief Post-trace-rays code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void postTraceRays(
    Device* layer,
    VkCommandBuffer commandBuffer
) {
    if (!layer->instance->config.serialize_cmdstream_trace_rays_post())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(
        commandBuffer,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        0,
        0, nullptr,
        0, nullptr,
        0, nullptr);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    VkDeviceAddress indirectDeviceAddress
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preTraceRays(layer, commandBuffer);
    layer->driver.vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
    postTraceRays(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirectKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    VkDeviceAddress indirectDeviceAddress
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preTraceRays(layer, commandBuffer);
    layer->driver.vkCmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
    postTraceRays(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
    const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
    uint32_t width,
    uint32_t height,
    uint32_t depth
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preTraceRays(layer, commandBuffer);
    layer->driver.vkCmdTraceRaysKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
    postTraceRays(layer, commandBuffer);
}