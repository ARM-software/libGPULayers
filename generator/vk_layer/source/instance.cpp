/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2024-2025 Arm Limited
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

#include <cassert>

#include "framework/utils.hpp"

#include "instance.hpp"

/**
 * @brief The dispatch lookup for all of the created Vulkan instances.
 */
static std::unordered_map<void*, std::unique_ptr<Instance>> g_instances;

/* See header for documentation. */
const APIVersion Instance::minAPIVersion { 1, 1 };

/* See header for documentation. */
const std::vector<std::string> Instance::extraExtensions {
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME
};

/* See header for documentation. */
void Instance::store(
    VkInstance handle,
    std::unique_ptr<Instance>& instance
) {
    void* key = getDispatchKey(handle);
    g_instances.insert({ key, std::move(instance) });
}

/* See header for documentation. */
Instance* Instance::retrieve(
    VkInstance handle
) {
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_instances));
    return g_instances.at(key).get();
}

/* See header for documentation. */
Instance* Instance::retrieve(
    VkPhysicalDevice handle
) {
    void* key = getDispatchKey(handle);
    assert(isInMap(key, g_instances));
    return g_instances.at(key).get();
}

/* See header for documentation. */
void Instance::destroy(
    Instance* instance
) {
    g_instances.erase(getDispatchKey(instance->instance));
}

/* See header for documentation. */
Instance::Instance(
    VkInstance _instance,
    PFN_vkGetInstanceProcAddr _nlayerGetProcAddress
) :
    instance(_instance),
    nlayerGetProcAddress(_nlayerGetProcAddress)
{
    initDriverInstanceDispatchTable(instance, nlayerGetProcAddress, driver);
}
