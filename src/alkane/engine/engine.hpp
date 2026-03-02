#pragma once

#include "platform/window.hpp"
#include "renderer/renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Engine 
{
    public:
        Engine(Window& window)
            : window(window) {}

        void setUpdate(void (*cb)()) { update = cb; }
        void setRender(void (*cb)()) { render = cb; }

        Renderer& getRenderer() {
            return renderer;
        }

        static float delta() {
            return deltaTime;
        }

        void run() {
            lastTime = glfwGetTime();

            while (!window.shouldClose()) {

                float current = glfwGetTime();
                deltaTime = current - lastTime;
                lastTime = current;

                renderer.clear(1.0f,1.0f,1.0f,1.0f); // clear frame

                if (update)
                    update();

                if (render)
                    render();

                window.swapBuffers();
                window.pollEvents();
            }
        }

    private:
        Window& window;
        Renderer renderer;

        void (*update)() = nullptr;
        void (*render)() = nullptr;

        inline static float deltaTime;
        float lastTime = 0.0f;
};
