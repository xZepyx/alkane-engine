# Sprite Physics

Now we're talking about sprite physics.

Sprite is essentially is a body so it inherits all the physics properties from the body.

You should read the [Physics Body Documentation](../physics/body/Body.md) to learn about how to simulate physics.

## Accessing Physics Prperties
This is a list for how you can access the properties of the body inside the sprite. Make sure to read the [Physics Body Documentation](../physics/body/Body.md) and then continue

```cpp
// Assuming you have created the sprite
Sprite sprite = { Body { 100, 50, 128, 128, "#FFFFFF", 1.0f}, texture };

// Note that all the physics stuff should be called in the update loop.
// Updating the sprite:
sprite.update(engine::Engine::deltaTime());

// Modifying the vx,vy,useGravity properties:
sprite.body.vx += 1.0f
sprite.body.vy += 1.0f
sprite.body.useGravity = true;
```
