# Layer: GPU Support

This layer is a tech support trick box that is designed to help diagnose causes
of functional and performance issues in applications. It works by letting you
quickly test your application with a set of API behavior overrides applied,
which can help to identify likely problem areas in the application if an
override causes an issue to disappear.

## What devices are supported?

This layer requires Vulkan 1.1 and timeline semaphores, but it does not rely on
any vendor-specific behavior.

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

Build the Support layer for Android using the provided build script, or using
equivalent manual commands, from the `layer_gpu_support` directory. For full
instructions see the _Build an Android layer_ and _Build a Linux layer_
sections in the [Build documentation](../docs/building.md).

### Running using the layer

You can perform support experiments by using the Android helper utility found
in the root directory to configure the layer and manage the application. You
must enable the support layer, and provide a configuration file to parameterize
it.

```sh
python3 lgl_android_install.py --layer layer_gpu_support --config <your.json>
```

The [`layer_config.json`](layer_config.json) file in this directory is a
template configuration file you can start from. It does not enable any
overrides by default, so running the layer using this configuration "as is"
will not do anything useful. Take a copy and modify it to enable the options
you want to try. Details of the configuration options in each override group
are document in the _Behavior overrides_ section below.

The Android helper utility contains many other options for configuring the
application under test and the capture process. For full instructions see the
[Running on Android documentation](../docs/running_android.md).

## Behavior overrides

The current override groups are supported:

* **Feature:** control use of optional Vulkan features that can impact
  correctness and performance.
* **Serialization:** control serialization of GPU workload scheduling to
  diagnose issues caused by missing queue or command stream synchronization.
* **Shaders and Pipelines:** control shader pipeline compilation to diagnose
  issues caused by shader precision issues.
* **Framebuffers:** control use of lossy and lossless image compression for
  uncompressed images that may be used as framebuffer attachments.

### Features

The feature overrides allow forceful enable or disable of optional features
in the API.

#### Configuration options

The configuration file allows optional features to be force-enabled or
force-disabled. If no forced setting is enabled, application behavior is
left unmodified. Only a single force setting per feature should be set to
avoid ambiguous settings.

```jsonc
"feature": {
    "robustBufferAccess_enable": false, // Force enable robustBufferAccess
    "robustBufferAccess_disable": false // Force disable robustBufferAccess
},
```

### Serialization

The serialization overrides allow forceful serialization of submitted
workloads, ensuring that they run in queue submit order. The synchronization
can be configured per workload type, allowing control over where serialization
is added to command buffers and queues.

#### Configuration options

The configuration file allows control over specific options, as well as
convenience options to force disable or enable all serialization.

* If the `none` option is `true` then no serialization is applied, irrespective
  of other settings.
* Else, if the `all` option is `true` then all serialization is applied,
  irrespective of other settings, with the exception of `queue_wait_idle` which
  must be enabled individually due to its extreme performance overhead.
* Else, the individual options are applied as specified.

```jsonc
"serialize": {
    "none": false,            // Enable no serialization options
    "all": false,             // Enable all serialization options except queue_wait_idle
    "queue": false,           // Force cross-queue serialization of submits
    "queue_wait_idle": false, // Insert vkDeviceWaitIdle after submits
    "commandstream": {
        "compute": {
            "pre": false,   // Insert full barrier before dispatches
            "post": false   // Insert full barrier after dispatches
        },
        "renderpass": {
            "pre": false,   // Insert full barrier before render passes
            "post": false   // Insert full barrier after render passes
        },
        "asbuild": {
            "pre": false,   // Insert full barrier before acceleration structure builds
            "post": false   // Insert full barrier after acceleration structure builds
        },
        "tracerays": {
            "pre": false,   // Insert full barrier before trace rays
            "post": false   // Insert full barrier after trace rays
        },
        "transfer": {
            "pre": false,   // Insert full barrier before transfers
            "post": false   // Insert full barrier after transfers
        }
    }
}
```

## Shaders and Pipelines

The shaders and pipelines overrides allow some control over how the shader
compiler handles compilation tasks.

#### Configuration options

```jsonc
"shader": {
    "disable_cache": false,              // Disable use of binary caches
    "disable_relaxed_precision": false,  // Disable use of relaxed precision decoration
    "enable_spirv_fuzz": false           // Enable SPIR-V fuzzing to change binary hash
}
```

## Framebuffers

The framebuffer overrides allows some control over how the framebuffers are
allocated and handled by the driver.

* If the `disable_compression` option is `true` then compression is always
  disabled, irrespective of other settings.
* Else, if the `force_default_compression` option is `true` then all images
  will be forced to use default compression (i.e. stripping all application use
  of fixed rate compression), irrespective of the fixed rate setting.
* Else, the `force_fixed_rate_compression` will be used to force fixed rate
  compression as close as possible (but no lower) than the specified bits
  per component setting. Images that do not support a fixed rate compression
  level that meets this bit rate requirement will be left at the original
  application setting.

#### Configuration options

```jsonc
"framebuffer": {
    "disable_compression": false,        // Disable all use of compression
    "force_default_compression": false,  // Force driver default compression
    "force_fixed_rate_compression": 0    // Force use of fixed rate compression as close
                                         // to this bits-per-channel as possible, but
                                         // no lower (0 = do not force)
}
```

- - -

_Copyright © 2025, Arm Limited and contributors._
