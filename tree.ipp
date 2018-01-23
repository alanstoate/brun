namespace brun {

template <typename T>
std::unique_ptr<tree_item<T>>& tree_item<T>::add_child(std::unique_ptr<tree_item<T>> t) 
{
    children.push_back(std::move(t));
    return children.back();
}

template <typename T>
void tree_item_view<T>::refresh() {
    move(0,0);
    wclear(win);
    item_list.clear();
    draw_item(root, 0);
}

template <typename T>
bool tree_item_view<T>::get_input() {
    int ch = getch();
    int y, x;
    getyx(win, y, x);
    for (auto& f : input_functions) {
        if (f.first == ch)
            return f.second(y, x);
    }
    return true;

}

template <typename T>
void tree_item_view<T>::add_input_rule(int ch, std::function<bool (int,int)> func) {
    input_functions.push_back(std::make_pair(ch, func));
}

template <typename T>
tree_item<T>* tree_item_view<T>::get_item_at_line(int y) {
    return item_list.at(y); 
}

template <typename T>
void tree_item_view<T>::draw_item(tree_item<T>* item, int depth) {
    for (int i = 0; i < depth; ++i) wprintw(win, "  ");
    wprintw(win, item->print_item().c_str());
    wprintw(win, "\n");
    item_list.push_back(item);

    if (!item->folded) {
        for (auto& c : item->get_children()) {
            draw_item(c.get(), depth + 1); 
        }
    }
}

}
