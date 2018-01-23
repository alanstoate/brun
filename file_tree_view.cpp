#include "file_tree_view.hpp"

namespace fs = std::experimental::filesystem;

file_tree_view::file_tree_view (file_tree_item* ti, WINDOW* win, WINDOW* s_win) : 
    tree_item_view(ti, win),
    main_window(win),
    search_window(s_win)
{
    add_input();
}

void file_tree_view::add_input() {
    add_input_rule('/', [&] (int y) { 
            mode = Mode::SEARCH;
            search_y = y;
            wclear(search_window);
            waddch(search_window, '/');
            return true; 
        });
    add_input_rule('q', [&] (int y) { 
            return false; 
        });
    add_input_rule('j', [&] (int y) { 
            if (y < item_list.size() - 1) 
            wmove(win, ++y, 0);
            return true; 
        });
    add_input_rule('k', [&] (int y) { 
            wmove(win, --y, 0);
            return true; 
        });
    add_input_rule('l', [&] (int y) { 
            get_item_at_line(y)->on_select();
            refresh();
            wmove(win, y,0);
            return true; 
        });
}

bool file_tree_view::get_input() {
    if (mode == Mode::NORMAL) {
        return tree_item_view::get_input(); 
    }
    else {
        int ch = wgetch(search_window);
        if (ch == '\n') {
            wmove(main_window, search_y, 0);
            mode = Mode::NORMAL;
            return true;
        }
        else if (ch == '\b') {
            search_string = search_string.substr(0 , search_string.size() - 1); 
        }

        search_string += ch;

        waddch(search_window, ch);
    }
    return true;
}
