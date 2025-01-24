# Layer: GPU Support

This layer is a tech support trick box that is designed to help diagnose causes
of functional and performance issues in applications. It works by letting you
quickly test your application with a set of API behavior overrides applied,
which can help to identify likely problem areas in the application if an
override causes an issue to disappear.

## Using this layer

This layer requires you to provide a configuration file that specifies the
overrides to apply. Details of the configuration options in each override
group are document in the Behavior overrides section below.

The [`layer_config.json`](layer_config.json) file in this directory is a
complete template configuration file you can start from. However, note that it
does not enable any overrides by default, so running the layer with this
configuration used "as is" will not do anything useful. Take a copy and
modify it to enable the options you want to try.

For Android you can run this layer with the following command line:

```sh
python3 lgl_android_install.py --layer layer_gpu_support --config <your.json>
```

## What devices are supported?

This layer is device agnostic and should support any GPU.

## Behavior overrides

The current override groups are supported:

* **Serialization:** control serialization of GPU workload scheduling to
  diagnose issues caused by missing queue or command stream synchronization.

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
irrespective of other settings.
* Else, the individual options are applied as specified.

```jsonc
"serialize": {
    "none": false,          // Enable no serialization options
    "all": false,           // Enable all serialization options
    "queue": false,         // Enable cross-queue serialization of submits
    "commandstream": {
        "compute": {
            "pre": false,   // Insert full barrier before dispatches
            "post": false   // Insert full barrier after dispatches
        },
        "renderpass": {
            "pre": false,   // Insert full barrier before render passes
            "post": false   // Insert full barrier after render passes
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
