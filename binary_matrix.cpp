//
// Created by Nicholas Patrick on 8/8/23.
//

#include "binary_matrix.h"

binary_matrix::binary_matrix() = default;

binary_matrix::binary_matrix(size_t m, size_t n, bool b) : m(m), n(n) {
    resize(m, n, b);
}

bool binary_matrix::at(size_t i, size_t j) const {
    return v[i][j];
}

void binary_matrix::set() {
    for (auto &i : v)
        i.assign(n, true);
}

void binary_matrix::set(size_t i, size_t j, bool b) {
    v[i][j] = b;
}

void binary_matrix::reset() {
    for (auto &i : v)
        i.assign(n, false);
}

void binary_matrix::reset(size_t i, size_t j) {
    v[i][j] = false;
}

void binary_matrix::resize(size_t new_m, size_t new_n, bool b = false) {
    m = new_m; n = new_n;
    for (size_t i = std::min(m, v.size()); i--;)
        v[i].resize(n, b);
    v.resize(m, std::vector<bool>(n, b));
}

binary_matrix binary_matrix::sub(size_t x, size_t y, size_t h, size_t w) const {
    binary_matrix ret(h, w, false);
    for (size_t i = std::max(size_t(0), -x); i < std::min(h, m - x); ++i) {
        for (size_t j = std::max(size_t(0), -y); i < std::min(w, n - y); ++i)
            ret.set(i, j, at(i + x, j + y));
    }
    return ret;
}

size_t binary_matrix::count() const {
    size_t ret = 0;
    for (const auto &row : v) for (auto i : row) ret += i;
    return ret;
}

size_t binary_matrix::height() const {
    return m;
}

size_t binary_matrix::width() const {
    return n;
}
