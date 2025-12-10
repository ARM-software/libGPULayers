# Layer: GPU Timeline - Developer Documentation

This layer is used with Arm GPU tooling that shows the scheduling of workloads
on to the GPU hardware queue. The layer provides additional semantic
annotation, extending the scheduling data from the Android Perfetto render
stages telemetry with useful API-aware context.

## Command stream modelling

Most properties we track are a property of the command buffer recording in
isolation. However, the user debug label stack is a property of the queue and
persists across submits. We therefore only determine the debug label
associated with a workload in the command stream at submit time, and must
resolve it per workload inside the command buffer.

To support this we implement a software command stream that contains simple
bytecode actions that represent the sequence of debug label and workload
commands inside each command buffer. This "command stream" is played to update
the queue state at submit time, triggering metadata submission for each
workload that snapshots the current state of the user debug label stack at
that point in the command stream.

## Updating protobuf

The protocol between the layer and the host tools uses Google Protocol
Buffers to implement the message encoding.

The layer implementation uses Protopuf, a light-weight implementation which
is easily integrated in to the layer. Protopuf message definitions are
defined directly in the C++ code (see `timeline_protobuf_encoder.cpp`) and do
not use the `timeline.proto` definitions.

The host implementation uses the Google `protoc` compiler to generate native
bindings from the `timeline.proto` definition. When updating the protocol
buffers you must ensure that the C++ and `proto` definitions match.

To regenerate the Python bindings, found in `lglpy/timeline/protos`, run the
following command from the `layer_gpu_timeline` directory:

```sh
protoc ./timeline.proto --python_out=../lglpy/timeline/protos/layer_driver/
```

- - -

_Copyright © 2024-2025, Arm Limited and contributors._
