#include <stdio.h>
#include <cmath>
#include <cuda_runtime.h>
#include <chrono>

__global__ void saxpy(int n, float a, float *x, float *y) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    int N = 1382400;
    size_t size = N * sizeof(float);

    float *x, *y;
    float *d_x, *d_y;

    cudaMallocHost((void**)&x, size);
    cudaMallocHost((void**)&y, size);
    cudaMalloc((void**)&d_x, size);
    cudaMalloc((void**)&d_y, size);

    for (int i = 0; i < N; i++) {
        x[i] = 2.0f;
    }

    const int numStreams = 4;
    const int warmupRuns = 1;
    const int numRuns = 1000;
    int blockSize = 256;
    int chunkSize = (N + numStreams - 1) / numStreams;

    cudaStream_t streams[numStreams];
    for (int i = 0; i < numStreams; ++i) {
        cudaStreamCreate(&streams[i]);
    }

    FILE *csv = fopen("simple_matrix_async_results.csv", "w");
    fprintf(csv, "run,duration_us,passed\n");

    bool allValid = true;
    for (int run = -warmupRuns; run < numRuns; run++) {
        for (int i = 0; i < N; i++) y[i] = 2.0f;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numStreams; ++i) {
            int offset = i * chunkSize;
            int currentN = (offset + chunkSize <= N) ? chunkSize : (N - offset);
            if (currentN <= 0) break;

            size_t currentSize = currentN * sizeof(float);
            int gridSize = (currentN + blockSize - 1) / blockSize;

            cudaMemcpyAsync(d_x + offset, x + offset, currentSize, cudaMemcpyHostToDevice, streams[i]);
            cudaMemcpyAsync(d_y + offset, y + offset, currentSize, cudaMemcpyHostToDevice, streams[i]);
            saxpy<<<gridSize, blockSize, 0, streams[i]>>>(currentN, 2.0f, d_x + offset, d_y + offset);
            cudaMemcpyAsync(y + offset, d_y + offset, currentSize, cudaMemcpyDeviceToHost, streams[i]);
        }

        for (int i = 0; i < numStreams; ++i) {
            cudaStreamSynchronize(streams[i]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        bool runValid = true;
        for (int i = 0; i < N; ++i) {
            float expected = 2.0f * x[i] + 2.0f;
            if (fabsf(y[i] - expected) > 1e-5f) {
                runValid = false;
                break;
            }
        }
        if (!runValid) allValid = false;

        if (run >= 0) {
            fprintf(csv, "%d,%ld,%s\n", run + 1, duration.count(), runValid ? "true" : "false");
        }
    }

    fclose(csv);

    if (allValid) {
        printf("Result verification passed. Results written to simple_matrix_async_results.csv\n");
    } else {
        printf("Some runs failed verification. Results written to simple_matrix_async_results.csv\n");
    }

    for (int i = 0; i < numStreams; ++i) {
        cudaStreamDestroy(streams[i]);
    }

    cudaFree(d_x);
    cudaFree(d_y);
    cudaFreeHost(x);
    cudaFreeHost(y);

    return allValid ? 0 : 1;
}