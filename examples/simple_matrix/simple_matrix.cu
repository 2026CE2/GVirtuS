#include <iostream>
#include <chrono>
#include <cublas_v2.h>

#define N 1000 // with 990 it does not work
#define R 1000

int main() {
    // Matrix A (2x3)
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Start Assign\n";
    float A[N*R];
    for (int i = 0; i < N*R; i++) {
        A[i] = static_cast<float>(i);
    }
    // Matrix B (3x2)
    float B[N*R];
    for (int i = 0; i < N*R; i++) {
        B[i] = static_cast<float>(i);
    }
    std::cout << "After assign\n";
    // Matrix C (2x2), the result
    float C[R*R] = {0};

    float *d_A, *d_B, *d_C;
    const float alpha = 1.0f;
    const float beta = 0.0f;
    std::cout << "Beginning mallocs\n";
    // Allocate device memory
    cudaMalloc((void **)&d_A, N*R * sizeof(float));
    cudaMalloc((void **)&d_B, N*R * sizeof(float));
    cudaMalloc((void **)&d_C, R*R * sizeof(float));

    // Copy matrices from host to device
    cudaMemcpy(d_A, A, N*R * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N*R * sizeof(float), cudaMemcpyHostToDevice);

    // Create cuBLAS handle
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Perform matrix multiplication: C = alpha * A * B + beta * C
    // A: 2x3, B: 3x2, C: 2x2
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, R, R, N, &alpha, d_A, R, d_B, N, &beta, d_C, R);

    // Copy result back to host
    cudaMemcpy(C, d_C, R*R * sizeof(float), cudaMemcpyDeviceToHost);


    // Free resources
    cublasDestroy(handle);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
