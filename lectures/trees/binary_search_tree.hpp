#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "binary_tree.hpp"

template <typename T>
class BinarySearchTree : public BinaryTree<T> {

    using typename BinaryTree<T>::N;

    N*& findNode(T const& el) {
        N** node = &this->rootNode;
        while (*node != nullptr && el != (*node)->data)
            if (el < (*node)->data)
                node = &((*node)->left);
            else
                node = &((*node)->right);
        return *node;
    }
public:
    using typename BinaryTree<T>::Position;

    bool exists(T const& el) const {
        return search(el);
    }

    Position search(T const& el) const {
        Position pos = this->rootPos();
        while (pos && el != *pos)
            // не сме намерили елемента (el != *pos) и позицията е валидна (pos)
            if (el < *pos)
                pos = -pos;
            else
                pos = +pos;
        // или сме намерили елемента 
        // или позицията е невалидна
        return pos;
    }

    bool insert(T const& el) {
        N*& node = findNode(el);
        if (node != nullptr)
          // елементът го има, не правим нищо
          return false;
        // елементът го няма, добавяме го
        node = new N{el, nullptr, nullptr};
        return true;
    }
};

#endif // BINARY_SEARCH_TREE_HPP