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
 * The implementation of the communications module client-only unit tests.
 *
 * For these tests to run an instance of the real host Python server must have
 * been started for the tests to run against. These tests are semi-manual as
 * we have no way of validating what was received by the server for any
 * message other than tx_rx.
 *
 * TODO: Get the test server to echo back tx and tx_async messages in a
 * subsequent tx_rx message.
 */
#include <gtest/gtest.h>

#include "comms/comms_interface.hpp"
#include "comms/comms_module.hpp"

std::unique_ptr<Comms::MessageData> make_test_payload(
    const std::string& str
) {
    auto data = std::make_unique<Comms::MessageData>(str.begin(), str.end());
    return data;
}

std::string decode_test_payload(
    std::unique_ptr<Comms::MessageData> data
) {
    std::string str(data->begin(), data->end());
    return str;
}

// ----------------------------------------------------------------------------
// Tests using a TCP/IP socket
/** @brief Test lifecycle with no sent messages. */
TEST(CommsClient, test_tcp_no_data)
{
    Comms::CommsModule client("127.0.0.1", 63412);
}

TEST(CommsClient, test_tcp_registry)
{
    Comms::CommsModule client("127.0.0.1", 63412);
    client.get_endpoint_id("dave");
}

/** @brief Test lifecycle with a TX sent message. */
TEST(CommsClient, test_tcp_tx_0b)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx(1, std::move(data));
}

/** @brief Test lifecycle with a TX sent message. */
TEST(CommsClient, test_tcp_tx_nb)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a 4 byte payload
    auto data = make_test_payload("abcd");
    client.tx(1, std::move(data));
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(CommsClient, test_tcp_tx_async_0b)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx_async(1, std::move(data));
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(CommsClient, test_tcp_tx_async_nb)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a 4 byte payload
    auto data = make_test_payload("abcd");
    client.tx_async(1, std::move(data));
}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(CommsClient, test_tcp_tx_rx_0b)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    auto resp = client.tx_rx(1, std::move(data));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 0);

}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(CommsClient, test_tcp_tx_rx_nb)
{
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a 4 byte payload
    auto data = make_test_payload("abcd");
     auto resp = client.tx_rx(1, std::move(data));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 4);
    EXPECT_EQ(resps, "dcba");
}