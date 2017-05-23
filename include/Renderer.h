#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include "Map.h"

#include <memory>

namespace map_solver {

class IMapView;
class IPathView;

class Renderer {
public:
    void setMapView(std::shared_ptr<IMapView> mapView);
    void setPathView(std::shared_ptr<IPathView> pathView);
    void draw() const;
private:

    std::shared_ptr<IMapView> m_mapView;
    std::shared_ptr<IPathView> m_pathView;
};

}

#endif
