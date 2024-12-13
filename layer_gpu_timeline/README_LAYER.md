# Layer: GPU Timeline

This layer is used with Arm GPUs for tracking submitted schedulable workloads
and emitting useful metadata that can be used in tooling visualizations. This
data can be combined with raw workload execution timing information captured
by the Android Perfetto service, providing developers with more useful
information about how their application is scheduled on to the Arm GPU.

## What devices are supported?

The Arm GPU driver integration with the Perfetto render stages scheduler event
trace is supported at production quality since the r47p0 driver version.
However, associating additional metadata from this layer relies on additional
functionality which requires an r51p0 or later driver version.

## What workloads are supported?

The Arm GPU scheduler event trace can generate timing events for each
atomically schedulable workload submitted to the GPU scheduler.

Most workloads submitted to a Vulkan queue by the application are a single
schedulable entity, for example a compute dispatch or transfer is a single
workload.

The exception to this is the render pass workload. Arm GPUs are tile-based, so
each group of merged subpasses from a render pass is processed as two
schedulable phases. The first phase - the vertex or binning phase - determines
which primitives contribute to which screen-space tiles. The second phase - the
fragment or main phase - reads the binning information and completes fragment
shading tile-by-tile.

This layer tracks the following workloads:

* Render passes
* Compute dispatches
* Trace rays dispatches
* Transfers to a buffer
* Transfers to an image

## Tracking workloads

The latest Arm driver integration with the Perfetto profiler propagates
application debug labels into the GPU Render Stages scheduler events. The debug
labels are the label stack created using either of these Vulkan methods:

* `vkCmdBegin/EndDebugUtilsLabelEXT()`
* `vkCmdDebugMarkerBegin/EndEXT()`

This layer utilizes this mechanism to wrap each submitted workload in a command
buffer with a unique `tagID` which identifies that recorded workload. A
metadata side-channel provides the metadata for each workload, annotating each
metadata record with the matching `tagID` to allow them to be cross-referenced
later.

### Limitation: Indirect dispatches and trace rays

The current implementation captures the metadata parameters when the command
buffer is recorded. The layer does not currently support asynchronous capture
of indirect parameter buffers. Indirect dispatch and trace rays are still
captured and reported, but with unknown workload dimensions.

### Limitation: Compute dispatch sizes

The current implementation reports the size of a compute workload as the
number of work groups, because this is the parameter used by the API. We
eventually want to report this as the number of work items, but the parsing
of the SPIR-V and pipeline parameters has not yet been implemented.

### Limitation: Dynamic render passes split over multiple command buffers

The label containing the `tagID` is recorded into the application command
buffer when the command buffer is recorded. The workload-to-metadata mapping
requires that every use of a `tagID` has the same properties, or we will
be unable to associate the correct metadata with its matching workload.

Content that splits a render pass over multiple command buffers that
are not one-time-submit violates this requirement. Multiple submits of a render
pass with a single `tagID` may have different numbers of draw calls, depending
on the number of draws that occur in the later command buffers that resume the
render pass. When the layer detects suspended render pass in a multi-submit
command buffer, it will still capture and report the workload, but with an
unknown draw call count.

## Command stream modelling

Most properties we track are a property of the command buffer recording in
isolation. However, the user debug label stack is a property of the queue and
persists across submits. We can therefore only determine the debug label
associated with a workload in the command stream at submit time, and must
resolve it per workload inside the command buffer.

To support this we implement a software command stream that contains simple
bytecode actions that represent the sequence of debug label and workload
commands inside each command buffer. This "command stream" can be played to
update the the queue state at submit time, triggering metadata submission
for each workload that can snapshot the current state of the user debug label
stack at that point in the command stream.

- - -

_Copyright © 2024, Arm Limited and contributors._
