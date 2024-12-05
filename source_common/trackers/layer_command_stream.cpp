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

#include <cassert>

#include "trackers/layer_command_stream.hpp"

namespace Tracker
{
/* See header for details. */
std::atomic<uint64_t> LCSWorkload::nextTagID { 1 };

LCSWorkload::LCSWorkload(
    uint64_t _tagID):
    tagID(_tagID)
{

}

LCSMarker::LCSMarker(
    const std::string& _label) :
    LCSWorkload(0),
    label(_label)
{

};

LCSRenderPass::LCSRenderPass(
    uint64_t _tagID,
    const RenderPass& renderPass,
    uint32_t _width,
    uint32_t _height,
    bool _suspending) :
    LCSWorkload(_tagID),
    width(_width),
    height(_height),
    suspending(_suspending)
{
    // Copy these as the renderpass object may be transient.
    subpassCount = renderPass.getSubpassCount();
    attachments = renderPass.getAttachments();
}

}
