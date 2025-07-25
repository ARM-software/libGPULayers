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

/**
 * @file Declares a simple comms encoder for the profile layer.
 */

#pragma once

#include "comms/comms_interface.hpp"

/**
 * @brief A simple message encoder for the profile layer comms endpoint.
 */
class ProfileComms
{
public:
    /**
     * @brief Construct a new encoder.
     *
     * @param comms   The common comms module used by all services.
     */
    ProfileComms(Comms::CommsInterface& comms);

    /**
     * @brief Send a message to the GPU profile endpoint service.
     *
     * @param message   The message to send.
     */
    void txMessage(const std::string& message);

private:
    /**
     * @brief The endpoint ID of the service, or 0 if not found.
     */
    Comms::EndpointID endpoint {0};

    /**
     * @brief The common module for network messaging.
     */
    Comms::CommsInterface& comms;
};
