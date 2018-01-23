#include "raii_attribs.hpp"

template <typename T>
void tree_item_view<T>::refresh() {
    wclear(win);
    item_list.clear();
    draw_item(root, 0);
    wmove(win, 0,0);
}

template <typename T>
bool tree_item_view<T>::get_input() {
    int ch = wgetch(win);
    int y, x;
    getyx(win, y, x);
    for (auto& f : input_functions) {
        if (f.first == ch)
            return f.second(y);
    }
    return true;

}

template <typename T>
void tree_item_view<T>::add_input_rule(int ch, std::function<bool (int)> func) {
    input_functions.push_back(std::make_pair(ch, func));
}

template <typename T>
tree_item<T>* tree_item_view<T>::get_item_at_line(int y) {
    return item_list.at(y); 
}

template <typename T>
void tree_item_view<T>::draw_item(tree_item<T>* item, int depth) {
    for (int i = 0; i < depth; ++i)
        wprintw(win, "  ");
    std::vector<int> atts;
    std::string output = item->print_item(atts);

    { // Scoped atts
        raii_attribs raii_atts(atts, win);
        wprintw(win, output.c_str());
        wprintw(win, "\n");
    }
    item_list.push_back(item);

    if (!item->folded) {
        for (auto& c : item->get_children()) {
            draw_item(c.get(), depth + 1); 
        }
    }
}
