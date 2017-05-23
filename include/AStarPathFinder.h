#ifndef ASTAR_PATH_FINDER_H
#define ASTAR_PATH_FINDER_H

#include "interfaces/IPathFinder.h"

#include <memory>


namespace map_solver {

class Path;
class Map;

class AStarPathFinder : public IPathFinder {
public:
    // IPathFinder
    virtual ~AStarPathFinder() final {};
    virtual std::unique_ptr<Path> solve() final;
protected:
    explicit AStarPathFinder(std::shared_ptr<Map> map);
    friend class PathFinderFactory;
private:
};


} //namespace map_solver

#endif
