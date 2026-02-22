# Input

Now that you have a window and a running loop, you probably want the player to actually do something.

First include the input header.

```
#include <alkane/input.hpp>
```

The engine internally calls the input update every frame inside the main loop.

---

### Keyboard

You can check keyboard state using three common queries.

```
input::isKeyDown(KEY_A);
input::isKeyPressed(KEY_A);
input::isKeyReleased(KEY_A);
```

Behavior:

* isKeyDown → key is currently held
* isKeyPressed → key was pressed this frame (edge trigger)
* isKeyReleased → key was released this frame

Example:

```
void update() {
    if (input::isKeyPressed(KEY_SPACE)) {
        // jump
    }

    if (input::isKeyDown(KEY_W)) {
        // move forward
    }
}
```

---

### Mouse Buttons

Mouse buttons follow the same pattern.

```
input::isMouseDown(MOUSE_LEFT);
input::isMousePressed(MOUSE_LEFT);
input::isMouseReleased(MOUSE_LEFT);
```

Example:

```
void update() {
    if (input::isMousePressed(MOUSE_LEFT)) {
        // shoot
    }
}
```

---

### Mouse Position

You can query the mouse position at any time.

```
double x, y;
input::getMousePosition(x, y);
```

Example:

```
void update() {
    double x, y;
    input::getMousePosition(x, y);

    // use x and y
}
```

---

### Key Constants

Alkane exposes readable constants instead of raw GLFW values.

Examples:

```
KEY_A
KEY_SPACE
KEY_ESCAPE
KEY_LEFT
KEY_F1
```

Categories include:

* Letters
* Numbers
* Function keys
* Arrows
* Navigation keys
* Modifiers (shift / ctrl / alt / super)
* Locks
* Symbols / punctuation

---

### Mouse Constants

Mouse constants are also provided.

```
MOUSE_LEFT
MOUSE_RIGHT
MOUSE_MIDDLE
MOUSE_4
MOUSE_5
```

---

### Important Notes

> [!NOTE]
> Input is frame-based.
> Pressed and Released only return true for a single frame.

> [!NOTE]
> You do not call any input update manually.
> The engine handles it inside `engine.run()`.

---

After this you should be able to move, click, and blame input bugs on something else.
