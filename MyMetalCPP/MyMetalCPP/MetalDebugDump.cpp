//
//  MetalDebugDump.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 17/05/2024.
//

#include "MetalDebugDump.hpp"
#include "Common.h"

#include <iostream>

static void PrintTitle(const char* text)
{
    std::cout << "=== " << text << " ===" << std::endl;
}

static void PrintBool(const char* text, bool condition)
{
    std::cout << text << " - " << (condition ? "YES" : "NO") << std::endl;
}

void MetalDebugDump(MTL::Device* pDevice)
{
    PrintTitle("MetalDebugDump - Device");
    PrintBool("Supports Ray Tracing", pDevice->supportsRaytracing());
}
