#!/bin/bash
# Compile and run test_multiple.cpp natively (direct GPU, no GVirtuS interception).
# Uses the existing OpenPose build inside openpose_gvirtus:cuda12.6 but overrides
# LD_LIBRARY_PATH so CUDA calls go straight to the local GPU.
set -e

OPENPOSE_ROOT=/opt/openpose
IMAGE="${OPENPOSE_IMAGE:-openpose_gvirtus:cuda12.6}"
# Lower resolution = less VRAM. Default uses the OpenPose-style size, which now
# fits with the smaller COCO pose model.
# Override with e.g.: NET_RESOLUTION=320x-1 make run-openpose-native-test
NET_RESOLUTION="${NET_RESOLUTION:--1x368}"
# Fewer runs by default for quick/low-memory smoke checks.
NUM_RUNS="${NUM_RUNS:-1}"
# Use a lighter pose model and CPU rendering by default to reduce VRAM while
# still producing visible pose overlays.
MODEL_POSE="${MODEL_POSE:-COCO}"
RENDER_POSE="${RENDER_POSE:-1}"
SCALE_NUMBER="${SCALE_NUMBER:-1}"

# Real CUDA + OpenPose libs only — GVirtuS frontend intentionally excluded.
NATIVE_LD_PATH="\
${OPENPOSE_ROOT}/build/src/openpose:\
${OPENPOSE_ROOT}/build/caffe/lib:\
/usr/local/cuda/lib64:\
/usr/local/nvidia/lib:\
/usr/local/nvidia/lib64"

echo "==> Image : ${IMAGE}"
echo "==> Using native CUDA (no GVirtuS)"
echo "==> net_resolution=${NET_RESOLUTION}, num_runs=${NUM_RUNS}, model_pose=${MODEL_POSE}, render_pose=${RENDER_POSE}, scale_number=${SCALE_NUMBER}"

docker run --rm \
  --name openpose_native_test \
  --runtime=nvidia \
  -e LD_LIBRARY_PATH="${NATIVE_LD_PATH}" \
  -e NET_RESOLUTION="${NET_RESOLUTION}" \
  -e NUM_RUNS="${NUM_RUNS}" \
  -e MODEL_POSE="${MODEL_POSE}" \
  -e RENDER_POSE="${RENDER_POSE}" \
  -e SCALE_NUMBER="${SCALE_NUMBER}" \
  -v "$(pwd)/examples/openpose/00_test.cpp:${OPENPOSE_ROOT}/examples/gvirtus/00_test.cpp:ro" \
  -v "$(pwd)/examples/openpose/media:${OPENPOSE_ROOT}/examples/media:rw" \
  "${IMAGE}" \
  bash -c "
    set -e
    OPENPOSE_ROOT=${OPENPOSE_ROOT}

    echo '==> Compiling 00_test.cpp...'
    g++ \${OPENPOSE_ROOT}/examples/gvirtus/00_test.cpp \
        -o /tmp/00_test_native \
        -std=c++17 \
        -I\${OPENPOSE_ROOT}/include \
        -I\${OPENPOSE_ROOT}/3rdparty/caffe/include \
        -I/usr/local/cuda/include \
        -L\${OPENPOSE_ROOT}/build/src/openpose \
        -L\${OPENPOSE_ROOT}/build/caffe/lib \
        -L/usr/local/cuda/lib64 \
        -lopenpose -lcaffe -lgflags -lcudart \
        \$(pkg-config --cflags --libs opencv4) \
        -Wl,-rpath,\${OPENPOSE_ROOT}/build/src/openpose:\${OPENPOSE_ROOT}/build/caffe/lib

    echo '==> Running native test (direct GPU)...'
    cd \${OPENPOSE_ROOT}
    /tmp/00_test_native \
        --image_path=\${OPENPOSE_ROOT}/examples/media/COCO_val2014_000000000589.jpg \
        --output_dir=\${OPENPOSE_ROOT}/examples/media \
        --csv_output=\${OPENPOSE_ROOT}/examples/media/results_native.csv \
        --num_runs="\${NUM_RUNS:-1}" \
        --net_resolution="\${NET_RESOLUTION:-160x-1}" \
        --model_pose="\${MODEL_POSE:-COCO}" \
        --render_pose="\${RENDER_POSE:-0}" \
        --scale_number="\${SCALE_NUMBER:-1}" \
        --disable_multi_thread=true \
        --display=0
  "
