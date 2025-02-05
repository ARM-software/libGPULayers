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

#include "device.hpp"
#include "framework/device_dispatch_table.hpp"

#include <map>
#include <mutex>

extern std::mutex g_vulkanLock;

// Opcode IDs for interesting SPIR-V opcodes
static const uint32_t SPIRV_OPCODE_OPDECORATE {71};
static const uint32_t SPIRV_OPCODE_OPMEMBERDECORATE {72};
static const uint32_t SPIRV_OPCODE_OPDECORATEID {332};
static const uint32_t SPIRV_OPCODE_OPDECORATESTRING {5632};
static const uint32_t SPIRV_OPCODE_OPMEMBERDECORATESTRING {5633};

// Map of decorate opcodes and the word offset of the decoration ID
static const std::map<uint32_t, size_t> SPIRV_DECORATE_OPCODES {
    {SPIRV_OPCODE_OPDECORATE, 2},
    {SPIRV_OPCODE_OPMEMBERDECORATE, 3},
    {SPIRV_OPCODE_OPDECORATEID, 2},
    {SPIRV_OPCODE_OPDECORATESTRING, 2},
    {SPIRV_OPCODE_OPMEMBERDECORATESTRING, 3},
};

// Decoration IDs for interesting SPIR-V decorations
static const uint32_t SPIRV_DECORATE_RELAXED_PRECISION {0};

/**
 * @brief Modify a SPIR-V module to remove all use of relaxed precision.
 *
 * @param originalCode   The original binary.
 *
 * @return   The modified binary.
 */
static std::vector<uint32_t> remove_relaxed_precision(const std::vector<uint32_t>& originalCode)
{
    // This module assumes the input SPIR-V is valid
    std::vector<uint32_t> code;

    // Process SPIR-V header
    for (size_t i = 0; i < 5; i++)
    {
        code.push_back(originalCode[i]);
    }

    // Process SPIR-V opcode payload
    for (size_t i = 5; i < originalCode.size(); /* Increment in loop. */)
    {
        uint32_t opWord0 = originalCode[i];

        uint32_t opCode {opWord0 & 0xFFFF};
        uint32_t opWordCount {opWord0 >> 16};

        // This should never happen, but avoids infinite loop on bad input
        if (opWordCount == 0)
        {
            LAYER_ERR("SPIR-V opcode has zero length");
            break;
        }

        bool keep {true};
        if (isInMap(opCode, SPIRV_DECORATE_OPCODES))
        {
            size_t offset = SPIRV_DECORATE_OPCODES.at(opCode);
            uint32_t decoration = originalCode[i + offset];
            if (decoration == SPIRV_DECORATE_RELAXED_PRECISION)
            {
                keep = false;
            }
        }

        if (keep)
        {
            for (size_t opI = 0; opI < opWordCount; opI++)
            {
                code.push_back(originalCode[i + opI]);
            }
        }

        i += opWordCount;
    }

    // Return the modified program
    return code;
}

/**
 * @brief Modify a SPIR-V module so it functionally the same with a different hash.
 *
 * @param originalCode   The original binary.
 *
 * @return   The modified binary.
 */
