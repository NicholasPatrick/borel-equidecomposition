//
// Created by Nicholas Patrick on 10/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_VEC2_H
#define BOREL_EQUIDECOMPOSITION_VEC2_H


struct vec2 {
    double x, y;
    explicit vec2(double = 0, double = 0);
    vec2 &operator+=(const vec2 &);
    vec2 &operator-=(const vec2 &);
    [[nodiscard]] vec2 operator-() const;
    [[nodiscard]] vec2 operator+(const vec2 &) const;
    [[nodiscard]] vec2 operator-(const vec2 &) const;
    [[nodiscard]] bool operator==(const vec2 &) const;
    [[nodiscard]] bool operator!=(const vec2 &) const;
    [[nodiscard]] double dot(const vec2 &) const;
    [[nodiscard]] double cross(const vec2 &) const;
    [[nodiscard]] double cross(const vec2 &, const vec2 &) const;
    [[nodiscard]] double length() const;

};


#endif //BOREL_EQUIDECOMPOSITION_VEC2_H
