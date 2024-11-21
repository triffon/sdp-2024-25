#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "linked_list.hpp"

template <typename T>
class Tree {
    T data;
    LinkedList<Tree<T>> children;

public:
    using SubtreeIterator = typename LinkedList<Tree<T>>::Iterator;

private:

    void printEdges(std::ostream& os) const {
       for(Tree const& child : children) {
            os << "  " << root() << " -> " << child.root() << ";" << std::endl;
            child.printEdges(os);
       }
/*
       for(SubtreeIterator sit = subtrees(); sit; ++sit) {
            os << "  " << root() << " -> " << (*sit).root() << ";" << std::endl;
            (*sit).printEdges(os);
       }
*/
    }

public:
    Tree(T const& _data) : data(_data) {}

    // !!! прави се копие на tree
    Tree& addSubtree(Tree<T> const& tree) {
        children.insertLast(tree);
        return *this;
    }

    T const& root() const { return data; }
    T      & root()       { return data; }

    SubtreeIterator subtrees() const { return children.begin(); }

    void printDOT(std::ostream& os = std::cout) const {
        os << "digraph tree { " << std::endl;
        printEdges(os);
        os << "}" << std::endl;
    }

    int depth() const {
        int result = 1;
        /*
        for(SubtreeIterator sit = subtrees(); sit; ++sit)
            result = std::max(result, (*sit).depth() + 1);
        */
        for(Tree const& child : children)
            result = std::max(result, child.depth() + 1);
        return result;
    }
};


#endif // TREE_HPP