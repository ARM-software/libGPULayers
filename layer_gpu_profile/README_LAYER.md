# Layer: GPU Profile

This layer is a frame profiler that can capture per workload performance
counters for selected frames running on an Arm GPU.

## What devices are supported?

This layer requires Vulkan 1.0 and an Arm GPU because it uses an Arm-specific
performance counter sampling library.

## What data can be collected?

The layer serializes workloads for instrumented frames and injects counter
samples between them, allowing the layer to measure the hardware metrics for
Vulkan render passes, compute dispatches, transfers, etc.

The serialization is very invasive to wall-clock performance, due to removal
of pipeline overlap between workloads and additional GPU idle time waiting for
the layer to perform each performance counter sampling operation. This will
have an impact on the counter data being captured!

Derived counters that show queue and functional unit utilization as a
percentage of the overall "active" time of their parent block will report
too low. This is because of time spent refilling and then draining the GPU
pipeline for each serialized workload.

The overall _GPU Active Cycles_ counter is also known to be unreliable, because
the serialization means that command stream setup and teardown costs are not
hidden in the shadow of surrounding work. We recommend using the individual
queue active cycles counters as the main measure of workload cost.

Note that any counters that measure direct work, such as architectural issue
cycles, or identifiable workload nouns, such as primitives or threads, should
be unaffected by the loss of pipelining as the workload itself is functionally
unaffected by the addition of serialization.

Arm GPUs provide a wide range of performance counters covering many different
aspects of hardware performance. The layer will collect a standard set of
counters by default but, with source modification, can collect any of the
hardware counters and derived expressions supported by the
[libGPUCounters][LGC] library that Arm provides on GitHub.

[LGC]: https://github.com/ARM-software/libGPUCounters

### GPU clock frequency impact

The GPU idle time waiting for the CPU to take a counter sample can cause the
system DVFS power governor to decide that the GPU is not busy. In production
devices we commonly see that the GPU will be down-clocked during the
instrumented frame, which may have an impact on a some of the available
performance counters. For example, GPU memory latency may appear lower than
normal if the reduction in GPU clock makes the memory system look faster in
comparison.

When running on a pre-production device you can minimize the impacts of these
effects by pinning CPU, GPU, and bus clock frequencies. This is not usually
possible on a production device.

## How do I use the layer?

### Prerequisites

Device setup steps:

* Ensure your Android device is in developer mode, with `adb` support enabled
  in developer settings.
* Ensure the Android device is connected to your development workstation, and
  visible to `adb` with an authorized debug connection.

Application setup steps:

* Build a debuggable build of your application and install it on the Android
  device.

Tooling setup steps

* Install the Android platform tools and ensure `adb` is on your `PATH`
  environment variable.
* Install the Android NDK and set the `ANDROID_NDK_HOME` environment variable
  to its installation path.

### Layer build

Build the Profile layer for Android using the provided build script, or using
equivalent manual commands, from the `layer_gpu_profile` directory. For full
instructions see the _Build an Android layer_ and _Build a Linux layer_
sections in the [Build documentation](../docs/building.md).

### Running using the layer

You can configure a device to run a profile by using the Android helper utility
found in the root directory to configure the layer and manage the application.
You must enable the profile layer, and provide a configuration file to
parameterize it.

```sh
python3 lgl_android_install.py --layer layer_gpu_profile --config <your.json>  --profile <out_dir>
```

The [`layer_config.json`](layer_config.json) file in this directory is a
template configuration file you can start from. It defaults to periodic
sampling every 600 frames, but you can modify this to suit your needs.

The `--profile` option specifies an output directory on the host to contain
the CSV files written by the tool. One CSV is written for each frame, each CSV
containing a table with one row per workload profiled in the frame, listed
in API submit order.

The Android helper utility contains many other options for configuring the
application under test and the capture process. For full instructions see the
[Running on Android documentation](../docs/running_android.md).

## Layer configuration

The current layer supports two `sampling_mode` values:

* `periodic_frame`: Sample every N frames.
* `frame_list`: Sample specific frames.

When `mode` is `periodic_frame` the integer value of the `periodic_frame` key
defines the frame sampling period. The integer value of the
`periodic_min_frame` key defines the first possible frame that could be
profiled, allowing profiles to skip over any loading frames. By default frame 0
is ignored.

When `mode` is `frame_list` the value of the `frame_list` key defines a list
of integers giving the specific frames to capture.

## Layer counters

The current layer uses a hard-coded set of performance counters defined in the
`Device` class constructor. If you wish to collect different counters you must
edit the [Device source](./source.device.cpp) and rebuild the layer.

Any counters that are specified but that are not available on the current GPU
will be ignored.

- - -

_Copyright © 2025, Arm Limited and contributors._
