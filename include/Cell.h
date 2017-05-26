#ifndef CELL_H
#define CELL_H

#include "utils/Types.h"
#include "Logging.h"

#include <cstdint>

namespace map_solver {

class Cell {
public:
    Cell() : m_type(-1), m_idx(-1) {};
    Cell(char type, index_t idx) : m_type(type), m_idx(idx) {
        LOG_TRACE << "Creating cell of type " << m_type << " at index " << idx;
    }

    char getType() const {return m_type;};
    index_t index() const {return m_idx;}
private:
    friend class ConsoleCellView;
    char m_type;
    index_t m_idx;
};

}

#endif
