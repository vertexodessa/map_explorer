#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <utility>
#include <stdexcept>

namespace map_solver {
using index_t  = uint32_t;
using weight_t =  uint32_t;
using Rect = std::pair<index_t, index_t>;
using CartesianPoint = std::pair<index_t, index_t>;

struct OutOfBoundsException : public std::runtime_error {
    OutOfBoundsException(const std::string& s) : std::runtime_error(s) {};
    virtual ~OutOfBoundsException() {}
};

}

#endif
