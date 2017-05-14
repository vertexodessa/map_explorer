#include "DijkstraPathFinder.h"
#include "Map.h"
#include "Utils.h"
#include "Path.h"


using namespace std;

namespace map_solver {

DijkstraPathFinder::DijkstraPathFinder(shared_ptr<Map> map)
    : IPathFinder(map) {
    
}

/*virtual*/ unique_ptr<Path> DijkstraPathFinder::Solve() {
    unique_ptr<Path> ret;
    
    return ret;
}

} //namespace map_solver
