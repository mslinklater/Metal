//
//  Renderer.hpp
//  DefaultGame
//
//  Created by Martin Linklater on 15/05/2024.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>

#include <Metal/Metal.hpp>

class Renderer {
public:
private:
    dispatch_semaphore_t inFlightSemaphore;
    
    MTL::Device* device;
    MTL::CommandQueue* commandQueue;
    MTL::Buffer* dynamicUniformBuffer;
    MTL::RenderPipelineState* pipelineState;
    MTL::DepthStencilState* depthState;
    MTL::Texture* colorMap;
    MTL::VertexDescriptor* vertexDescriptor;
};

#endif /* Renderer_hpp */
