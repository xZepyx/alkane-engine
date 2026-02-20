#pragma once
#include <alkane/sprite.hpp> // for getting Rect and other types

enum class CollisionType {
    Dynamic,
    Static
};

namespace physics {

inline bool checkCollision(const Body &a, const Body &b) {
    return (a.x < b.x + b.width) && (a.x + a.width > b.x) &&
           (a.y < b.y + b.height) && (a.y + a.height > b.y);
}

// Resolve collisions
inline void resolveCollision(Body &a, Body &b, CollisionType type) {
    Body A = a.getAABB();
    Body B = b.getAABB();

    if (!checkCollision(A, B))
        return;

    float aLeft = A.x;
    float aRight = A.x + A.width;
    float aBottom = A.y;
    float aTop = A.y + A.height;

    float bLeft = B.x;
    float bRight = B.x + B.width;
    float bBottom = B.y;
    float bTop = B.y + B.height;

    float overlapX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
    float overlapY = std::min(aTop, bTop) - std::max(aBottom, bBottom);

    // normals
    float nx = 0.0f;
    float ny = 0.0f;

    if (overlapX < overlapY) {
        nx = (A.x < B.x) ? -1.0f : 1.0f;
    } else {
        ny = (A.y < B.y) ? -1.0f : 1.0f;
    }

    // positional correction
    if (type == CollisionType::Static) {
        // move only A (dynamic body against static world)

        if (overlapX < overlapY) {
            if (A.x < B.x)
                a.x -= overlapX;
            else
                a.x += overlapX;
        } else {
            if (A.y < B.y)
                a.y -= overlapY;
            else
                a.y += overlapY;
        }
    } else {
        // dynamic vs dynamic → split correction
        if (overlapX < overlapY) {
            if (A.x < B.x) {
                a.x -= overlapX * 0.5f;
                b.x += overlapX * 0.5f;
            } else {
                a.x += overlapX * 0.5f;
                b.x -= overlapX * 0.5f;
            }
        } else {
            if (A.y < B.y) {
                a.y -= overlapY * 0.5f;
                b.y += overlapY * 0.5f;
            } else {
                a.y += overlapY * 0.5f;
                b.y -= overlapY * 0.5f;
            }
        }
    }
    // Static Collision
    if (type == CollisionType::Static) {
        if (nx != 0)
            a.vx = 0;
        if (ny != 0)
            a.vy = 0;
        return;
    }

    // impulse physics collision
    float rvx = a.vx - b.vx;
    float rvy = a.vy - b.vy;

    float velAlongNormal = rvx * nx + rvy * ny;

    if (velAlongNormal > -0.01f) {
        return;
    }

    float restitution = 0.01f;

    float j = -(1.0f + restitution) * velAlongNormal;
    j /= 2.0f;              // equal mass
    j = std::min(j, 50.0f); // clamp impulse

    float impulseX = j * nx;
    float impulseY = j * ny;

    a.vx += -impulseX;
    a.vy += -impulseY;
    b.vx += impulseX;
    b.vy += impulseY;
}
} // namespace physics