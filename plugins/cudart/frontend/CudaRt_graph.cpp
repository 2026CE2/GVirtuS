/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Written By: Theodoros Aslanidis <theodoros.aslanidis@ucdconnect.ie>,
 *             Department of Computer Science, University College Dublin
 *
 *             Ting-Hui Cheng <tinghc@es.aau.dk>
 *             Department of Electronic Systems, Aalborg University
 */

#include "CudaRt.h"

using namespace std;

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphGetNodes(cudaGraph_t graph,
                                                            cudaGraphNode_t* nodes,
                                                            size_t* numNodes) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddHostPointerForArguments(nodes);
    CudaRtFrontend::Execute("cudaGraphGetNodes");

    if (CudaRtFrontend::Success()) {
        *numNodes = CudaRtFrontend::GetOutputVariable<size_t>();
        // cout << "Get a node for graph." << endl;
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecDestroy(cudaGraphExec_t graphExec) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graphExec);
    CudaRtFrontend::Execute("cudaGraphExecDestroy");
    // cout << "Destroy graph execution." << endl;
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphInstantiate(cudaGraphExec_t* pGraphExec,
                                                               cudaGraph_t graph,
                                                               unsigned long long flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(flags);
    CudaRtFrontend::Execute("cudaGraphInstantiate");

    if (CudaRtFrontend::Success()) {
        *pGraphExec = CudaRtFrontend::GetOutputVariable<cudaGraphExec_t>();
        // cout << "Creates an executable graph from a graph." << endl;
    }
    return CudaRtFrontend::GetExitCode();
}

// TODO: needs testing
extern "C" __host__ cudaError_t CUDARTAPI cudaGraphInstantiateWithFlags(cudaGraphExec_t* pGraphExec,
                                                                        cudaGraph_t graph,
                                                                        unsigned long long flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(flags);
    CudaRtFrontend::Execute("cudaGraphInstantiateWithFlags");
    // cout << "Graph:" << graph << endl;                                                                           
    if (CudaRtFrontend::Success()) {
        *pGraphExec = CudaRtFrontend::GetOutputVariable<cudaGraphExec_t>();
        // cout << "Creates an executable graph from a graph." << endl;
    }
    return CudaRtFrontend::GetExitCode();
}

// TODO: needs testing
extern "C" __host__ cudaError_t CUDARTAPI cudaGraphDebugDotPrint(cudaGraph_t graph,
                                                                 const char* path,
                                                                 unsigned int flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddStringForArguments(path);
    CudaRtFrontend::AddVariableForArguments<unsigned int>(flags);
    CudaRtFrontend::Execute("cudaGraphDebugDotPrint");

    return CudaRtFrontend::GetExitCode();
}


extern "C" __host__ cudaError_t CUDARTAPI cudaGraphLaunch(cudaGraphExec_t graphExec,
                                                          cudaStream_t stream) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graphExec);
    CudaRtFrontend::AddDevicePointerForArguments(stream);
    CudaRtFrontend::Execute("cudaGraphLaunch");
    // cout << "Graph Launch" << endl;                                                        
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphCreate(cudaGraph_t* pGraph, unsigned int flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddVariableForArguments(flags);
    // cout << "Graph is Create" << *pGraph << endl;
    CudaRtFrontend::Execute("cudaGraphCreate");
    
    if (CudaRtFrontend::Success()) *pGraph = CudaRtFrontend::GetOutputVariable<cudaGraph_t>();
    
    return CudaRtFrontend::GetExitCode();
}


extern "C" __host__ cudaError_t CUDARTAPI cudaGraphDestroy(cudaGraph_t graph) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::Execute("cudaGraphDestroy");
    // cout << "Graph is Destroy" << endl;
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphUpload(cudaGraphExec_t graphExec, cudaStream_t stream) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graphExec);
    CudaRtFrontend::AddDevicePointerForArguments(stream);
    CudaRtFrontend::Execute("cudaGraphUpload");

    return CudaRtFrontend::GetExitCode();
}

