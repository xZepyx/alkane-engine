#include <alkane/alkane.hpp>

static Body playerBody{100, 50, 128, 128, "#FFFFFF", 1.0f};
static Body wallBody{200, 200, 100, 100, "#FF0000", 1.0f};

static Sprite playerSprite;
static Sprite wallSprite;

static engine::Engine* gEngine = nullptr;

void update()
{
    float delta = engine::Engine::deltaTime();

    playerBody.update(delta);
    wallBody.update(delta);

    // physics::resolveCollision(playerBody, wallBody, CollisionType::Static);

    // Movement
    if (input::isKeyDown(KEY_S))
        playerBody.vy += 5.0f;
    if (input::isKeyDown(KEY_W))
        playerBody.vy -= 5.0f;
    if (input::isKeyDown(KEY_D))
        playerBody.vx += 5.0f;
    if (input::isKeyDown(KEY_A))
        playerBody.vx -= 5.0f;
}

void render()
{
    graphics::clearFrame("#FFFFFF");

    Renderer& renderer = gEngine->getRenderer();

    renderer.draw(playerSprite);
    renderer.draw(wallSprite);
}

int main()
{
    engine::Engine engine(1024, 768, "Alkane Engine", nullptr, nullptr);
    gEngine = &engine;

    if (!engine.init())
        return -1;

    GLuint tex = loadTexture("assets/wall.jpg", GL_NEAREST);

    // Player sprite
    playerSprite.body = &playerBody;
    playerSprite.texture = tex;

    // Wall sprite (no texture = colored quad)
    wallSprite.body = &wallBody;
    wallSprite.texture = 0;

    engine.setUpdate(update);
    engine.setRender(render);
    engine.run();

    return 0;
}