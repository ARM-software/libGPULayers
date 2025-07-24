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
 * Defines the a config file to parameterize the layer.
 */

#include "layer_config.hpp"

#include "framework/utils.hpp"
#include "utils/misc.hpp"
#include "version.hpp"

#include <fstream>
#include <sstream>
#include <vector>

#include <vulkan/vulkan.h>

/* See header for documentation. */
void LayerConfig::parseSamplingOptions(const json& config)
{
    // Decode top level options
    std::string rawMode = config.at("sample_mode");

    if (rawMode == "disabled")
    {
        mode = MODE_DISABLED;
    }
    else if (rawMode == "periodic_frame")
    {
        mode = MODE_PERIODIC_FRAME;
        periodicFrame = config.at("periodic_frame");
    }
    else if (rawMode == "frame_list")
    {
        mode = MODE_FRAME_LIST;
        specificFrames = config.at("frame_list").get<std::vector<uint64_t>>();
    }
    else
    {
        LAYER_ERR("Unknown counter sample_mode: %s", rawMode.c_str());
        rawMode = "disabled";
    }

    LAYER_LOG("Layer sampling configuration");
    LAYER_LOG("============================");
    LAYER_LOG(" - Sample mode: %s", rawMode.c_str());

    if (mode == MODE_PERIODIC_FRAME)
    {
        LAYER_LOG(" - Frame period: %" PRIu64, periodicFrame);
    }
    else if (mode == MODE_FRAME_LIST)
    {
        std::stringstream result;
        std::copy(specificFrames.begin(), specificFrames.end(), std::ostream_iterator<uint64_t>(result, " "));
        LAYER_LOG(" - Frames: %s", result.str().c_str());
    }
}

/* See header for documentation. */
LayerConfig::LayerConfig()
{
#ifdef __ANDROID__
    std::string fileName("/data/local/tmp/");
    fileName.append(LGL_LAYER_CONFIG);
#else
    std::string fileName(LGL_LAYER_CONFIG);
#endif

    LAYER_LOG("Trying to read config: %s", fileName.c_str());

    std::ifstream stream(fileName);
    if (!stream)
    {
        LAYER_LOG("Failed to open layer config, using defaults");
        return;
    }

    json data;

    try
    {
        data = json::parse(stream);
    }
    catch (const json::parse_error& e)
    {
        LAYER_ERR("Failed to load layer config, using defaults");
        LAYER_ERR("Error: %s", e.what());
        return;
    }

    try
    {
        parseSamplingOptions(data);
    }
    catch (const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read feature config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }
}

/* See header for documentation. */
bool LayerConfig::isFrameOfInterest(
    uint64_t frameID
) const {
    switch(mode)
    {
    case MODE_DISABLED:
        return false;
    case MODE_PERIODIC_FRAME:
        return (frameID % periodicFrame) == 0;
    case MODE_FRAME_LIST:
        return isIn(frameID, specificFrames);
    }

    // Should never reach here
    return false;
}

