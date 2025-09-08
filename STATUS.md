# cudaDr (-lcuda)

| Function                          | Implemented | Tested  | Working |        Notes             |
| --------------------------------- | ----------- | ------- | ------- | ------------------------ |
| `cuInit`                          | ✅          | ❌      | ❓      |                          |
| `cuCtxCreate`                     | ✅          | ❌      | ❓      |                          |
| `cuCtxAttach`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuCtxDestroy`                    | ✅          | ❌      | ❓      |                          |
| `cuCtxDetach`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuCtxSetCurrent`                 | ❌          | ❌      | ❌      |                          |
| `cuCtxGetCurrent`                 | ❌          | ❌      | ❌      |                          |
| `cuCtxGetDevice`                  | ✅          | ❌      | ❓      |                          |
| `cuCtxPopCurrent`                 | ✅          | ❌      | ❓      |                          |
| `cuCtxPushCurrent`                | ✅          | ❌      | ❓      |                          |
| `cuCtxSynchronize`                | ✅          | ❌      | ❓      |                          |
| `cuCtxDisablePeerAccess`          | ✅          | ❌      | ❓      |                          |
| `cuCtxEnablePeerAccess`           | ✅          | ❌      | ❓      |                          |
| `cuDeviceCanAccessPeer`           | ✅          | ❌      | ❓      |                          |
| `cuDeviceComputeCapability`       | ✅          | ❌      | ❓      | Deprecated               |
| `cuDeviceGet`                     | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetAttribute`            | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetCount`                | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetName`                 | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetProperties`           | ✅          | ❌      | ❓      | Deprecated               |
| `cuDeviceTotalMem`                | ✅          | ❌      | ❓      |                          |
| `cuParamSetSize`                  | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncSetBlockShape`             | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchGrid`                    | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncGetAttribute`              | ✅          | ❌      | ❓      |                          |
| `cuFuncSetSharedSize`             | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunch`                        | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetf`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSeti`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetv`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetTexRef`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchGridAsync`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncSetCacheConfig`            | ✅          | ❌      | ❓      |                          |
| `cuMemFree`                       | ✅          | ❌      | ❓      |                          |
| `cuMemAlloc`                      | ✅          | ❌      | ❓      |                          |
| `cuMemAllocManaged`               | ❌          | ❌      | ❌      |                          |
| `cuMemHostAlloc`                  | ❌          | ❌      | ❌      |                          |
| `cuMemHostFree`                   | ❌          | ❌      | ❌      |                          |
| `cuMemcpyDtoH`                    | ✅          | ❌      | ❓      |                          |
| `cuMemcpyHtoD`                    | ✅          | ❌      | ❓      |                          |
| `cuMemcpyDtoD`                    | ❌          | ❌      | ❌      |                          |
| `cuMemcpyHtoDAsync`               | ❌          | ❌      | ❌      |                          |
| `cuMemcpyDtoHAsync`               | ❌          | ❌      | ❌      |                          |
| `cuMemsetD32`                     | ❌          | ❌      | ❌      |                          |
| `cuMemsetD8`                      | ❌          | ❌      | ❌      |                          |
| `cuArrayCreate`                   | ✅          | ❌      | ❓      |                          |
| `cuMemcpy2D`                      | ✅          | ❌      | ❓      |                          |
| `cuArrayDestroy`                  | ✅          | ❌      | ❓      |                          |
| `cuArray3DCreate`                 | ✅          | ❌      | ❓      |                          |
| `cuMemAllocPitch`                 | ✅          | ❌      | ❓      |                          |
| `cuMemGetAddressRange`            | ✅          | ❌      | ❓      |                          |
| `cuMemGetInfo`                    | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadData`                | ✅          | ❌      | ❓      |                          |
| `cuModuleLoad`                    | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadFatBinary`           | ✅          | ❌      | ❓      |                          |
| `cuModuleUnload`                  | ✅          | ❌      | ❓      |                          |
| `cuModuleGetFunction`             | ✅          | ❌      | ❓      |                          |
| `cuModuleGetGlobal`               | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadDataEx`              | ✅          | ❌      | ❓      |                          |
| `cuModuleGetTexRef`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuDriverGetVersion`              | ✅          | ✅      | ✅      |                          |
| `cuStreamCreate`                  | ✅          | ❌      | ❓      |                          |
| `cuStreamDestroy`                 | ✅          | ❌      | ❓      |                          |
| `cuStreamQuery`                   | ✅          | ❌      | ❓      |                          |
| `cuStreamSynchronize`             | ✅          | ❌      | ❓      |                          |
| `cuEventCreate`                   | ✅          | ❌      | ❓      |                          |
| `cuEventDestroy`                  | ✅          | ❌      | ❓      |                          |
| `cuEventElapsedTime`              | ✅          | ❌      | ❓      |                          |
| `cuEventQuery`                    | ✅          | ❌      | ❓      |                          |
| `cuEventRecord`                   | ✅          | ❌      | ❓      |                          |
| `cuEventSynchronize`              | ✅          | ❌      | ❓      |                          |
| `cuLinkCreate`                    | ❌          | ❌      | ❌      |                          |
| `cuLinkAddData`                   | ❌          | ❌      | ❌      |                          |
| `cuLinkComplete`                  | ❌          | ❌      | ❌      |                          |
| `cuModuleLoadDataEx`              | ❌          | ❌      | ❌      |                          |
| `cuGraphicsGLRegisterBuffer`      | ❌          | ❌      | ❌      |                          |
| `cuGraphicsMapResources`          | ❌          | ❌      | ❌      |                          |
| `cuTexRefSetArray`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetAddressMode`          | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFilterMode`           | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFlags`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFormat`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetAddress`              | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetArray`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetFlags`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetAddress`              | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchKernel`                  | ✅          | ❌      | ❓      |                          |

# cudaRT (-lcudart)

| Function                                                 | Implemented | Tested | Working  |          Notes          |
| -------------------------------------------------------- | ----------- | ------ | -------- | ----------------------- |
| `cudaMalloc`                                             | ✅          | ✅      | ✅      |                         |
| `cudaFree`                                               | ✅          | ✅      | ✅      |                         |
| `cudaMemGetInfo`                                         | ✅          | ✅      | ✅      |                         |
| `cudaThreadExchangeStreamCaptureMode`                    | ✅          | ✅      | ✅      |                         |
| `cudaDeviceGetDefaultMemPool`                            | ✅          | ✅      | ✅      |                         |
| `cudaMemPoolGetAttribute`                                | ✅          | ✅      | ✅      |                         |
| `cudaMallocHost`                                         | ❌          | ❌      | ❌      |                         |
| `cudaFreeHost`                                           | ❌          | ❌      | ❌      |                         |
| `cudaMemcpy`                                             | ✅          | ✅      | ✅      |                         |
| `cudaMemcpyAsync`                                        | ✅          | ✅      | ✅      |                         |
| `cudaMemset`                                             | ✅          | ✅      | ✅      |                         |
| `cudaMemsetAsync`                                        | ✅          | ✅      | ✅      |                         |
| `cudaGetDevice`                                          | ✅          | ✅      | ✅      |                         |
| `cudaSetDevice`                                          | ✅          | ✅      | ✅      |                         |
| `cudaStreamCreate`                                       | ✅          | ✅      | ✅      |                         |
| `cudaStreamQuery`                                        | ✅          | ❌      | ❓      |                         |
| `cudaStreamSynchronize`                                  | ✅          | ❌      | ❓      |                         |
| `cudaStreamCreateWithFlags`                              | ✅          | ❌      | ❓      |                         |
| `cudaStreamWaitEvent`                                    | ✅          | ❌      | ❓      |                         |
| `cudaStreamCreateWithPriority`                           | ✅          | ❌      | ❓      |                         |
| `cudaStreamDestroy`                                      | ✅          | ✅      | ✅      |                         |
| `cudaEventCreate`                                        | ✅          | ✅      | ✅      |                         |
| `cudaEventCreateWithFlags`                               | ✅          | ❌      | ❓      |                         |
| `cudaEventQuery`                                         | ✅          | ❌      | ❓      |                         |
| `cudaEventRecord`                                        | ✅          | ✅      | ✅      |                         |
| `cudaEventSynchronize`                                   | ✅          | ✅      | ✅      |                         |
| `cudaEventElapsedTime`                                   | ✅          | ✅      | ✅      |                         |
| `cudaEventDestroy`                                       | ✅          | ✅      | ✅      |                         |
| `cudaChooseDevice`                                       | ✅          | ❌      | ❓      |                         |
| `cudaGetDeviceCount`                                     | ✅          | ✅      | ✅      |                         |
| `cudaGetDeviceProperties`                                | ✅          | ❌      | ❓      |                         |
| `cudaSetDeviceFlags`                                     | ✅          | ❌      | ❓      |                         |
| `cudaSetValidDevices`                                    | ✅          | ❌      | ❓      |                         |
| `cudaDeviceReset`                                        | ✅          | ❌      | ❓      |                         |
| `cudaDeviceSynchronize`                                  | ✅          | ✅      | ✅      |                         |
| `cudaDeviceSetCacheConfig`                               | ✅          | ❌      | ❓      |                         |
| `cudaDeviceSetLimit`                                     | ✅          | ❌      | ❓      |                         |
| `cudaDeviceCanAccessPeer`                                | ✅          | ❌      | ❓      |                         |
| `cudaDeviceEnablePeerAccess`                             | ✅          | ❌      | ❓      |                         |
| `cudaDeviceDisablePeerAccess`                            | ✅          | ❌      | ❓      |                         |
| `cudaIpcGetMemHandle`                                    | ✅          | ❌      | ❓      |                         |
| `cudaIpcGetEventHandle`                                  | ✅          | ❌      | ❓      |                         |
| `cudaIpcOpenEventHandle`                                 | ✅          | ❌      | ❓      |                         |
| `cudaIpcOpenMemHandle`                                   | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessor`          | ✅          | ❌      | ❓      |                         |
| `cudaDeviceGetAttribute`                                 | ✅          | ❌      | ❓      |                         |
| `cudaDeviceGetStreamPriorityRange`                       | ✅          | ❌      | ❓      |                         |
| `cudaGetErrorString`                                     | ✅          | ❌      | ❓      |                         |
| `cudaGetLastError`                                       | ✅          | ❌      | ❓      |                         |
| `cudaPeekAtLastError`                                    | ✅          | ❌      | ❓      |                         |
| `cudaFuncGetAttributes`                                  | ✅          | ❌      | ❓      |                         |
| `cudaFuncSetCacheConfig`                                 | ✅          | ❌      | ❓      |                         |
| `cudaLaunchKernel`                                       | ✅          | ✅      | ✅      | Tested using both `<<<>>>` and direct syntax |
| `__cudaPushCallConfiguration`                            | ✅          | ✅      | ✅      | Tested implicitly using `<<<>>>` syntax |
| `__cudaPopCallConfiguration`                             | ✅          | ✅      | ✅      | Tested implicitly using `<<<>>>` syntax |
| `cudaLaunch`                                             | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0 |
| `cudaConfigureCall`                                      | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0 |
| `cudaSetupArgument`                                      | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0  |
| `cudaRegisterFatBinary`                                  | ✅          | ✅      | ✅      | Automatically called at program start |
| `cudaRegisterFatBinaryEnd`                               | ✅          | ✅      | ✅      | Automatically called after `cudaRegisterFatBinary` |
| `cudaUnregisterFatBinary`                                | ✅          | ✅      | ✅      | Automatically called at program exit |
| `cudaSetDoubleForHost`                                   | ✅          | ❌      | ❓      |                         |
| `cudaSetDoubleForDevice`                                 | ✅          | ❌      | ❓      |                         |
| `cudaRegisterFunction`                                   | ✅          | ❌      | ❓      |                         |
| `cudaRegisterVar`                                        | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSharedVar`                                  | ✅          | ❌      | ❓      |                         |
| `cudaRegisterShared`                                     | ✅          | ❌      | ❓      |                         |
| `cudaRegisterTexture`                                    | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSurface`                                    | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSharedMemory`                               | ✅          | ❌      | ❓      |                         |
| `cudaRequestSharedMemory`                                | ✅          | ❌      | ❓      |                         |
| `cudaFreeArray`                                          | ✅          | ❌      | ❓      |                         |
| `cudaGetSymbolAddress`                                   | ✅          | ❌      | ❓      |                         |
| `cudaGetSymbolSize`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMallocArray`                                        | ✅          | ❌      | ❓      |                         |
| `cudaMallocPitch`                                        | ✅          | ❌      | ❓      |                         |
| `cudaMallocManaged`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy2D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy3D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyFromSymbol`                                   | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyToArray`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpyToSymbol`                                     | ✅          | ❌      | ❓      |                         |
| `cudaMemset2D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyFromArray`                                    | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpyArrayToArray`                                 | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpy2DFromArray`                                  | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy2DToArray`                                    | ✅          | ❌      | ❓      |                         |
| `cudaMalloc3DArray`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyPeerAsync`                                    | ✅          | ❌      | ❓      |                         |
| `cudaGLSetGLDevice`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaGraphicsGLRegisterBuffer`                           | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsMapResources`                               | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsResourceGetMappedPointer`                   | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsUnmapResources`                             | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsUnregisterResource`                         | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsResourceSetMapFlags`                        | ✅          | ❌      | ❓      |                         |
| `cudaBindTexture`                                        | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindTexture2D`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindTextureToArray`                                 | ✅          | ❌      | ❓      | Deprecated              |
| `cudaCreateTextureObject`                                | ✅          | ❌      | ❓      |                         |
| `cudaGetChannelDesc`                                     | ✅          | ❌      | ❓      |                         |
| `cudaGetTextureAlignmentOffset`                          | ✅          | ❌      | ❓      | Deprecated              |
| `cudaGetTextureReference`                                | ✅          | ❌      | ❓      | Deprecated              |
| `cudaUnbindTexture`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindSurfaceToArray`                                 | ✅          | ❌      | ❓      |                         |
| `cudaGetTextureReference`                                | ✅          | ❌      | ❓      |                         |
| `cudaThreadExit`                                         | ✅          | ❌      | ❓      | Deprecated in favor of `cudaDeviceReset` |
| `cudaThreadSynchronize`                                  | ✅          | ❌      | ❓      | Deprecated in favor of `cudaDeviceSynchronize` |
| `cudaDriverGetVersion`                                   | ✅          | ❌      | ❓      |                         |
| `cudaRuntimeGetVersion`                                  | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessor`          | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags` | ✅          | ❌      | ❓      |                         |


