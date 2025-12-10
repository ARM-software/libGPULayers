# Creating a new layer

Layer creation is automated, allowing you to quickly create a new layer that is
complete and ready to use. After creating your new layer, all that you need to
do is add the additional API intercepts your layer needs to implement the
custom functionality that you want it to provide.

## Checking out the code

From the directory you want to contain the code, check out the project and all
third-party dependencies:

```sh
git clone https://github.com/ARM-software/libGPUlayers ./
git submodule update --init
```

## Generate the new layer project

Create your new layer, using a Python script to generate the project
directory containing the layer code. Replace the placeholder "Demo" with your
layer name.

```sh
python3 ./generator/generate_vulkan_layer.py --project-name VkLayerDemo --output layer_demo
```

* The Vulkan layer name must start with `VkLayer` and have a title-case name,
  e.g. `VkLayerExampleName`.
* The output directory name should start with `layer_` and have a snake-case
  name, e.g. `layer_example_name`.
* The output directory must be in the root of the git checkout, making it a
  sibling of the `source_common` directory.

You now have a complete layer that is ready to use! This layer does nothing
useful yet, but it is functional and is deployable. You must now edit the layer
code to make it do something useful.

### Generate the common code (optional)

The common code is checked into the repository, and should not need
regenerating unless you need to use a newer version of the Vulkan
specification.

Update the version of the Vulkan specification by updating the git version of
the `khronos/vulkan` submodule.

Once updated, regenerate the common code using a Python script:

```sh
python3 ./generator/generate_vulkan_common.py
```

## Adding custom intercepts to your layer

Custom intercept functions are implemented in your layer source tree, using
C++ template specialization to override the default implementations provided
in the common code.

### Adding intercept declarations

Instance function intercepts must be declared in a header called
`layer_instance_functions.hpp` in your layer `source` directory.

Device function intercepts must be declared in a header called
`layer_device_functions.hpp` in your layer `source` directory.

The function prototypes for a layer implementation must be templated versions
of the normal Vulkan prototype, with the type `user_tag` used for tag dispatch.

```C++
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode<user_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode);
```

When you build your layer, the compiler will automatically select your
`user_tag` specializations over the `default_tag` implementation provided in
the common code.

### Adding intercept definitions

The example below shows a typical no-op intercept implementation.

```C++
template <>
VKAPI_ATTR void VKAPI_CALL layer_vkCmdSetCullMode<user_tag>(
    VkCommandBuffer commandBuffer,
    VkCullModeFlags cullMode
) {
    LAYER_TRACE(__func__);

    // Hold the lock to access layer-wide global store
    std::unique_lock<std::mutex> lock { g_vulkanLock };
    auto* layer = Device::retrieve(commandBuffer);

    // Release the lock to call into the driver
    lock.unlock();
    layer->driver.vkCmdSetCullMode(commandBuffer, cullMode);
}
```

The framework uses a forwarding design for Vulkan handles, returning native
driver handles to the application and storing its local `Instance` or `Device`
context as side-band information held in the layer. This allows a layer to only
intercept a subset of the entry points without having to translate handles
everywhere.

Use the `Instance::retrieve()` and `Device::retrieve()` functions to retrieve
the layer context, using the API dispatchable handle as the key. Because
Vulkan is multi-threaded, any lookups into these shared structures must be
done with the layer-wide lock held.

You will typically want to release the layer-wide lock before calling in to
the driver to reduce the performance impact of having the layer installed on
multi-threaded Vulkan applications. How early you are able to release the lock
before calling the driver will depend on what your layer does.

### Overriding layer entrypoints

For most Vulkan API functions, the common code does nothing other than
providing a pass-through no-op, which will not be used at all unless the
`LGL_CONFIG_OPTIMIZE_DISPATCH` build option is disabled.

There are a number of functions in the common code that provide a manually
authored implementation because the layer needs to do something specific to
talk to the loader and to initialize itself. These functions include:

* `layer_vkGetInstanceProcAddr()`
* `layer_vkGetDeviceProcAddr()`
* `layer_vkEnumerateInstanceExtensionProperties()`
* `layer_vkEnumerateDeviceExtensionProperties()`
* `layer_vkEnumerateInstanceLayerProperties()`
* `layer_vkEnumerateDeviceLayerProperties()`
* `layer_vkCreateInstance()`
* `layer_vkDestroyInstance()`
* `layer_vkCreateDevice()`
* `layer_vkDestroyDevice()`

These are all implemented as `default_tag` implementations. A user layer might
still override any of these with a `user_tag` specialization if needed, but
must reimplement the required functionality taken from the common
implementation to ensure the layer still works. The common function
implementations are found in `source_common/framework/manual_functions.cpp`.

- - -

_Copyright © 2024-2025, Arm Limited and contributors._
