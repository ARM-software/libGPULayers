# Running using a layer on Android

There are multiple ways to install layer drivers for Android. For our use case
we cannot usually modify the application binary, so we install the layer into
the target application data directory on the file system.

## Script configuration

When generating a new layer, the generator also creates an installation
script for Android with the correct settings to use.

To install and configure a layer for use, run this script with the name of
the package that you want to instrument:

```sh
py -3 android_install.py --package <com.example.app>
```

... run your test scenario, and then press any key to wake the script and
remove the layer from the device.

## Manual configuration

For users with existing configuration flows, Vulkan layers can be manually
configured using `adb` to copy the files and set the system properties.

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

_Copyright © 2024, Arm Limited and contributors._