# cuBLAS (-lcublas)

| Function                | Implemented | Tested | Working  |          Notes          |
| ----------------------- | ----------- | ------ | -------- | ------------------------|
| `cublasCreate`          | ✅          | ✅      | ✅      |                         |
| `cublasDestroy`         | ✅          | ✅      | ✅      |                         |
| `cublasGetVersion`      | ✅          | ✅      | ✅      |                         |
| `cublasSetStream`       | ✅          | ✅      | ✅      |                         |
| `cublasSetVector`       | ✅          | ❌      | ❓      |                         |
| `cublasGetVector`       | ✅          | ❌      | ❓      |                         |
| `cublasSetMatrix`       | ✅          | ❌      | ❓      |                         |
| `cublasGetMatrix`       | ✅          | ❌      | ❓      |                         |
| `cublasGetPointerMode`  | ✅          | ❌      | ❓      |                         |
| `cublasSetPointerMode`  | ✅          | ❌      | ❓      |                         |
| `cublasSaxpy`           | ✅          | ✅      | ✅      | works only if alpha is host pointer |
| `cublasDaxpy`           | ✅          | ✅      | ✅      | works only if alpha is host pointer |
| `cublasCaxpy`           | ✅          | ❌      | ❓      |                         |
| `cublasZaxpy`           | ✅          | ❌      | ❓      |                         |
| `cublasScopy`           | ✅          | ✅      | ✅      |                         |
| `cublasDcopy`           | ✅          | ✅      | ✅      |                         |
| `cublasCcopy`           | ✅          | ❌      | ❓      |                         |
| `cublasZcopy`           | ✅          | ❌      | ❓      |                         |
| `cublasSnrm2`           | ✅          | ✅      | ✅      | works only if result is host pointer |
| `cublasDnrm2`           | ✅          | ✅      | ✅      | works only if result is host pointer |
| `cublasSgemm`           | ✅          | ✅      | ✅      | works only if alpha, beta are host pointers |
| `cublasDgemm`           | ✅          | ✅      | ✅      | works only if alpha, beta are host pointers |
| `cublasSgemv`           | ✅          | ✅      | ✅      | works only if alpha, beta are host pointers |
| `cublasDgemv`           | ✅          | ✅      | ✅      | works only if alpha, beta are host pointers |
| `cublasSdot`            | ✅          | ✅      | ✅      | works only if result is host pointer        |
| `cublasDdot`            | ✅          | ✅      | ✅      | works only if result is host pointer        |
| `cublasCdotu`           | ✅          | ❌      | ❓      |                         |
| `cublasCdotc`           | ✅          | ❌      | ❓      |                         |
| `cublasZdotu`           | ✅          | ❌      | ❓      |                         |
| `cublasZdotc`           | ✅          | ❌      | ❓      |                         |
| `cublasSscal`           | ✅          | ❌      | ❓      |                         |
| `cublasDscal`           | ✅          | ❌      | ❓      |                         |
| `cublasCscal`           | ✅          | ❌      | ❓      |                         |
| `cublasCsscal`          | ✅          | ❌      | ❓      |                         |
| `cublasZscal`           | ✅          | ❌      | ❓      |                         |
| `cublasZdscal`          | ✅          | ❌      | ❓      |                         |
| `cublasSswap`           | ✅          | ❌      | ❓      |                         |
| `cublasDswap`           | ✅          | ❌      | ❓      |                         |
| `cublasCswap`           | ✅          | ❌      | ❓      |                         |
| `cublasZswap`           | ✅          | ❌      | ❓      |                         |
| `cublasIsamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIdamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIcamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIzamax`          | ✅          | ❌      | ❓      |                         |
| `cublasSasum`           | ✅          | ❌      | ❓      |                         |
| `cublasDasum`           | ✅          | ❌      | ❓      |                         |
| `cublasScasum`          | ✅          | ❌      | ❓      |                         |
| `cublasDzasum`          | ✅          | ❌      | ❓      |                         |
| `cublasSrot`            | ✅          | ❌      | ❓      |                         |
| `cublasDrot`            | ✅          | ❌      | ❓      |                         |
| `cublasCrot`            | ✅          | ❌      | ❓      |                         |
| `cublasCsrot`           | ✅          | ❌      | ❓      |                         |
| `cublasZrot`            | ✅          | ❌      | ❓      |                         |
| `cublasZdrot`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasDrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasCrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasZrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotm`           | ✅          | ❌      | ❓      |                         |
| `cublasDrotm`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotmg`          | ✅          | ❌      | ❓      |                         |
| `cublasDrotmg`          | ✅          | ❌      | ❓      |                         |
| `cublasCgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasZgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasStbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasSsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasDsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasCsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasZsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasChemv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhemv`           | ✅          | ❌      | ❓      |                         |
| `cublasSsbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDsbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasChbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSspmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDspmv`           | ✅          | ❌      | ❓      |                         |
| `cublasChpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSger`            | ✅          | ❌      | ❓      |                         |
| `cublasDger`            | ✅          | ❌      | ❓      |                         |
| `cublasCgeru`           | ✅          | ❌      | ❓      |                         |
| `cublasCgerc`           | ✅          | ❌      | ❓      |                         |
| `cublasZgeru`           | ✅          | ❌      | ❓      |                         |
| `cublasZgerc`           | ✅          | ❌      | ❓      |                         |
| `cublasSsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasDsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasCsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasZsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasCher`            | ✅          | ❌      | ❓      |                         |
| `cublasZher`            | ✅          | ❌      | ❓      |                         |
| `cublasSspr`            | ✅          | ❌      | ❓      |                         |
| `cublasDspr`            | ✅          | ❌      | ❓      |                         |
| `cublasChpr`            | ✅          | ❌      | ❓      |                         |
| `cublasZhpr`            | ✅          | ❌      | ❓      |                         |
| `cublasSsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasDsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasCsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasZsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasCher2`           | ✅          | ❌      | ❓      |                         |
| `cublasZher2`           | ✅          | ❌      | ❓      |                         |
| `cublasSspr2`           | ✅          | ❌      | ❓      |                         |
| `cublasDspr2`           | ✅          | ❌      | ❓      |                         |
| `cublasChpr2`           | ✅          | ❌      | ❓      |                         |
| `cublasZhpr2`           | ✅          | ❌      | ❓      |                         |
| `cublasSgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasDgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasCgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasZgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasSgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasDgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasCgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasZgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasScnrm2`          | ✅          | ❌      | ❓      |                         |
| `cublasDznrm2`          | ✅          | ❌      | ❓      |                         |
| `cublasSsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasDsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasCsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasZsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasCherk`           | ✅          | ❌      | ❓      |                         |
| `cublasZherk`           | ✅          | ❌      | ❓      |                         |
| `cublasSsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasDsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasCsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasZsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasCher2k`          | ✅          | ❌      | ❓      |                         |
| `cublasZher2k`          | ✅          | ❌      | ❓      |                         |
| `cublasSsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasDsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasCsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasZsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasChemm`           | ✅          | ❌      | ❓      |                         |
| `cublasZhemm`           | ✅          | ❌      | ❓      |                         |
| `cublasStrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasStrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrmm`           | ✅          | ❌      | ❓      |                         |

