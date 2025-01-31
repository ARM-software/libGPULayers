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

#include "trackers/layer_command_stream.hpp"
#include "utils/misc.hpp"

#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace
{
/**
 * @brief Serialize the metadata for this render pass workload.
 *
 * @param renderpass The renderpass to serialize
 * @param debugLabel The debug label stack of the VkQueue at submit time.
 */
std::string serialize(const Tracker::LCSRenderPass& renderpass, const std::vector<std::string>& debugLabel)
{
    // Draw count for a multi-submit command buffer cannot be reliably
    // associated with a single tagID if restartable across command buffer
    // boundaries because different command buffer submit combinations can
    // result in different draw counts for the same starting tagID.
    int64_t drawCount = static_cast<int64_t>(renderpass.getDrawCallCount());

    if (!renderpass.isOneTimeSubmit() && renderpass.isSuspending())
    {
        drawCount = -1;
    }

    json metadata = {
        {"type", "renderpass"},
        {"tid", renderpass.getTagID()},
        {"width", renderpass.getWidth()},
        {"height", renderpass.getHeight()},
        {"drawCallCount", drawCount},
    };

    if (!debugLabel.empty())
    {
        metadata["label"] = debugLabel;
    }

    // Default is 1, so only store if we need it
    if (const auto spc = renderpass.getSubpassCount(); spc != 1)
    {
        metadata["subpassCount"] = spc;
    }

    json attachPoints = json::array();

    for (const auto& attachment : renderpass.getAttachments())
    {
        json attachPoint {
            {"binding", attachment.getAttachmentStr()},
        };

        // Default is false, so only serialize if we need it
        if (attachment.isLoaded())
        {
            attachPoint["load"] = true;
        }

        // Default is true, so only serialize if we need it
        if (!attachment.isStored())
        {
            attachPoint["store"] = false;
        }

        // Default is false, so only serialize if we need it
        if (attachment.isResolved())
        {
            attachPoint["resolve"] = true;
        }

        attachPoints.push_back(attachPoint);
    }

    metadata["attachments"] = attachPoints;

    return metadata.dump();
}

/**
 * @brief Serialize the metadata for this render pass continuation workload.
 *
 * @param continuation The renderpass continuation to serialize
 * @param tagIDContinuation The ID of the workload if this is a continuation of it.
 */
std::string serialize(const Tracker::LCSRenderPassContinuation& continuation, uint64_t tagIDContinuation)
{
    json metadata = {
        {"type", "renderpass"},
        {"tid", tagIDContinuation},
        {"drawCallCount", continuation.getDrawCallCount()},
    };

    return metadata.dump();
}

/**
 * @brief Get the metadata for this workload
 *
 * @param dispatch The dispatch to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
std::string serialize(const Tracker::LCSDispatch& dispatch, const std::vector<std::string>& debugLabel)
{
    json metadata = {
        {"type", "dispatch"},
        {"tid", dispatch.getTagID()},
        {"xGroups", dispatch.getXGroups()},
        {"yGroups", dispatch.getYGroups()},
        {"zGroups", dispatch.getZGroups()},
    };

    if (!debugLabel.empty())
    {
        metadata["label"] = debugLabel;
    }

    return metadata.dump();
}

/**
 * @brief Get the metadata for this workload
 *
 * @param traceRays The trace rays to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
std::string serialize(const Tracker::LCSTraceRays& traceRays, const std::vector<std::string>& debugLabel)
{
    json metadata = {
        {"type", "tracerays"},
        {"tid", traceRays.getTagID()},
        {"xItems", traceRays.getXItems()},
        {"yItems", traceRays.getYItems()},
        {"zItems", traceRays.getZItems()},
    };

    if (!debugLabel.empty())
    {
        metadata["label"] = debugLabel;
    }

    return metadata.dump();
}

/**
 * @brief Get the metadata for this workload
 *
 * @param imageTransfer The image transfer to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
std::string serialize(const Tracker::LCSImageTransfer& imageTransfer, const std::vector<std::string>& debugLabel)
{
    json metadata = {
        {"type", "imagetransfer"},
        {"tid", imageTransfer.getTagID()},
        {"subtype", imageTransfer.getTransferType()},
        {"pixelCount", imageTransfer.getPixelCount()},
    };

    if (!debugLabel.empty())
    {
        metadata["label"] = debugLabel;
    }

    return metadata.dump();
}

/**
 * @brief Get the metadata for this workload
 *
 * @param bufferTransfer The buffer transfer to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
std::string serialize(const Tracker::LCSBufferTransfer& bufferTransfer, const std::vector<std::string>& debugLabel)
{
    json metadata = {
        {"type", "buffertransfer"},
        {"tid", bufferTransfer.getTagID()},
        {"subtype", bufferTransfer.getTransferType()},
        {"byteCount", bufferTransfer.getByteCount()},
    };

    if (!debugLabel.empty())
    {
        metadata["label"] = debugLabel;
    }

    return metadata.dump();
}
}

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
    layerDevice.txMessage(serialize(renderpass, debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSRenderPassContinuation& continuation,
                                                const std::vector<std::string>& debugStack,
                                                uint64_t renderpassTagID)
{
    UNUSED(debugStack);

    layerDevice.txMessage(serialize(continuation, renderpassTagID));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSDispatch& dispatch,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(serialize(dispatch, debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSTraceRays& traceRays,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(serialize(traceRays, debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSImageTransfer& imageTransfer,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(serialize(imageTransfer, debugStack));
}

void WorkloadMetadataEmitterVisitor::operator()(const Tracker::LCSBufferTransfer& bufferTransfer,
                                                const std::vector<std::string>& debugStack)
{
    layerDevice.txMessage(serialize(bufferTransfer, debugStack));
}
