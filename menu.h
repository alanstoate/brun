#pragma once

#include <ncurses.h>

namespace menu {

class menu
{
public:
    menu (WINDOW* w) : win(w) {}

    void refresh() {
        for (auto& i : items) {
            wprintw(win, i.c_str());
        }
    }

private:
    WINDOW* win;
    std::vector<std::string> items;
};

} // namespace menu
