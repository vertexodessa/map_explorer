#ifndef IVIEWBACKEND_H
#define IVIEWBACKEND_H

namespace map_solver {

class IViewBackend {
public:
    virtual void Initialize() = 0;
    virtual void DeInitialize() = 0;
    virtual ~IViewBackend() {}
};

}

#endif
