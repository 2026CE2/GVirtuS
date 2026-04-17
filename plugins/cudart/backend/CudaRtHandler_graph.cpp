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

/*TODO add Batch 1
`cudaGraphAddDependencies`, `cudaGraphRemoveDependencies`, `cudaGraphGetEdges`,
`cudaGraphGetRootNodes`, `cudaGraphDestroyNode`*/