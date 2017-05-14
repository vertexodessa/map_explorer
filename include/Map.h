#ifndef MAP_H
#define MAP_H

#include "Cell.h"

#include <string>
#include <vector>

namespace map_solver {

class Map {
public:
    Map();
    ~Map(){}
    int ReadFromFile(std::string filename);
private:
    std::vector<Cell> m_cells;
};

}
#endif
