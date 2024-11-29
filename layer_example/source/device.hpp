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

/**
 * @file
 * This module implements layer tracking for VkDevice objects.
 *
 * Role summary
 * ============
 *
 * Devices represent the core context used by the application to connect to the underlying graphics
 * driver. A device object is the dispatch root for the Vulkan driver, so device commands all take
 * some form of dispatchable handle that can be resolved into a unique per-device key. For the
 * driver this key would simply be a pointer directly to the driver-internal device object, but for
 * our layer we use a device dispatch key as an index in to the map to find the layer's driver
 * object.
 *
 * Key properties
 * ==============
 *
 * Unlike EGL contexts, Vulkan devices are designed to be used concurrently by multiple application
 * threads. An application can have multiple concurrent devices (although this is less common than
 * with OpenGL ES applications), and use each device from multiple threads.
 */

#pragma once

#include <vulkan/vk_layer.h>

#include "instance.hpp"
#include "device_dispatch_table.hpp"

/**
 * \brief This class implements the layer state tracker for a single device.
 */
class Device
{
public:
    /**
     * \brief Store a new device into the global store of dispatchable devices.
     *
     * \param handle   The dispatchable device handle to use as an indirect key.
     * \param device   The \c Device object to store.
     */
    static void store(
        VkDevice handle,
        std::unique_ptr<Device> device);

    /**
     * \brief Fetch a device from the global store of dispatchable devices.
     *
     * \param handle   The dispatchable device handle to use as an indirect lookup.
     */
    static Device* retrieve(
        VkDevice handle);

    /**
     * \brief Fetch a device from the global store of dispatchable devices.
     *
     * \param handle   The dispatchable queue handle to use as an indirect lookup.
     */
    static Device* retrieve(
        VkQueue handle);

    /**
     * \brief Fetch a device from the global store of dispatchable devices.
     *
     * \param handle   The dispatchable command buffer handle to use as an indirect lookup.
     */
    static Device* retrieve(
        VkCommandBuffer handle);

    /**
     * \brief Drop a device from the global store of dispatchable devices.
     *
     * \param device   The device to drop.
     */
    static void destroy(
        Device* device);

    /**
     * \brief Create a new layer device object.
     *
     * \param instance               The layer instance object this device is created with.
     * \param physicalDevice         The physical device this logical device is for.
     * \param device                 The device handle this device is created with.
     * \param nlayerGetProcAddress   The vkGetProcAddress function in the driver/next layer down.
     */
    Device(
        Instance* instance,
        VkPhysicalDevice physicalDevice,
        VkDevice device,
        PFN_vkGetDeviceProcAddr nlayerGetProcAddress);

    /**
     * \brief Destroy this layer device object.
     */
    ~Device();

public:
    /**
     * \brief The instance this device is created with.
     */
    const Instance* instance;

    /**
     * \brief The physical device this device is created with.
     */
    const VkPhysicalDevice physicalDevice;

    /**
     * \brief The device handle this device is created with.
     */
    const VkDevice device;

    /**
     * \brief The driver function dispatch table.
     */
    DeviceDispatchTable driver { 0 };
};
