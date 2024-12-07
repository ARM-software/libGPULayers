# Layer: GPU Timeline - Command Buffer Modelling

One of the main challenges of this layer driver is modelling behavior in queues
and command buffers that is not known until submit time, and then taking
appropriate actions based on the combination of both the head state of the
queue and the content of the pre-recorded command buffers.

Our design to solve this is a lightweight software command stream which is
recorded when a command buffer is recorded, and then executed when the
command buffer is submitted to the queue. Just like a real hardware command
stream these commands can update state or trigger some other action we need
performed.

## Layer commands

**MARKER_BEGIN(const std::string\*):**

* Push a new marker into the queue debug label stack.

**MARKER_END():**

* Pop the latest marker from the queue debug label stack.

**RENDERPASS_BEGIN(const json\*):**

* Set the current workload to a new render pass with the passed metadata.

**RENDERPASS_RESUME(const json\*):**

* Update the current workload, which must be a render pass, with extra
  draw count metadata.

**COMPUTE_DISPATCH_BEGIN(const json\*):**

* Set the current workload to a new compute dispatch with the passed metadata.

**TRACE_RAYS_BEGIN(const json\*):**

* Set the current workload to a new trace rays with the passed metadata.

**BUFFER_TRANSFER_BEGIN(const json\*):**

* Set the current workload to a new a buffer transfer.

**IMAGE_TRANSFER(const json\*):**

* Set the current workload to a new image transfer.

**WORKLOAD_END():**

* Mark the current workload as complete, and emit a built metadata entry for
  it.

## Layer command recording

Command buffer recording is effectively building two separate state
structures for the layer.

The first is a per-workload or per-restart JSON structure that contains the
metadata we need for that workload. For partial workloads - e.g. a dynamic
render pass begin that has been suspended - this metadata will be partial and
rely on later restart metadata to complete it.

The second is the layer "command stream" that contains the bytecode commands
to execute when the command buffer is submitted to the queue. These commands
are very simple, consisting of a list of command+pointer pairs, where the
pointer value may be unused by some commands. Commands are stored in a
std::vector, but we reserve enough memory to store 256 commands without
reallocating which is enough for the majority of command buffers we see in
real applications.

The command stream for a secondary command buffer is inlined into the primary
command buffer during recording.

###  Recording sequence

When application records a new workload:

  * A `tagID` is assigned and recorded using `vkCmdMarkerBegin()` label in the
    Vulkan command stream _before_ the new workload is written to the command
    stream.
  * If workload is using indirect parameters, then a transfer job to copy
    indirect parameters into a layer-owned buffer is emitted _before_ the new
    workload. No additional barrier is needed because application barriers must
    have already ensured that the indirect parameter buffer is valid.
  * A proxy workload object is created in the layer storing the assigned
    `tagID` and all settings that are known at command recording time.
  * A layer command stream command is recorded into the submit time stream
    indicating `<TYPE>_BEGIN` with a pointer to the proxy workload. Note that
    this JSON may be modified later for some workloads.
  * If workload is using indirect parameters, a layer command stream command is
    recorded into the resolve time stream, which will handle cleanup and
    emitting the `submitID.tagID` annex message for the indirect data.
  * If the command buffer is not ONE_TIME_SUBMIT, if any workload is using
    indirect parameters, or contains incomplete render passes, the command
    buffer is marked as needing a `submitID` wrapper.
  * The user command is written to the Vulkan command stream.

When application resumes a render pass workload:

  * A `tagID` of zero is assigned, but not emitted to the command stream.
  * A layer command stream command is recorded into the submit time stream
    indicating `<TYPE>_RESUME` with a pointer to the proxy workload. Note that
    this JSON may be modified later for some workloads.
  * The user command is written to the Vulkan command stream.

When application ends a workload:

  * For render pass workloads, any statistics accumulated since the last begin
    are rolled up into the proxy workload object.
  * For render pass workloads, the user command is written to the Vulkan
    command stream.
  * The command steam label scope is closed using `vkCmdMarkerEnd()`.

## Layer command playback

The persistent state for command playback belongs to the queues the command
buffers are submitted to. The command stream bytecode is run by a bytecode
interpreter associated with the state of the current queue, giving the
interpreter access to the current `submitID` and queue debug label stack.

###  Submitting sequence

For each command buffer in the user submit:

* If the command buffer needs a `submitID` we allocate a unique `submitID` and
  create two new command buffers that will wrap the user command buffer with an
  additional stack layer of debug label containing the `s<ID>` string. We will
  inject a layer command stream async command to handle freeing the command
  buffers.
* The tool will process the submit-time layer commands, executing each command
  to either update some state or emit
* If there are any async layer commands, either recorded in the command buffer
  or from the wrapping command buffers, we will need to add an async handler.
  This cannot safely use the user fence or depend on any user object lifetime,
  so we will add a layer-owned timeline semaphore to the submit which we can
  wait on to determine when it is safe trigger the async work.

## Future: Async commands

One of our longer-term goals is to be able to capture indirect parameters,
which will be available after-the-fact once the GPU has processed the command
buffer. Once we have the data we can emit an annex message containing
parameters for each indirect `submitID.tagID` pair in the command buffer.

We need to be able to emit the metadata after the commands are complete,
and correctly synchronize use of the indirect capture staging buffer
if command buffers are reissued. My current thinking is that we would
implement this using additional layer commands that are processed on submit,
including support for async commands that run in a separate thread and
wait on the command buffer completion fence before running.

- - -

_Copyright © 2024, Arm Limited and contributors._
