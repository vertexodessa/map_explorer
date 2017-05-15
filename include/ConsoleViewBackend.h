#ifndef CONSOLEVIEWBACKEND_H
#define CONSOLEVIEWBACKEND_H

#include "interfaces/IViewBackend.h"

#include <memory>
#include <utility>

namespace map_solver {

class ConsoleViewBackend : public IViewBackend {
public:
    // IViewBackend
    virtual ~ConsoleViewBackend() final {};
    virtual void Initialize() final;
    virtual void DeInitialize() final;
};


}

#endif
