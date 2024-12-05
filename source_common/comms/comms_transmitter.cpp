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
 * The implementation of the communications module transmitter worker.
 */
#include <iostream>
#include <sys/socket.h>

#include "comms/comms_transmitter.hpp"
#include "comms/comms_module.hpp"
#include "framework/utils.hpp"

namespace Comms
{

/** See header for documentation. */
Transmitter::Transmitter(
    CommsModule& parent
) : parent(parent)
{
    // Create and start a worker thread
    worker = std::thread(&Transmitter::runTransmitter, this);
}

/** See header for documentation. */
Transmitter::~Transmitter()
{
    // Stop the worker thread if it's not stopped already
    if (!stopRequested)
    {
        stop();
    }
}

/** See header for documentation. */
void Transmitter::runTransmitter()
{
    // Keep looping until we are told to stop and message queue is empty
    while (!stopRequested || !parent.messageQueue.is_empty())
    {
        auto message = parent.dequeueMessage();

        // Stop messages are just used to wake the thread so do nothing
        if (message->messageType == MessageType::STOP)
        {
            continue;
        }

        // TX_RX messages need to be parked waiting for a response before
        // we send the message to avoid a race condition
        if (message->messageType == MessageType::TX_RX)
        {
            parent.receiver->parkMessage(message);
        }

        sendMessage(*message);

        // Notify TX messages to wake up the caller
        if (message->messageType == MessageType::TX)
        {
            message->notify();
        }
    }
}

/** See header for documentation. */
void Transmitter::stop()
{
    // Mark the engine as stopping
    stopRequested = true;

    // Use a dummy message to wake worker thread if blocked on the queue
    auto stopData = std::make_unique<MessageData>();
    auto message = std::make_shared<Message>(
        0, MessageType::STOP, 0, std::move(stopData));
    parent.enqueueMessage(message);

    // Join on the worker thread
    worker.join();
}

/** See header for documentation. */
void Transmitter::sendMessage(
    const Message& message
) {
    uint8_t* data = message.transmitData->data();
    size_t dataSize = message.transmitData->size();

    MessageHeader header;
    header.messageType = static_cast<uint8_t>(message.messageType);
    header.endpointID = message.endpointID;
    header.messageID = message.messageID;
    header.payloadSize = static_cast<uint32_t>(dataSize);

    // Send the packet header
    uint8_t* headerData = reinterpret_cast<uint8_t*>(&header);
    sendData(headerData, sizeof(header));

    // Send the packet data
    sendData(data, dataSize);
}

/** See header for documentation. */
void Transmitter::sendData(
    uint8_t* data,
    size_t dataSize
) {
    while(dataSize)
    {
        ssize_t sentSize = send(parent.sockfd, data, dataSize, 0);
        // An error occurred or server disconnected
        if (sentSize < 0)
        {
            return;
        }

        // Update to indicate remaining data
        dataSize -= sentSize;
        data += sentSize;
    }
}

}
