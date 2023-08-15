//
// Created by Nicholas Patrick on 8/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_BINARY_MATRIX_H
#define BOREL_EQUIDECOMPOSITION_BINARY_MATRIX_H
#include <vector>

class binary_matrix {
    size_t m, n;
    std::vector<std::vector<bool>> v;
public:
    binary_matrix();
    binary_matrix(size_t m, size_t n, bool = false);
    [[nodiscard]] bool at(size_t, size_t) const;
    void set();
    void set(size_t, size_t, bool = true);
    void reset();
    void reset(size_t, size_t);
    void resize(size_t, size_t, bool);
    [[nodiscard]] binary_matrix sub(size_t, size_t, size_t, size_t) const;
    [[nodiscard]] size_t count() const;
    [[nodiscard]] size_t height() const;
    [[nodiscard]] size_t width() const;
};


#endif //BOREL_EQUIDECOMPOSITION_BINARY_MATRIX_H
