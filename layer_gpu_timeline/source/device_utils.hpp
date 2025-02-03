/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024 Arm Limited
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
#include "framework/utils.hpp"

#include <vulkan/vulkan.h>

/**
 * @brief Emit a start tag via a driver debug utils label.
 *
 * @param layer           The layer context for the device.
 * @param commandBuffer   The command buffer we are recording.
 * @param tagID           The tagID to emit into the label.
 */
[[maybe_unused]] static void emitStartTag(Device* layer, VkCommandBuffer commandBuffer, uint64_t tagID)
{
    // Emit the unique workload tag into the command stream
    std::string tagLabel = formatString("t%" PRIu64, tagID);
    VkDebugUtilsLabelEXT tagInfo {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pNext = nullptr,
        .pLabelName = tagLabel.c_str(),
        .color = {0.0f, 0.0f, 0.0f, 0.0f},
    };

    layer->driver.vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &tagInfo);
}
