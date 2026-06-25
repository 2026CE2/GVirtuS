# PyTorch CUDA Graphs Frontend Test

This example sets up a PyTorch frontend workload for GVirtuS based on the CUDA
Graphs workflow described in the PyTorch blog post "Accelerating PyTorch with
CUDA Graphs" published on October 26, 2021 and updated on November 15, 2024:
https://pytorch.org/blog/accelerating-pytorch-with-cuda-graphs/

The benchmark runs the same small training step in two modes:

- Eager PyTorch execution on CUDA
- CUDA Graph replay using `torch.cuda.CUDAGraph`

The goal is to verify that a PyTorch frontend can:

- See CUDA through the GVirtuS frontend libraries
- Warm up on a side stream
- Capture a training step
- Replay the captured graph repeatedly

## Files

- `benchmark.py`: adapted from the PyTorch blog's whole-network capture pattern
- `setup.sh`: installs the Python packages needed on the frontend
- `run.sh`: injects the GVirtuS frontend libraries with `LD_PRELOAD` and runs the benchmark
- `Dockerfile`: frontend container image for running the example from the project root
- `Dockerfile.base`: cached PyTorch frontend base image with Python and torch preinstalled
- `entrypoint.sh`: container entrypoint used by the root `make` target
- `properties.json`: example-specific frontend connection config

## Frontend setup

Set `GVIRTUS_HOME` to the GVirtuS install path on the frontend, for example:

```bash
export GVIRTUS_HOME=/opt/GVirtuS
```

Install Python dependencies:

```bash
cd ${GVIRTUS_HOME}/examples/pytorch-cuda-graphs
./setup.sh
```

## Run

```bash
cd ${GVIRTUS_HOME}/examples/pytorch-cuda-graphs
./run.sh
```

You can override the benchmark size if you want a lighter first check:

```bash
./run.sh --batch-size 128 --benchmark-iters 10
```

This benchmark always measures both modes in one run and prints:

- eager total and per-iteration time
- graphed total and per-iteration time
- speedup
- final eager and graphed losses

By default it does not fail the process if the final losses differ. If you want
to enforce the correctness check, add:

```bash
./run.sh --fail-on-mismatch
```

Each benchmark run also writes a JSON summary file by default to:

```bash
examples/pytorch-cuda-graphs/results/benchmark-summary.json
```

You can override the output path with:

```bash
PYTORCH_CUDA_GRAPHS_OUTPUT_JSON=/opt/GVirtuS/examples/pytorch-cuda-graphs/results/run-01.json \
make run-pytorch-cuda-graphs-test
```

## Run From The Project Root

This example also follows the same project-root Docker workflow as the other
examples:

```bash
make docker-build-gvirtus
make docker-build-gvirtus-pytorch
make docker-build-pytorch-cuda-graphs
make run-pytorch-cuda-graphs-test
```

`docker-build-gvirtus-pytorch` is the expensive layer that installs Python and
PyTorch. Once that image exists locally, rebuilding
`pytorch-cuda-graphs_gvirtus:cuda12.6` no longer needs to redownload those
packages unless the base image or `Dockerfile.base` changes.

The `run-pytorch-cuda-graphs-test` target starts a frontend container, mounts
this example into `/opt/GVirtuS/examples/pytorch-cuda-graphs`, injects
`examples/pytorch-cuda-graphs/properties.json` as the frontend config, and runs
the benchmark with a lighter default workload:

```bash
--batch-size 128 --benchmark-iters 10
```

You can override those defaults with environment variables:

```bash
PYTORCH_CUDA_GRAPHS_BATCH_SIZE=256 \
PYTORCH_CUDA_GRAPHS_BENCHMARK_ITERS=20 \
make run-pytorch-cuda-graphs-test
```

To isolate frontend initialization and shutdown without running the benchmark:

```bash
make run-pytorch-import-smoke-test
```

## Expected output

The script prints a JSON summary with:

- total and per-iteration eager time
- total and per-iteration graphed time
- observed speedup
- final eager and graphed losses
- a boolean `final_loss_close`

If `final_loss_close` is `true`, the test completed without a correctness
regression large enough to exceed the script's tolerances.

## Notes

- This example intentionally uses a simple static-shape MLP because CUDA Graph
  replay requires stable shapes, control flow, and memory addresses.
- The benchmark is designed as a frontend test and does not modify GVirtuS
  build files.
- If PyTorch reports that CUDA is unavailable, verify that the GVirtuS backend
  is reachable and that the frontend libraries in `${GVIRTUS_HOME}/lib/frontend`
  are present.
