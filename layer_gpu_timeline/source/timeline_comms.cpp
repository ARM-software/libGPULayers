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

#include "timeline_comms.hpp"

#include "timeline_protobuf_encoder.hpp"

#include <memory>

/* See header for documentation. */
TimelineComms::TimelineComms(Comms::CommsInterface& _comms)
    : comms(_comms)
{
    if (comms.isConnected())
    {
        endpoint = comms.getEndpointID("GPUTimeline");

        TimelineProtobufEncoder::emitHeaderMessage(*this);
    }
}

/* See header for documentation. */
void TimelineComms::txMessage(Comms::MessageData&& message)
{
    // Message endpoint is not available
    if (endpoint == 0)
    {
        return;
    }

    auto data = std::make_unique<Comms::MessageData>(std::move(message));
    comms.txAsync(endpoint, std::move(data));
}
