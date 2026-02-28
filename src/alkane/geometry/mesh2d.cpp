#include <alkane/geometry/mesh2d.hpp>
#include <alkane/renderer/renderer.hpp>

void Mesh2D::submit(Renderer& renderer)
{
    renderer.draw(*this);
}