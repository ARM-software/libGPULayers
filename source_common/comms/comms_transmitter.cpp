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
#include "comms_transmitter.hpp"
#include "comms_module.hpp"

#include <iostream>
#include <sys/socket.h>

namespace Comms
{

/** See header for documentation. */
Transmitter::Transmitter(
    CommsModule& parent
) : parent(parent)
{
    // Create and start a worker thread
    worker = std::thread(&Transmitter::run_transmitter, this);
}

/** See header for documentation. */
Transmitter::~Transmitter()
{
    // Stop the worker thread if it's not stopped already
    if (!stop_requested)
    {
        stop();
    }
}

/** See header for documentation. */
void Transmitter::run_transmitter()
{
    // Keep looping until we are told to stop and message queue is empty
    while (!stop_requested || !parent.message_queue.is_empty())
    {
        auto message = parent.dequeue_message();

        // Stop messages are just used to wake the thread so do nothing
        if (message->message_type == MessageType::STOP)
        {
            continue;
        }

        // TX_RX messages need to be parked waiting for a response before
        // we send the message to avoid a race condition
        if (message->message_type == MessageType::TX_RX)
        {
            parent.receiver->park_message(message);
        }

        send_message(*message);

        // Notify TX messages to wake up the caller
        if (message->message_type == MessageType::TX)
        {
            message->notify();
        }
    }
}

/** See header for documentation. */
void Transmitter::stop()
{
    // Mark the engine as stopping
    stop_requested = true;

    // Use a dummy message to wake worker thread if blocked on the queue
    auto stop_data = std::make_unique<MessageData>();
    auto message = std::make_shared<Message>(
        0, MessageType::STOP, 0, std::move(stop_data));
    parent.enqueue_message(message);

    // Join on the worker thread
    worker.join();
}

/** See header for documentation. */
void Transmitter::send_message(
    const Message& message
) {
    uint8_t* data = message.transmit_data->data();
    size_t data_size = message.transmit_data->size();

    MessageHeader header;
    header.message_type = static_cast<uint8_t>(message.message_type);
    header.endpoint_id = message.endpoint_id;
    header.message_id = message.message_id;
    header.payload_size = static_cast<uint32_t>(data_size);

    // Send the packet header
    uint8_t* header_data = reinterpret_cast<uint8_t*>(&header);
    send_data(header_data, sizeof(header));

    // Send the packet data
    send_data(data, data_size);
}

/** See header for documentation. */
void Transmitter::send_data(
    uint8_t* data,
    size_t data_size
) {
    while(data_size)
    {
        ssize_t sent_size = send(parent.sockfd, data, data_size, 0);
        // An error occurred or server disconnected
        if (sent_size < 0)
        {
            return;
        }

        // Update to indicate remaining data
        data_size -= sent_size;
        data += sent_size;
    }
}

}
