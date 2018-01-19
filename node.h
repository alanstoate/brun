#pragma once

#include <memory>
#include <vector>
#include <experimental/filesystem>

namespace directory {
namespace fs = std::experimental::filesystem;



class Node {
public:
    Node (fs::path path, bool directory) : 
        _path(path),
        _directory(directory)
    {
    }


    Node* add_child(std::unique_ptr<Node> c) {
        c->_parent = this;
        children.emplace_back(std::move(c));
        return children.back().get();
    } 


    // setters
    void set_expanded(bool ex) { expanded = ex; }

    // getters
    std::vector<std::unique_ptr<Node>>& get_children() { return children; }
    fs::path get_path() { return _path; }
    bool is_expanded() { return expanded; }
    bool is_directory() { return _directory; }

private:
    fs::path _path;
    bool _directory;
    bool expanded = false;

    std::vector<std::unique_ptr<Node>> children;
    std::unique_ptr<Node> child;
    Node* _parent = nullptr;

}; // class Node

void scan_dir(const fs::path& path, directory::Node* parent) {
    for (auto& d : fs::directory_iterator(path)) {
        if (fs::is_directory(d.path())) {
            auto n = parent->add_child(std::make_unique<Node>(d.path(), true));
            scan_dir(d.path(), n);
        }
        else {
            parent->add_child(std::make_unique<Node>(d.path(), false));
        }
    }
}

} // namespace directory
