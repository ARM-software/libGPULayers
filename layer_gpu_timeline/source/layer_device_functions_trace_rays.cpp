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

#include <memory>
#include <mutex>
#include <thread>

extern std::mutex g_vulkanLock;

/**
 * @brief Register an acceleration structure build with the tracker.
 *
 * @param layer            The layer context for the device.
 * @param commandBuffer    The command buffer we are recording.
 * @param buildType        The build type.
 * @param primitiveCount   The number of primitives in the build.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerAccelerationStructureBuild(Device* layer,
                                                   VkCommandBuffer commandBuffer,
                                                   Tracker::LCSAccelerationStructureBuild::Type buildType,
                                                   int64_t primitiveCount)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.accelerationStructureBuild(buildType, primitiveCount);
}

/**
 * @brief Register a trace rays dispatch with the tracker.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param itemsX          The X size of the dispatch in work items.
 * @param itemsY          The Y size of the dispatch in work items.
 * @param itemsZ          The Z size of the dispatch in work items.
 *
 * @return The assigned tagID for the workload.
 */
static uint64_t registerTraceRays(Device* layer,
                                  VkCommandBuffer commandBuffer,
                                  int64_t itemsX,
                                  int64_t itemsY,
                                  int64_t itemsZ)
{
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    return cb.traceRays(itemsX, itemsY, itemsZ);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresIndirectKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkDeviceAddress* pIndirectDeviceAddresses,
    const uint32_t* pIndirectStrides,
    const uint32_t* const* ppMaxPrimitiveCounts)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerAccelerationStructureBuild(layer,
                                                        commandBuffer,
                                                        Tracker::LCSAccelerationStructureBuild::Type::unknown,
                                                        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer,
                                                              infoCount,
                                                              pInfos,
                                                              pIndirectDeviceAddresses,
                                                              pIndirectStrides,
                                                              ppMaxPrimitiveCounts);
    emitEndTag(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBuildAccelerationStructuresKHR<user_tag>(
    VkCommandBuffer commandBuffer,
    uint32_t infoCount,
    const VkAccelerationStructureBuildGeometryInfoKHR* pInfos,
    const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerAccelerationStructureBuild(layer,
                                                        commandBuffer,
                                                        Tracker::LCSAccelerationStructureBuild::Type::unknown,
                                                        -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
    emitEndTag(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdTraceRaysIndirect2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                      VkDeviceAddress indirectDeviceAddress)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerTraceRays(layer, commandBuffer, -1, -1, -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
    emitEndTag(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdTraceRaysIndirectKHR<user_tag>(VkCommandBuffer commandBuffer,
                                              const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
                                              const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
                                              VkDeviceAddress indirectDeviceAddress)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerTraceRays(layer, commandBuffer, -1, -1, -1);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdTraceRaysIndirectKHR(commandBuffer,
                                            pRaygenShaderBindingTable,
                                            pMissShaderBindingTable,
                                            pHitShaderBindingTable,
                                            pCallableShaderBindingTable,
                                            indirectDeviceAddress);
    emitEndTag(layer, commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL
    layer_vkCmdTraceRaysKHR<user_tag>(VkCommandBuffer commandBuffer,
                                      const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable,
                                      const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable,
                                      uint32_t width,
                                      uint32_t height,
                                      uint32_t depth)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    uint64_t tagID = registerTraceRays(layer, commandBuffer, width, height, depth);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdTraceRaysKHR(commandBuffer,
                                    pRaygenShaderBindingTable,
                                    pMissShaderBindingTable,
                                    pHitShaderBindingTable,
                                    pCallableShaderBindingTable,
                                    width,
                                    height,
                                    depth);
    emitEndTag(layer, commandBuffer);
}
