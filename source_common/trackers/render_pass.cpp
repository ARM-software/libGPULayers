/*
 * SPDX-License-Identifier: MIT
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022-2025 Arm Limited
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

#include "trackers/render_pass.hpp"

#include <cassert>

namespace Tracker
{

/* See header for details. */
RenderPassAttachment::RenderPassAttachment(RenderPassAttachName _name,
                                           VkAttachmentLoadOp _loadOp,
                                           VkAttachmentStoreOp _storeOp,
                                           bool _resolve)
    : name(_name),
      loadOp(_loadOp),
      storeOp(_storeOp),
      resolve(_resolve)
{
}

/* See header for details. */
std::string RenderPassAttachment::getAttachmentStr() const
{
    switch (name)
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

/* See header for details. */
RenderPass::RenderPass(VkRenderPass _handle, const VkRenderPassCreateInfo& createInfo)
    : handle(_handle)
{
    subpassCount = createInfo.subpassCount;

    auto& lastSubpass = createInfo.pSubpasses[subpassCount - 1];

    // Color attachments
    for (uint32_t i = 0; i < lastSubpass.colorAttachmentCount; i++)
    {
        auto& attachRef = lastSubpass.pColorAttachments[i];
        if (attachRef.attachment == VK_ATTACHMENT_UNUSED)
        {
            continue;
        }

        auto& attachDesc = createInfo.pAttachments[attachRef.attachment];
        attachments.emplace_back(static_cast<RenderPassAttachName>(i), attachDesc.loadOp, attachDesc.storeOp, false);
    }

    // Color resolve attachments
    for (uint32_t i = 0; i < lastSubpass.colorAttachmentCount; i++)
    {
        // We may not have any resolve attachments
        if (!lastSubpass.pResolveAttachments)
        {
            continue;
        }

        auto& attachRef = lastSubpass.pResolveAttachments[i];
        if (attachRef.attachment == VK_ATTACHMENT_UNUSED)
        {
            continue;
        }

        auto& attachDesc = createInfo.pAttachments[attachRef.attachment];
        attachments.emplace_back(static_cast<RenderPassAttachName>(i), attachDesc.loadOp, attachDesc.storeOp, true);
    }

    // Depth+Stencil attachments
    // TODO: Determine if this is depth/stencil/both from image format
    if (lastSubpass.pDepthStencilAttachment)
    {
        auto& attachRef = *lastSubpass.pDepthStencilAttachment;
        if (attachRef.attachment != VK_ATTACHMENT_UNUSED)
        {
            auto& attachDesc = createInfo.pAttachments[attachRef.attachment];

            // Canonicalize read-only attachments as storeOp=NONE
            VkAttachmentStoreOp depthStoreOp = attachDesc.storeOp;
            switch (attachRef.layout)
            {
            case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
                if (attachDesc.storeOp == VK_ATTACHMENT_STORE_OP_STORE)
                {
                    depthStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
                }
                break;
            default:
                break;
            }

            attachments.emplace_back(RenderPassAttachName::DEPTH, attachDesc.loadOp, depthStoreOp, false);

            // Canonicalize read-only attachments as storeOp=NONE
            VkAttachmentStoreOp stencilStoreOp = attachDesc.stencilStoreOp;
            switch (attachRef.layout)
            {
            case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
                if (attachDesc.stencilStoreOp == VK_ATTACHMENT_STORE_OP_STORE)
                {
                    stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
                }
                break;
            default:
                break;
            }

            attachments.emplace_back(RenderPassAttachName::STENCIL, attachDesc.stencilLoadOp, stencilStoreOp, false);
        }
    }
}

/* See header for details. */
RenderPass::RenderPass(VkRenderPass _handle, const VkRenderPassCreateInfo2& createInfo)
    : handle(_handle)
{
    subpassCount = createInfo.subpassCount;

    auto& lastSubpass = createInfo.pSubpasses[subpassCount - 1];

    // Color attachments
    for (uint32_t i = 0; i < lastSubpass.colorAttachmentCount; i++)
    {
        auto& attachRef = lastSubpass.pColorAttachments[i];
        if (attachRef.attachment == VK_ATTACHMENT_UNUSED)
        {
            continue;
        }

        auto& attachDesc = createInfo.pAttachments[attachRef.attachment];
        attachments.emplace_back(static_cast<RenderPassAttachName>(i), attachDesc.loadOp, attachDesc.storeOp, false);
    }

    // Color resolve attachments
    for (uint32_t i = 0; i < lastSubpass.colorAttachmentCount; i++)
    {
        // We may not have any resolve attachments
        if (!lastSubpass.pResolveAttachments)
        {
            continue;
        }

        auto& attachRef = lastSubpass.pResolveAttachments[i];
        if (attachRef.attachment == VK_ATTACHMENT_UNUSED)
        {
            continue;
        }

        auto& attachDesc = createInfo.pAttachments[attachRef.attachment];
        attachments.emplace_back(static_cast<RenderPassAttachName>(i), attachDesc.loadOp, attachDesc.storeOp, true);
    }

    // Depth+Stencil attachments
    // TODO: Determine if this is depth/stencil/both from image format
    if (lastSubpass.pDepthStencilAttachment)
    {
        auto& attachRef = *lastSubpass.pDepthStencilAttachment;
        if (attachRef.attachment != VK_ATTACHMENT_UNUSED)
        {
            auto& attachDesc = createInfo.pAttachments[attachRef.attachment];

            // Canonicalize read-only attachments as storeOp=NONE
            VkAttachmentStoreOp depthStoreOp = attachDesc.storeOp;
            switch (attachRef.layout)
            {
            case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
                if (attachDesc.storeOp == VK_ATTACHMENT_STORE_OP_STORE)
                {
                    depthStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
                }
                break;
            default:
                break;
            }

            attachments.emplace_back(RenderPassAttachName::DEPTH, attachDesc.loadOp, depthStoreOp, false);

            // Canonicalize read-only attachments as storeOp=NONE
            VkAttachmentStoreOp stencilStoreOp = attachDesc.stencilStoreOp;
            switch (attachRef.layout)
            {
            case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
            case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
                if (attachDesc.stencilStoreOp == VK_ATTACHMENT_STORE_OP_STORE)
                {
                    stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
                }
                break;
            default:
                break;
            }

            attachments.emplace_back(RenderPassAttachName::STENCIL, attachDesc.stencilLoadOp, stencilStoreOp, false);
        }
    }
}

/* See header for details. */
RenderPass::RenderPass(const VkRenderingInfo& createInfo)
    : handle(VK_NULL_HANDLE)
{
    // No subpasses in dynamic rendering
    subpassCount = 1;

    // Color attachments
    for (uint32_t i = 0; i < createInfo.colorAttachmentCount; i++)
    {
        auto& attachRef = createInfo.pColorAttachments[i];
        if (attachRef.imageView == VK_NULL_HANDLE)
        {
            continue;
        }

        attachments.emplace_back(static_cast<RenderPassAttachName>(i), attachRef.loadOp, attachRef.storeOp, false);
    }

    // Color resolve attachments
    for (uint32_t i = 0; i < createInfo.colorAttachmentCount; i++)
    {
        auto& attachRef = createInfo.pColorAttachments[i];
        if ((attachRef.imageView == VK_NULL_HANDLE) || (attachRef.resolveMode == VK_RESOLVE_MODE_NONE))
        {
            continue;
        }

        attachments.emplace_back(static_cast<RenderPassAttachName>(i),
                                 VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                 VK_ATTACHMENT_STORE_OP_STORE,
                                 true);
    }

    // Depth attachments
    if (createInfo.pDepthAttachment)
    {
        auto& attachRef = *createInfo.pDepthAttachment;

        // Canonicalize read-only attachments as storeOp=NONE
        VkAttachmentStoreOp depthStoreOp = attachRef.storeOp;
        switch (attachRef.imageLayout)
        {
        case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
        case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
            if (attachRef.storeOp == VK_ATTACHMENT_STORE_OP_STORE)
            {
                depthStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
            }
            break;
        default:
            break;
        }

        attachments.emplace_back(RenderPassAttachName::DEPTH, attachRef.loadOp, depthStoreOp, false);

        // Depth resolve attachment
        if ((attachRef.imageView != VK_NULL_HANDLE) && (attachRef.resolveMode != VK_RESOLVE_MODE_NONE))
        {
            attachments.emplace_back(RenderPassAttachName::DEPTH,
                                     VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                     VK_ATTACHMENT_STORE_OP_STORE,
                                     true);
        }
    }

    // Stencil attachment
    if (createInfo.pStencilAttachment)
    {
        auto& attachRef = *createInfo.pStencilAttachment;

        // Canonicalize read-only attachments as storeOp=NONE
        VkAttachmentStoreOp stencilStoreOp = attachRef.storeOp;
        switch (attachRef.imageLayout)
        {
        case VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
        case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
            if (attachRef.storeOp == VK_ATTACHMENT_STORE_OP_STORE)
            {
                stencilStoreOp = VK_ATTACHMENT_STORE_OP_NONE;
            }
            break;
        default:
            break;
        }

        attachments.emplace_back(RenderPassAttachName::STENCIL, attachRef.loadOp, stencilStoreOp, false);

        // Stencil resolve attachment
        if ((attachRef.imageView != VK_NULL_HANDLE) && (attachRef.resolveMode != VK_RESOLVE_MODE_NONE))
        {
            attachments.emplace_back(RenderPassAttachName::STENCIL,
                                     VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                                     VK_ATTACHMENT_STORE_OP_STORE,
                                     true);
        }
    }
}

}
