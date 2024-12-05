#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <vector>
#include <algorithm>
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

    N*& findMin(N*& start) {
        N** node = &start;
        while((*node)->left != nullptr)
            node = &((*node)->left);
        return *node;
    }

    /* Построява идеално балансирано ДДТ с елементите на индекси от left до right, включително */
    N* buildPerfectlyBalancedTree(std::vector<T>& elements, int left, int right) {
        if (left > right)
            return nullptr;
        int midIndex = (left + right) / 2;
        return new N{elements[midIndex], 
                     buildPerfectlyBalancedTree(elements, left, midIndex - 1),
                     buildPerfectlyBalancedTree(elements, midIndex + 1, right)};
    }
public:
    using typename BinaryTree<T>::Position;

    BinarySearchTree(std::vector<T> elements = std::vector<T>()) {
        std::sort(elements.begin(), elements.end());
        this->rootNode = buildPerfectlyBalancedTree(elements, 0, elements.size() - 1);
    }

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

    bool remove(T const& el) {
        N*& node = findNode(el);
        if (node == nullptr)
          // елементът го няма, не правим нищо
          return false;
        
        if (node->right == nullptr) {
            // нямаме дясно поддърво
            N* toDelete = node;
            node = node->left;
            delete toDelete;
            return true;
        }
        // node->right != nullptr;

        // TODO: да редуваме най-малък от дясното и най-голям от лявото

        // ходим наляво от дясното докато можем
        N*& minNode = node->left != nullptr ? findMin(node->right) : node;

        // прехвърляме стойността на minNode на мястото на корена
        node->data = minNode->data;
        N* toDelete = minNode;
        minNode = minNode->right;
        delete toDelete;

        return true;

    }
};

#endif // BINARY_SEARCH_TREE_HPP