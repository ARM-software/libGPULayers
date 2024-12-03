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
 * The declaration of the main communications module.
 *
 * Module summary
 * ==============
 *
 * Communications implements a message-based network communications link
 * between the layer driver in the device and a tool running on the host
 * machine.
 *
 * The host tool is the network server, and can expose multiple service
 * endpoints to the network client in the layer. All messages originate in the
 * layer, and messages are targeted at an endpoint service in the host server.
 *
 * Message types
 * -------------
 *
 * The protocol supports the following types of messages:
 *
 *   - tx_async (asynchronous transmit)
 *   - tx (synchronous transmit)
 *   - tx_rx (synchronous transmit and response receive)
 *
 * There is no support for the host pushing new messages to the layer, but
 * simple pseudo-host-driven event loops can be implement by the layer pulling
 * the next event from the host using sequences of tx_rx messages.
 *
 * Message ordering
 * ----------------
 *
 * Messages are guaranteed to be transmitted to the host in the order that they
 * were added to the transmit queue, irrespective of the endpoint address.
 * Endpoints in the host will receive the messages in this order, but behavior
 * after that is endpoint specific.
 *
 * There is no guarantee that responses to tx_rx messages are received in the
 * order of the original transmissions, although a specific endpoint may
 * guarantee that for its own messages.
 *
 * Performance
 * -----------
 *
 * This module is designed to be simple, and will process one message at a
 * time. Each message will make at least two socket send calls, one for
 * the header and one or more for the data payload. For short messages this
 * can add some overhead. Client service layers may want to implement local
 * buffering to merge multiple services messages into a single comms message.
 */

#pragma once

#include "comms/comms_interface.hpp"
#include "comms/comms_message.hpp"
#include "comms/comms_transmitter.hpp"
#include "comms/comms_receiver.hpp"
#include "utils/queue.hpp"

namespace Comms
{

/**
 * @brief The main communications module component.
 *
 * Exposes the CommsInterface to calling code.
 */
class CommsModule: public CommsInterface
{
public:
    /**
     * @brief Construct a new instance using a Unix domain socket.
     *
     * We will create an abstract domain socket, but the domain_address given
     * here must NOT include the leading NUL character needed to create an
     * abstract domain socket.
     *
     * @param domainAddress   The unix domain address to use.
     */
    CommsModule(
        const std::string& domainAddress);

    /**
     * @brief Construct a new instance using a TCP/IP socket.
     *
     * @param hostAddress   The host name or IP address to use.
     * @param port          The port number to use.
     */
    CommsModule(
        const std::string& hostAddress,
        int port);

    /**
     * @brief Close the host connection and stop all worker threads.
     *
     * Any pending transmit messages will be sent before the socket is closed,
     * but it is not guaranteed that any responses to tx_rx messages will be
     * preceived or processed.
     */
    virtual ~CommsModule();

    /** See @c comms_interface.hpp for documentation. */
    virtual bool isConnected();

    /** See @c comms_interface.hpp for documentation. */
    virtual EndpointID getEndpointID(
        const std::string& name);

    /** See @c comms_interface.hpp for documentation. */
    virtual void txAsync(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data);

    /** See @c comms_interface.hpp for documentation. */
    virtual void tx(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data);

    /** See @c comms_interface.hpp for documentation. */
    virtual std::unique_ptr<MessageData> txRx(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data);

    // Allow module internal classes to access private members
    friend class Transmitter;
    friend class Receiver;

private:
    /**
     * @brief Get the message ID to use for an outbound tx_rx message.
     *
     * @return The message ID nonce to use.
     */
    MessageID assignMessageID();

    /**
     * @brief Add a message to the end of outbound message task queue.
     *
     * @param message   The message to queue.
     */
    void enqueueMessage(
        std::shared_ptr<Message> message);

    /**
     * @brief Get the oldest message from the outbound message task queue.
     *
     * @return The message to send.
     */
    std::shared_ptr<Message> dequeueMessage();

    /**
     * @brief Get the host service endpoint list.
     *
     * @return The message to send.
     */
    void getHostServiceEndpoints();

private:
    /**
     * @brief The socket for communications.
     */
    int sockfd { -1 };

    /**
     * @brief The next message ID nonce to use.
     */
    std::atomic<MessageID> nextMessageID { 1 };

    /**
     * @brief The FIFO queue of messages to send.
     */
    TaskQueue<std::shared_ptr<Message>> messageQueue;

    /**
     * @brief The transmitter - runs with its own worker thread.
     */
    std::unique_ptr<Transmitter> transmitter;

    /**
     * @brief The receiver - runs with its own worker thread.
     */
    std::unique_ptr<Receiver> receiver;

    /**
     * @brief Lock protecting the registry.
     */
    std::mutex registryLock;

    /**
     * @brief Host endpoint registry.
     */
    std::unordered_map<std::string, EndpointID> registry;
};

}
