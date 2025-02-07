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

#include "timeline_protobuf_encoder.hpp"

#include "comms/comms_interface.hpp"
#include "trackers/layer_command_stream.hpp"
#include "trackers/render_pass.hpp"
#include "utils/misc.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

#include <protopuf/field.h>
#include <protopuf/message.h>
#include <protopuf/skip.h>

/* Possible version numbers that can be sent by the header */
enum class HeaderVersionNo
{
    /* The only version currently defined */
    version_1 = 0,
};

/* The connection header message sent to identify the version of the timeline protocol used. This should be sent exactly
 * once per connection */
using Header = pp::message<
    /* The only mandatory field of this message. This identifys the version. Any subsequent fields are
     * versioned based on this. All additional fields must be optional and additive (no removals) */
    pp::enum_field<"version_no", 1, HeaderVersionNo>>;

/* The metadata packet that is sent once for a given VkDevice, before any other
 * packet related to that Device and describes the VkDevice / VkPhysicalDevice
 * etc */
using DeviceMetadata = pp::message<
    /* The VkDevice handle */
    pp::uint64_field<"id", 1>,
    /* The PID of the process that the layer driver was loaded into */
    pp::uint32_field<"process_id", 2>,
    /* The major version that came from the VkPhysicalDeviceProperties for that VkDevice */
    pp::uint32_field<"major_version", 3>,
    /* The minor version that came from the VkPhysicalDeviceProperties for that VkDevice */
    pp::uint32_field<"minor_version", 4>,
    /* The patch version that came from the VkPhysicalDeviceProperties for that VkDevice */
    pp::uint32_field<"patch_version", 5>,
    /* The name that came from the VkPhysicalDeviceProperties for that VkDevice */
    pp::string_field<"name", 6>>;

/* A frame definition message */
using Frame = pp::message<
    /* The unique counter / identifier for this new frame */
    pp::uint64_field<"id", 1>,
    /* The VkDevice that the frame belongs to */
    pp::uint64_field<"device", 2>,
    /* The timestamp (in NS, CLOCK_MONOTONIC_RAW) of the point where QueuePresent was called */
    pp::uint64_field<"timestamp", 3>>;

/* A submit message */
using Submit = pp::message<
    /* The timestamp of the submission (in NS, CLOCK_MONOTONIC_RAW) */
    pp::uint64_field<"timestamp", 1>,
    /* The VkDevice that the submit belongs to */
    pp::uint64_field<"device", 2>,
    /* The VkQueue the frame belongs to */
    pp::uint64_field<"queue", 3>>;

/* Enumerates the possible attachment types a renderpass can have */
enum class RenderpassAttachmentType
{
    undefined = 0,
    color = 1,
    depth = 2,
    stencil = 3,
};

/* Describe an attachment to a renderpass */
using RenderpassAttachment = pp::message<
    /* The attachment type */
    pp::enum_field<"type", 1, RenderpassAttachmentType>,
    /* For color attachments, its index, otherwise should be zero/unspecified */
    pp::uint32_field<"index", 2>,
    /* True if the attachment was *not* loaded (this is inverted since usually
       things are loaded, so this saves a field in the data) */
    pp::bool_field<"not_loaded", 3>,
    /* True if the attachment was *not* stored (this is inverted since usually
       things are stored, so this saves a field in the data) */
    pp::bool_field<"not_stored", 4>,
    /* True if the attachment was resolved (this is *not* inverted since usually
       things are not resolved, so this saves a field in the data) */
    pp::bool_field<"resolved", 5>>;

/* Start a new renderpass */
using BeginRenderpass = pp::message<
    /* The unique identifier for this new renderpass */
    pp::uint64_field<"tag_id", 1>,
    /* The dimensions of the renderpass' attachments */
    pp::uint32_field<"width", 2>,
    pp::uint32_field<"height", 3>,
    /* The number of drawcalls in the renderpass */
    pp::uint32_field<"draw_call_count", 4>,
    /* The subpass count */
    pp::uint32_field<"subpass_count", 5>,
    /* Any user defined debug labels associated with the renderpass */
    pp::string_field<"debug_label", 6, pp::repeated>,
    /* Any attachments associated with the renderpass */
    pp::message_field<"attachments", 7, RenderpassAttachment, pp::repeated>>;

