/*
 * GVirtuS Async Kernel Benchmark
 *
 * Demonstrates the performance benefit of the asynchronous CUDA API when
 * running through GVirtuS over a network connection (TCP or QUIC).
 *
 * When GVirtuS intercepts CUDA calls, every blocking call becomes a full
 * network round-trip: the frontend sends the RPC, waits for the backend to
 * execute it, and only then returns to the application.  With NKERNEL kernels
 * per timestep, the synchronous path serialises NKERNEL × 3 round-trips
 * (H2D + launch + D2H).
 *
 * The QUIC communicator in GVirtuS supports async RPC pipelining: async
 * calls (cudaMemcpyAsync, kernel launches on named streams) are sent to the
 * backend without waiting for a reply.  A single cudaStreamSynchronize per
 * stream collects all in-flight results.  Multiple streams can overlap
 * independent kernel workloads entirely, reducing the total wall-clock time
 * per timestep from O(NKERNEL × RTT) to O(RTT).
 *
 * Test 1 – Synchronous (serial, no async):
 *   Each of the NKERNEL kernels is driven with:
 *     blocking cudaMemcpy H2D → kernel launch → blocking cudaMemcpy D2H
 *   Total round-trips per timestep: NKERNEL × 3.
 *
 * Test 2 – Asynchronous (multi-stream, QUIC-pipelined):
 *   NKERNEL independent CUDA streams each issue:
 *     cudaMemcpyAsync H2D → shortKernel (async) → cudaMemcpyAsync D2H
 *   All operations are dispatched without waiting; streams are then
 *   synchronised once each.  QUIC pipelines all in-flight RPCs together.
 */

#include <cuda_runtime.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/* Wall-clock helper: returns elapsed milliseconds between two timespec values */
static double elapsed_ms(struct timespec t0, struct timespec t1)
{
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

#define N        65536   /* float elements per per-kernel buffer (256 KB each) */
#define NSTEP    500     /* number of timesteps                                */
#define NKERNEL  8       /* independent kernel workloads per timestep          */

/* -------------------------------------------------------------------------- */
/* Error-checking helper                                                       */
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
/* Validation: verify out[k][i] == 1.23f * in[k][i] for all k and i            */
/* Returns true if all values are within tolerance, false otherwise.            */
/* -------------------------------------------------------------------------- */
static bool validate_outputs(float **h_in, float **h_out)
{
    for (int k = 0; k < NKERNEL; k++) {
        for (int i = 0; i < N; i++) {
            float expected = 1.23f * h_in[k][i];
            if (fabsf(h_out[k][i] - expected) > 1e-4f) {
                fprintf(stderr,
                        "Validation FAILED: kernel %d element %d — "
                        "got %.6f, expected %.6f\n",
                        k, i, h_out[k][i], expected);
                return false;
            }
        }
    }
    return true;
}

/* -------------------------------------------------------------------------- */
/* Kernel: element-wise scale — same operation as in cuda_graph_test           */
/* -------------------------------------------------------------------------- */
__global__ void shortKernel(float *out_d, float *in_d)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        out_d[idx] = 1.23f * in_d[idx];
}

