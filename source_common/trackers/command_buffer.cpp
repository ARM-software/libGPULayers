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

#include "trackers/command_buffer.hpp"

#include "utils/misc.hpp"

#include <cassert>

namespace Tracker
{

/* See header for documentation. */
CommandBuffer::CommandBuffer(VkCommandBuffer _handle)
    : handle(_handle) {
}

/* See header for documentation. */
void CommandBuffer::reset()
{
    oneTimeSubmit = false;
    stats.reset();
    workloadCommandStream.clear();
}

/* See header for documentation. */
void CommandBuffer::begin(bool _oneTimeSubmit)
{
    oneTimeSubmit = _oneTimeSubmit;
}

/* See header for documentation. */
void CommandBuffer::debugMarkerBegin(std::string marker)
{
    // Add command to update queue debug stack on submit
    workloadCommandStream.emplace_back(LCSInstructionMarkerPush(marker));
}

/* See header for documentation. */
void CommandBuffer::debugMarkerEnd()
{
    // Add command with empty workload to update queue debug stack on submit
    workloadCommandStream.emplace_back(LCSInstructionMarkerPop());
}

/* See header for documentation. */
uint64_t CommandBuffer::renderPassBegin(const RenderPass& renderPass,
                                        uint32_t width,
                                        uint32_t height,
                                        bool resuming,
                                        bool suspending)
{
    assert(!currentRenderPass);

    // Record the current draw call count so that the delta can be computed at
    // the end of the render pass; this gives the number of draw calls in that pass
    renderPassStartDrawCount = stats.getDrawCallCount();

    // Create the workload object and populate with config information
    if (!resuming)
    {
        // Assign ID and update the stats tracker for new render passes only
        const auto tagID = Tracker::LCSWorkload::assignTagID();
        stats.incRenderPassCount();

        // Create a new render pass object
        const auto workload =
            std::make_shared<LCSRenderPass>(tagID, renderPass, width, height, suspending, oneTimeSubmit);

        // Track the workload as it will be modified at the end of the render pass
        currentRenderPass = workload;

        // Add a command to the layer-side command stream
        workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

        return tagID;
    }
    else
    {
        // Create a render pass continuation object
        const auto workload = std::make_shared<LCSRenderPassContinuation>(suspending);

        // Track the workload as it will be modified at the end of the render pass
        currentRenderPass = workload;

        // Add a command to the layer-side command stream
        workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

        return 0;
    }
}

/* See header for documentation. */
bool CommandBuffer::renderPassEnd()
{
    assert(currentRenderPass);

    // Update stats based on what happened ...
    uint64_t endDrawCount = stats.getDrawCallCount();
    uint64_t drawCount = endDrawCount - renderPassStartDrawCount;
    currentRenderPass->setDrawCallCount(drawCount);

    // Cache the return state and clear the current render pass tracker
    bool suspending = currentRenderPass->isSuspending();
    currentRenderPass.reset();

    return suspending;
}

/* See header for documentation. */
uint64_t CommandBuffer::dispatch(int64_t xGroups, int64_t yGroups, int64_t zGroups)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incDispatchCount();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSDispatch>(tagID, xGroups, yGroups, zGroups);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::traceRays(int64_t xItems, int64_t yItems, int64_t zItems)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incTraceRaysCount();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSTraceRays>(tagID, xItems, yItems, zItems);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::imageTransfer(LCSImageTransfer::Type transferType, int64_t pixelCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incImageTransferCount();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSImageTransfer>(tagID, transferType, pixelCount);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::bufferTransfer(LCSBufferTransfer::Type transferType, int64_t byteCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incBufferTransferCount();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSBufferTransfer>(tagID, transferType, byteCount);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::accelerationStructureBuild(LCSAccelerationStructureBuild::Type buildType,
                                                   int64_t primitiveCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSAccelerationStructureBuild>(tagID, buildType, primitiveCount);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::accelerationStructureTransfer(LCSAccelerationStructureTransfer::Type transferType,
                                                      int64_t byteCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();

    // Add a workload to the command stream
    auto workload = std::make_shared<LCSAccelerationStructureTransfer>(tagID, transferType, byteCount);

    // Add a command to the layer-side command stream
    workloadCommandStream.emplace_back(LCSInstructionWorkload(workload));

    return tagID;
}

/* See header for documentation. */
void CommandBuffer::executeCommands(CommandBuffer& secondary)
{
    // Integrate secondary statistics into the primary
    stats.mergeCounts(secondary.getStats());

    // Integrate secondary layer commands
    vecAppend(workloadCommandStream, secondary.workloadCommandStream);
}

/* See header for documentation. */
CommandPool::CommandPool(VkCommandPool _handle)
    : handle(_handle) {
}

/* See header for documentation. */
CommandBuffer& CommandPool::allocateCommandBuffer(VkCommandBuffer commandBuffer)
{
    auto result = commandBuffers.insert({commandBuffer, std::make_unique<CommandBuffer>(commandBuffer)});

    // Validate that insertion worked
    assert(result.second);

    // Return the created command buffer
    return *result.first->second.get();
}

/* See header for documentation. */
void CommandPool::freeCommandBuffer(VkCommandBuffer commandBuffer)
{
    commandBuffers.erase(commandBuffer);
}

/* See header for documentation. */
void CommandPool::reset()
{
    for (auto& commandBuffer : commandBuffers)
    {
        commandBuffer.second->reset();
    }
}

}
