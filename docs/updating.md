# Updating layers

This page gives you instructions for updating an existing layer to use a newer
version of Vulkan.

## Updating Vulkan version

When updating to a newer version of Vulkan, there are three things that need to
be updated in sync or things will break:

* Upstream Vulkan headers (submodule)
* Upstream Vulkan utilities library (submodule)
* Generated common code in libGPULayers

### Updating submodules

Updating Khronos Vulkan headers, e.g.:

```sh
pushd .
cd ./source_third_party/khronos/vulkan/
git checkout v1.4.359
popd
```

Updating Khronos Vulkan utilities library, e.g.:

```sh
pushd .
cd ./source_third_party/khronos/vulkan-utilities/
git checkout v1.4.359
popd
```

### Updating generated code

After you have updated the Khronos Vulkan headers, which includes the
machine-readable XML, you can regenerate the auto-generated common code:

```sh
python3 ./generator/generate_vulkan_common.py
```

### Committing your changes

All three of these changes need to land at the same time to avoid runtime
errors caused by any mismatches or unknown structures.

For maintainers updating GitHub, ensure you commit all three together when
raising a new PR to update Vulkan.

## Updating existing layers

When updating to a newer Vulkan version, existing layers might need to be
updated.

We recommend layers use a forwarding pattern, which returns Vulkan API handles
from the layer below to the application. This means that any new entrypoints
will see a valid handle, and will function as expected if a layer does not
intercept them. It is common that this style of layer needs no updates, unless
a new API function needs to be explicitly processed to implement the desired
functionality in the layer itself.

For maintainers updating GitHub, we usually commit layer updates to support new
API entry points as per-layer commits, separately from the triggering Vulkan
API update. This makes patch sets smaller and easier to review.

- - -

_Copyright © 2026, Arm Limited and contributors._
