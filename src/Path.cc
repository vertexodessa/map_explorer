#include "Path.h"
#include "Logging.h"


using namespace std;

namespace map_solver {

void Path::calculateFromDistances(std::vector<int32_t> dist, const Point& start, const Point& end) {
    m_cells(end.first, end.second) = 1;
    const auto minimum = [](const int32_t a, const int32_t b, const int32_t c, const int32_t d) {
        return min(min(min(a, b), c), d);
    };

    Point current = end;
    int32_t x, y;

    // TODO: corner case: unreachable end point

    while (true) {
        if (current == start)
            break;

        x = current.first;
        y = current.second;

        int32_t top = numeric_limits<int32_t>::max();
        int32_t bottom = numeric_limits<int32_t>::max();
        int32_t left = numeric_limits<int32_t>::max();
        int32_t right = numeric_limits<int32_t>::max();
        if (y != 0)
            top = dist[x + (y-1) * m_cells.size1()];
        if (x != 0)
            left = dist[x-1 +  y * m_cells.size1()];
        if (y != m_cells.size2() -1)
            bottom = dist[x + (y+1)*m_cells.size1()];
        if (x != m_cells.size1() -1)
            bottom = dist[x+1 + y*m_cells.size1()];
        int min_int = minimum(top, bottom, left, right);

        if (min_int == top)
            m_cells(current.first, --current.second) = 1;
        else if (min_int == bottom)
            m_cells(current.first, ++current.second) = 1;
        else if (min_int == left)
            m_cells(--current.first, current.second) = 1;
        else if (min_int == bottom)
            m_cells(current.first, ++current.second) = 1;

    }

    for (unsigned i = 0; i < m_cells.size1 (); ++ i)
        for (unsigned j = 0; j < m_cells.size2 (); ++ j) {
            LOG_TRACE << "Matrix element " << i << ", " << j <<": " << m_cells (i, j);
        }

}

}
