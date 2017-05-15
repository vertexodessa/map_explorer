#ifndef IPATHFINDER_H
#define IPATHFINDER_H

#include <memory>

namespace map_solver {

class Path;
class Map;

class IPathFinder {
public:
    virtual ~IPathFinder(){};
    virtual std::unique_ptr<Path> Solve() =0;
protected:
    explicit IPathFinder(std::shared_ptr<Map> map) : m_map(map) {};
    std::shared_ptr<Map> m_map;
};

}

#endif
