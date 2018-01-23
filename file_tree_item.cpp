#include "file_tree_item.hpp"

namespace brun {

file_tree_item::file_tree_item (fs::path n) : tree_item(n) {}

std::string file_tree_item::print_item() {
    return data.stem().string();
}

void file_tree_item::on_select() {
    if (fs::is_directory(data))
        folded = !folded;
    else {
        clear();
        endwin();
        system(data.string().c_str());
        exit(0);
    }
}

void read_dir(file_tree_item& n) {
    for (auto& d : fs::directory_iterator(n.get_data())) {
        auto node = std::make_unique<file_tree_item>(d.path());
        if (fs::is_directory(d))
            read_dir(*node);

        n.add_child(std::move(node));
    }
}

std::unique_ptr<file_tree_item> file_tree_from_path(const fs::path& n) {
    auto root = std::make_unique<file_tree_item>(n);
    read_dir(*root);
    return std::move(root);
}
}
