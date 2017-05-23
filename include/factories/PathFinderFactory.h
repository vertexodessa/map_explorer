#ifndef PATHFINDERFACTORY_H
#define PATHFINDERFACTORY_H

#include "AStarPathFinder.h"
#include "DijkstraPathFinder.h"

namespace map_solver {

class PathFinderFactory {
public:
    static std::unique_ptr<IPathFinder> create(std::shared_ptr<Map> map) {
        return std::unique_ptr<IPathFinder>(new AStarPathFinder(map));
    };
};

}
#endif
