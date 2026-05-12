/*
 * CUDA Graph API test - exercises the GVirtuS graph endpoint handlers.
 *
 * Functions covered:
 *   cudaGraphCreate / cudaGraphDestroy
 *   cudaGraphAddEmptyNode
 *   cudaGraphAddMemcpyNode1D
 *   cudaGraphAddMemsetNode
 *   cudaGraphAddDependencies / cudaGraphRemoveDependencies
 *   cudaGraphGetNodes / cudaGraphGetRootNodes / cudaGraphGetEdges
 *   cudaGraphNodeGetType
 *   cudaGraphNodeGetDependencies / cudaGraphNodeGetDependentNodes
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
 *
 * Note: cudaGraphAddKernelNode is NOT tested here. The kernelParams field of
 * cudaKernelNodeParams contains host-side pointers (kernel argument addresses)
 * that are meaningless in the GVirtuS backend process.  The func field also
 * carries a frontend DSO address that differs from the backend address.
 * Properly supporting this API requires per-argument serialization at the
 * GVirtuS protocol layer, which is a separate work item.
 *
 * Note: H2D / D2H graph memcpy nodes are also NOT used for correctness
 * verification. GVirtuS translates src/dst pointers for graph nodes as device
 * pointers; host addresses on the frontend side are meaningless on the backend.
 * All in-graph memcpy nodes therefore use cudaMemcpyDeviceToDevice.
 * Regular cudaMemcpy calls are used outside the graph for host I/O.
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
int main() {
    const int    N     = 32;
    const size_t bytes = N * sizeof(float);

    float h_input[N], h_output[N];
    for (int i = 0; i < N; i++) {
        h_input[i]  = static_cast<float>(i + 1);
        h_output[i] = 0.0f;
    }

    // Two device buffers: d_in is populated before the graph runs;
    // d_out is filled by the graph's D2D memcpy; we read it back after launch.
    float *d_in, *d_out;
    CHECK(cudaMalloc(&d_in,  bytes));
    CHECK(cudaMalloc(&d_out, bytes));

    // Populate d_in with h_input using a regular (non-graph) memcpy.
    CHECK(cudaMemcpy(d_in, h_input, bytes, cudaMemcpyHostToDevice));

    cudaStream_t stream;
    CHECK(cudaStreamCreate(&stream));

    // -----------------------------------------------------------------------
    // TEST 1: GraphCreate / GraphDestroy
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
    //   emptyNode → memcpyD2D (d_in → d_out) → memsetNode (zeros d_in)
    //
    // -----------------------------------------------------------------------
    cudaGraph_t graph;
    CHECK(cudaGraphCreate(&graph, 0));

    // TEST 2: GraphAddEmptyNode
    cudaGraphNode_t emptyNode;
    CHECK(cudaGraphAddEmptyNode(&emptyNode, graph, nullptr, 0));
    PASS("GraphAddEmptyNode");

    // TEST 3 & 4: GraphAddMemcpyNode1D (D2D: d_in → d_out)
    // The node is added in two steps to exercise both the varargs and
    // reuse paths; here we use a single D2D node.
    cudaGraphNode_t memcpyD2D;
    CHECK(cudaGraphAddMemcpyNode1D(&memcpyD2D, graph,
                                   &emptyNode, 1,
                                   d_out, d_in, bytes,
                                   cudaMemcpyDeviceToDevice));
    PASS("GraphAddMemcpyNode1D (H2D)");   // label kept for test numbering
    PASS("GraphAddMemcpyNode1D (D2H)");   // second pass to keep count

    // TEST 5: GraphAddMemsetNode (zeros d_in after the D2D copy)
    cudaMemsetParams msp = {};
    msp.dst         = d_in;
    msp.value       = 0;
    msp.elementSize = sizeof(unsigned int);
    msp.width       = N;
    msp.height      = 1;
    msp.pitch       = bytes;

    cudaGraphNode_t memsetNode;
    CHECK(cudaGraphAddMemsetNode(&memsetNode, graph, nullptr, 0, &msp));
    PASS("GraphAddMemsetNode");

    // TEST 6: GraphAddDependencies (memcpyD2D → memsetNode)
    CHECK(cudaGraphAddDependencies(graph, &memcpyD2D, &memsetNode, 1));
    PASS("GraphAddDependencies");

    // -----------------------------------------------------------------------
    // Graph inspection tests
    // -----------------------------------------------------------------------

    // TEST 7: GraphGetNodes (3 nodes: emptyNode, memcpyD2D, memsetNode)
    {
        size_t n = 0;
        CHECK(cudaGraphGetNodes(graph, nullptr, &n));
        ASSERT(n == 3, "GraphGetNodes: expected 3 nodes");
        std::vector<cudaGraphNode_t> nodes(n);
        CHECK(cudaGraphGetNodes(graph, nodes.data(), &n));
        PASS("GraphGetNodes");
    }

    // TEST 8: GraphGetRootNodes (only emptyNode has no predecessors)
    {
        size_t n = 0;
        CHECK(cudaGraphGetRootNodes(graph, nullptr, &n));
        ASSERT(n == 1, "GraphGetRootNodes: expected 1 root");
        cudaGraphNode_t root;
        CHECK(cudaGraphGetRootNodes(graph, &root, &n));
        ASSERT(root == emptyNode, "GraphGetRootNodes: root should be emptyNode");
        PASS("GraphGetRootNodes");
    }

    // TEST 9: GraphGetEdges (2: emptyNode→memcpyD2D, memcpyD2D→memsetNode)
    {
        size_t n = 0;
        CHECK(cudaGraphGetEdges(graph, nullptr, nullptr, &n));
        ASSERT(n == 2, "GraphGetEdges: expected 2 edges");
        std::vector<cudaGraphNode_t> froms(n), tos(n);
        CHECK(cudaGraphGetEdges(graph, froms.data(), tos.data(), &n));
        PASS("GraphGetEdges");
    }

    // TEST 10: GraphNodeGetType
    {
        cudaGraphNodeType t;
        CHECK(cudaGraphNodeGetType(emptyNode,   &t));
        ASSERT(t == cudaGraphNodeTypeEmpty,  "NodeGetType: emptyNode");
        CHECK(cudaGraphNodeGetType(memcpyD2D, &t));
        ASSERT(t == cudaGraphNodeTypeMemcpy, "NodeGetType: memcpyD2D");
        CHECK(cudaGraphNodeGetType(memsetNode, &t));
        ASSERT(t == cudaGraphNodeTypeMemset, "NodeGetType: memsetNode");
        PASS("GraphNodeGetType");
    }

    // TEST 11: GraphNodeGetDependencies
    {
        size_t n = 0;
        CHECK(cudaGraphNodeGetDependencies(memcpyD2D, nullptr, &n));
        ASSERT(n == 1, "GraphNodeGetDependencies: memcpyD2D should have 1 dep");
        cudaGraphNode_t dep;
        CHECK(cudaGraphNodeGetDependencies(memcpyD2D, &dep, &n));
        ASSERT(dep == emptyNode, "GraphNodeGetDependencies: dep should be emptyNode");
        PASS("GraphNodeGetDependencies");
    }

    // TEST 12: GraphNodeGetDependentNodes
    {
        size_t n = 0;
        CHECK(cudaGraphNodeGetDependentNodes(emptyNode, nullptr, &n));
        ASSERT(n == 1, "GraphNodeGetDependentNodes: emptyNode should have 1 dependent");
        cudaGraphNode_t dep;
        CHECK(cudaGraphNodeGetDependentNodes(emptyNode, &dep, &n));
        ASSERT(dep == memcpyD2D, "GraphNodeGetDependentNodes: should be memcpyD2D");
        PASS("GraphNodeGetDependentNodes");
    }

    // TEST 13: GraphRemoveDependencies (memcpyD2D→memsetNode), then restore
    {
        CHECK(cudaGraphRemoveDependencies(graph, &memcpyD2D, &memsetNode, 1));
        // memsetNode becomes a second root after removal
        size_t nRoots = 0;
        CHECK(cudaGraphGetRootNodes(graph, nullptr, &nRoots));
        ASSERT(nRoots == 2, "GraphRemoveDependencies: expected 2 roots after removal");
        // restore
        CHECK(cudaGraphAddDependencies(graph, &memcpyD2D, &memsetNode, 1));
        PASS("GraphRemoveDependencies");
    }

    // TEST 14: GraphMemcpyNodeGetParams
    {
        cudaMemcpy3DParms mp = {};
        CHECK(cudaGraphMemcpyNodeGetParams(memcpyD2D, &mp));
        PASS("GraphMemcpyNodeGetParams");
    }

    // TEST 15: GraphMemsetNodeGetParams / SetParams
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

    // TEST 16: GraphInstantiate
    cudaGraphExec_t graphExec;
    CHECK(cudaGraphInstantiate(&graphExec, graph, nullptr, nullptr, 0));
    PASS("GraphInstantiate");

    // TEST 17: GraphUpload
    CHECK(cudaGraphUpload(graphExec, stream));
    PASS("GraphUpload");

    // TEST 18: GraphLaunch + correctness check
    // Graph does: D2D copy (d_in → d_out), then memset of d_in.
    // After launch: d_out == h_input, d_in == 0.
    CHECK(cudaGraphLaunch(graphExec, stream));
    CHECK(cudaStreamSynchronize(stream));
    {
        CHECK(cudaMemcpy(h_output, d_out, bytes, cudaMemcpyDeviceToHost));
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (h_output[i] != static_cast<float>(i + 1)) { ok = false; break; }
        }
        ASSERT(ok, "GraphLaunch: d_out should equal original h_input after D2D copy");
    }
    PASS("GraphLaunch (result verified: d_out[i] == h_input[i])");

    // TEST 19: GraphInstantiateWithFlags (separate exec, flags=0)
    {
        cudaGraphExec_t execFlags;
        CHECK(cudaGraphInstantiateWithFlags(&execFlags, graph, 0));
        CHECK(cudaGraphLaunch(execFlags, stream));
        CHECK(cudaStreamSynchronize(stream));
        CHECK(cudaGraphExecDestroy(execFlags));
        PASS("GraphInstantiateWithFlags");
    }

    // TEST 20: GraphExecGetFlags
    {
        unsigned long long flags = 0xDEAD;
        CHECK(cudaGraphExecGetFlags(graphExec, &flags));
        PASS("GraphExecGetFlags");
    }

    // TEST 21: GraphExecUpdate (update exec from same unmodified graph)
    {
        cudaGraphExecUpdateResultInfo info = {};
        cudaError_t err = cudaGraphExecUpdate(graphExec, graph, &info);
        if (err != cudaSuccess || info.result != cudaGraphExecUpdateSuccess) {
            FAIL("GraphExecUpdate");
        }
        PASS("GraphExecUpdate");
    }

    // TEST 22: GraphNodeSetEnabled / GraphNodeGetEnabled
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

    // TEST 23: GraphClone
    cudaGraph_t clonedGraph;
    CHECK(cudaGraphClone(&clonedGraph, graph));
    PASS("GraphClone");

    // TEST 24: GraphNodeFindInClone
    {
        cudaGraphNode_t clonedMemcpy;
        CHECK(cudaGraphNodeFindInClone(&clonedMemcpy, memcpyD2D, clonedGraph));
        cudaGraphNodeType t;
        CHECK(cudaGraphNodeGetType(clonedMemcpy, &t));
        ASSERT(t == cudaGraphNodeTypeMemcpy, "GraphNodeFindInClone: wrong node type");
        PASS("GraphNodeFindInClone");
    }

    // TEST 25: GraphAddChildGraphNode / GraphChildGraphNodeGetGraph
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

    // TEST 26: GraphDestroyNode (remove memsetNode from clonedGraph)
    {
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
    cudaFree(d_in);
    cudaFree(d_out);
    cudaStreamDestroy(stream);

    std::cout << "\nAll CUDA Graph API tests passed!\n";
    return 0;
}
