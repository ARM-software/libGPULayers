# About

libGPULayers provides tooling to rapidly create new Vulkan layer drivers,
allowing developers to quickly generate new layers that can be used for
ad hoc experiments during development.

In addition, we provide a number of pre-built layers that have been built
using these tools. These layers can be used as standalone tools in their
own right, and some can be used alongside other Arm tools such as Arm
Performance Studio.

## What are layer drivers?

Layers drivers provide a standard mechanism to inject diagnostic functionality
between an application and the underlying graphics driver. Layer drivers
intercept the graphics API calls from the application, perform their diagnostic
function, and then make any necessary API calls into the underlying graphics
driver to actually perform the rendering operations. The ability to see, and
change, everything that the native driver sees makes layers an exceptionally
powerful tool for debugging functional and performance issues.

The Vulkan API defines a standard layer driver mechanism. The API uses layers
to implement API parameter validation and error checking, but they are also a
general purpose mechanism for all kinds of developer tooling.

## What is the purpose of this project?

We support many application developers during their development cycle. We
rarely get access to application source code, so layer drivers provide us with
an invaluable mechanism to make modifications to application API usage. The
`GPU Support` layer in this project is a a tool we use during technical support
investigations to quickly triage developers problems.

We also use layer drivers as a way to develop new API-aware debug and profiling
capabilities. The performance layers in this repository, such as the
`GPU Timeline` layer, are often early prototypes that we want to share with
developers to test new ideas and gather feedback. Some are designed to be used
as standalone development tools, others can also be used alongside other Arm
tools such as the Arm Streamline profiler in [Arm Performance Studio][2].

As you can tell, we find layers exceptionally useful. However, creating a new
layer from scratch requires a lot of boilerplate code and is fiddly to get
right. We therefore also wanted to take this opportunity to share our layer
generation tools which make it trivial to create a complete bare-bones layer
that is ready to extend and use.

## Supported devices

This library is currently tested on devices running Android or Linux, and using
Arm® Immortalis™ and Arm Mali™ GPUs. Contributions adding support for other
platforms is welcome.

# License

This project is licensed under the MIT license. By downloading any component
from this repository you acknowledge that you accept terms specified in the
[LICENSE.txt](LICENSE.txt) file.

# Documentation

Common documentation

* [Building a new layer](./docs/building.md)
* [Running using a layer on Android](./docs/running_android.md)
* [Running using a layer on Linux](./docs/running_linux.md)
* [Frequently asked questions](./docs/faq.md)

Layer documentation

* [Layer: GPU Support](./layer_gpu_support/LAYER_README.md)
* [Layer: GPU Timeline](./layer_gpu_support/LAYER_README.md)

# Support

If you have issues with the layer framework, or the prebuilt layers, please
raise them in the project's GitHub issue tracker.

If you have any questions about Arm GPUs, application development for Arm GPUs,
or general mobile graphics development or technology, please submit them on the
[Arm Community graphics forums][1].

- - -

_Copyright © 2024-2025, Arm Limited and contributors._

[1]: https://community.arm.com/support-forums/f/graphics-gaming-and-vr-forum/
[2]: https://developer.arm.com/Tools%20and%20Software/Arm%20Performance%20Studio