cuBLAS handle typedefs changed in CUDA 12.


# cuRAND (-lcurand)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `curandCreateGenerator`                   | ✅          | ✅      | ✅      |                          |
| `curandCreateGeneratorHost`               | ✅          | ✅      | ✅      |                          |
| `curandSetPseudoRandomGeneratorSeed`      | ✅          | ✅      | ✅      |                          |
| `curandSetQuasiRandomGeneratorDimensions` | ✅          | ✅      | ✅      |            *             |
| `curandGenerate`                          | ✅          | ✅      | ✅      |            *             |
| `curandGenerateUniform`                   | ✅          | ✅      | ✅      |            *             |
| `curandGenerateNormal`                    | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLogNormal`                 | ✅          | ✅      | ✅      |            *             |
| `curandGeneratePoisson`                   | ✅          | ✅      | ✅      |            *             |
| `curandGenerateUniformDouble`             | ✅          | ✅      | ✅      |            *             |
| `curandGenerateNormalDouble`              | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLogNormalDouble`           | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLongLong`                  | ✅          | ✅      | ✅      |            *             |
| `curandGeneratePoisson`                   | ✅          | ✅      | ✅      |            *             |
| `curandDestroyGenerator`                  | ✅          | ✅      | ✅      |                          |

*This function can generate numbers using either a CPU or a GPU generator, created using `curandCreateGenerator` or `curandCreateGeneratorHost`, respectively. **Both CPU and GPU generations are tested and working**.


# cuFFT (-lcufft)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cufftCreate`                             | ✅          | ✅      | ✅      |                          |
| `cufftDestroy`                            | ✅          | ✅      | ✅      |                          |
| `cufftPlan1D`                             | ✅          | ✅      | ✅      |                          |
| `cufftPlan2D`                             | ✅          | ✅      | ✅      |                          |
| `cufftPlan3D`                             | ✅          | ✅      | ✅      |                          |
| `cufftEstimate1D`                         | ✅          | ✅      | ✅      |                          |
| `cufftEstimate2D`                         | ✅          | ✅      | ✅      |                          |
| `cufftEstimate3D`                         | ✅          | ✅      | ✅      |                          |
| `cuFFTEstimateMany`                       | ✅          | ✅      | ✅      |                          |
| `cufftExecC2C`                            | ✅          | ✅      | ✅      |                          |
| `ExecR2C`                                 | ✅          | ✅      | ✅      |                          |
| `ExecC2R`                                 | ✅          | ✅      | ✅      |                          |
| `ExecZ2Z`                                 | ✅          | ✅      | ✅      |                          |
| `ExecD2Z`                                 | ✅          | ✅      | ✅      |                          |
| `ExecZ2D`                                 | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan1D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan2D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan3D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlanMany`                       | ✅          | ✅      | ✅      |                          |
| `cufftMakePlanMany64`                     | ✅          | ✅      | ✅      |                          |
| `cufftGetSize1D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSize2D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSize3D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSizeMany`                        | ✅          | ✅      | ✅      |                          |
| `cufftGetSizeMany64`                      | ✅          | ✅      | ✅      |                          |
| `cufftGetSize`                            | ✅          | ✅      | ✅      |                          |
| `cufftSetWorkArea`                        | ✅          | ✅      | ✅      |                          |
| `cufftSetAutoAllocation`                  | ✅          | ✅      | ✅      |                          |
| `cufftGetVersion`                         | ✅          | ✅      | ✅      |                          |
| `cufftSetStream`                          | ✅          | ✅      | ✅      |                          |
| `cufftXtMalloc`                           | ✅          | ✅      | ✅      |                          |
| `cufftXtFree`                             | ✅          | ✅      | ✅      |                          |            
| `cufftXtMemcpy`                           | ✅          | ✅      | ❌      |                          |  
| `cufftXtSetGpus`                          | ✅          | ✅      | ✅      |                          |
| `cufftXtExecDescriptorC2C`                | ✅          | ✅      | ❌      |                          |
| `cufftXtMakePlanMany`                     | ✅          | ✅      | ❌      | Not Supported by GVirtuS |

cuFFT handle typedefs changed in CUDA 12.

# cudnn (-lcudnn)

| Function                                                   | Implemented | Tested  | Working |          Notes           |
| ---------------------------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cudnnCreate`                                              | ✅          | ✅      | ✅      |                          | 
| `cudnnDestroy`                                             | ✅          | ✅      | ✅      |                          | 
| `cudnnGetVersion`                                          | ✅          | ✅      | ✅      |                          | 
| `cudnnGetErrorString`                                      | ✅          | ✅      | ✅      |                          | 
| `cudnnSetStream`                                           | ✅          | ✅      | ✅      |                          | 
| `cudnnGetStream`                                           | ✅          | ✅      | ✅      |                          |  
| `cudnnCreateTensorDescriptor`                              | ✅          | ✅      | ✅      |                          | 
| `cudnnSetTensor4dDescriptor`                               | ✅          | ✅      | ✅      |                          | 
| `cudnnSetTensor4dDescriptorEx`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnGetTensor4dDescriptor`                               | ✅          | ✅      | ✅      |                          | 
| `cudnnSetTensorNdDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cudnnSetTensorNdDescriptorEx`                             | ✅          | ❌      | ❓      |                          |
| `cudnnGetTensorNdDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cudnnGetTensorSizeInBytes`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyTensorDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cudnnInitTransformDest`                                   | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnCreateTensorTransformDescriptor`                     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnSetTensorTransformDescriptor`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnGetTensorTransformDescriptor`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnDestroyTensorTransformDescriptor`                    | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnTransformTensor`                                     | ✅          | ✅      | ✅      | float and double both working, Deprecated as of v9      | 
| `cudnnTransformTensorEx`                                   | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnGetFoldedConvBackwardDataDescriptors`                | ✅          | ❌      | ❓      |                          | 
| `cudnnAddTensor`                                           | ✅          | ✅      | ✅      | float and double both working, Deprecated as of v9      | 
| `cudnnCreateOpTensorDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnSetOpTensorDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cudnnGetOpTensorDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyOpTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnOpTensor`                                            | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnCreateReduceTensorDescriptor`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnSetReduceTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnGetReduceTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyReduceTensorDescriptor`                       | ✅          | ❌      | ❓      |                          | 
| `cudnnGetReductionIndicesSize`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnGetReductionWorkspaceSize`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnReduceTensor`                                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnSetTensor`                                           | ✅          | ❌      | ❓      |                          | 
| `cudnnScaleTensor`                                         | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnCreateFilterDescriptor`                              | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnSetFilter4dDescriptor`                               | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnGetFilter4dDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnSetFilter4dDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFilter4dDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnSetFilter4dDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFilter4dDescriptor_v4`                            | ✅          | ❌      | ❓      |                          |
| `cudnnSetFilterNdDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnGetFilterNdDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnSetFilterNdDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFilterNdDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnSetFilterNdDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFilterNdDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFilterSizeInBytes`                                | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnDestroyFilterDescriptor`                             | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnTransformFilter`                                     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnReorderFilterAndBias`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateConvolutionDescriptor`                         | ✅          | ✅      | ✅      |                          | 
| `cudnnSetConvolutionMathType`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionMathType`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnSetConvolutionGroupCount`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionGroupCount`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnSetConvolutionReorderType`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionReorderType`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnSetConvolution2dDescriptor`                          | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolution2dDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolution2dForwardOutputDim`                    | ✅          | ✅      | ✅      |                          | 
| `cudnnSetConvolutionNdDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionNdDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionNdForwardOutputDim`                    | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyConvolutionDescriptor`                        | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolutionForwardAlgorithmMaxCount`              | ✅          | ❌      | ❓      |                          | 
| `cudnnFindConvolutionForwardAlgorithm`                     | ✅          | ✅      | ✅      |                          | 
| `cudnnFindConvolutionForwardAlgorithmEx`                   | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolutionForwardAlgorithm`                      | ✅          | ❌      | ❓      | Deprecated in v8, Use `cudnnGetConvolutionForwardAlgorithm_v7` instead | 
| `cudnnGetConvolutionForwardAlgorithm_v7`                   | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolutionForwardWorkspaceSize`                  | ✅          | ✅      | ✅      |                          | 
| `cudnnConvolutionForward`                                  | ✅          | ✅      | ✅      |                          | 
| `cudnnConvolutionBiasActivationForward`                    | ✅          | ❌      | ❓      | Deprecated in v9         | 
| `cudnnConvolutionBackwardBias`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionBackwardFilterAlgorithmMaxCount`       | ✅          | ❌      | ❓      |                          | 
| `cudnnFindConvolutionBackwardFilterAlgorithm`              | ✅          | ❌      | ❓      | Deprecated in v9         | 
| `cudnnFindConvolutionBackwardFilterAlgorithmEx`            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionBackwardFilterAlgorithm`               | ✅          | ❌      | ❓      | Deprecated in v8, Use `cudnnGetConvolutionBackwardFilterAlgorithm_v7` instead | 
| `cudnnGetConvolutionBackwardFilterAlgorithm_v7`            | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolutionBackwardFilterWorkspaceSize`           | ✅          | ✅      | ✅      |                          | 
| `cudnnConvolutionBackwardFilter`                           | ✅          | ✅      | ✅      |                          | 
| `cudnnGetConvolutionBackwardDataAlgorithmMaxCount`         | ✅          | ❌      | ❓      |                          | 
| `cudnnFindConvolutionBackwardDataAlgorithm`                | ✅          | ❌      | ❓      |                          | 
| `cudnnFindConvolutionBackwardDataAlgorithmEx`              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionBackwardDataAlgorithm`                 | ✅          | ❌      | ❓      | Deprecated in v8, Use `cudnnGetConvolutionBackwardDataAlgorithm_v7` instead | 
| `cudnnGetConvolutionBackwardDataAlgorithm_v7`              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetConvolutionBackwardDataWorkspaceSize`             | ✅          | ✅      | ✅      |                          | 
| `cudnnConvolutionBackwardData`                             | ✅          | ✅      | ✅      |                          | 
| `cudnnIm2Col`                                              | ✅          | ❌      | ❓      |                          | 
| `cudnnSoftmaxForward`                                      | ✅          | ❌      | ❓      |                          | 
| `cudnnSoftmaxBackward`                                     | ✅          | ✅      | ✅      |                          | 
| `cudnnCreatePoolingDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnSetPooling2dDescriptor`                              | ✅          | ✅      | ✅      |                          | 
| `cudnnGetPooling2dDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnSetPoolingNdDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetPoolingNdDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetPoolingNdForwardOutputDim`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnGetPooling2dForwardOutputDim`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyPoolingDescriptor`                            | ✅          | ✅      | ✅      |                          | 
| `cudnnPoolingForward`                                      | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnPoolingBackward`                                     | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnCreateActivationDescriptor`                          | ✅          | ✅      | ✅      |                          | 
| `cudnnSetActivationDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cudnnGetActivationDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyActivationDescriptor`                         | ✅          | ✅      | ✅      |                          | 
| `cudnnActivationForward`                                   | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnActivationBackward`                                  | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnCreateLRNDescriptor`                                 | ✅          | ✅      | ✅      |                          | 
| `cudnnSetLRNDescriptor`                                    | ✅          | ✅      | ✅      |                          | 
| `cudnnGetLRNDescriptor`                                    | ✅          | ✅      | ✅      |                          | 
| `cudnnDestroyLRNDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cudnnLRNCrossChannelForward`                              | ✅          | ✅      | ✅      | float and double both working | 
| `cudnnLRNCrossChannelBackward`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnDivisiveNormalizationForward`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnDivisiveNormalizationBackward`                       | ✅          | ❌      | ❓      |                          | 
| `cudnnDeriveBNTensorDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetBatchNormalizationForwardTrainingExWorkspaceSize` | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnGetBatchNormalizationBackwardExWorkspaceSize`        | ✅          | ❌      | ❓      |                          | 
| `cudnnGetBatchNormalizationTrainingExReserveSpaceSize`     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnBatchNormalizationForwardTraining`                   | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cudnnBatchNormalizationForwardTrainingEx`                 | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnBatchNormalizationForwardInference`                  | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnBatchNormalizationBackward`                          | ✅          | ✅      | ❓      | Deprecated as of v9      | 
| `cudnnBatchNormalizationBackwardEx`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cudnnCreateSpatialTransformerDescriptor`                  | ✅          | ❌      | ❓      |                          | 
| `cudnnSetSpatialTransformerNdDescriptor`                   | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroySpatialTransformerDescriptor`                 | ✅          | ❌      | ❓      |                          | 
| `cudnnSpatialTfGridGeneratorForward`                       | ✅          | ❌      | ❓      |                          | 
| `cudnnSpatialTfGridGeneratorBackward`                      | ✅          | ❌      | ❓      |                          | 
| `cudnnSpatialTfSamplerForward`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnSpatialTfSamplerBackward`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateDropoutDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cudnnDestroyDropoutDescriptor`                            | ✅          | ✅      | ✅      |                          | 
| `cudnnDropoutGetStatesSize`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnDropoutGetReserveSpaceSize`                          | ✅          | ❌      | ❓      |                          | 
| `cudnnSetDropoutDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cudnnRestoreDropoutDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnGetDropoutDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cudnnDropoutForward`                                      | ✅          | ❌      | ❓      |                          | 
| `cudnnDropoutBackward`                                     | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateRNNDescriptor`                                 | ✅          | ✅      | ✅      |                          | 
| `cudnnDestroyRNNDescriptor`                                | ✅          | ✅      | ✅      |                          |
| `cudnnRNNForward`                                          | ✅          | ✅      | ✅      |                          | 
| `cudnnSetRNNDescriptor_v5`                                 | ✅          | ❌      | ❓      |                          | 
| `cudnnGetRNNDescriptor_v5`                                 | ❌          | ❌      | ❌      |                          | 
| `cudnnSetRNNDescriptor_v6`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNBackwardData_v8` instead | 
| `cudnnGetRNNDescriptor_v6`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNDescriptor_v8` instead | 
| `cudnnSetRNNDescriptor_v8`                                 | ✅          | ❌      | ❓      |                          | 
| `cudnnGetRNNDescriptor_v8`                                 | ✅          | ❌      | ❓      |                          | 
| `cudnnSetRNNMatrixMathType`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnSetRNNDescriptor_v8` instead | 
| `cudnnGetRNNMatrixMathType`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnSetRNNBiasMode`                                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnSetRNNDescriptor_v8` instead | 
| `cudnnGetRNNBiasMode`                                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNDescriptor_v8` instead | 
| `cudnnRNNSetClip`                                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNSetClip_v9` instead | 
| `cudnnRNNGetClip`                                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNGetClip_v9` instead | 
| `cudnnSetRNNProjectionLayers`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnSetRNNDescriptor_v8` instead | 
| `cudnnGetRNNProjectionLayers`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNDescriptor_v8` instead | 
| `cudnnCreatePersistentRNNPlan`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cudnnDestroyPersistentRNNPlan`                            | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cudnnSetPersistentRNNPlan`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cudnnGetRNNWorkspaceSize`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNTempSpaceSizes` instead | 
| `cudnnGetRNNTrainingReserveSize`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNTempSpaceSizes` instead | 
| `cudnnGetRNNParamsSize`                                    | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNWeightSpaceSize` instead | 
| `cudnnGetRNNLinLayerMatrixParams`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNWeightParams` instead | 
| `cudnnGetRNNLinLayerBiasParams`                            | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNWeightParams` instead | 
| `cudnnRNNForwardInference`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cudnnRNNForwardTraining`                                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cudnnRNNBackwardData`                                     | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNBackwardData_v8` instead | 
| `cudnnRNNBackwardData_v8`                                  | ❌          | ❌      | ❌      |                          |
| `cudnnRNNBackwardWeights`                                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSetRNNPaddingMode`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNBackwardData_v8` instead | 
| `cudnnGetRNNPaddingMode`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNDescriptor_v8` instead | 
| `cudnnCreateRNNDataDescriptor`                             | ✅          | ✅      | ✅      |                          |
| `cudnnDestroyRNNDataDescriptor`                            | ✅          | ✅      | ✅      |                          |
| `cudnnSetRNNDataDescriptor`                                | ✅          | ✅      | ✅      |                          |
| `cudnnGetRNNDataDescriptor`                                | ✅          | ✅      | ✅      |                          |
| `cudnnGetRNNTempSpaceSizes`                                | ✅          | ✅      | ✅      |                          |
| `cudnnGetRNNWeightSpaceSize`                               | ✅          | ✅      | ✅      |                          |
| `cudnnRNNForwardTrainingEx`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cudnnRNNForwardInferenceEx`                               | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cudnnRNNBackwardDataEx`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNBackwardData_v8` instead | 
| `cudnnRNNBackwardWeightsEx`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSetRNNAlgorithmDescriptor`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetRNNForwardInferenceAlgorithmMaxCount`             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnFindRNNForwardInferenceAlgorithmEx`                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetRNNForwardTrainingAlgorithmMaxCount`              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnFindRNNForwardTrainingAlgorithmEx`                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetRNNBackwardDataAlgorithmMaxCount`                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnFindRNNBackwardDataAlgorithmEx`                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetRNNBackwardWeightsAlgorithmMaxCount`              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnFindRNNBackwardWeightsAlgorithmEx`                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnCreateSeqDataDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroySeqDataDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnSetSeqDataDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnGetSeqDataDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateAttnDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyAttnDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cudnnSetAttnDescriptor`                                   | ✅          | ❌      | ❓      |                          | 
| `cudnnGetAttnDescriptor`                                   | ✅          | ❌      | ❓      |                          | 
| `cudnnGetMultiHeadAttnBuffers`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnGetMultiHeadAttnWeights`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnMultiHeadAttnForward`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnMultiHeadAttnBackwardData`                           | ✅          | ❌      | ❓      |                          | 
| `cudnnMultiHeadAttnBackwardWeights`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateCTCLossDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnSetCTCLossDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnSetCTCLossDescriptorEx`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnGetCTCLossDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cudnnGetCTCLossDescriptorEx`                              | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyCTCLossDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cudnnCTCLoss`                                             | ✅          | ❌      | ❓      |                          | 
| `cudnnGetCTCLossWorkspaceSize`                             | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateAlgorithmDescriptor`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSetAlgorithmDescriptor`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetAlgorithmDescriptor`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnCopyAlgorithmDescriptor`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnDestroyAlgorithmDescriptor`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnCreateAlgorithmPerformance`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSetAlgorithmPerformance`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetAlgorithmPerformance`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnDestroyAlgorithmPerformance`                         | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnGetAlgorithmSpaceSize`                               | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSaveAlgorithm`                                       | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnRestoreAlgorithm`                                    | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cudnnSetCallback`                                         | ✅          | ❌      | ❓      |                          | 
| `cudnnGetCallback`                                         | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateFusedOpsConstParamPack`                        | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyFusedOpsConstParamPack`                       | ✅          | ❌      | ❓      |                          | 
| `cudnnSetFusedOpsConstParamPackAttribute`                  | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFusedOpsConstParamPackAttribute`                  | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateFusedOpsVariantParamPack`                      | ✅          | ❌      | ❓      |                          | 
| `cudnnDestroyFusedOpsVariantParamPack`                     | ✅          | ❌      | ❓      |                          | 
| `cudnnSetFusedOpsVariantParamPackAttribute`                | ✅          | ❌      | ❓      |                          | 
| `cudnnGetFusedOpsVariantParamPackAttribute`                | ✅          | ❌      | ❓      |                          | 
| `cudnnCreateFusedOpsPlan`                                  | ✅          | ✅      | ✅      |                          | 
| `cudnnDestroyFusedOpsPlan`                                 | ✅          | ✅      | ✅      |                          | 
| `cudnnMakeFusedOpsPlan`                                    | ✅          | ❌      | ❓      |                          | 
| `cudnnFusedOpsExecute`                                     | ✅          | ❌      | ❓      |                          | 


# cuSPARSE (-lcusparse)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cusparseCreate`                          | ✅          | ✅      | ✅      |                          | 
| `cusparseDestroy`                         | ✅          | ✅      | ✅      |                          | 
| `cusparseGetVersion`                      | ✅          | ✅      | ✅      |                          | 
| `cusparseGetErrorString`                  | ✅          | ✅      | ✅      |                          | 
| `cusparseSetStream`                       | ✅          | ✅      | ✅      |                          | 
| `cusparseGetStream`                       | ✅          | ✅      | ✅      |                          | 
| `cusparseXcsrgemm`                        | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsr2dense`                      | ❌          | ❌      | ❌      |                          | 
| `cusparseXdense2csr`                      | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv`                          | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv_analysis`                 | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv_solve`                    | ❌          | ❌      | ❌      |                          | 


