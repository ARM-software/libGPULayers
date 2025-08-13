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
 * @file
 * Declares the root class for layer management of VkInstance objects.
 *
 * Role summary
 * ============
 *
 * Instances represent the core context used by the application to connect to
 * the OS graphics subsystem prior to connection to a specific device instance.
 * An instance object is the dispatch root for the Vulkan subsystem, so
 * instance commands all take some form of dispatchable handle that can be
 * resolved into a unique per-instance key. For the driver this key would
 * simply be a pointer directly to the driver-internal instance object, but for
 * our layer we use a instance dispatch key as an index in to the map to find
 * the layer's instance object.
 *
 * Key properties
 * ==============
 *
 * Vulkan instances are designed to be used concurrently by multiple
 * application threads. An application can have multiple concurrent instances,
 * and use each instance from multiple threads.
 *
 * Access to the layer driver structures must therefore be kept thread-safe.
 * For sake of simplicity, we generally implement this by:
 *   - Holding a global lock whenever any thread is inside layer code.
 *   - Releasing the global lock whenever the layer calls a driver function.
 */

#pragma once

#include "framework/instance_dispatch_table.hpp"
#include "layer_config.hpp"

#include <memory>

#include <vulkan/vk_layer.h>
#include <vulkan/vulkan.h>

/**
 * @brief This class implements the layer state tracker for a single instance.
 */
class Instance
{
public:
    /**
     * @brief Store a new instance into the global store of dispatchable instances.
     *
     * @param handle     The dispatchable instance handle to use as an indirect key.
     * @param instance   The @c Instance object to store.
     */
    static void store(VkInstance handle, std::unique_ptr<Instance>& instance);

    /**
     * @brief Fetch an instance from the global store of dispatchable instances.
     *
     * @param handle   The dispatchable instance handle to use as an indirect lookup.
     *
     * @return The layer instance context.
     */
    static Instance* retrieve(VkInstance handle);

    /**
     * @brief Fetch an instance from the global store of dispatchable instances.
     *
     * @param handle   The dispatchable physical device handle to use as an indirect lookup.
     *
     * @return The layer instance context.
     */
    static Instance* retrieve(VkPhysicalDevice handle);

    /**
     * @brief Drop an instance from the global store of dispatchable instances.
     *
     * This must be called before the driver VkInstance has been destroyed, as
     * we deference the native instance handle to get the dispatch key.
     *
     * @param handle   The dispatchable instance handle to use as an indirect lookup.
     *
     * @return Returns the ownership of the Instance object to the caller.
     */
    static std::unique_ptr<Instance> destroy(
        VkInstance handle);

    /**
     * @brief Create a new layer instance object.
     *
     * @param instance               The instance handle this instance is created with.
     * @param nlayerGetProcAddress   The vkGetProcAddress function in the driver/next layer down.
     */
    Instance(VkInstance instance, PFN_vkGetInstanceProcAddr nlayerGetProcAddress);

public:
    /**
     * @brief The instance handle this instance is created with.
     */
    VkInstance instance;

    /**
     * @brief The next layer's @c vkGetInstanceProcAddr() function pointer.
     */
    PFN_vkGetInstanceProcAddr nlayerGetProcAddress;

    /**
     * @brief The driver function dispatch table.
     */
    InstanceDispatchTable driver {};

    /**
     * @brief The layer configuration.
     */
    const LayerConfig config;

    /**
     * @brief The minimum API version needed by this layer.
     */
    static const APIVersion minAPIVersion;

    /**
     * @brief The minimum set of instance extensions needed by this layer.
     */
    static const std::vector<std::string> extraExtensions;
};
