#ifndef IPATHVIEW_H
#define IPATHVIEW_H

#include "Utils.h"

#include <memory>
#include <utility>

namespace map_solver {

class Path;

class IPathView {
public:
    virtual ~IPathView() {}
    virtual void Draw() =0;
protected:
    friend class ConsolePathViewFactory;
    explicit IPathView(std::shared_ptr<Path> path): m_path (path) {};
    std::shared_ptr<Path> m_path;
private:
};

}

#endif
