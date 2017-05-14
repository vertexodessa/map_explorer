#ifndef CONSOLEPATHVIEW_H
#define CONSOLEPATHVIEW_H

#include "IPathView.h"
#include "Utils.h"

#include <utility>

namespace map_solver {

class ConsolePathView : public IPathView {
public:

    //IPathView
    virtual ~ConsolePathView() final {};
    virtual void Draw() final;
protected:
    explicit ConsolePathView(std::shared_ptr<Path> path) : IPathView(path) {};
private:
    friend class ConsolePathViewFactory;
};


class ConsolePathViewFactory {
public:
    static std::unique_ptr<IPathView> Create(std::shared_ptr<Path> path) {
        return std::unique_ptr<IPathView>(new ConsolePathView(path));
    };
};


}

#endif
