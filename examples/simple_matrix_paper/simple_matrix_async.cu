#include <stdio.h>
#include <cmath>
#include <cuda_runtime.h>
#include <chrono>

using hrc = std::chrono::high_resolution_clock;
using ms  = std::chrono::milliseconds;

static long elapsed_ms(hrc::time_point a, hrc::time_point b) {
    return std::chrono::duration_cast<ms>(b - a).count();
}

// Per-run timing breakdown written to the CSV.
struct RunResult {
    long h2d_ms;         // H2D transfer time
    long kernel_ms;      // kernel dispatch + cudaDeviceSynchronize (sync) or 0 (async)
    long d2h_ms;         // D2H transfer time (or D2H queue time for async)
    long stream_sync_ms; // cudaStreamSynchronize total (async only, else 0)
    long total_ms;       // end-to-end wall time
    bool ok;
};

__global__ void saxpy(int n, float a, float *x, float *y) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        y[i] = a * x[i] + y[i];
    }
}

static void init_data(float *x, float *y, int N) {
    for (int i = 0; i < N; i++) {
        x[i] = 2.0f;
        y[i] = 2.0f;
    }
}

static bool verify(const float *x, const float *y, int N) {
    for (int i = 0; i < N; ++i) {
        float expected = 2.0f * x[i] + 2.0f;
        if (fabsf(y[i] - expected) > 1e-5f) {
            printf("  Validation failed at index %d: y=%f expected=%f\n", i, y[i], expected);
            return false;
        }
    }
    return true;
}

// Synchronous baseline: blocking cudaMemcpy + single null-stream kernel launch.
static RunResult run_sync(float *x, float *y, float *d_x, float *d_y, int N) {
    size_t size = N * sizeof(float);
    int blockSize = 256;
    int gridSize = (N + blockSize - 1) / blockSize;

    init_data(x, y, N);

    auto t0 = hrc::now();

    cudaMemcpy(d_x, x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, size, cudaMemcpyHostToDevice);
    auto t1 = hrc::now();

    saxpy<<<gridSize, blockSize>>>(N, 2.0f, d_x, d_y);
    cudaDeviceSynchronize();
    auto t2 = hrc::now();

    cudaMemcpy(y, d_y, size, cudaMemcpyDeviceToHost);
    auto t3 = hrc::now();

    RunResult r;
    r.h2d_ms         = elapsed_ms(t0, t1);
    r.kernel_ms      = elapsed_ms(t1, t2);
    r.d2h_ms         = elapsed_ms(t2, t3);
    r.stream_sync_ms = 0;
    r.total_ms       = elapsed_ms(t0, t3);
    r.ok             = verify(x, y, N);

    printf("  Sync:  %s | h2d=%ld  kernel=%ld  d2h=%ld  total=%ld ms\n",
           r.ok ? "PASS" : "FAIL",
           r.h2d_ms, r.kernel_ms, r.d2h_ms, r.total_ms);
    return r;
}

// Async path: cudaMemcpyAsync + multi-stream kernel launches (fire-and-forget).
static RunResult run_async(float *x, float *y, float *d_x, float *d_y, int N, int numStreams) {
    size_t size = N * sizeof(float);
    int blockSize = 256;
    int chunkSize = (N + numStreams - 1) / numStreams;

    init_data(x, y, N);

    cudaStream_t streams[numStreams];
    for (int i = 0; i < numStreams; ++i)
        cudaStreamCreate(&streams[i]);

    auto t0 = hrc::now();

    // H2D + kernel: fire-and-forget per stream
    for (int i = 0; i < numStreams; ++i) {
        int offset   = i * chunkSize;
        int currentN = (offset + chunkSize <= N) ? chunkSize : (N - offset);
        if (currentN <= 0) break;
        size_t currentSize = currentN * sizeof(float);
        int gridSize = (currentN + blockSize - 1) / blockSize;
        cudaMemcpyAsync(d_x + offset, x + offset, currentSize, cudaMemcpyHostToDevice, streams[i]);
        cudaMemcpyAsync(d_y + offset, y + offset, currentSize, cudaMemcpyHostToDevice, streams[i]);
        saxpy<<<gridSize, blockSize, 0, streams[i]>>>(currentN, 2.0f, d_x + offset, d_y + offset);
    }
    auto t1 = hrc::now();

    // D2H: queue on each stream (synchronous read-back per GVirtuS design)
    for (int i = 0; i < numStreams; ++i) {
        int offset   = i * chunkSize;
        int currentN = (offset + chunkSize <= N) ? chunkSize : (N - offset);
        if (currentN <= 0) break;
        size_t currentSize = currentN * sizeof(float);
        cudaMemcpyAsync(y + offset, d_y + offset, currentSize, cudaMemcpyDeviceToHost, streams[i]);
    }
    auto t2 = hrc::now();

    for (int i = 0; i < numStreams; ++i) {
        cudaStreamSynchronize(streams[i]);
        cudaStreamDestroy(streams[i]);
    }
    auto t3 = hrc::now();

    RunResult r;
    r.h2d_ms         = elapsed_ms(t0, t1);  // H2D + kernel dispatch
    r.kernel_ms      = 0;                   // bundled with h2d_ms for async
    r.d2h_ms         = elapsed_ms(t1, t2);  // D2H queue time
    r.stream_sync_ms = elapsed_ms(t2, t3);  // waiting for streams to drain
    r.total_ms       = elapsed_ms(t0, t3);
    r.ok             = verify(x, y, N);

    printf("  Async (%d streams): %s | h2d_queue=%ld  d2h_queue=%ld  sync_wait=%ld  total=%ld ms\n",
           numStreams,
           r.ok ? "PASS" : "FAIL",
           r.h2d_ms, r.d2h_ms, r.stream_sync_ms, r.total_ms);
    return r;
}

