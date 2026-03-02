#pragma once
#include "math/transform.hpp"

class Renderable {
    public: 
        Transform2D transform;
        virtual ~Renderable() = default;
        virtual void draw() const = 0;
};