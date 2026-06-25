# CUDA Graph API Implementation Guide (GVirtuS `cudart`)

This guide explains exactly where to implement missing CUDA Graph runtime APIs, and in what order.

## 1) Files to modify for each new `cudaGraph*` API

For each API, touch these files:

1. Frontend wrapper:
- `plugins/cudart/frontend/CudaRt_graph.cpp`

2. Backend handler declaration:
- `plugins/cudart/backend/CudaRtHandler.h`

3. Backend handler registration:
- `plugins/cudart/backend/CudaRtHandler.cpp`

4. Backend handler implementation:
- `plugins/cudart/backend/CudaRtHandler_graph.cpp`

Notes:
- `plugins/cudart/CMakeLists.txt` already includes both graph source files. No CMake changes are needed if you keep implementations in those files.
- `plugins/cudart/frontend/CudaRt.h` already includes `cuda_runtime_api.h`; no new declaration file is required.

## 2) Step-by-step template for one API

Example target: `cudaGraphClone(cudaGraph_t* pGraphClone, cudaGraph_t originalGraph)`

### Step 1: Add frontend wrapper in `CudaRt_graph.cpp`

Pattern:
- `CudaRtFrontend::Prepare();`
- Marshal args in exact backend read order.
- `CudaRtFrontend::Execute("cudaGraphClone");`
- If success, read outputs with `GetOutputVariable<T>()` / `GetOutputHostPointer<T>()`.
- Return `CudaRtFrontend::GetExitCode();`

Marshal helper mapping:
- Opaque handles (`cudaGraph_t`, `cudaGraphExec_t`, `cudaGraphNode_t`, streams/events): `AddDevicePointerForArguments(...)`
- Scalars/flags/enums/counts: `AddVariableForArguments(...)`
- Strings: `AddStringForArguments(...)`
- Host pointers/arrays (input/output host memory): `AddHostPointerForArguments(ptr, n)`

### Step 2: Declare backend routine in `CudaRtHandler.h`

Add macro in graph section:
- `CUDA_ROUTINE_HANDLER(GraphClone);`

### Step 3: Register handler in `CudaRtHandler.cpp`

In graph block, add:
- `mspHandlers->insert(CUDA_ROUTINE_HANDLER_PAIR(GraphClone));`

### Step 4: Implement backend routine in `CudaRtHandler_graph.cpp`

Pattern:
- Read input args from `input_buffer` in same order used by frontend.
- Call native CUDA API.
- If outputs exist, create `Buffer out` and `out->Add<...>(...)` in exact output order expected by frontend.
- Return `std::make_shared<Result>(exit_code, out)` or `Result(exit_code)` when no output buffer.

### Step 5: Compile and smoke test

- Build plugin.
- Run one happy-path test and one invalid-arg test.
- Validate that pointer outputs are unmarshaled correctly.

## 3) Required ordering rules (dependencies)

Implement in dependency order to avoid blocked testing.

1. Base lifecycle first:
- `cudaGraphCreate`, `cudaGraphDestroy`, `cudaGraphInstantiate`, `cudaGraphLaunch`, `cudaGraphExecDestroy`
- Already implemented.

2. Graph topology operations:
- `cudaGraphClone`, `cudaGraphAddDependencies`, `cudaGraphRemoveDependencies`, `cudaGraphGetEdges`, `cudaGraphGetRootNodes`, `cudaGraphDestroyNode`
- These are prerequisites for many graph-edit tests.

3. Node creation APIs:
- `cudaGraphAddKernelNode`, `cudaGraphAddMemcpyNode`, `cudaGraphAddMemcpyNode1D`, `cudaGraphAddMemsetNode`, `cudaGraphAddHostNode`, `cudaGraphAddEmptyNode`
- Node set/get APIs depend on these.

4. Node parameter APIs:
- Kernel/Memcpy/Memset/Host node get/set parameter APIs.

5. Exec update APIs:
- `cudaGraphExec*SetParams`, `cudaGraphExecUpdate`, `cudaGraphInstantiateWithParams`, `cudaGraphExecGetFlags`
- Depend on both instantiated graph exec and node types.

6. Advanced families:
- Event nodes, external semaphore nodes, child graph nodes, mem alloc/free nodes, generic `AddNode` APIs.

7. Optional/late:
- `_v2` variants, user-object APIs, graph memory attribute APIs, conditional APIs, device-side graph helper APIs.

## 4) API family -> primary implementation file

Use this placement convention:

- Graph core / node / exec update APIs:
  - Frontend: `plugins/cudart/frontend/CudaRt_graph.cpp`
  - Backend: `plugins/cudart/backend/CudaRtHandler_graph.cpp`

- Stream-capture related APIs (`cudaStreamBeginCapture`, `cudaStreamEndCapture`, `cudaStreamGetCaptureInfo`, etc.):
  - Frontend: `plugins/cudart/frontend/CudaRt_stream.cpp`
  - Backend: `plugins/cudart/backend/CudaRtHandler_stream.cpp`

- Graph memory device attributes (`cudaDeviceGetGraphMemAttribute`, etc.):
  - Keep in graph files (recommended for cohesion), unless you want to mirror CUDA module layout and place device-scoped functions in device files.

## 5) Marshalling checklist (common failure points)

1. Frontend `Execute("...")` string must match backend routine name exactly.
2. Frontend argument order must match backend `Get<T>()`/`Assign<T>()` order exactly.
3. Output buffer order in backend must match frontend `GetOutput...()` order exactly.
4. For arrays, pass/consume `count` consistently.
5. Treat CUDA opaque handles as device pointers in this codebase (`AddDevicePointerForArguments`).

## 6) Immediate fixes before adding more APIs

1. `cudaGraphUpload` wrapper currently calls `Execute("cudaGraphLaunch")`; change to `Execute("cudaGraphUpload")`.
2. `cudaGraphDebugDotPrint` exists in frontend but has no backend declaration/registration/handler; add all three.

## 7) Suggested implementation batches

Batch A (unblock graph editing):
- `cudaGraphClone`
- `cudaGraphAddDependencies`
- `cudaGraphRemoveDependencies`
- `cudaGraphGetEdges`
- `cudaGraphGetRootNodes`
- `cudaGraphDestroyNode`

Batch B (high-usage node types):
- `cudaGraphAddKernelNode`
- `cudaGraphAddMemcpyNode`
- `cudaGraphAddMemcpyNode1D`
- `cudaGraphAddMemsetNode`
- `cudaGraphAddHostNode`
- corresponding node get/set params

Batch C (runtime updates):
- `cudaGraphExecKernelNodeSetParams`
- `cudaGraphExecMemcpyNodeSetParams`
- `cudaGraphExecMemsetNodeSetParams`
- `cudaGraphExecHostNodeSetParams`
- `cudaGraphExecUpdate`

