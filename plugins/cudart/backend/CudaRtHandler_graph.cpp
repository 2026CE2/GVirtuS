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
 * Written by: Ting-Hui Cheng <tinghc@es.aau.dk>,
 *             Department of Electronic Systems, Aalborg University, Denmark
 */

#include "CudaRtHandler.h"

#ifndef CUDART_VERSION
#error CUDART_VERSION not defined
#endif

CUDA_ROUTINE_HANDLER(GraphCreate) {
    try {
        cudaGraph_t pGraph;
        unsigned int flags = input_buffer->Get<unsigned int>();
        cudaError_t exit_code = cudaGraphCreate(&pGraph, flags);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraph_t>(pGraph);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphDestroy) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        return std::make_shared<Result>(cudaGraphDestroy(graph));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphGetNodes) {
    try {
        cudaGraph_t pGraph = input_buffer->Get<cudaGraph_t>();
        cudaGraphNode_t* nodes = input_buffer->Assign<cudaGraphNode_t>();
        size_t numNodes;
        cudaError_t exit_code = cudaGraphGetNodes(pGraph, nodes, &numNodes);
        // Debugging output
        // std::cout << "GraphGetNodes " << nodes << " with a size of "
        //     << numNodes << std::endl;
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numNodes);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

// cudaGraphInstantiate signature changed in CUDA 12.
CUDA_ROUTINE_HANDLER(GraphInstantiate) {
    try {
        cudaGraphExec_t pGraphExec;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        unsigned long long flags = input_buffer->Get<unsigned long long>();
        cudaError_t exit_code = cudaGraphInstantiate(&pGraphExec, graph, flags);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphExec_t>(pGraphExec);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphInstantiateWithFlags) {
    try {
        cudaGraphExec_t pGraphExec;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        unsigned long long flags = input_buffer->Get<unsigned long long>();

        cudaError_t exit_code = cudaGraphInstantiateWithFlags(&pGraphExec, graph, flags);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphExec_t>(pGraphExec);
        // std::cout << "execution: " << pGraphExec << " Graph: "<< graph << std::endl;
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

// No Testing
CUDA_ROUTINE_HANDLER(GraphLaunch) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaStream_t stream = input_buffer->Get<cudaStream_t>();
        return std::make_shared<Result>(cudaGraphLaunch(graphExec, stream));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecDestroy) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        return std::make_shared<Result>(cudaGraphExecDestroy(graphExec));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphUpload) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaStream_t stream = input_buffer->Get<cudaStream_t>();
        return std::make_shared<Result>(cudaGraphUpload(graphExec, stream));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphClone) {
    try {
        cudaGraph_t pGraphClone;
        cudaGraph_t originalGraph = input_buffer->Get<cudaGraph_t>();
        cudaError_t exit_code = cudaGraphClone(&pGraphClone,originalGraph);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraph_t>(pGraphClone);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);

    }


}

CUDA_ROUTINE_HANDLER(GraphAddDependencies){
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();

        size_t numDependencies = input_buffer->Get<size_t>();

        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(numDependencies);

        cudaError_t exit_code = cudaGraphAddDependencies(graph,from,to,numDependencies);

        return std::make_shared<Result>(exit_code);



    }catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }



}

CUDA_ROUTINE_HANDLER(GraphRemoveDependencies){
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();

        size_t numDependencies = input_buffer->Get<size_t>();

        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(numDependencies);

        cudaError_t exit_code = cudaGraphRemoveDependencies(graph,from,to,numDependencies);

        return std::make_shared<Result>(exit_code);



    }catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }



}

CUDA_ROUTINE_HANDLER(GraphGetEdges){

    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();

        size_t requested = input_buffer->Get<size_t>();

        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(requested);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(requested);
        size_t numEdges = requested;
        cudaError_t exit_code = cudaGraphGetEdges(graph,from,to,&numEdges);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numEdges);


        return std::make_shared<Result>(exit_code,out);
    }
    catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);

    }

}