/* -------------------------------------------------------------------------- */
/* Test 1: blocking cudaMemcpy + kernel + blocking cudaMemcpy, NKERNEL times   */
/* -------------------------------------------------------------------------- */
static void run_sync(float **h_in, float **h_out,
                     float **d_in, float **d_out,
                     int threads, int blocks,
                     float *total_ms_out, float *us_per_kernel_out,
                     bool *all_valid_out, FILE *fp)
{
    /* Warm-up */
    for (int w = 0; w < 3; w++) {
        for (int k = 0; k < NKERNEL; k++) {
            CHECK_CUDA(cudaMemcpy(d_in[k], h_in[k], N * sizeof(float), cudaMemcpyHostToDevice));
            shortKernel<<<blocks, threads>>>(d_out[k], d_in[k]);
            CHECK_CUDA(cudaMemcpy(h_out[k], d_out[k], N * sizeof(float), cudaMemcpyDeviceToHost));
        }
    }

    bool all_valid = true;
    double total_wall_ms = 0.0;
    for (int istep = 0; istep < NSTEP; istep++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (int k = 0; k < NKERNEL; k++) {
            CHECK_CUDA(cudaMemcpy(d_in[k], h_in[k], N * sizeof(float), cudaMemcpyHostToDevice));
            shortKernel<<<blocks, threads>>>(d_out[k], d_in[k]);
            CHECK_CUDA(cudaMemcpy(h_out[k], d_out[k], N * sizeof(float), cudaMemcpyDeviceToHost));
        }
        clock_gettime(CLOCK_MONOTONIC, &t1);

        double step_ms = elapsed_ms(t0, t1);
        total_wall_ms += step_ms;

        bool step_valid = validate_outputs(h_in, h_out);
        if (!step_valid) all_valid = false;

        if (fp)
            fprintf(fp, "sync,%d,%d,%d,%d,%.4f,%.4f,%s\n",
                    istep, N, NSTEP, NKERNEL,
                    step_ms, (step_ms * 1000.0) / NKERNEL,
                    step_valid ? "true" : "false");
    }

    float us_per_kernel = (float)(total_wall_ms * 1000.0 / ((double)NSTEP * NKERNEL));
    printf("[Synchronous / serial]  wall: %8.3f ms  |  effective time per kernel: %.2f us  |  validation: %s\n",
           (float)total_wall_ms, us_per_kernel, all_valid ? "PASSED" : "FAILED");

    if (total_ms_out)      *total_ms_out      = (float)total_wall_ms;
    if (us_per_kernel_out) *us_per_kernel_out = us_per_kernel;
    if (all_valid_out)     *all_valid_out     = all_valid;
}

/* -------------------------------------------------------------------------- */
/* Test 2: cudaMemcpyAsync + async kernel + cudaMemcpyAsync, NKERNEL streams   */
/* -------------------------------------------------------------------------- */
static void run_async(float **h_in, float **h_out,
                      float **d_in, float **d_out,
                      cudaStream_t *streams,
                      int threads, int blocks,
                      float *total_ms_out, float *us_per_kernel_out,
                      bool *all_valid_out, FILE *fp)
{
    /* Warm-up */
    for (int w = 0; w < 3; w++) {
        for (int k = 0; k < NKERNEL; k++) {
            CHECK_CUDA(cudaMemcpyAsync(d_in[k], h_in[k], N * sizeof(float),
                                      cudaMemcpyHostToDevice, streams[k]));
            shortKernel<<<blocks, threads, 0, streams[k]>>>(d_out[k], d_in[k]);
            CHECK_CUDA(cudaMemcpyAsync(h_out[k], d_out[k], N * sizeof(float),
                                      cudaMemcpyDeviceToHost, streams[k]));
        }
        for (int k = 0; k < NKERNEL; k++)
            CHECK_CUDA(cudaStreamSynchronize(streams[k]));
    }

    bool all_valid = true;
    double total_wall_ms = 0.0;
    for (int istep = 0; istep < NSTEP; istep++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);

        /* Dispatch all NKERNEL stream workloads without waiting */
        for (int k = 0; k < NKERNEL; k++) {
            CHECK_CUDA(cudaMemcpyAsync(d_in[k], h_in[k], N * sizeof(float),
                                      cudaMemcpyHostToDevice, streams[k]));
            shortKernel<<<blocks, threads, 0, streams[k]>>>(d_out[k], d_in[k]);
            CHECK_CUDA(cudaMemcpyAsync(h_out[k], d_out[k], N * sizeof(float),
                                      cudaMemcpyDeviceToHost, streams[k]));
        }
        /* Collect: one synchronisation barrier per stream */
        for (int k = 0; k < NKERNEL; k++)
            CHECK_CUDA(cudaStreamSynchronize(streams[k]));

        clock_gettime(CLOCK_MONOTONIC, &t1);

        double step_ms = elapsed_ms(t0, t1);
        total_wall_ms += step_ms;

        bool step_valid = validate_outputs(h_in, h_out);
        if (!step_valid) all_valid = false;

        if (fp)
            fprintf(fp, "async,%d,%d,%d,%d,%.4f,%.4f,%s\n",
                    istep, N, NSTEP, NKERNEL,
                    step_ms, (step_ms * 1000.0) / NKERNEL,
                    step_valid ? "true" : "false");
    }

    float us_per_kernel = (float)(total_wall_ms * 1000.0 / ((double)NSTEP * NKERNEL));
    printf("[Async  / multi-stream] wall: %8.3f ms  |  effective time per kernel: %.2f us  |  validation: %s\n",
           (float)total_wall_ms, us_per_kernel, all_valid ? "PASSED" : "FAILED");

    if (total_ms_out)      *total_ms_out      = (float)total_wall_ms;
    if (us_per_kernel_out) *us_per_kernel_out = us_per_kernel;
    if (all_valid_out)     *all_valid_out     = all_valid;
}

