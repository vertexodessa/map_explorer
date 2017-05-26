#include "Logging.h"
#include "Map.h"
#include "Path.h"
#include "Renderer.h"

#include "factories/MapViewFactory.h"
#include "factories/PathFinderFactory.h"
#include "factories/PathViewFactory.h"
#include "factories/ViewBackendFactory.h"

#include <memory>
#include <utility>

#include <cursesw.h>

using namespace map_solver;
using namespace std;

int main(int, char*[])
{
    Logging::initLogging();
    LOG_TRACE << "Starting";

    unique_ptr<IViewBackend> backend { ViewBackendFactory::create() };
    backend->initialize();

    LOG_TRACE << "Reading the map";

    shared_ptr<Map> map = make_shared<Map>();
    if (kNonexistentIndex == map->readFromFile("crafted_map.map")) {
        LOG_ERROR << "Can't read map; exiting";
        backend->deInitialize();
        exit(1);
    };

    LOG_TRACE << "Read the map. Creating map view.";

    unique_ptr<IMapView> view = MapViewFactory::create(map);
    shared_ptr<IMapView> viewPtr { move(view) };

    Renderer p;
    p.setMapView(viewPtr);

    unique_ptr<IPathFinder> pf = PathFinderFactory::create(map);
    shared_ptr<Path> path { pf->solve() };
    shared_ptr<IPathView> pathView = PathViewFactory::create(path);

    p.setPathView(pathView);
    p.draw();

    getch();

    backend->deInitialize();

    return 0;
}
