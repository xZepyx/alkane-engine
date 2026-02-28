#pragma once
#include <cmath>

struct Vector2 {
    float x;
    float y;

    // Constructors
    constexpr Vector2() : x(0.0f), y(0.0f) {}
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    // Static constants
    static constexpr Vector2 zero() { return Vector2(0.0f, 0.0f); }
    static constexpr Vector2 one()  { return Vector2(1.0f, 1.0f); }
    static constexpr Vector2 up()   { return Vector2(0.0f, 1.0f); }
    static constexpr Vector2 down() { return Vector2(0.0f,-1.0f); }
    static constexpr Vector2 left() { return Vector2(-1.0f,0.0f); }
    static constexpr Vector2 right(){ return Vector2(1.0f, 0.0f); }

    // Magnitude
    float sqrMagnitude() const {
        return x * x + y * y;
    }

    float magnitude() const {
        return std::sqrt(sqrMagnitude());
    }

    // Normalization
    Vector2 normalized() const {
        float len = magnitude();
        if (len == 0.0f) return Vector2(0.0f, 0.0f);
        return Vector2(x / len, y / len);
    }

    void normalize() {
        float len = magnitude();
        if (len == 0.0f) return;
        x /= len;
        y /= len;
    }

    // Dot product
    static float dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }

    // 2D Cross product (scalar result)
    static float cross(const Vector2& a, const Vector2& b) {
        return a.x * b.y - a.y * b.x;
    }

    // Distance
    static float distance(const Vector2& a, const Vector2& b) {
        return (b - a).magnitude();
    }

    static float sqrDistance(const Vector2& a, const Vector2& b) {
        return (b - a).sqrMagnitude();
    }

    // Angle (radians)
    static float angle(const Vector2& a, const Vector2& b) {
        float d = dot(a, b);
        float m = a.magnitude() * b.magnitude();
        if (m == 0.0f) return 0.0f;
        return std::acos(d / m);
    }

    // Signed angle (radians)
    static float signedAngle(const Vector2& a, const Vector2& b) {
        return std::atan2(cross(a, b), dot(a, b));
    }

    // Lerp
    static Vector2 lerp(const Vector2& a, const Vector2& b, float t) {
        return a + (b - a) * t;
    }

    // Clamp magnitude
    static Vector2 clampMagnitude(const Vector2& v, float maxLen) {
        float sqrLen = v.sqrMagnitude();
        if (sqrLen > maxLen * maxLen) {
            return v.normalized() * maxLen;
        }
        return v;
    }

    // Projection
    static Vector2 project(const Vector2& a, const Vector2& b) {
        float denom = b.sqrMagnitude();
        if (denom == 0.0f) return zero();
        return b * (dot(a, b) / denom);
    }

    // Reflection
    static Vector2 reflect(const Vector2& dir, const Vector2& normal) {
        return dir - normal * (2.0f * dot(dir, normal));
    }

    // Perpendicular
    Vector2 perpendicular() const {
        return Vector2(-y, x);
    }

    // Operators
    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator*(float s) const {
        return Vector2(x * s, y * s);
    }

    Vector2 operator/(float s) const {
        return Vector2(x / s, y / s);
    }

    Vector2& operator+=(const Vector2& v) {
        x += v.x; y += v.y; return *this;
    }

    Vector2& operator-=(const Vector2& v) {
        x -= v.x; y -= v.y; return *this;
    }

    Vector2& operator*=(float s) {
        x *= s; y *= s; return *this;
    }

    Vector2& operator/=(float s) {
        x /= s; y /= s; return *this;
    }

    bool operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector2& v) const {
        return !(*this == v);
    }
};