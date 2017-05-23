#include "Renderer.h"
#include "interfaces/IMapView.h"
#include "interfaces/IPathView.h"

namespace map_solver {

void Renderer::setMapView(std::shared_ptr<IMapView> mapView) {
    m_mapView = mapView;
}

void Renderer::setPathView(std::shared_ptr<IPathView> pathView) {
    m_pathView = pathView;
}

void Renderer::draw() const {
    m_mapView->draw();
    m_pathView->draw();
}

}
