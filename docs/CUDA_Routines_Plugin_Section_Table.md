# CUDA Routines by Plugin and Section

Generated: 2026-03-11 10:04:47

Source: backend handler registration calls (`mspHandlers->insert(..._PAIR(...))`).

## System Diagram (API Interaction Overview)

This diagram is grounded in these tests as concrete entry points:

- `tests/test_cudart.cu`
- `tests/test_cublas.cu`
- `tests/test_cusolver.cu`

```mermaid
flowchart LR
    A[Test binary<br/>GoogleTest CUDA calls]
    B[Frontend wrapper .so<br/>plugins/*/frontend/*.cpp]
    C[gvirtus::frontend::Frontend<br/>Prepare + Execute]
    D[Communicator<br/>TCP or Hybrid TCP/RDMA]
    E[gvirtus::backend::Process<br/>routine dispatch loop]
    F[Plugin Handler<br/>plugins/*/backend/*Handler*.cpp]
    G[Native NVIDIA library<br/>CUDA/cuBLAS/cuSOLVER/...]
    H[GPU]

    A -->|cudaMalloc, cublasSgemm,<br/>cusolverDnSetStream...| B
    B -->|serialize routine + args| C
    C -->|Write routine, Dump input buffer| D
    D -->|server-side read| E
    E -->|find CanExecute(routine)| F
    F -->|invoke real API| G
    G --> H
    H --> G
    G -->|status + output values| F
    F -->|Result::Dump| E
    E --> D
    D -->|Read exit_code + out buffer| C
    C -->|decode outputs| B
    B -->|return API status/data| A
```

```mermaid
sequenceDiagram
    participant T as Test (e.g. test_cusolver)
    participant W as Frontend Wrapper
    participant FE as gvirtus Frontend
    participant BE as Backend Process
    participant H as Plugin Handler
    participant N as Native CUDA Library

    T->>W: cusolverDnGetStream(handle,&stream)
    W->>FE: Prepare(); Add args; Execute("cusolverDnGetStream")
    FE->>BE: routine name + marshalled input buffer
    BE->>H: Execute(routine,input_buffer)
    H->>N: cusolverDnGetStream(handle,&stream)
    N-->>H: status + stream
    H-->>BE: Result(exit_code, output_buffer)
    BE-->>FE: exit_code + output_buffer
    FE-->>W: GetExitCode(), GetOutputVariable<cudaStream_t>()
    W-->>T: CUSOLVER_STATUS_SUCCESS + stream value
```

## Test-Derived API Paths

| Test file | API points used in test | Plugin path in this repo |
|---|---|---|
| `tests/test_cudart.cu` | `cudaMalloc`, `cudaMemcpy`, `cudaMemcpyAsync`, `cudaStream*`, `cudaGraph*`, `cudaEvent*` | `plugins/cudart/frontend/*` -> `src/frontend/Frontend.cpp` -> `src/backend/Process.cpp` -> `plugins/cudart/backend/CudaRtHandler_*.cpp` |
| `tests/test_cublas.cu` | `cublasCreate`, `cublasSetStream`, `cublasSgemm`, `cublasSaxpy`, `cublasSdot` | `plugins/cublas/frontend/*` -> `src/frontend/Frontend.cpp` -> `src/backend/Process.cpp` -> `plugins/cublas/backend/CublasHandler_*.cpp` |
| `tests/test_cusolver.cu` | `cusolverDnCreate`, `cusolverDnDestroy`, `cusolverDnSetStream`, `cusolverDnGetStream` | `plugins/cusolver/frontend/Cusolver_helper.cpp` -> `src/frontend/Frontend.cpp` -> `src/backend/Process.cpp` -> `plugins/cusolver/backend/CusolverHandler.cpp` |

## Summary

- Total routines (deduplicated by routine+plugin+section): 720
- Plugins covered: 10

- `cublas`: 177 routines
- `cudadr`: 91 routines
- `cudart`: 111 routines
- `cudnn`: 246 routines
- `cufft`: 39 routines
- `curand`: 15 routines
- `cusolver`: 4 routines
- `cusparse`: 6 routines
- `nvml`: 30 routines
- `nvrtc`: 1 routines


## Documentation Sources

