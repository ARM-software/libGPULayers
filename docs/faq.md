# Frequently asked questions

Some answers to commonly asked questions.

## Platform support

### Will you accept contributions for other platforms?

We are very willing to accept platform support contributions for the layer
skeleton generator.

### Will you accept new layer drivers?

We are currently not able to accept contributions for new pre-built layers, as
we have no way to test and maintain them. We encourage developers to share
their layer creations as new open-source projects.

We'd love to hear what you build, so let us know what you get up to!

### Will you add an Android OpenGL ES layer generation?

Yes, this is on our backlog.

### Will you add Arm Linux support for Vulkan layer generation?

Yes, this is on our backlog.

## Layer functionality

### Is there a way to select what gets intercepted?

You can do this by modifying the interception table in the generated code to
remove functions you do not want to intercept. There is currently no support
in the generator for specifying a user-provided function list.

- - -

_Copyright © 2024, Arm Limited and contributors._
