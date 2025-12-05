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

    // Config queries for features

    /**
     * @brief True if config wants to serialize across queue submits.
     */
    bool feature_enable_robustBufferAccess() const;

    /**
     * @brief True if config wants to serialize queue submits with the CPU.
     */
    bool feature_disable_robustBufferAccess() const;

    // Config queries for serializer

    /**
     * @brief True if config wants to serialize across queue submits.
     */
    bool serialize_queue() const;

    /**
     * @brief True if config wants to serialize queue submits with the CPU.
     */
    bool serialize_queue_wait_idle() const;

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

    /**
     * @brief True if config wants to serialize before acceleration structure build workloads.
     */
    bool serialize_cmdstream_as_build_pre() const;

    /**
     * @brief True if config wants to serialize after acceleration structure build workloads.
     */
    bool serialize_cmdstream_as_build_post() const;

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

    // Config queries for framebuffers

    /**
     * @brief True if we disable all framebuffer compression.
     */
    bool framebuffer_disable_all_compression() const;

    /**
     * @brief True if we force default framebuffer compression.
     */
    bool framebuffer_force_default_compression() const;

    /**
     * @brief True if we force fixed rate compression.
     *
     * If non-zero, this setting specifies the minimum number of bits per
     * component allowed. If an image format cannot compress to this level
     * the next highest level that is supported will be used. If no compression
     * is available that meets this threshold then default compression will
     * be used.
     *
     * If zero, then no force is set and default compression will be used.
     */
    uint32_t framebuffer_force_fixed_rate_compression() const;


    /**
     * @brief External compression control for swapchains/images.
     * 0 = passthrough (default), 
     * 1 = strip compression on external images, 
     * 2 = strip compression on external images even without presentation, using heuristic (no guarantee!)
     */
    int disable_external_compression() const;

private:
    /**
     * @brief Parse the configuration options for the feature module.
     *
     * @param config   The JSON configuration.
     *
     * @throws json::out_of_bounds if required fields are missing.
     */
    void parse_feature_options(const json& config);

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

    /**
     * @brief Parse the configuration options for the framebuffer module.
     *
     * @param config   The JSON configuration.
     *
     * @throws json::out_of_bounds if required fields are missing.
     */
    void parse_framebuffer_options(const json& config);

private:
    /**
     * @brief True if we force enable robustBufferAccess.
     */
    bool conf_feat_robustBufferAccess_enable {false};

    /**
     * @brief True if we force disable robustBufferAccess.
     */
    bool conf_feat_robustBufferAccess_disable {false};

    /**
     * @brief True if we force serialize all queue submits.
     */
    bool conf_serialize_queues {false};

    /**
     * @brief True if we force device idle after each queue submit.
     */
    bool conf_serialize_queue_wait_idle {false};

    /**
     * @brief True if we force serialize before compute dispatches.
     */
    bool conf_serialize_dispatch_pre {false};

    /**
     * @brief True if we force serialize after compute dispatches.
     */
    bool conf_serialize_dispatch_post {false};

    /**
     * @brief True if we force serialize before render pass workloads.
     */
    bool conf_serialize_render_pass_pre {false};

    /**
     * @brief True if we force serialize after render pass workloads.
     */
    bool conf_serialize_render_pass_post {false};

    /**
     * @brief True if we force serialize before trace rays workloads.
     */
    bool conf_serialize_trace_rays_pre {false};

    /**
     * @brief True if we force serialize after trace rays workloads.
     */
    bool conf_serialize_trace_rays_post {false};

    /**
     * @brief True if we force serialize before acceleration structure build workloads.
     */
    bool conf_serialize_as_build_pre {false};

    /**
     * @brief True if we force serialize after acceleration structure build workloads.
     */
    bool conf_serialize_as_build_post {false};

    /**
     * @brief True if we force serialize before transfer workloads.
     */
    bool conf_serialize_transfer_pre {false};

    /**
     * @brief True if we force serialize after transfer workloads.
     */
    bool conf_serialize_transfer_post {false};

    /**
     * @brief True if we force disable executable binary caching.
     */
    bool conf_shader_disable_program_cache {false};

    /**
     * @brief True if we force remove use of relaxed precision decoration.
     */
    bool conf_shader_disable_relaxed_precision {false};

    /**
     * @brief True if we change SPIR-V to change the program hash.
     */
    bool conf_shader_enable_fuzz_spirv_hash {false};

    /**
     * @brief True if we disable all framebuffer compression.
     *
     * This has precedence over default compression and forcing fixed rate
     * compression.
     */
    bool conf_framebuffer_disable_compression {false};

    /**
     * @brief True if we for all compression to default framebuffer compression.
     *
     * This has precedence over forcing fixed rate compression.
     */
    bool conf_framebuffer_force_default_compression {false};

    /**
     * @brief True if we force fixed rate compression.
     *
     * If non-zero, this setting specifies the minimum number of bits per
     * component allowed. If an image format cannot compress to this level
     * the next highest level that is supported will be used. If no compression
     * is available that meets this threshold then default compression will
     * be used.
     *
     * If zero, then no force is set and default compression will be used.
     */
    uint32_t conf_framebuffer_force_fixed_rate_compression {0};

    /**
     * @brief Forces disabling external compression.
     *
     * 0 = Perform no operation, passthrough.
     * 1 = Force disable external compression, requires image presentation.
     * 2 = Force disable external compression also without.
     * presentation, requires only the use of vkCreateImage.
     * 
     * WARNING! Currently implemented as an heuristic.
     */
    int conf_disable_external_compression {0};

};
