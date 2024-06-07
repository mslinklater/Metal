//
//  MetalDebug.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 17/05/2024.
//

#pragma once

// forward declare
namespace MTL
{
    class Device;
    class CommandQueue;
    class Library;
}

namespace MetalDebug
{
    void Dump(MTL::Device* pDevice);
    void Dump(MTL::CommandQueue* pCommandQueue);
    void Dump(MTL::Library* pLibrary);
}
