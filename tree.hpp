#pragma once

#include <ncurses.h>
#include <functional>
#include <memory>
#include <vector>

namespace brun {

// Type T represents the the data store in each node of the tree
template <typename T>
class tree_item
{
public:
    // Init tree item from instance of T 
    tree_item (T d) : data(d) {}

    // Adds a child to the tree
    // returns a reference to the pointer of that child
    // TODO: figure out if it makes sense to use unique_ptr as reutrn here
    std::unique_ptr<tree_item<T>>& add_child(std::unique_ptr<tree_item<T>> t);

    // Returns a reference to the children
    std::vector<std::unique_ptr<tree_item<T>>>& get_children() { return children; }

    // Represents if the node is in the folded state or not
    bool folded = true;

    // Virtual functions required by derived classes to add functionality to
    // each tree
    
    // Value returned from this function will be printed on each line for each item
    virtual std::string print_item() = 0;
    // Allows custom behaviour for selecting item
    virtual void on_select() = 0;

    // Return a copy of the data
    T& get_data() { return data; }

protected:
    // Data
    T data;

private:
    std::vector<std::unique_ptr<tree_item<T>>> children;
};

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

}

#include "tree.ipp"
