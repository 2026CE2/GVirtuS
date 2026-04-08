#include <cuda_runtime.h>

#include <iostream>

static int check(cudaError_t status, const char* what) {
    if (status != cudaSuccess) {
        std::cerr << what << " failed: " << cudaGetErrorString(status) << " (" << status
                  << ")\n";
        return 1;
    }
    return 0;
}

int main() {
    cudaGraph_t graph = nullptr;
    cudaGraph_t clone = reinterpret_cast<cudaGraph_t>(0x1);

    if (check(cudaGraphCreate(&graph, 0), "cudaGraphCreate")) return 1;

    size_t n1 = 0;
    if (check(cudaGraphGetNodes(graph, nullptr, &n1), "cudaGraphGetNodes(original)")) {
        cudaGraphDestroy(graph);
        return 1;
    }

    if (check(cudaGraphClone(&clone, graph), "cudaGraphClone")) {
        cudaGraphDestroy(graph);
        return 1;
    }

    if (clone == nullptr || clone == reinterpret_cast<cudaGraph_t>(0x1)) {
        std::cerr << "cudaGraphClone did not populate output handle\n";
        cudaGraphDestroy(graph);
        return 1;
    }

    size_t n2 = 0;
    if (check(cudaGraphGetNodes(clone, nullptr, &n2), "cudaGraphGetNodes(clone)")) {
        cudaGraphDestroy(clone);
        cudaGraphDestroy(graph);
        return 1;
    }

    if (n1 != n2) {
        std::cerr << "node count mismatch: original=" << n1 << " clone=" << n2 << "\n";
        cudaGraphDestroy(clone);
        cudaGraphDestroy(graph);
        return 1;
    }

    cudaError_t invalid_out = cudaGraphClone(nullptr, graph);
    if (invalid_out == cudaSuccess) {
        std::cerr << "expected failure for cudaGraphClone(nullptr, graph)\n";
        cudaGraphDestroy(clone);
        cudaGraphDestroy(graph);
        return 1;
    }

    cudaError_t invalid_in = cudaGraphClone(&clone, nullptr);
    if (invalid_in == cudaSuccess) {
        std::cerr << "expected failure for cudaGraphClone(&clone, nullptr)\n";
        cudaGraphDestroy(clone);
        cudaGraphDestroy(graph);
        return 1;
    }

    if (check(cudaGraphDestroy(clone), "cudaGraphDestroy(clone)")) {
        cudaGraphDestroy(graph);
        return 1;
    }
    if (check(cudaGraphDestroy(graph), "cudaGraphDestroy(original)")) return 1;

    std::cout << "graphClone test passed\n";
    return 0;
}
