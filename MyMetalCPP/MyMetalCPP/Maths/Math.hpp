//
//  Math.hpp
//  MyMetalCPP
//
//  Created by Martin Linklater on 18/05/2024.
//

#pragma once

#include <stdio.h>
#include <simd/simd.h>
#include "MathsTypes.h"

namespace Maths
{
    Vector3f add( const Vector3f& a, const Vector3f& b );
    Matrix44f makeIdentity();

    Matrix44f makePerspective( float fovRadians, float aspect, float znear, float zfar );
    Matrix44f makeXRotate( float angleRadians );
    Matrix44f makeYRotate( float angleRadians );
    Matrix44f makeZRotate( float angleRadians );
    Matrix44f makeTranslate( const Vector3f& v );
    Matrix44f makeScale( const Vector3f& v );
    Matrix33f discardTranslation( const Matrix44f& m );
}
