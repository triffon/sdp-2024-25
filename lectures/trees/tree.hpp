#ifndef TREE_HPP
#define TREE_HPP

#include "linked_list.hpp"

template <typename T>
class Tree {
    T data;
    LinkedList<Tree<T>> children;
public:
    using SubtreeIterator = typename LinkedList<Tree<T>>::Iterator;

    Tree(T const& _data) : data(_data) {}
    Tree& addSubtree(Tree<T> const& tree) {
        children.insertLast(tree);
        return *this;
    }

    T const& root() const { return data; }
    T      & root()       { return data; }

    SubtreeIterator subtrees() const { return children.begin(); }
};


#endif // TREE_HPP