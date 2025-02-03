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
 * The implementation of the main communications module.
 */

#include "comms_module.hpp"

#include "framework/utils.hpp"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace Comms
{

/* See header for documentation. */
CommsModule::CommsModule(const std::string& domainAddress)
{
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        LAYER_LOG("  - ERROR: Client UDS socket create failed");
        return;
    }

    struct sockaddr_un servAddr
    {
    };
    servAddr.sun_family = AF_UNIX;

    // Copy the domain address, inserting leading NUL needed for abstract UDS
    std::strcpy(servAddr.sun_path + 1, domainAddress.c_str());
    servAddr.sun_path[0] = '\0';

    int conn = connect(sockfd,
                       reinterpret_cast<const struct sockaddr*>(&servAddr),
                       offsetof(struct sockaddr_un, sun_path) + domainAddress.size() + 1);
    if (conn != 0)
    {
        LAYER_LOG("  - ERROR: Client UDS connection failed");
        close(sockfd);
        sockfd = -1;
        return;
    }

    transmitter = std::make_unique<Transmitter>(*this);
    receiver = std::make_unique<Receiver>(*this);
}

/* See header for documentation. */
CommsModule::CommsModule(const std::string& hostAddress, int port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        LAYER_LOG("  - ERROR: Client TCP socket create failed");
        return;
    }

    struct sockaddr_in servAddr
    {
    };
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = inet_addr(hostAddress.c_str());

    int conn = connect(sockfd, reinterpret_cast<const struct sockaddr*>(&servAddr), sizeof(servAddr));
    if (conn != 0)
    {
        LAYER_LOG("  - ERROR: Client TCP connection failed");
        close(sockfd);
        sockfd = -1;
        return;
    }

    transmitter = std::make_unique<Transmitter>(*this);
    receiver = std::make_unique<Receiver>(*this);
}

/* See header for documentation. */
CommsModule::~CommsModule()
{
    // Stop async worker threads before closing the socket
    // Transmitter must be shut down first
    if (transmitter)
    {
        // May take some time as any pending messages must be sent
        transmitter->stop();
    }

    if (receiver)
    {
        receiver->stop();
    }

    // Close the socket after workers have stopped
    if (sockfd >= 0)
    {
        close(sockfd);
    }
}

/* See header for documentation. */
bool CommsModule::isConnected()
{
    return sockfd >= 0;
}

/* See header for documentation. */
EndpointID CommsModule::getEndpointID(const std::string& name)
{
    std::lock_guard<std::mutex> lock(registryLock);
    if (registry.empty())
    {
        // Request the registry from the host
        auto data = std::make_unique<std::vector<uint8_t>>();
        auto resp = txRx(0, std::move(data));

        // Process the response
        while (resp->size())
        {
            // If not enough bytes to read the service header then stop
            if (resp->size() < 5)
            {
                break;
            }

            uint8_t svcId = (*resp)[0];
            size_t size = static_cast<size_t>((*resp)[4] << 24) | static_cast<size_t>((*resp)[3] << 16)
                        | static_cast<size_t>((*resp)[2] << 8) | static_cast<size_t>((*resp)[1] << 0);

            // If not enough bytes to read the service name then stop
            if (resp->size() < 5 + size)
            {
                break;
            }

            std::string svcName(resp->begin() + 5, resp->begin() + 5 + size);

            // Remove the entry we've read
            resp->erase(resp->begin(), resp->begin() + 5 + size);

            // Store the persistent registry entry
            registry[svcName] = svcId;
        }
    }

    // Service found
    try
    {
        return registry[name];
    }
    // Service not found
    catch (const std::out_of_range&)
    {
        return NO_ENDPOINT;
    }
}

/* See header for documentation. */
void CommsModule::txAsync(EndpointID endpoint, std::unique_ptr<MessageData> data)
{
    auto message = std::make_shared<Message>(endpoint, MessageType::TX_ASYNC, 0, std::move(data));

    enqueueMessage(std::move(message));
}

/* See header for documentation. */
void CommsModule::tx(EndpointID endpoint, std::unique_ptr<MessageData> data)
{
    auto message = std::make_shared<Message>(endpoint, MessageType::TX, 0, std::move(data));

    enqueueMessage(message);
    message->wait();
}

/* See header for documentation. */
std::unique_ptr<MessageData> CommsModule::txRx(EndpointID endpoint, std::unique_ptr<MessageData> data)
{
    auto message = std::make_shared<Message>(endpoint, MessageType::TX_RX, assignMessageID(), std::move(data));

    enqueueMessage(message);
    message->wait();

    return std::move(message->responseData);
}

/* See header for documentation. */
MessageID CommsModule::assignMessageID()
{
    return nextMessageID.fetch_add(1, std::memory_order_relaxed);
}

/* See header for documentation. */
void CommsModule::enqueueMessage(std::shared_ptr<Message> message)
{
    messageQueue.put(std::move(message));
}

/* See header for documentation. */
std::shared_ptr<Message> CommsModule::dequeueMessage()
{
    return messageQueue.get();
}

}
