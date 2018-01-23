#include "file_tree_item.hpp"
#include "file_tree_view.hpp"
#include <experimental/filesystem>
#include <memory>
#include <ncurses.h>

int main(int argc, char *argv[]) {
    // Init
    initscr();
    noecho();

    // Create root node and read directories into nodes
    auto root = file_tree_from_path(fs::current_path()); 

    // Init treeview
    file_tree_view tree(root.get(), stdscr);
    tree.refresh();

    // Loop while input is recieved
    while(tree.get_input());

    // Cleanup
    clear();
    endwin();

    return 0;
}
