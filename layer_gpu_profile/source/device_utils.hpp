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

#pragma once

#include "device.hpp"

#include <chrono>
#include <thread>

#include <vulkan/vulkan.h>

/**
 * @brief Emit workaround sleep if needed.
 */
[[maybe_unused]] static void workaroundDelay()
{
    // We could make this conditional (enable if GPU is CSF and DDK < r54p0).
    // However the profile is always going to be invasive, and it's quite a bit
    // of added complexity to handle.
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
}

/**
 * @brief Emit the GPU-side trigger/wait for a CPU-side trap.
 *
 * Note: this relies on an undocumented extension supported by Arm GPUs, which
 * allows the CPU to set/wait/reset events in a command buffer after it has
 * been submitted to a queue.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 */
[[maybe_unused]] static void emitCPUTrap(
    Device& layer,
    VkCommandBuffer commandBuffer
) {
    // Don't instrument outside of active frame of interest
    if(!layer.isFrameOfInterest)
    {
        return;
    }

    // Signal the gpuToCpu to wake the CPU to perform its operation
    layer.driver.vkCmdSetEvent(
        commandBuffer,
        layer.gpuToCpuEvent,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

    // Wait for cpuToGpu to wake the GPU after CPU has finished
    layer.driver.vkCmdWaitEvents(
        commandBuffer,
        1,
        &layer.cpuToGpuEvent,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
        0, nullptr,
        0, nullptr,
        0, nullptr);

    // Reset cpuToGpu so it's ready to use again
    layer.driver.vkCmdResetEvent(
        commandBuffer,
        layer.cpuToGpuEvent,
        VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
}

/**
 * @brief Perform the CPU-side wait for a CPU-side trap.
 *
 * Note: this relies on an undocumented extension supported by Arm GPUs, which
 * allows the CPU to set/wait/reset events in a command buffer after it has
 * been submitted to a queue.
 *
 * @param layer           The layer context for the device.
 */
[[maybe_unused]] static void waitForGPU(
    Device& layer
) {
    // Wait for gpuToCpu to wake the CPU after GPU has finished
    while(true)
    {
        auto res = layer.driver.vkGetEventStatus(layer.device, layer.gpuToCpuEvent);
        if (res == VK_EVENT_SET)
        {
            break;
        }

        if (res != VK_EVENT_RESET)
        {
            LAYER_LOG("Failed to wait for gpuToCpuEvent");
        }

        // Sleep before polling again
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    // Reset gpuToCpu so it's ready to use again
     auto res = layer.driver.vkResetEvent(layer.device, layer.gpuToCpuEvent);
    if (res != VK_SUCCESS)
    {
        LAYER_LOG("Failed to reset gpuToCpuEvent");
    }

    // Sleep after event set to workaround counter sync errata on older drivers
    workaroundDelay();
}

/**
 * @brief Perform the CPU-side notify of the GPU after a CPU-side trap.
 *
 * Note: this relies on an undocumented extension supported by Arm GPUs, which
 * allows the CPU to set/wait/reset events in a command buffer after it has
 * been submitted to a queue.
 *
 * @param layer           The layer context for the device.
 */
[[maybe_unused]] static void notifyGPU(
    Device& layer
) {
    // Signal cpuToGpu to wake the GPU to keep processing the command stream
    auto res = layer.driver.vkSetEvent(layer.device, layer.cpuToGpuEvent);
    if (res != VK_SUCCESS)
    {
        LAYER_LOG("Failed to notify cpuToGpuEvent");
    }
}
