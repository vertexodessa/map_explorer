// ConsoleCellView
// ConsoleMapVieConfiguration


#include "ConsoleMapView.h"
#include "Map.h"

#include <iostream>

using namespace std;

namespace map_solver {

namespace {

wchar_t CellRepresentation(char cellType) {
    // currently just a cell type is returned.
    return cellType;
};

}

void ConsoleMapView::Draw() {
    for (int y=0; y < m_map->height(); ++y) {
        for (int x=0; x < m_map->width(); ++x) {
            int32_t cellPos = x + (y * m_map->width());
            char cellType = m_map->m_cells[cellPos].getType();
            wchar_t cell_representation = CellRepresentation(cellType);
            wcout << cell_representation;
        }
        cout << '\n';
    }
    cout << flush;
}

}
