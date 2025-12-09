# Extension support in a layer

It might be useful for some layers to implement an extension, such as
`VK_EXT_frame_boundary`, even if the underlying driver does not support it.
This page explains the general approach that needs to be taken, and the
specific API modifications that need to be applied for specific extensions.

Note that the core framework allows you to expose additional extensions via
the default `vkEnumerate*ExtensionProperties()` implementation, but per-layer
code must implement the API modifications to other functions as needed.

## Exposing a new extension

New extensions are advertised to applications by adding the extension string to
the list returned by `vkEnumerate*ExtensionProperties()`. This functionality
is provided in the common framework default functions. Layer implementations
add the new extension information that they want to expose to either:

* `Instance::injectedInstanceExtensions` for instance extensions.
* `Instance::injectedDeviceExtensions` for device extensions.

Device extensions will be removed from this list if we can detect that the
underlying device already supports them, which means we can just pass through.

### Handling extended API entry points

All entrypoints that are touched by an extension need to be intercepted with
a `user_tag` version of a function, which will implement the functionality that
the layer requires.

If the driver beneath the layer actually supports the extension, the extended
API parameters can be passed down to the driver without modification. This
scenario can be detected by checking that the extension name is no longer in
the `injectedExtensions` list, although the layer will probably want to cache
this check to reduce performance overhead.

If the driver beneath the layer does not support the extension, the extended
API parameters must be rewritten to remove the extension before passing down
to the driver. User structure inputs to the Vulkan API are usually marked as
`const`, so we must take a safe-struct copy which we can modify and pass
that copy to the driver.

## Common extension notes

This section is a set of brief notes about extensions that we have implemented,
summarizing the changes needed and referencing where you can find an example
of the changes if you need something similar.

### VK_EXT_frame_boundary

This extension allows applications to annotate arbitrary submit calls to
indicate which frame the submitted work belongs to, instead of relying on
`vkQueuePresent()`. This can be useful for multi-threaded applications,
where CPU processing for frames can overlap, and for applications which
do not have frames, but that want to use tools such as RenderDoc that
require them.

#### Exposing extension

Adding exposure handling:

* Add `VK_EXT_frame_boundary` to device extension list.
* Add `VkPhysicalDeviceFrameBoundary` to `VkPhysicalDeviceFeatures2.pNext` list
  returned by `vkGetPhysicalDeviceFeatures2()`, or force existing structure to
  `VK_TRUE`, if not supported by driver.
* Query `VkPhysicalDeviceFrameBoundary` in `VkDeviceCreateInfo.pNext` to see if
  application enabled the extension. Strip if not supported by the driver.

#### Implementing extension

Adding implementation handling:

* Add `VkFrameBoundaryEXT` extension struct handling to:
  * `vkQueueSubmit()`
  * `vkQueueSubmit2()`
  * `vkQueuePresent()`
  * `vkQueueBindSparse()`

#### Implementation notes

Most applications using this that I have seen are using it to demarcate frames
when using a single submitting render thread for off-screen rendering or
compute use cases that do not use `vkQueuePresent()`. In these systems just
detecting a change in frame ID is enough to indicate "frame changed", much
how we would use `vkQueuePresent()` to do the same without this extension.

It is possible for applications to have multiple concurrent frames being
submitted in an overlapping manner, which can be handled by tagging work with
the frame ID found in the extension structure for each `vkQueue*()` call. This
will require downstream data handling to cope with overlapping frame
submissions, which most of our layers do not handle, as it is rarely
encountered.

- - -

_Copyright © 2025, Arm Limited and contributors._