CUDA_ROUTINE_HANDLER(GraphGetRootNodes){
    try {cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
    
        size_t requested = input_buffer->Get<size_t>();

        cudaGraphNode_t* pRootNodes = input_buffer->Assign<cudaGraphNode_t>(requested);

        size_t NumRootNodes = requested;

        cudaError_t exit_code = cudaGraphGetRootNodes(graph,pRootNodes,&NumRootNodes);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();

        out->Add<size_t>(NumRootNodes);

        return std::make_shared<Result>(exit_code,out);
    
    
    }
    catch(const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}


CUDA_ROUTINE_HANDLER(GraphDestroyNode){
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
    
        cudaError_t exit_code = cudaGraphDestroyNode(node);

        return std::make_shared<Result>(exit_code);
        
        
    }catch(const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);


    }

}

CUDA_ROUTINE_HANDLER(GraphNodeGetType){
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaGraphNodeType type;
        cudaError_t exit_code = cudaGraphNodeGetType(node,&type);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNodeType>(type);
        return std::make_shared<Result>(exit_code,out);


    }catch(const std::exception& e){
        cerr << e.what() << endl;

        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeFindInClone) {
    try {
        cudaGraphNode_t pNode;
        cudaGraphNode_t originalNode = input_buffer->Get<cudaGraphNode_t>();
        cudaGraph_t clonedGraph = input_buffer->Get<cudaGraph_t>();
        cudaError_t exit_code = cudaGraphNodeFindInClone(&pNode, originalNode, clonedGraph);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddEmptyNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaError_t exit_code =
            cudaGraphAddEmptyNode(&pGraphNode, graph, pDependencies, numDependencies);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddChildGraphNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraph_t childGraph = input_buffer->Get<cudaGraph_t>();
        cudaError_t exit_code = cudaGraphAddChildGraphNode(&pGraphNode, graph, pDependencies,
                                                           numDependencies, childGraph);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphChildGraphNodeGetGraph) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaGraph_t pGraph;
        cudaError_t exit_code = cudaGraphChildGraphNodeGetGraph(node, &pGraph);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraph_t>(pGraph);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddKernelNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaKernelNodeParams* pNodeParams = input_buffer->Assign<cudaKernelNodeParams>();
        cudaError_t exit_code = cudaGraphAddKernelNode(&pGraphNode, graph, pDependencies,
                                                       numDependencies, pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddHostNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaHostNodeParams* pNodeParams = input_buffer->Assign<cudaHostNodeParams>();
        cudaError_t exit_code =
            cudaGraphAddHostNode(&pGraphNode, graph, pDependencies, numDependencies, pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemcpyNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaMemcpy3DParms* pCopyParams = input_buffer->Assign<cudaMemcpy3DParms>();
        cudaError_t exit_code = cudaGraphAddMemcpyNode(&pGraphNode, graph, pDependencies,
                                                       numDependencies, pCopyParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemcpyNode1D) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code = cudaGraphAddMemcpyNode1D(&pGraphNode, graph, pDependencies,
                                                         numDependencies, dst, src, count, kind);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemcpyNodeFromSymbol) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const char* symbol = pThis->GetSymbol(input_buffer);
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code = cudaGraphAddMemcpyNodeFromSymbol(
            &pGraphNode, graph, pDependencies, numDependencies, dst, symbol, count, offset, kind);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemcpyNodeToSymbol) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        const char* symbol = pThis->GetSymbol(input_buffer);
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code = cudaGraphAddMemcpyNodeToSymbol(
            &pGraphNode, graph, pDependencies, numDependencies, symbol, src, count, offset, kind);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemsetNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaMemsetParams* pMemsetParams = input_buffer->Assign<cudaMemsetParams>();
        cudaError_t exit_code = cudaGraphAddMemsetNode(&pGraphNode, graph, pDependencies,
                                                       numDependencies, pMemsetParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddEventRecordNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        cudaError_t exit_code = cudaGraphAddEventRecordNode(&pGraphNode, graph, pDependencies,
                                                            numDependencies, event);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddEventWaitNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        cudaError_t exit_code = cudaGraphAddEventWaitNode(&pGraphNode, graph, pDependencies,
                                                          numDependencies, event);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddExternalSemaphoresSignalNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaExternalSemaphoreSignalNodeParams* nodeParams =
            input_buffer->Assign<cudaExternalSemaphoreSignalNodeParams>();
        cudaError_t exit_code = cudaGraphAddExternalSemaphoresSignalNode(
            &pGraphNode, graph, pDependencies, numDependencies, nodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddExternalSemaphoresWaitNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaExternalSemaphoreWaitNodeParams* nodeParams =
            input_buffer->Assign<cudaExternalSemaphoreWaitNodeParams>();
        cudaError_t exit_code = cudaGraphAddExternalSemaphoresWaitNode(
            &pGraphNode, graph, pDependencies, numDependencies, nodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemAllocNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaMemAllocNodeParams* nodeParams = input_buffer->Assign<cudaMemAllocNodeParams>();
        cudaError_t exit_code = cudaGraphAddMemAllocNode(&pGraphNode, graph, pDependencies,
                                                         numDependencies, nodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        out->Add(nodeParams);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddMemFreeNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        void* dptr = (void*)input_buffer->Get<pointer_t>();
        cudaError_t exit_code = cudaGraphAddMemFreeNode(&pGraphNode, graph, pDependencies,
                                                        numDependencies, dptr);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddNode) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        const cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphNodeParams* pNodeParams = input_buffer->Assign<cudaGraphNodeParams>();
        cudaError_t exit_code = cudaGraphAddNode(&pGraphNode, graph, pDependencies, numDependencies,
                                                 pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphKernelNodeGetParams){
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();

        cudaKernelNodeParams pNodeParams;

        cudaError_t exit_code = cudaGraphKernelNodeGetParams(node,&pNodeParams);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();

        out->Add<cudaKernelNodeParams>(pNodeParams);


        return std::make_shared<Result>(exit_code,out);

    }catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }




}

CUDA_ROUTINE_HANDLER(GraphKernelNodeSetParams){
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();

        cudaKernelNodeParams* pNodeParams = input_buffer->Assign<cudaKernelNodeParams>();
        cudaError_t exit_code = cudaGraphKernelNodeSetParams(node,pNodeParams);
        return std::make_shared<Result>(exit_code);

    }catch (const std::exception& e ){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);



    }
}

