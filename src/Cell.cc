
#include "Cell.h"
#include "Logging.h"

#include <map>

using namespace std;

namespace map_solver {

int GetWeightFor(char type) {
    static map<char, int> s_map = {
        {' ', 1},
        {'*', 65000}
    };
    if (s_map.find(type) == s_map.end()) {
        LOG_ERROR << (int) type << " not found in the weight map!";
        return 1;
    }
    return s_map[type];
}

Cell::Cell(char type, int32_t x, int32_t y) :
    m_type(type),
    m_x(x),
    m_y(y) {
    LOG_TRACE << "Creating cell of type " << (int) type;
}

}
