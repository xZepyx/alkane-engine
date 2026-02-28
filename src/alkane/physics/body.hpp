#pragma once
#include <alkane/geometry/box2d.hpp>
#include <alkane/physics/constants.hpp>
#include <string>

struct Body {
    // Position and size
    float x = 0.0f;
    float y = 0.0f;
    float width = 64.0f;
    float height = 64.0f;

    // Color (hex string) and alpha
    std::string hexColor = "#FFFFFF";
    float alpha = 1.0f;

    // Rotation
    float angle = 0.0f; // degrees

    // Velocity
    float vx = 0.0f;
    float vy = 0.0f;

    // Hitbox
    float hitboxX = 0.0f;
    float hitboxY = 0.0f;
    float hitboxW = 0.0f;
    float hitboxH = 0.0f;

    // Gravity toggle
    bool useGravity = false;

    // Update
    void update(float delta, float gravity = 0.0f) {
        if (useGravity)
            vy -= gravity * delta;
        x += vx * delta;
        y += vy * delta;
    }

    /* void draw() const {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (tex != 0)
            glEnable(GL_TEXTURE_2D);
        else
            glDisable(GL_TEXTURE_2D);

        if (tex != 0)
            glBindTexture(GL_TEXTURE_2D, tex);

        glPushMatrix();

        // Translate to center for rotation
        glTranslatef(x + width * 0.5f, y + height * 0.5f, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-width * 0.5f, -height * 0.5f, 0.0f);

        // Color
        float r = 1.0f, g = 1.0f, b = 1.0f;
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
        glColor4f(r, g, b, alpha);

        glBegin(GL_QUADS);
        if (tex != 0)
            glTexCoord2f(0, 1);
        glVertex2f(0, 0);
        if (tex != 0)
            glTexCoord2f(0, 0);
        glVertex2f(0, height);
        if (tex != 0)
            glTexCoord2f(1, 0);
        glVertex2f(width, height);
        if (tex != 0)
            glTexCoord2f(1, 1);
        glVertex2f(width, 0);

        if (tex == 0) { // plain colored quad
            glVertex2f(0, 0);
            glVertex2f(0, height);
            glVertex2f(width, height);
            glVertex2f(width, 0);
        }
        glEnd();

        glPopMatrix();

        if (tex != 0)
            glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    } */

    // for collision
    Box2D bounds() const {
        float w = hitboxW > 0 ? hitboxW : width;
        float h = hitboxH > 0 ? hitboxH : height;
        return {x + hitboxX, y + hitboxY, w, h};
    }
};