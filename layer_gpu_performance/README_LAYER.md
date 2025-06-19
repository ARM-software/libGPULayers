# Layer: GPU Performance

This layer is a standalone performance analysis layer that can be used to
analyze the workloads that make up a single frame.

This layer supports two modes:

* Per workload time, read via Vulkan API queries
* Per workload performance counters, read via a non-API mechanism

## What devices are supported?

The per workload timing uses Vulkan API timer queries, and should work on any
GPU that supports the required Vulkan features.

The per workload performance counters uses the Arm libGPUCounters library,
and requires an Arm GPU.

## Is this layer non-invasive?

The goal of this layer is to cost the major workloads submitted via the API, in
a way which is compatible with the way that a tile-based renderer schedules
render passes.

Under normal scheduling, tile-based renderers split render passes into two
pieces which are independently scheduled and that can overlap with other work
that is running on the GPU. Blindly timing render passes using timer queries
can result in confusing results because the reported time might include time
spent processing unrelated workloads that happen to be running in parallel.

The timing diagram below shows one possible arrangement of workloads scheduled
on the GPU hardware queues for an Arm 5th Generation architecture GPU. We are
trying to time render pass 1 indicated by the `1` characters in the diagram,
starting a timer query when this render pass starts (`S`) in the binning phase
queue, and stopping when it ends (`E`) in the main phase queue.

```
         Compute:              222
   Binning phase: S 11111 3333
      Main phase:   00000000 111111111111 E
```

In this scenario the timer query correctly reflects the elapsed time of the
render pass, but does not give an accurate measure of its cost. The elapsed
time includes time where other workloads are running in parallel, indicated by
the `0`, `2`, and `3` characters. It also includes time between the two phases
where workload `1` is not running at all, because the binning phase work has
completed and the main phase work is stuck waiting for an earlier workload to
finish to free up the hardware.

To accurately cost workloads on a tile-based renderer, which will overlap and
run workloads in parallel if it is allowed to, the layer must inject additional
synchronization to serialize all workloads within a queue and across queues.
This ensures that timer query values reflect the cost of individual workloads,
however it also means that overall frame performance will be reduced due to
loss of workload parallelization.

# Design notes

## Dependencies

This layer uses timeline semaphores, so requires either Vulkan 1.1 or
the `VK_KHR_timeline_semaphore` extension.

## Implementing serialization

Cross-queue serialization is implemented using an injected timeline semaphore.
Each submit is assigned an incrementing `ID`, and will wait for `ID - 1` in the
timeline before starting, and set `ID` in the timeline when completing. This
allows us to implement serialization using a single sync primitive.

Serialization within a queue is implemented by injecting a full pipeline
barrier before the pre-workload timer query, ensuring that all prior work has
completed before the time is sampled. Similarly we put a full pipeline barrier
after the post-workload timer query, ensuring that no following work starts
before the time is sampled.

## Implementing query lifetime tracking

Timer queries are implemented using query pools. The timer write commands are
recorded into each command buffer alongside the user commands. Each timer write
command specifies the specific counter slots used in a specific query pool, so
the query pool and slot usage must be assigned when the command buffer is
recorded.

Query pools in the layer are a managed resource. We allocate query pools on
demand, and maintain a free-list of query pools that have been freed and are
ready for reuse.

Query pools are allocated with enough space for 64 query results which is, in
the best case, enough for 63 workloads (N+1 counters). This can reduce for
render passes using multi-view rendering, which allocate 1 counter slot per
view.

Query pools are assigned to a command buffer when recording, and multiple
query pools can be assigned to a single command buffer if more query result
space is needed. Query pools are fully reset on first use in the command
buffer. Query pools are returned to the layer free-list when the command buffer
is reset or destroyed.

### Multi-submit command buffers

Reusable command buffers that are not one-time submit can be problematic for
this type of instrumentation.

A single primary command buffer could be submitted multiple times. This can be
managed by serializing the workloads and ensuring that the query results are
consumed between executions. This may impact performance due to additional
serialization, but it can be made to work.

**NOTE:** This impact of this case could be mitigated by having the layer
inject a command buffer after the user command buffer, which inserts a copy
command to copy the query results to a buffer. This buffer is owned by the
layer and can be N-buffered to avoid stalls.

The more problematic case is the case where a single secondary command buffer
is executed multiple times from within the same primary. In this case there
is no place to solve the collision with CPU-side synchronization, and relying
on only CPU-side recording will only capture the last copy.

### Split command buffers

Vulkan 1.3 can split dynamic render passes over multiple command buffers,
although all parts must be part of the same queue submit call. The layer will
only emit timestamps for the final part of the render pass, and will ignore
suspend/resumes.
