#include "file_tree_item.hpp"
#include "file_tree_view.hpp"
#include <experimental/filesystem>
#include <memory>
#include <iostream>
#include <ncurses.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "USAGE: brun <script directory>\n";
        exit(0);
    }

    fs::path script_path(argv[1]);
    if (!fs::exists(script_path)) {
        std::cout << "ERROR: Directory does not exist\n";
        exit(0);
    }

    // Init
    initscr();
    noecho();

    // Create root node and read directories into nodes
    auto root = file_tree_from_path(script_path); 

    WINDOW* search_win;
    WINDOW* main_win;
    int h, w;

    // Init treeview
    file_tree_view tree(root.get(), stdscr, search_win);
    tree.refresh();

    // Loop while input is recieved
    while(tree.get_input());

    // Cleanup
    clear();
    endwin();

    return 0;
}
