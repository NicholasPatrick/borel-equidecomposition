//
// Created by Nicholas Patrick on 10/8/23.
//

#include <algorithm>
#include "lerp.h"

double lerp(double a, double b, double t) {
    return a * (1 - t) + b * t;
}

double cubic_lerp(double a, double b, double t) {
    return lerp(a, b, t * t * (3 - 2 * t));
}

double set_within(double low, double high, double val) {
    return std::max(low, std::min(high, val));
}
