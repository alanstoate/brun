#pragma once

#include "tree_item.hpp"
#include <ncurses.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

// Derived from tree item
class file_tree_item : public tree_item<fs::path>
{
public:
    file_tree_item (fs::path n);

    // Virtual functions to provide functionality
    std::string print_item() override;
    void on_select() override;
};

// Creates a root tree_item from a given path
std::unique_ptr<file_tree_item> file_tree_from_path(const fs::path& n);
