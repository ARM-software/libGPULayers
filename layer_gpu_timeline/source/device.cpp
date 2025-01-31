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

#include "device.hpp"

#include "comms/comms_module.hpp"
#include "framework/utils.hpp"
#include "instance.hpp"
#include "workload_metadata_builder.hpp"

#include <vector>

#include <sys/stat.h>
#include <unistd.h>

/**
 * @brief The dispatch lookup for all of the created Vulkan devices.
 */
static std::unordered_map<void*, std::unique_ptr<Device>> g_devices;

/* See header for documentation. */
const std::vector<std::string> Device::extraExtensions {};

/* See header for documentation. */
std::unique_ptr<Comms::CommsModule> Device::commsModule;

/* See header for documentation. */
std::unique_ptr<TimelineComms> Device::commsWrapper;

/* See header for documentation. */
void Device::store(VkDevice handle, std::unique_ptr<Device> device)
{
    void* key = getDispatchKey(handle);
    g_devices.insert({key, std::move(device)});
}

/* See header for documentation. */
Device* Device::retrieve(VkDevice handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
Device* Device::retrieve(VkQueue handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
Device* Device::retrieve(VkCommandBuffer handle)
{
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_devices));
    return g_devices.at(key).get();
}

/* See header for documentation. */
void Device::destroy(Device* device)
{
    g_devices.erase(getDispatchKey(device));
}

/* See header for documentation. */
Device::Device(Instance* _instance,
               VkPhysicalDevice _physicalDevice,
               VkDevice _device,
               PFN_vkGetDeviceProcAddr nlayerGetProcAddress,
               const VkDeviceCreateInfo& createInfo)
    : instance(_instance),
      physicalDevice(_physicalDevice),
      device(_device)
{
    UNUSED(createInfo);

    initDriverDeviceDispatchTable(device, nlayerGetProcAddress, driver);

    // Init the shared comms module for the first device built
    if (!commsModule)
    {
        commsModule = std::make_unique<Comms::CommsModule>("lglcomms");
        commsWrapper = std::make_unique<TimelineComms>(*commsModule);
    }

    // Determine the driver version and emit the preamble message
    VkPhysicalDeviceProperties deviceProperties;
    instance->driver.vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

    std::string name {deviceProperties.deviceName};

    uint32_t driverVersion = deviceProperties.driverVersion;
    uint32_t major = VK_VERSION_MAJOR(driverVersion);
    uint32_t minor = VK_VERSION_MINOR(driverVersion);
    uint32_t patch = VK_VERSION_PATCH(driverVersion);

    pid_t processPID = getpid();

    WorkloadMetadataEmitterVisitor::emitMetadata(*this, processPID, major, minor, patch, std::move(name));
}
