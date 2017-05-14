#ifndef CONSOLECELLVIEW_H
#define CONSOLECELLVIEW_H

#include <memory>

namespace map_solver {

class Cell;

class ConsoleCellView {
public:
    ConsoleCellView(std::shared_ptr<Cell> cell) : m_cell(cell) {}
    void Draw();
private:
    std::shared_ptr<Cell> m_cell;
};

}

#endif
