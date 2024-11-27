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
 * The declaration of the external interface to the communications module.
 *
 * See documentation in @c comms_module.hpp for more information.
 */
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Comms
{

/**
 * @brief A type used for service endpoint addresses in the host.
 */
using EndpointID = uint8_t;

/**
 * @brief A type used for the message data payload.
 */
using MessageData = std::vector<uint8_t>;

/**
 * @brief A type used for service endpoint addresses in the host.
 *
 * Note that this hides the built-in registry service, which uses endpoint
 * zero, because a normaluser should not be calling it.
 */
static const EndpointID NO_ENDPOINT { 0 };

/**
 * @brief Abstract base class defining the public interface for comms.
 */
class CommsInterface
{
public:
    virtual ~CommsInterface() { }

    /**
     * @brief Is this comms module connected to a host server?
     *
     * @return Returns @c true if connected, @c false otherwise.
     */
    virtual bool is_connected() = 0;

    /**
     * @brief Get the service endpoint address for the named service.
     *
     * @param name   The name of the service.
     *
     * @return The service address, or @c NO_ENDPOINT if service is not found.
     */
    virtual EndpointID get_endpoint_id(
        const std::string& name) = 0;

    /**
     * @brief Asynchronously transmit message to the host.
     *
     * This function aims not to block, but may do so if the total size of
     * messages in the message queue exceeds a threshold size.
     *
     * @param endpoint   The address of the destination service.
     * @param data       The data to transmit.
     */
    virtual void tx_async(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data) = 0;

    /**
     * @brief Synchronously transmit message to the host.
     *
     * This function will block and wait for the message to be sent to the
     * host. This implies draining the message queue, as messages are send
     * in-order to the host.
     *
     * @param endpoint   The address of the destination service.
     * @param data       The data to transmit.
     */
    virtual void tx(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data) = 0;

    /**
     * @brief Synchronously transmit message to the host and wait for response.
     *
     * This function will block and wait for the host service to respond to
     * the message. Response timing depends on the implementation of the host
     * service, and is not guaranteed to be in order with respect to triggering
     * transmit messages.
     *
     * @param endpoint   The address of the destination service.
     * @param data       The data to transmit.
     *
     * @return The response message data payload.
     */
    virtual std::unique_ptr<MessageData> tx_rx(
        EndpointID endpoint,
        std::unique_ptr<MessageData> data) = 0;
};

}