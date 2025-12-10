# About Vulkan layers

This page captures some interesting points to note about Vulkan layers, and is
mostly intended for developers of layers and maintainers of this project.

## Android vs Linux differences

Linux and Windows use the Khronos Vulkan loader, which has been extended over
time to have a richer loader-layer interface to support more use cases. The
current Khronos loader implements the v2 protocol from the
[Loader-Layer Interface][LLI] specification.

Android uses a custom Vulkan loader, which supports the basic v0 protocol with
some Android-specific limitations. This interface is functional, but lacks
some useful capabilities of the Khronos layer such as being able to intercept
pre-instance functions in implicit layers.

The libGPULayers framework has been designed to support both loaders, but
currently only supports functionality that works with the Android loader. There
are some areas that could be improved for Linux.

## Layer lifetime

Layer lifetime is managed by the Vulkan loader, and it is possible for a layer
to get loaded and unloaded multiple times within the lifetime of a single
application process. When a layer is unloaded, any global state is lost so
there is no way to use memory to persist per-process state in a layer as you
cannot guarantee you stay loaded.

On Android, layer libraries are loaded when the loader needs them (for a query
or to create an instance) and will be unloaded when a non-zero `VkInstance`
refcount is decremented and hits zero. They might subsequently be reloaded
again if the application restarts using Vulkan functionality.


## Querying Instance version

It could be useful for a layer to query `vkEnumerateInstanceVersion()` to
determine the maximum possible Vulkan API version supported on a platform,
although note that a device version might be a lower version so you need
to check both.

It is not possible for a layer to hook pre-instance functions on Android, and
only implicit layers are allowed to do it with the Khronos loader, so we do
not support doing this in libGPULayers. Layers must defer checking the
supported API versions until they get a concrete `VkDevice` to query, which
they would have to anyway, because the device version might be different to the
instance version.

Note: querying device version is much easier, because that uses normal
dispatchable Vulkan API functions, not pre-instance functions.

## Querying Instance extensions

Similar to the above, it could be useful for a layer to query the available
instance extensions using `vkEnumerateInstanceExtensionProperties()`. This
function is also a pre-instance function, and has the same limitations on
layer use as `vkEnumerateInstanceVersion()` in the section above, so it's not
supported in libGPULayers.

Because a layer cannot query the supported Vulkan version, or the available
instance extensions, layers that require the implementation beneath them to
support a specific extension simply have to assume that it is available.

This might result in an error on instance creation if the extension is not
supported. One possibility is that `vkCreateInstance()` will return
`VK_ERROR_EXTENSION_NOT_PRESENT`, because the extension is known but not
supported. Alternatively, it might result in undefined behavior, because the
layer passes in an extension structure on the `pNext` chain which is not known
by the version of Vulkan implemented by the loader or the driver.

Note: querying device extensions is much easier, as that uses normal
dispatchable Vulkan API functions, not pre-instance functions.

## Adding new extensions

Layers might expose extensions that the driver does not. Layers advertise their
new extensions by adding the extension strings and versions to the extension
properties list returned by `vkEnumerateInstanceExtensionProperties()` and
`vkEnumerateDeviceExtensionProperties()` when the `pLayerName` parameter is
the current layer's name.

For device extensions, it is also possible to modify the extension list
returned by the driver below by adding our extensions to the list returned
when `pLayerName` is `nullptr`.

The specification requires that implementations do not expose extensions that
conflict with other extensions but, given that a layer has no way to check
what other layers might be exposing, we just assume that our list is safe to
expose.

## Hiding device extensions

Layers might hide device extensions exposed by the layers below by modifying
the list returned by `vkEnumerateDeviceExtensionProperties()` when calling
down the stack, removing entries that the layer wants to hide before
returning it to the caller.

Note: This is only possible for device extensions, because instance extensions
are discovered per component by the loader, not in a layered manner.


## References

* [Loader-Layer Interface][LLI].

- - -

[LLI]: https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs

_Copyright © 2025, Arm Limited and contributors._
