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
#include <nlohmann/json.hpp>

#include "trackers/layer_command_stream.hpp"

using json = nlohmann::json;

namespace Tracker
{
/* See header for details. */
std::atomic<uint64_t> LCSWorkload::nextTagID { 1 };

LCSWorkload::LCSWorkload(
    uint64_t _tagID
):
    tagID(_tagID)
{

}

/* See header for details. */
LCSMarker::LCSMarker(
    const std::string& _label
) :
    LCSWorkload(0),
    label(_label)
{

};

/* See header for details. */
LCSRenderPass::LCSRenderPass(
    uint64_t _tagID,
    const RenderPass& renderPass,
    uint32_t _width,
    uint32_t _height,
    bool _suspending,
    bool _oneTimeSubmit
) :
    LCSWorkload(_tagID),
    width(_width),
    height(_height),
    suspending(_suspending),
    oneTimeSubmit(_oneTimeSubmit)
{
    // Copy these as the render pass object may be transient.
    subpassCount = renderPass.getSubpassCount();
    attachments = renderPass.getAttachments();
}

/* See header for details. */
std::string LCSRenderPass::getBeginMetadata(
    const std::string* debugLabel,
    uint64_t submitID) const
{
    // Draw count for a multi-submit command buffer cannot be reliably
    // associated with a single tagID if restartable across command buffer
    // boundaries because different command buffer submit combinations can
    // result in different draw counts for the same starting tagID.
    int64_t drawCount = static_cast<int64_t>(drawCallCount);
    if (!oneTimeSubmit && suspending)
    {
        drawCount = -1;
    }

    json metadata = {
        { "type", "renderpass" },
        { "tid", tagID },
        { "width", width },
        { "height", height },
        { "drawCallCount", drawCount }
    };

    if (submitID != 0)
    {
        metadata["sid"] = submitID;
    }

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    // Default is 1, so only store if we need it
    if (subpassCount != 1)
    {
        metadata["subpassCount"] = subpassCount;
    }

    json attachPoints = json::array();
    for (const auto& attachment : attachments)
    {
        json attachPoint {
            { "binding", attachment.getAttachmentStr() },
        };

        // Default is false, so only serialize if we need it
        if (attachment.isLoaded())
        {
            attachPoint["load"] = true;
        }

        // Default is true, so only serialize if we need it
        if (!attachment.isStored())
        {
            attachPoint["store"] = false;
        }

        // Default is false, so only serialize if we need it
        if (attachment.isResolved())
        {
            attachPoint["resolve"] = true;
        }

        attachPoints.push_back(attachPoint);
    }

    metadata["attachments"] = attachPoints;
    return metadata.dump();
}

/* See header for details. */
std::string LCSRenderPass::getContinuationMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID) const
{
    json metadata = {
        { "type", "renderpass" },
        { "tid", tagIDContinuation },
        { "drawCallCount", drawCallCount }
    };

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    if (submitID != 0)
    {
        metadata["sid"] = submitID;
    }

    return metadata.dump();
}

/* See header for details. */
std::string LCSRenderPass::getMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID) const
{
    if (tagID)
    {
        assert(tagIDContinuation == 0);
        return getBeginMetadata(debugLabel, submitID);
    }

    assert(tagIDContinuation != 0);
    return getContinuationMetadata(debugLabel, tagIDContinuation, submitID);
}

/* See header for details. */
LCSDispatch::LCSDispatch(
    uint64_t _tagID,
    int64_t _xGroups,
    int64_t _yGroups,
    int64_t _zGroups
) :
    LCSWorkload(_tagID),
    xGroups(_xGroups),
    yGroups(_yGroups),
    zGroups(_zGroups)
{

}

/* See header for details. */
std::string LCSDispatch::getMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID
) const {
    UNUSED(tagIDContinuation);
    UNUSED(submitID);

    json metadata = {
        { "type", "dispatch" },
        { "tid", tagID },
        { "xGroups", xGroups },
        { "yGroups", yGroups },
        { "zGroups", zGroups }
    };

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    return metadata.dump();
}

/* See header for details. */
LCSTraceRays::LCSTraceRays(
    uint64_t _tagID,
    int64_t _xItems,
    int64_t _yItems,
    int64_t _zItems
) :
    LCSWorkload(_tagID),
    xItems(_xItems),
    yItems(_yItems),
    zItems(_zItems)
{

}

/* See header for details. */
std::string LCSTraceRays::getMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID
) const {
    UNUSED(tagIDContinuation);
    UNUSED(submitID);

    json metadata = {
        { "type", "tracerays" },
        { "tid", tagID },
        { "xItems", xItems },
        { "yItems", yItems },
        { "zItems", zItems }
    };

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    return metadata.dump();
}

/* See header for details. */
LCSImageTransfer::LCSImageTransfer(
    uint64_t _tagID,
    const std::string& _transferType,
    int64_t _pixelCount
):
    LCSWorkload(_tagID),
    transferType(_transferType),
    pixelCount(_pixelCount)
{

}

/* See header for details. */
std::string LCSImageTransfer::getMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID
) const {
    UNUSED(tagIDContinuation);
    UNUSED(submitID);

    json metadata = {
        { "type", "imagetransfer" },
        { "tid", tagID },
        { "subtype", transferType },
        { "pixels", pixelCount }
    };

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    return metadata.dump();
}

/* See header for details. */
LCSBufferTransfer::LCSBufferTransfer(
    uint64_t _tagID,
    const std::string& _transferType,
    int64_t _byteCount
):
    LCSWorkload(_tagID),
    transferType(_transferType),
    byteCount(_byteCount)
{

}

/* See header for details. */
std::string LCSBufferTransfer::getMetadata(
    const std::string* debugLabel,
    uint64_t tagIDContinuation,
    uint64_t submitID
) const {
    UNUSED(tagIDContinuation);
    UNUSED(submitID);

    json metadata = {
        { "type", "buffertransfer" },
        { "tid", tagID },
        { "subtype", transferType },
        { "bytes", byteCount }
    };

    if (debugLabel && debugLabel->size())
    {
        metadata["label"] = *debugLabel;
    }

    return metadata.dump();
}

}
