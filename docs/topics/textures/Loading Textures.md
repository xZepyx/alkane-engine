# Loading a Texture

* At some point colors are not enough.
* You will want images.

First include the textures header.

```
#include <alkane/textures/textures.hpp>
```

Textures are loaded from disk and uploaded to the GPU.

---

### Loading a Texture

Use the texture loader function.

```
GLuint tex = loadTexture("assets/wall.jpg", GL_NEAREST);
```

Parameters:

* path → file path to the image
* filterType → GL_NEAREST or GL_LINEAR

Behavior:

* Loads image from disk
* Forces RGBA format
* Uploads texture to GPU
* Applies filtering and wrapping

If loading fails, the function returns 0.

Which means the GPU politely refused.

---

### Using a Texture With a Sprite

Sprites accept a texture id.

```
GLuint tex = loadTexture("assets/wall.jpg", GL_NEAREST);

Sprite sprite = {
    Body{
        100,
        50,
        128,
        128,
        "#FFFFFF",
        1.0f},
    tex};
```

The sprite will render using that texture.

---

### Example

Minimal example inside a game.

```
Sprite sprite;

int main() {
    engine::Engine engine(1024, 768, "Alkane Engine", nullptr, nullptr);

    if (!engine.init())
        return -1;

    GLuint tex = loadTexture("assets/wall.jpg", GL_NEAREST);

    sprite = {
        Body{100, 50, 128, 128, "#FFFFFF", 1.0f},
        tex};

    engine.setUpdate(update);
    engine.setRender(render);
    engine.run();
}
```

---

### Filtering

Common options:

```
GL_NEAREST  // pixelated
GL_LINEAR   // smooth
```

Use NEAREST for pixel art.
Use LINEAR for everything else.

Arguments may start later.

---

### Important Notes

> [!NOTE]
> Texture loading must happen after engine.init().

> [!NOTE]
> The returned value is a GPU texture id.

> [!NOTE]
> Reuse textures instead of loading every frame.

> [!NOTE]
> This is very **important** only load texture in the main/render/update loop not on a global level or it will cause a segfault. This is because the engine isn't initialized yet and if you try to call something before that it will cause a segfault.
---

After this your rectangles should look less like rectangles.
