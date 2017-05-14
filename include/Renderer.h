#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include "Map.h"

#include <memory>

namespace map_solver {

class IMapView;
class IPathView;

class Renderer {
public:
    void SetMapView(std::shared_ptr<IMapView> mapView);
    void SetPathView(std::shared_ptr<IPathView> pathView);
    void Draw() const;
private:

    std::shared_ptr<IMapView> m_mapView;
    std::shared_ptr<IPathView> m_pathView;
};

}

#endif
