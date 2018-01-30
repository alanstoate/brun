#include "file_tree_item.hpp"

file_tree_item::file_tree_item (fs::path n) : path(n) {}

std::string file_tree_item::print_item(std::vector<int>& attribs) {
    if (fs::is_directory(path))
        attribs = {A_BOLD};
    else if (highlighted)
        attribs.push_back(A_UNDERLINE);
    return path.stem().string() + path.extension().string();
}

void file_tree_item::on_select() {
    // If item is directory, fold it
    if (fs::is_directory(path))
        folded = !folded;
    else {
    // If item is not directory, execute script and exit
        clear();
        endwin();
        system(path.string().c_str());
        exit(0);
    }
}

// Helper recursive function used by file_tree_from_path below
bool read_dir(file_tree_item& n) {
    bool found_sh = false;
    for (auto& d : fs::directory_iterator(n.path)) {
        auto node = std::make_unique<file_tree_item>(d.path());
        if (fs::is_directory(d)) {
            // Only include directories that contain scripts
            if (read_dir(*node)) {
                n.add_child(std::move(node));
            }
        }
        else if (d.path().extension().string() == ".sh") {
            n.add_child(std::move(node));
            found_sh = true;
        }
    }

    // found_sh will only be true if a bash script was in the directory
    return found_sh;
}

std::unique_ptr<file_tree_item> file_tree_from_path(const fs::path& n) {
    auto root = std::make_unique<file_tree_item>(n);
    root->folded = false;
    read_dir(*root);
    return std::move(root);
}
