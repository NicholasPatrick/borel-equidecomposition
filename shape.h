//
// Created by Nicholas Patrick on 10/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_SHAPE_H
#define BOREL_EQUIDECOMPOSITION_SHAPE_H

#include <vector>
#include "vec2.h"

class shape {
public:
    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double left() const = 0;
    [[nodiscard]] virtual double right() const = 0;
    [[nodiscard]] virtual double top() const = 0;
    [[nodiscard]] virtual double bottom() const = 0;
    virtual void translate(vec2) = 0;
    virtual void scale(double) = 0;
    [[nodiscard]] virtual bool in(vec2 p) const = 0;
};

class polygon : public shape {
    std::vector<vec2> points;
public:
    explicit polygon(const std::vector<vec2> &);
    [[nodiscard]] double area() const override;
    [[nodiscard]] double left() const override;
    [[nodiscard]] double right() const override;
    [[nodiscard]] double top() const override;
    [[nodiscard]] double bottom() const override;
    void translate(vec2) override;
    void scale(double) override;
    [[nodiscard]] bool in(vec2) const override;
};

class circle : public shape {
public:
    vec2 o;
    double r;
    explicit circle(vec2 o = vec2(), double r = 1);
    [[nodiscard]] double area() const override;
    [[nodiscard]] double left() const override;
    [[nodiscard]] double right() const override;
    [[nodiscard]] double top() const override;
    [[nodiscard]] double bottom() const override;
    void translate(vec2) override;
    void scale(double) override;
    [[nodiscard]] bool in(vec2) const override;
};

class disjoint_union : public shape {
    std::vector<polygon> v;
public:
    [[maybe_unused]] explicit disjoint_union(const std::vector<polygon> &);
    [[nodiscard]] double area() const override;
    [[nodiscard]] double left() const override;
    [[nodiscard]] double right() const override;
    [[nodiscard]] double top() const override;
    [[nodiscard]] double bottom() const override;
    void translate(vec2) override;
    void scale(double) override;
    [[nodiscard]] bool in(vec2) const override;
};

#endif //BOREL_EQUIDECOMPOSITION_SHAPE_H
