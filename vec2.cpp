//
// Created by Nicholas Patrick on 10/8/23.
//

#include <cmath>
#include "vec2.h"

vec2::vec2(double x, double y) : x(x), y(y) {}

vec2 &vec2::operator+=(const vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

vec2 &vec2::operator-=(const vec2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

vec2 vec2::operator+(const vec2 &rhs) const {
    return vec2(x + rhs.x, y + rhs.y);
}

vec2 vec2::operator-(const vec2 &rhs) const {
    return vec2(x - rhs.x, y - rhs.y);
}

double vec2::dot(const vec2 &rhs) const {
    return x * rhs.x + y * rhs.y;
}

double vec2::cross(const vec2 &rhs) const {
    return x * rhs.y - y * rhs.x;
}

double vec2::cross(const vec2 &b, const vec2 &c) const {
    return this->operator-(b).cross(this->operator-(c));
}

bool vec2::operator==(const vec2 &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool vec2::operator!=(const vec2 &rhs) const {
    return x != rhs.x || y != rhs.y;
}

vec2 vec2::operator-() const {
    return vec2(-x, -y);
}

double vec2::length() const {
    return hypot(x, y);
}
