//
// Created by Nicholas Patrick on 10/8/23.
//

#include "solve_borel.h"

std::vector<std::vector<int>> solve_borel(const binary_matrix &left, const binary_matrix &right,
                                          const std::vector<std::pair<int, int>> &directions) {
    int height = int(left.height()), width = int(left.width());
    hop_karp hop_karp(height * width, height * width);
    matcher *matcher = &hop_karp;
    auto xy_to_index = [&](int x, int y) {
        return x * width + y;
    };
    auto index_to_xy = [&](int index) {
        return std::pair(index / width, index % width);
    };
    for (const auto & direction : directions) {
        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                int right_x = x + direction.first, right_y = y + direction.second;
                if (0 > right_x || right_x >= height || 0 > right_y || right_y >= width) continue;
                if (left.at(x, y) && right.at(right_x, right_y))
                    matcher->addEdge(xy_to_index(x, y), xy_to_index(right_x, right_y));
            }
        }
    }
    std::vector<int> matches = matcher->findMatch();
    std::vector<std::vector<int>> piece_number(width, std::vector(height, -1));
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            int left_index = xy_to_index(x, y);
            int right_index = int(matches[left_index]);
            if (right_index != -1) {
                auto [right_x, right_y] = index_to_xy(right_index);
                for (int i = 0; i < directions.size(); ++i) {
                    if (directions[i] == std::pair(right_x - x, right_y - y)) {
                        piece_number[x][y] = i;
                        break;
                    }
                }
            }
        }
    }
    return piece_number;
}
