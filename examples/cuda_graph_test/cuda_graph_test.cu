/*
 * CUDA Graph API test - exercises the GVirtuS graph endpoint handlers.
 *
 * Functions covered:
 *   cudaGraphCreate / cudaGraphDestroy
 *   cudaGraphAddEmptyNode
 *   cudaGraphAddMemcpyNode1D
 *   cudaGraphAddKernelNode
 *   cudaGraphAddMemsetNode
 *   cudaGraphAddDependencies / cudaGraphRemoveDependencies
 *   cudaGraphGetNodes / cudaGraphGetRootNodes / cudaGraphGetEdges
 *   cudaGraphNodeGetType
 *   cudaGraphNodeGetDependencies / cudaGraphNodeGetDependentNodes
 *   cudaGraphKernelNodeGetParams / cudaGraphKernelNodeSetParams
 *   cudaGraphMemcpyNodeGetParams
 *   cudaGraphMemsetNodeGetParams / cudaGraphMemsetNodeSetParams
 *   cudaGraphInstantiate / cudaGraphInstantiateWithFlags
 *   cudaGraphUpload / cudaGraphLaunch / cudaGraphExecDestroy
 *   cudaGraphExecGetFlags
 *   cudaGraphClone / cudaGraphNodeFindInClone
 *   cudaGraphAddChildGraphNode / cudaGraphChildGraphNodeGetGraph
 *   cudaGraphExecUpdate
 *   cudaGraphNodeSetEnabled / cudaGraphNodeGetEnabled
 *   cudaGraphDestroyNode
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cuda_runtime.h>

// ---------------------------------------------------------------------------
// Helper macros
// ---------------------------------------------------------------------------
#define CHECK(call)                                                            \
    do {                                                                       \
        cudaError_t _e = (call);                                               \
        if (_e != cudaSuccess) {                                               \
            std::cerr << "[FAIL] CUDA error at " << __FILE__ << ":"           \
                      << __LINE__ << "  " << cudaGetErrorString(_e)           \
                      << "\n  call: " #call "\n";                             \
            std::exit(1);                                                      \
        }                                                                      \
    } while (0)

#define PASS(name)   std::cout << "[PASS] " << (name) << "\n"
#define FAIL(name)   do { std::cerr << "[FAIL] " << (name) << "\n"; std::exit(1); } while (0)
#define ASSERT(cond, name) do { if (!(cond)) FAIL(name); } while (0)

// ---------------------------------------------------------------------------
// Simple kernel: multiplies every element by 2
// ---------------------------------------------------------------------------
__global__ void doubleValues(float* data, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) data[idx] *= 2.0f;
}

// ---------------------------------------------------------------------------
int main() {
    const int   N     = 32;
    const size_t bytes = N * sizeof(float);

    // Use pinned host memory so it is valid inside graph nodes
    float *h_input, *h_output;
    CHECK(cudaMallocHost(&h_input,  bytes));
    CHECK(cudaMallocHost(&h_output, bytes));
    for (int i = 0; i < N; i++) {
        h_input[i]  = static_cast<float>(i + 1);
        h_output[i] = 0.0f;
    }

    float *d_buf;
    CHECK(cudaMalloc(&d_buf, bytes));

    cudaStream_t stream;
    CHECK(cudaStreamCreate(&stream));

    // -----------------------------------------------------------------------
    // TEST 1: GraphCreate / GraphDestroy (trivial round-trip)
    // -----------------------------------------------------------------------
    {
        cudaGraph_t g;
        CHECK(cudaGraphCreate(&g, 0));
        CHECK(cudaGraphDestroy(g));
        PASS("GraphCreate / GraphDestroy");
    }

    // -----------------------------------------------------------------------
    // Build the main test graph:
    //
    //   emptyNode ──► memcpyH2D ──► kernelNode ──► memcpyD2H
    //         │
    //         └──────────────────► memsetNode
    //
    // -----------------------------------------------------------------------
    cudaGraph_t graph;
    CHECK(cudaGraphCreate(&graph, 0));

    // TEST 2: GraphAddEmptyNode
    cudaGraphNode_t emptyNode;
    CHECK(cudaGraphAddEmptyNode(&emptyNode, graph, nullptr, 0));
    PASS("GraphAddEmptyNode");

    // TEST 3: GraphAddMemcpyNode1D  (H2D: h_input → d_buf)
    cudaGraphNode_t memcpyH2D;
    CHECK(cudaGraphAddMemcpyNode1D(&memcpyH2D, graph,
                                   &emptyNode, 1,
                                   d_buf, h_input, bytes,
                                   cudaMemcpyHostToDevice));
    PASS("GraphAddMemcpyNode1D (H2D)");

    // TEST 4: GraphAddKernelNode
    int nVal = N;
    void* kernelArgs[] = { (void*)&d_buf, (void*)&nVal };
    cudaKernelNodeParams kp = {};
    kp.func           = (void*)doubleValues;
    kp.gridDim        = dim3(1);
    kp.blockDim       = dim3(N);
    kp.sharedMemBytes = 0;
    kp.kernelParams   = kernelArgs;
    kp.extra          = nullptr;

    cudaGraphNode_t kernelNode;
    CHECK(cudaGraphAddKernelNode(&kernelNode, graph, &memcpyH2D, 1, &kp));
    PASS("GraphAddKernelNode");

    // TEST 5: GraphAddMemcpyNode1D  (D2H: d_buf → h_output)
    cudaGraphNode_t memcpyD2H;
    CHECK(cudaGraphAddMemcpyNode1D(&memcpyD2H, graph,
                                   &kernelNode, 1,
                                   h_output, d_buf, bytes,
                                   cudaMemcpyDeviceToHost));
    PASS("GraphAddMemcpyNode1D (D2H)");

    // TEST 6: GraphAddMemsetNode  (zero d_buf; no deps so it runs in parallel)
    cudaMemsetParams msp = {};
    msp.dst         = d_buf;
    msp.value       = 0;
    msp.elementSize = sizeof(unsigned int);
    msp.width       = N;
    msp.height      = 1;
    msp.pitch       = bytes;

    cudaGraphNode_t memsetNode;
    CHECK(cudaGraphAddMemsetNode(&memsetNode, graph, nullptr, 0, &msp));
    PASS("GraphAddMemsetNode");

    // TEST 7: GraphAddDependencies  (emptyNode → memsetNode)
    CHECK(cudaGraphAddDependencies(graph, &emptyNode, &memsetNode, 1));
    PASS("GraphAddDependencies");

    // -----------------------------------------------------------------------
    // Graph inspection tests
    // -----------------------------------------------------------------------

    // TEST 8: GraphGetNodes
    {
        size_t n = 0;
        CHECK(cudaGraphGetNodes(graph, nullptr, &n));
        ASSERT(n == 5, "GraphGetNodes: expected 5 nodes");
        std::vector<cudaGraphNode_t> nodes(n);
        CHECK(cudaGraphGetNodes(graph, nodes.data(), &n));
        PASS("GraphGetNodes");
    }

    // TEST 9: GraphGetRootNodes  (only emptyNode has no predecessors)
    {
        size_t n = 0;
        CHECK(cudaGraphGetRootNodes(graph, nullptr, &n));
        ASSERT(n == 1, "GraphGetRootNodes: expected 1 root");
        cudaGraphNode_t root;
        CHECK(cudaGraphGetRootNodes(graph, &root, &n));
        ASSERT(root == emptyNode, "GraphGetRootNodes: root should be emptyNode");
        PASS("GraphGetRootNodes");
    }

    // TEST 10: GraphGetEdges
    // Edges: emptyNode→memcpyH2D, memcpyH2D→kernelNode,
    //        kernelNode→memcpyD2H, emptyNode→memsetNode  (4 total)
    {
        size_t n = 0;
        CHECK(cudaGraphGetEdges(graph, nullptr, nullptr, &n));
        ASSERT(n == 4, "GraphGetEdges: expected 4 edges");
        std::vector<cudaGraphNode_t> froms(n), tos(n);
        CHECK(cudaGraphGetEdges(graph, froms.data(), tos.data(), &n));
        PASS("GraphGetEdges");
    }

    // TEST 11: GraphNodeGetType
    {
        cudaGraphNodeType t;
        CHECK(cudaGraphNodeGetType(emptyNode,  &t));
        ASSERT(t == cudaGraphNodeTypeEmpty,  "NodeGetType: emptyNode");
        CHECK(cudaGraphNodeGetType(kernelNode, &t));
        ASSERT(t == cudaGraphNodeTypeKernel, "NodeGetType: kernelNode");
        CHECK(cudaGraphNodeGetType(memcpyH2D, &t));
        ASSERT(t == cudaGraphNodeTypeMemcpy, "NodeGetType: memcpyH2D");
        CHECK(cudaGraphNodeGetType(memsetNode, &t));
        ASSERT(t == cudaGraphNodeTypeMemset, "NodeGetType: memsetNode");
        PASS("GraphNodeGetType");
    }

    // TEST 12: GraphNodeGetDependencies
    {
        size_t n = 0;
        CHECK(cudaGraphNodeGetDependencies(kernelNode, nullptr, &n));
        ASSERT(n == 1, "GraphNodeGetDependencies: kernelNode should have 1 dep");
        cudaGraphNode_t dep;
        CHECK(cudaGraphNodeGetDependencies(kernelNode, &dep, &n));
        ASSERT(dep == memcpyH2D, "GraphNodeGetDependencies: dep should be memcpyH2D");
        PASS("GraphNodeGetDependencies");
    }

    // TEST 13: GraphNodeGetDependentNodes
    {
        size_t n = 0;
        CHECK(cudaGraphNodeGetDependentNodes(emptyNode, nullptr, &n));
        ASSERT(n == 2, "GraphNodeGetDependentNodes: emptyNode should have 2 dependents");
        std::vector<cudaGraphNode_t> deps(n);
        CHECK(cudaGraphNodeGetDependentNodes(emptyNode, deps.data(), &n));
        PASS("GraphNodeGetDependentNodes");
    }

    // TEST 14: GraphRemoveDependencies  (emptyNode→memsetNode)
    //          After removal memsetNode becomes a second root; then restore.
    {
        CHECK(cudaGraphRemoveDependencies(graph, &emptyNode, &memsetNode, 1));
        size_t nRoots = 0;
        CHECK(cudaGraphGetRootNodes(graph, nullptr, &nRoots));
        ASSERT(nRoots == 2, "GraphRemoveDependencies: expected 2 roots after removal");
        // restore
        CHECK(cudaGraphAddDependencies(graph, &emptyNode, &memsetNode, 1));
        PASS("GraphRemoveDependencies");
    }

    // TEST 15: GraphKernelNodeGetParams / SetParams
    {
        cudaKernelNodeParams outKP = {};
        CHECK(cudaGraphKernelNodeGetParams(kernelNode, &outKP));
        ASSERT(outKP.func == (void*)doubleValues, "KernelNodeGetParams: wrong func ptr");
        // Set the same params back – should be a no-op
        CHECK(cudaGraphKernelNodeSetParams(kernelNode, &outKP));
        PASS("GraphKernelNodeGetParams / SetParams");
    }

    // TEST 16: GraphMemcpyNodeGetParams
    {
        cudaMemcpy3DParms mp = {};
        CHECK(cudaGraphMemcpyNodeGetParams(memcpyH2D, &mp));
        PASS("GraphMemcpyNodeGetParams");
    }

    // TEST 17: GraphMemsetNodeGetParams / SetParams
    {
        cudaMemsetParams outMSP = {};
        CHECK(cudaGraphMemsetNodeGetParams(memsetNode, &outMSP));
        ASSERT(outMSP.value == 0, "MemsetNodeGetParams: value should be 0");
        // Temporarily change value, then restore
        outMSP.value = 0xAB;
        CHECK(cudaGraphMemsetNodeSetParams(memsetNode, &outMSP));
        outMSP.value = 0;
        CHECK(cudaGraphMemsetNodeSetParams(memsetNode, &outMSP));
        PASS("GraphMemsetNodeGetParams / SetParams");
    }

    // -----------------------------------------------------------------------
    // Instantiation / execution tests
    // -----------------------------------------------------------------------

    // TEST 18: GraphInstantiate
    cudaGraphExec_t graphExec;
    CHECK(cudaGraphInstantiate(&graphExec, graph, nullptr, nullptr, 0));
    PASS("GraphInstantiate");

    // TEST 19: GraphUpload
    CHECK(cudaGraphUpload(graphExec, stream));
    PASS("GraphUpload");

    // TEST 20: GraphLaunch + correctness check
    CHECK(cudaGraphLaunch(graphExec, stream));
    CHECK(cudaStreamSynchronize(stream));
    {
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (h_output[i] != (i + 1) * 2.0f) { ok = false; break; }
        }
        ASSERT(ok, "GraphLaunch: output values incorrect");
    }
    PASS("GraphLaunch (result verified: input[i]*(2) == output[i])");

    // TEST 21: GraphInstantiateWithFlags (separate exec, flags=0)
    {
        cudaGraphExec_t execFlags;
        CHECK(cudaGraphInstantiateWithFlags(&execFlags, graph, 0));
        CHECK(cudaGraphLaunch(execFlags, stream));
        CHECK(cudaStreamSynchronize(stream));
        CHECK(cudaGraphExecDestroy(execFlags));
        PASS("GraphInstantiateWithFlags");
    }

    // TEST 22: GraphExecGetFlags
    {
        unsigned long long flags = 0xDEAD;
        CHECK(cudaGraphExecGetFlags(graphExec, &flags));
        PASS("GraphExecGetFlags");
    }

    // TEST 23: GraphExecUpdate (update exec from same unmodified graph – should succeed)
    {
        cudaGraphExecUpdateResultInfo info = {};
        cudaError_t err = cudaGraphExecUpdate(graphExec, graph, &info);
        if (err != cudaSuccess || info.result != cudaGraphExecUpdateSuccess) {
            FAIL("GraphExecUpdate");
        }
        PASS("GraphExecUpdate");
    }

    // TEST 24: GraphNodeSetEnabled / GraphNodeGetEnabled
    {
        unsigned int enabled = 0xFF;
        CHECK(cudaGraphNodeGetEnabled(graphExec, memsetNode, &enabled));
        ASSERT(enabled == 1, "GraphNodeGetEnabled: should start enabled");
        CHECK(cudaGraphNodeSetEnabled(graphExec, memsetNode, 0));
        CHECK(cudaGraphNodeGetEnabled(graphExec, memsetNode, &enabled));
        ASSERT(enabled == 0, "GraphNodeSetEnabled: should now be disabled");
        CHECK(cudaGraphNodeSetEnabled(graphExec, memsetNode, 1));
        PASS("GraphNodeSetEnabled / GraphNodeGetEnabled");
    }

    // -----------------------------------------------------------------------
    // Clone-related tests
    // -----------------------------------------------------------------------

    // TEST 25: GraphClone
    cudaGraph_t clonedGraph;
    CHECK(cudaGraphClone(&clonedGraph, graph));
    PASS("GraphClone");

    // TEST 26: GraphNodeFindInClone
    {
        cudaGraphNode_t clonedKernel;
        CHECK(cudaGraphNodeFindInClone(&clonedKernel, kernelNode, clonedGraph));
        cudaGraphNodeType t;
        CHECK(cudaGraphNodeGetType(clonedKernel, &t));
        ASSERT(t == cudaGraphNodeTypeKernel, "GraphNodeFindInClone: wrong node type");
        PASS("GraphNodeFindInClone");
    }

    // TEST 27: GraphAddChildGraphNode / GraphChildGraphNodeGetGraph
    {
        cudaGraph_t parentGraph;
        CHECK(cudaGraphCreate(&parentGraph, 0));

        cudaGraphNode_t childNode;
        CHECK(cudaGraphAddChildGraphNode(&childNode, parentGraph, nullptr, 0, clonedGraph));
        PASS("GraphAddChildGraphNode");

        cudaGraph_t retrieved;
        CHECK(cudaGraphChildGraphNodeGetGraph(childNode, &retrieved));
        PASS("GraphChildGraphNodeGetGraph");

        CHECK(cudaGraphDestroy(parentGraph));
    }

    // TEST 28: GraphDestroyNode (remove memsetNode from clonedGraph)
    {
        // Find the memset node in the clone and destroy it
        size_t n = 0;
        CHECK(cudaGraphGetNodes(clonedGraph, nullptr, &n));
        std::vector<cudaGraphNode_t> nodes(n);
        CHECK(cudaGraphGetNodes(clonedGraph, nodes.data(), &n));

        for (auto& node : nodes) {
            cudaGraphNodeType t;
            CHECK(cudaGraphNodeGetType(node, &t));
            if (t == cudaGraphNodeTypeMemset) {
                CHECK(cudaGraphDestroyNode(node));
                break;
            }
        }

        size_t nAfter = 0;
        CHECK(cudaGraphGetNodes(clonedGraph, nullptr, &nAfter));
        ASSERT(nAfter == n - 1, "GraphDestroyNode: node count should decrease by 1");
        PASS("GraphDestroyNode");
    }

    // -----------------------------------------------------------------------
    // Cleanup
    // -----------------------------------------------------------------------
    CHECK(cudaGraphExecDestroy(graphExec));
    PASS("GraphExecDestroy");
    CHECK(cudaGraphDestroy(clonedGraph));
    CHECK(cudaGraphDestroy(graph));
    cudaFree(d_buf);
    cudaFreeHost(h_input);
    cudaFreeHost(h_output);
    cudaStreamDestroy(stream);

    std::cout << "\nAll CUDA Graph API tests passed!\n";
    return 0;
}
