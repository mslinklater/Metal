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
    ~Renderer();
    
    void draw( MTK::View* pView );
private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCommandQueue;
};
