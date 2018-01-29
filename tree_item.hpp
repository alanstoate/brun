pragma once 

#include <memory>
#include <vector>

// Type T represents the the data store in each node of the tree
class tree_item
{
public:
    // Init tree item from instance of T 
    tree_item () {}

    // Adds a child to the tree
    // returns a reference to the pointer of that child
    // TODO: figure out if it makes sense to use unique_ptr& as return here
    std::unique_ptr<tree_item>& add_child(std::unique_ptr<tree_item> t);

    // Returns a reference to the children
    std::vector<std::unique_ptr<tree_item>>& get_children() { return children; }

    // Represents if the node is in the folded state or not
    bool folded = true;

    // Virtual functions required by derived classes to add functionality to
    // each tree
    
    // Value returned from this function will be printed on each line for each item
    // Custom attributes can be set with the attribs parameter
    virtual std::string print_item(std::vector<int>& attribs) = 0;
    // Allows custom behaviour for selecting item
    virtual void on_select() = 0;

private:
    std::vector<std::unique_ptr<tree_item>> children;
};

