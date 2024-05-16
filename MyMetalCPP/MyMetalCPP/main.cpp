//
//  main.cpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

#include <iostream>

#include <cassert>

/// Instantiate MetalCPP here...
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include "AppDelegate.hpp"

int main(int argc, const char * argv[]) 
{
    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    
    AppDelegate del;

    NS::Application* pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate( &del );
    pSharedApplication->run();
    
    pAutoreleasePool->release();
    
    return 0;
}