static std::vector<uint32_t> fuzz_spirv(const std::vector<uint32_t>& originalCode)
{
    // This module assumes the input SPIR-V is valid
    std::vector<uint32_t> code = originalCode;

    // Opcode NOP = 1 word, Opcode ID 0
    uint32_t opNOP = (1 << 16) | 0;
    code.push_back(opNOP);

    return code;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShaderModule<user_tag>(VkDevice device,
                                                                    const VkShaderModuleCreateInfo* pCreateInfo,
                                                                    const VkAllocationCallbacks* pAllocator,
                                                                    VkShaderModule* pShaderModule)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();

    // Create a copy of the code that we can modify
    std::vector<uint32_t> code;
    code.assign(pCreateInfo->pCode, pCreateInfo->pCode + (pCreateInfo->codeSize / sizeof(uint32_t)));

    if (layer->instance->config.shader_disable_relaxed_precision())
    {
        code = remove_relaxed_precision(code);
    }

    if (layer->instance->config.shader_fuzz_spirv_hash())
    {
        code = fuzz_spirv(code);
    }

    VkShaderModuleCreateInfo newCreateInfo = *pCreateInfo;
    newCreateInfo.pCode = code.data();
    newCreateInfo.codeSize = code.size() * sizeof(uint32_t);

    return layer->driver.vkCreateShaderModule(device, &newCreateInfo, pAllocator, pShaderModule);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateShadersEXT<user_tag>(VkDevice device,
                                                                  uint32_t createInfoCount,
                                                                  const VkShaderCreateInfoEXT* pCreateInfos,
                                                                  const VkAllocationCallbacks* pAllocator,
                                                                  VkShaderEXT* pShaders)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Create copies we can modify
    std::vector<VkShaderCreateInfoEXT> newCreateInfo;
    newCreateInfo.resize(createInfoCount);

    std::vector<std::vector<uint32_t>> newCodes;
    for (uint32_t i = 0; i < createInfoCount; i++)
    {
        newCreateInfo[i] = pCreateInfos[i];

        // No preprocessing on binary shaders
        if (newCreateInfo[i].codeType != VK_SHADER_CODE_TYPE_SPIRV_EXT)
        {
            continue;
        }

        // Preprocess SPIR-V shaders
        const uint32_t* pCode = static_cast<const uint32_t*>(newCreateInfo[i].pCode);
        uint32_t codeWords = newCreateInfo[i].codeSize / sizeof(uint32_t);

        std::vector<uint32_t> newCode;
        newCode.assign(pCode, pCode + codeWords);

        if (layer->instance->config.shader_disable_relaxed_precision())
        {
            newCode = remove_relaxed_precision(newCode);
        }

        if (layer->instance->config.shader_fuzz_spirv_hash())
        {
            newCode = fuzz_spirv(newCode);
        }

        // Patch the descriptors
        newCodes.push_back(std::move(newCode));
        newCreateInfo[i].pCode = newCodes[newCodes.size() - 1].data();
        newCreateInfo[i].codeSize = newCodes[newCodes.size() - 1].size() * sizeof(uint32_t);
    }

    // Release the lock to call into the driver
    lock.unlock();
    auto result = layer->driver.vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders);

    // On error just return
    if ((result != VK_SUCCESS) && (result != VK_INCOMPATIBLE_SHADER_BINARY_EXT))
    {
        return result;
    }

    // If no need to fiddle just return
    if (!layer->instance->config.shader_disable_cache())
    {
        return result;
    }

    // If caching is disabled reject binaries that the driver didn't reject
    for (uint32_t i = 0; i < createInfoCount; i++)
    {
        // Shader is already invalid
        if (pShaders[i] == VK_NULL_HANDLE)
        {
            continue;
        }

        // Shader is not a binary shader
        if (pCreateInfos[i].codeType != VK_SHADER_CODE_TYPE_BINARY_EXT)
        {
            continue;
        }

        // Shader is a binary shader so delete it and tell app it failed
        layer->driver.vkDestroyShaderEXT(device, pShaders[i], pAllocator);
        pShaders[i] = VK_NULL_HANDLE;
        result = VK_INCOMPATIBLE_SHADER_BINARY_EXT;
    }

    return result;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkGetPipelineKeyKHR<user_tag>(VkDevice device,
                                                                   const VkPipelineCreateInfoKHR* pPipelineCreateInfo,
                                                                   VkPipelineBinaryKeyKHR* pPipelineKey)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // If caching is disabled then return a scrambled global key
    if (layer->instance->config.shader_disable_cache() && !pPipelineCreateInfo)
    {
        for (size_t i = 0; i < VK_MAX_PIPELINE_BINARY_KEY_SIZE_KHR; i++)
        {
            pPipelineKey->key[i] = static_cast<uint8_t>(i);
        }

        pPipelineKey->keySize = VK_MAX_PIPELINE_BINARY_KEY_SIZE_KHR;
        return VK_SUCCESS;
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkGetPipelineKeyKHR(device, pPipelineCreateInfo, pPipelineKey);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateComputePipelines<user_tag>(VkDevice device,
                                                                        VkPipelineCache pipelineCache,
                                                                        uint32_t createInfoCount,
                                                                        const VkComputePipelineCreateInfo* pCreateInfos,
                                                                        const VkAllocationCallbacks* pAllocator,
                                                                        VkPipeline* pPipelines)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    if (layer->instance->config.shader_disable_cache())
    {
        pipelineCache = VK_NULL_HANDLE;
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver
        .vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkCreateGraphicsPipelines<user_tag>(VkDevice device,
                                              VkPipelineCache pipelineCache,
                                              uint32_t createInfoCount,
                                              const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                              const VkAllocationCallbacks* pAllocator,
                                              VkPipeline* pPipelines)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    if (layer->instance->config.shader_disable_cache())
    {
        pipelineCache = VK_NULL_HANDLE;
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver
        .vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL
    layer_vkCreateRayTracingPipelinesKHR<user_tag>(VkDevice device,
                                                   VkDeferredOperationKHR deferredOperation,
                                                   VkPipelineCache pipelineCache,
                                                   uint32_t createInfoCount,
                                                   const VkRayTracingPipelineCreateInfoKHR* pCreateInfos,
                                                   const VkAllocationCallbacks* pAllocator,
                                                   VkPipeline* pPipelines)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    if (layer->instance->config.shader_disable_cache())
    {
        pipelineCache = VK_NULL_HANDLE;
    }

    // Release the lock to call into the driver
    lock.unlock();
    return layer->driver.vkCreateRayTracingPipelinesKHR(device,
                                                        deferredOperation,
                                                        pipelineCache,
                                                        createInfoCount,
                                                        pCreateInfos,
                                                        pAllocator,
                                                        pPipelines);
}
