#include "file_tree_view.hpp"
#include <algorithm>

namespace fs = std::experimental::filesystem;

file_tree_view::file_tree_view (file_tree_item* ti, WINDOW* win) :
    tree_view(ti, set_dimensions(win))
{
    // init input rules
    add_input(); 
}

// Add input rules for file_tree
void file_tree_view::add_input() {
    // Enter search mode
    add_input_rule('/', [&] (int y) { 
            mode = Mode::SEARCH;
            search_y = y;
            search_string.clear();
            wclear(search_window);
            waddch(search_window, '/');
            return true; 
        });

    // quit app
    add_input_rule('q', [&] (int y) { 
            return false; 
        });

    // move down
    add_input_rule('j', [&] (int y) { 
            if (y < item_list.size() - 1) 
            wmove(win, ++y, 0);
            return true; 
        });

    // move up
    add_input_rule('k', [&] (int y) { 
            wmove(win, --y, 0);
            return true; 
        });

    // select
    add_input_rule('l', [&] (int y) { 
            get_item_at_line(y)->on_select();
            refresh();
            wmove(win, y,0);
            return true; 
        });

    // go to next found item
    add_input_rule('n', [&] (int y) { 
            if (!highlighted_lines.empty())
                wmove(win, move_to_next_highlighted(y), 0);
            return true; 
        });

    // go to prev found item
    add_input_rule('N', [&] (int y) { 
            if (!highlighted_lines.empty())
                wmove(win, move_to_prev_highlighted(y), 0);
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
            search_string.clear();
            tree_view::refresh();
            return true;
        }

        search_string += ch;
        waddch(search_window, ch);
    }
    return true;
}

bool file_tree_view::recursive_search(tree_item* node, std::string& search_string) {
    bool found = false;
    for (auto& c : node->get_children()) {

        // This feels dodgy may need to rethink structure
        auto file_node = dynamic_cast<file_tree_item*>(c.get()); 

        if (fs::is_directory(file_node->path)) {
            if (recursive_search(c.get(), search_string)) {
                file_node->folded = false; 
                found = true;
            }
            else {
                file_node->folded = true;
            }
        }

        auto file_name = file_node->path.stem().string();
        if (file_name.find(search_string) != std::string::npos) {
            file_node->highlighted = true;
            c->folded = false;
            found = true;
        }
        else {
            file_node->highlighted = false;
        }
    }

    return found;
}

void file_tree_view::search_tree() {
    highlighted_lines.clear();
    recursive_search(root, search_string);
    refresh();
    for (auto it = item_list.begin(); it != item_list.end(); ++it) {
        // This feels dodgy may need to rethink structure (again)
        auto file_node = dynamic_cast<file_tree_item*>(*it); 
        if (file_node->highlighted)
            highlighted_lines.push_back(it - item_list.begin());
    }
}

WINDOW* file_tree_view::set_dimensions(WINDOW* parent) {
    getmaxyx(parent, height, width); 
    main_window = newwin(height -1,width,0,0);
    search_window = newwin(1,width,height-1,0);
    return main_window;
}

int file_tree_view::move_to_next_highlighted(int current) {
    auto line = std::find_if(highlighted_lines.begin(), highlighted_lines.end(),
            [&] (int i) { return i > current; });

    // Note: no checking that highlighted_lines is not empty
    return line != highlighted_lines.end() ? *line : highlighted_lines.front();
}

int file_tree_view::move_to_prev_highlighted(int current) {
    auto line = std::find_if(highlighted_lines.rbegin(), highlighted_lines.rend(),
            [&] (int i) { return i < current; });

    return line != highlighted_lines.rend() ? *line : highlighted_lines.back();
}
