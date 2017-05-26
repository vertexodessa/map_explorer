#ifndef PATH_H
#define PATH_H

#include "Cell.h"
#include "utils/Types.h"

#include <boost/numeric/ublas/matrix.hpp>

#include <vector>


namespace map_solver {
class Cell;

class Path {
public:
    Path(index_t w, index_t h) : m_cells(w*h), m_width(w), m_height(h) {};

    index_t fieldWidth() const {return m_width;}
    index_t fieldHeight() const {return m_height;}

    weight_t calculateFromDistances(std::vector<index_t> dist, index_t start, index_t end);
    index_t cell(index_t idx) const;
    index_t cell(index_t x, index_t y) const;

    void markCell(index_t idx);

    index_t cartesianToIndex(index_t x, index_t y) const;
    CartesianPoint indexToCartesian(index_t i) const;
private:
    void checkInBounds(index_t idx) const;

    std::vector<index_t> m_cells;
    index_t m_width, m_height;
};

}

#endif
