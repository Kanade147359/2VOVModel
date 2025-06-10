#include "Vec2.hpp"
#include <cmath>

Vec2 Vec2::operator+(const Vec2& v) const { return {x+v.x, y+v.y}; }
Vec2 Vec2::operator-(const Vec2& v) const { return {x-v.x, y-v.y}; }
Vec2 Vec2::operator*(double s) const { return {x*s, y*s}; }
Vec2& Vec2::operator+=(const Vec2& v) { x+=v.x; y+=v.y; return *this;}
double Vec2::norm() const { return std::sqrt(x*x + y*y); }
Vec2 Vec2::normalized() const {
    double n = norm();
    return n > 1e-12 ? Vec2{x/n, y/n} : Vec2{0, 0};
} 

double Vec2::dot(const Vec2& v) const { return x*v.x + y*v.y; } 
