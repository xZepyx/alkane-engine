#pragma once
#include "vertex2d.hpp"
#include <alkane/physics/body.hpp>
#include <alkane/renderer/renderable.hpp>
#include "GLFW/glfw3.h"
#include "vector"

class Mesh2D: public Renderable {
public:
    std::vector<Vertex2D> vertices;
    std::vector<unsigned int> indices;
    GLuint texture = 0; // mesh texture

    GLenum drawMode = GL_TRIANGLES;

    Body* body = nullptr; // collision representation

    void clear() {
        vertices.clear();
        indices.clear();
    }

    void submit(Renderer& renderer) override;
};