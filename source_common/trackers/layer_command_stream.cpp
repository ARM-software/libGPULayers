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

#include "trackers/layer_command_stream.hpp"

#include <cassert>
#include <memory>

namespace Tracker
{
/* See header for details. */
std::atomic<uint64_t> LCSWorkload::nextTagID {1};

LCSWorkload::LCSWorkload(uint64_t _tagID)
    : tagID(_tagID)
{
}

/* See header for details. */
LCSRenderPassBase::LCSRenderPassBase(uint64_t _tagID, bool _suspending)
    : LCSWorkload(_tagID),
      suspending(_suspending)
{
}

/* See header for details. */
LCSRenderPass::LCSRenderPass(uint64_t _tagID,
                             const RenderPass& renderPass,
                             uint32_t _width,
                             uint32_t _height,
                             bool _suspending,
                             bool _oneTimeSubmit)
    : LCSRenderPassBase(_tagID, _suspending),
      width(_width),
      height(_height),
      oneTimeSubmit(_oneTimeSubmit)
{
    // Copy these as the render pass object may be transient.
    subpassCount = renderPass.getSubpassCount();
    attachments = renderPass.getAttachments();
}

/* See header for details. */
LCSDispatch::LCSDispatch(uint64_t _tagID, int64_t _xGroups, int64_t _yGroups, int64_t _zGroups)
    : LCSWorkload(_tagID),
      xGroups(_xGroups),
      yGroups(_yGroups),
      zGroups(_zGroups)
{
}

/* See header for details. */
LCSTraceRays::LCSTraceRays(uint64_t _tagID, int64_t _xItems, int64_t _yItems, int64_t _zItems)
    : LCSWorkload(_tagID),
      xItems(_xItems),
      yItems(_yItems),
      zItems(_zItems)
{
}

/* See header for details. */
LCSImageTransfer::LCSImageTransfer(uint64_t _tagID, const std::string& _transferType, int64_t _pixelCount)
    : LCSWorkload(_tagID),
      transferType(_transferType),
      pixelCount(_pixelCount)
{
}

/* See header for details. */
LCSBufferTransfer::LCSBufferTransfer(uint64_t _tagID, const std::string& _transferType, int64_t _byteCount)
    : LCSWorkload(_tagID),
      transferType(_transferType),
      byteCount(_byteCount)
{
}

/* See header for details. */
LCSInstructionMarkerPush::LCSInstructionMarkerPush(const std::string& _label)
    : label(std::make_shared<std::string>(_label))
{
}

}
