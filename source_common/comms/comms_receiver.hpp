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
 * The declaration of the communications module receiver worker.
 */
#pragma once

#include "comms/comms_message.hpp"

#include <memory>
#include <thread>
#include <unordered_map>

namespace Comms
{

// Predeclare to break circular reference
class CommsModule;

/**
 * @brief The network communications receiver component.
 */
class Receiver
{
public:
    /**
     * @brief Construct a new receiver and start the worker thread.
     *
     * @param parent   The parent comms module.
     */
    Receiver(CommsModule& parent);

    /**
     * @brief Destroy this receiver.
     *
     * This will stop the worker thread if it hasn't stopped already.
     */
    ~Receiver();

    /**
     * @brief Stop the worker thread.
     */
    void stop();

    /**
     * @brief Park a new message waiting for a response from the host.
     *
     * @param message   The message waiting for a response.
     */
    void parkMessage(std::shared_ptr<Message> message);

private:
    /**
     * @brief Entrypoint for the worker thread.
     */
    void runReceiver();

    /**
     * @brief Wake a message with the given message ID.
     *
     * @param messageID   The message to wake.
     * @param data        The response data payload from the host.
     */
    void wakeMessage(MessageID messageID, std::unique_ptr<MessageData> data);

    /**
     * @brief Receive N bytes of data from the socket.
     *
     * @param data       The data storage to write to.
     * @param dataSize   The number of bytes expected in the message.
     *
     * @return @c true if we received a message, @c false otherwise.
     */
    bool receiveData(uint8_t* data, size_t dataSize);

private:
    /**
     * @brief The parent module that owns this receiver.
     */
    CommsModule& parent;

    /**
     * @brief The worker thread running the receiver.
     */
    std::thread worker;

    /**
     * @brief Has the worker been asked to stop?
     */
    std::atomic<bool> stopRequested;

    /**
     * @brief Pipe used to unblock the read socket rather than use timeouts.
     *
     * Pipe fds are not duplex: [0] is read fd, [1] is write fd.
     */
    int stopRequestPipe[2] {-1, -1};

    /**
     * @brief Lock protecting the parking buffer.
     */
    std::mutex parkingLock;

    /**
     * @brief Parking buffer holding messages waiting for responses.
     */
    std::unordered_map<MessageID, std::shared_ptr<Message>> parkingBuffer;
};

}