# cuSOLVER (-lcusolver)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cusolverDnCreate`                        | ✅          | ✅      | ✅       |                          |       
| `cusolverDnDestroy`                       | ✅          | ✅      | ✅       |                          | 
| `cusolverDnSetStream`                     | ✅          | ✅      | ✅       |                          | 
| `cusolverDnGetStream`                     | ✅          | ✅      | ✅       |                          |
| `cusolverDnSgetrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDgetrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSgetrs`                        | ❌          | ❌      | ❌       |                          |     
| `cusolverDnDgetrs`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSgesvd`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDgesvd`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSpotrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDpotrf`                        | ❌          | ❌      | ❌       |                          |

# cudaDr (-lcuda)

| Function                          | Implemented | Tested  | Working |        Notes             |
| --------------------------------- | ----------- | ------- | ------- | ------------------------ |
| `cuInit`                          | ✅          | ❌      | ❓      |                          |
| `cuCtxCreate`                     | ✅          | ❌      | ❓      |                          |
| `cuCtxAttach`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuCtxDestroy`                    | ✅          | ❌      | ❓      |                          |
| `cuCtxDetach`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuCtxSetCurrent`                 | ❌          | ❌      | ❌      |                          |
| `cuCtxGetCurrent`                 | ❌          | ❌      | ❌      |                          |
| `cuCtxGetDevice`                  | ✅          | ❌      | ❓      |                          |
| `cuCtxPopCurrent`                 | ✅          | ❌      | ❓      |                          |
| `cuCtxPushCurrent`                | ✅          | ❌      | ❓      |                          |
| `cuCtxSynchronize`                | ✅          | ❌      | ❓      |                          |
| `cuCtxDisablePeerAccess`          | ✅          | ❌      | ❓      |                          |
| `cuCtxEnablePeerAccess`           | ✅          | ❌      | ❓      |                          |
| `cuDeviceCanAccessPeer`           | ✅          | ❌      | ❓      |                          |
| `cuDeviceComputeCapability`       | ✅          | ❌      | ❓      | Deprecated               |
| `cuDeviceGet`                     | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetAttribute`            | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetCount`                | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetName`                 | ✅          | ❌      | ❓      |                          |
| `cuDeviceGetProperties`           | ✅          | ❌      | ❓      | Deprecated               |
| `cuDeviceTotalMem`                | ✅          | ❌      | ❓      |                          |
| `cuParamSetSize`                  | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncSetBlockShape`             | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchGrid`                    | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncGetAttribute`              | ✅          | ❌      | ❓      |                          |
| `cuFuncSetSharedSize`             | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunch`                        | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetf`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSeti`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetv`                     | ✅          | ❌      | ❓      | Deprecated               |
| `cuParamSetTexRef`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchGridAsync`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuFuncSetCacheConfig`            | ✅          | ❌      | ❓      |                          |
| `cuMemFree`                       | ✅          | ❌      | ❓      |                          |
| `cuMemAlloc`                      | ✅          | ❌      | ❓      |                          |
| `cuMemAllocManaged`               | ❌          | ❌      | ❌      |                          |
| `cuMemHostAlloc`                  | ❌          | ❌      | ❌      |                          |
| `cuMemHostFree`                   | ❌          | ❌      | ❌      |                          |
| `cuMemcpyDtoH`                    | ✅          | ❌      | ❓      |                          |
| `cuMemcpyHtoD`                    | ✅          | ❌      | ❓      |                          |
| `cuMemcpyDtoD`                    | ❌          | ❌      | ❌      |                          |
| `cuMemcpyHtoDAsync`               | ❌          | ❌      | ❌      |                          |
| `cuMemcpyDtoHAsync`               | ❌          | ❌      | ❌      |                          |
| `cuMemsetD32`                     | ❌          | ❌      | ❌      |                          |
| `cuMemsetD8`                      | ❌          | ❌      | ❌      |                          |
| `cuArrayCreate`                   | ✅          | ❌      | ❓      |                          |
| `cuMemcpy2D`                      | ✅          | ❌      | ❓      |                          |
| `cuArrayDestroy`                  | ✅          | ❌      | ❓      |                          |
| `cuArray3DCreate`                 | ✅          | ❌      | ❓      |                          |
| `cuMemAllocPitch`                 | ✅          | ❌      | ❓      |                          |
| `cuMemGetAddressRange`            | ✅          | ❌      | ❓      |                          |
| `cuMemGetInfo`                    | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadData`                | ✅          | ❌      | ❓      |                          |
| `cuModuleLoad`                    | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadFatBinary`           | ✅          | ❌      | ❓      |                          |
| `cuModuleUnload`                  | ✅          | ❌      | ❓      |                          |
| `cuModuleGetFunction`             | ✅          | ❌      | ❓      |                          |
| `cuModuleGetGlobal`               | ✅          | ❌      | ❓      |                          |
| `cuModuleLoadDataEx`              | ✅          | ❌      | ❓      |                          |
| `cuModuleGetTexRef`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuDriverGetVersion`              | ✅          | ❌      | ❓      |                          |
| `cuStreamCreate`                  | ✅          | ❌      | ❓      |                          |
| `cuStreamDestroy`                 | ✅          | ❌      | ❓      |                          |
| `cuStreamQuery`                   | ✅          | ❌      | ❓      |                          |
| `cuStreamSynchronize`             | ✅          | ❌      | ❓      |                          |
| `cuEventCreate`                   | ✅          | ❌      | ❓      |                          |
| `cuEventDestroy`                  | ✅          | ❌      | ❓      |                          |
| `cuEventElapsedTime`              | ✅          | ❌      | ❓      |                          |
| `cuEventQuery`                    | ✅          | ❌      | ❓      |                          |
| `cuEventRecord`                   | ✅          | ❌      | ❓      |                          |
| `cuEventSynchronize`              | ✅          | ❌      | ❓      |                          |
| `cuLinkCreate`                    | ❌          | ❌      | ❌      |                          |
| `cuLinkAddData`                   | ❌          | ❌      | ❌      |                          |
| `cuLinkComplete`                  | ❌          | ❌      | ❌      |                          |
| `cuModuleLoadDataEx`              | ❌          | ❌      | ❌      |                          |
| `cuGraphicsGLRegisterBuffer`      | ❌          | ❌      | ❌      |                          |
| `cuGraphicsMapResources`          | ❌          | ❌      | ❌      |                          |
| `cuTexRefSetArray`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetAddressMode`          | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFilterMode`           | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFlags`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetFormat`               | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetAddress`              | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetArray`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefGetFlags`                | ✅          | ❌      | ❓      | Deprecated               |
| `cuTexRefSetAddress`              | ✅          | ❌      | ❓      | Deprecated               |
| `cuLaunchKernel`                  | ✅          | ❌      | ❓      |                          |

# cudaRT (-lcudart)

| Function                                                 | Implemented | Tested | Working  |          Notes          |
| -------------------------------------------------------- | ----------- | ------ | -------- | ----------------------- |
| `cudaMalloc`                                             | ✅          | ✅      | ✅      |                         |
| `cudaFree`                                               | ✅          | ✅      | ✅      |                         |
| `cudaMallocHost`                                         | ❌          | ❌      | ❌      |                         |
| `cudaFreeHost`                                           | ❌          | ❌      | ❌      |                         |
| `cudaMemcpy`                                             | ✅          | ✅      | ✅      |                         |
| `cudaMemcpyAsync`                                        | ✅          | ✅      | ✅      |                         |
| `cudaMemset`                                             | ✅          | ✅      | ✅      |                         |
| `cudaMemsetAsync`                                        | ✅          | ✅      | ✅      |                         |
| `cudaGetDevice`                                          | ✅          | ✅      | ✅      |                         |
| `cudaSetDevice`                                          | ✅          | ✅      | ✅      |                         |
| `cudaStreamCreate`                                       | ✅          | ✅      | ✅      |                         |
| `cudaStreamQuery`                                        | ✅          | ❌      | ❓      |                         |
| `cudaStreamSynchronize`                                  | ✅          | ❌      | ❓      |                         |
| `cudaStreamCreateWithFlags`                              | ✅          | ❌      | ❓      |                         |
| `cudaStreamWaitEvent`                                    | ✅          | ❌      | ❓      |                         |
| `cudaStreamCreateWithPriority`                           | ✅          | ❌      | ❓      |                         |
| `cudaStreamDestroy`                                      | ✅          | ✅      | ✅      |                         |
| `cudaEventCreate`                                        | ✅          | ✅      | ✅      |                         |
| `cudaEventCreateWithFlags`                               | ✅          | ❌      | ❓      |                         |
| `cudaEventQuery`                                         | ✅          | ❌      | ❓      |                         |
| `cudaEventRecord`                                        | ✅          | ✅      | ✅      |                         |
| `cudaEventSynchronize`                                   | ✅          | ✅      | ✅      |                         |
| `cudaEventElapsedTime`                                   | ✅          | ✅      | ✅      |                         |
| `cudaEventDestroy`                                       | ✅          | ✅      | ✅      |                         |
| `cudaChooseDevice`                                       | ✅          | ❌      | ❓      |                         |
| `cudaGetDeviceCount`                                     | ✅          | ❌      | ❓      |                         |
| `cudaGetDeviceProperties`                                | ✅          | ❌      | ❓      |                         |
| `cudaSetDeviceFlags`                                     | ✅          | ❌      | ❓      |                         |
| `cudaSetValidDevices`                                    | ✅          | ❌      | ❓      |                         |
| `cudaDeviceReset`                                        | ✅          | ❌      | ❓      |                         |
| `cudaDeviceSynchronize`                                  | ✅          | ✅      | ✅      |                         |
| `cudaDeviceSetCacheConfig`                               | ✅          | ❌      | ❓      |                         |
| `cudaDeviceSetLimit`                                     | ✅          | ❌      | ❓      |                         |
| `cudaDeviceCanAccessPeer`                                | ✅          | ❌      | ❓      |                         |
| `cudaDeviceEnablePeerAccess`                             | ✅          | ❌      | ❓      |                         |
| `cudaDeviceDisablePeerAccess`                            | ✅          | ❌      | ❓      |                         |
| `cudaIpcGetMemHandle`                                    | ✅          | ❌      | ❓      |                         |
| `cudaIpcGetEventHandle`                                  | ✅          | ❌      | ❓      |                         |
| `cudaIpcOpenEventHandle`                                 | ✅          | ❌      | ❓      |                         |
| `cudaIpcOpenMemHandle`                                   | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessor`          | ✅          | ❌      | ❓      |                         |
| `cudaDeviceGetAttribute`                                 | ✅          | ❌      | ❓      |                         |
| `cudaDeviceGetStreamPriorityRange`                       | ✅          | ❌      | ❓      |                         |
| `cudaGetErrorString`                                     | ✅          | ❌      | ❓      |                         |
| `cudaGetLastError`                                       | ✅          | ❌      | ❓      |                         |
| `cudaPeekAtLastError`                                    | ✅          | ❌      | ❓      |                         |
| `cudaFuncGetAttributes`                                  | ✅          | ❌      | ❓      |                         |
| `cudaFuncSetCacheConfig`                                 | ✅          | ❌      | ❓      |                         |
| `cudaLaunchKernel`                                       | ✅          | ✅      | ✅      | Tested using both `<<<>>>` and direct syntax |
| `__cudaPushCallConfiguration`                            | ✅          | ✅      | ✅      | Tested implicitly using `<<<>>>` syntax |
| `__cudaPopCallConfiguration`                             | ✅          | ✅      | ✅      | Tested implicitly using `<<<>>>` syntax |
| `cudaLaunch`                                             | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0 |
| `cudaConfigureCall`                                      | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0 |
| `cudaSetupArgument`                                      | ✅          | ❌      | ❓      | This function is deprecated as of CUDA 7.0  |
| `cudaRegisterFatBinary`                                  | ✅          | ✅      | ✅      | Automatically called at program start |
| `cudaRegisterFatBinaryEnd`                               | ✅          | ✅      | ✅      | Automatically called after `cudaRegisterFatBinary` |
| `cudaUnregisterFatBinary`                                | ✅          | ✅      | ✅      | Automatically called at program exit |
| `cudaSetDoubleForHost`                                   | ✅          | ❌      | ❓      |                         |
| `cudaSetDoubleForDevice`                                 | ✅          | ❌      | ❓      |                         |
| `cudaRegisterFunction`                                   | ✅          | ❌      | ❓      |                         |
| `cudaRegisterVar`                                        | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSharedVar`                                  | ✅          | ❌      | ❓      |                         |
| `cudaRegisterShared`                                     | ✅          | ❌      | ❓      |                         |
| `cudaRegisterTexture`                                    | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSurface`                                    | ✅          | ❌      | ❓      |                         |
| `cudaRegisterSharedMemory`                               | ✅          | ❌      | ❓      |                         |
| `cudaRequestSharedMemory`                                | ✅          | ❌      | ❓      |                         |
| `cudaFreeArray`                                          | ✅          | ❌      | ❓      |                         |
| `cudaGetSymbolAddress`                                   | ✅          | ❌      | ❓      |                         |
| `cudaGetSymbolSize`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMallocArray`                                        | ✅          | ❌      | ❓      |                         |
| `cudaMallocPitch`                                        | ✅          | ❌      | ❓      |                         |
| `cudaMallocManaged`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy2D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy3D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyFromSymbol`                                   | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyToArray`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpyToSymbol`                                     | ✅          | ❌      | ❓      |                         |
| `cudaMemset2D`                                           | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyFromArray`                                    | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpyArrayToArray`                                 | ✅          | ❌      | ❓      | Deprecated              |
| `cudaMemcpy2DFromArray`                                  | ✅          | ❌      | ❓      |                         |
| `cudaMemcpy2DToArray`                                    | ✅          | ❌      | ❓      |                         |
| `cudaMalloc3DArray`                                      | ✅          | ❌      | ❓      |                         |
| `cudaMemcpyPeerAsync`                                    | ✅          | ❌      | ❓      |                         |
| `cudaGLSetGLDevice`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaGraphicsGLRegisterBuffer`                           | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsMapResources`                               | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsResourceGetMappedPointer`                   | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsUnmapResources`                             | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsUnregisterResource`                         | ✅          | ❌      | ❓      |                         |
| `cudaGraphicsResourceSetMapFlags`                        | ✅          | ❌      | ❓      |                         |
| `cudaBindTexture`                                        | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindTexture2D`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindTextureToArray`                                 | ✅          | ❌      | ❓      | Deprecated              |
| `cudaCreateTextureObject`                                | ✅          | ❌      | ❓      |                         |
| `cudaGetChannelDesc`                                     | ✅          | ❌      | ❓      |                         |
| `cudaGetTextureAlignmentOffset`                          | ✅          | ❌      | ❓      | Deprecated              |
| `cudaGetTextureReference`                                | ✅          | ❌      | ❓      | Deprecated              |
| `cudaUnbindTexture`                                      | ✅          | ❌      | ❓      | Deprecated              |
| `cudaBindSurfaceToArray`                                 | ✅          | ❌      | ❓      |                         |
| `cudaGetTextureReference`                                | ✅          | ❌      | ❓      |                         |
| `cudaThreadExit`                                         | ✅          | ❌      | ❓      | Deprecated in favor of `cudaDeviceReset` |
| `cudaThreadSynchronize`                                  | ✅          | ❌      | ❓      | Deprecated in favor of `cudaDeviceSynchronize` |
| `cudaDriverGetVersion`                                   | ✅          | ❌      | ❓      |                         |
| `cudaRuntimeGetVersion`                                  | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessor`          | ✅          | ❌      | ❓      |                         |
| `cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags` | ✅          | ❌      | ❓      |                         |


