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

#include "device.hpp"
#include "device_utils.hpp"
#include "framework/device_dispatch_table.hpp"
#include "framework/utils.hpp"
#include "trackers/render_pass.hpp"

#include <mutex>

extern std::mutex g_vulkanLock;

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass<user_tag>(VkDevice device,
                                                                  const VkRenderPassCreateInfo* pCreateInfo,
                                                                  const VkAllocationCallbacks* pAllocator,
                                                                  VkRenderPass* pRenderPass)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    VkResult ret = layer->driver.vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    if (ret != VK_SUCCESS)
    {
        return ret;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto& tracker = layer->getStateTracker();
    tracker.createRenderPass(*pRenderPass, *pCreateInfo);
    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2<user_tag>(VkDevice device,
                                                                   const VkRenderPassCreateInfo2* pCreateInfo,
                                                                   const VkAllocationCallbacks* pAllocator,
                                                                   VkRenderPass* pRenderPass)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    VkResult ret = layer->driver.vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
    if (ret != VK_SUCCESS)
    {
        return ret;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto& tracker = layer->getStateTracker();
    tracker.createRenderPass(*pRenderPass, *pCreateInfo);
    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR VkResult VKAPI_CALL layer_vkCreateRenderPass2KHR<user_tag>(VkDevice device,
                                                                      const VkRenderPassCreateInfo2* pCreateInfo,
                                                                      const VkAllocationCallbacks* pAllocator,
                                                                      VkRenderPass* pRenderPass)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    // Release the lock to call into the driver
    lock.unlock();
    VkResult ret = layer->driver.vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass);
    if (ret != VK_SUCCESS)
    {
        return ret;
    }

    // Retake the lock to access layer-wide global store
    lock.lock();
    auto& tracker = layer->getStateTracker();
    tracker.createRenderPass(*pRenderPass, *pCreateInfo);
    return VK_SUCCESS;
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkDestroyRenderPass<user_tag>(VkDevice device,
                                                               VkRenderPass renderPass,
                                                               const VkAllocationCallbacks* pAllocator)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(device);

    auto& tracker = layer->getStateTracker();
    tracker.destroyRenderPass(renderPass);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkDestroyRenderPass(device, renderPass, pAllocator);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass<user_tag>(VkCommandBuffer commandBuffer,
                                                                const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                VkSubpassContents contents)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    auto& rp = tracker.getRenderPass(pRenderPassBegin->renderPass);
    uint32_t width = pRenderPassBegin->renderArea.extent.width;
    uint32_t height = pRenderPassBegin->renderArea.extent.height;

    // Notify the command buffer we are starting a new render pass
    uint64_t tagID = cb.renderPassBegin(rp, width, height);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2<user_tag>(VkCommandBuffer commandBuffer,
                                                                 const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                 const VkSubpassBeginInfo* pSubpassBeginInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    auto& rp = tracker.getRenderPass(pRenderPassBegin->renderPass);
    uint32_t width = pRenderPassBegin->renderArea.extent.width;
    uint32_t height = pRenderPassBegin->renderArea.extent.height;

    // Notify the command buffer we are starting a new render pass
    uint64_t tagID = cb.renderPassBegin(rp, width, height);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderPass2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                    const VkRenderPassBeginInfo* pRenderPassBegin,
                                                                    const VkSubpassBeginInfo* pSubpassBeginInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    auto& rp = tracker.getRenderPass(pRenderPassBegin->renderPass);
    uint32_t width = pRenderPassBegin->renderArea.extent.width;
    uint32_t height = pRenderPassBegin->renderArea.extent.height;

    // Notify the command buffer we are starting a new render pass
    uint64_t tagID = cb.renderPassBegin(rp, width, height);

    // Release the lock to call into the driver
    lock.unlock();
    emitStartTag(layer, commandBuffer, tagID);
    layer->driver.vkCmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRendering<user_tag>(VkCommandBuffer commandBuffer,
                                                               const VkRenderingInfo* pRenderingInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    bool resuming = pRenderingInfo->flags & VK_RENDERING_RESUMING_BIT;
    bool suspending = pRenderingInfo->flags & VK_RENDERING_SUSPENDING_BIT;

    // Extract metadata for later use ...
    Tracker::RenderPass rp(*pRenderingInfo);
    uint32_t width = pRenderingInfo->renderArea.extent.width;
    uint32_t height = pRenderingInfo->renderArea.extent.height;

    // Notify the command buffer we are starting a new render pass
    uint64_t tagID = cb.renderPassBegin(rp, width, height, resuming, suspending);

    // Release the lock to call into the driver
    lock.unlock();
    // Emit the label only for new render passes
    if (!resuming)
    {
        emitStartTag(layer, commandBuffer, tagID);
    }
    layer->driver.vkCmdBeginRendering(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdBeginRenderingKHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                  const VkRenderingInfo* pRenderingInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);

    bool resuming = pRenderingInfo->flags & VK_RENDERING_RESUMING_BIT;
    bool suspending = pRenderingInfo->flags & VK_RENDERING_SUSPENDING_BIT;

    // Extract metadata for later use ...
    Tracker::RenderPass rp(*pRenderingInfo);
    uint32_t width = pRenderingInfo->renderArea.extent.width;
    uint32_t height = pRenderingInfo->renderArea.extent.height;

    // Notify the command buffer we are starting a new render pass
    uint64_t tagID = cb.renderPassBegin(rp, width, height, resuming, suspending);

    // Release the lock to call into the driver
    lock.unlock();
    // Emit the label only for new render passes
    if (!resuming)
    {
        emitStartTag(layer, commandBuffer, tagID);
    }
    layer->driver.vkCmdBeginRenderingKHR(commandBuffer, pRenderingInfo);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass<user_tag>(VkCommandBuffer commandBuffer)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Update the layer command stream in the tracker
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    cb.renderPassEnd();

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass(commandBuffer);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2<user_tag>(VkCommandBuffer commandBuffer,
                                                               const VkSubpassEndInfo* pSubpassEndInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderPass2KHR<user_tag>(VkCommandBuffer commandBuffer,
                                                                  const VkSubpassEndInfo* pSubpassEndInfo)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
    layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRendering<user_tag>(VkCommandBuffer commandBuffer)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Update the layer command stream in the tracker
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    bool suspending = cb.renderPassEnd();

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRendering(commandBuffer);
    if (!suspending)
    {
        layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
    }
}

/* See Vulkan API for documentation. */
template<>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdEndRenderingKHR<user_tag>(VkCommandBuffer commandBuffer)
{
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock {g_vulkanLock};
    auto* layer = Device::retrieve(commandBuffer);

    // Update the layer command stream in the tracker
    auto& tracker = layer->getStateTracker();
    auto& cb = tracker.getCommandBuffer(commandBuffer);
    bool suspending = cb.renderPassEnd();

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdEndRenderingKHR(commandBuffer);
    if (!suspending)
    {
        layer->driver.vkCmdEndDebugUtilsLabelEXT(commandBuffer);
    }
}
