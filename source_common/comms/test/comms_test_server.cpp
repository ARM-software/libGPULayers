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
 * The implementation of the communications module unit test dummy server.
 */

#include "comms/test/comms_test_server.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace CommsTest
{

/** See header for documentation. */
CommsTestServer::CommsTestServer(
    const std::string& domain_address
) {
    int pipe_err = pipe(stop_request_pipe);
    if (pipe_err)
    {
        std::cout << "  - ERROR: Svr pipe create failed" << std::endl;
        return;
    }

    listen_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_sockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket create failed" << std::endl;
        return;
    }

    // Build the address to listen on
    struct sockaddr_un serv_addr {};
    serv_addr.sun_family = AF_UNIX;

    // Copy the domain address, inserting leading NUL needed for abstract UDS
    std::strcpy(serv_addr.sun_path + 1, domain_address.c_str());
    serv_addr.sun_path[0] = '\0';

    // Bind the socket to the address
    int bind_err = bind(
        listen_sockfd,
        reinterpret_cast<const struct sockaddr*>(&serv_addr),
        sizeof(struct sockaddr_un));
    if (bind_err)
    {
        std::cout << "  - ERROR: Svr socket bind failed" << std::endl;
        close(listen_sockfd);
        listen_sockfd = -1;
        return;
    }

    // Listen on the socket
    int listen_err = listen(listen_sockfd,  5);
    if(listen_err)
    {
        std::cout << "  - ERROR: Svr socket listen failed" << std::endl;
        close(listen_sockfd);
        listen_sockfd = -1;
        return;
    }

    // Create and start a worker thread so we can respond while the test
    // thread is blocked waiting for a response to a tx_rx message
    worker = std::thread(&CommsTestServer::run_server, this);
}

/** See header for documentation. */
CommsTestServer::CommsTestServer(
    int port
) {
    int pipe_err = pipe(stop_request_pipe);
    if (pipe_err)
    {
        std::cout << "  - ERROR: Svr pipe create failed" << std::endl;
        return;
    }

    listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket create failed" << std::endl;
        return;
    }

    int reuse = 1;
    int result = setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (result < 0)
    {
        std::cout << "  - WARN: Svr socket setsockopt failed" << std::endl;
    }

    struct sockaddr_in serv_addr {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address
    int bind_err = bind(
        listen_sockfd,
        reinterpret_cast<const struct sockaddr*>(&serv_addr),
        sizeof(struct sockaddr_in));
    if (bind_err)
    {
        std::cout << "  - ERROR: Svr socket bind failed " << std::endl;
        close(listen_sockfd);
        listen_sockfd = -1;
        return;
    }

    // Listen on the socket
    int listen_err = listen(listen_sockfd,  5);
    if(listen_err)
    {
        std::cout << "  - ERROR: Svr socket listen failed" << std::endl;
        close(listen_sockfd);
        listen_sockfd = -1;
        return;
    }

    // Create and start a worker thread so we can respond while the test
    // thread is blocked waiting for a response to a tx_rx message
    worker = std::thread(&CommsTestServer::run_server, this);
}

/** See header for documentation. */
CommsTestServer::~CommsTestServer()
{
    // Stop the worker thread if it's not stopped already
    if (!stop_requested)
    {
        stop();
    }

    // Close all the sockets
    if (listen_sockfd > 0)
    {
        close(listen_sockfd);
    }

    // Close the pipes
    close(stop_request_pipe[0]);
    close(stop_request_pipe[1]);
}

/** See header for documentation. */
void CommsTestServer::stop()
{
    // Mark the engine as stopping
    stop_requested = true;

    // Wake the worker thread if it is blocked on socket read
    int data = 0xdead;
    write(stop_request_pipe[1], &data, sizeof(int));

    // Wait for the worker to finish
    worker.join();
}

/** See header for documentation. */
void CommsTestServer::run_server()
{
    int data_sockfd = accept(listen_sockfd, NULL, NULL);
    if(data_sockfd < 0)
    {
        std::cout << "  - ERROR: Svr socket accept failed" << std::endl;
        close(listen_sockfd);
        return;
    }

    while (!stop_requested)
    {
        bool data_ok;

        // Read the fixed size message header
        Comms::MessageHeader header;
        data_ok = receive_data(data_sockfd, reinterpret_cast<uint8_t*>(&header), sizeof(header));
        if (!data_ok)
        {
            break;
        }

        // Read the a payload based on the data size in the header
        size_t payload_size = header.payload_size;
        auto payload = std::make_unique<Comms::MessageData>(payload_size);
        data_ok = receive_data(data_sockfd, payload->data(), payload_size);
        if (!data_ok)
        {
            break;
        }

        // Store the message for later checking
        std::string decoded_payload(payload->begin(), payload->end());
        received.emplace_back(
            static_cast<Comms::EndpointID>(header.endpoint_id),
            static_cast<Comms::MessageType>(header.message_type),
            std::move(payload));

        // If this is a tx_rx message reverse payload and send it back ...
        if (header.message_type == static_cast<uint8_t>(Comms::MessageType::TX_RX))
        {
            // Response data is same size as request data so we can reuse header
            std::vector<uint8_t> response_data;
            if (decoded_payload.size() > 0)
            {
                size_t data_len = decoded_payload.size();
                for (size_t i = 0; i < data_len; i++)
                {
                    response_data.push_back(decoded_payload[data_len - i - 1]);
                }
            }

            // Send the packet header
            uint8_t* header_data = reinterpret_cast<uint8_t*>(&header);
            send_data(data_sockfd, header_data, sizeof(header));

            // Send the packet data
            send_data(data_sockfd, response_data.data(), payload_size);
        }
    }

    close(data_sockfd);
}

/** See header for documentation. */
bool CommsTestServer::receive_data(
    int sockfd,
    uint8_t* data,
    size_t data_size
) {
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
            std::cout << "  - ERROR: Svr select failed" << std::endl;
            return false;
        }

        // Received a stop event on the pipe so exit
        if (FD_ISSET(pipefd, &read_fds))
        {
            return false;
        }

        // Otherwise keep reading bytes until we've read them all
        int read_bytes = read(sockfd, data, data_size);

        // Has the client-side of the connection been closed?
        if (read_bytes <= 0)
        {
            return false;
        }

        data += read_bytes;
        data_size -= read_bytes;
    }

    return true;
}

/** See header for documentation. */
void CommsTestServer::send_data(
    int sockfd,
    uint8_t* data,
    size_t data_size
) {
    while(data_size)
    {
        ssize_t sent_size = send(sockfd, data, data_size, 0);
        // An error occurred
        if (sent_size < 0)
        {
            std::cout << "  - ERROR: Svr socket send failed" << std::endl;
            return;
        }

        // Update to indicate remaining data
        data_size -= sent_size;
        data += sent_size;
    }
}

}
