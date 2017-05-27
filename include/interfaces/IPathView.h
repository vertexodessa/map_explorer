#ifndef IPATHVIEW_H
#define IPATHVIEW_H

#include <memory>

namespace map_solver {

class Path;

class IPathView {
public:
    virtual ~IPathView() {}
    virtual void draw() const =0;
protected:
    friend class ConsolePathViewFactory;
    explicit IPathView(std::shared_ptr<Path> path): m_path (path) {};
    std::shared_ptr<const Path> path() const {return m_path;};
private:
    std::shared_ptr<Path> m_path;
};

}

#endif
