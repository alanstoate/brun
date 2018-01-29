#pragma once

#include "tree_item.hpp"
#include "tree_item_view.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>
#include <ncurses.h>

namespace fs = std::experimental::filesystem;

class file_tree_view : public tree_item_view {
public:
    // Create new file_tree_view that displays root_item in window provided
    file_tree_view (file_tree_item* root_item, WINDOW* win);

    // Get input for file_tree_view
    bool get_input() override;

private:
    enum class Mode {NORMAL, SEARCH};
    Mode mode = Mode::NORMAL;

    int height, width;
    WINDOW* main_window;
    WINDOW* search_window;
    int search_y;
    std::string search_string;

    void add_input();
    void search_tree();
    WINDOW* set_dimensions(WINDOW* parent);
};
