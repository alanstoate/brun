#pragma once

#include "tree.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class file_tree_view : public brun::tree_item_view<fs::path> {
public:
    file_tree_view (brun::file_tree_item* ti, WINDOW* win);

private:
    void add_input();
};
