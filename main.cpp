#include "tree.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>
#include <memory>
#include <ncurses.h>

void init_session () {
    initscr();
    noecho();
}

void end_session () {
    clear();
    endwin();
}

int main(int argc, char *argv[]) {
    init_session();

    // Create root node and read directories into nodes
    auto root = brun::file_tree_from_path(fs::current_path()); 

    // Init treeview
    brun::tree_item_view<fs::path> tree(root.get(), stdscr);
    tree.refresh();

    // Loop while input is recieved
    while(tree.get_input());

    end_session();
    return 0;
}
