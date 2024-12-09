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
 * \file
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
 * @brief The state tracker for a render pass.
 */
class RenderPassAttachment
{
public:
    RenderPassAttachment(
        RenderPassAttachName name,
        VkAttachmentLoadOp loadOp,
        VkAttachmentStoreOp storeOp,
        bool resolve);

    std::string getAttachmentStr() const
    {
        switch(name)
        {
        case RenderPassAttachName::COLOR0:
            return "C0";
        case RenderPassAttachName::COLOR1:
            return "C1";
        case RenderPassAttachName::COLOR2:
            return "C2";
        case RenderPassAttachName::COLOR3:
            return "C3";
        case RenderPassAttachName::COLOR4:
            return "C4";
        case RenderPassAttachName::COLOR5:
            return "C5";
        case RenderPassAttachName::COLOR6:
            return "C6";
        case RenderPassAttachName::COLOR7:
            return "C7";
        case RenderPassAttachName::DEPTH:
            return "D";
        case RenderPassAttachName::STENCIL:
            return "S";
        default:
            assert(false);
        }

        return "U";
    }

    bool isLoaded() const
    {
        return loadOp == VK_ATTACHMENT_LOAD_OP_LOAD;
    }

    bool isStored() const
    {
        return storeOp ==  VK_ATTACHMENT_STORE_OP_STORE;
    }

    bool isResolved() const
    {
        return resolve;
    }

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
    RenderPass(
        VkRenderPass handle,
        const VkRenderPassCreateInfo& createInfo);

    RenderPass(
        VkRenderPass handle,
        const VkRenderPassCreateInfo2& createInfo);

    RenderPass(
        const VkRenderingInfo& createInfo);

    uint32_t getSubpassCount() const
    {
        return subpassCount;
    };

    const std::vector<RenderPassAttachment>& getAttachments() const
    {
        return attachments;
    };

private:
    /**
     * @brief The handle of the native render pass we represent.
     */
    VkRenderPass handle;

    /**
     * @brief The render pass subpass count.
     */
    uint32_t subpassCount { 1 };

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
