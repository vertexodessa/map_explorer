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
    Path(index_t w, index_t h) : m_cells(w*h), m_w(w), m_h(h) {};
    void calculateFromDistances(std::vector<index_t> dist, index_t start, index_t end);
    index_t cell(index_t idx) const {return m_cells[idx];}
    index_t cell(index_t x, index_t y) const {return m_cells[cartesianToIndex(x, y)];}
    index_t fieldWidth() const {return m_w;}
    index_t fieldHeight() const {return m_h;}
    void markCell(index_t idx) {
        m_cells[idx] = 1;
    };

    index_t cartesianToIndex(index_t x, index_t y) const throw(OutOfBoundsException);
    CartesianPoint indexToCartesian(index_t i) const throw(OutOfBoundsException);
private:
    std::vector<index_t> m_cells;
    index_t m_w, m_h;
};

}

#endif
