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
 * The implementation of the communications module receiver worker.
 */

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>

#include "comms/comms_receiver.hpp"
#include "comms_module.hpp"

namespace Comms
{
/** See header for documentation. */
Receiver::Receiver(
    CommsModule& parent
) : parent(parent)
{
    int pipe_err = pipe(stop_request_pipe);
    if (pipe_err)
    {
        std::cout << "  - ERROR: Client pipe create failed" << std::endl;
    }

    // Create and start a worker thread
    worker = std::thread(&Receiver::run_receiver, this);
}

/** See header for documentation. */
Receiver::~Receiver()
{
    // Stop the worker thread if it's not stopped already
    if (!stop_requested)
    {
        stop();
    }

    // Close the pipes
    close(stop_request_pipe[0]);
    close(stop_request_pipe[1]);
}

/** See header for documentation. */
void Receiver::stop()
{
    // Mark the engine as stopping
    stop_requested = true;

    // Poke the pipe to wake the worker thread if it is blocked on a read
    int data = 0xdead;
    write(stop_request_pipe[1], &data, sizeof(int));

    // Join on the worker thread
    worker.join();
}

/** See header for documentation. */
void Receiver::park_message(
    std::shared_ptr<Message> message
) {
    std::lock_guard<std::mutex> lock(parking_lock);
    parking_buffer.insert({ message->message_id, std::move(message) });
}

/** See header for documentation. */
void Receiver::run_receiver()
{
    while (!stop_requested)
    {
        bool data_ok;

        // Read the fixed size message header
        MessageHeader header;
        data_ok = receive_data(reinterpret_cast<uint8_t*>(&header), sizeof(header));
        if (!data_ok)
        {
            break;
        }

        // Read the a payload based on the data size in the header
        size_t payload_size = header.payload_size;
        auto payload = std::make_unique<MessageData>(payload_size);
        data_ok = receive_data(payload->data(), payload_size);
        if (!data_ok)
        {
            break;
        }

        wake_message(header.message_id, std::move(payload));
    }
}

/** See header for documentation. */
void Receiver::wake_message(
    MessageID message_id,
    std::unique_ptr<MessageData> data
) {
    std::lock_guard<std::mutex> lock(parking_lock);

    // Handle message not found ...
    if (parking_buffer.count(message_id) == 0)
    {
        std::cout << "  - ERROR: Cln: Message " << message_id << " not found" << std::endl;
        return;
    }

    // Extract the message and remove from the parking buffer map
    auto message = parking_buffer[message_id];
    parking_buffer.erase(message_id);

    // Notify the sending thread that the response is available
    message->response_data = std::move(data);
    message->notify();
}

/** See header for documentation. */
bool Receiver::receive_data(
    uint8_t* data,
    size_t data_size
) {
    int sockfd = parent.sockfd;
    int pipefd = stop_request_pipe[0];
    int max_fd = std::max(sockfd, pipefd);

    while (data_size)
    {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        FD_SET(pipefd, &read_fds);

        int sel_resp = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        // Error
        if (sel_resp <= 0)
        {
            return false;
        }

        // Received a stop event on the pipe so exit
        if (FD_ISSET(pipefd, &read_fds))
        {
            return false;
        }

        // Otherwise keep reading bytes until we've read them all
        int read_bytes = read(sockfd, data, data_size);
        if (read_bytes <= 0)
        {
            return false;
        }

        data += read_bytes;
        data_size -= read_bytes;
    }

    return true;
}

}
