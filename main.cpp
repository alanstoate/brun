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

    int h, w;
    getmaxyx(stdscr, h,w);
    WINDOW* main_win = newwin(h -1,w,0,0);
    WINDOW* search_win = newwin(1,w,h-1,0);
    wprintw(search_win, std::string("search").c_str());
    wrefresh(search_win);

    // Init treeview
    file_tree_view tree(root.get(), main_win, search_win);
    tree.refresh();

    // Loop while input is recieved
    while(tree.get_input());

    // Cleanup
    clear();
    endwin();

    return 0;
}
