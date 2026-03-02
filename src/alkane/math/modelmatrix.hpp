#pragma once

#include <cmath>

#include "transform.hpp"

static void buildModelMatrix(const Transform2D& t, float* m)
{
    float c = cosf(t.rotation);
    float s = sinf(t.rotation);

    // Column-major layout
    m[0]  =  t.sx * c;
    m[1]  =  t.sx * s;
    m[2]  =  0.0f;
    m[3]  =  0.0f;

    m[4]  = -t.sy * s;
    m[5]  =  t.sy * c;
    m[6]  =  0.0f;
    m[7]  =  0.0f;

    m[8]  =  0.0f;
    m[9]  =  0.0f;
    m[10] =  1.0f;
    m[11] =  0.0f;

    m[12] =  t.x;
    m[13] =  t.y;
    m[14] =  0.0f;
    m[15] =  1.0f;
}