#pragma once
#include <string>
#include <sstream>
#include <glad/glad.h>

namespace colors {
inline void clearFrame(const std::string &hex) {
    if (hex.size() != 7 || hex[0] != '#')
        return;

    unsigned int color = 0;
    std::stringstream ss;
    ss << std::hex << hex.substr(1);
    ss >> color;

    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace colors
