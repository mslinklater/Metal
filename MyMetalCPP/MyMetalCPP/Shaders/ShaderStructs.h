//
//  ShaderStructs.h
//  MyMetalCPP
//
//  Created by Martin Linklater on 18/05/2024.
//

#ifndef ShaderStructs_h
#define ShaderStructs_h

#include <simd/simd.h>

//struct FrameData
//{
//   float angle;
//};

struct InstanceData // size 80 bytes
{
    simd::float4x4 instanceTransform;
    simd::float4 instanceColor;
};

struct CameraData
{
    simd::float4x4 perspectiveTransform;
    simd::float4x4 worldTransform;
};

#endif /* ShaderStructs_h */
