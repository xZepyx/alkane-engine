#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Mesh2D {
    public: 
        Mesh2D(const std::vector<float>& vertices) {
            vertexCount = vertices.size() / 3;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER,
                        vertices.size() * sizeof(float),
                        vertices.data(),
                        GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                3 * sizeof(float), (void*)0);

            glEnableVertexAttribArray(0);
            glBindVertexArray(0);

        }

        ~Mesh2D()
        {
            glDeleteBuffers(1, &VBO);
            glDeleteVertexArrays(1, &VAO);
        }

        void render() const
        {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        }

    private: 
        GLuint VAO = 0;
        GLuint VBO = 0;
        int vertexCount;
};