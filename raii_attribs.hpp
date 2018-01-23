#pragma once

#include <vector>
#include <ncurses.h>

// Raii class for setting scoped attributes
class raii_attribs
{
public:
    raii_attribs (std::vector<int> attribs, WINDOW* window) : 
        atts(attribs),
        win(window)
    {
        for (auto& a : atts) wattron(win, a);
    }

    ~raii_attribs () {
        for (auto& a : atts) wattroff(win, a);
    }

private:
     std::vector<int> atts;
     WINDOW* win;
};
