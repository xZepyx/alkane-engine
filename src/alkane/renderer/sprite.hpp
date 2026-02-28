#pragma once
#include <GLFW/glfw3.h>
#include <alkane/renderer/renderable.hpp>
#include <alkane/physics/constants.hpp>
#include <alkane/physics/body.hpp>

class Sprite : public Renderable {
public:
    Body* body;
    GLuint texture;

    void submit(Renderer& renderer) override;
};