#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include "Constants.h"
#include "Utils.h"
#include "interfaces/IMapView.h"

#include <algorithm>
#include <string>
#include <vector>
#include <utility>

namespace map_solver {

typedef uint32_t index;

class Map {
public:
    Map();
    ~Map(){}
    int readFromFile(std::string filename);

    int32_t width() const {return m_width;};
    int32_t height() const {return m_height;};

    Cell& operator[](size_t idx) { return m_cells[idx]; };

    const index start() const;
    const index finish() const;

    uint32_t weight(index idx) const;

private:
    friend class ConsoleMapView;

    std::vector<Cell> m_cells;
    int32_t m_width {-1};
    int32_t m_height {-1};
};

}
#endif
