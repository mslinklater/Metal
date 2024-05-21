//
//  Renderer.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#pragma once

#include "Common.h"

static constexpr size_t kInstanceRows = 10;
static constexpr size_t kInstanceColumns = 10;
static constexpr size_t kInstanceDepth = 10;
static constexpr size_t kNumInstances = (kInstanceRows * kInstanceColumns * kInstanceDepth);
static constexpr size_t kMaxFramesInFlight = 3;
static constexpr uint32_t kTextureWidth = 128;
static constexpr uint32_t kTextureHeight = 128;

class Renderer
{
public:
    Renderer( MTL::Device* pDevice );
    virtual ~Renderer();
    
    void update();
    void draw( MTK::View* pView );
    void resize( MTK::View* pView, CGSize size );

    void buildShaders();
    void buildDepthStencilStates();
    void buildBuffers();
    void buildTextures();
    void buildComputePipeline();
    void generateMandelbrotTexture();
//    void generateMandelbrotTexture( MTL::CommandBuffer* pCommandBuffer );

private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCommandQueue;
    MTL::Library* _pShaderLibrary;
    MTL::RenderPipelineState* _pPSO;
    MTL::ComputePipelineState* _pComputePSO;
    MTL::DepthStencilState* _pDepthStencilState;
    MTL::Texture* _pTexture;
    MTL::Buffer* _pVertexDataBuffer;
    MTL::Buffer* _pInstanceDataBuffer[kMaxFramesInFlight];
    MTL::Buffer* _pCameraDataBuffer[kMaxFramesInFlight];
    MTL::Buffer* _pIndexBuffer;
    MTL::Buffer* _pTextureAnimationBuffer;
    
    float _angle;
    int _frame;
    dispatch_semaphore_t _semaphore;
    static const int kMaxFramesInFlight;
    
    uint _animationIndex;
};
