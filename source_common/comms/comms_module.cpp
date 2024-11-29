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

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>


namespace Comms
{

/** See header for documentation. */
CommsModule::CommsModule(
    const std::string& domain_address
) {
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cout << "  - ERROR: Client socket create failed" << std::endl;
        return;
    }

    struct sockaddr_un serv_addr {};
    serv_addr.sun_family = AF_UNIX;

    // Copy the domain address, inserting leading NUL needed for abstract UDS
    std::strcpy(serv_addr.sun_path + 1, domain_address.c_str());
    serv_addr.sun_path[0] = '\0';

    int conn = connect(
        sockfd,
        reinterpret_cast<const struct sockaddr*>(&serv_addr),
        sizeof(serv_addr));
    if (conn != 0)
    {
        std::cout << "  - ERROR: Client connection failed" << std::endl;
        close(sockfd);
        sockfd = -1;
        return;
    }

    transmitter = std::make_unique<Transmitter>(*this);
    receiver = std::make_unique<Receiver>(*this);
}

/** See header for documentation. */
CommsModule::CommsModule(
    const std::string& host_address,
    int port
) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cout << "  - ERROR: Client socket create failed" << std::endl;
        return;
    }

    struct sockaddr_in serv_addr {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(host_address.c_str());

    int conn = connect(
        sockfd,
        reinterpret_cast<const struct sockaddr*>(&serv_addr),
        sizeof(serv_addr));
    if (conn != 0)
    {
        std::cout << "  - ERROR: Client connection failed" << std::endl;
        close(sockfd);
        sockfd = -1;
        return;
    }

    transmitter = std::make_unique<Transmitter>(*this);
    receiver = std::make_unique<Receiver>(*this);
}

/** See header for documentation. */
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

/** See header for documentation. */
bool CommsModule::is_connected()
{
    return sockfd >= 0;
}

/** See header for documentation. */
EndpointID CommsModule::get_endpoint_id(
    const std::string& name
) {
    std::lock_guard<std::mutex> lock(registry_lock);
    if (registry.empty())
    {
        // Request the registry from the host
        auto data = std::make_unique<std::vector<uint8_t>>();
        auto resp = tx_rx(0, std::move(data));

        // Process the response
        while (resp->size())
        {
            // If not enough bytes to read the service header then stop
            if (resp->size() < 5)
            {
                break;
            }

            uint8_t id = (*resp)[0];
            size_t size = static_cast<size_t>((*resp)[4] << 24)
                        | static_cast<size_t>((*resp)[3] << 16)
                        | static_cast<size_t>((*resp)[2] << 8)
                        | static_cast<size_t>((*resp)[1] << 0);

            // If not enough bytes to read the service name then stop
            if (resp->size() < 5 + size)
            {
                break;
            }

            std::string name(resp->begin() + 5, resp->begin() + 5 + size);

            // Remove the entry we've read
            resp->erase(resp->begin(), resp->begin() + 5 + size);

            // Store the persistent registry entry
            registry[name] = id;
        }
    }

    // Service found
    try
    {
        return registry[name];
    }
    // Service not found
    catch(std::out_of_range)
    {
        return NO_ENDPOINT;
    }
}

/** See header for documentation. */
void CommsModule::tx_async(
    EndpointID endpoint,
    std::unique_ptr<MessageData> data
) {
    auto message = std::make_shared<Message>(
        endpoint,
        MessageType::TX_ASYNC,
        0,
        std::move(data));

    enqueue_message(std::move(message));
}

/** See header for documentation. */
void CommsModule::tx(
    EndpointID endpoint,
    std::unique_ptr<MessageData> data
) {
    auto message = std::make_shared<Message>(
        endpoint,
        MessageType::TX,
        0,
        std::move(data));

    enqueue_message(message);
    message->wait();
}

/** See header for documentation. */
std::unique_ptr<MessageData> CommsModule::tx_rx(
    EndpointID endpoint,
    std::unique_ptr<MessageData> data
) {
    auto message = std::make_shared<Message>(
        endpoint,
        MessageType::TX_RX,
        assign_message_id(),
        std::move(data));

    enqueue_message(message);
    message->wait();

    return std::move(message->response_data);
}

/** See header for documentation. */
MessageID CommsModule::assign_message_id()
{
    return next_message_id.fetch_add(1, std::memory_order_relaxed);
}

/** See header for documentation. */
void CommsModule::enqueue_message(
    std::shared_ptr<Message> message
) {
    message_queue.put(std::move(message));
}

/** See header for documentation. */
std::shared_ptr<Message> CommsModule::dequeue_message()
{
    return message_queue.get();
}

}
