# Updating the generated protobuf (de)serialization code

This project uses protobufs for (de)serialization of certain data:

 * In the raw GPU timeline messages sent from `layer_gpu_timeline` to the host.
 * In the Perfetto data collected from the device.

Python decoders for those protocols are pre-generated and stored in the sources
under `lglpy/timeline/protos`. 

To regenerate or update the timeline protocol files use:

        protoc -I layer_gpu_timeline/                           \
            --python_out=lglpy/timeline/protos/layer_driver/    \
            layer_gpu_timeline/timeline.proto

- - -

_Copyright © 2025, Arm Limited and contributors._
