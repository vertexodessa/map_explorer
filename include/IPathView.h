#ifndef IPATHVIEW_H
#define IPATHVIEW_H

#include <utility>

namespace map_solver {
class IPathView {
public:
    virtual ~IPathView() {}
    virtual void Draw() =0;
protected:
    explicit IPathView(std::shared_ptr<Path> path): m_path (path);
    std::shared_ptr<Path> m_path;
private:
};
}

#endif
