#pragma once

class Renderable {
public:
    virtual ~Renderable() = default;
    virtual void submit(class Renderer& renderer) = 0;
};