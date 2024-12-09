# Layer: GPU Timeline

This layer is used with Arm GPUs for tracking submitted schedulable workloads
and emitting semantic information about them. This data can be combined with
the raw workload execution timing information captured using the Android
Perfetto service, providing developers with a richer debug visualization.

## What devices?

The Arm GPU driver integration with the Perfetto render stages scheduler event
trace is supported at production quality since the r47p0 driver version.
However, associating semantics from this layer relies on a further integration
with debug labels which requires an r51p0 or later driver version.

## What workloads?

A schedulable workload is the smallest workload that the Arm GPU command stream
scheduler will issue to the GPU hardware work queues. This includes the
following workload types:

* Render passes, split into:
  * Vertex or Binning phase
  * Fragment or Main phase
* Compute dispatches
* Trace rays
* Transfers to a buffer
* Transfers to an image

Most workloads are dispatched using a single API call, and are trivial to
manage in the layer. However, render passes are more complex and need extra
handling. In particular:

* Render passes are issued using multiple API calls.
* Useful render pass properties, such as draw count, are not known until the
  render pass recording has ended.
* Dynamic render passes using `vkCmdBeginRendering()` and `vkCmdEndRendering()`
  can be suspended and resumed across command buffer boundaries. Properties
  such as draw count are not defined by the scope of a single command buffer.

## Tracking workloads

This layer tracks workloads encoded in command buffers, and emits semantic
metadata for each workload via a communications side-channel. A host tool
combines the semantic data stream with the Perfetto data stream, using debug
label tags injected by the layer as a common cross-reference to link across
the streams.

### Workload labelling

Command stream labelling is implemented using `vkCmdDebugMarkerBeginEXT()`
and `vkCmdDebugMarkerEndEXT()`, wrapping one layer-owned `tagID` label around
each semantic workload. This `tagID` can unambiguously refer to this workload
encoding, and metadata that we do not expect to change per submit will be
emitted using the matching `tagID` as the sole identifier.

_**TODO:** Dynamic `submitID` tracking is not yet implemented._

The `tagID` label is encoded into the recorded command buffer which means, for
reusable command buffers, it is not an unambiguous identifier of a specific
running workload. To allow us to disambiguate specific workload instances, the
layer can optionally add an outer wrapper of `submitID` labels around each
submitted command buffer. This wrapper is only generated if the submit contains
any command buffers that require the generation of a per-submit annex (see the
following section for when this is needed).

The `submitID.tagID` pair of IDs uniquely identifies a specific running
workload, and can be used to attach an instance-specific metadata annex to a
specific submitted workload rather than to the shared recorded command buffer.

### Workload metadata for split render passes

_**TODO:** Split render pass tracking is not yet implemented._

Dynamic render passes can be split across multiple Begin/End pairs, including
being split across command buffer boundaries. If these splits occur within a
single primary command buffer, or its secondaries, it is handled transparently
by the layer and it appears as a single message as if no splits occurred. If
these splits occur across primary command buffer boundaries, then some
additional work is required.

In our design a `tagID` debug marker is only started when the render pass first
starts (not on resume), and stopped at the end of the render pass (not on
suspend). The same `tagID` is used to refer to all parts of the render pass,
no matter how many times it was suspended and resumed.

If a render pass splits across command buffers, we cannot precompute metrics
based on `tagID` alone, even if the command buffers are one-time use. This is
because we do not know what combination of submitted command buffers will be
used, and so we cannot know what the render pass contains until submit time.
Split render passes will emit a `submitID.tagID` metadata annex containing
the parameters that can only be known at submit time.

### Workload metadata for compute dispatches

_**TODO:** Compute workgroup parsing from the SPIR-V is not yet implemented._

Compute workload dispatch is simple to track, but one of the metadata items we
want to export is the total size of the work space (work_group_count *
work_group_size).

The work group count is defined by the API call, but may be an indirect
parameter (see indirect tracking above).

The work group size is defined by the program pipeline, and is defined in the
SPIR-V via a literal or a build-time specialization constant. To support this
use case we will need to parse the SPIR-V when the pipeline is built, if
SPIR-V is available.

### Workload metadata for indirect calls

_**TODO:** Indirect parameter tracking is not yet implemented._

One of the valuable pieces of metadata that we want to present is the size of
each workload. For render passes this is captured at API call time, but for
other workloads the size can be an indirect parameter that is not known when
the triggering API call is made.

To capture indirect parameters we insert a transfer that copies the indirect
parameters into a layer-owned buffer. To ensure exclusive use of the buffer and
avoid data corruption, each buffer region used is unique to a specific `tagID`.
Attempting to submit the same command buffer multiple times will result in
the workload being serialized to avoid racy access to the buffer. Once the
buffer has been retrieved by the layer, a metadata annex containing the
indirect parameters will be emitted using the `submitID.tagID` pair. This may
be some time later than the original submit.

### Workload metadata for user-defined labels

The workload metadata captures user-defined labels that the application
provides using `vkCmdDebugMarkerBeginEXT()` and `vkCmdDebugMarkerEndEXT()`.
These are a stack-based debug mechanism where `Begin` pushes a new entry on to
to the stack, and `End` pops the the most recent level off the stack.

Workloads are labelled with the stack values that existed when the workload
was started. For render passes this is the value on the stack when, e.g.,
`vkCmdBeginRenderPass()` was called. We do not capture any labels that exist
inside the render pass.

The debug label stack belongs to the queue, not to the command buffer, so the
value of the label stack is not known until submit time. The debug information
for a specific `submitID.tagID` pair is therefore provided as an annex at
submit time once the stack can be resolved.

## Message protocol

For each workload in a command buffer, or part-workload in the case of a
suspended render pass, we record a JSON metadata blob containing the payload
we want to send.

The low level protocol message contains:

* Message type `uint8_t`
* Sequence ID `uint64_t` (optional, implied by message type)
* Tag ID `uint64_t`
* JSON length `uint32_t`
* JSON payload `uint8_t[]`

Each workload will read whatever properties it can from the `tagID` metadata
and will then merge in all fields from any subsequent `sequenceID.tagID`
metadata that matches.

- - -

_Copyright © 2024, Arm Limited and contributors._
