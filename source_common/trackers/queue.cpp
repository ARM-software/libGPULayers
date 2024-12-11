/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022-2024 Arm Limited
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

#include <cassert>

#include "trackers/queue.hpp"

namespace Tracker
{
/* See header for details. */
std::atomic<uint64_t> Queue::nextSubmitID { 1 };

/* See header for details. */
Queue::Queue(
    VkQueue _handle):
    handle(_handle) { };

/* See header for details. */
void Queue::runSubmitCommandStream(
    const std::vector<LCSInstruction>& stream,
    std::function<void(const std::string&)> callback
) {
    for (auto& instr: stream)
    {
        LCSOpcode opCode = instr.first;
        const LCSWorkload* opData = instr.second.get();

        if (opCode == LCSOpcode::MARKER_BEGIN)
        {
            debugStack.push_back(opData->getMetadata());
        }
        else if (opCode == LCSOpcode::MARKER_END)
        {
            debugStack.pop_back();
        }
        else if (opCode == LCSOpcode::RENDER_PASS)
        {
            auto* workload = dynamic_cast<const LCSRenderPass*>(opData);
            uint64_t tagID = workload->getTagID();

            // Build the debug info
            std::string log = joinString(debugStack, "|");

            // Workload is a new render pass
            if (tagID > 0)
            {
                assert(lastRenderPassTagID == 0);
                callback(workload->getMetadata(&log));

                lastRenderPassTagID = 0;
                if (workload->isSuspending())
                {
                    lastRenderPassTagID = tagID;
                }
            }
            // Workload is a continuation
            else
            {
                assert(lastRenderPassTagID != 0);
                callback(workload->getMetadata(nullptr, lastRenderPassTagID));
                if (!workload->isSuspending())
                {
                    lastRenderPassTagID = 0;
                }
            }
        }
    }
}

}
