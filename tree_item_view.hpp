#pragma once

#include "tree_item.hpp"
#include <ncurses.h>
#include <functional>
#include <memory>
#include <vector>

// Object that takes a tree_item root and window and draws a tree in that 
// window
template <typename T>
class tree_item_view {
public:
    tree_item_view(tree_item<T>* r, WINDOW* w) :
        root(r),
        win(w)
    { }

    // Refresh and redraw the tree
    void refresh(); 

    // Get input from the user
    bool get_input();

    // Adds an event response as defined in func which will be called
    // when ch is pressed
    void add_input_rule(int ch, std::function<bool (int,int)> func);

    tree_item<T>* get_item_at_line(int y);

protected:
    WINDOW* win;
    tree_item<T>* root;
    std::vector<tree_item<T>*> item_list;

private:
    std::vector<std::pair<int, std::function<bool (int, int)>>> input_functions;
    void draw_item(tree_item<T>* item, int depth);
};

#include "tree_item_view.ipp"
