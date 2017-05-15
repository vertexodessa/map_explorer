#include "Constants.h"
#include "DijkstraPathFinder.h"
#include "Logging.h"
#include "Map.h"
#include "Path.h"
#include "Utils.h"

#include <list>
#include <map>
#include <set>

using namespace std;

namespace map_solver {

DijkstraPathFinder::DijkstraPathFinder(shared_ptr<Map> map)
    : IPathFinder(map) {

}

unique_ptr<Path> DijkstraPathFinder::Solve() {

    auto FindStartCell = [](Map* map) -> Cell const* {
        for(auto& cell : map->Cells()) {
            if (cell.getType() == kStartCellType) {
                return &cell;
            }
        }
        return nullptr;
    };

    auto FindFinishCell = [](Map* map) -> Cell const* {
        for(auto& cell : map->Cells()) {
            if (cell.getType() == kFinishCellType) {
                return &cell;
            }
        }
        return nullptr;
    };


    Cell const *startCell, *finishCell;
    startCell = FindStartCell(m_map.get());
    finishCell = FindFinishCell(m_map.get());

    if (!startCell || !finishCell) {
        LOG_FATAL << "The map is not correct. Cannot find a start or finish cell.";
        return nullptr;
    }

    // In the set, the first of the pair is the distance; the second is the position on the map.
    set< pair<int32_t, int32_t> > setds;
    int32_t cell_count = m_map->width() * m_map->height();

    const int32_t kINF = 100000000;
    vector<int32_t> dist(cell_count, kINF);

    int32_t start_pos = startCell->x() * startCell->y();

    setds.insert(make_pair(0, start_pos));
    dist[start_pos] = 0;

    while (!setds.empty())
    {
        pair<int32_t, int32_t> tmp = *(setds.begin());
        setds.erase(setds.begin());

        int currentCell = tmp.second;

        struct AdjacentCell {
            AdjacentCell(int32_t p, int32_t w) : pos(p), weight(w) {};
            int32_t pos;
            int32_t weight;
        };

        list< AdjacentCell > adj;

        // update adjacent cell vector
        int32_t w = m_map->width();
        int32_t h = m_map->height();
        int32_t x = currentCell%w;
        int32_t y = currentCell/w;

        if (x > 0) {
            int32_t weight = GetWeightFor(m_map->Cells()[currentCell-1].getType());
            adj.emplace_back(currentCell-1, weight);
        }
        if (x < w-1) {
            int32_t weight = GetWeightFor(m_map->Cells()[currentCell+1].getType());
            adj.emplace_back(currentCell+1, weight);
        }
        if (y > 0) {
            int32_t weight = GetWeightFor(m_map->Cells()[currentCell-w].getType());
            adj.emplace_back(currentCell-w, weight);
        }
        if (y < h-1) {
            int32_t weight = GetWeightFor(m_map->Cells()[currentCell+w].getType());
            adj.emplace_back(currentCell+w, weight);
        }

        // 'i' is used to get all adjacent cells of a cell
        list< AdjacentCell >::iterator i;
        for (i = adj.begin(); i != adj.end(); ++i)
        {
            LOG_TRACE << "Got adjacent cell: " << i->pos;
            int32_t currentAdjacent = i->pos;
            int32_t weight = i->weight;

            LOG_TRACE << "Distance of current adjacent cell to the start: " << dist[currentAdjacent];
            LOG_TRACE << "Weight of current adjacent cell: " << weight;
            LOG_TRACE << "Distance of current cell to the start: " << dist[currentCell];

            if (dist[currentAdjacent] > dist[currentCell] + weight)
            {
                if (dist[currentAdjacent] != kINF) {
                    // we only get here if there is another way to get to this cell.
                    if (setds.find(make_pair(dist[currentAdjacent], currentAdjacent)) == setds.end()) {
                        LOG_FATAL << "Can't find cell #" << currentAdjacent << " with dist to start " << dist[currentAdjacent];
                        exit(1);
                    }

                    setds.erase(setds.find(make_pair(dist[currentAdjacent], currentAdjacent)));
                }

                // Updating distance of currentAdjacent
                dist[currentAdjacent] = dist[currentCell] + weight;
                setds.insert(make_pair(dist[currentAdjacent], currentAdjacent));
            }
        }
    }

    unique_ptr<Path> ret {new Path(m_map->width(), m_map->height())};

    Point startPoint{startCell->x(), startCell->y()};
    Point endPoint{finishCell->x(), finishCell->y()};

    for (uint32_t i=0; i < dist.size(); ++i) {
        LOG_TRACE << "element #" << i <<": " << dist[i];
    }

    ret->CalculateFromDistances(dist, startPoint, endPoint);

    return ret;
}

} //namespace map_solver
