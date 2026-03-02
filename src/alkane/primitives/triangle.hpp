#pragma once

#include <vector>

#include "renderer/renderable.hpp"
#include "renderer/shader.hpp"
#include "renderer/mesh.hpp"

class Triangle : public Renderable {
public:
    Triangle(const std::string& vs,
             const std::string& fs)
        : shader(vs, fs),
          mesh({
              -0.5f, -0.5f, 0.0f,
               0.5f, -0.5f, 0.0f,
               0.0f,  0.5f, 0.0f
          })
    {}

    void draw() const override
    {
        shader.use();
        mesh.render();
    }

private:
    Shader shader;
    Mesh2D mesh;
};