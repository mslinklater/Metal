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
    _pRenderer->draw( pView );
}
