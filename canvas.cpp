//
// Created by Nicholas Patrick on 9/8/23.
//

#include "canvas.h"

canvas::canvas(const char *filename, size_t width, size_t height, uint32_t init_color) : width(width), height(height),
    filename(filename), color_val(init_color), board(height, std::vector<uint32_t>(width, init_color)) {

}

void canvas::point(size_t x, size_t y) {
    board[x][y] = color_val;
}

void canvas::save() const {
    FILE *f = fopen(filename, "w");
    fprintf(f, "P6 %lu %lu 255 ", width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            uint32_t color = board[i][j];
            fprintf(f, "%c%c%c", color & 255, color >> 8 & 255, color >> 16 & 255);
        }
    }
    fclose(f);
}
