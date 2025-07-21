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
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

#include "comms/comms_module.hpp"
#include "device.hpp"
#include "framework/manual_functions.hpp"
#include "framework/utils.hpp"
#include "instance.hpp"

/**
 * @brief The dispatch lookup for all of the created Vulkan devices.
 */
static std::unordered_map<void*, std::unique_ptr<Device>> g_devices;

/* See header for documentation. */
const std::vector<DeviceCreatePatchPtr> Device::createInfoPatches {};

/* See header for documentation. */
std::unique_ptr<Comms::CommsModule> Device::commsModule;

/* See header for documentation. */
std::unique_ptr<ProfileComms> Device::commsWrapper;

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

    // Emit a log if debug utils entry points did not load. In this scenario
    // the layer will still be loaded and send metadata packets to the server
    // socket, but the Perfetto data will not contain any tag labels. We will
    // therefore be unable to cross-reference the two data streams to produce a
    // usable visualization.
    if (!driver.vkCmdBeginDebugUtilsLabelEXT)
    {
        LAYER_LOG("  - ERROR: Device does not expose VK_EXT_debug_utils");
        LAYER_LOG("           Profiling will not contain debug labels");
    }

    // Init the shared comms module for the first device built
    if (!commsModule)
    {
        commsModule = std::make_unique<Comms::CommsModule>("lglcomms");
        commsWrapper = std::make_unique<ProfileComms>(*commsModule);
    }

    // Create events for CPU<>GPU synchronization
    VkEventCreateInfo eventCreateInfo {
        .sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };

    auto result = driver.vkCreateEvent(device, &eventCreateInfo, nullptr, &gpuToCpuEvent);
    if (result != VK_SUCCESS)
    {
        LAYER_ERR("Failed vkCreateEvent() for gpu->cpu synchronization");
    }

    result = driver.vkCreateEvent(device, &eventCreateInfo, nullptr, &cpuToGpuEvent);
    if (result != VK_SUCCESS)
    {
        LAYER_ERR("Failed vkCreateEvent() for cpu->gpu synchronization");
    }

    // Create the counter context
    lgcGpu = std::make_unique<hwcpipe::gpu>(0);
    if (!lgcGpu->valid())
    {
        LAYER_ERR("Failed libGPUCounters GPU context creation");
        return;
    }

    // Create the counter sampler config
    auto config = hwcpipe::sampler_config(*lgcGpu.get());

    LAYER_LOG("Configuring libGPUCounters:");

    // Queue cycles, not all of these are available on all GPUs - the ones that
    // are not available will be transparently dropped
    addCounter(config, MaliCompQueueActiveCy, "Compute queue active cycles");
    addCounter(config, MaliVertQueueActiveCy, "Vertex queue active cycles");
    addCounter(config, MaliBinningQueueActiveCy, "Binning phase queue active cycles");
    addCounter(config, MaliNonFragQueueActiveCy, "Non-fragment queue active cycles");
    addCounter(config, MaliFragQueueActiveCy, "Fragment queue active cycles");
    addCounter(config, MaliMainQueueActiveCy, "Main phase queue active cycles");

    // External bandwidth
    addCounter(config, MaliExtBusRdBy, "External read bytes");
    addCounter(config, MaliExtBusWrBy, "External write bytes");

    // Primitive counts
    addCounter(config, MaliGeomTotalPrim, "Input primitives");
    addCounter(config, MaliGeomVisiblePrim, "Visible primitives");

    // Thread counts
    addCounter(config, MaliNonFragThread, "Non-fragment threads");
    addCounter(config, MaliFragThread, "Fragment threads");

    // Functional unit counters
    // TODO HIVE-1307: Currently libGPUCounters doesn't expose a MaliALUIssueCy
    // counter, so we use instruction counts as a measure of relative
    // arithmetic complexity across workloads, but note that it is not directly
    // comparable with the other "* unit cycles" counters.
    addCounter(config, MaliEngInstr, "Arithmetic unit instructions");
    addCounter(config, MaliEngFMAInstr, "Arithmetic unit FMA instructions");
    addCounter(config, MaliEngCVTInstr, "Arithmetic unit CVT instructions");
    addCounter(config, MaliEngSFUInstr, "Arithmetic unit SFU instructions");
    addCounter(config, MaliVarIssueCy, "Varying unit cycles");
    addCounter(config, MaliTexIssueCy, "Texture unit cycles");
    addCounter(config, MaliLSIssueCy, "Load/store unit cycles");

    // Create the counter sampler and set it running
    lgcSampler = std::make_unique<hwcpipe::sampler<>>(config);
    auto ec = lgcSampler->start_sampling();
    if (ec)
    {
        LAYER_ERR("Failed libGPUCounters GPU sampler creation");
    }
}

void Device::addCounter(
    hwcpipe::sampler_config& config,
    hwcpipe_counter counterID,
    const char* counterName
) {
    auto ec = config.add_counter(counterID);
    if (ec)
    {
        LAYER_LOG(" - %s not available", counterName);
    }
    else
    {
        LAYER_LOG(" + %s selected", counterName);
        lgcActiveCounters.emplace_back(counterID, counterName);
    }
}
