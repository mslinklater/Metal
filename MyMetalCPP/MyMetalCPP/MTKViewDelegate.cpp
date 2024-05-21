//
//  MTKViewDelegate.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#include "MTKViewDelegate.hpp"

#include "Renderer.hpp"

MTKViewDelegate::MTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
, _pRenderer( new Renderer( pDevice ) )
{
}

MTKViewDelegate::~MTKViewDelegate()
{
    delete _pRenderer;
}

void MTKViewDelegate::drawInMTKView( MTK::View* pView )
{
#if ENABLE_RENDERING
    _pRenderer->update();
    _pRenderer->draw( pView );
#endif
}

void MTKViewDelegate::drawableSizeWillChange( MTK::View* pView, CGSize size )
{
    if(_pRenderer)
    {
        _pRenderer->resize(pView, size);
    }
}
