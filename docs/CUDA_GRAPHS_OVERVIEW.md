# CUDA Graphs Overview

## Current State

GVirtuS currently has a minimal CUDA Runtime graph path implemented in the `cudart` plugin. The code covers a narrow subset of the CUDA Graphs API:

- Stream capture:
  - `cudaThreadExchangeStreamCaptureMode`
  - `cudaStreamIsCapturing`
  - `cudaStreamBeginCapture`
  - `cudaStreamEndCapture`
  - `cudaStreamGetCaptureInfo`
- Graph lifecycle:
  - `cudaGraphCreate`
  - `cudaGraphDestroy`
  - `cudaGraphGetNodes`
  - `cudaGraphInstantiate`
  - `cudaGraphInstantiateWithFlags`
  - `cudaGraphLaunch`
  - `cudaGraphExecDestroy`
  - `cudaGraphUpload`

The current implementation is best described as a temporary pass-through for simple capture -> instantiate -> launch flows. It is not yet a full CUDA Graphs implementation.

There is no corresponding CUDA Driver graph support (`cuGraph*`) in `plugins/cudadr`.

## Immediate Correctness Gaps

These need to be fixed before expanding API coverage.

### 1. `cudaGraphUpload` is miswired

The frontend calls `cudaGraphLaunch` instead of `cudaGraphUpload`.

