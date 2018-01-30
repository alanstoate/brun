#pragma once

#include "tree_item.hpp"
#include "tree_view.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>
#include <ncurses.h>

namespace fs = std::experimental::filesystem;

// Tree view for a file tree item
class file_tree_view : public tree_view {
public:
    // Create new file_tree_view that displays root_item in window provided
    file_tree_view (file_tree_item* root_item, WINDOW* win);

    // Get input for file_tree_view
    bool get_input() override;

private:
    // Mode
    enum class Mode {NORMAL, SEARCH};
    Mode mode = Mode::NORMAL;

    // Windows/attributes
    int height, width;
    WINDOW* main_window;
    WINDOW* search_window;
    int search_y;
    std::string search_string;

    // Lines that have been highlighted
    std::vector<int> highlighted_lines; 

    void add_input();
    void search_tree();
    bool recursive_search(tree_item* node, std::string& str);
    WINDOW* set_dimensions(WINDOW* parent);
    int move_to_next_highlighted(int current_line);
    int move_to_prev_highlighted(int current_line);
};