# cuBLAS (-lcublas)

| Function                | Implemented | Tested | Working  |          Notes          |
| ----------------------- | ----------- | ------ | -------- | ------------------------|
| `cublasCreate`          | ✅          | ✅      | ✅      |                         |
| `cublasDestroy`         | ✅          | ✅      | ✅      |                         |
| `cublasGetVersion`      | ✅          | ✅      | ✅      |                         |
| `cublasSetStream`       | ✅          | ✅      | ❌      |     broke in CUDA 12    |
| `cublasSetVector`       | ✅          | ❌      | ❓      |                         |
| `cublasGetVector`       | ✅          | ❌      | ❓      |                         |
| `cublasSetMatrix`       | ✅          | ❌      | ❓      |                         |
| `cublasGetMatrix`       | ✅          | ❌      | ❓      |                         |
| `cublasGetPointerMode`  | ✅          | ❌      | ❓      |                         |
| `cublasSetPointerMode`  | ✅          | ❌      | ❓      |                         |
| `cublasSaxpy`           | ✅          | ✅      | ✅      |                         |
| `cublasDaxpy`           | ✅          | ✅      | ❌      |     broke in CUDA 12    |
| `cublasCaxpy`           | ✅          | ❌      | ❓      |                         |
| `cublasZaxpy`           | ✅          | ❌      | ❓      |                         |
| `cublasScopy`           | ✅          | ✅      | ✅      |                         |
| `cublasDcopy`           | ✅          | ✅      | ✅      |                         |
| `cublasCcopy`           | ✅          | ❌      | ❓      |                         |
| `cublasZcopy`           | ✅          | ❌      | ❓      |                         |
| `cublasSnrm2`           | ✅          | ✅      | ❌      |     broke in CUDA 12    |
| `cublasDnrm2`           | ✅          | ✅      | ❌      |     broke in CUDA 12    |
| `cublasSgemm`           | ✅          | ✅      | ❌      |                         |
| `cublasDgemm`           | ✅          | ✅      | ❌      |                         |
| `cublasSgemv`           | ✅          | ✅      | ❌      |                         |
| `cublasDgemv`           | ✅          | ✅      | ❌      |                         |
| `cublasSdot`            | ✅          | ✅      | ❌      |                         |
| `cublasDdot`            | ✅          | ✅      | ❌      |                         |
| `cublasCdotu`           | ✅          | ❌      | ❓      |                         |
| `cublasCdotc`           | ✅          | ❌      | ❓      |                         |
| `cublasZdotu`           | ✅          | ❌      | ❓      |                         |
| `cublasZdotc`           | ✅          | ❌      | ❓      |                         |
| `cublasSscal`           | ✅          | ❌      | ❓      |                         |
| `cublasDscal`           | ✅          | ❌      | ❓      |                         |
| `cublasCscal`           | ✅          | ❌      | ❓      |                         |
| `cublasCsscal`          | ✅          | ❌      | ❓      |                         |
| `cublasZscal`           | ✅          | ❌      | ❓      |                         |
| `cublasZdscal`          | ✅          | ❌      | ❓      |                         |
| `cublasSswap`           | ✅          | ❌      | ❓      |                         |
| `cublasDswap`           | ✅          | ❌      | ❓      |                         |
| `cublasCswap`           | ✅          | ❌      | ❓      |                         |
| `cublasZswap`           | ✅          | ❌      | ❓      |                         |
| `cublasIsamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIdamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIcamax`          | ✅          | ❌      | ❓      |                         |
| `cublasIzamax`          | ✅          | ❌      | ❓      |                         |
| `cublasSasum`           | ✅          | ❌      | ❓      |                         |
| `cublasDasum`           | ✅          | ❌      | ❓      |                         |
| `cublasScasum`          | ✅          | ❌      | ❓      |                         |
| `cublasDzasum`          | ✅          | ❌      | ❓      |                         |
| `cublasSrot`            | ✅          | ❌      | ❓      |                         |
| `cublasDrot`            | ✅          | ❌      | ❓      |                         |
| `cublasCrot`            | ✅          | ❌      | ❓      |                         |
| `cublasCsrot`           | ✅          | ❌      | ❓      |                         |
| `cublasZrot`            | ✅          | ❌      | ❓      |                         |
| `cublasZdrot`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasDrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasCrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasZrotg`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotm`           | ✅          | ❌      | ❓      |                         |
| `cublasDrotm`           | ✅          | ❌      | ❓      |                         |
| `cublasSrotmg`          | ✅          | ❌      | ❓      |                         |
| `cublasDrotmg`          | ✅          | ❌      | ❓      |                         |
| `cublasSgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasDgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasCgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasZgemv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSgbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasStpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtpsv`           | ✅          | ❌      | ❓      |                         |
| `cublasStbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasDtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasCtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasZtbsv`           | ✅          | ❌      | ❓      |                         |
| `cublasSsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasDsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasCsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasZsymv`           | ✅          | ❌      | ❓      |                         |
| `cublasChemv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhemv`           | ✅          | ❌      | ❓      |                         |
| `cublasSsbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDsbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasChbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhbmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSspmv`           | ✅          | ❌      | ❓      |                         |
| `cublasDspmv`           | ✅          | ❌      | ❓      |                         |
| `cublasChpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasZhpmv`           | ✅          | ❌      | ❓      |                         |
| `cublasSger`            | ✅          | ❌      | ❓      |                         |
| `cublasDger`            | ✅          | ❌      | ❓      |                         |
| `cublasCgeru`           | ✅          | ❌      | ❓      |                         |
| `cublasCgerc`           | ✅          | ❌      | ❓      |                         |
| `cublasZgeru`           | ✅          | ❌      | ❓      |                         |
| `cublasZgerc`           | ✅          | ❌      | ❓      |                         |
| `cublasSsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasDsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasCsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasZsyr`            | ✅          | ❌      | ❓      |                         |
| `cublasCher`            | ✅          | ❌      | ❓      |                         |
| `cublasZher`            | ✅          | ❌      | ❓      |                         |
| `cublasSspr`            | ✅          | ❌      | ❓      |                         |
| `cublasDspr`            | ✅          | ❌      | ❓      |                         |
| `cublasChpr`            | ✅          | ❌      | ❓      |                         |
| `cublasZhpr`            | ✅          | ❌      | ❓      |                         |
| `cublasSsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasDsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasCsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasZsyr2`           | ✅          | ❌      | ❓      |                         |
| `cublasCher2`           | ✅          | ❌      | ❓      |                         |
| `cublasZher2`           | ✅          | ❌      | ❓      |                         |
| `cublasSspr2`           | ✅          | ❌      | ❓      |                         |
| `cublasDspr2`           | ✅          | ❌      | ❓      |                         |
| `cublasChpr2`           | ✅          | ❌      | ❓      |                         |
| `cublasZhpr2`           | ✅          | ❌      | ❓      |                         |
| `cublasSgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasDgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasCgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasZgemm`           | ✅          | ❌      | ❓      |                         |
| `cublasSgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasDgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasCgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasZgemmBatched`    | ✅          | ❌      | ❓      |                         |
| `cublasSnrm2`           | ✅          | ❌      | ❓      |                         |
| `cublasDnrm2`           | ✅          | ❌      | ❓      |                         |
| `cublasScnrm2`          | ✅          | ❌      | ❓      |                         |
| `cublasDznrm2`          | ✅          | ❌      | ❓      |                         |
| `cublasSsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasDsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasCsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasZsyrk`           | ✅          | ❌      | ❓      |                         |
| `cublasCherk`           | ✅          | ❌      | ❓      |                         |
| `cublasZherk`           | ✅          | ❌      | ❓      |                         |
| `cublasSsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasDsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasCsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasZsyr2k`          | ✅          | ❌      | ❓      |                         |
| `cublasCher2k`          | ✅          | ❌      | ❓      |                         |
| `cublasZher2k`          | ✅          | ❌      | ❓      |                         |
| `cublasSsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasDsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasCsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasZsymm`           | ✅          | ❌      | ❓      |                         |
| `cublasChemm`           | ✅          | ❌      | ❓      |                         |
| `cublasZhemm`           | ✅          | ❌      | ❓      |                         |
| `cublasStrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrsm`           | ✅          | ❌      | ❓      |                         |
| `cublasStrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasDtrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasCtrmm`           | ✅          | ❌      | ❓      |                         |
| `cublasZtrmm`           | ✅          | ❌      | ❓      |                         |

