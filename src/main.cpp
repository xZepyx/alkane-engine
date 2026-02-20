#include <alkane/physics/collisions.hpp>
#include <alkane/textures/textures.hpp>
#include <alkane/engine.hpp>
#include <alkane/input.hpp>
#include <alkane/graphics.hpp>
#include <alkane/sprite.hpp>

Sprite sprite;
Body body = {200, 200, 100, 100, "#FF0000"};

void update() {
    // all game logic like physics etc
    float delta = engine::Engine::deltaTime();

    sprite.update(delta);
    body.update(delta);

    physics::resolveCollision(sprite.body, body, CollisionType::Dynamic);

    // Movement with keys
    if (input::isKeyDown(KEY_S))
        sprite.body.vy += 5.0f;
    if (input::isKeyDown(KEY_W))
        sprite.body.vy -= 5.0f;
    if (input::isKeyDown(KEY_D))
        sprite.body.vx += 5.0f;
    if (input::isKeyDown(KEY_A))
        sprite.body.vx -= 5.0f;
}

void render() {
    colors::clearFrame("#FFFFFF");
    sprite.draw();
    body.draw();
}

int main() {
    // Create the engine instance
    engine::Engine engine(1024, 768, "Alkane Engine", nullptr, nullptr);

    // Initialize engine (GLFW + GLAD + viewport)
    if (!engine.init()) {
        return -1; // initialization failed
    }

    GLuint tex = loadTexture("assets/wall.jpg", GL_NEAREST);
    sprite = {
        Body{
            100,
            50,
            128,
            128,
            "#FFFFFF",
            1.0f},
        tex};
    // sprite.useGravity = true;

    // Set user callbacks
    engine.setUpdate(update);
    engine.setRender(render);

    // Start the main loop (engine owns loop, swap/poll handled internally)
    engine.run();

    return 0;
}
