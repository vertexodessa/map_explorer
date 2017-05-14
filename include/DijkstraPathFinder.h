#ifndef DIJKSTRA_PATH_FINDER_H
#define DIJKSTRA_PATH_FINDER_H

#include "IPathFinder.h"

#include <memory>


namespace map_solver {

class Path;
class Map;

class DijkstraPathFinder : public IPathFinder {
public:
    explicit DijkstraPathFinder(std::shared_ptr<Map>);
    virtual ~DijkstraPathFinder(){};

    // IPathFinder
    virtual std::unique_ptr<Path> Solve();
private:
};

} //namespace map_solver

#endif
