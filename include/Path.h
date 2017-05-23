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
    Path(int32_t w, int32_t h) : m_cells(boost::numeric::ublas::zero_matrix<int>(w, h)) {};
    void calculateFromDistances(std::vector<int32_t> dist, const Point& start, const Point& end);
    const int32_t cell(int32_t x, int32_t y) const {return m_cells(x, y);}
    const int32_t fieldWidth() const {return m_cells.size1();}
    const int32_t fieldHeight() const {return m_cells.size2();}
    void markCell(size_t idx) {
        size_t x = idx % fieldWidth();
        size_t y = idx / fieldWidth();
        m_cells(x, y) = 1;
    };
private:
    // friend class ConsolePathView;
    boost::numeric::ublas::matrix<int32_t> m_cells;
};

}

#endif
