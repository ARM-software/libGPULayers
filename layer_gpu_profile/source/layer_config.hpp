/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited
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
 * Declares the a config file to parameterize the layer.
 */

#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
 * @brief This class implements a config interface for this layer.
 *
 * The layer contains a default config, but users can provide a JSON config
 * file on the file system which is loaded at init time.
 *  - On Android the file is loaded from /data/local/tmp.
 *  - On Linux the file is loaded from the current working directory.
 */
class LayerConfig
{
public:
    /**
     * @brief Create a new layer config.
     */
    LayerConfig();

    /**
     * @brief Test if next frame should be profiled.
     *
     * @param frameID   The index of the next frame.
     *
     * @return True if profiling should be enabled, False otherwise.
     */
    bool isFrameOfInterest(uint64_t frameID) const;

private:
    /**
     * @brief Supported sampling modes.
     */
    enum SamplingMode
    {
        MODE_DISABLED,
        MODE_FRAME_LIST,
        MODE_PERIODIC_FRAME
    };

    /**
     * @brief Parse the configuration options for the sampling module.
     *
     * @param config   The JSON configuration.
     *
     * @throws json::out_of_bounds if required fields are missing.
     */
    void parseSamplingOptions(const json& config);

    /**
     * @brief The sampling mode.
     */
    SamplingMode mode {MODE_DISABLED};

    /**
     * @brief The sampling period in frames, or 0 if disabled.
     */
    uint64_t periodicFrame {0};

    /**
     * @brief The minimum frame to sample (inclusive).
     */
    uint64_t periodicMinFrame {0};

    /**
     * @brief The sampling frame list, or empty if disabled.
     */
    std::vector<uint64_t> specificFrames;
};
