#ifndef DIJKSTRA_PATH_FINDER_H
#define DIJKSTRA_PATH_FINDER_H

#include "interfaces/IPathFinder.h"

#include <memory>


namespace map_solver {

class Path;
class Map;

class DijkstraPathFinder : public IPathFinder {
public:
    // IPathFinder
    ~DijkstraPathFinder() final = default;
    std::unique_ptr<Path> solve() final;
protected:
    explicit DijkstraPathFinder(std::shared_ptr<Map> map);
    friend class PathFinderFactory;
private:
};


} //namespace map_solver

#endif