cuBLAS handle typedefs changed in CUDA 12.


# cuRAND (-lcurand)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `curandCreateGenerator`                   | ✅          | ✅      | ✅      |                          |
| `curandCreateGeneratorHost`               | ✅          | ✅      | ✅      |                          |
| `curandSetPseudoRandomGeneratorSeed`      | ✅          | ✅      | ✅      |                          |
| `curandSetQuasiRandomGeneratorDimensions` | ✅          | ✅      | ✅      |            *             |
| `curandGenerate`                          | ✅          | ✅      | ✅      |            *             |
| `curandGenerateUniform`                   | ✅          | ✅      | ✅      |            *             |
| `curandGenerateNormal`                    | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLogNormal`                 | ✅          | ✅      | ✅      |            *             |
| `curandGeneratePoisson`                   | ✅          | ✅      | ✅      |            *             |
| `curandGenerateUniformDouble`             | ✅          | ✅      | ✅      |            *             |
| `curandGenerateNormalDouble`              | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLogNormalDouble`           | ✅          | ✅      | ✅      |            *             |
| `curandGenerateLongLong`                  | ✅          | ✅      | ✅      |            *             |
| `curandGeneratePoisson`                   | ✅          | ✅      | ✅      |            *             |
| `curandDestroyGenerator`                  | ✅          | ✅      | ✅      |                          |

