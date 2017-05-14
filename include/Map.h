#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include "IMapView.h"

#include <string>
#include <vector>

namespace map_solver {

class Map {
public:
    Map();
    ~Map(){}
    int ReadFromFile(std::string filename);
    int32_t width() {return m_height;};
    int32_t height() {return m_width;};

private:
    friend class ConsoleMapView;
    std::vector<Cell> m_cells;
    int32_t m_width {-1};
    int32_t m_height {-1};
};

}
#endif
