#include "Path.h"
#include "Logging.h"
#include "utils/Constants.h"
#include "utils/AdjacentCellIterator.h"

using namespace std;

namespace map_solver {

void Path::checkInBounds(index_t idx) const {
    if (idx > m_cells.size())
        throw OutOfBoundsException("index is larger than the current cell size");
    if (idx/m_width > m_height)
        throw OutOfBoundsException("y is larger than the current height");
    if (m_width == kInvalidWeight || m_height == kInvalidWeight)
        throw OutOfBoundsException("m_width or m_height == -1");
}

index_t Path::cell(index_t idx) const {
    checkInBounds(idx);
    return m_cells[idx];
}

index_t Path::cell(index_t x, index_t y) const {
    index_t idx = cartesianToIndex(x, y);
    checkInBounds(idx);

    return m_cells[idx];
}

void Path::markCell(index_t idx) {
    checkInBounds(idx);
    m_cells[idx] = 1;
};

index_t Path::cartesianToIndex(index_t x, index_t y) const {
    // TODO: make a test
    if (m_width == kInvalidWeight)
        throw OutOfBoundsException("m_w is incorrect");
    return x + y * m_width;
}
CartesianPoint Path::indexToCartesian(index_t i) const {
    index_t x = i%m_width;
    index_t y = i/m_width;

    if ( y > m_height )
        throw OutOfBoundsException("y > m_h");

    return CartesianPoint{ x, y };

}

weight_t Path::calculateFromDistances(const std::vector<index_t> dist,
                                  index_t start_idx,
                                  index_t end_idx) {
    checkInBounds(start_idx);
    checkInBounds(end_idx);

    m_cells[end_idx] = 1;

    index_t current_idx = end_idx;

    weight_t total_weight = 0;

    LOG_TRACE << "Total distance: " << dist[end_idx];

    total_weight = dist[end_idx];
    if (total_weight >= kWallWeight)
        throw DestinationUnreachableException("can't reach from start to end");

    while (true) {
        if (current_idx == start_idx)
            break;

        AdjacentCells<index_t> cells(m_width, m_height, current_idx);
        auto min = min_element(cells.begin(), cells.end(), [&](auto&& lhs, auto&& rhs) {
                return dist[lhs] < dist[rhs];
            });

        index_t min_idx = *min;
        m_cells[min_idx] = 1;
        current_idx = min_idx;
    }

    for (index_t i = 0; i < m_width; ++ i)
        for (index_t j = 0; j < m_height; ++ j) {
            LOG_TRACE << "Element " << i << ", " << j <<": " << m_cells[cartesianToIndex(i, j)];
        }

    return total_weight;
}

}
