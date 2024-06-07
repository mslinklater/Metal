//
//  ShaderStructs.h
//  MyMetalCPP
//
//  Created by Martin Linklater on 18/05/2024.
//

#ifndef ShaderStructs_h
#define ShaderStructs_h

#include <simd/simd.h>

#include "../Maths/MathsTypes.h"

struct VertexData
{
    Vector3f position;
    Vector3f normal;
    Vector2f texcoord;
};

struct InstanceData // size 80 bytes
{
    Matrix44f instanceTransform;
    Matrix33f instanceNormalTransform;
    Vector4f instanceColor;
};

struct CameraData
{
    Matrix44f perspectiveTransform;
    Matrix44f worldTransform;
    Matrix33f worldNormalTransform;
};

#endif /* ShaderStructs_h */
