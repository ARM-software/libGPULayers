# Running using a layer on Android

To make it easy to install and configure layers for Android, we provide an
installation script which can automatically configure one or more layers.

These instruction assume that you have already built the layers that you want
to install. See the [Building a new layer](./building.md) page for build
instructions.

## Script configuration

From the root directory of the GitHub project run the Android installation
utility, specifying the directory containing the layer that you want to
install:

```sh
python3 lgl_android_install.py --layer layer_gpu_example
```

By default the script will automatically search to find connected Android
devices, and debuggable packages on the chosen device. If there are multiple
options the script will present a menu and prompt you for a selection. You
can avoid this by manually specifying the device (`--device`/`-D`) and package
(`--package`/`-P`) to instrument.

Wait for the layer to be installed and configured. The script will notify you
when this has been done. You can now perform your development work. When you
are finished, return to the script and press a key to notify it that it can
clean up the device and remove the layers.

### Layer configuration

Some layers require a configuration file to control their behavior. Most
layers that need a configuration file ship with a default config,
`layer_config.json`, in their layer directory. Users can override this with
a custom config by using the `--config`/`-C` option to specify a custom
config file.

**NOTE:** The layer that each config file applies to is specified in the config
file itself, and is not implied by command line order.

### Multi-layer installation

The script can install multiple layers in a stack. Specify the `--layer`/`-L`
option multiple times, once per layer. Layers are stacked in command line
order, with the first layer specified being the top of the stack closest to the
application.

### Khronos validation layer installation

The script can install the Khronos validation layer. A dummy layer directory ,
`layer_khronos_validation`, is provided. Download the the latest binary release
from the [Vulkan-ValidationLayers/releases][1] GitHub, and place the binaries
into dummy build tree at the correct location.

Once this is done you can install the validation layer like any other.

**NOTE:** When installing the Khronos validation layer you need to decide where
to install it in the layer stack. If you install it as the first layer in the
stack it will only report issues from the application. If you install it last,
it will report errors from the application and all layers above it in the
stack.

### Capturing Android logcat

During development it is often useful to capture the Android log, using
`logcat` to save it to a file on the host.

If you specify the `--logcat <file>` option the script will automatically clear
the logcat log after installing the layers, and start recording logcat to the
specified file. Logcat recording will end during device clean up.

### Capturing Android Perfetto traces

The Timeline layer is designed to provide semantic metadata that can be used
to annotate an Android Perfetto render stages trace. This provides profiling
tools with API information that Perfetto alone cannot provide, making it a
much more data-rich visualization .

If you specify the `--perfetto <file>` option the script will automatically
configure Perfetto to capture render stages information for the target
application and save it to the specified file.

## Manual configuration

For users with existing configuration flows, Vulkan layers can be manually
configured using `adb` to copy the files and set the system properties.

For layers with configuration files, the configuration file must be named
after the layer (e.g. `VK_LAYER_LGL_GPUSUPPORT.json`) and then pushed to
the `/data/local/tmp` directory with global (`0666`) access permissions.

**Note:** Android will fail to start an application if it has a layer enabled,
but the layer library cannot be found. Ensure that you disable your layer when
you have finished using it.

### Install

```sh
PACKAGE=com.example.app
LAYER_LIB=libVkLayerDemo.so
LAYER_NAME=VK_LAYER_LGL_DEMO

adb push $LAYER_LIB /data/local/tmp
adb shell run-as $PACKAGE cp /data/local/tmp/$LAYER_LIB .
adb shell settings put global enable_gpu_debug_layers 1
adb shell settings put global gpu_debug_app $PACKAGE
adb shell settings put global gpu_debug_layer_app $PACKAGE
adb shell settings put global gpu_debug_layers $LAYER_NAME
```

### Uninstall

```sh
PACKAGE=com.example.app
LAYER_LIB=libVkLayerDemo.so
LAYER_NAME=VK_LAYER_LGL_DEMO

adb shell rm /data/local/tmp/$LAYER_LIB
adb shell run-as $PACKAGE rm $LAYER_LIB
adb shell settings delete global enable_gpu_debug_layers
adb shell settings delete global gpu_debug_app
adb shell settings delete global gpu_debug_layers
adb shell settings delete global gpu_debug_layer_app
```

- - -

_Copyright © 2024-2025, Arm Limited and contributors._

[1]: https://github.com/KhronosGroup/Vulkan-ValidationLayers/releases/