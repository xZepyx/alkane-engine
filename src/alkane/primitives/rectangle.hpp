#pragma once

#include <vector>

#include "renderer/renderable.hpp"
#include "renderer/shader.hpp"
#include "renderer/mesh.hpp"
#include "math/modelmatrix.hpp"
#include "math/colors.hpp"
#include "string"

class Rectangle : public Renderable {
  public:
    Rectangle(const std::string &vs,
             const std::string &fs)
        : shader(vs, fs),
            mesh({
                // Triangle 1
                0.0f, 100.0f, 0.0f,
                100.0f, 100.0f, 0.0f,
                0.0f, 0.0f, 0.0f,

                // Triangle 2
                0.0f, 0.0f, 0.0f,
                100.0f, 100.0f, 0.0f,
                100.0f, 0.0f, 0.0f
            }) {}

    void render(Renderer &renderer) const override {
        shader.use();

        float model[16];
        buildModelMatrix(transform, model);

        shader.setMat4("uModel", model);
        shader.setMat4("uProjection", renderer.getProjection());

        shader.setVec4("uColor",
                    color.r,
                    color.g,
                    color.b,
                    color.a);
        mesh.render();
    }

  private:
    Shader shader;
    Mesh2D mesh;
};