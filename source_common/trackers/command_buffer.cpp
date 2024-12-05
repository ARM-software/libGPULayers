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

#include "trackers/command_buffer.hpp"
#include "framework/utils.hpp"

namespace Tracker
{

/* See header for documentation. */
CommandBuffer::CommandBuffer(
    VkCommandBuffer _handle) :
    handle(_handle)
{

};

/* See header for documentation. */
void CommandBuffer::reset()
{
    stats.reset();
    workloads.clear();
    workloadCommandStream.clear();
}

/**
 * @brief Begin a user debug marker range.
 */
void CommandBuffer::debugMarkerBegin(
    std::string marker
) {
    // Create a workload we can reference later
    auto workload = std::make_shared<LCSMarker>(marker);
    workloads.push_back(workload);

    // Add command to update queue debug stack on submit
    auto instr = std::make_pair(LCSOpcode::MARKER_BEGIN, workload);
    workloadCommandStream.push_back(instr);
}

/**
 * @brief End a user debug marker range.
 */
void CommandBuffer::debugMarkerEnd()
{
    // Add command with empty workload to update queue debug stack on submit
    auto workload = std::shared_ptr<LCSWorkload>();
    auto instr = std::make_pair(LCSOpcode::MARKER_END, workload);
    workloadCommandStream.push_back(instr);
}

/**
 * @brief End a user render pass.
 */
uint64_t CommandBuffer::renderPassBegin(
    bool resuming,
    bool suspending
) {
    uint64_t tagID { 0 };

    // Assign ID and update the stats tracker for new render passes only
    if (!resuming)
    {
        tagID = Tracker::LCSWorkload::getTagID();
        stats.incRenderPassCount();
    }

    // TODO: Populate render pass with config information
    auto workload = std::make_shared<LCSRenderPass>(
        tagID,
        suspending);
    workloads.push_back(workload);

    auto instr = std::make_pair(LCSOpcode::RENDERPASS_BEGIN, workload);
    workloadCommandStream.push_back(instr);

    return tagID;
}

/**
 * @brief End a user render pass.
 */
bool CommandBuffer::renderPassEnd()
{
    LCSWorkload* workload = workloads.back().get();
    LCSRenderPass* renderpass = dynamic_cast<LCSRenderPass*>(workload);
    assert(renderpass != nullptr);

    // TODO: Merge stats since begin into the workload object
    return renderpass->isSuspending();
}

/* See header for documentation. */
CommandPool::CommandPool(
    VkCommandPool _handle) :
    handle(_handle)
{

};

/* See header for documentation. */
CommandBuffer& CommandPool::allocateCommandBuffer(
    VkCommandBuffer commandBuffer
) {
    auto result = commandBuffers.insert({
        commandBuffer,
        std::make_unique<CommandBuffer>(commandBuffer)
    });

    // Validate that insertion worked
    assert(result.second);

    // Return the created command buffer
    return *result.first->second.get();
}

/* See header for documentation. */
void CommandPool::freeCommandBuffer(
    VkCommandBuffer commandBuffer
) {
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
