#pragma once

#include <cmath>

struct Vec2 {
    double x, y;
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(double s) const;
    Vec2& operator+=(const Vec2& v);
    double norm() const;
    Vec2 normalized() const;
    double dot(const Vec2& v) const; 
};

