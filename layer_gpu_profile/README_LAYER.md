# Layer: GPU Profile

This layer is a frame profiler that can capture per workload performance
counters for selected frames running on an Arm GPU.

## What devices are supported?

This layer requires Vulkan 1.0 and an Arm GPU because it uses an Arm-specific
counter sampling library.

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