/* Continue a split renderpass */
using ContinueRenderpass = pp::message<
    /* The unique identifier for the renderpass that is being continued */
    pp::uint64_field<"tag_id", 1>,
    /* The number of drawcalls to add to the total in the renderpass */
    pp::uint32_field<"draw_call_count", 2>,
    /* Any user defined debug labels to add to the renderpass */
    pp::string_field<"debug_label", 3, pp::repeated>>;

/* A dispatch object submission */
using Dispatch = pp::message<
    /* The unique identifier for this operation */
    pp::uint64_field<"tag_id", 1>,
    /* The dimensions of the dispatch */
    pp::int64_field<"x_groups", 2>,
    pp::int64_field<"y_groups", 3>,
    pp::int64_field<"z_groups", 4>,
    /* Any user defined debug labels associated with the dispatch */
    pp::string_field<"debug_label", 5, pp::repeated>>;

/* A trace rays object submission */
using TraceRays = pp::message<
    /* The unique identifier for this operation */
    pp::uint64_field<"tag_id", 1>,
    /* The dimensions of the operation */
    pp::int64_field<"x_items", 2>,
    pp::int64_field<"y_items", 3>,
    pp::int64_field<"z_items", 4>,
    /* Any user defined debug labels associated with the dispatch */
    pp::string_field<"debug_label", 5, pp::repeated>>;

/* Enumerates possible image transfer types */
enum class ImageTransferType
{
    unknown_image_transfer = 0,
    clear_image = 1,
    copy_image = 2,
    copy_buffer_to_image = 3,
    copy_image_to_buffer = 4,
};

/* An image transfer submission */
using ImageTransfer = pp::message<
    /* The unique identifier for this operation */
    pp::uint64_field<"tag_id", 1>,
    /* The number of pixels being transfered */
    pp::int64_field<"pixel_count", 2>,
    /* The image type */
    pp::enum_field<"transfer_type", 3, ImageTransferType>,
    /* Any user defined debug labels associated with the dispatch */
    pp::string_field<"debug_label", 4, pp::repeated>>;

/* Enumerates possible buffer transfer types */
enum class BufferTransferType
{
    unknown_buffer_transfer = 0,
    fill_buffer = 1,
    copy_buffer = 2,
};

/* An buffer transfer submission */
using BufferTransfer = pp::message<
    /* The unique identifier for this operation */
    pp::uint64_field<"tag_id", 1>,
    /* The number of bytes being transfered */
    pp::int64_field<"byte_count", 2>,
    /* The buffer type */
    pp::enum_field<"transfer_type", 3, BufferTransferType>,
    /* Any user defined debug labels associated with the dispatch */
    pp::string_field<"debug_label", 4, pp::repeated>>;

/* The data payload message that wraps all other messages */
using TimelineRecord = pp::message<pp::message_field<"header", 1, Header>,
                                   pp::message_field<"metadata", 2, DeviceMetadata>,
                                   pp::message_field<"frame", 3, Frame>,
                                   pp::message_field<"submit", 4, Submit>,
                                   pp::message_field<"renderpass", 5, BeginRenderpass>,
                                   pp::message_field<"continue_renderpass", 6, ContinueRenderpass>,
                                   pp::message_field<"dispatch", 7, Dispatch>,
                                   pp::message_field<"trace_rays", 8, TraceRays>,
                                   pp::message_field<"image_transfer", 9, ImageTransfer>,
                                   pp::message_field<"buffer_transfer", 10, BufferTransfer>>;

