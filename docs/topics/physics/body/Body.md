# Physics Body

This physics body is the primary parent for all other classes like Sprite. 

Structure:
```cpp
struct Body {
    // Position and size
    float x = 0.0f;
    float y = 0.0f;
    float width = 64.0f;
    float height = 64.0f;

    // Color (hex string) and alpha
    std::string hexColor = "#FFFFFF";
    float alpha = 1.0f;

    // Optional texture
    GLuint tex = 0; // 0 = no texture

    // Rotation
    float angle = 0.0f; // degrees

    // Velocity (optional, for movement)
    float vx = 0.0f;
    float vy = 0.0f;

    // Hitbox (optional smaller than rect)
    float hitboxX = 0.0f;
    float hitboxY = 0.0f;
    float hitboxW = 0.0f;
    float hitboxH = 0.0f;

    // Gravity toggle
    bool useGravity = false;

    // Update
    void update(float delta, float gravity = 0.0f) {
        if (useGravity)
            vy -= gravity * delta;
        x += vx * delta;
        y += vy * delta;
    }

    // Draw
    void draw() const {
        // Render logic
    }

    // AABB for collision
    Body getAABB() const {
        float w = hitboxW > 0 ? hitboxW : width;
        float h = hitboxH > 0 ? hitboxH : height;
        return {x + hitboxX, y + hitboxY, w, h};
    }
};
```

## Physics
To simulate physics we first need to call the body's update function in the main update loop.

```cpp
// Assuming that you have created the body by: 
// Body body = {xPos, YPos, width, height, hexColor}
body.update(engine::Engine::deltaTime());
```

Now you can modify the vx and vy properties to move the sprite (in the update function).

```cpp
body.vx += 1.0f;
body.vy += 1.0f;
```

If you want to move the sprite using WASD or do something when a key is pressed prefer reading [Input Documentation](../../input/Input.md).

You can also flip the useGravity bool to simulate gravity.

```
body.useGravity = true;
```
