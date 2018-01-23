#pragma once

#include <vector>
#include <ncurses.h>

// Raii class for setting scoped attributes
class raii_attribs
{
public:
    raii_attribs (std::vector<int> attribs) : atts(attribs) {
        for (auto& a : atts) attron(a);
    }

    ~raii_attribs () {
        for (auto& a : atts) attroff(a);
    }

private:
     std::vector<int> atts;
};
