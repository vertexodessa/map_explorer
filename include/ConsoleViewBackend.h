#ifndef CONSOLEVIEWBACKEND_H
#define CONSOLEVIEWBACKEND_H

#include "interfaces/IViewBackend.h"

#include <memory>
#include <utility>

namespace map_solver {

class ConsoleViewBackend : public IViewBackend {
public:
    // IViewBackend
    ~ConsoleViewBackend() final = default;
    void initialize() final;
    void deInitialize() final;
};


}

#endif
