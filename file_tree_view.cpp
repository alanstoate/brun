#include "file_tree_view.hpp"

namespace fs = std::experimental::filesystem;

file_tree_view::file_tree_view (file_tree_item* ti, WINDOW* win, WINDOW* s_win) : 
    tree_item_view(ti, win),
    search_window(s_win)
{
    add_input();
}

void file_tree_view::add_input() {
    add_input_rule('q', [&] (int y) { 
            return false; 
        });
    add_input_rule('j', [&] (int y) { 
            if (y < item_list.size() - 1) 
                move(++y, 0);
            return true; 
        });
    add_input_rule('k', [&] (int y) { 
            move(--y, 0);
            return true; 
        });
    add_input_rule('l', [&] (int y) { 
            get_item_at_line(y)->on_select();
            refresh();
            move(y,0);
            return true; 
        });
}