*This function can generate numbers using either a CPU or a GPU generator, created using `curandCreateGenerator` or `curandCreateGeneratorHost`, respectively. **Both CPU and GPU generations are tested and working**.


# cuFFT (-lcufft)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cufftCreate`                             | ✅          | ✅      | ✅      |                          |
| `cufftDestroy`                            | ✅          | ✅      | ✅      |                          |
| `cufftPlan1D`                             | ✅          | ✅      | ✅      |                          |
| `cufftPlan2D`                             | ✅          | ✅      | ✅      |                          |
| `cufftPlan3D`                             | ✅          | ✅      | ✅      |                          |
| `cufftEstimate1D`                         | ✅          | ✅      | ✅      |                          |
| `cufftEstimate2D`                         | ✅          | ✅      | ✅      |                          |
| `cufftEstimate3D`                         | ✅          | ✅      | ✅      |                          |
| `cuFFTEstimateMany`                       | ✅          | ✅      | ✅      |                          |
| `cufftExecC2C`                            | ✅          | ✅      | ✅      |                          |
| `ExecR2C`                                 | ✅          | ✅      | ✅      |                          |
| `ExecC2R`                                 | ✅          | ✅      | ✅      |                          |
| `ExecZ2Z`                                 | ✅          | ✅      | ✅      |                          |
| `ExecD2Z`                                 | ✅          | ✅      | ✅      |                          |
| `ExecZ2D`                                 | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan1D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan2D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlan3D`                         | ✅          | ✅      | ✅      |                          |
| `cufftMakePlanMany`                       | ✅          | ✅      | ✅      |                          |
| `cufftMakePlanMany64`                     | ✅          | ✅      | ✅      |                          |
| `cufftGetSize1D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSize2D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSize3D`                          | ✅          | ✅      | ✅      |                          |
| `cufftGetSizeMany`                        | ✅          | ✅      | ✅      |                          |
| `cufftGetSizeMany64`                      | ✅          | ✅      | ✅      |                          |
| `cufftGetSize`                            | ✅          | ✅      | ✅      |                          |
| `cufftSetWorkArea`                        | ✅          | ✅      | ✅      |                          |
| `cufftSetAutoAllocation`                  | ✅          | ✅      | ✅      |                          |
| `cufftGetVersion`                         | ✅          | ✅      | ✅      |                          |
| `cufftSetStream`                          | ✅          | ✅      | ✅      |                          |
| `cufftXtMalloc`                           | ✅          | ✅      | ✅      |                          |
| `cufftXtFree`                             | ✅          | ✅      | ✅      |                          |            
| `cufftXtMemcpy`                           | ✅          | ✅      | ❌      |                          |  
| `cufftXtSetGpus`                          | ✅          | ✅      | ✅      |                          |
| `cufftXtExecDescriptorC2C`                | ✅          | ✅      | ❌      |                          |
| `cufftXtMakePlanMany`                     | ✅          | ✅      | ❌      | Not Supported by GVirtuS |

cuFFT handle typedefs changed in CUDA 12.

# cuDNN (-lcudnn)

| Function                                                   | Implemented | Tested  | Working |          Notes           |
| ---------------------------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cuDNNCreate`                                              | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroy`                                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetVersion`                                          | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetErrorString`                                      | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetStream`                                           | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetStream`                                           | ✅          | ✅      | ✅      |                          |  
| `cuDNNCreateTensorDescriptor`                              | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetTensor4dDescriptor`                               | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetTensor4dDescriptorEx`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetTensor4dDescriptor`                               | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetTensorNdDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetTensorNdDescriptorEx`                             | ✅          | ❌      | ❓      |                          |
| `cuDNNGetTensorNdDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetTensorSizeInBytes`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyTensorDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNInitTransformDest`                                   | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNCreateTensorTransformDescriptor`                     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNSetTensorTransformDescriptor`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNGetTensorTransformDescriptor`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNDestroyTensorTransformDescriptor`                    | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNTransformTensor`                                     | ✅          | ✅      | ✅      | float and double both working, Deprecated as of v9      | 
| `cuDNNTransformTensorEx`                                   | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNGetFoldedConvBackwardDataDescriptors`                | ✅          | ❌      | ❓      |                          | 
| `cuDNNAddTensor`                                           | ✅          | ✅      | ✅      | float and double both working, Deprecated as of v9      | 
| `cuDNNCreateOpTensorDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetOpTensorDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetOpTensorDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyOpTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNOpTensor`                                            | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNCreateReduceTensorDescriptor`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetReduceTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetReduceTensorDescriptor`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyReduceTensorDescriptor`                       | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetReductionIndicesSize`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetReductionWorkspaceSize`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNReduceTensor`                                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNSetTensor`                                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNScaleTensor`                                         | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNCreateFilterDescriptor`                              | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNSetFilter4dDescriptor`                               | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNGetFilter4dDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNSetFilter4dDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFilter4dDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetFilter4dDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFilter4dDescriptor_v4`                            | ✅          | ❌      | ❓      |                          |
| `cuDNNSetFilterNdDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNGetFilterNdDescriptor`                               | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNSetFilterNdDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFilterNdDescriptor_v3`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetFilterNdDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFilterNdDescriptor_v4`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFilterSizeInBytes`                                | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNDestroyFilterDescriptor`                             | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNTransformFilter`                                     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNReorderFilterAndBias`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateConvolutionDescriptor`                         | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetConvolutionMathType`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionMathType`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetConvolutionGroupCount`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionGroupCount`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetConvolutionReorderType`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionReorderType`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetConvolution2dDescriptor`                          | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolution2dDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolution2dForwardOutputDim`                    | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetConvolutionNdDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionNdDescriptor`                          | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionNdForwardOutputDim`                    | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyConvolutionDescriptor`                        | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolutionForwardAlgorithmMaxCount`              | ✅          | ❌      | ❓      |                          | 
| `cuDNNFindConvolutionForwardAlgorithm`                     | ✅          | ✅      | ✅      |                          | 
| `cuDNNFindConvolutionForwardAlgorithmEx`                   | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolutionForwardAlgorithm`                      | ✅          | ❌      | ❓      | Deprecated in v8, Use `cuDNNGetConvolutionForwardAlgorithm_v7` instead | 
| `cuDNNGetConvolutionForwardAlgorithm_v7`                   | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolutionForwardWorkspaceSize`                  | ✅          | ✅      | ✅      |                          | 
| `cuDNNConvolutionForward`                                  | ✅          | ✅      | ✅      |                          | 
| `cuDNNConvolutionBiasActivationForward`                    | ✅          | ❌      | ❓      | Deprecated in v9         | 
| `cuDNNConvolutionBackwardBias`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionBackwardFilterAlgorithmMaxCount`       | ✅          | ❌      | ❓      |                          | 
| `cuDNNFindConvolutionBackwardFilterAlgorithm`              | ✅          | ❌      | ❓      | Deprecated in v9         | 
| `cuDNNFindConvolutionBackwardFilterAlgorithmEx`            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionBackwardFilterAlgorithm`               | ✅          | ❌      | ❓      | Deprecated in v8, Use `cuDNNGetConvolutionBackwardFilterAlgorithm_v7` instead | 
| `cuDNNGetConvolutionBackwardFilterAlgorithm_v7`            | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolutionBackwardFilterWorkspaceSize`           | ✅          | ✅      | ✅      |                          | 
| `cuDNNConvolutionBackwardFilter`                           | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetConvolutionBackwardDataAlgorithmMaxCount`         | ✅          | ❌      | ❓      |                          | 
| `cuDNNFindConvolutionBackwardDataAlgorithm`                | ✅          | ❌      | ❓      |                          | 
| `cuDNNFindConvolutionBackwardDataAlgorithmEx`              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionBackwardDataAlgorithm`                 | ✅          | ❌      | ❓      | Deprecated in v8, Use `cuDNNGetConvolutionBackwardDataAlgorithm_v7` instead | 
| `cuDNNGetConvolutionBackwardDataAlgorithm_v7`              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetConvolutionBackwardDataWorkspaceSize`             | ✅          | ✅      | ✅      |                          | 
| `cuDNNConvolutionBackwardData`                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNIm2Col`                                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNSoftmaxForward`                                      | ✅          | ❌      | ❓      |                          | 
| `cuDNNSoftmaxBackward`                                     | ✅          | ✅      | ✅      |                          | 
| `cuDNNCreatePoolingDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetPooling2dDescriptor`                              | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetPooling2dDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetPoolingNdDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetPoolingNdDescriptor`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetPoolingNdForwardOutputDim`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetPooling2dForwardOutputDim`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyPoolingDescriptor`                            | ✅          | ✅      | ✅      |                          | 
| `cuDNNPoolingForward`                                      | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNPoolingBackward`                                     | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNCreateActivationDescriptor`                          | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetActivationDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetActivationDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyActivationDescriptor`                         | ✅          | ✅      | ✅      |                          | 
| `cuDNNActivationForward`                                   | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNActivationBackward`                                  | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNCreateLRNDescriptor`                                 | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetLRNDescriptor`                                    | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetLRNDescriptor`                                    | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroyLRNDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNLRNCrossChannelForward`                              | ✅          | ✅      | ✅      | float and double both working | 
| `cuDNNLRNCrossChannelBackward`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNDivisiveNormalizationForward`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNDivisiveNormalizationBackward`                       | ✅          | ❌      | ❓      |                          | 
| `cuDNNDeriveBNTensorDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetBatchNormalizationForwardTrainingExWorkspaceSize` | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNGetBatchNormalizationBackwardExWorkspaceSize`        | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetBatchNormalizationTrainingExReserveSpaceSize`     | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNBatchNormalizationForwardTraining`                   | ✅          | ✅      | ✅      | Deprecated as of v9      | 
| `cuDNNBatchNormalizationForwardTrainingEx`                 | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNBatchNormalizationForwardInference`                  | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNBatchNormalizationBackward`                          | ✅          | ✅      | ❓      | Deprecated as of v9      | 
| `cuDNNBatchNormalizationBackwardEx`                        | ✅          | ❌      | ❓      | Deprecated as of v9      | 
| `cuDNNCreateSpatialTransformerDescriptor`                  | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetSpatialTransformerNdDescriptor`                   | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroySpatialTransformerDescriptor`                 | ✅          | ❌      | ❓      |                          | 
| `cuDNNSpatialTfGridGeneratorForward`                       | ✅          | ❌      | ❓      |                          | 
| `cuDNNSpatialTfGridGeneratorBackward`                      | ✅          | ❌      | ❓      |                          | 
| `cuDNNSpatialTfSamplerForward`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNSpatialTfSamplerBackward`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateDropoutDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroyDropoutDescriptor`                            | ✅          | ✅      | ✅      |                          | 
| `cuDNNDropoutGetStatesSize`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNDropoutGetReserveSpaceSize`                          | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetDropoutDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNRestoreDropoutDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetDropoutDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNDropoutForward`                                      | ✅          | ❌      | ❓      |                          | 
| `cuDNNDropoutBackward`                                     | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateRNNDescriptor`                                 | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroyRNNDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetRNNDescriptor_v5`                                 | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetRNNDescriptor_v5`                                 | ❌          | ❌      | ❌      |                          | 
| `cuDNNSetRNNDescriptor_v6`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNBackwardData_v8` instead | 
| `cuDNNGetRNNDescriptor_v6`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNGetRNNDescriptor_v8` instead | 
| `cuDNNSetRNNDescriptor_v8`                                 | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetRNNDescriptor_v8`                                 | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetRNNMatrixMathType`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNSetRNNDescriptor_v8` instead | 
| `cuDNNGetRNNMatrixMathType`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetRNNBiasMode`                                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNSetRNNDescriptor_v8` instead | 
| `cuDNNGetRNNBiasMode`                                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNGetRNNDescriptor_v8` instead | 
| `cuDNNRNNSetClip`                                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNSetClip_v9` instead | 
| `cuDNNRNNGetClip`                                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNGetClip_v9` instead | 
| `cuDNNSetRNNProjectionLayers`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNSetRNNDescriptor_v8` instead | 
| `cuDNNGetRNNProjectionLayers`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNGetRNNDescriptor_v8` instead | 
| `cuDNNCreatePersistentRNNPlan`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cuDNNDestroyPersistentRNNPlan`                            | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cuDNNSetPersistentRNNPlan`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnBuildRNNDynamic` instead | 
| `cuDNNGetRNNWorkspaceSize`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNTempSpaceSize` instead | 
| `cuDNNGetRNNTrainingReserveSize`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNTempSpaceSize` instead | 
| `cuDNNGetRNNParamsSize`                                    | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use  `cudnnGetRNNWeightSpaceSize` instead | 
| `cuDNNGetRNNLinLayerMatrixParams`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNWeightParams` instead | 
| `cuDNNGetRNNLinLayerBiasParams`                            | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnGetRNNWeightParams` instead | 
| `cuDNNRNNForwardInference`                                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cuDNNRNNForwardTraining`                                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cuDNNRNNBackwardData`                                     | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNBackwardData_v8` instead | 
| `cuDNNRNNBackwardData_v8`                                  | ❌          | ❌      | ❌      |                          |
| `cuDNNRNNBackwardWeights`                                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSetRNNPaddingMode`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNBackwardData_v8` instead | 
| `cuDNNGetRNNPaddingMode`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNGetRNNDescriptor_v8` instead | 
| `cuDNNCreateRNNDataDescriptor`                             | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroyRNNDataDescriptor`                            | ✅          | ✅      | ✅      |                          | 
| `cuDNNSetRNNDataDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNGetRNNDataDescriptor`                                | ✅          | ✅      | ✅      |                          | 
| `cuDNNRNNForwardTrainingEx`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cuDNNRNNForwardInferenceEx`                               | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cudnnRNNForward` instead | 
| `cuDNNRNNBackwardDataEx`                                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9, Use `cuDNNRNNBackwardData_v8` instead | 
| `cuDNNRNNBackwardWeightsEx`                                | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSetRNNAlgorithmDescriptor`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetRNNForwardInferenceAlgorithmMaxCount`             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNFindRNNForwardInferenceAlgorithmEx`                  | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetRNNForwardTrainingAlgorithmMaxCount`              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNFindRNNForwardTrainingAlgorithmEx`                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetRNNBackwardDataAlgorithmMaxCount`                 | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNFindRNNBackwardDataAlgorithmEx`                      | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetRNNBackwardWeightsAlgorithmMaxCount`              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNFindRNNBackwardWeightsAlgorithmEx`                   | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNCreateSeqDataDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroySeqDataDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetSeqDataDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetSeqDataDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateAttnDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyAttnDescriptor`                               | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetAttnDescriptor`                                   | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetAttnDescriptor`                                   | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetMultiHeadAttnBuffers`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetMultiHeadAttnWeights`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNMultiHeadAttnForward`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNMultiHeadAttnBackwardData`                           | ✅          | ❌      | ❓      |                          | 
| `cuDNNMultiHeadAttnBackwardWeights`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateCTCLossDescriptor`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetCTCLossDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetCTCLossDescriptorEx`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetCTCLossDescriptor`                                | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetCTCLossDescriptorEx`                              | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyCTCLossDescriptor`                            | ✅          | ❌      | ❓      |                          | 
| `cuDNNCTCLoss`                                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetCTCLossWorkspaceSize`                             | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateAlgorithmDescriptor`                           | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSetAlgorithmDescriptor`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetAlgorithmDescriptor`                              | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNCopyAlgorithmDescriptor`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNDestroyAlgorithmDescriptor`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNCreateAlgorithmPerformance`                          | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSetAlgorithmPerformance`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetAlgorithmPerformance`                             | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNDestroyAlgorithmPerformance`                         | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNGetAlgorithmSpaceSize`                               | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSaveAlgorithm`                                       | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNRestoreAlgorithm`                                    | ✅          | ❌      | ❓      | Deprecated in v8, Removed in v9 | 
| `cuDNNSetCallback`                                         | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetCallback`                                         | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateFusedOpsConstParamPack`                        | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyFusedOpsConstParamPack`                       | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetFusedOpsConstParamPackAttribute`                  | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFusedOpsConstParamPackAttribute`                  | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateFusedOpsVariantParamPack`                      | ✅          | ❌      | ❓      |                          | 
| `cuDNNDestroyFusedOpsVariantParamPack`                     | ✅          | ❌      | ❓      |                          | 
| `cuDNNSetFusedOpsVariantParamPackAttribute`                | ✅          | ❌      | ❓      |                          | 
| `cuDNNGetFusedOpsVariantParamPackAttribute`                | ✅          | ❌      | ❓      |                          | 
| `cuDNNCreateFusedOpsPlan`                                  | ✅          | ✅      | ✅      |                          | 
| `cuDNNDestroyFusedOpsPlan`                                 | ✅          | ✅      | ✅      |                          | 
| `cuDNNMakeFusedOpsPlan`                                    | ✅          | ❌      | ❓      |                          | 
| `cuDNNFusedOpsExecute`                                     | ✅          | ❌      | ❓      |                          | 


