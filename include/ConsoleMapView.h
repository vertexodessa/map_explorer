#ifndef CONSOLEMAPVIEW_H
#define CONSOLEMAPVIEW_H

#include "IMapView.h"

#include <utility>

namespace map_solver {

class ConsoleMapView : public IMapView {
public:
    virtual ~ConsoleMapView() final {};
    //IMapView
    virtual void Draw() final {};

protected:
    explicit ConsoleMapView(std::shared_ptr<Map> map) : IMapView(map) {};
private:
    friend class ConsoleMapViewFactory;
};


class ConsoleMapViewFactory {
public:
    static std::unique_ptr<IMapView> Create(std::shared_ptr<Map> map) {
        return std::unique_ptr<IMapView>(new ConsoleMapView(map));
    };
};


}

#endif
