#ifndef IVIEWBACKEND_H
#define IVIEWBACKEND_H

namespace map_solver {

class IViewBackend {
public:
    virtual void initialize() = 0;
    virtual void deInitialize() = 0;
    virtual ~IViewBackend() = default;
};

}

#endif
