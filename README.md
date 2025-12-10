# About

libGPULayers provides tooling to create new Vulkan layer drivers, allowing
you to quickly generate new layers suitable for creation of new developer tools
or for ad hoc experiments during development.

In addition, we provide a number of pre-built layers that have been built
using this framework. These layers might be used as standalone tools in their
own right, or might be used alongside other Arm tools such as
[Arm Performance Studio][2].

## What are layer drivers?

Layer drivers provide a standard mechanism to inject diagnostic functionality
between an application and the underlying graphics driver. Layer drivers
intercept the graphics API calls from the application, perform their diagnostic
function, and then call into the underlying graphics driver to actually perform
the requested operation. The ability to see, and change, the calls into the
native driver makes layers an exceptionally powerful tool for debugging both
functional and performance issues.

Layer drivers are designed in to the Vulkan API, and they are the mechanism
for common workflows such as error checking using the Vulkan Validation Layer
(VVL), but they are also a general purpose mechanism suitable for all kinds of
developer tooling.

## What is the purpose of this project?

We help many application developers to investigate issues during their
development cycle. We rarely get access to application source code for these
investigations, and cannot change drivers on production devices. Layer drivers
provide us with an invaluable mechanism to monitor and make modifications to
application API usage without needing to modify the application itself. The
`GPU Support` layer in this project is a tool we use during technical
support investigations to quickly triage problems.

We also use layer drivers as a way to develop new API-aware debug and profiling
capabilities. The performance layers in this repository, such as the
`GPU Profile` and `GPU Timeline` layers, are used to profile performance,
or add API-aware annotations to performance captures made using other tooling.

As you might be able to tell, we find layers exceptionally useful, and we
often want to create ad hoc layers to use for one-off experiments. Creating a
new layer from scratch requires a lot of code and is fiddly to get right, with
obscure errors when it doesn't work, so we wrote a tool to automate layer
creation. This final part of this project is this layer generation tooling,
which you use to quickly create a new layer that is ready to deploy.

## Supported devices

This library is currently tested on devices running Android or Linux, and using
Arm® Immortalis™ and Arm Mali™ GPUs. Contributions adding support for other
platforms are welcome.

# License

This project is licensed under the MIT license. By downloading any component
from this repository you acknowledge that you accept terms specified in the
[LICENSE.txt](LICENSE.txt) file.

# Documentation

Common documentation

* [Building a layer](./docs/building.md)
* [Creating a new layer](./docs/creating.md)
* [Running using a layer on Android](./docs/running_android.md)
* [Running using a layer on Linux](./docs/running_linux.md)
* [About layers design notes](./docs/about_layers.md)
* [Frequently asked questions](./docs/faq.md)

Layer documentation

* [Layer: GPU Support](./layer_gpu_support/README_LAYER.md)
* [Layer: GPU Profile](./layer_gpu_support/README_LAYER.md)
* [Layer: GPU Timeline](./layer_gpu_timeline/README_LAYER.md)

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
