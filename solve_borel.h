//
// Created by Nicholas Patrick on 10/8/23.
//

#ifndef BOREL_EQUIDECOMPOSITION_SOLVE_BOREL_H
#define BOREL_EQUIDECOMPOSITION_SOLVE_BOREL_H

#include <vector>
#include "matcher.h"
#include "binary_matrix.h"

std::vector<std::vector<int>> solve_borel(const binary_matrix &, const binary_matrix &,
                                          const std::vector<std::pair<int, int>> &);


#endif //BOREL_EQUIDECOMPOSITION_SOLVE_BOREL_H
