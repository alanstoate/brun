#pragma once

#include "tree_item.hpp"
#include "tree_item_view.hpp"
#include "file_tree_item.hpp"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class file_tree_view : public tree_item_view<fs::path> {
public:
    file_tree_view (file_tree_item* ti, WINDOW* win);

private:
    void add_input();
};
