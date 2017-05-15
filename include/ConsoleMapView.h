#ifndef CONSOLEMAPVIEW_H
#define CONSOLEMAPVIEW_H

#include "IMapView.h"


namespace map_solver {

class ConsoleMapView : public IMapView {
public:
    virtual ~ConsoleMapView() final {};
    //IMapView
    virtual void Draw() const final;

protected:
    explicit ConsoleMapView(std::shared_ptr<Map> map) : IMapView(map) { };
private:
    friend class MapViewFactory;
};


}

#endif
