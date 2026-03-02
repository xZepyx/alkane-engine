#pragma once

namespace ortho {
static void buildOrtho(float left, float right, float bottom, float top, float* m)
{
    for (int i = 0; i < 16; i++)
        m[i] = 0.0f;

    m[0]  =  2.0f / (right - left);
    m[5]  =  2.0f / (top - bottom);
    m[10] = -1.0f;

    m[12] = -(right + left) / (right - left);
    m[13] = -(top + bottom) / (top - bottom);

    m[15] = 1.0f;
}
}