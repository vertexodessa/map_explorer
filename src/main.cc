#include "ConsoleMapView.h"
#include "ConsolePathView.h"
#include "DijkstraPathFinder.h"
#include "Logging.h"
#include "Map.h"
#include "Path.h"
#include "Renderer.h"

#include <memory>
#include <utility>

#include <cursesw.h>

using namespace map_solver;
using namespace std;

int main(int, char*[])
{
    InitLogging();
    LOG_TRACE << "Starting";

    ConsoleMapView::Initialize();

    LOG_TRACE << "Reading the map";

    shared_ptr<Map> map = make_shared<Map>();
    if (-1 == map->ReadFromFile("crafted_map.map")) {
        LOG_ERROR << "Can't read map; exiting";
        ConsoleMapView::DeInitialize();
        exit(1);
    };

    LOG_TRACE << "Read the map. Creating map view.";

    unique_ptr<IMapView> view = ConsoleMapViewFactory::Create(map);

    shared_ptr<IMapView> viewPtr { move(view) };
    Renderer p;
    p.SetMapView(viewPtr);

    unique_ptr<IPathFinder> pf = DijkstraPathFinderFactory::Create(map);
    shared_ptr<Path> path { pf->Solve() };
    shared_ptr<IPathView> pathView = ConsolePathViewFactory::Create(path);

    p.SetPathView(pathView);
    p.Draw();

    getch();

    ConsoleMapView::DeInitialize();

    return 0;
}
