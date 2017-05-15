#ifndef MAPVIEWFACTORY_H
#define MAPVIEWFACTORY_H

#include "ConsoleMapView.h"

namespace map_solver {

class MapViewFactory {
public:
    static std::unique_ptr<IMapView> Create(std::shared_ptr<Map> map) {
        // TODO: add possibility to create a different kind of MapView
        return std::unique_ptr<IMapView>(new ConsoleMapView(map));
    };

};

}
#endif