- Frontend issue: [plugins/cudart/frontend/CudaRt_graph.cpp](/home/kris/Project/GVirtuS/plugins/cudart/frontend/CudaRt_graph.cpp#L131)
- Effect: tests may pass while exercising the wrong backend routine.

### 2. `cudaStreamGetCaptureInfo` marshalling is not robust

The handler currently mixes host-pointer input marshalling with backend-returned opaque handles and dependency arrays in a way that is unsafe for a full implementation.

- Frontend path: [plugins/cudart/frontend/CudaRt_stream.cpp](/home/kris/Project/GVirtuS/plugins/cudart/frontend/CudaRt_stream.cpp#L132)
- Backend path: [plugins/cudart/backend/CudaRtHandler_stream.cpp](/home/kris/Project/GVirtuS/plugins/cudart/backend/CudaRtHandler_stream.cpp#L218)

Specific problems:

- `graph_out` is added back as a pointer-sized value even though the frontend expects a returned graph handle.
- `dependencies_out` is treated like a raw pointer value, but the dependency list belongs to backend memory and is not meaningfully usable on the frontend without explicit translation rules.
- `numDependencies_out` is written back through buffer pointer semantics instead of a clear value protocol.
- Debug logging is still present in the backend.

For a virtualized setup, every returned graph handle and graph node handle must be treated as an opaque remote handle, not as host-accessible memory.

### 3. `cudaGraphGetNodes` only returns a count

The current implementation accepts a `nodes` pointer but only returns `numNodes`.

- Frontend: [plugins/cudart/frontend/CudaRt_graph.cpp](/home/kris/Project/GVirtuS/plugins/cudart/frontend/CudaRt_graph.cpp#L33)
- Backend: [plugins/cudart/backend/CudaRtHandler_graph.cpp](/home/kris/Project/GVirtuS/plugins/cudart/backend/CudaRtHandler_graph.cpp#L56)

That is enough for the current test, because the test passes `nodes == NULL`, but it is not a complete implementation.

### 4. Several graph paths are explicitly untested

The code already marks some graph functions as needing testing.

- `cudaGraphInstantiateWithFlags`
- `cudaGraphDebugDotPrint`
- `cudaStreamEndCapture`
- `cudaGraphLaunch` backend comment says "No Testing"

### 5. Status documentation is incomplete

`docs/STATUS.md` does not currently list the CUDA Graphs runtime functions, so the advertised support level is hard to track.

## What "Full" Support Should Mean

A full CUDA Graphs implementation for GVirtuS should support:

- Correct capture semantics across virtualized streams.
- Stable remote-handle management for `cudaGraph_t`, `cudaGraphExec_t`, and `cudaGraphNode_t`.
- Graph introspection APIs returning usable results to the frontend.
- Graph construction and editing APIs, not only capture-derived graphs.
- Graph exec update and node parameter update flows.
- Coverage across CUDA 11/12 API differences where signatures changed.
- A test suite that validates behavior, not only successful return codes.

## Work Plan

### Phase 1. Make the current subset correct

1. Fix `cudaGraphUpload` frontend dispatch to call the correct backend routine.
2. Redesign `cudaStreamGetCaptureInfo` result marshalling:
   - return `captureStatus` and `id` as plain values
   - return `graph_out` as an opaque remote graph handle
   - define whether `dependencies_out` is supported now, stubbed cleanly, or translated into frontend-visible opaque node handles
   - return `numDependencies_out` as a plain value
3. Complete `cudaGraphGetNodes` so it supports both:
   - `nodes == NULL` -> count query
   - `nodes != NULL` -> returned array of opaque `cudaGraphNode_t` handles
4. Remove debug prints and temporary comments from the graph/capture handlers.

### Phase 2. Define a handle model for graphs and nodes

This is the key architectural step.

The implementation currently relies on passing backend-created opaque handles through the existing pointer transport. That works only as long as the frontend never needs to interpret anything beyond "send this handle back later."

We should explicitly define:

- `cudaGraph_t` as a remote graph handle
- `cudaGraphExec_t` as a remote executable graph handle
- `cudaGraphNode_t` as a remote node handle

Then decide how arrays of these handles are serialized:

- as plain `pointer_t` values in arrays
- with dedicated helper functions for "opaque handle array" marshalling

This handle model should be reused by all future graph APIs.

### Phase 3. Expand runtime API coverage

After the handle model is stable, add the missing runtime APIs in priority order.

Recommended priority:

1. Graph query and topology:
   - `cudaGraphGetRootNodes`
   - `cudaGraphGetEdges`
   - `cudaGraphGetNodes` completion if still partial
   - `cudaGraphNodeGetType`
2. Explicit graph construction:
   - `cudaGraphAddKernelNode`
   - `cudaGraphAddMemcpyNode`
   - `cudaGraphAddMemsetNode`
   - `cudaGraphAddHostNode`
   - `cudaGraphAddEmptyNode`
   - `cudaGraphAddChildGraphNode`
   - `cudaGraphAddDependencies`
   - `cudaGraphRemoveDependencies`
3. Graph node inspection:
   - `cudaGraphKernelNodeGetParams`
   - `cudaGraphMemcpyNodeGetParams`
   - `cudaGraphMemsetNodeGetParams`
   - `cudaGraphHostNodeGetParams`
4. Graph node mutation:
   - `cudaGraphKernelNodeSetParams`
   - `cudaGraphMemcpyNodeSetParams`
   - `cudaGraphMemsetNodeSetParams`
   - `cudaGraphExecKernelNodeSetParams`
   - `cudaGraphExecMemcpyNodeSetParams`
   - `cudaGraphExecMemsetNodeSetParams`
   - `cudaGraphExecHostNodeSetParams`
5. Graph cloning and child graphs:
   - `cudaGraphClone`
   - child-graph query helpers as needed
6. Graph executable lifecycle and update:
   - `cudaGraphExecUpdate`
   - `cudaGraphExecChildGraphNodeSetParams`
   - instantiate variants required by supported CUDA versions

### Phase 4. Handle version compatibility explicitly

Graph APIs changed noticeably across CUDA releases, especially around instantiate/update signatures.

The code already contains one CUDA 12 note:

- [plugins/cudart/backend/CudaRtHandler_graph.cpp](/home/kris/Project/GVirtuS/plugins/cudart/backend/CudaRtHandler_graph.cpp#L74)

Full support should add:

- `#if CUDART_VERSION` guards where signatures differ
- a documented support matrix for CUDA 11.x and 12.x
- tests compiled against the supported runtime versions

### Phase 5. Build a real validation suite

The current tests prove basic wiring, but not full graph correctness.

- Existing tests: [tests/test_cudart.cu](/home/kris/Project/GVirtuS/tests/test_cudart.cu#L109)

Add tests for:

- querying capture info while active and after capture ends
- node enumeration with non-null `nodes`
- launch correctness with observable side effects, not only return codes
- upload semantics distinct from launch semantics
- explicit graph creation with added nodes
- dependency ordering
- graph clone behavior
- graph exec update success and failure cases
- negative cases:
  - invalid handles
  - invalid capture state transitions
  - unsupported cross-stream or cross-thread capture patterns

The tests should validate outputs in device memory so we know the launched graph actually executed the expected workload.

### Phase 6. Document support and limitations

Once the implementation is stable:

- add CUDA Graphs rows to `docs/STATUS.md`
- document which graph APIs are supported
- document which return values are opaque remote handles
- document any unsupported capture patterns or node types

## Suggested Implementation Order

If the goal is to move from temporary support to something usable quickly, the shortest path is:

1. Fix `cudaGraphUpload`
2. Fix `cudaStreamGetCaptureInfo` marshalling
3. Complete `cudaGraphGetNodes`
4. Strengthen tests around capture, launch, and node enumeration
5. Add explicit graph construction APIs for kernel/memcpy/memset nodes
6. Add graph exec update APIs
7. Expand documentation and version handling

## Recommended Definition of Done

CUDA Graphs support should be considered "fully implemented" only when:

- the currently implemented subset is correct and tested
- graph/node/exec handles are cleanly modeled as remote opaque handles
- construction, query, mutation, and launch/update APIs all work
- CUDA version differences are handled intentionally
- `docs/STATUS.md` reflects the real state of support
- tests validate graph behavior, not only API return codes
