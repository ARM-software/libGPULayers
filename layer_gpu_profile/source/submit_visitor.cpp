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
#include "device_utils.hpp"
#include "submit_visitor.hpp"
#include "framework/utils.hpp"

#include <nlohmann/json.hpp>

#include <string>

using json = nlohmann::json;

/* See header for documentation */
void ProfileSubmitVisitor::handleCPUTrap(
    const std::string& workloadType,
    const std::vector<std::string>& debugStack
) {
    json message {
        { "type", workloadType },
        { "labels", debugStack },
        { "counters", json::array() }
    };

    waitForGPU(device);

    auto ec = device.lgcSampler->sample_now();

    notifyGPU(device);

    if (ec)
    {
        LAYER_ERR("Failed to make libGPUCounters GPU counter sample");
    }
    else
    {
        for (const auto& pair : device.lgcActiveCounters)
        {
            hwcpipe::counter_sample sample;
            ec = device.lgcSampler->get_counter_value(pair.first, sample);
            if (ec)
            {
                LAYER_ERR("Failed to get libGPUCounters GPU counter value");
                continue;
            }

            if (sample.type == hwcpipe::counter_sample::type::uint64)
            {
                json counter {
                    { pair.second, sample.value.uint64 },
                };

                message["counters"].push_back(counter);

            }
            else
            {
                json counter {
                    { pair.second, sample.value.float64 },
                };

                message["counters"].push_back(counter);

            }
        }
    }

    device.txMessage(message.dump());

}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSRenderPass& renderPass,
    const std::vector<std::string>& debugStack
) {
    UNUSED(renderPass);

    handleCPUTrap("renderpass", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSRenderPassContinuation& continuation,
    const std::vector<std::string>& debugStack,
    uint64_t renderPassTagID
) {
    UNUSED(continuation);
    UNUSED(debugStack);
    UNUSED(renderPassTagID);

    // Ignore continuations because we only trigger one trap per render pass
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSDispatch& dispatch,
    const std::vector<std::string>& debugStack
) {
    UNUSED(dispatch);

    handleCPUTrap("compute", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSTraceRays& traceRays,
    const std::vector<std::string>& debugStack
) {
    UNUSED(traceRays);

    handleCPUTrap("tracerays", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSImageTransfer& imageTransfer,
    const std::vector<std::string>& debugStack
) {
    UNUSED(imageTransfer);

    handleCPUTrap("image_transfer", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSBufferTransfer& bufferTransfer,
    const std::vector<std::string>& debugStack
) {
    UNUSED(bufferTransfer);

    handleCPUTrap("buffer_transfer", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSAccelerationStructureBuild& asBuild,
    const std::vector<std::string>& debugStack
) {
    UNUSED(asBuild);

    handleCPUTrap("as_build", debugStack);
}

/* See header for documentation */
void ProfileSubmitVisitor::operator()(
    const Tracker::LCSAccelerationStructureTransfer& asTransfer,
    const std::vector<std::string>& debugStack
) {
    UNUSED(asTransfer);

    handleCPUTrap("as_transfer", debugStack);
}
