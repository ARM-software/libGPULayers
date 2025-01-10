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
 * Map persisting render pass suspend state from dynamic begin to end.
 * Shared access, so must only access with vulkanLock held.
 */
static std::unordered_map<VkCommandBuffer, bool> dynamic_suspend_state;

/**
 * @brief Pre-render-pass code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void preRenderPass(
    Device* layer,
    VkCommandBuffer commandBuffer
) {
    if (!layer->instance->config.serialize_cmdstream_render_pass_pre())
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
 * @brief Post-render-pass code injection point.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
static void postRenderPass(
    Device* layer,
    VkCommandBuffer commandBuffer
) {
    if (!layer->instance->config.serialize_cmdstream_render_pass_post())
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
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    VkSubpassContents contents
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preRenderPass(layer, commandBuffer);
    layer->driver.vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preRenderPass(layer, commandBuffer);
    layer->driver.vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderPassBeginInfo* pRenderPassBegin,
    const VkSubpassBeginInfo* pSubpassBeginInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    preRenderPass(layer, commandBuffer);
    layer->driver.vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    bool resuming = pRenderingInfo->flags & VK_RENDERING_RESUMING_BIT;
    bool suspending = pRenderingInfo->flags & VK_RENDERING_SUSPENDING_BIT;
    dynamic_suspend_state[commandBuffer] = suspending;

    // Release the lock to call into the driver
    lock.unlock();

    // Only modify synchronization for the first part of the render pass
    if (!resuming)
    {
        preRenderPass(layer, commandBuffer);
    }
    layer->driver.vkCmdBeginRendering(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    const VkRenderingInfo* pRenderingInfo
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    bool resuming = pRenderingInfo->flags & VK_RENDERING_RESUMING_BIT_KHR;
    bool suspending = pRenderingInfo->flags & VK_RENDERING_SUSPENDING_BIT_KHR;
    dynamic_suspend_state[commandBuffer] = suspending;

    // Release the lock to call into the driver
    lock.unlock();

    // Only modify synchronization for the first part of the render pass
    if (!resuming)
    {
        preRenderPass(layer, commandBuffer);
    }
    layer->driver.vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<user_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    layer->driver.vkCmdEndRenderPass(commandBuffer);
    postRenderPass(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL  layer_vkCmdEndRendering<user_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Retrieve the begin rendering suspend state
    bool suspending = dynamic_suspend_state[commandBuffer];
    dynamic_suspend_state.erase(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    layer->driver.vkCmdEndRendering(commandBuffer);

    // Only modify synchronization for the last part of the render pass
    if (!suspending)
    {
        postRenderPass(layer, commandBuffer);
    }
}

/* See Vulkan API for documentation. */
template <>
VKAPI_ATTR void VKAPI_CALL  layer_vkCmdEndRenderingKHR<user_tag>(
    VkCommandBuffer commandBuffer
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Retrieve the begin rendering suspend state
    bool suspending = dynamic_suspend_state[commandBuffer];
    dynamic_suspend_state.erase(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();

    layer->driver.vkCmdEndRenderingKHR(commandBuffer);

    // Only modify synchronization for the last part of the render pass
    if (suspending)
    {
        postRenderPass(layer, commandBuffer);
    }
}