/* -------------------------------------------------------------------------- */
/* Main                                                                        */
/* -------------------------------------------------------------------------- */
int main(void)
{
    const int threads = 256;
    const int blocks  = (N + threads - 1) / threads;

    /* Per-kernel pinned host buffers + device buffers */
    float *h_in[NKERNEL], *h_out[NKERNEL];
    float *d_in[NKERNEL], *d_out[NKERNEL];

    for (int k = 0; k < NKERNEL; k++) {
        CHECK_CUDA(cudaMallocHost((void **)&h_in[k],  N * sizeof(float)));
        CHECK_CUDA(cudaMallocHost((void **)&h_out[k], N * sizeof(float)));
        CHECK_CUDA(cudaMalloc(&d_in[k],  N * sizeof(float)));
        CHECK_CUDA(cudaMalloc(&d_out[k], N * sizeof(float)));
        for (int i = 0; i < N; i++)
            h_in[k][i] = (float)(k + 1);
    }

    cudaStream_t streams[NKERNEL];
    for (int k = 0; k < NKERNEL; k++)
        CHECK_CUDA(cudaStreamCreate(&streams[k]));

    printf("Benchmark: %d timesteps x %d kernels, N=%d elements/kernel\n\n",
           NSTEP, NKERNEL, N);

    float sync_ms = 0.0f, sync_us = 0.0f;
    float async_ms = 0.0f, async_us = 0.0f;
    bool sync_valid = true, async_valid = true;

    /* Open CSV – write header only if file is empty */
    const char *csv_path = "async_shortkernel_results.csv";
    FILE *fp = fopen(csv_path, "a");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
            fprintf(fp, "test,step,N,NSTEP,NKERNEL,step_ms,us_per_kernel,passed\n");
    } else {
        fprintf(stderr, "Warning: could not open %s for writing\n", csv_path);
    }

    run_sync (h_in, h_out, d_in, d_out,         threads, blocks,
              &sync_ms,  &sync_us,  &sync_valid,  fp);
    run_async(h_in, h_out, d_in, d_out, streams, threads, blocks,
              &async_ms, &async_us, &async_valid, fp);

    if (fp) {
        fclose(fp);
        printf("\nPer-step results appended to %s\n", csv_path);
    }

    float speedup = (async_us > 0.0f) ? (sync_us / async_us) : 0.0f;
    printf("\nSpeedup (async vs sync): %.2fx\n", speedup);
    printf("Overall validation:      sync=%s  async=%s\n",
           sync_valid ? "PASSED" : "FAILED",
           async_valid ? "PASSED" : "FAILED");

    for (int k = 0; k < NKERNEL; k++) {
        CHECK_CUDA(cudaStreamDestroy(streams[k]));
        CHECK_CUDA(cudaFree(d_in[k]));
        CHECK_CUDA(cudaFree(d_out[k]));
        CHECK_CUDA(cudaFreeHost(h_in[k]));
        CHECK_CUDA(cudaFreeHost(h_out[k]));
    }

    return (sync_valid && async_valid) ? 0 : 1;
}
