# Building layers

This page gives you instructions for building a layer that already exists.

## Building for Android

You must have the following tools installed and on your `PATH`:

* CMake
* GNU Make

You must also have the Android NDK installed, and the `ANDROID_NDK_HOME`
environment variable must be set to the root of the NDK installation.

```sh
cd <layer_dir>

cmake \
  -B <build_dir> \
  -G "Unix Makefiles" \
  -DCMAKE_SYSTEM_NAME=Android \
  -DANDROID_PLATFORM=29 \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_TOOLCHAIN=clang \
  -DANDROID_STL=c++_static \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake" \
  ..

cmake --build <build_dir>
```

CMake builds are build system agnostic. You can replace GNU Make with another
build system, such as Ninja, if you prefer.

An Android build script for Linux hosts, `./android_build.sh`, is provided
as a convenience wrapper for the commands above. It is not required to use
this; it is primarily included to provide a one-line build for our CI test
system.

## Build for Linux

You must have the following tools installed and on your `PATH`:

* CMake
* GNU Make

```sh
cd <layer_dir>

cmake \
  -B <build_dir> \
  -G "Unix Makefiles" \
  -DCMAKE_BUILD_TYPE=Release \
  ..

cmake --build <build_dir>
```

## Build options

The standard layer generation provides some optional build options which you
optionally set during CMake configuration.

`LGL_CONFIG_LOG` controls logging to logcat (Android) or stdout (Linux). It is
on by default, and is disabled using `-DLGL_CONFIG_LOG=OFF` on the CMake
configure line.

`LGL_CONFIG_TRACE` controls logging API entrypoint calls to logcat (Android) or
stdout. It is disabled by default, and is enabled using `-DLGL_CONFIG_TRACE=ON`
on the CMake configure line. Note that this option has a high performance
overhead, due to the amount of logging it creates, but it is a quick way to
discover what entrypoints an application is using.

`LGL_CONFIG_OPTIMIZE_DISPATCH` controls whether the layer optimizes away
unnecessary `default_tag` intercepts, allowing API calls to bypass the layer
and call directly to the layer/driver below. It is enabled by default, and is
be disabled using `-DLGL_CONFIG_OPTIMIZE_DISPATCH=OFF` on the CMake configure
line. Disabling this optimization is useful when used in conjunction with
`LGL_CONFIG_TRACE` if you want to trace all entrypoints, and not just the ones
that the layer normally intercepts.

- - -

_Copyright © 2024-2025, Arm Limited and contributors._
