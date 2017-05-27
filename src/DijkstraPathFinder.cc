#include "DijkstraPathFinder.h"
#include "Logging.h"
#include "Map.h"
#include "Path.h"
#include "utils/AdjacentCellIterator.h"
#include "utils/Constants.h"
#include "utils/Types.h"

#include <list>
#include <map>
#include <set>

using namespace std;

namespace map_solver {

DijkstraPathFinder::DijkstraPathFinder(shared_ptr<Map> map)
    : IPathFinder(map) {

}

unique_ptr<Path> DijkstraPathFinder::solve() {

    index_t start_idx = map()->start();
    index_t finish_idx = map()->finish();

    if (kInvalidWeight == start_idx || kInvalidWeight == finish_idx) {
        LOG_FATAL << "The map is not correct. Cannot find a start or finish cell.";
        return nullptr;
    }

    // In the set, the first of the pair is the distance; the second is the position on the map.
    set< pair<weight_t, index_t> > setds;
    index_t cell_count = map()->width() * map()->height();

    const weight_t kINF = kWallWeight;
    vector<index_t> dist(cell_count, kINF);

    setds.insert(make_pair(0, start_idx));
    dist[start_idx] = 0;

    while (!setds.empty())
    {
        pair<index_t, index_t> tmp = *(setds.begin());
        setds.erase(setds.begin());

        int currentCell = tmp.second;

        AdjacentCells<index_t> adj(map()->width(), map()->height(), currentCell);

        AdjacentCells<index_t>::iterator currentAdjacent;
        for (currentAdjacent = adj.begin(); currentAdjacent != adj.end(); ++currentAdjacent)
        {
            LOG_TRACE << "Got adjacent cell: " << *currentAdjacent;
            index_t weight = map()->weight(*currentAdjacent);

            LOG_TRACE << "Distance of current adjacent cell to the start: " << dist[*currentAdjacent];
            LOG_TRACE << "Weight of current adjacent cell: " << weight;
            LOG_TRACE << "Distance of current cell to the start: " << dist[currentCell];

            if (dist[*currentAdjacent] > dist[currentCell] + weight)
            {
                if (dist[*currentAdjacent] != kINF) {
                    // we only get here if there is another way to get to this cell.
                    if (setds.find(make_pair(dist[*currentAdjacent], *currentAdjacent)) == setds.end()) {
                        LOG_FATAL << "Can't find cell #" << *currentAdjacent << " with dist to start " << dist[*currentAdjacent];
                        throw(OutOfBoundsException("Can't find a pair that represents the currently calculated distance to a current cell."
                                                   " That looks like an algorithm error."));
                    }

                    setds.erase(setds.find(make_pair(dist[*currentAdjacent], *currentAdjacent)));
                }

                // Updating distance of currentAdjacent
                dist[*currentAdjacent] = dist[currentCell] + weight;
                setds.insert(make_pair(dist[*currentAdjacent], *currentAdjacent));
            }
        }
    }

    unique_ptr<Path> ret {new Path(map()->width(), map()->height())};

    for (index_t i=0; i < dist.size(); ++i) {
        LOG_TRACE << "element #" << i <<": " << dist[i];
    }

    weight_t weight = ret->calculateFromDistances(dist, start_idx, finish_idx);
    ret->setWeight(weight);

    return ret;
}

} //namespace map_solver
