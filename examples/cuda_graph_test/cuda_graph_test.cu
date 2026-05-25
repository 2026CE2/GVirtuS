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
#include <string.h>
#include <time.h>

/* Wall-clock helper: returns elapsed milliseconds between two timespec values */
static double elapsed_ms(struct timespec t0, struct timespec t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

#define N       500000  /* array size – kernel takes a few microseconds */
#define NSTEP   1000     /* number of timesteps                          */
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
                                int threads, int blocks,
                                float *total_ms_out, float *us_per_kernel_out,
                                FILE *fp)
{
    cudaEvent_t total_start, total_stop;
    CHECK_CUDA(cudaEventCreate(&total_start));
    CHECK_CUDA(cudaEventCreate(&total_stop));

    /* Warm-up */
    for (int istep = 0; istep < 3; istep++) {
        for (int ikrnl = 0; ikrnl < NKERNEL; ikrnl++)
            shortKernel<<<blocks, threads, 0, stream>>>(out_d, in_d);
        CHECK_CUDA(cudaStreamSynchronize(stream));
    }

    CHECK_CUDA(cudaEventRecord(total_start, stream));

    double total_wall_ms = 0.0;
    for (int istep = 0; istep < NSTEP; istep++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (int ikrnl = 0; ikrnl < NKERNEL; ikrnl++)
            shortKernel<<<blocks, threads, 0, stream>>>(out_d, in_d);
        CHECK_CUDA(cudaStreamSynchronize(stream));
        clock_gettime(CLOCK_MONOTONIC, &t1);

        double step_ms = elapsed_ms(t0, t1);
        total_wall_ms += step_ms;

        if (fp)
            fprintf(fp, "without_graphs,%d,%d,%d,%d,%.4f,%.4f\n",
                    istep, N, NSTEP, NKERNEL,
                    step_ms, (step_ms * 1000.0) / NKERNEL);
    }

    CHECK_CUDA(cudaEventRecord(total_stop, stream));
    CHECK_CUDA(cudaEventSynchronize(total_stop));

    float gpu_total_ms = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&gpu_total_ms, total_start, total_stop));
    float us_per_kernel = (float)(total_wall_ms * 1000.0 / ((double)NSTEP * NKERNEL));

    printf("[Without CUDA Graphs]  wall: %8.3f ms  gpu: %8.3f ms  |  effective time per kernel: %.2f us\n",
           (float)total_wall_ms, gpu_total_ms, us_per_kernel);

    if (total_ms_out)      *total_ms_out      = (float)total_wall_ms;
    if (us_per_kernel_out) *us_per_kernel_out = us_per_kernel;

    CHECK_CUDA(cudaEventDestroy(total_start));
    CHECK_CUDA(cudaEventDestroy(total_stop));
}

/* -------------------------------------------------------------------------- */
/* Test 2: CUDA Graph – capture once, launch every timestep                   */
/* -------------------------------------------------------------------------- */
static void run_with_graphs(float *in_d, float *out_d, cudaStream_t stream,
                             int threads, int blocks,
                             float *total_ms_out, float *us_per_kernel_out,
                             FILE *fp)
{
    cudaEvent_t     total_start, total_stop;
    cudaGraph_t     graph;
    cudaGraphExec_t instance;
    bool            graphCreated = false;

    CHECK_CUDA(cudaEventCreate(&total_start));
    CHECK_CUDA(cudaEventCreate(&total_stop));

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

    CHECK_CUDA(cudaEventRecord(total_start, stream));

    double total_wall_ms = 0.0;
    for (int istep = 0; istep < NSTEP; istep++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        cudaGraphLaunch(instance, stream);
        CHECK_CUDA(cudaStreamSynchronize(stream));
        clock_gettime(CLOCK_MONOTONIC, &t1);

        double step_ms = elapsed_ms(t0, t1);
        total_wall_ms += step_ms;

        if (fp)
            fprintf(fp, "with_graphs,%d,%d,%d,%d,%.4f,%.4f\n",
                    istep, N, NSTEP, NKERNEL,
                    step_ms, (step_ms * 1000.0) / NKERNEL);
    }

    CHECK_CUDA(cudaEventRecord(total_stop, stream));
    CHECK_CUDA(cudaEventSynchronize(total_stop));

    float gpu_total_ms = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&gpu_total_ms, total_start, total_stop));
    float us_per_kernel = (float)(total_wall_ms * 1000.0 / ((double)NSTEP * NKERNEL));

    printf("[With    CUDA Graphs]  wall: %8.3f ms  gpu: %8.3f ms  |  effective time per kernel: %.2f us\n",
           (float)total_wall_ms, gpu_total_ms, us_per_kernel);

    if (total_ms_out)      *total_ms_out      = (float)total_wall_ms;
    if (us_per_kernel_out) *us_per_kernel_out = us_per_kernel;

    CHECK_CUDA(cudaGraphExecDestroy(instance));
    CHECK_CUDA(cudaGraphDestroy(graph));
    CHECK_CUDA(cudaEventDestroy(total_start));
    CHECK_CUDA(cudaEventDestroy(total_stop));
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

    float no_graph_ms = 0.0f, no_graph_us = 0.0f;
    float graph_ms    = 0.0f, graph_us    = 0.0f;

    /* ------------------------------------------------------------------ */
    /* Open CSV – write header only when file is empty                      */
    /* ------------------------------------------------------------------ */
    const char *csv_path = "cuda_graph_results.csv";
    FILE *fp = fopen(csv_path, "a");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
            fprintf(fp, "test,step,N,NSTEP,NKERNEL,step_ms,us_per_kernel\n");
    } else {
        fprintf(stderr, "Warning: could not open %s for writing\n", csv_path);
    }

    run_without_graphs(in_d, out_d, stream, threads, blocks, &no_graph_ms, &no_graph_us, fp);
    run_with_graphs   (in_d, out_d, stream, threads, blocks, &graph_ms,    &graph_us,    fp);

    if (fp) {
        fclose(fp);
        printf("\nPer-step results appended to %s\n", csv_path);
    }

    CHECK_CUDA(cudaStreamDestroy(stream));
    CHECK_CUDA(cudaFree(in_d));
    CHECK_CUDA(cudaFree(out_d));

    return 0;
}
