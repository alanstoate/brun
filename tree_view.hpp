#pragma once

#include "tree_item.hpp"
#include <ncurses.h>
#include <functional>
#include <memory>
#include <vector>

// Object that takes a tree_item root and window and draws a tree in that 
// window
class tree_view {
public:
    tree_view(tree_item* r, WINDOW* w) :
        root(r),
        win(w)
    { }

    // Refresh and redraw the tree
    void refresh(); 

    // Get input from the user
    virtual bool get_input();

    // Adds an event response as defined in func which will be called
    // when ch is pressed
    void add_input_rule(int ch, std::function<bool (int)> func);

    tree_item* get_item_at_line(int y);

protected:
    WINDOW* win;
    tree_item* root;
    std::vector<tree_item*> item_list;

private:
    std::vector<std::pair<int, std::function<bool (int)>>> input_functions;
    void draw_item(tree_item* item, int depth);
};

