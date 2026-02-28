#pragma once
#include <alkane/renderer/sprite.hpp>
#include <GLFW/glfw3.h>
#include <sstream>

class Renderer {
  public:
    void draw(const Sprite &sprite) {
        drawQuad(sprite);
    }

    /*void draw(Mesh& mesh) {
        drawMesh(mesh);
    }*/

  private:
    void drawQuad(const Sprite &sprite) {
        if (!sprite.body) return;

        const Body* body = sprite.body;

        float x = body->x;
        float y = body->y;
        float width  = body->width;
        float height = body->height;
        float angle  = body->angle;

        GLuint tex = sprite.texture;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (tex != 0)
            glEnable(GL_TEXTURE_2D);
        else
            glDisable(GL_TEXTURE_2D);

        if (tex != 0)
            glBindTexture(GL_TEXTURE_2D, tex);

        glPushMatrix();

        // transform
        glTranslatef(x + width * 0.5f, y + height * 0.5f, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-width * 0.5f, -height * 0.5f, 0.0f);

        // color parsing
        float r = 1.0f, g = 1.0f, b = 1.0f;

        const std::string& hexColor = sprite.body->hexColor;

        if (!hexColor.empty() && hexColor[0] == '#' && hexColor.size() == 7) {
            unsigned int ri, gi, bi;
            std::stringstream ss;

            ss << std::hex << hexColor.substr(1, 2);
            ss >> ri;
            ss.clear();

            ss << std::hex << hexColor.substr(3, 2);
            ss >> gi;
            ss.clear();

            ss << std::hex << hexColor.substr(5, 2);
            ss >> bi;

            r = ri / 255.0f;
            g = gi / 255.0f;
            b = bi / 255.0f;
        }

        glColor4f(r, g, b, sprite.body->alpha);

        glBegin(GL_QUADS);

        if (tex != 0) glTexCoord2f(0, 1);
        glVertex2f(0, 0);

        if (tex != 0) glTexCoord2f(0, 0);
        glVertex2f(0, height);

        if (tex != 0) glTexCoord2f(1, 0);
        glVertex2f(width, height);

        if (tex != 0) glTexCoord2f(1, 1);
        glVertex2f(width, 0);

        glEnd();

        glPopMatrix();

        if (tex != 0)
            glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    };
    /*void drawMesh(const Mesh& mesh);*/
};