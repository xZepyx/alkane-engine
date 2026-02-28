#pragma once
#include <GLFW/glfw3.h>

namespace input {
// Keyboard
inline bool keysCurrent[GLFW_KEY_LAST] = {false};
inline bool keysPrevious[GLFW_KEY_LAST] = {false};

// Mouse
inline bool mouseCurrent[GLFW_MOUSE_BUTTON_LAST] = {false};
inline bool mousePrevious[GLFW_MOUSE_BUTTON_LAST] = {false};
inline double mouseX = 0.0;
inline double mouseY = 0.0;

// Update function, called once per frame inside Engine::run()
inline void update(GLFWwindow *window) {
    // Copy previous state
    for (int i = 0; i < GLFW_KEY_LAST; ++i)
        keysPrevious[i] = keysCurrent[i];
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
        mousePrevious[i] = mouseCurrent[i];

    // Poll current key and mouse states
    for (int i = 0; i < GLFW_KEY_LAST; ++i)
        keysCurrent[i] = (glfwGetKey(window, i) == GLFW_PRESS);
    for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
        mouseCurrent[i] = (glfwGetMouseButton(window, i) == GLFW_PRESS);

    // Update mouse position
    glfwGetCursorPos(window, &mouseX, &mouseY);
}

// Keyboard API
inline bool isKeyDown(int key) { return keysCurrent[key]; }
inline bool isKeyPressed(int key) { return keysCurrent[key] && !keysPrevious[key]; }
inline bool isKeyReleased(int key) { return !keysCurrent[key] && keysPrevious[key]; }

// Mouse API
inline bool isMouseDown(int button) { return mouseCurrent[button]; }
inline bool isMousePressed(int button) { return mouseCurrent[button] && !mousePrevious[button]; }
inline bool isMouseReleased(int button) { return !mouseCurrent[button] && mousePrevious[button]; }
inline void getMousePosition(double &x, double &y) {
    x = mouseX;
    y = mouseY;
}
} // namespace input

// Keyboard constants

// Letters
inline constexpr int KEY_A = GLFW_KEY_A;
inline constexpr int KEY_B = GLFW_KEY_B;
inline constexpr int KEY_C = GLFW_KEY_C;
inline constexpr int KEY_D = GLFW_KEY_D;
inline constexpr int KEY_E = GLFW_KEY_E;
inline constexpr int KEY_F = GLFW_KEY_F;
inline constexpr int KEY_G = GLFW_KEY_G;
inline constexpr int KEY_H = GLFW_KEY_H;
inline constexpr int KEY_I = GLFW_KEY_I;
inline constexpr int KEY_J = GLFW_KEY_J;
inline constexpr int KEY_K = GLFW_KEY_K;
inline constexpr int KEY_L = GLFW_KEY_L;
inline constexpr int KEY_M = GLFW_KEY_M;
inline constexpr int KEY_N = GLFW_KEY_N;
inline constexpr int KEY_O = GLFW_KEY_O;
inline constexpr int KEY_P = GLFW_KEY_P;
inline constexpr int KEY_Q = GLFW_KEY_Q;
inline constexpr int KEY_R = GLFW_KEY_R;
inline constexpr int KEY_S = GLFW_KEY_S;
inline constexpr int KEY_T = GLFW_KEY_T;
inline constexpr int KEY_U = GLFW_KEY_U;
inline constexpr int KEY_V = GLFW_KEY_V;
inline constexpr int KEY_W = GLFW_KEY_W;
inline constexpr int KEY_X = GLFW_KEY_X;
inline constexpr int KEY_Y = GLFW_KEY_Y;
inline constexpr int KEY_Z = GLFW_KEY_Z;

// Numbers
inline constexpr int KEY_0 = GLFW_KEY_0;
inline constexpr int KEY_1 = GLFW_KEY_1;
inline constexpr int KEY_2 = GLFW_KEY_2;
inline constexpr int KEY_3 = GLFW_KEY_3;
inline constexpr int KEY_4 = GLFW_KEY_4;
inline constexpr int KEY_5 = GLFW_KEY_5;
inline constexpr int KEY_6 = GLFW_KEY_6;
inline constexpr int KEY_7 = GLFW_KEY_7;
inline constexpr int KEY_8 = GLFW_KEY_8;
inline constexpr int KEY_9 = GLFW_KEY_9;

