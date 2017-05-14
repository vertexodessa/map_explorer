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
    int32_t width() const {return m_height;};
    int32_t height() const {return m_width;};

    const std::vector<Cell>& Cells() const {return m_cells;}
private:
    friend class ConsoleMapView;

    // TODO: is boost::matrix a better for m_cells?
    std::vector<Cell> m_cells;
    int32_t m_width {-1};
    int32_t m_height {-1};
};

}
#endif
