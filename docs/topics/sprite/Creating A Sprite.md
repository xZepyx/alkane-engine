# Creating A Sprite

To create a sprite we first need to import the sprites header: `#include <alkane/sprite.hpp>`

After that we create the sprite.

```cpp
Sprite sprite = { Body { 100, 50, 128, 128, "#FFFFFF", 1.0f}, texture };
```

Explanation of the properties:

Inside the sprite we create a body which requires the following data:

```
{.x=200, .y=200, .width=100, .height=100, .hexColor="#FF0000"};
```

* This is because sprite itself is a child of it's parent 'body'.
* Sprites contains a body inside it and has a texture property.

After creating the sprite we need to draw/render it on the screen. To do so we need to call the sprite's draw function in the render loop like:

```cpp
sprite.draw();
```

If you did everything correctly you will see a sprite on the coords: 200,200 with a size of 128x128 inside the window.

> [!NOTE]
> If you don't have a texture you can define a hex color instead.

Sprite struct for clarity:
```cpp
struct Sprite {
    Body body;      // composition: sprite has a body
    GLuint tex = 0; // texture id

    void update(float delta) {
        body.update(delta, physics::gravity);
    }

    void draw() {
        // Render logic is done here
    }

    Body getAABB() const {
        return body.getAABB();
    }
};
```

If you want to know about the 'body' struct you may read the documentation about [Physics Body](../physics/body/Body.md)

To learn how to load texture you may read the [Texture Documentation](../textures/Loading%20Textures.md)
