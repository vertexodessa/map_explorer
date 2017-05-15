#ifndef PATHFINDERFACTORY_H
#define PATHFINDERFACTORY_H

#include "DijkstraPathFinder.h"

namespace map_solver {

class PathFinderFactory {
public:
    static std::unique_ptr<IPathFinder> Create(std::shared_ptr<Map> map) {
        return std::unique_ptr<IPathFinder>(new DijkstraPathFinder(map));
    };
};

}
#endif
