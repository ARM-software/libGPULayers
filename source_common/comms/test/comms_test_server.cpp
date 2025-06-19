/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024-2025 Arm Limited
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
 * The implementation of the communications module unit test dummy server.
 */

#include "comms/test/comms_test_server.hpp"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace CommsTest
{

/* See header for documentation. */
CommsTestServer::CommsTestServer(const std::string& domainAddress)
{
    int pipeErr = pipe(stopRequestPipe);
    if (pipeErr)
    {
        std::cout << "  - ERROR: Svr pipe create failed" << std::endl;
        return;
    }

    listenSockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listenSockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket create failed" << std::endl;
        return;
    }

    // Build the address to listen on
    struct sockaddr_un servAddr
    {
    };
    servAddr.sun_family = AF_UNIX;

    // Copy the domain address, inserting leading NUL needed for abstract UDS
    std::strcpy(servAddr.sun_path + 1, domainAddress.c_str());
    servAddr.sun_path[0] = '\0';

    // Bind the socket to the address
    int bindErr = bind(listenSockfd,
                       reinterpret_cast<const struct sockaddr*>(&servAddr),
                       offsetof(struct sockaddr_un, sun_path) + domainAddress.size() + 1);
    if (bindErr)
    {
        std::cout << "  - ERROR: Svr socket bind failed" << std::endl;
        close(listenSockfd);
        listenSockfd = -1;
        return;
    }

    // Listen on the socket
    int listenErr = listen(listenSockfd, 5);
    if (listenErr)
    {
        std::cout << "  - ERROR: Svr socket listen failed" << std::endl;
        close(listenSockfd);
        listenSockfd = -1;
        return;
    }

    // Create and start a worker thread so we can respond while the test
    // thread is blocked waiting for a response to a tx_rx message
    worker = std::thread(&CommsTestServer::runServer, this);
}

/* See header for documentation. */
CommsTestServer::CommsTestServer(int port)
{
    int pipeErr = pipe(stopRequestPipe);
    if (pipeErr)
    {
        std::cout << "  - ERROR: Svr pipe create failed" << std::endl;
        return;
    }

    listenSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket create failed" << std::endl;
        return;
    }

    int reuse = 1;
    int result = setsockopt(listenSockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (result < 0)
    {
        std::cout << "  - WARN: Svr socket setsockopt failed" << std::endl;
    }

    struct sockaddr_in servAddr
    {
    };
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    int bindErr = bind(listenSockfd, reinterpret_cast<const struct sockaddr*>(&servAddr), sizeof(struct sockaddr_in));
    if (bindErr)
    {
        std::cout << "  - ERROR: Svr socket bind failed " << std::endl;
        close(listenSockfd);
        listenSockfd = -1;
        return;
    }

    // Listen on the socket
    int listenErr = listen(listenSockfd, 5);
    if (listenErr)
    {
        std::cout << "  - ERROR: Svr socket listen failed" << std::endl;
        close(listenSockfd);
        listenSockfd = -1;
        return;
    }

    // Create and start a worker thread so we can respond while the test
    // thread is blocked waiting for a response to a tx_rx message
    worker = std::thread(&CommsTestServer::runServer, this);
}

/* See header for documentation. */
CommsTestServer::~CommsTestServer()
{
    // Stop the worker thread if it's not stopped already
    if (!stopRequested)
    {
        stop();
    }

    // Close all the sockets
    if (listenSockfd > 0)
    {
        close(listenSockfd);
    }

    // Close the pipes
    close(stopRequestPipe[0]);
    close(stopRequestPipe[1]);
}

/* See header for documentation. */
void CommsTestServer::stop()
{
    // Mark the engine as stopping
    stopRequested = true;

    // Wake the worker thread if it is blocked on socket read
    int data = 0xdead;
    write(stopRequestPipe[1], &data, sizeof(int));

    // Wait for the worker to finish
    worker.join();
}

/* See header for documentation. */
void CommsTestServer::runServer()
{
    int dataSockfd = accept(listenSockfd, NULL, NULL);
    if (dataSockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket accept failed" << std::endl;
        close(listenSockfd);
        return;
    }

    while (!stopRequested)
    {
        bool dataOk;

        // Read the fixed size message header
        Comms::MessageHeader header;
        dataOk = receiveData(dataSockfd, reinterpret_cast<uint8_t*>(&header), sizeof(header));
        if (!dataOk)
        {
            break;
        }

        // Read the a payload based on the data size in the header
        size_t payloadSize = header.payloadSize;
        auto payload = std::make_unique<Comms::MessageData>(payloadSize);
        dataOk = receiveData(dataSockfd, payload->data(), payloadSize);
        if (!dataOk)
        {
            break;
        }

        // Store the message for later checking
        std::string decodedPayload(payload->begin(), payload->end());
        received.emplace_back(static_cast<Comms::EndpointID>(header.endpointID),
                              static_cast<Comms::MessageType>(header.messageType),
                              std::move(payload));

        // If this is a tx_rx message reverse payload and send it back ...
        if (header.messageType == static_cast<uint8_t>(Comms::MessageType::TX_RX))
        {
            // Response data is same size as request data so we can reuse header
            std::vector<uint8_t> response_data;
            if (decodedPayload.size() > 0)
            {
                size_t data_len = decodedPayload.size();
                for (size_t i = 0; i < data_len; i++)
                {
                    response_data.push_back(decodedPayload[data_len - i - 1]);
                }
            }

            // Send the packet header
            uint8_t* headerData = reinterpret_cast<uint8_t*>(&header);
            send_data(dataSockfd, headerData, sizeof(header));

            // Send the packet data
            send_data(dataSockfd, response_data.data(), payloadSize);
        }
    }

    close(dataSockfd);
}

/* See header for documentation. */
bool CommsTestServer::receiveData(int sockfd, uint8_t* data, size_t dataSize)
{
    int pipefd = stopRequestPipe[0];
    int maxfd = std::max(sockfd, pipefd);

    while (dataSize)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        FD_SET(pipefd, &readfds);

        int sel_resp = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        // Error
        if (sel_resp <= 0)
        {
            std::cout << "  - ERROR: Svr select failed" << std::endl;
            return false;
        }

        // Received a stop event on the pipe so exit
        if (FD_ISSET(pipefd, &readfds))
        {
            return false;
        }

        // Otherwise keep reading bytes until we've read them all
        int readBytes = read(sockfd, data, dataSize);

        // Has the client-side of the connection been closed?
        if (readBytes <= 0)
        {
            return false;
        }

        data += readBytes;
        dataSize -= readBytes;
    }

    return true;
}

/* See header for documentation. */
void CommsTestServer::send_data(int sockfd, uint8_t* data, size_t dataSize)
{
    while (dataSize)
    {
        ssize_t sentSize = send(sockfd, data, dataSize, 0);
        // An error occurred
        if (sentSize < 0)
        {
            std::cout << "  - ERROR: Svr socket send failed" << std::endl;
            return;
        }

        // Update to indicate remaining data
        dataSize -= sentSize;
        data += sentSize;
    }
}

}
