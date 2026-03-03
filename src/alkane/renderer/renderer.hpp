#pragma once
#include <glad/glad.h>

#include "math/ortho.hpp"

class Scene; // forward declare

class Renderer 
{
    public:
        Renderer() = default;

        void clear(float r, float g, float b, float a = 1.0f) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        const float* getProjection() const {
            return projection;
        }

        void setOrtho(float width, float height) {
            ortho::buildOrtho(
                0.0f, width,
                height, 0.0f,
                projection
            );
        }

        void render(const Scene& scene);


    private: 
        float projection[16]{};

};


// definition for Renderer::render
#include "engine/scene.hpp"

inline void Renderer::render(const Scene& scene)
{
    scene.submit(*this);
}