// This is not a commercial example. This example is used for testing only.

#include "../src/alkane/alkane.hpp"
#include "engine/scene.hpp"
#include "math/colors.hpp"
#include "platform/window.hpp"

Window window(800, 600, "Alkane Engine");
Engine engine(window);
Scene scene;
auto &tri = scene.create<Triangle>("src/alkane/shaders/default.vert",
                                   "src/alkane/shaders/default.frag");

void update() {
  input::update(window.getNative());

  if (input::isKeyDown(KEY_S))
    tri.transform.y += 5.0f;
  if (input::isKeyDown(KEY_W))
    tri.transform.y -= 5.0f;
  if (input::isKeyDown(KEY_D))
    tri.transform.x += 5.0f;
  if (input::isKeyDown(KEY_A))
    tri.transform.x -= 5.0f;
}

void render(Renderer &renderer) {
  renderer.clear(0.0f, 0.0f, 0.0f);
  renderer.render(scene);
  tri.setColor(Colors::Red);
}

int main() {

  engine.setUpdate(update);
  engine.setRender(render);

  engine.run();
}