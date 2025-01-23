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

#include <fstream>

#include "framework/utils.hpp"

#include "layer_config.hpp"
#include "version.hpp"


/* See header for documentation. */
void LayerConfig::parse_serialization_options(
    const json& config
) {
    // Decode serialization state
    json serialize = config.at("serialize");

    // Decode top level options
    bool s_all = serialize.at("all");
    bool s_none = serialize.at("none");
    bool s_queue = serialize.at("queue");

    // Decode command stream options
    json s_stream = serialize.at("commandstream");

    bool s_stream_c_pre = s_stream.at("compute").at("pre");
    bool s_stream_c_post = s_stream.at("compute").at("post");

    bool s_stream_rp_pre = s_stream.at("renderpass").at("pre");
    bool s_stream_rp_post = s_stream.at("renderpass").at("post");

    bool s_stream_rt_pre = s_stream.at("tracerays").at("pre");
    bool s_stream_rt_post = s_stream.at("tracerays").at("post");

    bool s_stream_tx_pre = s_stream.at("transfer").at("pre");
    bool s_stream_tx_post = s_stream.at("transfer").at("post");

    serialize_queues = (!s_none) && (s_all || s_queue);
    serialize_dispatch_pre = (!s_none) && (s_all || s_stream_c_pre);
    serialize_dispatch_post = (!s_none) && (s_all || s_stream_c_post);
    serialize_render_pass_pre = (!s_none) && (s_all || s_stream_rp_pre);
    serialize_render_pass_post = (!s_none) && (s_all || s_stream_rp_post);
    serialize_trace_rays_pre = (!s_none) && (s_all || s_stream_rt_pre);
    serialize_trace_rays_post = (!s_none) && (s_all || s_stream_rt_post);
    serialize_transfer_pre = (!s_none) && (s_all || s_stream_tx_pre);
    serialize_transfer_post = (!s_none) && (s_all || s_stream_tx_post);

    LAYER_LOG("Layer serialization configuration");
    LAYER_LOG("=================================");
    LAYER_LOG(" - Serialize queues: %d", serialize_queues);
    LAYER_LOG(" - Serialize compute pre: %d", serialize_dispatch_pre);
    LAYER_LOG(" - Serialize compute post: %d", serialize_dispatch_post);
    LAYER_LOG(" - Serialize render pass pre: %d", serialize_render_pass_pre);
    LAYER_LOG(" - Serialize render pass post: %d", serialize_render_pass_post);
    LAYER_LOG(" - Serialize trace rays pre: %d", serialize_trace_rays_pre);
    LAYER_LOG(" - Serialize trace rays post: %d", serialize_trace_rays_post);
    LAYER_LOG(" - Serialize transfer pre: %d", serialize_transfer_pre);
    LAYER_LOG(" - Serialize transfer post: %d", serialize_transfer_post);
}

/* See header for documentation. */
void LayerConfig::parse_shader_options(
    const json& config
) {
    // Decode serialization state
    json shader = config.at("shader");

    shader_disable_program_cache = shader.at("disable_cache");
    shader_disable_program_relaxed_precision = shader.at("disable_relaxed_precision");
    shader_enable_program_fuzz_spirv_hash = shader.at("enable_spirv_fuzz");

    LAYER_LOG("Layer shader configuration");
    LAYER_LOG("==========================");
    LAYER_LOG(" - Disable binary cache: %d", shader_disable_program_cache);
    LAYER_LOG(" - Disable relaxed precision %d", shader_disable_program_relaxed_precision);
    LAYER_LOG(" - Enable SPIR-V fuzzer: %d", shader_enable_program_fuzz_spirv_hash);
}

/* See header for documentation. */
LayerConfig::LayerConfig()
{
#ifdef __ANDROID__
    std::string file_name("/data/local/tmp/");
    file_name.append(LGL_LAYER_CONFIG);
#else
    std::string file_name(LGL_LAYER_CONFIG);
#endif


    LAYER_LOG("Trying to read config: %s", file_name.c_str());

    std::ifstream stream(file_name);
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
    catch(const json::parse_error& e)
    {
        LAYER_ERR("Failed to load layer config, using defaults");
        LAYER_ERR("Error: %s", e.what());
        return;
    }

    try
    {
        parse_serialization_options(data);
    }
    catch(const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read serialization config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }

    try
    {
        parse_shader_options(data);
    }
    catch(const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read shader config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }
}

/* See header for documentation. */
bool LayerConfig::serialize_queue() const
{
    return serialize_queues;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_compute_dispatch_pre() const
{
    return serialize_dispatch_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_compute_dispatch_post() const
{
    return serialize_dispatch_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_render_pass_pre() const
{
    return serialize_render_pass_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_render_pass_post() const
{
    return serialize_render_pass_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_trace_rays_pre() const
{
    return serialize_trace_rays_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_trace_rays_post() const
{
    return serialize_trace_rays_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_transfer_pre() const
{
    return serialize_transfer_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_transfer_post() const
{
    return serialize_transfer_post;
}

/* See header for documentation. */
bool LayerConfig::shader_disable_cache() const
{
    return shader_disable_program_cache;
}

/* See header for documentation. */
bool LayerConfig::shader_disable_relaxed_precision() const
{
    return shader_disable_program_relaxed_precision;
}

/* See header for documentation. */
bool LayerConfig::shader_fuzz_spirv_hash() const
{
    return shader_enable_program_fuzz_spirv_hash;
}
