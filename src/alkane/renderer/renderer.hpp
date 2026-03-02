#pragma once
#include <glad/glad.h>

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

    private: 
        float projection[16]{};

};