# cuSPARSE (-lcusparse)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cusparseCreate`                          | ✅          | ✅      | ✅      |                          | 
| `cusparseDestroy`                         | ✅          | ✅      | ✅      |                          | 
| `cusparseGetVersion`                      | ✅          | ✅      | ✅      |                          | 
| `cusparseGetErrorString`                  | ✅          | ✅      | ✅      |                          | 
| `cusparseSetStream`                       | ✅          | ✅      | ✅      |                          | 
| `cusparseGetStream`                       | ✅          | ✅      | ✅      |                          | 
| `cusparseXcsrgemm`                        | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsr2dense`                      | ❌          | ❌      | ❌      |                          | 
| `cusparseXdense2csr`                      | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv`                          | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv_analysis`                 | ❌          | ❌      | ❌      |                          | 
| `cusparseXcsrmv_solve`                    | ❌          | ❌      | ❌      |                          | 


# cuSOLVER (-lcusolver)

| Function                                  | Implemented | Tested  | Working |          Notes           |
| ----------------------------------------- | ----------- | ------- | ------- | -------------------------|
| `cusolverDnCreate`                        | ✅          | ✅      | ✅       |                          |       
| `cusolverDnDestroy`                       | ✅          | ✅      | ✅       |                          | 
| `cusolverDnSetStream`                     | ✅          | ✅      | ✅       |                          | 
| `cusolverDnGetStream`                     | ✅          | ✅      | ✅       |                          |
| `cusolverDnSgetrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDgetrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSgetrs`                        | ❌          | ❌      | ❌       |                          |     
| `cusolverDnDgetrs`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSgesvd`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDgesvd`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnSpotrf`                        | ❌          | ❌      | ❌       |                          |
| `cusolverDnDpotrf`                        | ❌          | ❌      | ❌       |                          |
