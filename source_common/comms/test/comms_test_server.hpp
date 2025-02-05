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
 * The definition of the communications module unit test dummy server.
 */

#pragma once

#include "comms/comms_message.hpp"

#include <atomic>
#include <string>
#include <thread>

namespace CommsTest
{

/**
 * @brief A recording of a message received by the test server.
 */
class TestMessage
{
public:
    /**
     * @brief Construct a new message.
     *
     * @param endpointID     The destination endpoint.
     * @param messageType    The type of the message.
     * @param data            The received data.
     */
    TestMessage(Comms::EndpointID endpointID, Comms::MessageType messageType, std::unique_ptr<Comms::MessageData> data)
        : endpointID(endpointID),
          messageType(messageType),
          data(std::move(data))
    {
    }

    /**
     * @brief The endpoint of the message.
     */
    Comms::EndpointID endpointID;

    /**
     * @brief The type of the message.
     */
    Comms::MessageType messageType;

    /**
     * @brief The received data.
     */
    std::unique_ptr<Comms::MessageData> data;
};

class CommsTestServer
{
public:
    /**
     * @brief Construct a new server listening on a domain socket.
     *
     * Note that the UDS address given here must exclude the leading NUL, to
     * avoid it being seen as a zero-length string literal.
     *
     * @param domainAddress   The unix domain address to use.
     */
    CommsTestServer(const std::string& domainAddress);

    /**
     * @brief Construct a new server listening on TCP/IP socket.
     *
     * @param port   The port number to use.
     */
    CommsTestServer(int port);

    /**
     * @brief Close the host connection and stop all worker threads.
     *
     * Any pending transmit messages will be sent before the socket is closed,
     * but it is not guaranteed that any responses to tx_rx messages will be
     * preceived or processed.
     */
    ~CommsTestServer();

private:
    /**
     * @brief Stop the worker thread.
     */
    void stop();

    /**
     * @brief Entrypoint for the worker thread.
     */
    void runServer();

    /**
     * @brief Receive N bytes of data from the socket.
     *
     * @param sockfd     The client connection socket.
     * @param data       The data storage to write to.
     * @param dataSize   The number of bytes expected in the message.
     *
     * @return @c true if we received a message, @c false otherwise.
     */
    bool receiveData(int sockfd, uint8_t* data, size_t dataSize);

    /**
     * @brief Send N bytes of data to the socket.
     *
     * @param sockfd     The client connection socket.
     * @param data       The data to send.
     * @param dataSize   The number of bytes in the data.
     */
    void send_data(int sockfd, uint8_t* data, size_t dataSize);

public:
    /**
     * @brief List of messages received by this test server for later checking.
     */
    std::vector<TestMessage> received;

private:
    /**
     * @brief The socket for listening for connections.
     */
    int listenSockfd {-1};

    /**
     * @brief Pipe used to unblock the read socket rather than use timeouts.
     *
     * Pipe fds are not duplex: [0] is read fd, [1] is write fd.
     */
    int stopRequestPipe[2] {-1, -1};

    /**
     * @brief The transmitter - runs with its own worker thread.
     */
    std::thread worker;

    /**
     * @brief Has the worker been asked to stop?
     */
    std::atomic<bool> stopRequested;
};

}