// Function keys
inline constexpr int KEY_F1 = GLFW_KEY_F1;
inline constexpr int KEY_F2 = GLFW_KEY_F2;
inline constexpr int KEY_F3 = GLFW_KEY_F3;
inline constexpr int KEY_F4 = GLFW_KEY_F4;
inline constexpr int KEY_F5 = GLFW_KEY_F5;
inline constexpr int KEY_F6 = GLFW_KEY_F6;
inline constexpr int KEY_F7 = GLFW_KEY_F7;
inline constexpr int KEY_F8 = GLFW_KEY_F8;
inline constexpr int KEY_F9 = GLFW_KEY_F9;
inline constexpr int KEY_F10 = GLFW_KEY_F10;
inline constexpr int KEY_F11 = GLFW_KEY_F11;
inline constexpr int KEY_F12 = GLFW_KEY_F12;
inline constexpr int KEY_F13 = GLFW_KEY_F13;
inline constexpr int KEY_F14 = GLFW_KEY_F14;
inline constexpr int KEY_F15 = GLFW_KEY_F15;
inline constexpr int KEY_F16 = GLFW_KEY_F16;
inline constexpr int KEY_F17 = GLFW_KEY_F17;
inline constexpr int KEY_F18 = GLFW_KEY_F18;
inline constexpr int KEY_F19 = GLFW_KEY_F19;
inline constexpr int KEY_F20 = GLFW_KEY_F20;
inline constexpr int KEY_F21 = GLFW_KEY_F21;
inline constexpr int KEY_F22 = GLFW_KEY_F22;
inline constexpr int KEY_F23 = GLFW_KEY_F23;
inline constexpr int KEY_F24 = GLFW_KEY_F24;
inline constexpr int KEY_F25 = GLFW_KEY_F25;

// Arrows
inline constexpr int KEY_UP = GLFW_KEY_UP;
inline constexpr int KEY_DOWN = GLFW_KEY_DOWN;
inline constexpr int KEY_LEFT = GLFW_KEY_LEFT;
inline constexpr int KEY_RIGHT = GLFW_KEY_RIGHT;

// Navigation
inline constexpr int KEY_HOME = GLFW_KEY_HOME;
inline constexpr int KEY_END = GLFW_KEY_END;
inline constexpr int KEY_PAGE_UP = GLFW_KEY_PAGE_UP;
inline constexpr int KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN;
inline constexpr int KEY_INSERT = GLFW_KEY_INSERT;
inline constexpr int KEY_DELETE = GLFW_KEY_DELETE;

// Modifiers
inline constexpr int KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;
inline constexpr int KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT;
inline constexpr int KEY_LEFT_CTRL = GLFW_KEY_LEFT_CONTROL;
inline constexpr int KEY_RIGHT_CTRL = GLFW_KEY_RIGHT_CONTROL;
inline constexpr int KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT;
inline constexpr int KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT;
inline constexpr int KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER;
inline constexpr int KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER;

// Locks
inline constexpr int KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK;
inline constexpr int KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK;
inline constexpr int KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK;

// Other common keys
inline constexpr int KEY_SPACE = GLFW_KEY_SPACE;
inline constexpr int KEY_ENTER = GLFW_KEY_ENTER;
inline constexpr int KEY_TAB = GLFW_KEY_TAB;
inline constexpr int KEY_ESCAPE = GLFW_KEY_ESCAPE;
inline constexpr int KEY_BACKSPACE = GLFW_KEY_BACKSPACE;
inline constexpr int KEY_PAUSE = GLFW_KEY_PAUSE;
inline constexpr int KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN;
inline constexpr int KEY_MENU = GLFW_KEY_MENU;

// Punctuation / symbols
inline constexpr int KEY_MINUS = GLFW_KEY_MINUS;
inline constexpr int KEY_EQUAL = GLFW_KEY_EQUAL;
inline constexpr int KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET;
inline constexpr int KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET;
inline constexpr int KEY_BACKSLASH = GLFW_KEY_BACKSLASH;
inline constexpr int KEY_SEMICOLON = GLFW_KEY_SEMICOLON;
inline constexpr int KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE;
inline constexpr int KEY_COMMA = GLFW_KEY_COMMA;
inline constexpr int KEY_PERIOD = GLFW_KEY_PERIOD;
inline constexpr int KEY_SLASH = GLFW_KEY_SLASH;
inline constexpr int KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT;

// Mouse Btns
inline constexpr int MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT;
inline constexpr int MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT;
inline constexpr int MOUSE_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE;
inline constexpr int MOUSE_4 = GLFW_MOUSE_BUTTON_4;
inline constexpr int MOUSE_5 = GLFW_MOUSE_BUTTON_5;