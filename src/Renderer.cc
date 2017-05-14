#include "Renderer.h"
#include "IMapView.h"
#include "IPathView.h"

namespace map_solver {

void Renderer::SetMapView(std::shared_ptr<IMapView> mapView) {
    m_mapView = mapView;
}

void Renderer::SetPathView(std::shared_ptr<IPathView> pathView) {
    m_pathView = pathView;
}

void Renderer::Draw() {
    m_mapView->Draw();
    m_pathView->Draw();
}

}