CUDA_ROUTINE_HANDLER(GraphKernelNodeGetAttribute){
    try{
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();

        cudaKernelNodeAttrID attr = input_buffer->Get<cudaKernelNodeAttrID>();

        cudaKernelNodeAttrValue value_out;
        cudaError_t exit_code = cudaGraphKernelNodeGetAttribute(node, attr, &value_out);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();

        out->Add<cudaKernelNodeAttrValue>(value_out);

        return std::make_shared<Result>(exit_code,out);
    }catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);

    }



}

CUDA_ROUTINE_HANDLER(GraphKernelNodeSetAttribute) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaKernelNodeAttrID attr = input_buffer->Get<cudaKernelNodeAttrID>();
        cudaKernelNodeAttrValue* value = input_buffer->Assign<cudaKernelNodeAttrValue>();
        cudaError_t exit_code = cudaGraphKernelNodeSetAttribute(node, attr, value);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphKernelNodeCopyAttributes) {
    try {
        cudaGraphNode_t dst = input_buffer->Get<cudaGraphNode_t>();
        cudaGraphNode_t src = input_buffer->Get<cudaGraphNode_t>();
        return std::make_shared<Result>(cudaGraphKernelNodeCopyAttributes(dst, src));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphHostNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaHostNodeParams pNodeParams;
        cudaError_t exit_code = cudaGraphHostNodeGetParams(node, &pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaHostNodeParams>(pNodeParams);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphHostNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaHostNodeParams* pNodeParams = input_buffer->Assign<cudaHostNodeParams>();
        return std::make_shared<Result>(cudaGraphHostNodeSetParams(node, pNodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemcpyNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemcpy3DParms pNodeParams;
        cudaError_t exit_code = cudaGraphMemcpyNodeGetParams(node, &pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaMemcpy3DParms>(pNodeParams);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemcpyNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemcpy3DParms* pNodeParams = input_buffer->Assign<cudaMemcpy3DParms>();
        return std::make_shared<Result>(cudaGraphMemcpyNodeSetParams(node, pNodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemcpyNodeSetParams1D) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code = cudaGraphMemcpyNodeSetParams1D(node, dst, src, count, kind);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemcpyNodeSetParamsFromSymbol) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const char* symbol = pThis->GetSymbol(input_buffer);
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code =
            cudaGraphMemcpyNodeSetParamsFromSymbol(node, dst, symbol, count, offset, kind);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemcpyNodeSetParamsToSymbol) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        const char* symbol = pThis->GetSymbol(input_buffer);
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        cudaError_t exit_code =
            cudaGraphMemcpyNodeSetParamsToSymbol(node, symbol, src, count, offset, kind);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemsetNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemsetParams pNodeParams;
        cudaError_t exit_code = cudaGraphMemsetNodeGetParams(node, &pNodeParams);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaMemsetParams>(pNodeParams);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemsetNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemsetParams* pNodeParams = input_buffer->Assign<cudaMemsetParams>();
        return std::make_shared<Result>(cudaGraphMemsetNodeSetParams(node, pNodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphEventRecordNodeGetEvent) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event;
        cudaError_t exit_code = cudaGraphEventRecordNodeGetEvent(node, &event);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaEvent_t>(event);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphEventRecordNodeSetEvent) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        return std::make_shared<Result>(cudaGraphEventRecordNodeSetEvent(node, event));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphEventWaitNodeGetEvent) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event;
        cudaError_t exit_code = cudaGraphEventWaitNodeGetEvent(node, &event);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaEvent_t>(event);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphEventWaitNodeSetEvent) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        return std::make_shared<Result>(cudaGraphEventWaitNodeSetEvent(node, event));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExternalSemaphoresSignalNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreSignalNodeParams params;
        cudaError_t exit_code = cudaGraphExternalSemaphoresSignalNodeGetParams(node, &params);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaExternalSemaphoreSignalNodeParams>(params);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExternalSemaphoresSignalNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreSignalNodeParams* params =
            input_buffer->Assign<cudaExternalSemaphoreSignalNodeParams>();
        cudaError_t exit_code = cudaGraphExternalSemaphoresSignalNodeSetParams(node, params);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExternalSemaphoresWaitNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreWaitNodeParams params;
        cudaError_t exit_code = cudaGraphExternalSemaphoresWaitNodeGetParams(node, &params);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaExternalSemaphoreWaitNodeParams>(params);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExternalSemaphoresWaitNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreWaitNodeParams* params =
            input_buffer->Assign<cudaExternalSemaphoreWaitNodeParams>();
        cudaError_t exit_code = cudaGraphExternalSemaphoresWaitNodeSetParams(node, params);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemAllocNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemAllocNodeParams params;
        cudaError_t exit_code = cudaGraphMemAllocNodeGetParams(node, &params);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaMemAllocNodeParams>(params);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphMemFreeNodeGetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        void* dptr = nullptr;
        cudaError_t exit_code = cudaGraphMemFreeNodeGetParams(node, &dptr);
        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add((pointer_t)dptr);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeSetParams) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaGraphNodeParams* nodeParams = input_buffer->Assign<cudaGraphNodeParams>();
        cudaError_t exit_code = cudaGraphNodeSetParams(node, nodeParams);
        return std::make_shared<Result>(exit_code);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecKernelNodeSetParams) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaKernelNodeParams* params = input_buffer->Assign<cudaKernelNodeParams>();
        return std::make_shared<Result>(cudaGraphExecKernelNodeSetParams(graphExec, node, params));

    } catch (const std::exception& e ){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);

    }

}

