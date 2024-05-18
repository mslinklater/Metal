//
//  MyShader.metal
//  MyMetalCPP
//
//  Created by Martin Linklater on 17/05/2024.
//

#include <metal_stdlib>
#include "ShaderStructs.h"

using namespace metal;

// Vertex -> Fragment
struct v2f
{
    float4 position [[position]];
    half3 color;
};

// Argument buffer - pointers to two other buffers
struct VertexData
{
   device float3* positions [[id(0)]];
   device float3* colors [[id(1)]];
};


// Vertex
v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]], constant FrameData* frameData [[buffer(1)]], uint vertexId [[vertex_id]] )
{
    float a = frameData->angle;
    float3x3 rotationMatrix = float3x3( sin(a), cos(a), 0.0, cos(a), -sin(a), 0.0, 0.0, 0.0, 1.0 );
    v2f o;
    o.position = float4( rotationMatrix * vertexData->positions[ vertexId ], 1.0 );
    o.color = half3(vertexData->colors[ vertexId ]);
    return o;
}

// Fragment
half4 fragment fragmentMain( v2f in [[stage_in]] )
{
    return half4( in.color, 1.0 );
}
