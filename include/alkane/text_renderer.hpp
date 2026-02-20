#pragma once
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Glyph {
    GLuint tex;
    float width, height;
    float bearingX, bearingY;
    float advance;
};

struct Font {
    std::map<char, Glyph> glyphs;
    float size;
};

inline std::map<std::string, Font> fonts;

inline bool loadFont(const std::string &path, const std::string &name, float size = 48.0f) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        return false;

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
        return false;
    FT_Set_Pixel_Sizes(face, 0, size);

    Font f;
    f.size = size;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 32; c < 127; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            continue;

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0, GL_ALPHA, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Glyph g;
        g.tex = tex;
        g.width = (float)face->glyph->bitmap.width;
        g.height = (float)face->glyph->bitmap.rows;
        g.bearingX = (float)face->glyph->bitmap_left;
        g.bearingY = (float)face->glyph->bitmap_top;
        g.advance = (float)(face->glyph->advance.x >> 6);

        f.glyphs[c] = g;
    }

    fonts[name] = f;

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return true;
}

inline void drawText(float x, float y, const std::string &textStr,
                     const std::string &hexColor = "#000000",
                     const std::string &fontName = "") {

    if (fonts.find(fontName) == fonts.end())
        return;
    const Font &f = fonts[fontName];

    unsigned int color = 0;
    if (hexColor.size() == 7 && hexColor[0] == '#') {
        std::stringstream ss;
        ss << std::hex << hexColor.substr(1);
        ss >> color;
    }
    float r = ((color >> 16) & 0xFF) / 255.f;
    float g = ((color >> 8) & 0xFF) / 255.f;
    float b = (color & 0xFF) / 255.f;

    // push specific glyphs up/down
    static const std::map<char, float> glyphYOffsetFactor = {
        {'g', -0.2f},
        {'j', -0.10f},
        {'p', -0.2f},
        {'q', -0.2f},
        {'y', -0.2f},
        {'Q', -0.12f},
        {'a', -0.1f},
        {'l', 0.2f},
        {'i', 0.2f},
        {'k', 0.2f},
        {'h', 0.2f},
        {'t', 0.2f},
        {'e', -0.1f},
        {'d', 0.1f},
        {'b', 0.1f},
        {'c', -0.1f},
        {'f', 0.1f}};

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(r, g, b);
    glEnable(GL_TEXTURE_2D);

    for (unsigned char c : textStr) {
        if (f.glyphs.find(c) == f.glyphs.end())
            continue;

        const Glyph &g = f.glyphs.at(c);

        float xpos = x + g.bearingX;
        float ypos = y - (g.height - g.bearingY);

        // scale offset based on font size
        auto it = glyphYOffsetFactor.find(c);
        if (it != glyphYOffsetFactor.end()) {
            float scaledOffset = f.size * it->second;
            ypos -= scaledOffset; // subtract to push DOWN
        }

        float w = g.width;
        float h = g.height;

        glBindTexture(GL_TEXTURE_2D, g.tex);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(xpos, ypos);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(xpos, ypos + h);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(xpos + w, ypos + h);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(xpos + w, ypos);
        glEnd();

        x += g.advance;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}