- CUDA Runtime API modules: https://docs.nvidia.com/cuda/archive/13.1.1/cuda-runtime-api/modules.html
- CUDA Driver API modules: https://docs.nvidia.com/cuda/cuda-driver-api/index.html
- cuBLAS API family (cuBLAS/cuBLASLt/cuBLASXt): https://docs.nvidia.com/cuda/cublas/index.html
- cuDNN backend API/library split: https://docs.nvidia.com/deeplearning/cudnn/backend/v9.6.0/api/overview.html
- cuFFT API reference structure: https://docs.nvidia.com/cuda/archive/12.0.0/cufft/index.html
- cuRAND Host API Overview: https://docs.nvidia.com/cuda/curand/host-api-overview.html
- cuSOLVER docs (Dense LAPACK helper reference): https://docs.nvidia.com/cuda/archive/12.2.1/cusolver/index.html
- NVRTC docs: https://docs.nvidia.com/cuda/nvrtc/
- NVML API Reference (categories/modules): https://docs.nvidia.com/deploy/nvml-api/nvml-api-reference.html and https://docs.nvidia.com/deploy/nvml-api/modules.html


## Plugin + Section Counts

| Plugin | Section | Documentation Label | Amount of routines |
|---|---|---|---:|
| `cublas` | `CublasHandler Extension functions` | `cuBLAS API - Extensions (Ex/Batched/StridedBatched)` | 2 |
| `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` | 13 |
| `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` | 46 |
| `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` | 66 |
| `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` | 39 |
| `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` | 11 |
| `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` | 16 |
| `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` | 7 |
| `cudadr` | `CudaDrHandler_driver_entry_point` | `CUDA Driver API - Driver Entry Point Access` | 1 |
| `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` | 6 |
| `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` | 13 |
| `cudadr` | `CudaDrHAndler_initialization` | `CUDA Driver API - Initialization` | 1 |
| `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` | 15 |
| `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` | 8 |
| `cudadr` | `CudaDrHandler_stream` | `CUDA Driver API - Stream Management` | 4 |
| `cudadr` | `CudaDrHandler_streammemory` | `CUDA Driver API - Stream Memory Operations` | 1 |
| `cudadr` | `CudaDrHandler_tensormap` | `CUDA Driver API - Tensor Map Object Management` | 1 |
| `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` | 9 |
| `cudadr` | `CudaDrHandler_unified` | `CUDA Driver API - Unified Addressing` | 1 |
| `cudadr` | `CudaDrHandler_version` | `CUDA Driver API - Version Management` | 1 |
| `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` | 7 |
| `cudart` | `CudaRtHandler_api` | `CUDA Runtime API - Execution Control (Attributes)` | 1 |
| `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` | 22 |
| `cudart` | `CudaRtHandler_error` | `CUDA Runtime API - Error Handling` | 3 |
| `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` | 7 |
| `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` | 9 |
| `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` | 8 |
| `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` | 7 |
| `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` | 26 |
| `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` | 7 |
| `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` | 12 |
| `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` | 6 |
| `cudart` | `CudaRtHandler_version` | `CUDA Runtime API - Version Management` | 3 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` | 84 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` | 6 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` | 58 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` | 37 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` | 10 |
| `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` | 51 |
| `cufft` | `Create/Destroy` | `cuFFT API - Handle Management` | 2 |
| `cufft` | `CufftX` | `cuFFT Xt API - Multi-GPU` | 4 |
| `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` | 9 |
| `cufft` | `Exec` | `cuFFT API - FFT Execution` | 6 |
| `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` | 6 |
| `cufft` | `MakePlan` | `cuFFT API - Plan Creation` | 5 |
| `cufft` | `Memory Management` | `cuFFT Xt API - Memory Management` | 3 |
| `cufft` | `Plan` | `cuFFT API - Plan Specification` | 4 |
| `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` | 15 |
| `cusolver` | `General` | `cuSOLVERDN - Helper Functions` | 4 |
| `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` | 6 |
| `nvml` | `General` | `NVML - Device Queries` | 21 |
| `nvml` | `General` | `NVML - Error Reporting` | 1 |
| `nvml` | `General` | `NVML - Event Handling Methods` | 2 |
| `nvml` | `General` | `NVML - Initialization and Cleanup` | 3 |
| `nvml` | `General` | `NVML - Query / Control API` | 1 |
| `nvml` | `General` | `NVML - System Queries` | 2 |
| `nvrtc` | `General` | `NVRTC - Error / Utility Functions` | 1 |

## Table

| Routine | Plugin | Section | Documentation Label |
|---|---|---|---|
| `cuArray3DCreate` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuArrayCreate` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuArrayDestroy` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cublasCaxpy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCcopy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCdotc_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCdotu_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCgemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCgemmBatched_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCgemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCgerc_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCgeru_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasChbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasChemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasChemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCher2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCher2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCher_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCherk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasChpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasChpr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasChpr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCreate_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasCrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCrotg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCsrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCsscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCswap_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasCsymm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCsymv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCsyr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCsyr2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCsyr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCsyrk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCtbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCtbsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCtpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCtpsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCtrmm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasCtrmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasCtrsm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDasum_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDaxpy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDcopy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDdot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDestroy_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasDgbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDgemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDgemmBatched_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDgemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDger_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDnrm2_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDrotg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDrotm_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDrotmg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDsbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDspmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDspr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDspr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDswap_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDsymm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDsymv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDsyr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDsyr2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDsyr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDsyrk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDtbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDtbsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDtpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDtpsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDtrmm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDtrmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasDtrsm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasDzasum_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasDznrm2_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasGemmEx` | `cublas` | `CublasHandler Extension functions` | `cuBLAS API - Extensions (Ex/Batched/StridedBatched)` |
| `cublasGemmStridedBatchedEx` | `cublas` | `CublasHandler Extension functions` | `cuBLAS API - Extensions (Ex/Batched/StridedBatched)` |
| `cublasGetMathMode` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasGetMatrix` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasGetPointerMode_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasGetVector` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasGetVersion_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasIcamax_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasIdamax_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasIsamax_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasIzamax_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasLtMatmul` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulAlgoGetHeuristic` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulDescCreate` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulDescDestroy` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulDescSetAttribute` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulPreferenceCreate` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulPreferenceDestroy` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatmulPreferenceSetAttribute` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatrixLayoutCreate` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatrixLayoutDestroy` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasLtMatrixLayoutSetAttribute` | `cublas` | `CublasHandler Lt functions` | `cuBLASLt API` |
| `cublasSasum_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSaxpy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasScasum_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasScnrm2_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasScopy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSdot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSetMathMode` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSetMatrix` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSetPointerMode_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSetStream_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSetVector` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSetWorkspace_v2` | `cublas` | `CublasHandler Helper functions` | `cuBLAS API - Context / Helper Functions` |
| `cublasSgbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSgemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSgemmBatched_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSgemmStridedBatched` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSgemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSger_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSnrm2_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSrotg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSrotm_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSrotmg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSsbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSspmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSspr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSspr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSswap_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasSsymm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSsymv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSsyr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSsyr2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasSsyr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasSsyrk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasStbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasStbsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasStpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasStpsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasStrmm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasStrmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasStrsm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZaxpy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZcopy_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZdotc_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZdotu_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZdrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZdscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZgemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZgemmBatched_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZgemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZgerc_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZgeru_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZhbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZhemm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZhemv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZher2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZher2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZher_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZherk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZhpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZhpr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZhpr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZrot_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZrotg_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZscal_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZswap_v2` | `cublas` | `CublasHandler Level1 functions` | `cuBLAS API - Level-1 BLAS` |
| `cublasZsymm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZsymv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZsyr2_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZsyr2k_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZsyr_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZsyrk_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZtbmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZtbsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZtpmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZtpsv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZtrmm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cublasZtrmv_v2` | `cublas` | `CublasHandler Level2 functions` | `cuBLAS API - Level-2 BLAS` |
| `cublasZtrsm_v2` | `cublas` | `CublasHandler Level3 functions` | `cuBLAS API - Level-3 BLAS` |
| `cuCtxAttach` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxCreate` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxDestroy` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxDetach` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxDisablePeerAccess` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxEnablePeerAccess` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxGetCurrent` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxGetDevice` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxGetLimit` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxPopCurrent` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxPushCurrent` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxSetCurrent` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxSetLimit` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuCtxSynchronize` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cudaChooseDevice` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaConfigureCall` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaDeviceCanAccessPeer` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceDisablePeerAccess` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceEnablePeerAccess` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceGetAttribute` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceGetDefaultMemPool` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceGetStreamPriorityRange` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceReset` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceSetCacheConfig` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceSetLimit` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDeviceSynchronize` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaDriverGetVersion` | `cudart` | `CudaRtHandler_version` | `CUDA Runtime API - Version Management` |
| `cudaEventCreate` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventCreateWithFlags` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventDestroy` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventElapsedTime` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventQuery` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventRecord` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaEventSynchronize` | `cudart` | `CudaRtHandler_event` | `CUDA Runtime API - Event Management` |
| `cudaFree` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaFreeArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaFreeAsync` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaFuncGetAttributes` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaFuncSetAttribute` | `cudart` | `CudaRtHandler_api` | `CUDA Runtime API - Execution Control (Attributes)` |
| `cudaFuncSetCacheConfig` | `cudart` | `CudaRtHandler_version` | `CUDA Runtime API - Version Management` |
| `cudaGetDevice` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaGetDeviceCount` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaGetDeviceProperties` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaGetErrorString` | `cudart` | `CudaRtHandler_error` | `CUDA Runtime API - Error Handling` |
| `cudaGetLastError` | `cudart` | `CudaRtHandler_error` | `CUDA Runtime API - Error Handling` |
| `cudaGetSymbolAddress` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaGetSymbolSize` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaGLSetGLDevice` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphCreate` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphDestroy` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphExecDestroy` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphGetNodes` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphicsGLRegisterBuffer` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphicsMapResources` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphicsResourceGetMappedPointer` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphicsResourceSetMapFlags` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphicsUnmapResources` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphicsUnregisterResource` | `cudart` | `CudaRtHandler_opengl` | `CUDA Runtime API - OpenGL / Graphics Interoperability` |
| `cudaGraphInstantiate` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphInstantiateWithFlags` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphLaunch` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaGraphUpload` | `cudart` | `CudaRtHandler_graph` | `CUDA Runtime API - Graph Management` |
| `cudaHostRegister` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaHostUnregister` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaIpcGetEventHandle` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaIpcGetMemHandle` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaIpcOpenEventHandle` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaIpcOpenMemHandle` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaLaunch` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaLaunchKernel` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaMalloc` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMalloc3DArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMallocArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMallocAsync` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaMallocManaged` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMallocPitch` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpy` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpy2D` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpy2DFromArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpy2DToArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpy3D` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyArrayToArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyAsync` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyFromArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyFromSymbol` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyPeerAsync` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyToArray` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemcpyToSymbol` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemGetInfo` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemPoolCreate` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaMemPoolDestroy` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaMemPoolGetAttribute` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaMemPoolSetAttribute` | `cudart` | `CudaRtHandler_stream_memory` | `CUDA Runtime API - Stream Ordered Memory Allocator` |
| `cudaMemset` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaMemset2D` | `cudart` | `CudaRtHandler_memory` | `CUDA Runtime API - Memory Management` |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessor` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaPeekAtLastError` | `cudart` | `CudaRtHandler_error` | `CUDA Runtime API - Error Handling` |
| `cudaPopCallConfiguration` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaPushCallConfiguration` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaRegisterFatBinary` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRegisterFatBinaryEnd` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRegisterFunction` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRegisterShared` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRegisterSharedVar` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRegisterVar` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cudaRuntimeGetVersion` | `cudart` | `CudaRtHandler_version` | `CUDA Runtime API - Version Management` |
| `cudaSetDevice` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaSetDeviceFlags` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaSetDoubleForDevice` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaSetDoubleForHost` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaSetupArgument` | `cudart` | `CudaRtHandler_execution` | `CUDA Runtime API - Execution Control` |
| `cudaSetValidDevices` | `cudart` | `CudaRtHandler_device` | `CUDA Runtime API - Device Management` |
| `cudaStreamBeginCapture` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamCreate` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamCreateWithFlags` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamCreateWithPriority` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamDestroy` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamEndCapture` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamGetCaptureInfo` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamIsCapturing` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamQuery` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamSynchronize` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaStreamWaitEvent` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaThreadExchangeStreamCaptureMode` | `cudart` | `CudaRtHandler_stream` | `CUDA Runtime API - Stream Management` |
| `cudaUnregisterFatBinary` | `cudart` | `CudaRtHandler_internal` | `CUDA Runtime API - C++ API Routines / Driver Interactions` |
| `cuDeviceCanAccessPeer` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuDeviceComputeCapability` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDeviceGet` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDeviceGetAttribute` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDeviceGetCount` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDeviceGetName` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDeviceGetProperties` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cuDevicePrimaryCtxGetState` | `cudadr` | `CudaDrHandler_context` | `CUDA Driver API - Context Management / Peer Context Access` |
| `cuDeviceTotalMem` | `cudadr` | `CudaDrHandler_device` | `CUDA Driver API - Device Management` |
| `cudnnActivationBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnActivationForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnAddTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnBackendCreateDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBackendDestroyDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBackendExecute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBackendFinalize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBackendGetAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBackendSetAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Backend API (Graph / Descriptor API)` |
| `cudnnBatchNormalizationBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnBatchNormalizationBackwardEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnBatchNormalizationForwardInference` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnBatchNormalizationForwardTraining` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnBatchNormalizationForwardTrainingEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnConvolutionBackwardBias` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnConvolutionBackwardData` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnConvolutionBackwardFilter` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnConvolutionBiasActivationForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnConvolutionForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnCopyAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreate` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateActivationDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCreateAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateAlgorithmPerformance` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateAttnDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateConvolutionDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnCreateCTCLossDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnCreateDropoutDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCreateFilterDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateFusedOpsConstParamPack` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateFusedOpsPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateFusedOpsVariantParamPack` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateLRNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateOpTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCreatePersistentRNNPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnCreatePoolingDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnCreateReduceTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCreateRNNDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnCreateRNNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnCreateSeqDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateSpatialTransformerDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnCreateTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCreateTensorTransformDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnCTCLoss` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnDeriveBNTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroy` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyActivationDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroyAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyAlgorithmPerformance` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyAttnDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyConvolutionDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnDestroyCTCLossDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnDestroyDropoutDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroyFilterDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyFusedOpsConstParamPack` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyFusedOpsPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyFusedOpsVariantParamPack` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyLRNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyOpTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroyPersistentRNNPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnDestroyPoolingDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnDestroyReduceTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroyRNNDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnDestroyRNNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnDestroySeqDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroySpatialTransformerDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDestroyTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDestroyTensorTransformDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDivisiveNormalizationBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDivisiveNormalizationForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnDropoutBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDropoutForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDropoutGetReserveSpaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnDropoutGetStatesSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnFindConvolutionBackwardDataAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindConvolutionBackwardDataAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindConvolutionBackwardFilterAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindConvolutionBackwardFilterAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindConvolutionForwardAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindConvolutionForwardAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnFindRNNBackwardDataAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnFindRNNBackwardWeightsAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnFindRNNForwardInferenceAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnFindRNNForwardTrainingAlgorithmEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnFusedOpsExecute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetActivationDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetAlgorithmPerformance` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetAlgorithmSpaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetAttnDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetBatchNormalizationBackwardExWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetCallback` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetConvolution2dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolution2dForwardOutputDim` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardDataAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardDataAlgorithm_v7` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardDataAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardDataWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardFilterAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardFilterAlgorithm_v7` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardFilterAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionBackwardFilterWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionForwardAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionForwardAlgorithm_v7` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionForwardAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionForwardWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionGroupCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionMathType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionNdForwardOutputDim` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetConvolutionReorderType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnGetCTCLossDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetCTCLossDescriptorEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetCTCLossWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetDropoutDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetErrorString` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilter4dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilter4dDescriptor_v3` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilter4dDescriptor_v4` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilterNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilterNdDescriptor_v3` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilterNdDescriptor_v4` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFilterSizeInBytes` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFoldedConvBackwardDataDescriptors` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFusedOpsConstParamPackAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetFusedOpsVariantParamPackAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetLastErrorString` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetLRNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetMultiHeadAttnBuffers` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetMultiHeadAttnWeights` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetOpTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetPooling2dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnGetPooling2dForwardOutputDim` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnGetPoolingNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnGetPoolingNdForwardOutputDim` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnGetProperty` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetReduceTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetReductionIndicesSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetReductionWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetRNNBackwardDataAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNBackwardWeightsAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNBiasMode` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNDescriptor_v5` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNDescriptor_v6` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNDescriptor_v8` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNForwardInferenceAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNForwardTrainingAlgorithmMaxCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNLinLayerBiasParams` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNLinLayerMatrixParams` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNMatrixMathType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNPaddingMode` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNParamsSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNProjectionLayers` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNTempSpaceSizes` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNTrainingReserveSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNWeightSpaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetRNNWorkspaceSize` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnGetSeqDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetStream` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnGetTensor4dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetTensorNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetTensorSizeInBytes` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetTensorTransformDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnGetVersion` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnIm2Col` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnInitTransformDest` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnLRNCrossChannelBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnLRNCrossChannelForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnMakeFusedOpsPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnMultiHeadAttnBackwardData` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnMultiHeadAttnBackwardWeights` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnMultiHeadAttnForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnOpTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnPoolingBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnPoolingForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnReduceTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnReorderFilterAndBias` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnRestoreAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnRestoreDropoutDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnRNNBackwardData` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNBackwardDataEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNBackwardWeights` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNBackwardWeightsEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNForwardInference` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNForwardInferenceEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNForwardTraining` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNForwardTrainingEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNGetClip` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnRNNSetClip` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSaveAlgorithm` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnScaleTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetActivationDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetAlgorithmPerformance` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetAttnDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetCallback` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetConvolution2dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnSetConvolutionGroupCount` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnSetConvolutionMathType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnSetConvolutionNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnSetConvolutionReorderType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Convolution (cnn)` |
| `cudnnSetCTCLossDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetCTCLossDescriptorEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetDropoutDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetFilter4dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFilter4dDescriptor_v3` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFilter4dDescriptor_v4` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFilterNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFilterNdDescriptor_v3` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFilterNdDescriptor_v4` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFusedOpsConstParamPackAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetFusedOpsVariantParamPackAttribute` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetLRNDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetOpTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetPersistentRNNPlan` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetPooling2dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnSetPoolingNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Pooling / Ops` |
| `cudnnSetReduceTensorDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetRNNAlgorithmDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNBiasMode` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNDescriptor_v5` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNDescriptor_v6` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNDescriptor_v8` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNMatrixMathType` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNPaddingMode` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetRNNProjectionLayers` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Advanced (RNN/CTC/Attention)` |
| `cudnnSetSeqDataDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetSpatialTransformerNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetStream` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSetTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetTensor4dDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetTensor4dDescriptorEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetTensorNdDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSetTensorTransformDescriptor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSoftmaxBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSoftmaxForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnSpatialTfGridGeneratorBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSpatialTfGridGeneratorForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSpatialTfSamplerBackward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnSpatialTfSamplerForward` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnTransformFilter` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN API - Legacy + Backend` |
| `cudnnTransformTensor` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cudnnTransformTensorEx` | `cudnn` | `CublasHandler Query Platform Info` | `cuDNN Legacy API - Tensor/Ops` |
| `cuDriverGetVersion` | `cudadr` | `CudaDrHandler_version` | `CUDA Driver API - Version Management` |
| `cuEventCreate` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cuEventDestroy` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cuEventElapsedTime` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cuEventQuery` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cuEventRecord` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cuEventSynchronize` | `cudadr` | `CudaDrHandler_event` | `CUDA Driver API - Event Management` |
| `cufftCreate` | `cufft` | `Create/Destroy` | `cuFFT API - Handle Management` |
| `cufftDestroy` | `cufft` | `Create/Destroy` | `cuFFT API - Handle Management` |
| `cufftEstimate1d` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftEstimate2d` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftEstimate3d` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftEstimateMany` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftExecC2C` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftExecC2R` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftExecD2Z` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftExecR2C` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftExecZ2D` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftExecZ2Z` | `cufft` | `Exec` | `cuFFT API - FFT Execution` |
| `cufftGetProperty` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftGetSize` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetSize1d` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetSize2d` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetSize3d` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetSizeMany` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetSizeMany64` | `cufft` | `GetSize` | `cuFFT API - Refined Work Area Size` |
| `cufftGetVersion` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftMakePlan1d` | `cufft` | `MakePlan` | `cuFFT API - Plan Creation` |
| `cufftMakePlan2d` | `cufft` | `MakePlan` | `cuFFT API - Plan Creation` |
| `cufftMakePlan3d` | `cufft` | `MakePlan` | `cuFFT API - Plan Creation` |
| `cufftMakePlanMany` | `cufft` | `MakePlan` | `cuFFT API - Plan Creation` |
| `cufftMakePlanMany64` | `cufft` | `MakePlan` | `cuFFT API - Plan Creation` |
| `cufftPlan1d` | `cufft` | `Plan` | `cuFFT API - Plan Specification` |
| `cufftPlan2d` | `cufft` | `Plan` | `cuFFT API - Plan Specification` |
| `cufftPlan3d` | `cufft` | `Plan` | `cuFFT API - Plan Specification` |
| `cufftPlanMany` | `cufft` | `Plan` | `cuFFT API - Plan Specification` |
| `cufftSetAutoAllocation` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftSetStream` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftSetWorkArea` | `cufft` | `Estimate` | `cuFFT API - Estimated Work Area` |
| `cufftXtExecDescriptorC2C` | `cufft` | `CufftX` | `cuFFT Xt API - Multi-GPU` |
| `cufftXtFree` | `cufft` | `Memory Management` | `cuFFT Xt API - Memory Management` |
| `cufftXtMakePlanMany` | `cufft` | `CufftX` | `cuFFT Xt API - Multi-GPU` |
| `cufftXtMalloc` | `cufft` | `Memory Management` | `cuFFT Xt API - Memory Management` |
| `cufftXtMemcpy` | `cufft` | `Memory Management` | `cuFFT Xt API - Memory Management` |
| `cufftXtSetCallback` | `cufft` | `CufftX` | `cuFFT Xt API - Multi-GPU` |
| `cufftXtSetGPUs` | `cufft` | `CufftX` | `cuFFT Xt API - Multi-GPU` |
| `cuFuncGetAttribute` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuFuncSetBlockShape` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuFuncSetCacheConfig` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuFuncSetSharedSize` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuGetProcAddress` | `cudadr` | `CudaDrHandler_driver_entry_point` | `CUDA Driver API - Driver Entry Point Access` |
| `cuInit` | `cudadr` | `CudaDrHAndler_initialization` | `CUDA Driver API - Initialization` |
| `cuLaunch` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuLaunchGrid` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuLaunchGridAsync` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuLaunchKernel` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuMemAddressFree` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemAddressReserve` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemAlloc` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemAllocPitch` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemcpy2D` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemcpyDtoH` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemcpyHtoD` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemCreate` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemExportToShareableHandle` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemFree` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemGetAddressRange` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemGetAllocationGranularity` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemGetInfo` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemImportFromShareableHandle` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemMap` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemRelease` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemSetAccess` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuMemsetD32Async` | `cudadr` | `CudaDrHandler_memory` | `CUDA Driver API - Memory Management` |
| `cuMemUnmap` | `cudadr` | `CudaDrHandler_virtmemory` | `CUDA Driver API - Virtual Memory Management` |
| `cuModuleGetFunction` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleGetGlobal` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleGetTexRef` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleLoad` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleLoadData` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleLoadDataEx` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleLoadFatBinary` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuModuleUnload` | `cudadr` | `CudaDrHandler_module` | `CUDA Driver API - Module Management` |
| `cuParamSetf` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuParamSeti` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuParamSetSize` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuParamSetTexRef` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuParamSetv` | `cudadr` | `CudaDrHandler_execution` | `CUDA Driver API - Execution Control` |
| `cuPointerGetAttribute` | `cudadr` | `CudaDrHandler_unified` | `CUDA Driver API - Unified Addressing` |
| `curandCreateGenerator` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandCreateGeneratorHost` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandDestroyGenerator` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerate` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateLogNormal` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateLogNormalDouble` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateLongLong` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateNormal` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateNormalDouble` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGeneratePoisson` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateUniform` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandGenerateUniformDouble` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandSetGeneratorOffset` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandSetPseudoRandomGeneratorSeed` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `curandSetQuasiRandomGeneratorDimensions` | `curand` | `CurandHandler Query Platform Info` | `cuRAND Host API - Generator / Generation Functions` |
| `cusolverDnCreate` | `cusolver` | `General` | `cuSOLVERDN - Helper Functions` |
| `cusolverDnDestroy` | `cusolver` | `General` | `cuSOLVERDN - Helper Functions` |
| `cusolverDnGetStream` | `cusolver` | `General` | `cuSOLVERDN - Helper Functions` |
| `cusolverDnSetStream` | `cusolver` | `General` | `cuSOLVERDN - Helper Functions` |
| `cusparseCreate` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cusparseDestroy` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cusparseGetErrorString` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cusparseGetStream` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cusparseGetVersion` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cusparseSetStream` | `cusparse` | `General` | `cuSPARSE - Implemented Legacy API Subset` |
| `cuStreamCreate` | `cudadr` | `CudaDrHandler_stream` | `CUDA Driver API - Stream Management` |
| `cuStreamDestroy` | `cudadr` | `CudaDrHandler_stream` | `CUDA Driver API - Stream Management` |
| `cuStreamQuery` | `cudadr` | `CudaDrHandler_stream` | `CUDA Driver API - Stream Management` |
| `cuStreamSynchronize` | `cudadr` | `CudaDrHandler_stream` | `CUDA Driver API - Stream Management` |
| `cuStreamWriteValue32` | `cudadr` | `CudaDrHandler_streammemory` | `CUDA Driver API - Stream Memory Operations` |
| `cuTensorMapEncodeTiled` | `cudadr` | `CudaDrHandler_tensormap` | `CUDA Driver API - Tensor Map Object Management` |
| `cuTexRefGetAddress` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefGetArray` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefGetFlags` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetAddress` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetAddressMode` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetArray` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetFilterMode` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetFlags` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `cuTexRefSetFormat` | `cudadr` | `CudaDrHandler_texture` | `CUDA Driver API - Texture Reference/Object Management` |
| `nvmlDeviceGetComputeMode` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetCount` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetDisplayActive` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetEccMode` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetEnforcedPowerLimit` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetFanSpeed` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetHandleByIndex` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetIndex` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetMaxMigDeviceCount` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetMemoryInfo` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetMigMode` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetName` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetPciInfo_v3` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetPerformanceState` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetPersistenceMode` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetPowerUsage` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetTemperature` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetUtilizationRates` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceGetVirtualizationMode` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceIsMigDeviceHandle` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlDeviceValidateInforom` | `nvml` | `General` | `NVML - Device Queries` |
| `nvmlErrorString` | `nvml` | `General` | `NVML - Error Reporting` |
| `nvmlEventSetCreate` | `nvml` | `General` | `NVML - Event Handling Methods` |
| `nvmlEventSetFree` | `nvml` | `General` | `NVML - Event Handling Methods` |
| `nvmlInit` | `nvml` | `General` | `NVML - Initialization and Cleanup` |
| `nvmlInitWithFlags` | `nvml` | `General` | `NVML - Initialization and Cleanup` |
| `nvmlInternalGetExportTable` | `nvml` | `General` | `NVML - Query / Control API` |
| `nvmlShutdown` | `nvml` | `General` | `NVML - Initialization and Cleanup` |
| `nvmlSystemGetCudaDriverVersion_v2` | `nvml` | `General` | `NVML - System Queries` |
| `nvmlSystemGetDriverVersion` | `nvml` | `General` | `NVML - System Queries` |
| `nvrtcGetErrorString` | `nvrtc` | `General` | `NVRTC - Error / Utility Functions` |
