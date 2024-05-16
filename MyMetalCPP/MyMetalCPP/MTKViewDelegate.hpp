//
//  MTKViewDelegate.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#pragma once

#include "Common.h"

class Renderer;

class MTKViewDelegate : public MTK::ViewDelegate
{
public:
    MTKViewDelegate( MTL::Device* pDevice );
    virtual ~MTKViewDelegate() override;
    virtual void drawInMTKView( MTK::View* pView ) override;

private:
    Renderer* _pRenderer;
};
