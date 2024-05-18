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
    float3 position;
//   device float3* positions [[id(0)]];
//   device float3* colors [[id(1)]];
};

// Vertex
v2f vertex vertexMain( device const VertexData* vertexData [[buffer(0)]],
                       device const InstanceData* instanceData [[buffer(1)]],
                       uint vertexId [[vertex_id]],
                       uint instanceId [[instance_id]] )
{
    v2f o;
    float4 pos = float4( vertexData[ vertexId ].position, 1.0 );
    o.position = instanceData[ instanceId ].instanceTransform * pos;
    o.color = half3( instanceData[ instanceId ].instanceColor.rgb );
    return o;
}

// Fragment
half4 fragment fragmentMain( v2f in [[stage_in]] )
{
    return half4( in.color, 1.0 );
}
