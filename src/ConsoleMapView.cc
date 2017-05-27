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
    // Possible to display a cell using different unicode charasters later.
    return cellType;
};

}

void ConsoleMapView::draw() const {
    int initX, initY;
    getyx(stdscr, initY, initX);

    LOG_TRACE << "Initial cursor position " <<
        "y: " << initY << "," <<
        "x: " << initX;

    int w, h, x, y;
    h = map()->height()+2;
    w = map()->width()+2;
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

    for (index_t y=0; y < map()->height(); ++y) {
        wmove(map_win, y, 0);
        for (index_t x=0; x < map()->width(); ++x) {
            index_t cellPos = x + (y * map()->width());
            char cellType = map()->m_cells[cellPos].getType();
            wchar_t cell_representation = CellRepresentation(cellType);

            LOG_TRACE << "Outputting character at x: " << x << ", y: " << y;

            wmove(map_win, y+1, x+1);

            cchar_t ct;
            memset(&ct, 0, sizeof(ct));
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
    getch();
}

}
