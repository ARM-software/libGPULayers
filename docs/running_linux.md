# Running using a layer on Linux

There are multiple ways to install layer drivers for Linux. For our use case
we cannot usually modify the application binary, so we install the layer and
manifest in to a user-owned directory on the target device and configure the
layer driver using environment options.

## Create a manifest

Layers are specified to the system loader using a JSON manifest file. This file
must be called `manifest.json` and saved into a directory on the target device.
The example below shows the manifest for a generated layer called "Fizzbuzz".

```json
{
  "file_format_version": "1.1.2",
  "layer": {
      "name": "VK_LAYER_LGL_FIZZBUZZ",
      "type": "INSTANCE",
      "library_path": "./libVkLayerFizzbuzz.so",
      "api_version": "1.2.162",
      "implementation_version": "1",
      "description": "Vulkan layer that does something useful and interesting."
  }
}
```

## Install the layer

Copy the built layer into the same directory as the manifest on the target
device.

## Run the application

Our layer is not a system layer, so we use environment variables to tell the
Vulkan loader that our layer exists and where to load it from.

Assuming both the manifest (`manifest.json`) and the built layer binary
(`libVkLayerFizzbuzz.so`) are saved in the `vkwork` directory in the user home
area, the following command should run the Vulkan `vkcube` sample with the
Fizzbuzz layer loaded.

```bash
env VK_LOADER_DEBUG=all \
    VK_LAYER_PATH=$VK_LAYER_PATH:/home/${USER}/vkwork \
    LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/${USER}/vkwork \
    VK_INSTANCE_LAYERS=VK_LAYER_LGL_FIZZBUZZ \
    vkcube
```

The `VK_LOADER_DEBUG=all` option enables verbose logging in the loader itself,
and is a useful tool that might help you work out why your layer is not being
loaded when you expect. Once your layer is being loaded correctly, this option
should be removed.

## Uninstall

If you follow the steps above, no persistent system state is modified. Running
an application without any of the environment variables set will run without
the Fizzbuzz layer installed.

- - -

_Copyright © 2024-2025, Arm Limited and contributors._
