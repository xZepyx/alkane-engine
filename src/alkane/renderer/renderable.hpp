#pragma once
#include "math/transform.hpp"
#include "math/colors.hpp"
#include "renderer.hpp"

class Renderable {
  protected:
    Color color{1, 1, 1, 1};

  public:
    Transform2D transform;
    virtual ~Renderable() = default;
    virtual void render(Renderer &renderer) const = 0;
    void setColor(const Color &c) { color = c; }
    const Color &getColor() const { return color; }
};