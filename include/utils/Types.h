#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <utility>
#include <stdexcept>

namespace map_solver {
using index_t  = uint32_t;
using weight_t = uint32_t;
using Rect = std::pair<index_t, index_t>;
using CartesianPoint = std::pair<index_t, index_t>;

class OutOfBoundsException : public std::runtime_error {
public:
    OutOfBoundsException(const std::string& s) : std::runtime_error(s) {};
};

class DestinationUnreachableException : public std::runtime_error {
public:
    DestinationUnreachableException(const std::string& s) : std::runtime_error(s) {};
};

}

#endif
