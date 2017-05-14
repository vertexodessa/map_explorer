#ifndef CELL_H
#define CELL_H

namespace map_solver {

class Cell {
public:
    Cell() : m_type(-1) {};
    Cell(char type);
    char getType() {return m_type;};
private:
    char m_type;
    friend class ConsoleCellView;
};

}

#endif
