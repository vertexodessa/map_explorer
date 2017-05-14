// ConsoleCellView
// ConsoleMapVieConfiguration


#include "ConsoleMapView.h"
#include "Map.h"

#include <iostream>

#include <cursesw.h>

using namespace std;

namespace map_solver {

namespace {

wchar_t CellRepresentation(char cellType) {
    // currently just a cell type is returned.
    return cellType;
};

WINDOW* gWindow;

}

void ConsoleMapView::Initialize(WINDOW* win) {gWindow = win;}
void ConsoleMapView::DeInitialize() {}

void ConsoleMapView::Draw() {
    int initX, initY;
    getyx(gWindow, initY, initX);

    WINDOW * map_win = newwin(
             m_map->height(), m_map->width(),
             initY, initX);

    for (int y=0; y < m_map->height(); ++y) {
        wmove(map_win, y, 0);
        for (int x=0; x < m_map->width(); ++x) {
            int32_t cellPos = x + (y * m_map->width());
            char cellType = m_map->m_cells[cellPos].getType();
            wchar_t cell_representation = CellRepresentation(cellType);

            move(y,x);
            cchar_t ct = {0};
            ct.chars[1] = L'\0';
            ct.chars[0] = cell_representation;
            add_wch(&ct);
        }
    }
    refresh();
    delwin(map_win);
    // rewind to the map start
    wmove(gWindow, initY, initX);
}

}
