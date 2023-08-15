//
// Created by Nicholas Patrick on 8/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_MATCHER_H
#define BOREL_EQUIDECOMPOSITION_MATCHER_H
#include <queue>

class matcher {
protected:
    int l, r;
    std::vector<std::vector<int>> e_r;
public:
    explicit matcher(int, int);
    void addEdge(int, int);

    [[nodiscard]] virtual std::vector<int> findMatch() const = 0;
};

class romanian : public matcher {
public:
    romanian(int, int);
    [[nodiscard]] std::vector<int> findMatch() const override;
};

class hop_karp : public matcher {
public:
    hop_karp(int, int);
    [[nodiscard]] std::vector<int> findMatch() const override;
};

#endif //BOREL_EQUIDECOMPOSITION_MATCHER_H
