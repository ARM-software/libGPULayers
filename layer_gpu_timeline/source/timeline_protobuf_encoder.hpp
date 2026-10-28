/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025-2026 Arm Limited
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
#include "timeline_comms.hpp"
#include "trackers/layer_command_stream.hpp"
#include "trackers/queue.hpp"

#include <cstdint>

#include <vulkan/vulkan_core.h>

/**
 * Encodes various protocol messages in protobuf format for transmission to the
 * host
 */
class TimelineProtobufEncoder : public Tracker::SubmitCommandWorkloadVisitor
{
public:
    /**
     * @brief Emit a header message.
     *
     * This is called once, when the GPU timeline comms connection is first
     * established. It outputs a header message into the stream that identifies
     * the version of the layer driver protocol used.
     *
     * @param comms   The comms interface used to transmit the message
     */
    static void emitHeaderMessage(
        TimelineComms& comms);

    /**
     * @brief Emit a device metadata message.
     *
     * This is called once, when the layer is first created for a device. It
     * outputs a metadata message into the steam that identifies the device and
     * driver configuration it uses.
     *
     * @param device   The device object that the payloads are produced for
     * @param pid      The process ID of this process
     * @param major    The driver major version
     * @param minor    The driver minor version
     * @param patch    The driver patch version
     * @param name     The device name
     */
    static void emitMetadata(
        Device& device,
        uint32_t pid,
        uint32_t major,
        uint32_t minor,
        uint32_t patch,
        std::string name);

    /**
     * @brief Emit a start of frame message.
     *
     * This is called at the start of every frame, delimiting the subsequent
     * messages from from any earlier frame.
     *
     * @param device        The device object that the payloads are produced for
     * @param frameNumber   The frame number that uniquely identifies this frame
     * @param timestamp     The timestamp of the frame
     */
    static void emitFrame(
        Device& device,
        uint64_t frameNumber,
        uint64_t timestamp);

    /**
     * @brief Construct a new workload metadata emitter for the provided device.
     *
     * @param _device   The device object that the payloads are produced for.
     */
    TimelineProtobufEncoder(
        Device& _device
    ) :
        device(_device)
    {
    }

    // Visitor should not be copied or moved from
    TimelineProtobufEncoder(
        const TimelineProtobufEncoder&) = delete;

    TimelineProtobufEncoder(
        TimelineProtobufEncoder&&) noexcept = delete;

    TimelineProtobufEncoder& operator=(
        const TimelineProtobufEncoder&) = delete;

    TimelineProtobufEncoder& operator=(
        TimelineProtobufEncoder&&) noexcept = delete;

    // Methods from the visitor interface
    void operator()(
        const Tracker::LCSRenderPass& renderPass,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSRenderPassContinuation& continuation,
        const std::vector<std::string>& debugStack,
        uint64_t renderPassTagID) override;

    void operator()(
        const Tracker::LCSDispatch& dispatch,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSDispatchDataGraph& dispatch,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSTraceRays& traceRays,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSImageTransfer& imageTransfer,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSBufferTransfer& bufferTransfer,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSAccelerationStructureBuild& asBuild,
        const std::vector<std::string>& debugStack) override;

    void operator()(
        const Tracker::LCSAccelerationStructureTransfer& asTransfer,
        const std::vector<std::string>& debugStack) override;

    /**
     * @brief Emit a queue submit message.
     *
     * This is called at the start of every submit, delimiting the subsequent
     * messages from from any earlier submit.
     *
     * @param queue       The queue that was submitted to
     * @param timestamp   The timestamp of the submission
     */
    void emitSubmit(
        VkQueue queue,
        uint64_t timestamp);

private:
    Device& device;
};
