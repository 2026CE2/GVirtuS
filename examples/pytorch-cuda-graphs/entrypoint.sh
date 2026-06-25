#!/bin/bash
set -euo pipefail

export GVIRTUS_HOME=/opt/GVirtuS
export LD_LIBRARY_PATH="${GVIRTUS_HOME}/lib:${GVIRTUS_HOME}/lib/frontend:${LD_LIBRARY_PATH:-}"

cd "${GVIRTUS_HOME}/build" && make -j"$(nproc)" && make install

cd "${GVIRTUS_HOME}/examples/pytorch-cuda-graphs"

if [ "${PYTORCH_CUDA_GRAPHS_MODE:-benchmark}" = "import-smoke" ]; then
  LD_PRELOAD="${GVIRTUS_HOME}/lib/frontend/libcudart.so:${GVIRTUS_HOME}/lib/frontend/libcuda.so:${GVIRTUS_HOME}/lib/frontend/libcublas.so:${GVIRTUS_HOME}/lib/frontend/libcublasLt.so:${GVIRTUS_HOME}/lib/frontend/libcudnn.so:${GVIRTUS_HOME}/lib/frontend/libcufft.so:${GVIRTUS_HOME}/lib/frontend/libcurand.so:${GVIRTUS_HOME}/lib/frontend/libcusparse.so:${GVIRTUS_HOME}/lib/frontend/libcusolver.so:${GVIRTUS_HOME}/lib/frontend/libnvrtc.so" \
  PYTHONUNBUFFERED=1 \
  PYTHONFAULTHANDLER=1 \
  python3 import_smoke.py
  exit $?
fi

mkdir -p "${GVIRTUS_HOME}/examples/pytorch-cuda-graphs/results"
OUTPUT_JSON="${PYTORCH_CUDA_GRAPHS_OUTPUT_JSON:-${GVIRTUS_HOME}/examples/pytorch-cuda-graphs/results/benchmark-summary.json}"
OUTPUT_CSV="${PYTORCH_CUDA_GRAPHS_OUTPUT_CSV:-${GVIRTUS_HOME}/examples/pytorch-cuda-graphs/pytorch_cuda_graphs_results.csv}"

PYTORCH_CUDA_GRAPHS_OUTPUT_CSV="${OUTPUT_CSV}" \
./run.sh --batch-size "${PYTORCH_CUDA_GRAPHS_BATCH_SIZE:-128}" \
  --benchmark-iters "${PYTORCH_CUDA_GRAPHS_BENCHMARK_ITERS:-10}" \
  --num-runs "${PYTORCH_CUDA_GRAPHS_NUM_RUNS:-50}" \
  --output-json "${OUTPUT_JSON}" \
  "$@"
