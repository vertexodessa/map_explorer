#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include "interfaces/IMapView.h"
#include "utils/Constants.h"
#include "utils/Types.h"

#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <istream>

namespace map_solver {

class Map {
public:
    Map();
    ~Map(){}
    index_t readFromFile(std::string filename);
    index_t readFromStream(std::istream& s);

    Cell& operator[](index_t idx) { return m_cells[idx]; };

    index_t start() const;
    index_t finish() const;

    index_t width() const {return m_width;};
    index_t height() const {return m_height;};

    weight_t weight(index_t idx) const;

    index_t cartesianToIndex(index_t x, index_t y) const throw(OutOfBoundsException);
    CartesianPoint indexToCartesian(index_t i) const throw(OutOfBoundsException);
private:
    friend class ConsoleMapView;

    std::vector<Cell> m_cells;
    index_t m_width {kNonexistentIndex};
    index_t m_height {kNonexistentIndex};
};

}
#endif
