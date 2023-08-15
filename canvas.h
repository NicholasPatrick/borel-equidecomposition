//
// Created by Nicholas Patrick on 9/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_CANVAS_H
#define BOREL_EQUIDECOMPOSITION_CANVAS_H
#include <iostream>
#include <vector>

class canvas {
    size_t width, height;
    const char *filename;
    std::vector<std::vector<uint32_t>> board;
public:
    canvas(const char *filename, size_t width, size_t height, uint32_t init_color = 0);
    uint32_t color_val;
    void point(size_t x, size_t y);
    void save() const;
};


#endif //BOREL_EQUIDECOMPOSITION_CANVAS_H