CUDA_ROUTINE_HANDLER(GraphExecMemcpyNodeSetParams){
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemcpy3DParms* pNodeParams = input_buffer->Assign<cudaMemcpy3DParms>();
        return std::make_shared<Result>(cudaGraphExecMemcpyNodeSetParams(graphExec, node, pNodeParams));

    } catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);


    }


}

CUDA_ROUTINE_HANDLER(GraphExecMemsetNodeSetParams){
    try{
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaMemsetParams* pNodeParams = input_buffer->Assign<cudaMemsetParams>();

        return std::make_shared<Result>(cudaGraphExecMemsetNodeSetParams(graphExec, node, pNodeParams));

    } catch (const std::exception& e){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);

    }


}

CUDA_ROUTINE_HANDLER(GraphExecHostNodeSetParams){
    try{
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaHostNodeParams* pNodeParams = input_buffer->Assign<cudaHostNodeParams>();

        return std::make_shared<Result>(cudaGraphExecHostNodeSetParams(graphExec, node, pNodeParams));




    } catch(const std::exception& e ){
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }

}

CUDA_ROUTINE_HANDLER(GraphExecUpdate){
    try{
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();

        cudaGraphExecUpdateResultInfo* result = input_buffer->Assign<cudaGraphExecUpdateResultInfo>();

        cudaError_t exit_code = cudaGraphExecUpdate(graphExec, graph, result);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphExecUpdateResultInfo>(*result);

        return std::make_shared<Result>(exit_code,out);

    }catch (const std::exception& e ){

        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorGraphExecUpdateFailure);

    }

}

