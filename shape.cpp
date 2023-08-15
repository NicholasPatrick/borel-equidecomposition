//
// Created by Nicholas Patrick on 10/8/23.
//

#include <cfloat>
#include <algorithm>
#include <cmath>
#include "shape.h"

polygon::polygon(const std::vector<vec2> &points) : points(points) {}

double polygon::area() const {
    double ret = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        size_t j = i + 1 == points.size() ? 0 : i + 1;
        ret += points[i].cross(points[j]);
    }
    return ret / 2;
}

double polygon::top() const {
    double ret = DBL_MAX;
    for (const auto &point : points)
        ret = std::min(ret, point.x);
    return ret;
}

double polygon::bottom() const {
    double ret = DBL_MIN;
    for (const auto &point : points)
        ret = std::max(ret, point.x);
    return ret;
}

double polygon::left() const {
    double ret = DBL_MAX;
    for (const auto &point : points)
        ret = std::min(ret, point.y);
    return ret;
}

double polygon::right() const {
    double ret = DBL_MIN;
    for (const auto &point : points)
        ret = std::max(ret, point.y);
    return ret;
}

void polygon::translate(vec2 vec2) {
    for (auto &point: points)
        point += vec2;
}

void polygon::scale(double scale) {
    for (auto &point: points) {
        point.x *= scale;
        point.y *= scale;
    }
}

bool polygon::in(vec2 p) const {
    auto is_bot = [&](vec2 q) {
        if (p.x != q.x) return p.x < q.x;
        return p.y < q.y;
    };
    bool ret = false;
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i] == p) return false;
        size_t j = i + 1 == points.size() ? 0 : i + 1;
        bool i_bot = is_bot(points[i]);
        bool j_bot = is_bot(points[j]);
        double cross = p.cross(points[i], points[j]);
        if (i_bot != j_bot) {
            if (cross == 0) return false;
            ret = ret ^ i_bot ^ (cross > 0);
        }
    }
    return ret;
}

[[maybe_unused]] disjoint_union::disjoint_union(const std::vector<polygon> &v) : v(v) {}

double disjoint_union::area() const {
    double ret = 0;
    for (const auto &part : v)
        ret += part.area();
    return ret;
}

double disjoint_union::top() const {
    double ret = DBL_MAX;
    for (const auto &part : v)
        ret = std::min(ret, part.top());
    return ret;
}

double disjoint_union::bottom() const {
    double ret = DBL_MIN;
    for (const auto &part : v)
        ret = std::max(ret, part.bottom());
    return ret;
}

double disjoint_union::left() const {
    double ret = DBL_MAX;
    for (const auto &part : v)
        ret = std::min(ret, part.left());
    return ret;
}

double disjoint_union::right() const {
    double ret = DBL_MIN;
    for (const auto &part : v)
        ret = std::max(ret, part.right());
    return ret;
}

void disjoint_union::translate(vec2 vec2) {
    for (auto &part: v)
        part.translate(vec2);
}

void disjoint_union::scale(double scale) {
    for (auto &part: v)
        part.scale(scale);
}

bool disjoint_union::in(vec2 p) const {
    return any_of(v.begin(), v.end(), [&p](auto part) {return part.in(p);});
}

circle::circle(vec2 o, double r) : o(o), r(r) {}

double circle::area() const {
    return acos(-1.0) * r * r;
}

double circle::top() const {
    return o.x - r;
}

double circle::bottom() const {
    return o.x + r;
}

double circle::left() const {
    return o.y - r;
}

double circle::right() const {
    return o.y + r;
}

void circle::translate(vec2 vec2) {
    o += vec2;
}

void circle::scale(double scale) {
    o.x *= scale;
    o.y *= scale;
    r *= scale;
}

bool circle::in(vec2 p) const {
    return (p - o).length() < r;
}
