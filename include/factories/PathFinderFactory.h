#ifndef PATHFINDERFACTORY_H
#define PATHFINDERFACTORY_H

#include "AStarPathFinder.h"
#include "DijkstraPathFinder.h"

namespace map_solver {

class PathFinderFactory {
public:
    enum PathFinderType {
        AStar,
        Dijkstra
    };
    void setType(PathFinderType t) {m_type = t;};
    std::unique_ptr<IPathFinder> create(std::shared_ptr<Map> map) {
        if (m_type == Dijkstra)
            return std::unique_ptr<IPathFinder>(new DijkstraPathFinder(map));
        else if (m_type == AStar)
            return std::unique_ptr<IPathFinder>(new AStarPathFinder(map));
        else {
            LOG_FATAL << "Factory cannot produce the item of this type";
            return nullptr;
        }
    };
private:
    PathFinderType m_type {AStar};
};

}
#endif
