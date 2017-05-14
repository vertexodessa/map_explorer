
#include "Renderer.h"
#include "ConsoleMapView.h"
#include "Logging.h"
#include "Map.h"

#include <memory>
#include <utility>

using namespace map_solver;
using namespace std;

int main(int, char*[])
{
    LOG_TRACE << "Starting";

    LOG_TRACE << "Reading the map";

    shared_ptr<Map> map = make_shared<Map>();
    if (-1 == map->ReadFromFile("crafted_map.map")) {
        LOG_ERROR << "Can't read map; exiting";
        // exit(1);
    };

    LOG_TRACE << "Read the map. Creating map view.";

    unique_ptr<IMapView> view = ConsoleMapViewFactory::Create(map);

    shared_ptr<IMapView> viewPtr = move(view);
    Renderer p;
    p.SetMapView(viewPtr);
    p.Draw();

    return 0;
}