namespace
{
/**
 * A helper to pack some message into a TimelineRecord and then encode it to the
 * corresponding protobuf byte sequence.
 *
 * @param c The record field name
 * @param f The record field value
 * @return The encoded byte sequence
 */
template<pp::basic_fixed_string F, typename T>
Comms::MessageData packBuffer(pp::constant<F> c, T&& f)
{
    using namespace pp;

    TimelineRecord record {};
    record[c] = std::move(f);

    // allocate storage for the message
    Comms::MessageData buffer {};
    buffer.resize(skipper<message_coder<TimelineRecord>>::encode_skip(record));

    const auto bufferBytes = bytes(reinterpret_cast<std::byte*>(buffer.data()), buffer.size());
    const auto encodeResult = message_coder<TimelineRecord>::encode(record, bufferBytes);
    assert(encodeResult.has_value());

    const auto& bufferEnd = *encodeResult;
    const auto usedLength = begin_diff(bufferEnd, bufferBytes);
    buffer.resize(usedLength);

    return buffer;
}

/**
 * @brief Map the state-tracker enum value that describes the renderpass attachment name to some pair of
 * protocol values, being the attachment type, and optional attachment index.
 *
 * @param name The name value to map to the pair of type and index
 * @return A pair, where the first value is the corresponding attachment type, and the second value is
 * the corresponding attachment index (or nullopt in the case the index is not relevant).
 */
constexpr std::pair<RenderpassAttachmentType, std::optional<uint32_t>> mapRenderpassAttachmentName(
    Tracker::RenderPassAttachName name)
{
    switch (name)
    {
    case Tracker::RenderPassAttachName::COLOR0:
        return {RenderpassAttachmentType::color, 0};
    case Tracker::RenderPassAttachName::COLOR1:
        return {RenderpassAttachmentType::color, 1};
    case Tracker::RenderPassAttachName::COLOR2:
        return {RenderpassAttachmentType::color, 2};
    case Tracker::RenderPassAttachName::COLOR3:
        return {RenderpassAttachmentType::color, 3};
    case Tracker::RenderPassAttachName::COLOR4:
        return {RenderpassAttachmentType::color, 4};
    case Tracker::RenderPassAttachName::COLOR5:
        return {RenderpassAttachmentType::color, 5};
    case Tracker::RenderPassAttachName::COLOR6:
        return {RenderpassAttachmentType::color, 6};
    case Tracker::RenderPassAttachName::COLOR7:
        return {RenderpassAttachmentType::color, 7};
    case Tracker::RenderPassAttachName::DEPTH:
        return {RenderpassAttachmentType::depth, std::nullopt};
    case Tracker::RenderPassAttachName::STENCIL:
        return {RenderpassAttachmentType::stencil, std::nullopt};
    default:
        assert(false && "What is this attachment name?");
        return {RenderpassAttachmentType::undefined, std::nullopt};
    }
}

/**
 * @brief Map the state-tracker enum value that describes the buffer transfer type into the protocol encoded value
 *
 * NB: Whilst we are currently just replicating one enum value into another (which the compiler should be smart enough
 * to fix), we do it this way to ensure we decouple the state-tracker from the protobuf encoding, since we don't want to
 * accidentally change some enum wire-value in the future.
 *
 * @param type The type enum to convert
 * @return The wire value enum to store in the protobuf message
 */
constexpr BufferTransferType mapBufferTransferType(Tracker::LCSBufferTransfer::Type type)
{
    switch (type)
    {
    case Tracker::LCSBufferTransfer::Type::unknown:
        return BufferTransferType::unknown_buffer_transfer;
    case Tracker::LCSBufferTransfer::Type::fill_buffer:
        return BufferTransferType::fill_buffer;
    case Tracker::LCSBufferTransfer::Type::copy_buffer:
        return BufferTransferType::copy_buffer;
    default:
        assert(false && "Unexpected LCSBufferTransfer::Type");
        return BufferTransferType::unknown_buffer_transfer;
    }
}

/**
 * @brief Map the state-tracker enum value that describes the image transfer type into the protocol encoded value
 *
 * NB: Whilst we are currently just replicating one enum value into another (which the compiler should be smart enough
 * to fix), we do it this way to ensure we decouple the state-tracker from the protobuf encoding, since we don't want to
 * accidentally change some enum wire-value in the future.
 *
 * @param type The type enum to convert
 * @return The wire value enum to store in the protobuf message
 */
constexpr ImageTransferType mapImageTransferType(Tracker::LCSImageTransfer::Type type)
{
    switch (type)
    {
    case Tracker::LCSImageTransfer::Type::unknown:
        return ImageTransferType::unknown_image_transfer;
    case Tracker::LCSImageTransfer::Type::clear_image:
        return ImageTransferType::clear_image;
    case Tracker::LCSImageTransfer::Type::copy_image:
        return ImageTransferType::copy_image;
    case Tracker::LCSImageTransfer::Type::copy_buffer_to_image:
        return ImageTransferType::copy_buffer_to_image;
    case Tracker::LCSImageTransfer::Type::copy_image_to_buffer:
        return ImageTransferType::copy_image_to_buffer;
    default:
        assert(false && "Unexpected LCSImageTransfer::Type");
        return ImageTransferType::unknown_image_transfer;
    }
}

/**
 * @brief Serialize the metadata for this render pass workload.
 *
 * @param renderpass The renderpass to serialize
 * @param debugLabel The debug label stack of the VkQueue at submit time.
 */
Comms::MessageData serialize(const Tracker::LCSRenderPass& renderpass, const std::vector<std::string>& debugLabel)
{
    using namespace pp;

    // Draw count for a multi-submit command buffer cannot be reliably
    // associated with a single tagID if restartable across command buffer
    // boundaries because different command buffer submit combinations can
    // result in different draw counts for the same starting tagID.
    const auto drawCount = (!renderpass.isOneTimeSubmit() && renderpass.isSuspending()
                                ? -1
                                : static_cast<int64_t>(renderpass.getDrawCallCount()));

    // make the attachements array
    const auto& attachments = renderpass.getAttachments();
    std::vector<RenderpassAttachment> attachmentsMsg {};
    attachmentsMsg.reserve(attachments.size());

    for (const auto& attachment : attachments)
    {
        const auto [type, index] = mapRenderpassAttachmentName(attachment.getAttachmentName());

        attachmentsMsg.emplace_back(type,
                                    index,
                                    // these two are expected to be inverted, and will only be sent if the value is
                                    // "not_loaded" / "not_stored" since that is the uncommon case
                                    (attachment.isLoaded() ? std::nullopt : std::make_optional(false)),
                                    (attachment.isStored() ? std::nullopt : std::make_optional(false)),
                                    // resolved is not inverted since that is the incommon case
                                    (attachment.isResolved() ? std::make_optional(true) : std::nullopt));
    }

    return packBuffer("renderpass"_f,
                      BeginRenderpass {
                          renderpass.getTagID(),
                          renderpass.getWidth(),
                          renderpass.getHeight(),
                          drawCount,
                          renderpass.getSubpassCount(),
                          debugLabel,
                          std::move(attachmentsMsg),
                      });
}

/**
 * @brief Serialize the metadata for this render pass continuation workload.
 *
 * @param continuation The renderpass continuation to serialize
 * @param tagIDContinuation The ID of the workload if this is a continuation of it.
 */
Comms::MessageData serialize(const Tracker::LCSRenderPassContinuation& continuation, uint64_t tagIDContinuation)
{
    using namespace pp;

    return packBuffer("continue_renderpass"_f,
                      ContinueRenderpass {
                          tagIDContinuation,
                          continuation.getDrawCallCount(),
                          {},
                      });
}

/**
 * @brief Get the metadata for this workload
 *
 * @param dispatch The dispatch to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
Comms::MessageData serialize(const Tracker::LCSDispatch& dispatch, const std::vector<std::string>& debugLabel)
{
    using namespace pp;

    return packBuffer("dispatch"_f,
                      Dispatch {
                          dispatch.getTagID(),
                          dispatch.getXGroups(),
                          dispatch.getYGroups(),
                          dispatch.getZGroups(),
                          debugLabel,
                      });
}

/**
 * @brief Get the metadata for this workload
 *
 * @param traceRays The trace rays to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
Comms::MessageData serialize(const Tracker::LCSTraceRays& traceRays, const std::vector<std::string>& debugLabel)
{
    using namespace pp;

    return packBuffer("trace_rays"_f,
                      TraceRays {
                          traceRays.getTagID(),
                          traceRays.getXItems(),
                          traceRays.getYItems(),
                          traceRays.getZItems(),
                          debugLabel,
                      });
}

/**
 * @brief Get the metadata for this workload
 *
 * @param imageTransfer The image transfer to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
Comms::MessageData serialize(const Tracker::LCSImageTransfer& imageTransfer, const std::vector<std::string>& debugLabel)
{
    using namespace pp;

    return packBuffer("image_transfer"_f,
                      ImageTransfer {
                          imageTransfer.getTagID(),
                          imageTransfer.getPixelCount(),
                          mapImageTransferType(imageTransfer.getTransferType()),
                          debugLabel,
                      });
}

/**
 * @brief Get the metadata for this workload
 *
 * @param bufferTransfer The buffer transfer to serialize
 * @param debugLabel The debug label stack for the VkQueue at submit time.
 */
Comms::MessageData serialize(const Tracker::LCSBufferTransfer& bufferTransfer,
                             const std::vector<std::string>& debugLabel)
{
    using namespace pp;

    return packBuffer("buffer_transfer"_f,
                      BufferTransfer {
                          bufferTransfer.getTagID(),
                          bufferTransfer.getByteCount(),
                          mapBufferTransferType(bufferTransfer.getTransferType()),
                          debugLabel,
                      });
}
}

