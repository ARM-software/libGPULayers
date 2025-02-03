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
 * @file
 * The declaration of the communications module transmitter worker.
 */
#pragma once

#include "comms/comms_message.hpp"

#include <atomic>
#include <memory>
#include <thread>

namespace Comms
{

// Predeclare to break circular reference
class CommsModule;

/**
 * @brief The network communications transmitter component.
 */
class Transmitter
{
public:
    /**
     * @brief Construct a new transmitter and start the worker thread.
     *
     * @param parent   The parent comms module.
     */
    Transmitter(CommsModule& parent);

    /**
     * @brief Destroy this transmitter.
     *
     * This will stop the worker thread if it hasn't stopped already.
     */
    virtual ~Transmitter();

    /**
     * @brief Drain the message queue and stop the worker thread.
     */
    void stop();

private:
    /**
     * @brief Entrypoint for the worker thread.
     */
    void runTransmitter();

    /**
     * @brief Send a message on the socket.
     *
     * @param message   The message to send.
     */
    void sendMessage(const Message& message);

    /**
     * @brief Send N bytes of data to the socket.
     *
     * @param data       The data to send.
     * @param dataSize   The number of bytes in the data.
     */
    void sendData(uint8_t* data, size_t dataSize);

private:
    /**
     * @brief The parent module that owns this transmitter.
     */
    CommsModule& parent;

    /**
     * @brief The worker thread running the transmitter.
     */
    std::thread worker;

    /**
     * @brief Has the worker been asked to stop?
     */
    std::atomic<bool> stopRequested;
};

}
