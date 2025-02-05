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
#include "version.hpp"

#include <fstream>

#include <vulkan/vulkan.h>

/* See header for documentation. */
void LayerConfig::parse_serialization_options(const json& config)
{
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

    // Write after all options read from JSON so we know it parsed correctly
    conf_serialize_queues = (!s_none) && (s_all || s_queue);
    conf_serialize_dispatch_pre = (!s_none) && (s_all || s_stream_c_pre);
    conf_serialize_dispatch_post = (!s_none) && (s_all || s_stream_c_post);
    conf_serialize_render_pass_pre = (!s_none) && (s_all || s_stream_rp_pre);
    conf_serialize_render_pass_post = (!s_none) && (s_all || s_stream_rp_post);
    conf_serialize_trace_rays_pre = (!s_none) && (s_all || s_stream_rt_pre);
    conf_serialize_trace_rays_post = (!s_none) && (s_all || s_stream_rt_post);
    conf_serialize_transfer_pre = (!s_none) && (s_all || s_stream_tx_pre);
    conf_serialize_transfer_post = (!s_none) && (s_all || s_stream_tx_post);

    LAYER_LOG("Layer serialization configuration");
    LAYER_LOG("=================================");
    LAYER_LOG(" - Serialize queues: %d", conf_serialize_queues);
    LAYER_LOG(" - Serialize compute pre: %d", conf_serialize_dispatch_pre);
    LAYER_LOG(" - Serialize compute post: %d", conf_serialize_dispatch_post);
    LAYER_LOG(" - Serialize render pass pre: %d", conf_serialize_render_pass_pre);
    LAYER_LOG(" - Serialize render pass post: %d", conf_serialize_render_pass_post);
    LAYER_LOG(" - Serialize trace rays pre: %d", conf_serialize_trace_rays_pre);
    LAYER_LOG(" - Serialize trace rays post: %d", conf_serialize_trace_rays_post);
    LAYER_LOG(" - Serialize transfer pre: %d", conf_serialize_transfer_pre);
    LAYER_LOG(" - Serialize transfer post: %d", conf_serialize_transfer_post);
}

/* See header for documentation. */
void LayerConfig::parse_shader_options(const json& config)
{
    // Decode serialization state
    json shader = config.at("shader");

    bool disable_program_cache = shader.at("disable_cache");
    bool disable_relaxed_precision = shader.at("disable_relaxed_precision");
    bool enable_fuzz_spirv_hash = shader.at("enable_spirv_fuzz");

    // Write after all options read from JSON so we know it parsed correctly
    conf_shader_disable_program_cache = disable_program_cache;
    conf_shader_disable_relaxed_precision = disable_relaxed_precision;
    conf_shader_enable_fuzz_spirv_hash = enable_fuzz_spirv_hash;

    LAYER_LOG("Layer shader configuration");
    LAYER_LOG("==========================");
    LAYER_LOG(" - Disable binary cache: %d", conf_shader_disable_program_cache);
    LAYER_LOG(" - Disable relaxed precision %d", conf_shader_disable_relaxed_precision);
    LAYER_LOG(" - Enable SPIR-V hash fuzzer: %d", conf_shader_enable_fuzz_spirv_hash);
}

/* See header for documentation. */
void LayerConfig::parse_framebuffer_options(const json& config)
{
    // Decode serialization state
    json framebuffer = config.at("framebuffer");

    bool disable_all_compression = framebuffer.at("disable_compression");
    bool default_all_compression = framebuffer.at("force_default_compression");
    uint64_t force_fixed_rate_compression = framebuffer.at("force_fixed_rate_compression");

    // Apply precedence ladder
    if (disable_all_compression)
    {
        default_all_compression = false;
        force_fixed_rate_compression = 0;
    }
    else if (default_all_compression)
    {
        force_fixed_rate_compression = 0;
    }

    // Convert fixed_rate_compression into a bit mask
    uint32_t fixed_rate_mask {0};
    if (force_fixed_rate_compression > 0)
    {
        if (force_fixed_rate_compression <= 1)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_1BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 2)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_2BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 3)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_3BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 4)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_4BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 5)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_5BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 6)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_6BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 7)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_7BPC_BIT_EXT;
        }

        if (force_fixed_rate_compression <= 8)
        {
            fixed_rate_mask |= VK_IMAGE_COMPRESSION_FIXED_RATE_8BPC_BIT_EXT;
        }
    }

    // Write after all options read from JSON so we know it parsed correctly
    conf_framebuffer_disable_compression = disable_all_compression;
    conf_framebuffer_force_default_compression = default_all_compression;
    conf_framebuffer_force_fixed_rate_compression = fixed_rate_mask;

    LAYER_LOG("Layer framebuffer configuration");
    LAYER_LOG("===============================");
    LAYER_LOG(" - Disable framebuffer compression: %d", conf_framebuffer_disable_compression);
    LAYER_LOG(" - Force default framebuffer compression: %d", conf_framebuffer_force_default_compression);
    LAYER_LOG(" - Force fixed rate compression: %lu bpc", force_fixed_rate_compression);
    LAYER_LOG(" - Force fixed rate compression mask: %08x", conf_framebuffer_force_fixed_rate_compression);
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
    catch (const json::parse_error& e)
    {
        LAYER_ERR("Failed to load layer config, using defaults");
        LAYER_ERR("Error: %s", e.what());
        return;
    }

    try
    {
        parse_serialization_options(data);
    }
    catch (const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read serialization config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }

    try
    {
        parse_shader_options(data);
    }
    catch (const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read shader config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }

    try
    {
        parse_framebuffer_options(data);
    }
    catch (const json::out_of_range& e)
    {
        LAYER_ERR("Failed to read framebuffer config, using defaults");
        LAYER_ERR("Error: %s", e.what());
    }
}

/* See header for documentation. */
bool LayerConfig::serialize_queue() const
{
    return conf_serialize_queues;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_compute_dispatch_pre() const
{
    return conf_serialize_dispatch_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_compute_dispatch_post() const
{
    return conf_serialize_dispatch_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_render_pass_pre() const
{
    return conf_serialize_render_pass_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_render_pass_post() const
{
    return conf_serialize_render_pass_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_trace_rays_pre() const
{
    return conf_serialize_trace_rays_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_trace_rays_post() const
{
    return conf_serialize_trace_rays_post;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_transfer_pre() const
{
    return conf_serialize_transfer_pre;
}

/* See header for documentation. */
bool LayerConfig::serialize_cmdstream_transfer_post() const
{
    return conf_serialize_transfer_post;
}

/* See header for documentation. */
bool LayerConfig::shader_disable_cache() const
{
    return conf_shader_disable_program_cache;
}

/* See header for documentation. */
bool LayerConfig::shader_disable_relaxed_precision() const
{
    return conf_shader_disable_relaxed_precision;
}

/* See header for documentation. */
bool LayerConfig::shader_fuzz_spirv_hash() const
{
    return conf_shader_enable_fuzz_spirv_hash;
}

/* See header for documentation. */
bool LayerConfig::framebuffer_disable_all_compression() const
{
    return conf_framebuffer_disable_compression;
}

/* See header for documentation. */
bool LayerConfig::framebuffer_force_default_compression() const
{
    return conf_framebuffer_force_default_compression;
}

/* See header for documentation. */
uint32_t LayerConfig::framebuffer_force_fixed_rate_compression() const
{
    return conf_framebuffer_force_fixed_rate_compression;
}