void TimelineProtobufEncoder::emitHeaderMessage(TimelineComms& comms)
{
    using namespace pp;

    comms.txMessage(packBuffer("header"_f,
                               Header {
                                   HeaderVersionNo::version_1,
                               }));
}

void TimelineProtobufEncoder::emitMetadata(Device& device,
                                           uint32_t pid,
                                           uint32_t major,
                                           uint32_t minor,
                                           uint32_t patch,
                                           std::string name)
{
    using namespace pp;

    device.txMessage(packBuffer("metadata"_f,
                                DeviceMetadata {
                                    reinterpret_cast<uintptr_t>(device.device),
                                    pid,
                                    major,
                                    minor,
                                    patch,
                                    std::move(name),
                                }));
}

void TimelineProtobufEncoder::emitFrame(Device& device, uint64_t frameNumber, uint64_t timestamp)
{
    using namespace pp;

    device.txMessage(packBuffer("frame"_f,
                                Frame {
                                    frameNumber,
                                    reinterpret_cast<uintptr_t>(device.device),
                                    timestamp,
                                }));
}

void TimelineProtobufEncoder::emitSubmit(VkQueue queue, uint64_t timestamp)
{
    using namespace pp;

    device.txMessage(packBuffer("submit"_f,
                                Submit {
                                    timestamp,
                                    reinterpret_cast<uintptr_t>(device.device),
                                    reinterpret_cast<uintptr_t>(queue),
                                }));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSRenderPass& renderpass,
                                         const std::vector<std::string>& debugStack)
{
    device.txMessage(serialize(renderpass, debugStack));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSRenderPassContinuation& continuation,
                                         const std::vector<std::string>& debugStack,
                                         uint64_t renderpassTagID)
{
    UNUSED(debugStack);

    device.txMessage(serialize(continuation, renderpassTagID));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSDispatch& dispatch,
                                         const std::vector<std::string>& debugStack)
{
    device.txMessage(serialize(dispatch, debugStack));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSTraceRays& traceRays,
                                         const std::vector<std::string>& debugStack)
{
    device.txMessage(serialize(traceRays, debugStack));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSImageTransfer& imageTransfer,
                                         const std::vector<std::string>& debugStack)
{
    device.txMessage(serialize(imageTransfer, debugStack));
}

void TimelineProtobufEncoder::operator()(const Tracker::LCSBufferTransfer& bufferTransfer,
                                         const std::vector<std::string>& debugStack)
{
    device.txMessage(serialize(bufferTransfer, debugStack));
}
