#ifndef CONSOLEPATHVIEW_H
#define CONSOLEPATHVIEW_H

#include "interfaces/IPathView.h"

namespace map_solver {

class ConsolePathView : public IPathView {
public:

    //IPathView
    virtual ~ConsolePathView() final {};
    virtual void draw() const final;
protected:
    explicit ConsolePathView(std::shared_ptr<Path> path) : IPathView(path) {};
private:
    friend class PathViewFactory;
};

}

#endif
