#ifndef IPATHVIEW_H
#define IPATHVIEW_H

#include <utility>

namespace map_solver {
class IPathView {
    virtual explicit IPathView(std::shared_ptr<Path>) =0;
    virtual ~IPathView() {}
    virtual void Show() =0;
};
}

#endif
