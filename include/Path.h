#ifndef PATH_H
#define PATH_H

#include "Cell.h"
#include "Utils.h"

#include <boost/numeric/ublas/matrix.hpp>

#include <vector>


namespace map_solver {

class Cell;

class Path {
public:
    Path(int32_t w, int32_t h) : m_cells(boost::numeric::ublas::zero_matrix<int>(w, h)) {};
    void CalculateFromDistances(std::vector<int32_t> dist, const Point& start, const Point& end);
    const int32_t Cell(int32_t x, int32_t y) const {return m_cells(x, y);}
    const int32_t FieldWidth() const {return m_cells.size1();}
    const int32_t FieldHeight() const {return m_cells.size2();}
private:
    // friend class ConsolePathView;
    boost::numeric::ublas::matrix<int32_t> m_cells;
};

}

#endif
