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

#include "trackers/command_buffer.hpp"

#include "framework/utils.hpp"
#include "utils/misc.hpp"

#include <cassert>

namespace Tracker
{

/* See header for documentation. */
CommandBuffer::CommandBuffer(VkCommandBuffer _handle)
    : handle(_handle) {

      };

/* See header for documentation. */
void CommandBuffer::reset()
{
    oneTimeSubmit = false;
    stats.reset();
    workloads.clear();
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
    // Create a workload we can reference later
    auto workload = std::make_shared<LCSMarker>(marker);
    workloads.push_back(workload);

    // Add command to update queue debug stack on submit
    auto instr = std::make_pair(LCSOpcode::MARKER_BEGIN, workload);
    workloadCommandStream.push_back(instr);
}

/* See header for documentation. */
void CommandBuffer::debugMarkerEnd()
{
    // Add command with empty workload to update queue debug stack on submit
    auto workload = std::shared_ptr<LCSWorkload>();
    auto instr = std::make_pair(LCSOpcode::MARKER_END, workload);
    workloadCommandStream.push_back(instr);
}

/* See header for documentation. */
uint64_t CommandBuffer::renderPassBegin(const RenderPass& renderPass,
                                        uint32_t width,
                                        uint32_t height,
                                        bool resuming,
                                        bool suspending)
{
    uint64_t tagID {0};

    assert(!currentRenderPass);

    // Assign ID and update the stats tracker for new render passes only
    if (!resuming)
    {
        tagID = Tracker::LCSWorkload::assignTagID();
        stats.incRenderPassCount();
    }

    // Populate render pass with config information
    renderPassStartDrawCount = stats.getDrawCallCount();

    auto workload = std::make_shared<LCSRenderPass>(tagID, renderPass, width, height, suspending, oneTimeSubmit);

    currentRenderPass = workload;
    workloads.push_back(workload);

    // Add a command to the layer-side command stream
    auto instr = std::make_pair(LCSOpcode::RENDER_PASS, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
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

    // Add a workload to the render pass
    auto workload = std::make_shared<LCSDispatch>(tagID, xGroups, yGroups, zGroups);
    workloads.push_back(workload);

    // Add a command to the layer-side command stream
    auto instr = std::make_pair(LCSOpcode::DISPATCH, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::traceRays(int64_t xItems, int64_t yItems, int64_t zItems)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incTraceRaysCount();

    // Add a workload to the render pass
    auto workload = std::make_shared<LCSTraceRays>(tagID, xItems, yItems, zItems);
    workloads.push_back(workload);

    // Add a command to the layer-side command stream
    auto instr = std::make_pair(LCSOpcode::TRACE_RAYS, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::imageTransfer(const std::string& transferType, int64_t pixelCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incImageTransferCount();

    // Add a workload to the render pass
    auto workload = std::make_shared<LCSImageTransfer>(tagID, transferType, pixelCount);
    workloads.push_back(workload);

    // Add a command to the layer-side command stream
    auto instr = std::make_pair(LCSOpcode::IMAGE_TRANSFER, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
}

/* See header for documentation. */
uint64_t CommandBuffer::bufferTransfer(const std::string& transferType, int64_t byteCount)
{
    uint64_t tagID = Tracker::LCSWorkload::assignTagID();
    stats.incBufferTransferCount();

    // Add a workload to the render pass
    auto workload = std::make_shared<LCSBufferTransfer>(tagID, transferType, byteCount);
    workloads.push_back(workload);

    // Add a command to the layer-side command stream
    auto instr = std::make_pair(LCSOpcode::BUFFER_TRANSFER, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
}

/* See header for documentation. */
void CommandBuffer::executeCommands(CommandBuffer& secondary)
{
    // Integrate secondary statistics into the primary
    stats.mergeCounts(secondary.getStats());

    // Integrate secondary layer commands
    vecAppend(workloads, secondary.workloads);
    vecAppend(workloadCommandStream, secondary.workloadCommandStream);
}

/* See header for documentation. */
CommandPool::CommandPool(VkCommandPool _handle)
    : handle(_handle) {

      };

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
