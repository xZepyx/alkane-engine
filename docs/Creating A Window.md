# Creating a Window
* Now as you may have setup your project. Let's start by creating a window.

First we include the **`engine`** and the **`graphics`** header for making the window.
```
#include <alkane/engine.hpp>
#include <alkane/graphics.hpp>
```

Now we create a **`main()`** function and construct the engine instance:

```
#include <alkane/engine.hpp>
#include <alkane/graphics.hpp>
int main() {
    // Create the engine instance
    engine::Engine engine(1024, 768, "Alkane Engine", nullptr, nullptr);

    // Initialize engine
    if (!engine.init()) {
        return -1; // if initialization failed
    }
}
```

> [!NOTE]
> As we progress the complete file will be shown in each step's code in some files for clarity.

Now we setup the user callbacks and the run function:

```
#include <alkane/engine.hpp>
#include <alkane/graphics.hpp>

void update() {
    // all game logic like physics etc. happens here
}

void render() {
    // All the drawing and rendering stuff happens here.

    // clear frame with white color
    colors::clearFrame("#FFFFFF");
}

int main() {
    // Create the engine instance
    engine::Engine engine(1024, 768, "Alkane Engine", nullptr, nullptr);

    // Initialize engine (GLFW + GLAD + viewport)
    if (!engine.init()) {
        return -1; // initialization failed
    }

    // Set user callbacks
    engine.setUpdate(update);
    engine.setRender(render);

    // Start the main loop (engine owns loop, swap/poll handled internally)
    engine.run();

    return 0;
}
```

After this you should get a empty window when you run a code.
