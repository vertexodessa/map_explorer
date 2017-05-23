#ifndef PATHVIEWFACTORY_H
#define PATHVIEWFACTORY_H

#include "ConsolePathView.h"

namespace map_solver {

class PathViewFactory {
public:
    static std::unique_ptr<IPathView> create(std::shared_ptr<Path> path) {
        // TODO: add possibility to create a different kind of PathView
        return std::unique_ptr<IPathView>(new ConsolePathView(path));
    };
};

}
#endif
