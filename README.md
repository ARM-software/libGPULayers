# About

libGPULayers provides tooling for creating a skeleton implementation of a
graphics API layer driver. Over time, we plan to add a set of useful
ready-to-use diagnostic layers that have been built using the tooling.

## What are layer drivers?

Layers drivers provide a standard mechanism to inject diagnostic functionality
between an application and the underlying graphics driver. Layer drivers
intercept the graphics API calls from the application, perform their diagnostic
function, and then make any necessary API calls into the underlying graphics
driver to actually perform the rendering operations. The ability to see, and
change, everything that the native driver sees makes layers an exceptionally
powerful tool for debugging functional and performance issues.

The Vulkan API defines a standard layer driver mechanism. The API uses layers
to implement API parameter validation and error checking, but they are a
general purpose mechanism for all kinds of developer tooling.

The OpenGL ES API does not have layer drivers as a standard feature. However,
since Android 10, the Android OpenGL ES loader has implemented support for
OpenGL ES layers, so we can access the same methodology benefits as Vulkan.

## What is the purpose of this project?

We support many application developers during their development cycle. We
rarely get access to application source code, so layer drivers provide us a
convenient way for us to make modifications to API behavior. We use this
capability to triage bugs and to test the impact of application API usage fixes
and optimizations, and wanted to share the capability with our wider developer
ecosystem.

This project has two main goals:

* Firstly, it provides developers with access to the same easy-to-use layer
  generation tooling that we use internally, allowing them to perform their
  own experiments using layers.
* Secondly, we will use this layer generation to provide a number of pre-built
  layers than can be used during development to debug and optimize application
  rendering.

## Supported devices

This library is currently tested on devices running Android and using Arm®
Immortalis™ and Arm Mali™ GPUs. Contributions adding support for other
platforms is welcome.

# License

This project is licensed under the MIT license. By downloading any component
from this repository you acknowledge that you accept terms specified in the
[LICENSE.txt](LICENSE.txt) file.

# Documentation

* [Building a new layer](./docs/building.md)
* [Running using a layer on Android](./docs/running_android.md)
* [Running using a layer on Linux](./docs/running_linux.md)
* [Frequently asked questions](./docs/faq.md)

# Support

If you have issues with the layer framework, or the prebuilt layers, please
raise them in the project's GitHub issue tracker.

If you have any questions about Arm GPUs, application development for Arm GPUs,
or general mobile graphics development or technology please submit them on the
[Arm Community graphics forums][1].

- - -

_Copyright © 2024, Arm Limited and contributors._

[1]: https://community.arm.com/support-forums/f/graphics-gaming-and-vr-forum/
