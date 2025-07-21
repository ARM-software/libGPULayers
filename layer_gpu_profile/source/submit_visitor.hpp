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

#pragma once

#include "device.hpp"
#include "trackers/layer_command_stream.hpp"
#include "trackers/queue.hpp"

#include <string>
#include <vector>

/**
 * Handles setting up async state ...
 */
class ProfileSubmitVisitor : public Tracker::SubmitCommandWorkloadVisitor
{
public:
    /**
     * Construct a profile workload visitor for a layer command stream.
     *
     * @param _device The device object for the command stream.
     */
    ProfileSubmitVisitor(Device& _device)
        : device(_device)
    {
    }

    // Visitor should not be copied or moved from
    ProfileSubmitVisitor(const ProfileSubmitVisitor&) = delete;
    ProfileSubmitVisitor(ProfileSubmitVisitor&&) noexcept = delete;
    ProfileSubmitVisitor& operator=(const ProfileSubmitVisitor&) = delete;
    ProfileSubmitVisitor& operator=(ProfileSubmitVisitor&&) noexcept = delete;

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

private:
    void handleCPUTrap(
        const std::string& workloadType,
        const std::vector<std::string>& debugStack);

private:
    Device& device;
};

