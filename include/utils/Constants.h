#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "utils/Types.h"

namespace map_solver {
constexpr int kStartCellType = 's';
constexpr int kFinishCellType = 'e';

constexpr index_t  kInvalidIndex  = (index_t) -1;
constexpr weight_t kInvalidWeight = (weight_t) -1;
constexpr weight_t kWallWeight = (weight_t) 65000;

}

#endif
