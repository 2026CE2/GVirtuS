# CUDA Graph Implemented Endpoints Overview

Generated: 2026-04-29

Scope:
- Frontend wrappers: `plugins/cudart/frontend/CudaRt_graph.cpp`
- Backend handlers: `plugins/cudart/backend/CudaRtHandler_graph.cpp`
- Backend declarations: `plugins/cudart/backend/CudaRtHandler.h`
- Backend registrations: `plugins/cudart/backend/CudaRtHandler.cpp`

This overview lists the CUDA graph-related endpoints currently implemented in the `cudart` plugin frontend/backend path.

## Summary

- Implemented graph-related host endpoints: 94
- Device-only graph helper APIs intentionally not implemented as host RPC endpoints: 6
- All listed implemented endpoints have frontend wrappers and backend handler coverage unless noted otherwise.

## Core Graph Lifecycle

- `cudaGraphCreate`
- `cudaGraphDestroy`
- `cudaGraphGetNodes`
- `cudaGraphDebugDotPrint`
- `cudaGraphInstantiate`
- `cudaGraphInstantiateWithFlags`
- `cudaGraphInstantiateWithParams`
- `cudaGraphLaunch`
- `cudaGraphUpload`
- `cudaGraphExecDestroy`

## Graph Topology And Dependency Management

- `cudaGraphClone`
- `cudaGraphAddDependencies`
- `cudaGraphAddDependencies_v2`
- `cudaGraphRemoveDependencies`
- `cudaGraphRemoveDependencies_v2`
- `cudaGraphGetEdges`
- `cudaGraphGetEdges_v2`
- `cudaGraphGetRootNodes`
- `cudaGraphDestroyNode`
- `cudaGraphNodeGetType`
- `cudaGraphNodeFindInClone`
- `cudaGraphNodeGetDependencies`
- `cudaGraphNodeGetDependencies_v2`
- `cudaGraphNodeGetDependentNodes`
- `cudaGraphNodeGetDependentNodes_v2`

## Node Creation

- `cudaGraphAddEmptyNode`
- `cudaGraphAddChildGraphNode`
- `cudaGraphChildGraphNodeGetGraph`
- `cudaGraphAddKernelNode`
- `cudaGraphAddHostNode`
- `cudaGraphAddMemcpyNode`
- `cudaGraphAddMemcpyNode1D`
- `cudaGraphAddMemcpyNodeFromSymbol`
- `cudaGraphAddMemcpyNodeToSymbol`
- `cudaGraphAddMemsetNode`
- `cudaGraphAddEventRecordNode`
- `cudaGraphAddEventWaitNode`
- `cudaGraphAddExternalSemaphoresSignalNode`
- `cudaGraphAddExternalSemaphoresWaitNode`
- `cudaGraphAddMemAllocNode`
- `cudaGraphAddMemFreeNode`
- `cudaGraphAddNode`
- `cudaGraphAddNode_v2`

## Non-Executable Node Parameter APIs

- `cudaGraphKernelNodeGetParams`
- `cudaGraphKernelNodeSetParams`
- `cudaGraphKernelNodeGetAttribute`
- `cudaGraphKernelNodeSetAttribute`
- `cudaGraphKernelNodeCopyAttributes`
- `cudaGraphHostNodeGetParams`
- `cudaGraphHostNodeSetParams`
- `cudaGraphMemcpyNodeGetParams`
- `cudaGraphMemcpyNodeSetParams`
- `cudaGraphMemcpyNodeSetParams1D`
- `cudaGraphMemcpyNodeSetParamsFromSymbol`
- `cudaGraphMemcpyNodeSetParamsToSymbol`
- `cudaGraphMemsetNodeGetParams`
- `cudaGraphMemsetNodeSetParams`
- `cudaGraphEventRecordNodeGetEvent`
- `cudaGraphEventRecordNodeSetEvent`
- `cudaGraphEventWaitNodeGetEvent`
- `cudaGraphEventWaitNodeSetEvent`
- `cudaGraphExternalSemaphoresSignalNodeGetParams`
- `cudaGraphExternalSemaphoresSignalNodeSetParams`
- `cudaGraphExternalSemaphoresWaitNodeGetParams`
- `cudaGraphExternalSemaphoresWaitNodeSetParams`
- `cudaGraphMemAllocNodeGetParams`
- `cudaGraphMemFreeNodeGetParams`
- `cudaGraphNodeSetParams`

## Executable Graph Update And Control APIs

- `cudaGraphExecUpdate`
- `cudaGraphExecGetFlags`
- `cudaGraphExecChildGraphNodeSetParams`
- `cudaGraphExecKernelNodeSetParams`
- `cudaGraphExecHostNodeSetParams`
- `cudaGraphExecMemcpyNodeSetParams`
- `cudaGraphExecMemcpyNodeSetParams1D`
- `cudaGraphExecMemcpyNodeSetParamsFromSymbol`
- `cudaGraphExecMemcpyNodeSetParamsToSymbol`
- `cudaGraphExecMemsetNodeSetParams`
- `cudaGraphExecEventRecordNodeSetEvent`
- `cudaGraphExecEventWaitNodeSetEvent`
- `cudaGraphExecExternalSemaphoresSignalNodeSetParams`
- `cudaGraphExecExternalSemaphoresWaitNodeSetParams`
- `cudaGraphExecNodeSetParams`
- `cudaGraphNodeGetEnabled`
- `cudaGraphNodeSetEnabled`

## Graph Memory APIs

- `cudaDeviceGetGraphMemAttribute`
- `cudaDeviceSetGraphMemAttribute`
- `cudaDeviceGraphMemTrim`

## User Object APIs

- `cudaUserObjectCreate`
- `cudaUserObjectRetain`
- `cudaUserObjectRelease`
- `cudaGraphRetainUserObject`
- `cudaGraphReleaseUserObject`

## Conditional Graph API

- `cudaGraphConditionalHandleCreate`

## Not Implemented In Host RPC Path

These CUDA graph APIs are device-side helpers, not normal host runtime calls. They were intentionally left out of the `CudaRtFrontend`/`CudaRtHandler` host endpoint pattern.

- `cudaGetCurrentGraphExec`
- `cudaGraphSetConditional`
- `cudaGraphKernelNodeSetEnabled`
- `cudaGraphKernelNodeSetGridDim`
- `cudaGraphKernelNodeSetParam`
- `cudaGraphKernelNodeUpdatesApply`

## Notes

- Build verification still requires a configured CUDA toolkit. Local CMake configuration currently stops before compilation unless `CUDA_TOOLKIT_ROOT_DIR` is set.
- Some newer graph APIs require CUDA 12.x headers. If the build environment uses an older CUDA toolkit, version guards may be needed.
