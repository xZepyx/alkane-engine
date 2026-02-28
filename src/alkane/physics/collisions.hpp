#pragma once
#include <alkane/geometry/geometry.hpp>
#include <alkane/physics/body.hpp>
#include <algorithm>

enum class CollisionType {
    Dynamic,
    Static
};

namespace physics {

// AABB collision check
inline bool checkCollision(const Box2 &a, const Box2 &b) { // takes two bouding boxes
    return (a.x < b.x + b.width) && (a.x + a.width > b.x) &&
           (a.y < b.y + b.height) && (a.y + a.height > b.y);
}

// Main collision resolver
inline void resolveCollision(Body &a, Body &b, CollisionType type) {
    Box2 A = a.bounds();
    Box2 B = b.bounds();

    if (!checkCollision(A, B))
        return;

    // Calculate overlaps
    float overlapX = std::min(A.x + A.width, B.x + B.width) - std::max(A.x, B.x);
    float overlapY = std::min(A.y + A.height, B.y + B.height) - std::max(A.y, B.y);

    if (overlapX <= 0 || overlapY <= 0)
        return;

    // Determine collision normal (axis of minimum penetration)
    float nx = 0.0f, ny = 0.0f;
    bool pushX = overlapX < overlapY;
    if (pushX)
        nx = (A.x < B.x) ? -1.0f : 1.0f;
    else
        ny = (A.y < B.y) ? -1.0f : 1.0f;

    // pos correction
    float percent = 0.8f; // push factor
    if (type == CollisionType::Static) {
        if (pushX)
            a.x += (A.x < B.x ? -overlapX : overlapX);
        else
            a.y += (A.y < B.y ? -overlapY : overlapY);
    } else {
        if (pushX) {
            a.x += (A.x < B.x ? -overlapX * 0.5f : overlapX * 0.5f);
            b.x += (A.x < B.x ? overlapX * 0.5f : -overlapX * 0.5f);
        } else {
            a.y += (A.y < B.y ? -overlapY * 0.5f : overlapY * 0.5f);
            b.y += (A.y < B.y ? overlapY * 0.5f : -overlapY * 0.5f);
        }
    }

    // (Static Collision) Zero Velcity Alone Normal
    if (type == CollisionType::Static) {
        if (pushX)
            a.vx = 0.0f;
        else
            a.vy = 0.0f;
        return;
    }

}

} // namespace physics