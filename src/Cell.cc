
#include "Cell.h"
#include "Logging.h"

namespace map_solver {

Cell::Cell(char type) : m_type(type) {
    LOG_TRACE << "Creating cell of type " << (int) type;
}

}
