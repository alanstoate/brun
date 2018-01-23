#pragma once

#include "tree_item.hpp"
#include "tree_item_view.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>
#include <ncurses.h>

namespace fs = std::experimental::filesystem;

class file_tree_view : public tree_item_view<fs::path> {
public:
    file_tree_view (file_tree_item* ti, WINDOW* win, WINDOW* s_win);

    bool get_input();

private:
    enum class Mode {NORMAL, SEARCH};
    Mode mode = Mode::NORMAL;

    void add_input();

    WINDOW* search_window;
    WINDOW* main_window;
    int search_y;
    std::string search_string;

    void search_tree();
};
