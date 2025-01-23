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

    // Config queries for serializer

    /**
     * @brief True if config wants to serialize before compute workloads.
     */
    bool serialize_queue() const;

    /**
     * @brief True if config wants to serialize before compute workloads.
     */
    bool serialize_cmdstream_compute_dispatch_pre() const;

    /**
     * @brief True if config wants to serialize after compute workloads.
     */
    bool serialize_cmdstream_compute_dispatch_post() const;

    /**
     * @brief True if config wants to serialize before render pass workloads.
     */
    bool serialize_cmdstream_render_pass_pre() const;

    /**
     * @brief True if config wants to serialize after render pass workloads.
     */
    bool serialize_cmdstream_render_pass_post() const;

    /**
     * @brief True if config wants to serialize before trace rays workloads.
     */
    bool serialize_cmdstream_trace_rays_pre() const;

    /**
     * @brief True if config wants to serialize after trace rays workloads.
     */
    bool serialize_cmdstream_trace_rays_post() const;

    /**
     * @brief True if config wants to serialize before transfer workloads.
     */
    bool serialize_cmdstream_transfer_pre() const;

    /**
     * @brief True if config wants to serialize after transfer workloads.
     */
    bool serialize_cmdstream_transfer_post() const;

    // Config queries for shaders

    /**
     * @brief True if config wants to disable shader caching.
     */
    bool shader_disable_cache() const;

    /**
     * @brief True if config wants to disable use of relaxed precision.
     */
    bool shader_disable_relaxed_precision() const;

    /**
     * @brief True if config wants to enable SPIR-V hash fuzzing.
     */
    bool shader_fuzz_spirv_hash() const;

private:
    /**
     * @brief Parse the configuration options for the serializer.
     *
     * @param config   The JSON configuration.
     *
     * @throws json::out_of_bounds if required fields are missing.
     */
    void parse_serialization_options(const json& config);

    /**
     * @brief Parse the configuration options for the shader module.
     *
     * @param config   The JSON configuration.
     *
     * @throws json::out_of_bounds if required fields are missing.
     */
    void parse_shader_options(const json& config);

private:
    /**
     * @brief True if we force serialize across queues.
     */
    bool serialize_queues { false };

    /**
     * @brief True if we force serialize before compute dispatches.
     */
    bool serialize_dispatch_pre { false };

    /**
     * @brief True if we force serialize after compute dispatches.
     */
    bool serialize_dispatch_post { false };

    /**
     * @brief True if we force serialize before render pass workloads.
     */
    bool serialize_render_pass_pre { false };

    /**
     * @brief True if we force serialize after render pass workloads.
     */
    bool serialize_render_pass_post { false };

    /**
     * @brief True if we force serialize before trace rays workloads.
     */
    bool serialize_trace_rays_pre { false };

    /**
     * @brief True if we force serialize after trace rays workloads.
     */
    bool serialize_trace_rays_post { false };

    /**
     * @brief True if we force serialize before transfer workloads.
     */
    bool serialize_transfer_pre { false };

    /**
     * @brief True if we force serialize after transfer workloads.
     */
    bool serialize_transfer_post { false };

    /**
     * @brief True if we force disable executable binary caching.
     */
    bool shader_disable_program_cache { false };

    /**
     * @brief True if we force remove use of relaxed precision decoration.
     */
    bool shader_disable_program_relaxed_precision { false };

    /**
     * @brief True if we change SPIR-V to change the program hash.
     */
    bool shader_enable_program_fuzz_spirv_hash { false };
};
