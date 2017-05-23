#ifndef CELL_H
#define CELL_H

#include <cstdint>

namespace map_solver {

class Cell {
public:
    Cell() : m_type(-1), m_x(-1), m_y(-1) {};
    Cell(char type, int32_t x, int32_t y);

    char getType() const {return m_type;};
    int32_t x() const {return m_x;}
    int32_t y() const {return m_y;}
private:
    char m_type;
    int32_t m_x;
    int32_t m_y;
    friend class ConsoleCellView;
};

}

#endif
