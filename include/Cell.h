#ifndef CELL_H
#define CELL_H

#include "ConsoleCellView.h"

namespace map_solver {

class Cell {
public:
    Cell() : m_type(-1) {};
    Cell(char type);
private:
    char m_type;
    friend class ConsoleCellView;
};

}

#endif
