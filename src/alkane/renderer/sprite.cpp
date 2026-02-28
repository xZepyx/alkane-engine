#include <alkane/renderer/sprite.hpp>
#include <alkane/renderer/renderer.hpp>

void Sprite::submit(Renderer& renderer)
{
    renderer.draw(*this);
}