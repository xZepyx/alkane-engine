#include <alkane/geometry/sprite2d.hpp>
#include <alkane/renderer/renderer.hpp>

void Sprite2D::submit(Renderer& renderer)
{
    renderer.draw(*this);
}