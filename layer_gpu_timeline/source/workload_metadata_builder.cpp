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

#include "workload_metadata_builder.hpp"

#include "utils/misc.hpp"

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void WorkloadMetadataEmitterVisitor::emitMetadata(Device& layerDevice,
                                                  uint32_t pid,
                                                  uint32_t major,
                                                  uint32_t minor,
                                                  uint32_t patch,
                                                  std::string name)
{
    json deviceMetadata {
        {"type", "device"},
        {"pid", pid},
        {"device", reinterpret_cast<uintptr_t>(layerDevice.device)},
        {"deviceName", std::move(name)},
        {"driverMajor", major},
        {"driverMinor", minor},
        {"driverPatch", patch},
    };

    layerDevice.txMessage(deviceMetadata.dump());
}

void WorkloadMetadataEmitterVisitor::emitFrame(Device& device, uint64_t frameNumber, uint64_t timestamp)
{
    json frame {
        {"type", "frame"},
        {"device", reinterpret_cast<uintptr_t>(device.device)},
        {"fid", frameNumber},
        {"timestamp", timestamp},
    };

    device.txMessage(frame.dump());
}

void WorkloadMetadataEmitterVisitor::emitSubmit(VkDevice device, VkQueue queue, uint64_t timestamp)
{
    // Write the queue submit metadata
    json submitMetadata {
        {"type", "submit"},
        {"device", reinterpret_cast<uintptr_t>(device)},
        {"queue", reinterpret_cast<uintptr_t>(queue)},
        {"timestamp", timestamp},
    };

    layerDevice.txMessage(submitMetadata.dump());
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSRenderPass& renderpass,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(renderpass.getMetadata(debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSRenderPassContinuation& continuation,
                                                const std::vector<std::string>& debugStack,
                                                uint64_t renderpassTagID)
{
    UNUSED(debugStack);

    layerDevice.txMessage(continuation.getMetadata(renderpassTagID));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSDispatch& dispatch,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(dispatch.getMetadata(debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSTraceRays& traceRays,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(traceRays.getMetadata(debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSImageTransfer& imageTransfer,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(imageTransfer.getMetadata(debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSBufferTransfer& bufferTransfer,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(bufferTransfer.getMetadata(debugStack));
}
