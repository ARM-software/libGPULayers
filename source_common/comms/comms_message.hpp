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
 * The declaration of the communication module internal message types.
 */
#pragma once

#include "../utils/queue.hpp"
#include "comms/comms_interface.hpp"

namespace Comms
{

/**
 * @brief A type used for message sequence identifiers in the protocol.
 */
using MessageID = uint64_t;

/**
 * @brief A type used for message types in the protocol.
 */
enum class MessageType : uint8_t
{
    /** Message is an asynchronous transmit. */
    TX_ASYNC = 0,
    /** Message is a synchronous transmit. */
    TX = 1,
    /** Message is a synchronous transmit and wait for receive. */
    TX_RX = 2,
    /** Message is a dummy message to unblock the transmitter thread. */
    STOP = 255
};

/**
 * @brief The packed data layout (assuming both ends are little-endian)
 */
typedef struct __attribute__((packed))
{
    uint8_t messageType;  // Is this tx_async (0), tx (1), or tx_rx (2)?
    uint8_t endpointID;   // The endpoint service address.
    uint64_t messageID;   // The unique message ID for a tx_rx pair.
    uint32_t payloadSize; // The size of the payload in bytes.
} MessageHeader;

/**
 * @brief Class representing a task in the protocol.
 */
class Message : public Task
{
public:
    /**
     * @brief Construct a new message.
     *
     * @param endpointID     The destination endpoint.
     * @param messageType    The type of the message.
     * @param messageID      The sequence ID of the message.
     * @param transmitData   The data to transmit.
     */
    Message(EndpointID endpointID,
            MessageType messageType,
            MessageID messageID,
            std::unique_ptr<MessageData> transmitData);

    /**
     * @brief The type of the message.
     */
    EndpointID endpointID;

    /**
     * @brief The type of the message.
     */
    MessageType messageType;

    /**
     * @brief The sequence ID of the message.
     *
     * Only required if @c messageType is @c TX_RX and we have to match a
     * response to a triggering message.
     */
    MessageID messageID;

    /**
     * @brief The data to transmit.
     *
     * Can be reset and data discarded once the data is transmitted.
     */
    std::unique_ptr<MessageData> transmitData;

    /**
     * @brief The data that was received.
     *
     * Only present if @c messageType is @c TX_RX and we have received a
     * response from the host.
     */
    std::unique_ptr<MessageData> responseData;
};

}
