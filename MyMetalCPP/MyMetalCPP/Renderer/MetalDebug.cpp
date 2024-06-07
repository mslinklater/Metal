//
//  MetalDebugDump.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 17/05/2024.
//

#include "MetalDebug.hpp"
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

static void PrintCString(const char* text, const char* str)
{
    if (str)
    {
        std::cout << text << " - " << str << std::endl;
    }
    else
    {
        std::cout << text << " - " << "NULL" << std::endl;
    }
}

namespace MetalDebug
{

void Dump(MTL::Device* pDevice)
{
    PrintTitle("MetalDebug::Dump - Device");
    PrintBool("Supports Ray Tracing", pDevice->supportsRaytracing());
}

void Dump(MTL::CommandQueue* pCommandQueue)
{
    PrintTitle("MetalDebug::Dump - CommandQueue");
    PrintCString("Label", pCommandQueue->label()->utf8String());
}

void Dump(MTL::Library* pLibrary)
{
    PrintTitle("MetalDebug::Dump - Library");
    PrintCString("Label", pLibrary->label()->utf8String());
    NS::Array* array = pLibrary->functionNames();
    for (int i = 0 ; i < array->count() ; ++i)
    {
        NS::String* str = array->object<NS::String>(i);
        PrintCString("Function", str->utf8String());
    }
}

}