// Extensions of the CUDA Graph APIs 

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphClone(cudaGraph_t* pGraphClone ,cudaGraph_t originalGraph) {

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(originalGraph);
    CudaRtFrontend::Execute("cudaGraphClone");
    

    if (CudaRtFrontend::Success()){

        *pGraphClone = CudaRtFrontend::GetOutputVariable<cudaGraph_t>();

    }
    return CudaRtFrontend::GetExitCode();



}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddDependencies(cudaGraph_t graph, const cudaGraphNode_t* from, const cudaGraphNode_t* to,/* const cudaGraphEdgeData* edgeData,*/ size_t numDependencies){

    /*NOTE cudaGraphEdgeData is a v2 implementation of this instance. if the cuda version gets update then it can be implemented. */

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);

    //Could add if condition depending on size of number of dependencies 
    
    
    CudaRtFrontend::AddHostPointerForArguments(from,numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(to,numDependencies);
    
    CudaRtFrontend::Execute("cudaGraphAddDependencies");

    return CudaRtFrontend::GetExitCode();




}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphRemoveDependencies(cudaGraph_t graph, const cudaGraphNode_t* from, const cudaGraphNode_t* to,/* const cudaGraphEdgeData* edgeData,*/ size_t numDependencies){

    /*NOTE cudaGraphEdgeData is a v2 implementation of this instance. if the cuda version gets update then it can be implemented. */

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);

    //Could add if condition depending on size of number of dependencies 
    
    
    CudaRtFrontend::AddHostPointerForArguments(from,numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(to,numDependencies);
    
    CudaRtFrontend::Execute("cudaGraphRemoveDependencies");

    return CudaRtFrontend::GetExitCode();

}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphGetEdges(cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to, size_t* numEdges){
    //Edge data can be introduced as a v2 implementation. Depends on cuda version
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);

    size_t requested = (numEdges ? *numEdges : 0);
    CudaRtFrontend::AddVariableForArguments(requested);

    //output buffers
    CudaRtFrontend::AddHostPointerForArguments(from,requested);
    CudaRtFrontend::AddHostPointerForArguments(to,requested);

    CudaRtFrontend::Execute("cudaGraphGetEdges");
    if (CudaRtFrontend::Success() && numEdges){
        *numEdges = CudaRtFrontend::GetOutputVariable<size_t>();
    }
    return CudaRtFrontend::GetExitCode();

}


