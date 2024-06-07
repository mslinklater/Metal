//
//  MathsTypes.h
//  MyMetalCPP
//
//  Created by Martin Linklater on 07/06/2024.
//

#pragma once

#include "../Defines.h"

#if USE_SIMD
#include <simd/simd.h>

typedef simd::float4 Vector4f;
typedef simd::float3 Vector3f;
typedef simd::float2 Vector2f;

typedef simd::float4x4 Matrix44f;
typedef simd::float3x3 Matrix33f;
#else
#endif // USE_SIMD
