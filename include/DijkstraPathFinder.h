#ifndef DIJKSTRA_PATH_FINDER_H
#define DIJKSTRA_PATH_FINDER_H

#include "IPathFinder.h"

#include <memory>


namespace map_solver {

class Path;
class Map;

class DijkstraPathFinder : public IPathFinder {
public:

    // IPathFinder
    virtual ~DijkstraPathFinder() final {};
    virtual std::unique_ptr<Path> Solve() final;
protected:
    explicit DijkstraPathFinder(std::shared_ptr<Map> map);
    friend class DijkstraPathFinderFactory;
private:
};

class DijkstraPathFinderFactory {
public:
    static std::unique_ptr<IPathFinder> Create(std::shared_ptr<Map> map) {
        return std::unique_ptr<IPathFinder>(new DijkstraPathFinder(map));
    };
};

} //namespace map_solver

#endif
