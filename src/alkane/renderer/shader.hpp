#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader 
{
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath) {
            std::string vSrc = readFile(vertexPath);
            std::string fSrc = readFile(fragmentPath);

            GLuint vertex = compile(GL_VERTEX_SHADER, vSrc.c_str());
            GLuint fragment = compile(GL_FRAGMENT_SHADER, fSrc.c_str());

            program = glCreateProgram();
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);
            glLinkProgram(program);

            GLint success;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                char info[512];
                glGetProgramInfoLog(program, 512, nullptr, info);
                glDeleteShader(vertex);
                glDeleteShader(fragment);
                throw std::runtime_error(info);
            }

            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        ~Shader() {
            if (program) 
                glDeleteProgram(program);
        }

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept {
            program = other.program;
            other.program = 0;
        }

        Shader& operator=(Shader&& other) noexcept {
            if (this != &other) {
                glDeleteProgram(program);
                program = other.program;
                other.program = 0;
            }
            return *this;
        }

        void use() const {
            glUseProgram(program);
        }

        GLint id() const { return program; }

        void setFloat(const std::string& name,float v) const {
            glUniform1f(location(name), v);
        }

        void setInt(const std::string& name, int v) const {
            glUniform1i(location(name), v);
        }

        void setVec2(const std::string& name, float x, float y) const {
            glUniform2f(location(name), x, y);
        }

        void setVec3(const std::string& name, float x, float y, float z) const {
            glUniform3f(location(name), x, y, z);
        }

        void setVec4(const std::string& name,
                    float x, float y,
                    float z, float w) const {
            glUniform4f(location(name), x, y, z, w);
        }

        void setMat4(const std::string& name, const float* m) const {
            glUniformMatrix4fv(location(name), 1, GL_FALSE, m);
        }

    private:
        GLuint program = 0;

        static GLuint compile(GLenum type, const char* src) {
            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            GLint success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                char info[512];
                glGetShaderInfoLog(shader, 512, nullptr, info);
                throw std::runtime_error(info);
            }

            return shader;
        }

        static std::string readFile(const std::string& path) {
            std::ifstream file(path);
            if (!file.is_open())
                throw std::runtime_error("Failed to open shader file: " + path);

            std::stringstream ss;
            ss << file.rdbuf();
            return ss.str();
        }

        GLint location(const std::string& name) const {
            return glGetUniformLocation(program, name.c_str());
        }
};