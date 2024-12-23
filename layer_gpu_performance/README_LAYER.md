# Layer: GPU Performance

This layer is a standalone performance analysis layer that can be used to
analyze the workloads that make up a single frame.

This layer supports two modes:

* Per workload time, read via queries
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
pieces which are independently scheduled and can overlap with other work that
is running on the GPU. Blindly timing render passes using timer queries can
result in confusing results because the time includes time spend processing
unrelated workloads running in parallel.

The diagram shows one possible arrangement of workloads scheduled on the GPU
hardware queues for an Arm 5th Generation architecture GPU. We're trying to
time render pass 1 indicated by the `1` characters in the diagram, starting a
timer query when this render pass starts (`S`) in the binning phase queue, and
stopping when it ends (`E`) in the main phase queue.

```
         Compute:              222
   Binning phase: S 11111 3333
      Main phase:   00000000 111111111111 E
```

In this scenario the timer query correctly reflects the elapsed time of the
render pass, but is not an accurate measure of cost of this workload. The
elapsed time includes time where other workloads are running in parallel,
indicated by the `0`, `2`, and `3` characters. It also includes time between
the two phases where workload `1` is not running at all, because the binning
phase work has completed, but is waiting for the main phase queue to finish an
earlier workload.

To accurately cost workloads on a tile-based renderer, which will overlap and
run workloads in parallel if it is allowed to, the layer must inject additional
synchronization primitives to serialize all workloads within a queue and across
queues. This ensures that timer query values reflect the cost of individual
workloads, however it also means that overall frame performance will be reduced
due to loss of workload parallelization.
