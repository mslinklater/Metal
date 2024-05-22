//
//  Common.h
//  MyMetalCPP
//
//  Created by Martin Linklater on 16/05/2024.
//

# pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <iostream>

#define ENABLE_RENDERING 1
//#define ENABLE_IMGUI 1

#define AAPLSTR( str ) reinterpret_cast< const NS::String* >(__builtin___CFStringMakeConstantString( str ))