int main() {
    const int RUNS   = 100;
    const int WARMUP = 1;
    const int STREAM_COUNTS[] = {4, 8, 16};
    const int NUM_STREAM_CONFIGS = (int)(sizeof(STREAM_COUNTS) / sizeof(STREAM_COUNTS[0]));

    int N = 13824000;
    size_t size = N * sizeof(float);

    float *x, *y, *d_x, *d_y;
    cudaMallocHost((void**)&x, size);
    cudaMallocHost((void**)&y, size);
    cudaMalloc((void**)&d_x, size);
    cudaMalloc((void**)&d_y, size);

    // Open CSV output — includes num_streams column (0 for sync)
    FILE *csv = fopen("results.csv", "w");
    if (!csv) { perror("fopen results.csv"); return 1; }
    fprintf(csv, "run,mode,num_streams,warmup,h2d_ms,kernel_ms,d2h_ms,stream_sync_ms,total_ms,pass\n");

    printf("=== GVirtuS async benchmark (N=%d floats, %.1f MB, %d runs, %d warmup) ===\n",
           N, size / 1e6, RUNS, WARMUP);

    // --- Sync ---
    printf("\n[Sync]\n");
    long sync_sum = 0;
    for (int r = 0; r < RUNS; ++r) {
        RunResult res = run_sync(x, y, d_x, d_y, N);
        int warmup = (r < WARMUP) ? 1 : 0;
        fprintf(csv, "%d,sync,0,%d,%ld,%ld,%ld,%ld,%ld,%d\n",
                r, warmup,
                res.h2d_ms, res.kernel_ms, res.d2h_ms,
                res.stream_sync_ms, res.total_ms, res.ok ? 1 : 0);
        if (r < WARMUP) printf("  (warmup)\n");
        else            sync_sum += res.total_ms;
    }
    double sync_avg = (double)sync_sum / (RUNS - WARMUP);
    printf("  Avg (excl. %d warmup): %.1f ms\n", WARMUP, sync_avg);

    // --- Async sweep over stream counts ---
    printf("\n[Async stream sweep]\n");
    for (int s = 0; s < NUM_STREAM_CONFIGS; ++s) {
        int ns = STREAM_COUNTS[s];
        printf("\n  --- %d stream(s) ---\n", ns);
        long async_sum = 0;
        for (int r = 0; r < RUNS; ++r) {
            RunResult res = run_async(x, y, d_x, d_y, N, ns);
            int warmup = (r < WARMUP) ? 1 : 0;
            fprintf(csv, "%d,async,%d,%d,%ld,%ld,%ld,%ld,%ld,%d\n",
                    r, ns, warmup,
                    res.h2d_ms, res.kernel_ms, res.d2h_ms,
                    res.stream_sync_ms, res.total_ms, res.ok ? 1 : 0);
            if (r < WARMUP) printf("  (warmup)\n");
            else            async_sum += res.total_ms;
        }
        double async_avg = (double)async_sum / (RUNS - WARMUP);
        printf("  Avg (excl. %d warmup): %.1f ms  |  Speedup vs sync: %.2fx\n",
               WARMUP, async_avg, sync_avg / async_avg);
    }

    fclose(csv);
    printf("\nResults written to results.csv\n");

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFreeHost(x);
    cudaFreeHost(y);

    return 0;
}