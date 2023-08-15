#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <random>
#include "canvas.h"
#include "shape.h"
#include "binary_matrix.h"
#include "matcher.h"
#include "solve_borel.h"
#include "lerp.h"

int main(int argc, char *argv[]) {
    // parse args
    if (argc != 5) {
        std::cout << "\narguments must be width, height, transition duration, transition delta\n";
        return 1;
    }
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    int transition_duration = std::stoi(argv[3]);
    int transition_delta = std::stoi(argv[4]);
    // determine shapes
    polygon polygon1 = polygon(std::vector<vec2>{
            vec2(0, 0),
            vec2(1, 0),
            vec2(1, 1),
            vec2(0, 1)});
    shape *shape1 = &polygon1;
    circle circle2;
    shape *shape2 = &circle2;
    // first reposition
    shape1->translate(-vec2(shape1->top(), shape1->left()));
    shape2->translate(-vec2(shape2->top(), shape2->left()));
    // resize
    double scale1 = std::min(double(height) / shape1->bottom(), double(width) / shape1->right());
    double scale2 = std::min(double(height) / shape2->bottom(), double(width) / shape2->right());
    double area1 = shape1->area(), area2 = shape2->area();
    if (scale1 * scale1 * area1 > scale2 * scale2 * area2) {
        scale1 = sqrt(area2 / area1) * scale2;
    } else {
        scale2 = sqrt(area1 / area2) * scale1;
    }
    shape1->scale(scale1);
    shape2->scale(scale2);
    // second reposition
    shape1->translate(vec2((double(height) - shape1->bottom()) / 2, (double(width) - shape1->right()) / 2));
    shape2->translate(vec2((double(height) - shape2->bottom()) / 2, (double(width) - shape2->right()) / 2));
    // get bit matrices
    binary_matrix bm1(height, width), bm2(height, width);
    for (int i = 0; i < height; ++i) for (int j = 0; j < width; ++j) {
        bm1.set(i, j, shape1->in(vec2(i, j)));
        bm2.set(i, j, shape2->in(vec2(i, j)));
    }
    int bc1 = int(bm1.count());
    int bc2 = int(bm2.count());
    int expected_flow = std::min(bc1, bc2);
    assert(expected_flow > 0);
    // random direction helpers
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::normal_distribution vertical_distrib{0., height * 0.2};
    std::normal_distribution horizontal_distrib{0., width * 0.2};
    auto random_vertical = [&] {return int(round(vertical_distrib(rng)));};
    auto random_horizontal = [&] {return int(round(horizontal_distrib(rng)));};
    auto get_direction = [&] {
        std::pair<int, int> ret;
        do ret = std::pair(random_vertical(), random_horizontal());
        while (abs(ret.first) >= height || abs(ret.second) >= width);
        return ret;
    };
    std::vector<std::pair<int, int>> directions, best_directions;
    std::vector<std::vector<int>> solution, best_solution;
    // get a complete flow
    int flow;
    romanian romanian(bc1, bc2);
    do {
        directions.push_back(get_direction());
        printf("trying %lu directions\n", directions.size());
        solution = solve_borel(bm1, bm2, directions);
        flow = 0;
        for (const auto & i : solution) for (const auto & j : i) if (j != -1) ++flow;
        printf("flow: %d/%d\n", flow, expected_flow);
    } while (flow < expected_flow);
    int piece_count = int(directions.size());
    printf("INITIAL SOLUTION SIZE: %d\n", piece_count);
    // optimise piece count
    best_directions = directions;
    best_solution = solution;
    do {
        for (int tries = 0; tries < 20; ++tries) {
            printf("try # %d of using %d directions\n", tries, piece_count - 1);
            directions.clear();
            for (int i = 1; i < piece_count; ++i) directions.push_back(get_direction());
            solution = solve_borel(bm1, bm2, directions);
            flow = 0;
            for (const auto &i: solution) for (const auto &j: i) if (j != -1) ++flow;
            if (flow == expected_flow) {
                --piece_count;
                printf("FOUND A SOLUTION IN %d DIRECTIONS\n", piece_count);
                best_directions = directions;
                best_solution = solution;
                break;
            }
        }
    } while (flow == expected_flow);
    directions = best_directions;
    printf("directions:");
    for (auto i : directions) printf(" (%d, %d)", i.first, i.second);
    printf("\n");
    solution = best_solution;
    // determine colors
    std::vector<uint32_t> colors{0xff6666, 0x66ff66, 0x6666ff, 0xffffff, 0x666666, 0xff0000};
    // draw
    int frame_count = transition_delta * (piece_count - 1) + transition_duration + 1;
    for (int frame_number = 0; frame_number < frame_count; ++frame_number) {
        std::string padded = std::to_string(frame_number);
        padded.insert(padded.begin(), 5 - padded.size(), '0');
        std::string filename = "frames/frame" + padded + ".ppm";
        canvas cv(filename.c_str(), width * 2, height);
        for (int piece_number = 0; piece_number < directions.size(); ++piece_number) {
            auto direction = directions[piece_number];
            double transition_progress = set_within(0.0, 1.0, double(frame_number - piece_number * transition_delta) / transition_duration);
            int translation_x = int(round(cubic_lerp(0, direction.first, transition_progress)));
            int translation_y = int(round(cubic_lerp(0, width + direction.second, transition_progress)));
            cv.color_val = colors[piece_number] & 16777215;
            for (int x = 0; x < height; ++x) for (int y = 0; y < width; ++y) {
                if (solution[x][y] == piece_number) {
                    cv.point(x + translation_x, y + translation_y);
                }
            }
        }
        cv.save();
    }
    return 0;
}
