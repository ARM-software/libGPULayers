# Creating a new layer

Layers are generated automatically from the Khronos specification XML.

## Checking out the code

From the directory you want to contain the code, check out the project and the
Khronos registry dependencies:

```sh
git clone https://github.com/ARM-software/libGPUlayers ./
git submodule update --init
```

## Generate the layer skelton

Use the Python script to generate the layer driver skeleton. Replace the
placeholder "Demo" with your layer name, but the layer name must start with
`VkLayer` to be considered a legal Vulkan layer.

```
python3 --project-name VkLayerDemo --output layer_demo
```

## Build the layer

A standard build script is provided for Linux hosts. Build the layer using the
helper script, specifying either `Release` or `Debug` as your build type.

```sh
export ANDROID_NDK_HOME=/path/to/android/ndk

cd layer_demo
./android_build.sh Release
```

**Note:** The skeleton layer does nothing other than intercept all of the
Vulkan API entry points and forward them to the next layer/driver in the stack.
You must edit the skeleton source code to make it do something useful ...

- - -

_Copyright © 2024, Arm Limited and contributors._
