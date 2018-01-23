template <typename T>
std::unique_ptr<tree_item<T>>& tree_item<T>::add_child(std::unique_ptr<tree_item<T>> t) 
{
    children.push_back(std::move(t));
    return children.back();
}

