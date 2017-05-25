#include "ConsolePathView.h"
#include "Logging.h"
#include "Path.h"

#include <cursesw.h>

namespace map_solver {

void ConsolePathView::draw() const {
    if(!m_path)
        return;

    int initX, initY;
    getyx(stdscr, initY, initX);
    int w, h, x, y;
    h = m_path->fieldWidth()+2;
    w = m_path->fieldHeight()+2;
    y = initY;
    x = initX;

    WINDOW *map_win = newwin(h, w, y, x);

    // border
    box(map_win, 0, 0);
    refresh();


    int width  = w-2;
    int height = h-2;

    for (int y=0; y < height; ++y) {
        wmove(map_win, y, 0);
        for (int x=0; x < width; ++x) {
            bool needsDisplay = m_path->cell(x,y);
            if(!needsDisplay)
                continue;

            LOG_TRACE << "Outputting character at x: " << x << ", y: " << y;

            wmove(map_win, y+1, x+1);

            cchar_t ct;
            memset(&ct, 0, sizeof(ct));

            ct.chars[1] = L'\0';
            ct.chars[0] = L'*';
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
