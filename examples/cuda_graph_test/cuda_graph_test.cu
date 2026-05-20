/*
 * CUDA Graphs Benchmark
 *
 * Demonstrates the performance difference between launching kernels
 * individually vs. using CUDA Graphs, based on:
 * https://developer.nvidia.com/blog/cuda-graphs/
 *
 * Test 1 – Without CUDA Graphs:
 *   Each of NKERNEL kernels per timestep is launched individually.
 *   A single cudaStreamSynchronize is called once per timestep (not per
 *   kernel), so launch overhead can overlap with kernel execution.
 *
 * Test 2 – With CUDA Graphs:
 *   All NKERNEL kernels per timestep are captured once into a graph on the
 *   first timestep, instantiated, and then re-launched as a single operation
 *   on every subsequent timestep.
 */

#include <cuda_runtime.h>
#include <stdio.h>

#define N       500000  /* array size – kernel takes a few microseconds */
#define NSTEP   1000    /* number of timesteps                          */
#define NKERNEL 20      /* kernels per timestep                         */

/* -------------------------------------------------------------------------- */
/* Error checking helper                                                       */
/* -------------------------------------------------------------------------- */
#define CHECK_CUDA(call)                                                        \
    do {                                                                        \
        cudaError_t _err = (call);                                              \
        if (_err != cudaSuccess) {                                              \
            fprintf(stderr, "CUDA error at %s:%d – %s\n",                      \
                    __FILE__, __LINE__, cudaGetErrorString(_err));              \
            exit(EXIT_FAILURE);                                                 \
        }                                                                       \
    } while (0)

/* -------------------------------------------------------------------------- */
/* Kernel                                                                      */
/* -------------------------------------------------------------------------- */
__global__ void shortKernel(float *out_d, float *in_d)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        out_d[idx] = 1.23f * in_d[idx];
}

/* -------------------------------------------------------------------------- */
/* Test 1: multiple individual launches, one sync per timestep                 */
/* -------------------------------------------------------------------------- */
static void run_without_graphs(float *in_d, float *out_d, cudaStream_t stream,
                                int threads, int blocks)
{
    cudaEvent_t start, stop;
    CHECK_CUDA(cudaEventCreate(&start));
    CHECK_CUDA(cudaEventCreate(&stop));

    /* Warm-up */
    for (int istep = 0; istep < 3; istep++) {
        for (int ikrnl = 0; ikrnl < NKERNEL; ikrnl++)
            shortKernel<<<blocks, threads, 0, stream>>>(out_d, in_d);
        CHECK_CUDA(cudaStreamSynchronize(stream));
    }

    CHECK_CUDA(cudaEventRecord(start, stream));

    for (int istep = 0; istep < NSTEP; istep++) {
        for (int ikrnl = 0; ikrnl < NKERNEL; ikrnl++)
            shortKernel<<<blocks, threads, 0, stream>>>(out_d, in_d);
        cudaStreamSynchronize(stream); /* one sync per timestep */
    }

    CHECK_CUDA(cudaEventRecord(stop, stream));
    CHECK_CUDA(cudaEventSynchronize(stop));

    float ms = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&ms, start, stop));
    float us_per_kernel = (ms * 1000.0f) / ((float)NSTEP * NKERNEL);

    printf("[Without CUDA Graphs]  total: %8.3f ms  |  effective time per kernel: %.2f us\n",
           ms, us_per_kernel);

    CHECK_CUDA(cudaEventDestroy(start));
    CHECK_CUDA(cudaEventDestroy(stop));
}

/* -------------------------------------------------------------------------- */
/* Test 2: CUDA Graph – capture once, launch every timestep                   */
/* -------------------------------------------------------------------------- */
static void run_with_graphs(float *in_d, float *out_d, cudaStream_t stream,
                             int threads, int blocks)
{
    cudaEvent_t     start, stop;
    cudaGraph_t     graph;
    cudaGraphExec_t instance;
    bool            graphCreated = false;

    CHECK_CUDA(cudaEventCreate(&start));
    CHECK_CUDA(cudaEventCreate(&stop));

    /* Warm-up (graph is created on the very first iteration) */
    for (int istep = 0; istep < 3; istep++) {
        if (!graphCreated) {
            CHECK_CUDA(cudaStreamBeginCapture(stream, cudaStreamCaptureModeGlobal));
            for (int ikrnl = 0; ikrnl < NKERNEL; ikrnl++)
                shortKernel<<<blocks, threads, 0, stream>>>(out_d, in_d);
            CHECK_CUDA(cudaStreamEndCapture(stream, &graph));
            CHECK_CUDA(cudaGraphInstantiate(&instance, graph, NULL, NULL, 0));
            graphCreated = true;
        }
        CHECK_CUDA(cudaGraphLaunch(instance, stream));
        CHECK_CUDA(cudaStreamSynchronize(stream));
    }

    CHECK_CUDA(cudaEventRecord(start, stream));

    for (int istep = 0; istep < NSTEP; istep++) {
        cudaGraphLaunch(instance, stream);      /* single launch per timestep */
        cudaStreamSynchronize(stream);
    }

    CHECK_CUDA(cudaEventRecord(stop, stream));
    CHECK_CUDA(cudaEventSynchronize(stop));

    float ms = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&ms, start, stop));
    float us_per_kernel = (ms * 1000.0f) / ((float)NSTEP * NKERNEL);

    printf("[With    CUDA Graphs]  total: %8.3f ms  |  effective time per kernel: %.2f us\n",
           ms, us_per_kernel);

    CHECK_CUDA(cudaGraphExecDestroy(instance));
    CHECK_CUDA(cudaGraphDestroy(graph));
    CHECK_CUDA(cudaEventDestroy(start));
    CHECK_CUDA(cudaEventDestroy(stop));
}

/* -------------------------------------------------------------------------- */
/* Main                                                                        */
/* -------------------------------------------------------------------------- */
int main(void)
{
    const int threads = 512;
    const int blocks  = (N + threads - 1) / threads;

    float *in_d  = NULL;
    float *out_d = NULL;
    CHECK_CUDA(cudaMalloc(&in_d,  N * sizeof(float)));
    CHECK_CUDA(cudaMalloc(&out_d, N * sizeof(float)));
    CHECK_CUDA(cudaMemset(in_d,  1, N * sizeof(float)));
    CHECK_CUDA(cudaMemset(out_d, 0, N * sizeof(float)));

    cudaStream_t stream;
    CHECK_CUDA(cudaStreamCreate(&stream));

    printf("Benchmark: %d timesteps x %d kernels, N=%d elements\n\n",
           NSTEP, NKERNEL, N);

    run_without_graphs(in_d, out_d, stream, threads, blocks);
    run_with_graphs   (in_d, out_d, stream, threads, blocks);

    CHECK_CUDA(cudaStreamDestroy(stream));
    CHECK_CUDA(cudaFree(in_d));
    CHECK_CUDA(cudaFree(out_d));

    return 0;
}
