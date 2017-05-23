
#include "Cell.h"
#include "Logging.h"

#include <map>

using namespace std;

namespace map_solver {

Cell::Cell(char type, int32_t x, int32_t y) :
    m_type(type),
    m_x(x),
    m_y(y) {
    LOG_TRACE << "Creating cell of type " << (int) type;
}

}
