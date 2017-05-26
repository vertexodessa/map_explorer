#ifndef IPATHFINDER_H
#define IPATHFINDER_H

#include "utils/Constants.h"

#include <memory>

namespace map_solver {

class Path;
class Map;

class IPathFinder {
public:
    virtual ~IPathFinder(){};
    virtual std::unique_ptr<Path> solve() =0;
    virtual weight_t weight() {return m_weight;};
protected:
    explicit IPathFinder(std::shared_ptr<Map> map) : m_map(map) {};
    std::shared_ptr<Map> m_map;
    weight_t m_weight {kNonExistentWeight};
};

}

#endif
