#!/bin/bash
set -euo pipefail

if [ -z "${GVIRTUS_HOME:-}" ]; then
    echo "GVIRTUS_HOME is not set."
    exit 1
fi

export LD_LIBRARY_PATH="${GVIRTUS_HOME}/lib/frontend:${GVIRTUS_HOME}/lib:${LD_LIBRARY_PATH:-}"
export GVIRTUS_LOGLEVEL="${GVIRTUS_LOGLEVEL:-50000}"

LD_PRELOAD="${GVIRTUS_HOME}/lib/frontend/libcudart.so:${GVIRTUS_HOME}/lib/frontend/libcuda.so:${GVIRTUS_HOME}/lib/frontend/libcublas.so:${GVIRTUS_HOME}/lib/frontend/libcublasLt.so:${GVIRTUS_HOME}/lib/frontend/libcudnn.so:${GVIRTUS_HOME}/lib/frontend/libcufft.so:${GVIRTUS_HOME}/lib/frontend/libcurand.so:${GVIRTUS_HOME}/lib/frontend/libcusparse.so:${GVIRTUS_HOME}/lib/frontend/libcusolver.so:${GVIRTUS_HOME}/lib/frontend/libnvrtc.so" \
PYTORCH_NVML_BASED_CUDA_CHECK=1 \
TORCHINDUCTOR_FORCE_DISABLE_CACHES=1 \
PYTHONUNBUFFERED=1 \
PYTHONFAULTHANDLER=1 \
CUDA_LAUNCH_BLOCKING="${CUDA_LAUNCH_BLOCKING:-1}" \
TORCH_SHOW_CPP_STACKTRACES=1 \
TORCH_DISABLE_ADDR2LINE=1 \
python3 benchmark.py \
  --output-csv "${PYTORCH_CUDA_GRAPHS_OUTPUT_CSV:-${GVIRTUS_HOME}/examples/pytorch-cuda-graphs/pytorch_cuda_graphs_results.csv}" \
  --num-runs "${PYTORCH_CUDA_GRAPHS_NUM_RUNS:-1}" \
  "$@"
