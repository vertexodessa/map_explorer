#ifndef VIEWBACKENDFACTORY_H
#define VIEWBACKENDFACTORY_H

#include "ConsoleViewBackend.h"
#include "interfaces/IViewBackend.h"

namespace map_solver {

class ViewBackendFactory {
public:
    static std::unique_ptr<IViewBackend> Create() {
        // TODO: add possibility to create a different kind of ViewBackend
        return std::unique_ptr<IViewBackend>(new ConsoleViewBackend());
    };

};

}
#endif
