//
//  Renderer.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#pragma once

#include "Common.h"

class Renderer 
{
public:
    Renderer( MTL::Device* pDevice );
    virtual ~Renderer();
    
    void draw( MTK::View* pView );
    
    void buildShaders();
    void buildBuffers();
    void buildFrameData();
    
private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCommandQueue;
    MTL::Library* _pShaderLibrary;
    MTL::RenderPipelineState* _pPSO;
    
    MTL::Buffer* _pArgBuffer;
    MTL::Buffer* _pVertexPositionsBuffer;
    MTL::Buffer* _pVertexColorsBuffer;
    
    // Per-frame data
    MTL::Buffer* _pFrameData[3];
    float _angle;
    int _frame;
    dispatch_semaphore_t _semaphore;
    static const int kMaxFramesInFlight;
};
