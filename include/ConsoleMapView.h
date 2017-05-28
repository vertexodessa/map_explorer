#ifndef CONSOLEMAPVIEW_H
#define CONSOLEMAPVIEW_H

#include "interfaces/IMapView.h"


namespace map_solver {

class ConsoleMapView : public IMapView {
public:
    ~ConsoleMapView() final = default;
    //IMapView
    void draw() const final;

protected:
    explicit ConsoleMapView(std::shared_ptr<Map> map) : IMapView(map) { };
private:
    friend class MapViewFactory;
};


}

#endif
