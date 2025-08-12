/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022-2024 Arm Limited
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
 * The declaration of Vulkan render pass use trackers.
 *
 * Role summary
 * ============
 *
 * These trackers are used to monitor the use of a render pass.
 */

#pragma once

#include <cassert>
#include <string>
#include <vector>

#include <vulkan/vulkan.h>

namespace Tracker
{

/**
 * @brief Symbolic names of render pass attachments.
 */
enum class RenderPassAttachName
{
    COLOR0 = 0,
    COLOR1 = 1,
    COLOR2 = 2,
    COLOR3 = 3,
    COLOR4 = 4,
    COLOR5 = 5,
    COLOR6 = 6,
    COLOR7 = 7,
    DEPTH = 100,
    STENCIL = 200
};

/**
 * @brief The state tracker for a single render pass attachment.
 */
class RenderPassAttachment
{
public:
    /**
     * @brief Construct a new render pass attachment tracker.
     *
     * @param name      The name of the attachment point.
     * @param loadOp    The render pass loadOp for this attachment.
     * @param storeOp   The render pass storeOp for this attachment.
     * @param resolve   Is this a resolve attachment or the main attachment?
     */
    RenderPassAttachment(RenderPassAttachName name,
                         VkAttachmentLoadOp loadOp,
                         VkAttachmentStoreOp storeOp,
                         bool resolve);

    /**
     * @brief Get a string form of the attachment point name.
     *
     * @return The attachment point name.
     */
    std::string getAttachmentStr() const;

    /**
     * @brief Get the name of the attachment point.
     *
     * @return The attachment point name.
     */
    RenderPassAttachName getAttachmentName() const { return name; }

    /**
     * @brief Is this attachment loaded at the start of the render pass?
     *
     * @return @c true if loaded from memory.
     */
    bool isLoaded() const { return loadOp == VK_ATTACHMENT_LOAD_OP_LOAD; }

    /**
     * @brief Is this attachment stored at the end of the render pass?
     *
     * @return @c true if stored to memory.
     */
    bool isStored() const { return storeOp == VK_ATTACHMENT_STORE_OP_STORE; }

    /**
     * @brief Is this attachment a resolve attachment?
     *
     * Note that in dynamic rendering resolve attachments are implicitly not
     * loaded and stored. There are no explicit settings for this.
     *
     * @return @c true if this is a resolve attachment.
     */
    bool isResolved() const { return resolve; }

private:
    /**
     * @brief The attachment point name.
     */
    RenderPassAttachName name;

    /**
     * @brief The attachment load operation.
     */
    VkAttachmentLoadOp loadOp;

    /**
     * @brief The attachment store operation.
     */
    VkAttachmentStoreOp storeOp;

    /**
     * @brief Is this attachment a resolve attachment?
     */
    bool resolve;
};

/**
 * @brief The state tracker for a render pass.
 */
class RenderPass
{
public:
    /**
     * @brief Construct a new render pass from Vulkan 1.0-style render passes.
     *
     * @param handle       The driver handle of the render pass.
     * @param createInfo   The API context creating the render pass.
     */
    RenderPass(VkRenderPass handle, const VkRenderPassCreateInfo& createInfo);

    /**
     * @brief Construct a new render pass from Vulkan 1.0-style render passes.
     *
     * @param handle       The driver handle of the render pass.
     * @param createInfo   The API context creating the render pass.
     */
    RenderPass(VkRenderPass handle, const VkRenderPassCreateInfo2& createInfo);

    /**
     * @brief Construct a new render pass from Vulkan 1.3 dynamic rendering.
     *
     * @param createInfo   The API context starting the render pass.
     */
    RenderPass(const VkRenderingInfo& createInfo);

    /**
     * @brief Get the number of subpasses in the render pass.
     *
     * @return The number of subpasses. Always returns 1 for dynamic render
     *         passes which no longer use subpasses.
     */
    uint32_t getSubpassCount() const { return subpassCount; };

    /**
     * @brief Get the attachment list for the render pass.
     */
    const std::vector<RenderPassAttachment>& getAttachments() const { return attachments; };

private:
    /**
     * @brief The handle of the native render pass we represent.
     */
    VkRenderPass handle;

    /**
     * @brief The render pass subpass count.
     */
    uint32_t subpassCount {1};

    /**
     * @brief The render pass attachments in this render pass.
     *
     * For render passes that are using multiple sub-passes this stores the
     * the output attachments present in the final subpass.
     *
     * TODO: In future we could store more information here using the subpass
     * merging feedback extension to work out how many boxes we're going to
     * end up with on the timeline, and store attachments per merged chunk.
     */
    std::vector<RenderPassAttachment> attachments;
};

}
