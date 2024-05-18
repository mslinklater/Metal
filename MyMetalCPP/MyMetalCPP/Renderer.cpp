//
//  Renderer.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#include "Renderer.hpp"
#include "MetalDebugDump.hpp"
#include "Shaders/ShaderStructs.h"
#include <simd/simd.h>

const int Renderer::kMaxFramesInFlight = 3;

Renderer::Renderer( MTL::Device* pDevice )
: _pDevice( pDevice->retain() )
, _angle ( 0.f )
, _frame( 0 )
{
    MetalDebugDump(pDevice);
    
    _pCommandQueue = _pDevice->newCommandQueue();   // already retained as 'new'
    buildShaders();
    buildBuffers();
    
    buildFrameData();
    
    _semaphore = dispatch_semaphore_create( Renderer::kMaxFramesInFlight );
}

Renderer::~Renderer()
{
    _pVertexPositionsBuffer->release();
    _pVertexColorsBuffer->release();
    for ( int i = 0; i <  Renderer::kMaxFramesInFlight; ++i )
    {
        _pFrameData[i]->release();
    }
    _pPSO->release();
    _pCommandQueue->release();
    _pDevice->release();
}

void Renderer::buildShaders()
{
    using NS::StringEncoding::UTF8StringEncoding;

    NS::Error* pError = nullptr;
    MTL::Library* pLibrary = _pDevice->newDefaultLibrary();
    
    if ( !pLibrary )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }

    MTL::Function* pVertexFn = pLibrary->newFunction( NS::String::string("vertexMain", UTF8StringEncoding) );
    MTL::Function* pFragFn = pLibrary->newFunction( NS::String::string("fragmentMain", UTF8StringEncoding) );

    MTL::RenderPipelineDescriptor* pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
    pDesc->setVertexFunction( pVertexFn );
    pDesc->setFragmentFunction( pFragFn );
    pDesc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

    _pPSO = _pDevice->newRenderPipelineState( pDesc, &pError );    // EXPENSIVE...
    if ( !_pPSO )
    {
        __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
        assert( false );
    }

    pVertexFn->release();
    pFragFn->release();
    pDesc->release();
   _pShaderLibrary = pLibrary;
}

void Renderer::buildBuffers()
{
    const size_t NumVertices = 3;
    
    simd::float3 positions[NumVertices] =
    {
        { -0.8f,  0.8f, 0.0f },
        {  0.0f, -0.8f, 0.0f },
        { +0.8f,  0.8f, 0.0f }
    };
    
    simd::float3 colors[NumVertices] =
    {
        {  1.0, 0.3f, 0.2f },
        {  0.8f, 1.0, 0.0f },
        {  0.8f, 0.0f, 1.0 }
    };
    
    const size_t positionsDataSize = NumVertices * sizeof( simd::float3 );
    const size_t colorDataSize = NumVertices * sizeof( simd::float3 );
    
    MTL::Buffer* pVertexPositionsBuffer = _pDevice->newBuffer( positionsDataSize, MTL::ResourceStorageModeManaged );
    MTL::Buffer* pVertexColorsBuffer = _pDevice->newBuffer( colorDataSize, MTL::ResourceStorageModeManaged );
    
    _pVertexPositionsBuffer = pVertexPositionsBuffer;
    _pVertexColorsBuffer = pVertexColorsBuffer;
    
    memcpy( _pVertexPositionsBuffer->contents(), positions, positionsDataSize );
    memcpy( _pVertexColorsBuffer->contents(), colors, colorDataSize );
    
    _pVertexPositionsBuffer->didModifyRange( NS::Range::Make( 0, _pVertexPositionsBuffer->length() ) );
    _pVertexColorsBuffer->didModifyRange( NS::Range::Make( 0, _pVertexColorsBuffer->length() ) );
    
    using NS::StringEncoding::UTF8StringEncoding;
    assert( _pShaderLibrary );

    MTL::Function* pVertexFn = _pShaderLibrary->newFunction( NS::String::string( "vertexMain", UTF8StringEncoding ) );
    MTL::ArgumentEncoder* pArgEncoder = pVertexFn->newArgumentEncoder( 0 );

    MTL::Buffer* pArgBuffer = _pDevice->newBuffer( pArgEncoder->encodedLength(), MTL::ResourceStorageModeManaged );
    _pArgBuffer = pArgBuffer;

    pArgEncoder->setArgumentBuffer( _pArgBuffer, 0 );

    pArgEncoder->setBuffer( _pVertexPositionsBuffer, 0, 0 );
    pArgEncoder->setBuffer( _pVertexColorsBuffer, 0, 1 );

    _pArgBuffer->didModifyRange( NS::Range::Make( 0, _pArgBuffer->length() ) );

    pVertexFn->release();
    pArgEncoder->release();}

void Renderer::buildFrameData()
{
    for ( int i = 0; i < Renderer::kMaxFramesInFlight; ++i )
    {
        _pFrameData[ i ]= _pDevice->newBuffer( sizeof( FrameData ), MTL::ResourceStorageModeManaged );
    }
}

void Renderer::draw(MTK::View *pView)
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();
    
    _frame = (_frame + 1) % Renderer::kMaxFramesInFlight;
    MTL::Buffer* pFrameDataBuffer = _pFrameData[ _frame ];
    
    MTL::CommandBuffer* pCommandBuffer = _pCommandQueue->commandBuffer(); // autoreleased ?

    // Completion handler
    dispatch_semaphore_wait( _semaphore, DISPATCH_TIME_FOREVER );
    Renderer* pRenderer = this;
    pCommandBuffer->addCompletedHandler( ^void( MTL::CommandBuffer* pCommandBuffer ){
        dispatch_semaphore_signal( pRenderer->_semaphore );
    });

    reinterpret_cast< FrameData * >( pFrameDataBuffer->contents() )->angle = (_angle += 0.01f);
    pFrameDataBuffer->didModifyRange( NS::Range::Make( 0, sizeof( FrameData ) ) );

    MTL::RenderPassDescriptor* pRenderPassDescriptor = pView->currentRenderPassDescriptor();
    
    MTL::RenderCommandEncoder* pRenderCommandEncoder = pCommandBuffer->renderCommandEncoder( pRenderPassDescriptor );
    
    pRenderCommandEncoder->setRenderPipelineState( _pPSO );
    pRenderCommandEncoder->setVertexBuffer( _pArgBuffer, 0, 0 );
    pRenderCommandEncoder->useResource( _pVertexPositionsBuffer, MTL::ResourceUsageRead );
    pRenderCommandEncoder->useResource( _pVertexColorsBuffer, MTL::ResourceUsageRead );
    pRenderCommandEncoder->setVertexBuffer( pFrameDataBuffer, 0, 1 );
    
    pRenderCommandEncoder->drawPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3) );
    
    pRenderCommandEncoder->endEncoding();
    pCommandBuffer->presentDrawable( pView->currentDrawable() );
    pCommandBuffer->commit();
    
    pPool->release();
}
