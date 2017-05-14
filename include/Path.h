#ifndef PATH_H
#define PATH_H

#include <vector>

class Cell;

namespace map_solver {

class Path {
public:
    Path();
private:
    std::vector<Cell> m_cells;
    
};

}

#endif
