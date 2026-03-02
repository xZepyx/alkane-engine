#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) : width(width), height(height)
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to init GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title, monitor, share);

        if (!handle) {
            glfwTerminate();
            throw std::runtime_error("Failed to create window");
        }

        glfwSetWindowUserPointer(handle, this);
        glfwSetFramebufferSizeCallback(handle, framebufferCallback);

        glfwMakeContextCurrent(handle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(handle);
            glfwTerminate();
            throw std::runtime_error("Failed to init GLAD");
        }

        std::cout << "Alkane: Window initialized successfully\n";

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(handle, framebufferCallback);
    }

    ~Window() {
        if (handle)
            glfwDestroyWindow(handle);

        glfwTerminate(); // only safe if single-window engine
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(handle);
    }

    void swapBuffers() {
        glfwSwapBuffers(handle);
    }

    void pollEvents() {
        glfwPollEvents();
    }

    GLFWwindow* getNative() const {
        return handle;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

private:
    GLFWwindow* handle = nullptr;
    int width = 0;
    int height = 0;

    static void framebufferCallback(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);

        Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (self) {
            self->width = w;
            self->height = h;
        }
    }
};
