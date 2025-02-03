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

#include "device.hpp"
#include "framework/device_dispatch_table.hpp"

#include <mutex>

extern std::mutex g_vulkanLock;

/**
 * @brief Pre-dispatch code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void preDispatch(Device* layer, VkCommandBuffer commandBuffer)
{
    if (!layer->instance->config.serialize_cmdstream_compute_dispatch_pre())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(commandBuffer,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       0,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr);
}

/**
 * @brief Post-dispatch code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void postDispatch(Device* layer, VkCommandBuffer commandBuffer)
{
    if (!layer->instance->config.serialize_cmdstream_compute_dispatch_post())
    {
        return;
    }

    // Execution dependency
    layer->driver.vkCmdPipelineBarrier(commandBuffer,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                                       0,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr,
                                       0,
                                       nullptr);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatch<user_tag>(VkCommandBuffer commandBuffer,
                                                         uint32_t groupCountX,
                                                         uint32_t groupCountY,
                                                         uint32_t groupCountZ)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preDispatch(layer, commandBuffer);
    layer->driver.vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
    postDispatch(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBase<user_tag>(VkCommandBuffer commandBuffer,
                                                             uint32_t baseGroupX,
                                                             uint32_t baseGroupY,
                                                             uint32_t baseGroupZ,
                                                             uint32_t groupCountX,
                                                             uint32_t groupCountY,
                                                             uint32_t groupCountZ)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preDispatch(layer, commandBuffer);
    layer->driver
        .vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    postDispatch(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchBaseKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                uint32_t baseGroupX,
                                                                uint32_t baseGroupY,
                                                                uint32_t baseGroupZ,
                                                                uint32_t groupCountX,
                                                                uint32_t groupCountY,
                                                                uint32_t groupCountZ)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preDispatch(layer, commandBuffer);
    layer->driver
        .vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    postDispatch(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdDispatchIndirect<user_tag>(VkCommandBuffer commandBuffer,
                                                                 VkBuffer buffer,
                                                                 VkDeviceSize offset)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preDispatch(layer, commandBuffer);
    layer->driver.vkCmdDispatchIndirect(commandBuffer, buffer, offset);
    postDispatch(layer, commandBuffer);
}
