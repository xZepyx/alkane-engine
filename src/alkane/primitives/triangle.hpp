#pragma once

#include <vector>

#include "renderer/renderable.hpp"
#include "renderer/shader.hpp"
#include "renderer/mesh.hpp"
#include "math/modelmatrix.hpp"
#include "math/colors.hpp"

class Triangle : public Renderable {
  public:
    Triangle(const std::string &vs,
             const std::string &fs)
        : shader(vs, fs),
          mesh({0.0f, 100.0f, 0.0f,
                100.0f, 100.0f, 0.0f,
                50.0f, 0.0f, 0.0f}) {}

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