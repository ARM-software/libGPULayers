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
    int pipe_err = pipe(stopRequestPipe);
    if (pipe_err)
    {
        std::cout << "  - ERROR: Client pipe create failed" << std::endl;
    }

    // Create and start a worker thread
    worker = std::thread(&Receiver::runReceiver, this);
}

/** See header for documentation. */
Receiver::~Receiver()
{
    // Stop the worker thread if it's not stopped already
    if (!stopRequested)
    {
        stop();
    }

    // Close the pipes
    close(stopRequestPipe[0]);
    close(stopRequestPipe[1]);
}

/** See header for documentation. */
void Receiver::stop()
{
    // Mark the engine as stopping
    stopRequested = true;

    // Poke the pipe to wake the worker thread if it is blocked on a read
    int data = 0xdead;
    write(stopRequestPipe[1], &data, sizeof(int));

    // Join on the worker thread
    worker.join();
}

/** See header for documentation. */
void Receiver::parkMessage(
    std::shared_ptr<Message> message
) {
    std::lock_guard<std::mutex> lock(parkingLock);
    parkingBuffer.insert({ message->messageID, std::move(message) });
}

/** See header for documentation. */
void Receiver::runReceiver()
{
    while (!stopRequested)
    {
        bool dataOk;

        // Read the fixed size message header
        MessageHeader header;
        dataOk = receiveData(reinterpret_cast<uint8_t*>(&header), sizeof(header));
        if (!dataOk)
        {
            break;
        }

        // Read the a payload based on the data size in the header
        size_t payload_size = header.payloadSize;
        auto payload = std::make_unique<MessageData>(payload_size);
        dataOk = receiveData(payload->data(), payload_size);
        if (!dataOk)
        {
            break;
        }

        wakeMessage(header.messageID, std::move(payload));
    }
}

/** See header for documentation. */
void Receiver::wakeMessage(
    MessageID messageID,
    std::unique_ptr<MessageData> data
) {
    std::lock_guard<std::mutex> lock(parkingLock);

    // Handle message not found ...
    if (parkingBuffer.count(messageID) == 0)
    {
        std::cout << "  - ERROR: Cln: Message " << messageID << " not found" << std::endl;
        return;
    }

    // Extract the message and remove from the parking buffer map
    auto message = parkingBuffer[messageID];
    parkingBuffer.erase(messageID);

    // Notify the sending thread that the response is available
    message->responseData = std::move(data);
    message->notify();
}

/** See header for documentation. */
bool Receiver::receiveData(
    uint8_t* data,
    size_t dataSize
) {
    int sockfd = parent.sockfd;
    int pipefd = stopRequestPipe[0];
    int maxfd = std::max(sockfd, pipefd);

    while (dataSize)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        FD_SET(pipefd, &readfds);

        int selResp = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        // Error
        if (selResp <= 0)
        {
            return false;
        }

        // Received a stop event on the pipe so exit
        if (FD_ISSET(pipefd, &readfds))
        {
            return false;
        }

        // Otherwise keep reading bytes until we've read them all
        int readBytes = read(sockfd, data, dataSize);
        if (readBytes <= 0)
        {
            return false;
        }

        data += readBytes;
        dataSize -= readBytes;
    }

    return true;
}

}
