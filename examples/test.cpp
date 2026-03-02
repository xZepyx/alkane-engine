// This is not a commercial example. This example is used for testing only.

#include "../src/alkane/alkane.hpp"
#include "engine/scene.hpp"
#include "platform/window.hpp"

Scene scene;

void update()
{
    // Physics or logic here
}


void render()
{
    scene.render();
}

int main()
{
    Window window(800, 600, "Alkane Engine");
    Engine engine(window);

    engine.setUpdate(update);
    engine.setRender(render);

    scene.create<Triangle>(
        "src/alkane/shaders/default.vert",
        "src/alkane/shaders/default.frag"
    );
    engine.run();

}