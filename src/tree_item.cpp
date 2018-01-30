#include <tree_item.hpp>
std::unique_ptr<tree_item>& tree_item::add_child(std::unique_ptr<tree_item> t) 
{
    children.push_back(std::move(t));
    return children.back();
}