CUDA_ROUTINE_HANDLER(GraphDebugDotPrint) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        char* path = input_buffer->AssignString();
        unsigned int flags = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaGraphDebugDotPrint(graph, path, flags));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddDependencies_v2) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphEdgeData* edgeData = input_buffer->Assign<cudaGraphEdgeData>(numDependencies);
        return std::make_shared<Result>(
            cudaGraphAddDependencies_v2(graph, from, to, edgeData, numDependencies));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphRemoveDependencies_v2) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphEdgeData* edgeData = input_buffer->Assign<cudaGraphEdgeData>(numDependencies);
        return std::make_shared<Result>(
            cudaGraphRemoveDependencies_v2(graph, from, to, edgeData, numDependencies));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphGetEdges_v2) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t requested = input_buffer->Get<size_t>();
        cudaGraphNode_t* from = input_buffer->Assign<cudaGraphNode_t>(requested);
        cudaGraphNode_t* to = input_buffer->Assign<cudaGraphNode_t>(requested);
        cudaGraphEdgeData* edgeData = input_buffer->Assign<cudaGraphEdgeData>(requested);
        size_t numEdges = requested;
        cudaError_t exit_code = cudaGraphGetEdges_v2(graph, from, to, edgeData, &numEdges);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numEdges);
        if (requested > 0) {
            out->Add<cudaGraphNode_t>(from, requested);
            out->Add<cudaGraphNode_t>(to, requested);
            out->Add<cudaGraphEdgeData>(edgeData, requested);
        }
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeGetDependencies) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        size_t requested = input_buffer->Get<size_t>();
        cudaGraphNode_t* dependencies = input_buffer->Assign<cudaGraphNode_t>(requested);
        size_t numDependencies = requested;
        cudaError_t exit_code =
            cudaGraphNodeGetDependencies(node, dependencies, &numDependencies);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numDependencies);
        if (requested > 0) out->Add<cudaGraphNode_t>(dependencies, requested);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeGetDependencies_v2) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        size_t requested = input_buffer->Get<size_t>();
        cudaGraphNode_t* dependencies = input_buffer->Assign<cudaGraphNode_t>(requested);
        cudaGraphEdgeData* edgeData = input_buffer->Assign<cudaGraphEdgeData>(requested);
        size_t numDependencies = requested;
        cudaError_t exit_code =
            cudaGraphNodeGetDependencies_v2(node, dependencies, edgeData, &numDependencies);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numDependencies);
        if (requested > 0) {
            out->Add<cudaGraphNode_t>(dependencies, requested);
            out->Add<cudaGraphEdgeData>(edgeData, requested);
        }
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeGetDependentNodes) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        size_t requested = input_buffer->Get<size_t>();
        cudaGraphNode_t* dependentNodes = input_buffer->Assign<cudaGraphNode_t>(requested);
        size_t numDependentNodes = requested;
        cudaError_t exit_code =
            cudaGraphNodeGetDependentNodes(node, dependentNodes, &numDependentNodes);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numDependentNodes);
        if (requested > 0) out->Add<cudaGraphNode_t>(dependentNodes, requested);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeGetDependentNodes_v2) {
    try {
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        size_t requested = input_buffer->Get<size_t>();
        cudaGraphNode_t* dependentNodes = input_buffer->Assign<cudaGraphNode_t>(requested);
        cudaGraphEdgeData* edgeData = input_buffer->Assign<cudaGraphEdgeData>(requested);
        size_t numDependentNodes = requested;
        cudaError_t exit_code =
            cudaGraphNodeGetDependentNodes_v2(node, dependentNodes, edgeData, &numDependentNodes);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<size_t>(numDependentNodes);
        if (requested > 0) {
            out->Add<cudaGraphNode_t>(dependentNodes, requested);
            out->Add<cudaGraphEdgeData>(edgeData, requested);
        }
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphAddNode_v2) {
    try {
        cudaGraphNode_t pGraphNode;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        size_t numDependencies = input_buffer->Get<size_t>();
        cudaGraphNode_t* pDependencies = input_buffer->Assign<cudaGraphNode_t>(numDependencies);
        cudaGraphEdgeData* dependencyData = input_buffer->Assign<cudaGraphEdgeData>(numDependencies);
        cudaGraphNodeParams* pNodeParams = input_buffer->Assign<cudaGraphNodeParams>();
        cudaError_t exit_code = cudaGraphAddNode_v2(
            &pGraphNode, graph, pDependencies, dependencyData, numDependencies, pNodeParams);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphNode_t>(pGraphNode);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphInstantiateWithParams) {
    try {
        cudaGraphExec_t pGraphExec;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        cudaGraphInstantiateParams* instantiateParams =
            input_buffer->Assign<cudaGraphInstantiateParams>();
        cudaError_t exit_code =
            cudaGraphInstantiateWithParams(&pGraphExec, graph, instantiateParams);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphExec_t>(pGraphExec);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecGetFlags) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        unsigned long long flags = 0;
        cudaError_t exit_code = cudaGraphExecGetFlags(graphExec, &flags);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<unsigned long long>(flags);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecChildGraphNodeSetParams) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaGraph_t childGraph = input_buffer->Get<cudaGraph_t>();
        return std::make_shared<Result>(
            cudaGraphExecChildGraphNodeSetParams(graphExec, node, childGraph));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecMemcpyNodeSetParams1D) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        return std::make_shared<Result>(
            cudaGraphExecMemcpyNodeSetParams1D(graphExec, node, dst, src, count, kind));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecMemcpyNodeSetParamsFromSymbol) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        void* dst = (void*)input_buffer->Get<pointer_t>();
        const char* symbol = pThis->GetSymbol(input_buffer);
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        return std::make_shared<Result>(cudaGraphExecMemcpyNodeSetParamsFromSymbol(
            graphExec, node, dst, symbol, count, offset, kind));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecMemcpyNodeSetParamsToSymbol) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        const char* symbol = pThis->GetSymbol(input_buffer);
        const void* src = (const void*)input_buffer->Get<pointer_t>();
        size_t count = input_buffer->Get<size_t>();
        size_t offset = input_buffer->Get<size_t>();
        cudaMemcpyKind kind = input_buffer->Get<cudaMemcpyKind>();
        return std::make_shared<Result>(cudaGraphExecMemcpyNodeSetParamsToSymbol(
            graphExec, node, symbol, src, count, offset, kind));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecEventRecordNodeSetEvent) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        return std::make_shared<Result>(
            cudaGraphExecEventRecordNodeSetEvent(graphExec, node, event));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecEventWaitNodeSetEvent) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaEvent_t event = input_buffer->Get<cudaEvent_t>();
        return std::make_shared<Result>(
            cudaGraphExecEventWaitNodeSetEvent(graphExec, node, event));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecExternalSemaphoresSignalNodeSetParams) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreSignalNodeParams* nodeParams =
            input_buffer->Assign<cudaExternalSemaphoreSignalNodeParams>();
        return std::make_shared<Result>(
            cudaGraphExecExternalSemaphoresSignalNodeSetParams(graphExec, node, nodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecExternalSemaphoresWaitNodeSetParams) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaExternalSemaphoreWaitNodeParams* nodeParams =
            input_buffer->Assign<cudaExternalSemaphoreWaitNodeParams>();
        return std::make_shared<Result>(
            cudaGraphExecExternalSemaphoresWaitNodeSetParams(graphExec, node, nodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphExecNodeSetParams) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        cudaGraphNodeParams* nodeParams = input_buffer->Assign<cudaGraphNodeParams>();
        return std::make_shared<Result>(cudaGraphExecNodeSetParams(graphExec, node, nodeParams));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeGetEnabled) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        unsigned int isEnabled = 0;
        cudaError_t exit_code = cudaGraphNodeGetEnabled(graphExec, node, &isEnabled);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<unsigned int>(isEnabled);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphNodeSetEnabled) {
    try {
        cudaGraphExec_t graphExec = input_buffer->Get<cudaGraphExec_t>();
        cudaGraphNode_t node = input_buffer->Get<cudaGraphNode_t>();
        unsigned int isEnabled = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaGraphNodeSetEnabled(graphExec, node, isEnabled));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(DeviceGetGraphMemAttribute) {
    try {
        int device = input_buffer->Get<int>();
        cudaGraphMemAttributeType attr = input_buffer->Get<cudaGraphMemAttributeType>();
        unsigned long long value = 0;
        cudaError_t exit_code = cudaDeviceGetGraphMemAttribute(device, attr, &value);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<unsigned long long>(value);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(DeviceSetGraphMemAttribute) {
    try {
        int device = input_buffer->Get<int>();
        cudaGraphMemAttributeType attr = input_buffer->Get<cudaGraphMemAttributeType>();
        unsigned long long value = input_buffer->Get<unsigned long long>();
        return std::make_shared<Result>(cudaDeviceSetGraphMemAttribute(device, attr, &value));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(DeviceGraphMemTrim) {
    try {
        int device = input_buffer->Get<int>();
        return std::make_shared<Result>(cudaDeviceGraphMemTrim(device));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(UserObjectCreate) {
    try {
        cudaUserObject_t object;
        void* ptr = (void*)input_buffer->Get<pointer_t>();
        cudaHostFn_t destroy = reinterpret_cast<cudaHostFn_t>(input_buffer->Get<uintptr_t>());
        unsigned int initialRefcount = input_buffer->Get<unsigned int>();
        unsigned int flags = input_buffer->Get<unsigned int>();
        cudaError_t exit_code =
            cudaUserObjectCreate(&object, ptr, destroy, initialRefcount, flags);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaUserObject_t>(object);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}

CUDA_ROUTINE_HANDLER(UserObjectRetain) {
    try {
        cudaUserObject_t object = input_buffer->Get<cudaUserObject_t>();
        unsigned int count = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaUserObjectRetain(object, count));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(UserObjectRelease) {
    try {
        cudaUserObject_t object = input_buffer->Get<cudaUserObject_t>();
        unsigned int count = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaUserObjectRelease(object, count));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphRetainUserObject) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        cudaUserObject_t object = input_buffer->Get<cudaUserObject_t>();
        unsigned int count = input_buffer->Get<unsigned int>();
        unsigned int flags = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaGraphRetainUserObject(graph, object, count, flags));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphReleaseUserObject) {
    try {
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        cudaUserObject_t object = input_buffer->Get<cudaUserObject_t>();
        unsigned int count = input_buffer->Get<unsigned int>();
        return std::make_shared<Result>(cudaGraphReleaseUserObject(graph, object, count));
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorInvalidValue);
    }
}

CUDA_ROUTINE_HANDLER(GraphConditionalHandleCreate) {
    try {
        cudaGraphConditionalHandle handle;
        cudaGraph_t graph = input_buffer->Get<cudaGraph_t>();
        unsigned int defaultLaunchValue = input_buffer->Get<unsigned int>();
        unsigned int flags = input_buffer->Get<unsigned int>();
        cudaError_t exit_code =
            cudaGraphConditionalHandleCreate(&handle, graph, defaultLaunchValue, flags);

        std::shared_ptr<Buffer> out = std::make_shared<Buffer>();
        out->Add<cudaGraphConditionalHandle>(handle);
        return std::make_shared<Result>(exit_code, out);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return std::make_shared<Result>(cudaErrorMemoryAllocation);
    }
}


