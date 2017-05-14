// ConsoleCellView
// ConsoleMapVieConfiguration


#include "ConsoleMapView.h"
#include "Logging.h"
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

}

void ConsoleMapView::Initialize() { }
void ConsoleMapView::DeInitialize() { }

void ConsoleMapView::Draw() {
    int initX, initY;
    getyx(stdscr, initY, initX);

    LOG_TRACE << "Initial cursor position " <<
        "y: " << initY << "," <<
        "x: " << initX;

    int w, h, x, y;
    h = m_map->height()+2;
    w = m_map->width()+2;
    y = initY;
    x = initX;

    WINDOW *map_win = newwin(h, w, y, x);

    LOG_TRACE << "Created curses WINDOW with parameters: " <<
        "h: " << h << "," <<
        "w: " << w << "," <<
        "y: " << y << "," <<
        "x: " << x;

    // border
    box(map_win, 0, 0);
    refresh();

    for (int y=0; y < m_map->height(); ++y) {
        wmove(map_win, y, 0);
        for (int x=0; x < m_map->width(); ++x) {
            int32_t cellPos = x + (y * m_map->width());
            char cellType = m_map->m_cells[cellPos].getType();
            wchar_t cell_representation = CellRepresentation(cellType);

            LOG_TRACE << "Outputting character at x: " << x << ", y: " << y;

            wmove(map_win, y+1, x+1);

            cchar_t ct = {0};
            ct.chars[1] = L'\0';
            ct.chars[0] = cell_representation;
            wadd_wch(map_win, &ct);
            wrefresh(map_win);
        }
    }
    refresh();
    delwin(map_win);

    // rewind to the map start
    wmove(stdscr, initY, initX);
}

}
