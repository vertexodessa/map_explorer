#include "ConsoleViewBackend.h"

#include <cursesw.h>

namespace map_solver {

void ConsoleViewBackend::initialize() {
    def_prog_mode();
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
}

void ConsoleViewBackend::deInitialize() {
    erase();
    reset_prog_mode();
    curs_set(TRUE);
    refresh();
    endwin();
}

}
