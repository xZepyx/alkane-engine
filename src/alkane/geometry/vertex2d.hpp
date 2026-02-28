#pragma once
#include "vector2d.hpp"

struct Vertex2D {
    Vector2 position;
    Vector2 uv;       // texture coordinates
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f; // color per vertex
};