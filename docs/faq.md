# Frequently asked questions

Some answers to commonly asked questions.

## Platform support

### Will you accept contributions for other platforms?

We are very willing to accept platform support contributions for the layer
generator and common code.

### Will you accept new layer drivers?

We are not able to accept contributions for new pre-built layers, as we have no
way to test and maintain them. We encourage developers to share their layer
creations as new open-source projects.

We'd love to hear what you build, so let us know what you get up to!

### Will you add support for Android OpenGL ES layer generation?

No, this is no longer planned.

## Layer functionality

### Is there a way to select what gets intercepted?

By default only essential entrypoints required by the layer framework, or
specific entrypoints implemented as `user_tag` specializations in a layer
project, are intercepted. Unused entrypoints are not intercepted unless the
`LGL_CONFIG_OPTIMIZE_DISPATCH` option is disabled.

- - -

_Copyright © 2024-2025, Arm Limited and contributors._
