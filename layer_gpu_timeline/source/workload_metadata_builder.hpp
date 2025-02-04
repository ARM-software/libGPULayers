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
 * \file
 * Methods for transforming layer command stream workloads into metadata messages
 * for transmission to the host.
 *
 * Role summary
 * ============
 *
 * These methods convert a command stream workload into some metadata payload
 * message that can then be sent to the host.
 */

#pragma once

#include "device.hpp"
#include "trackers/layer_command_stream.hpp"
#include "trackers/queue.hpp"

#include <cstdint>

#include <vulkan/vulkan_core.h>

class WorkloadMetadataEmitterVisitor : public Tracker::SubmitCommandWorkloadVisitor
{
public:
    /**
     * @brief Called once when the layer is first created to produce the "metadata" frame for that layer device
     *
     * @param device The device object that the payloads are produced for, and to which they are passed for transmission
     * @param pid The process ID of this process
     * @param major The driver major version
     * @param minor The driver minor version
     * @param patch The driver patch version
     * @param name The device name
     */
    static void emitMetadata(Device& device,
                             uint32_t pid,
                             uint32_t major,
                             uint32_t minor,
                             uint32_t patch,
                             std::string name);

    /**
     * @brief Called at the start of a frame, delimiting the subsequent items from any later frame
     *
     * @param device The device object that the payloads are produced for, and to which they are passed for transmission
     * @param frameNumber The frame number that uniquely identifies this frame
     * @param timestamp The timestamp of the frame
     */
    static void emitFrame(Device& device, uint64_t frameNumber, uint64_t timestamp);

    /**
     * Construct a new workload metadata emitter that will output paylaods for the provided device
     *
     * @param _device The device object that the payloads are produced for, and to which they are passed for
     * transmission
     */
    WorkloadMetadataEmitterVisitor(Device& _device)
        : device(_device)
    {
    }

    // visitor should not be copied or moved from
    WorkloadMetadataEmitterVisitor(const WorkloadMetadataEmitterVisitor&) = delete;
    WorkloadMetadataEmitterVisitor(WorkloadMetadataEmitterVisitor&&) noexcept = delete;
    WorkloadMetadataEmitterVisitor& operator=(const WorkloadMetadataEmitterVisitor&) = delete;
    WorkloadMetadataEmitterVisitor& operator=(WorkloadMetadataEmitterVisitor&&) noexcept = delete;

    // methods from the visitor interface
    void operator()(const Tracker::LCSRenderPass& renderpass, const std::vector<std::string>& debugStack) override;
    void operator()(const Tracker::LCSRenderPassContinuation& continuation,
                    const std::vector<std::string>& debugStack,
                    uint64_t renderpassTagID) override;
    void operator()(const Tracker::LCSDispatch& dispatch, const std::vector<std::string>& debugStack) override;
    void operator()(const Tracker::LCSTraceRays& traceRays, const std::vector<std::string>& debugStack) override;
    void operator()(const Tracker::LCSImageTransfer& imageTransfer,
                    const std::vector<std::string>& debugStack) override;
    void operator()(const Tracker::LCSBufferTransfer& bufferTransfer,
                    const std::vector<std::string>& debugStack) override;

    /**
     * @brief Called at the start of the submit to emit a "Submit" record, delimiting the subsequent items from any
     * later submit
     *
     * @param queue The queue that was submitted to
     * @param timestamp The timestamp of the submission
     */
    void emitSubmit(VkQueue queue, uint64_t timestamp);

private:
    Device& device;
};
