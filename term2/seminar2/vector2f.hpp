#pragma once
#include <cmath>
#include <iostream>

struct Vector2f
{
    float x;
    float y;

    Vector2f operator+(const Vector2f& v) const {
        return Vector2f{x + v.x, y + v.y};
    }

    Vector2f operator-(const Vector2f& v) const {
        return Vector2f{x - v.x, y - v.y};
    }

    Vector2f operator*(float scalar) const {
        return Vector2f{x * scalar, y * scalar};
    }

    float operator*(const Vector2f& v) const {
        return x * v.x + y * v.y;
    }

    Vector2f operator+() const {
        return *this;
    }

    Vector2f operator-() const {
        return Vector2f{-x, -y};
    }

    bool operator==(const Vector2f& v) const { 
        return x == v.x && y == v.y;
    }
    
    Vector2f& operator+=(const Vector2f& v) { 
        x += v.x;
        y += v.y;
        return *this;
    }
    
    Vector2f& operator-=(const Vector2f& v) { 
        x -= v.x;
        y -= v.y;
        return *this;
    }
    
    bool operator!=(const Vector2f& v) const {
        return !(*this == v);
    }

    Vector2f& operator*=(float scalar) { 
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2f& operator/=(float scalar) { 
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const Vector2f& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Vector2f& v) {
    in >> v.x >> v.y;
    return in;
}

Vector2f operator*(float scalar, const Vector2f& v) {
    return Vector2f{v.x * scalar, v.y * scalar};
}