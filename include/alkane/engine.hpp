#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <alkane/input.hpp>

namespace engine {

class Engine {
  public:
    // Constructor and Deconstructor
    Engine(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
        : width(width), height(height), title(title), window(nullptr) {}
    ~Engine() {
        if (window)
            glfwTerminate();
    }

    // setter functions
    void setUpdate(void (*cb)()) { update = cb; }
    void setRender(void (*cb)()) { render = cb; }

    bool init() {

        if (!glfwInit()) { // init glfw
            return false;
        }

        window = glfwCreateWindow(width, height, title, nullptr, nullptr); // keep monitor and share nullptr for simplicity (atleast for now).

        if (!window) {
            return false;
        } // if window does not gets created then return false

        glfwMakeContextCurrent(window); // set window as main context for the main thread

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwTerminate();
            return false;
        } // init glad

        glViewport(0, 0, width, height); // setup viewport

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1); // pixel space (top-left origin)

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // update the viewport size when the user resizes the window
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        return true;
    }

    void run() { // engine owns main loop; user code runs via callbacks
        float lastTime = glfwGetTime();
        while (!glfwWindowShouldClose(window)) {

            float currentTime = glfwGetTime();
            delta = currentTime - lastTime; // calculate delta
            lastTime = currentTime;

            input::update(window); // update keyboard/mouse states

            if (update)
                update();
            if (render)
                render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    static float deltaTime() { return delta; }

  private:
    int width;
    int height;
    const char *title;
    GLFWwindow *window;
    void (*update)() = nullptr;
    void (*render)() = nullptr;

    inline static float delta = 0.0f; // delta

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) { // framebuffer callback for window resizing
        glViewport(0, 0, width, height);
    }
};

} // namespace engine