#include "file_tree_view.hpp"

namespace fs = std::experimental::filesystem;

file_tree_view::file_tree_view (file_tree_item* ti, WINDOW* win) :
    tree_view(ti, set_dimensions(win))
{
    add_input();
}

void file_tree_view::add_input() {
    add_input_rule('/', [&] (int y) { 
            mode = Mode::SEARCH;
            search_y = y;
            search_string.clear();
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
        return tree_view::get_input(); 
    }
    else {
        int ch = wgetch(search_window);
        if (ch == '\n') {
            wmove(main_window, search_y, 0);
            mode = Mode::NORMAL;
            search_tree();
            tree_view::refresh();
            return true;
        }

        search_string += ch;
        waddch(search_window, ch);
    }
    return true;
}

bool recursive_search(tree_item* node, std::string& search_string) {
    bool found = false;
    for (auto& c : node->get_children()) {
        // This feels dodgy may need to rethink structure
        auto file_node = dynamic_cast<file_tree_item*>(c.get()); 

        if (fs::is_directory(file_node->path)) {
            if (recursive_search(c.get(), search_string)) {
                c->folded = false; 
                found = true;
            }
        }

        auto file_name = file_node->path.stem().string();
        if (file_name.find(search_string) != std::string::npos) {
            file_node->highlighted = true;
            c->folded = false;
            found = true;
        }
    }

    return found;
}

void file_tree_view::search_tree() {
    recursive_search(root, search_string);
}

WINDOW* file_tree_view::set_dimensions(WINDOW* parent) {
    getmaxyx(parent, height, width); 
    main_window = newwin(height -1,width,0,0);
    search_window = newwin(1,width,height-1,0);
    return main_window;
}
