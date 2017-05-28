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
    ~Map() = default;
    index_t readFromFile(const std::string& filename);
    index_t readFromStream(std::istream& s);

    index_t width() const {return m_width;};
    index_t height() const {return m_height;};

    Cell& operator[](index_t idx);

    index_t start() const;
    index_t finish() const;

    weight_t weight(index_t idx) const;

    index_t cartesianToIndex(index_t x, index_t y) const;
    CartesianPoint indexToCartesian(index_t i) const;
private:
    friend class ConsoleMapView;

    void checkInBounds(index_t idx) const;
    std::vector<Cell> m_cells;
    index_t m_width {kInvalidIndex};
    index_t m_height {kInvalidIndex};
};

}
#endif
