#include "Path.h"
#include "Logging.h"
#include "utils/Constants.h"

using namespace std;

namespace map_solver {

index_t Path::cartesianToIndex(index_t x, index_t y) const throw(OutOfBoundsException) {
    // TODO: test
    if (m_w == kNonexistentIndex)
        throw OutOfBoundsException("m_w is incorrect");
    return x + y * m_w;
}
CartesianPoint Path::indexToCartesian(index_t i) const throw(OutOfBoundsException) {
    index_t x = i%m_w;
    index_t y = i/m_w;

    if ( y > m_h )
        throw OutOfBoundsException("y > m_h");

    return CartesianPoint{ x, y };

}

void Path::calculateFromDistances(std::vector<index_t> dist, index_t start_idx, index_t end_idx) {

    m_cells[end_idx] = 1;
    const auto minimum = [](const index_t a, const index_t b, const index_t c, const index_t d) {
        return min(min(min(a, b), c), d);
    };

    CartesianPoint current = indexToCartesian(end_idx);
    CartesianPoint start = indexToCartesian(start_idx);
    index_t x, y;

    // TODO: corner case: unreachable end point

    while (true) {
        if (current == start)
            break;

        x = current.first;
        y = current.second;

        index_t width = m_w;
        index_t height = m_h;

        index_t top = numeric_limits<index_t>::max();
        index_t bottom = numeric_limits<index_t>::max();
        index_t left = numeric_limits<index_t>::max();
        index_t right = numeric_limits<index_t>::max();
        if (y != 0)
            top = dist[x + (y-1) * m_w];
        if (x != 0)
            left = dist[x-1 +  y * m_w];
        if (y != height - 1)
            bottom = dist[x + (y+1)*m_w];
        if (x != width - 1)
            right = dist[x+1 + y*m_w];

        index_t min_int = minimum(top, bottom, left, right);

        index_t idx = 0;
        if (min_int == top)
            idx = cartesianToIndex(current.first, --current.second);
        else if (min_int == bottom)
            idx = cartesianToIndex(current.first, ++current.second);
        else if (min_int == left)
            idx = cartesianToIndex(--current.first, current.second);
        else if (min_int == right)
            idx = cartesianToIndex(++current.first, current.second);
        m_cells[idx] = 1;
    }

    for (index_t i = 0; i < m_w; ++ i)
        for (index_t j = 0; j < m_h; ++ j) {
            LOG_TRACE << "Element " << i << ", " << j <<": " << m_cells[cartesianToIndex(i, j)];
        }

}

}
