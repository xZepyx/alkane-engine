#include <alkane/alkane.hpp>
#include <cmath>
#include <vector>

static Body playerBody{100, 50, 128, 128, "#FFFFFF", 1.0f};
static Body wallBody{200, 200, 100, 100, "#FF0000", 1.0f};

static Sprite2D playerSprite;
static Sprite2D wallSprite;

static Mesh2D pentagonMesh;
static Mesh2D hexagonMesh;
static Mesh2D heptagonMesh;

static engine::Engine* gEngine = nullptr;

// Helper to create regular polygons
void createPolygon(Mesh2D& mesh, float cx, float cy, float radius, int sides) {
    mesh.vertices.clear();
    mesh.indices.clear();

    for (int i = 0; i < sides; i++) {
        float angle = 2.0f * M_PI * i / sides;
        Vertex2D v;
        v.position = Vector2{cx + radius * cos(angle), cy + radius * sin(angle)};
        v.uv = Vector2{0.0f, 0.0f}; // no texture
        v.r = 1.0f; v.g = 1.0f; v.b = 1.0f; v.a = 1.0f;
        mesh.vertices.push_back(v);
    }

    // Create triangle fan indices
    for (int i = 1; i < sides - 1; i++) {
        mesh.indices.push_back(0);
        mesh.indices.push_back(i);
        mesh.indices.push_back(i + 1);
    }

    mesh.drawMode = GL_TRIANGLES;
    mesh.texture = loadTexture("assets/wall.jpg", GL_NEAREST);
}

void update()
{
    float delta = engine::Engine::deltaTime();

    playerBody.update(delta);
    wallBody.update(delta);

    physics::resolveCollision(playerBody, wallBody, CollisionType::Static);

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

    renderer.draw(pentagonMesh);
    renderer.draw(hexagonMesh);
    renderer.draw(heptagonMesh);
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

    // Create meshes
    createPolygon(pentagonMesh, 500, 150, 50, 5);
    createPolygon(hexagonMesh, 650, 150, 50, 6);
    createPolygon(heptagonMesh, 800, 150, 50, 7);

    engine.setUpdate(update);
    engine.setRender(render);
    engine.run();

    return 0;
}