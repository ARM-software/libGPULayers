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
 * The implementation of the communications module unit tests.
 *
 * Note that all tests that validate server-side message receipt must end with
 * a tx_rx message to guarantee that the server received all earlier messages.
 * A normal tx message guarantees that the messages is sent before returning,
 * but does not guarantee that the server has received and processed it.
 */
#include <gtest/gtest.h>

#include "comms/comms_interface.hpp"
#include "comms/comms_module.hpp"
#include "comms/test/comms_test_server.hpp"

using namespace CommsTest;

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

std::string decode_test_payload(
    TestMessage& msg
) {
    std::string str(msg.data->begin(), msg.data->end());
    return str;
}

// ----------------------------------------------------------------------------
// Tests using a unix domain socket

/** @brief Test lifecycle with no sent messages. */
TEST(Comms, test_uds_no_data)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");
}

/** @brief Test lifecycle with a TX sent message. */
TEST(Comms, test_uds_tx_0b)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx(1, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);
}

/** @brief Test lifecycle with a TX sent message. */
TEST(Comms, test_uds_tx_nb)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a non-zero byte payload
    auto data = make_test_payload("abcd");
    client.tx(2, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 2);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(Comms, test_uds_tx_async_0b)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx_async(1, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("abcd");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);

    EXPECT_EQ(server.received[1].endpoint_id, 2);
    EXPECT_EQ(server.received[1].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[1]),"abcd");
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(Comms, test_uds_tx_async_nb)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a non-zero byte payload
    auto datab = make_test_payload("abcd");
    client.tx_async(1, std::move(datab));

    // Ensure server processes the earlier message
    datab = make_test_payload("efg");
    client.tx_rx(2, std::move(datab));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");

    EXPECT_EQ(server.received[1].endpoint_id, 2);
    EXPECT_EQ(server.received[1].data->size(), 3);
    EXPECT_EQ(decode_test_payload(server.received[1]),"efg");
}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(Comms, test_uds_tx_rx_0b)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    auto resp = client.tx_rx(1, std::move(data));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 1);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 0);
}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(Comms, test_uds_tx_rx_nb)
{
    CommsTest::CommsTestServer server("commstest");
    Comms::CommsModule client("commstest");

    // Send a non-zero byte payload
    auto datab = make_test_payload("abcd");
    auto resp = client.tx_rx(1, std::move(datab));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 1);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 4);
    EXPECT_EQ(resps,"dcba");
}

// ----------------------------------------------------------------------------
// Tests using a TCP/IP socket
/** @brief Test lifecycle with no sent messages. */
TEST(Comms, test_tcp_no_data)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);
}

/** @brief Test lifecycle with a TX sent message. */
TEST(Comms, test_tcp_tx_0b)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx(1, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);
}

/** @brief Test lifecycle with a TX sent message. */
TEST(Comms, test_tcp_tx_nb)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a non-zero byte payload
    auto data = make_test_payload("abcd");
    client.tx(2, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 2);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(Comms, test_tcp_tx_async_0b)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    client.tx_async(1, std::move(data));

    // Ensure server processes the earlier message
    data = make_test_payload("abcd");
    client.tx_rx(2, std::move(data));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);

    EXPECT_EQ(server.received[1].endpoint_id, 2);
    EXPECT_EQ(server.received[1].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[1]),"abcd");
}

/** @brief Test lifecycle with a TX_ASYNC sent message. */
TEST(Comms, test_tcp_tx_async_nb)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a non-zero byte payload
    auto datab = make_test_payload("abcd");
    client.tx_async(1, std::move(datab));

    // Ensure server processes the earlier message
    datab = make_test_payload("efg");
    client.tx_rx(2, std::move(datab));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 2);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");

    EXPECT_EQ(server.received[1].endpoint_id, 2);
    EXPECT_EQ(server.received[1].data->size(), 3);
    EXPECT_EQ(decode_test_payload(server.received[1]),"efg");
}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(Comms, test_tcp_tx_rx_0b)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a zero byte payload
    auto data = std::make_unique<std::vector<uint8_t>>();
    auto resp = client.tx_rx(1, std::move(data));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 1);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 0);

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 0);
}

/** @brief Test lifecycle with a TX_RX sent message. */
TEST(Comms, test_tcp_tx_rx_nb)
{
    CommsTest::CommsTestServer server(63412);
    Comms::CommsModule client("127.0.0.1", 63412);

    // Send a non-zero byte payload
    auto datab = make_test_payload("abcd");
    auto resp = client.tx_rx(1, std::move(datab));
    auto resps = decode_test_payload(std::move(resp));

    // Validate it was received correctly
    EXPECT_EQ(server.received.size(), 1);

    EXPECT_EQ(server.received[0].endpoint_id, 1);
    EXPECT_EQ(server.received[0].data->size(), 4);
    EXPECT_EQ(decode_test_payload(server.received[0]),"abcd");

    // Validate it was responded to correctly
    EXPECT_EQ(resps.size(), 4);
    EXPECT_EQ(resps,"dcba");
}
