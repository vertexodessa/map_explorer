#ifndef IPATHFINDER_H
#define IPATHFINDER_H

#include <memory>

namespace map_solver {

class Path;

class IPathFinder {
public:
    virtual ~IPathFinder(){};
    virtual std::unique_ptr<Path> Solve() =0;
};

}

#endif