extern "C" __host__ cudaError_t CUDARTAPI cudaGraphGetRootNodes(cudaGraph_t graph,cudaGraphNode_t* pRootNodes, size_t* pNumRootNodes){

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);


    size_t requested = (pNumRootNodes ? *pNumRootNodes : 0);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(pRootNodes, requested);

    CudaRtFrontend::Execute("cudaGraphGetRootNodes");

    if(CudaRtFrontend::Success() && pNumRootNodes){
        *pNumRootNodes = CudaRtFrontend::GetOutputVariable<size_t>();



    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphDestroyNode(cudaGraphNode_t node){
    CudaRtFrontend::Prepare();

    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphDestroyNode");

    return CudaRtFrontend::GetExitCode();



}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetType(cudaGraphNode_t node, cudaGraphNodeType* pType ){
    CudaRtFrontend::Prepare();

    CudaRtFrontend::AddDevicePointerForArguments(node);

    CudaRtFrontend::Execute("cudaGraphNodeGetType");
    if (CudaRtFrontend::Success()){

        *pType = CudaRtFrontend::GetOutputVariable<cudaGraphNodeType>();
            //could check if pType is null pointer
    }

    return CudaRtFrontend::GetExitCode();

}




extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeFindInClone(cudaGraphNode_t* pNode,
                                                                    cudaGraphNode_t originalNode,
                                                                    cudaGraph_t clonedGraph) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(originalNode);
    CudaRtFrontend::AddDevicePointerForArguments(clonedGraph);
    CudaRtFrontend::Execute("cudaGraphNodeFindInClone");

    if (CudaRtFrontend::Success() && pNode) {
        *pNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddEmptyNode(cudaGraphNode_t* pGraphNode,
                                                                 cudaGraph_t graph,
                                                                 const cudaGraphNode_t* pDependencies,
                                                                 size_t numDependencies) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::Execute("cudaGraphAddEmptyNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddChildGraphNode(cudaGraphNode_t* pGraphNode,
                                                                      cudaGraph_t graph,
                                                                      const cudaGraphNode_t* pDependencies,
                                                                      size_t numDependencies,
                                                                      cudaGraph_t childGraph) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(childGraph);
    CudaRtFrontend::Execute("cudaGraphAddChildGraphNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphChildGraphNodeGetGraph(cudaGraphNode_t node,
                                                                           cudaGraph_t* pGraph) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphChildGraphNodeGetGraph");

    if (CudaRtFrontend::Success() && pGraph) {
        *pGraph = CudaRtFrontend::GetOutputVariable<cudaGraph_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddKernelNode(cudaGraphNode_t* pGraphNode,
                                                                  cudaGraph_t graph,
                                                                  const cudaGraphNode_t* pDependencies,
                                                                  size_t numDependencies,
                                                                  const cudaKernelNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphAddKernelNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddHostNode(cudaGraphNode_t* pGraphNode,
                                                                cudaGraph_t graph,
                                                                const cudaGraphNode_t* pDependencies,
                                                                size_t numDependencies,
                                                                const cudaHostNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphAddHostNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemcpyNode(cudaGraphNode_t* pGraphNode,
                                                                  cudaGraph_t graph,
                                                                  const cudaGraphNode_t* pDependencies,
                                                                  size_t numDependencies,
                                                                  const cudaMemcpy3DParms* pCopyParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pCopyParams);
    CudaRtFrontend::Execute("cudaGraphAddMemcpyNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemcpyNode1D(cudaGraphNode_t* pGraphNode,
                                                                    cudaGraph_t graph,
                                                                    const cudaGraphNode_t* pDependencies,
                                                                    size_t numDependencies,
                                                                    void* dst,
                                                                    const void* src,
                                                                    size_t count,
                                                                    cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphAddMemcpyNode1D");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemcpyNodeFromSymbol(cudaGraphNode_t* pGraphNode,
                                                                            cudaGraph_t graph,
                                                                            const cudaGraphNode_t* pDependencies,
                                                                            size_t numDependencies,
                                                                            void* dst,
                                                                            const void* symbol,
                                                                            size_t count,
                                                                            size_t offset,
                                                                            cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphAddMemcpyNodeFromSymbol");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemcpyNodeToSymbol(cudaGraphNode_t* pGraphNode,
                                                                          cudaGraph_t graph,
                                                                          const cudaGraphNode_t* pDependencies,
                                                                          size_t numDependencies,
                                                                          const void* symbol,
                                                                          const void* src,
                                                                          size_t count,
                                                                          size_t offset,
                                                                          cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphAddMemcpyNodeToSymbol");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemsetNode(cudaGraphNode_t* pGraphNode,
                                                                  cudaGraph_t graph,
                                                                  const cudaGraphNode_t* pDependencies,
                                                                  size_t numDependencies,
                                                                  const cudaMemsetParams* pMemsetParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pMemsetParams);
    CudaRtFrontend::Execute("cudaGraphAddMemsetNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddEventRecordNode(cudaGraphNode_t* pGraphNode,
                                                                       cudaGraph_t graph,
                                                                       const cudaGraphNode_t* pDependencies,
                                                                       size_t numDependencies,
                                                                       cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphAddEventRecordNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddEventWaitNode(cudaGraphNode_t* pGraphNode,
                                                                     cudaGraph_t graph,
                                                                     const cudaGraphNode_t* pDependencies,
                                                                     size_t numDependencies,
                                                                     cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphAddEventWaitNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI
cudaGraphAddExternalSemaphoresSignalNode(
    cudaGraphNode_t* pGraphNode, cudaGraph_t graph, const cudaGraphNode_t* pDependencies,
    size_t numDependencies, const cudaExternalSemaphoreSignalNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphAddExternalSemaphoresSignalNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI
cudaGraphAddExternalSemaphoresWaitNode(
    cudaGraphNode_t* pGraphNode, cudaGraph_t graph, const cudaGraphNode_t* pDependencies,
    size_t numDependencies, const cudaExternalSemaphoreWaitNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphAddExternalSemaphoresWaitNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemAllocNode(
    cudaGraphNode_t* pGraphNode, cudaGraph_t graph, const cudaGraphNode_t* pDependencies,
    size_t numDependencies, cudaMemAllocNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphAddMemAllocNode");

    if (CudaRtFrontend::Success()) {
        if (pGraphNode) {
            *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
        }
        if (nodeParams) {
            *nodeParams = *CudaRtFrontend::GetOutputHostPointer<cudaMemAllocNodeParams>();
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddMemFreeNode(cudaGraphNode_t* pGraphNode,
                                                                   cudaGraph_t graph,
                                                                   const cudaGraphNode_t* pDependencies,
                                                                   size_t numDependencies,
                                                                   void* dptr) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddDevicePointerForArguments(dptr);
    CudaRtFrontend::Execute("cudaGraphAddMemFreeNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddNode(cudaGraphNode_t* pGraphNode,
                                                            cudaGraph_t graph,
                                                            const cudaGraphNode_t* pDependencies,
                                                            size_t numDependencies,
                                                            cudaGraphNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphAddNode");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddNode_v2(cudaGraphNode_t* pGraphNode,
                                                               cudaGraph_t graph,
                                                               const cudaGraphNode_t* pDependencies,
                                                               const cudaGraphEdgeData* dependencyData,
                                                               size_t numDependencies,
                                                               cudaGraphNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(dependencyData, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphAddNode_v2");

    if (CudaRtFrontend::Success() && pGraphNode) {
        *pGraphNode = CudaRtFrontend::GetOutputVariable<cudaGraphNode_t>();
    }
    return CudaRtFrontend::GetExitCode();
}


extern "C" __host__ cudaError_t CUDARTAPI cudaGraphKernelNodeGetParams(
    cudaGraphNode_t node, cudaKernelNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphKernelNodeGetParams");

    if (CudaRtFrontend::Success() && pNodeParams) {
        *pNodeParams = CudaRtFrontend::GetOutputVariable<cudaKernelNodeParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphKernelNodeSetParams(
    cudaGraphNode_t node, const cudaKernelNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphKernelNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphKernelNodeGetAttribute(
    cudaGraphNode_t hNode, cudaKernelNodeAttrID attr, cudaKernelNodeAttrValue* value_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddVariableForArguments(attr);
    CudaRtFrontend::Execute("cudaGraphKernelNodeGetAttribute");

    if (CudaRtFrontend::Success() && value_out) {
        *value_out = CudaRtFrontend::GetOutputVariable<cudaKernelNodeAttrValue>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphKernelNodeSetAttribute(
    cudaGraphNode_t hNode, cudaKernelNodeAttrID attr, const cudaKernelNodeAttrValue* value) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddVariableForArguments(attr);
    CudaRtFrontend::AddHostPointerForArguments(value);
    CudaRtFrontend::Execute("cudaGraphKernelNodeSetAttribute");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphKernelNodeCopyAttributes(
    cudaGraphNode_t dst, cudaGraphNode_t src) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::Execute("cudaGraphKernelNodeCopyAttributes");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphHostNodeGetParams(
    cudaGraphNode_t node, cudaHostNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphHostNodeGetParams");

    if (CudaRtFrontend::Success() && pNodeParams) {
        *pNodeParams = CudaRtFrontend::GetOutputVariable<cudaHostNodeParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphHostNodeSetParams(
    cudaGraphNode_t node, const cudaHostNodeParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphHostNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemcpyNodeGetParams(
    cudaGraphNode_t node, cudaMemcpy3DParms* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphMemcpyNodeGetParams");

    if (CudaRtFrontend::Success() && pNodeParams) {
        *pNodeParams = CudaRtFrontend::GetOutputVariable<cudaMemcpy3DParms>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemcpyNodeSetParams(
    cudaGraphNode_t node, const cudaMemcpy3DParms* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphMemcpyNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemcpyNodeSetParams1D(
    cudaGraphNode_t node, void* dst, const void* src, size_t count, cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphMemcpyNodeSetParams1D");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemcpyNodeSetParamsFromSymbol(
    cudaGraphNode_t node, void* dst, const void* symbol, size_t count, size_t offset,
    cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphMemcpyNodeSetParamsFromSymbol");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemcpyNodeSetParamsToSymbol(
    cudaGraphNode_t node, const void* symbol, const void* src, size_t count, size_t offset,
    cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphMemcpyNodeSetParamsToSymbol");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemsetNodeGetParams(
    cudaGraphNode_t node, cudaMemsetParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphMemsetNodeGetParams");

    if (CudaRtFrontend::Success() && pNodeParams) {
        *pNodeParams = CudaRtFrontend::GetOutputVariable<cudaMemsetParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemsetNodeSetParams(
    cudaGraphNode_t node, const cudaMemsetParams* pNodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);
    CudaRtFrontend::Execute("cudaGraphMemsetNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphEventRecordNodeGetEvent(
    cudaGraphNode_t node, cudaEvent_t* event_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphEventRecordNodeGetEvent");

    if (CudaRtFrontend::Success() && event_out) {
        *event_out = CudaRtFrontend::GetOutputVariable<cudaEvent_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphEventRecordNodeSetEvent(
    cudaGraphNode_t node, cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphEventRecordNodeSetEvent");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphEventWaitNodeGetEvent(
    cudaGraphNode_t node, cudaEvent_t* event_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphEventWaitNodeGetEvent");

    if (CudaRtFrontend::Success() && event_out) {
        *event_out = CudaRtFrontend::GetOutputVariable<cudaEvent_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphEventWaitNodeSetEvent(
    cudaGraphNode_t node, cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphEventWaitNodeSetEvent");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExternalSemaphoresSignalNodeGetParams(
    cudaGraphNode_t hNode, cudaExternalSemaphoreSignalNodeParams* params_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::Execute("cudaGraphExternalSemaphoresSignalNodeGetParams");

    if (CudaRtFrontend::Success() && params_out) {
        *params_out = CudaRtFrontend::GetOutputVariable<cudaExternalSemaphoreSignalNodeParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExternalSemaphoresSignalNodeSetParams(
    cudaGraphNode_t hNode, const cudaExternalSemaphoreSignalNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphExternalSemaphoresSignalNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExternalSemaphoresWaitNodeGetParams(
    cudaGraphNode_t hNode, cudaExternalSemaphoreWaitNodeParams* params_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::Execute("cudaGraphExternalSemaphoresWaitNodeGetParams");

    if (CudaRtFrontend::Success() && params_out) {
        *params_out = CudaRtFrontend::GetOutputVariable<cudaExternalSemaphoreWaitNodeParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExternalSemaphoresWaitNodeSetParams(
    cudaGraphNode_t hNode, const cudaExternalSemaphoreWaitNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphExternalSemaphoresWaitNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemAllocNodeGetParams(
    cudaGraphNode_t node, cudaMemAllocNodeParams* params_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphMemAllocNodeGetParams");

    if (CudaRtFrontend::Success() && params_out) {
        *params_out = CudaRtFrontend::GetOutputVariable<cudaMemAllocNodeParams>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphMemFreeNodeGetParams(
    cudaGraphNode_t node, void* dptr_out) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::Execute("cudaGraphMemFreeNodeGetParams");

    if (CudaRtFrontend::Success() && dptr_out) {
        *static_cast<void**>(dptr_out) = CudaRtFrontend::GetOutputDevicePointer();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeSetParams(
    cudaGraphNode_t node, cudaGraphNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecKernelNodeSetParams( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaKernelNodeParams* pNodeParams){

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);

    CudaRtFrontend::Execute("cudaGraphExecKernelNodeSetParams");
    return CudaRtFrontend::GetExitCode();



}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecMemcpyNodeSetParams ( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaMemcpy3DParms* pNodeParams ){

    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);

    CudaRtFrontend::Execute("cudaGraphExecMemcpyNodeSetParams");
    return CudaRtFrontend::GetExitCode();


}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecMemsetNodeSetParams ( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaMemsetParams* pNodeParams ){
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);

    CudaRtFrontend::Execute("cudaGraphExecMemsetNodeSetParams");
    return CudaRtFrontend::GetExitCode();

}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecHostNodeSetParams ( cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const cudaHostNodeParams* pNodeParams ){
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(pNodeParams);

    CudaRtFrontend::Execute("cudaGraphExecHostNodeSetParams");
    return CudaRtFrontend::GetExitCode();



}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecUpdate ( cudaGraphExec_t hGraphExec, cudaGraph_t hGraph, cudaGraphExecUpdateResultInfo* resultInfo ){
    CudaRtFrontend::Prepare();

    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hGraph);
    CudaRtFrontend::AddHostPointerForArguments(resultInfo);
    CudaRtFrontend::Execute("cudaGraphExecUpdate");
    if (CudaRtFrontend::Success() && resultInfo){

        *resultInfo = CudaRtFrontend::GetOutputVariable<cudaGraphExecUpdateResultInfo>();
    }

    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphAddDependencies_v2(
    cudaGraph_t graph, const cudaGraphNode_t* from, const cudaGraphNode_t* to,
    const cudaGraphEdgeData* edgeData, size_t numDependencies) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(from, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(to, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(edgeData, numDependencies);
    CudaRtFrontend::Execute("cudaGraphAddDependencies_v2");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphRemoveDependencies_v2(
    cudaGraph_t graph, const cudaGraphNode_t* from, const cudaGraphNode_t* to,
    const cudaGraphEdgeData* edgeData, size_t numDependencies) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(from, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(to, numDependencies);
    CudaRtFrontend::AddHostPointerForArguments(edgeData, numDependencies);
    CudaRtFrontend::Execute("cudaGraphRemoveDependencies_v2");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphGetEdges_v2(
    cudaGraph_t graph, cudaGraphNode_t* from, cudaGraphNode_t* to,
    cudaGraphEdgeData* edgeData, size_t* numEdges) {
    size_t requested = numEdges ? *numEdges : 0;
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(from, requested);
    CudaRtFrontend::AddHostPointerForArguments(to, requested);
    CudaRtFrontend::AddHostPointerForArguments(edgeData, requested);
    CudaRtFrontend::Execute("cudaGraphGetEdges_v2");

    if (CudaRtFrontend::Success() && numEdges) {
        *numEdges = CudaRtFrontend::GetOutputVariable<size_t>();
        if (requested > 0 && from && to && edgeData) {
            cudaGraphNode_t* outFrom = CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            cudaGraphNode_t* outTo = CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            cudaGraphEdgeData* outData = CudaRtFrontend::GetOutputHostPointer<cudaGraphEdgeData>(requested);
            for (size_t i = 0; i < requested; ++i) {
                from[i] = outFrom[i];
                to[i] = outTo[i];
                edgeData[i] = outData[i];
            }
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetDependencies(
    cudaGraphNode_t node, cudaGraphNode_t* pDependencies, size_t* pNumDependencies) {
    size_t requested = pNumDependencies ? *pNumDependencies : 0;
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, requested);
    CudaRtFrontend::Execute("cudaGraphNodeGetDependencies");

    if (CudaRtFrontend::Success() && pNumDependencies) {
        *pNumDependencies = CudaRtFrontend::GetOutputVariable<size_t>();
        if (requested > 0 && pDependencies) {
            cudaGraphNode_t* outDeps =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            for (size_t i = 0; i < requested; ++i) pDependencies[i] = outDeps[i];
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetDependencies_v2(
    cudaGraphNode_t node, cudaGraphNode_t* pDependencies, cudaGraphEdgeData* edgeData,
    size_t* pNumDependencies) {
    size_t requested = pNumDependencies ? *pNumDependencies : 0;
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(pDependencies, requested);
    CudaRtFrontend::AddHostPointerForArguments(edgeData, requested);
    CudaRtFrontend::Execute("cudaGraphNodeGetDependencies_v2");

    if (CudaRtFrontend::Success() && pNumDependencies) {
        *pNumDependencies = CudaRtFrontend::GetOutputVariable<size_t>();
        if (requested > 0 && pDependencies && edgeData) {
            cudaGraphNode_t* outDeps =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            cudaGraphEdgeData* outData =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphEdgeData>(requested);
            for (size_t i = 0; i < requested; ++i) {
                pDependencies[i] = outDeps[i];
                edgeData[i] = outData[i];
            }
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetDependentNodes(
    cudaGraphNode_t node, cudaGraphNode_t* pDependentNodes, size_t* pNumDependentNodes) {
    size_t requested = pNumDependentNodes ? *pNumDependentNodes : 0;
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(pDependentNodes, requested);
    CudaRtFrontend::Execute("cudaGraphNodeGetDependentNodes");

    if (CudaRtFrontend::Success() && pNumDependentNodes) {
        *pNumDependentNodes = CudaRtFrontend::GetOutputVariable<size_t>();
        if (requested > 0 && pDependentNodes) {
            cudaGraphNode_t* outNodes =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            for (size_t i = 0; i < requested; ++i) pDependentNodes[i] = outNodes[i];
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetDependentNodes_v2(
    cudaGraphNode_t node, cudaGraphNode_t* pDependentNodes, cudaGraphEdgeData* edgeData,
    size_t* pNumDependentNodes) {
    size_t requested = pNumDependentNodes ? *pNumDependentNodes : 0;
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddVariableForArguments(requested);
    CudaRtFrontend::AddHostPointerForArguments(pDependentNodes, requested);
    CudaRtFrontend::AddHostPointerForArguments(edgeData, requested);
    CudaRtFrontend::Execute("cudaGraphNodeGetDependentNodes_v2");

    if (CudaRtFrontend::Success() && pNumDependentNodes) {
        *pNumDependentNodes = CudaRtFrontend::GetOutputVariable<size_t>();
        if (requested > 0 && pDependentNodes && edgeData) {
            cudaGraphNode_t* outNodes =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphNode_t>(requested);
            cudaGraphEdgeData* outData =
                CudaRtFrontend::GetOutputHostPointer<cudaGraphEdgeData>(requested);
            for (size_t i = 0; i < requested; ++i) {
                pDependentNodes[i] = outNodes[i];
                edgeData[i] = outData[i];
            }
        }
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphInstantiateWithParams(
    cudaGraphExec_t* pGraphExec, cudaGraph_t graph,
    cudaGraphInstantiateParams* instantiateParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddHostPointerForArguments(instantiateParams);
    CudaRtFrontend::Execute("cudaGraphInstantiateWithParams");

    if (CudaRtFrontend::Success() && pGraphExec) {
        *pGraphExec = CudaRtFrontend::GetOutputVariable<cudaGraphExec_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecGetFlags(
    cudaGraphExec_t graphExec, unsigned long long* flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graphExec);
    CudaRtFrontend::Execute("cudaGraphExecGetFlags");

    if (CudaRtFrontend::Success() && flags) {
        *flags = CudaRtFrontend::GetOutputVariable<unsigned long long>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecChildGraphNodeSetParams(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t node, cudaGraph_t childGraph) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(childGraph);
    CudaRtFrontend::Execute("cudaGraphExecChildGraphNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecMemcpyNodeSetParams1D(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t node, void* dst, const void* src,
    size_t count, cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphExecMemcpyNodeSetParams1D");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecMemcpyNodeSetParamsFromSymbol(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t node, void* dst, const void* symbol,
    size_t count, size_t offset, cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddDevicePointerForArguments(dst);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphExecMemcpyNodeSetParamsFromSymbol");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecMemcpyNodeSetParamsToSymbol(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const void* symbol, const void* src,
    size_t count, size_t offset, cudaMemcpyKind kind) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddSymbolForArguments(reinterpret_cast<const char*>(symbol));
    CudaRtFrontend::AddDevicePointerForArguments(src);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(offset);
    CudaRtFrontend::AddVariableForArguments(kind);
    CudaRtFrontend::Execute("cudaGraphExecMemcpyNodeSetParamsToSymbol");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecEventRecordNodeSetEvent(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphExecEventRecordNodeSetEvent");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecEventWaitNodeSetEvent(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, cudaEvent_t event) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddDevicePointerForArguments(event);
    CudaRtFrontend::Execute("cudaGraphExecEventWaitNodeSetEvent");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecExternalSemaphoresSignalNodeSetParams(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode,
    const cudaExternalSemaphoreSignalNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphExecExternalSemaphoresSignalNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecExternalSemaphoresWaitNodeSetParams(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode,
    const cudaExternalSemaphoreWaitNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphExecExternalSemaphoresWaitNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphExecNodeSetParams(
    cudaGraphExec_t graphExec, cudaGraphNode_t node, cudaGraphNodeParams* nodeParams) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graphExec);
    CudaRtFrontend::AddDevicePointerForArguments(node);
    CudaRtFrontend::AddHostPointerForArguments(nodeParams);
    CudaRtFrontend::Execute("cudaGraphExecNodeSetParams");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeGetEnabled(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned int* isEnabled) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::Execute("cudaGraphNodeGetEnabled");

    if (CudaRtFrontend::Success() && isEnabled) {
        *isEnabled = CudaRtFrontend::GetOutputVariable<unsigned int>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphNodeSetEnabled(
    cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned int isEnabled) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(hGraphExec);
    CudaRtFrontend::AddDevicePointerForArguments(hNode);
    CudaRtFrontend::AddVariableForArguments(isEnabled);
    CudaRtFrontend::Execute("cudaGraphNodeSetEnabled");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaDeviceGetGraphMemAttribute(
    int device, cudaGraphMemAttributeType attr, void* value) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddVariableForArguments(device);
    CudaRtFrontend::AddVariableForArguments(attr);
    CudaRtFrontend::Execute("cudaDeviceGetGraphMemAttribute");

    if (CudaRtFrontend::Success() && value) {
        *static_cast<unsigned long long*>(value) =
            CudaRtFrontend::GetOutputVariable<unsigned long long>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaDeviceSetGraphMemAttribute(
    int device, cudaGraphMemAttributeType attr, void* value) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddVariableForArguments(device);
    CudaRtFrontend::AddVariableForArguments(attr);
    CudaRtFrontend::AddVariableForArguments(value ? *static_cast<unsigned long long*>(value) : 0);
    CudaRtFrontend::Execute("cudaDeviceSetGraphMemAttribute");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaDeviceGraphMemTrim(int device) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddVariableForArguments(device);
    CudaRtFrontend::Execute("cudaDeviceGraphMemTrim");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaUserObjectCreate(
    cudaUserObject_t* object_out, void* ptr, cudaHostFn_t destroy,
    unsigned int initialRefcount, unsigned int flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(ptr);
    CudaRtFrontend::AddVariableForArguments(reinterpret_cast<uintptr_t>(destroy));
    CudaRtFrontend::AddVariableForArguments(initialRefcount);
    CudaRtFrontend::AddVariableForArguments(flags);
    CudaRtFrontend::Execute("cudaUserObjectCreate");

    if (CudaRtFrontend::Success() && object_out) {
        *object_out = CudaRtFrontend::GetOutputVariable<cudaUserObject_t>();
    }
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaUserObjectRetain(
    cudaUserObject_t object, unsigned int count) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(object);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::Execute("cudaUserObjectRetain");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaUserObjectRelease(
    cudaUserObject_t object, unsigned int count) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(object);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::Execute("cudaUserObjectRelease");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphRetainUserObject(
    cudaGraph_t graph, cudaUserObject_t object, unsigned int count, unsigned int flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddDevicePointerForArguments(object);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::AddVariableForArguments(flags);
    CudaRtFrontend::Execute("cudaGraphRetainUserObject");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphReleaseUserObject(
    cudaGraph_t graph, cudaUserObject_t object, unsigned int count) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddDevicePointerForArguments(object);
    CudaRtFrontend::AddVariableForArguments(count);
    CudaRtFrontend::Execute("cudaGraphReleaseUserObject");
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaGraphConditionalHandleCreate(
    cudaGraphConditionalHandle* pHandle_out, cudaGraph_t graph,
    unsigned int defaultLaunchValue, unsigned int flags) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddDevicePointerForArguments(graph);
    CudaRtFrontend::AddVariableForArguments(defaultLaunchValue);
    CudaRtFrontend::AddVariableForArguments(flags);
    CudaRtFrontend::Execute("cudaGraphConditionalHandleCreate");

    if (CudaRtFrontend::Success() && pHandle_out) {
        *pHandle_out = CudaRtFrontend::GetOutputVariable<cudaGraphConditionalHandle>();
    }
    return CudaRtFrontend::GetExitCode();
}


