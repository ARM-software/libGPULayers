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

#include "device.hpp"
#include "device_utils.hpp"
#include "framework/device_dispatch_table.hpp"

#include <mutex>

extern std::mutex g_vulkanLock;

/**
 * @brief Register a compute dispatch with the tracker.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param groupX          The X size of the dispatch in groups.
 * @param groupY          The Y size of the dispatch in groups.
 * @param groupZ          The Z size of the dispatch in groups.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerDispatch(Device* layer,
                                 VkCommandBuffer commandBuffer,
                                 int64_t groupX,
                                 int64_t groupY,
                                 int64_t groupZ)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.dispatch(groupX, groupY, groupZ);
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

    uint64_t tagID = registerDispatch(layer,
                                      commandBuffer,
                                      static_cast<int64_t>(groupCountX),
                                      static_cast<int64_t>(groupCountY),
                                      static_cast<int64_t>(groupCountZ));

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
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

    uint64_t tagID = registerDispatch(layer,
                                      commandBuffer,
                                      static_cast<int64_t>(groupCountX),
                                      static_cast<int64_t>(groupCountY),
                                      static_cast<int64_t>(groupCountZ));

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver
        .vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
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

    uint64_t tagID = registerDispatch(layer,
                                      commandBuffer,
                                      static_cast<int64_t>(groupCountX),
                                      static_cast<int64_t>(groupCountY),
                                      static_cast<int64_t>(groupCountZ));

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver
        .vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
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

    uint64_t tagID = registerDispatch(layer, commandBuffer, -1, -1, -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdDispatchIndirect(commandBuffer, buffer, offset);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}
