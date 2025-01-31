/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022-2025 Arm Limited
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

#include "trackers/queue.hpp"

#include "trackers/layer_command_stream.hpp"
#include "utils/misc.hpp"

#include <cassert>
#include <variant>
#include <vector>

namespace Tracker
{
namespace
{

    /**
     * @brief A visitor implementation that processes each command stream instruction, and
     *        correctly updates the Queue's state, as well as serializing workload objects
     *        into the message data callback.
     */
    class SubmitCommandInstructionVisitor
    {
    public:
        SubmitCommandInstructionVisitor(QueueState& _queueState, std::function<void(const std::string&)> _callback)
            : queueState(_queueState),
              callback(_callback)
        {
        }

        // visitor should not be copied or moved from
        SubmitCommandInstructionVisitor(const SubmitCommandInstructionVisitor&) = delete;
        SubmitCommandInstructionVisitor(SubmitCommandInstructionVisitor&&) noexcept = delete;
        SubmitCommandInstructionVisitor& operator=(const SubmitCommandInstructionVisitor&) = delete;
        SubmitCommandInstructionVisitor& operator=(SubmitCommandInstructionVisitor&&) noexcept = delete;

        /**
         * @brief Visit a debug-label push marker instruction
         *
         * @param instruction The push instruction
         */
        void operator()(const LCSInstructionMarkerPush& instruction)
        {
            queueState.debugStack.emplace_back(instruction.getLabel());
        }

        /**
         * @brief Visit a debug-label pop marker instruction
         *
         * @param instruction The pop instruction
         */
        void operator()(const LCSInstructionMarkerPop& instruction)
        {
            UNUSED(instruction);

            queueState.debugStack.pop_back();
        }

        /**
         * @brief Visit a renderpass workload instruction
         *
         * @param instruction The workload instruction
         */
        void operator()(const LCSInstructionWorkload<LCSRenderPass>& instruction)
        {
            const auto& workload = instruction.getWorkload();
            const auto tagID = workload.getTagID();

            // Workload is a new render pass
            if (tagID > 0)
            {
                assert(queueState.lastRenderPassTagID == 0);
                callback(workload.getBeginMetadata(queueState.debugStack));

                queueState.lastRenderPassTagID = 0;
                if (workload.isSuspending())
                {
                    queueState.lastRenderPassTagID = tagID;
                }
            }
            // Workload is a continuation
            else
            {
                assert(queueState.lastRenderPassTagID != 0);
                callback(workload.getContinuationMetadata(queueState.lastRenderPassTagID));
                if (!workload.isSuspending())
                {
                    queueState.lastRenderPassTagID = 0;
                }
            }
        }

        /**
         * @brief Visit a dispatch/trace rays/image transfer/buffer transfer workload instruction
         *
         * @param instruction The workload instruction
         */
        template<typename WorkloadType>
        requires(std::is_same_v<WorkloadType, LCSDispatch> || std::is_same_v<WorkloadType, LCSTraceRays>
                 || std::is_same_v<WorkloadType, LCSImageTransfer> || std::is_same_v<WorkloadType, LCSBufferTransfer>)
        void operator()(const LCSInstructionWorkload<WorkloadType>& instruction)
        {
            const auto& workload = instruction.getWorkload();

            callback(workload.getMetadata(queueState.debugStack));
        }

    private:
        QueueState& queueState;
        std::function<void(const std::string&)> callback;
    };

}

/* See header for details. */
Queue::Queue(VkQueue _handle)
    : state(_handle) {

      };

/* See header for details. */
void Queue::runSubmitCommandStream(const std::vector<LCSInstruction>& stream,
                                   std::function<void(const std::string&)> callback)
{
    SubmitCommandInstructionVisitor visitor {state, callback};

    for (auto& instr : stream)
    {
        std::visit(visitor, instr);
    }
}

}
