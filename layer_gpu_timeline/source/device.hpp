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

/**
 * @file Declares the root class for layer management of VkDevice objects.
 *
 * Role summary
 * ============
 *
 * Devices represent the core context used by the application to connect to the
 * underlying graphics driver. A device object is the dispatch root for the
 * Vulkan driver, so device commands all take some form of dispatchable handle
 * that can be resolved into a unique per-device key. For the driver this key
 * would simply be a pointer directly to the driver-internal device object, but
 * for our layer we use a device dispatch key as an index in to the map to find
 * the layer's driver object.
 *
 * Key properties
 * ==============
 *
 * Vulkan devices are designed to be used concurrently by multiple application
 * threads. An application can have multiple concurrent devices, and use each
 * device from multiple threads.
 *
 * Access to the layer driver structures must therefore be kept thread-safe.
 * For sake of simplicity, we generally implement this by:
 *   - Holding a global lock whenever any thread is inside layer code.
 *   - Releasing the global lock whenever the layer calls a driver function.
 */

#pragma once

#include <string>
#include <vector>
#include <vulkan/utility/vk_safe_struct.hpp>
#include <vulkan/vk_layer.h>

#include "comms/comms_module.hpp"
#include "framework/device_dispatch_table.hpp"
#include "instance.hpp"
#include "timeline_comms.hpp"
#include "trackers/device.hpp"

/**
 * @brief Function pointer type for patching VkDeviceCreateInfo.
 */
using DeviceCreatePatchPtr = void (*)(Instance& instance,
                                      VkPhysicalDevice physicalDevice,
                                      vku::safe_VkDeviceCreateInfo& createInfo,
                                      std::vector<std::string>& supported);

/**
 * @brief This class implements the layer state tracker for a single device.
 */
class Device
{
public:
    /**
     * @brief Store a new device into the global store of dispatchable devices.
     *
     * @param handle   The dispatchable device handle to use as an indirect key.
     * @param device   The @c Device object to store.
     */
    static void store(VkDevice handle, std::unique_ptr<Device> device);

    /**
     * @brief Fetch a device from the global store of dispatchable devices.
     *
     * @param handle   The dispatchable device handle to use as an indirect lookup.
     *
     * @return The layer device context.
     */
    static Device* retrieve(VkDevice handle);

    /**
     * @brief Fetch a device from the global store of dispatchable devices.
     *
     * @param handle   The dispatchable queue handle to use as an indirect lookup.
     *
     * @return The layer device context.
     */
    static Device* retrieve(VkQueue handle);

    /**
     * @brief Fetch a device from the global store of dispatchable devices.
     *
     * @param handle   The dispatchable command buffer handle to use as an indirect lookup.
     *
     * @return The layer device context.
     */
    static Device* retrieve(VkCommandBuffer handle);

    /**
     * \brief Drop a device from the global store of dispatchable devices.
     *
     * This must be called before the driver VkDevice has been destroyed, as
     * we deference the native device handle to get the dispatch key.
     *
     * \param handle   The dispatchable device handle to use as an indirect lookup.
     *
     * \return Returns the ownership of the Device object to the caller.
     */
    static std::unique_ptr<Device> destroy(
        VkDevice handle);

    /**
     * @brief Create a new layer device object.
     *
     * Create info is transient, so the constructor must copy what it needs.
     *
     * @param instance               The layer instance object this device is created with.
     * @param physicalDevice         The physical device this logical device is for.
     * @param device                 The device handle this device is created with.
     * @param nlayerGetProcAddress   The vkGetDeviceProcAddress function for the driver.
     * @param createInfo             The create info used to create the device.
     */
    Device(Instance* instance,
           VkPhysicalDevice physicalDevice,
           VkDevice device,
           PFN_vkGetDeviceProcAddr nlayerGetProcAddress,
           const VkDeviceCreateInfo& createInfo);

    /**
     * @brief Destroy this layer device object.
     */
    ~Device() = default;

    /**
     * @brief Callback for sending some message for the device.
     *
     * @param message   The message to send.
     */
    void txMessage(Comms::MessageData&& message) { commsWrapper->txMessage(std::move(message)); }

    /**
     * @brief Get the cumulative stats for this device.
     */
    Tracker::Device& getStateTracker() { return stateTracker; }

public:
    /**
     * @brief The instance this device is created with.
     */
    const Instance* instance;

    /**
     * @brief The physical device this device is created with.
     */
    const VkPhysicalDevice physicalDevice;

    /**
     * @brief The device handle this device is created with.
     */
    const VkDevice device;

    /**
     * @brief The driver function dispatch table.
     */
    DeviceDispatchTable driver {};

    /**
     * @brief The set of VkCreateDeviceInfo patches needed by this layer.
     */
    static const std::vector<DeviceCreatePatchPtr> createInfoPatches;

private:
    /**
     * @brief State tracker for this device.
     */
    Tracker::Device stateTracker;

    /**
     * @brief Shared network communications module.
     */
    static std::unique_ptr<Comms::CommsModule> commsModule;

    /**
     * @brief Shared network communications message encoder.
     */
    static std::unique_ptr<TimelineComms> commsWrapper;
};
