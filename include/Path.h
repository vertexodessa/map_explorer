#ifndef PATH_H
#define PATH_H

#include <vector>

namespace map_solver {

class Cell;

class Path {
public:
    Path();
private:
    std::vector<Cell> m_cells;
    
};

}

#endif
