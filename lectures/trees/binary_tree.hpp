#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct BinaryTreeNode {
    T data;
    BinaryTreeNode *left, *right;
};

template <typename T>
class BinaryTreePosition {
    BinaryTreeNode<T>* node;
public:
    BinaryTreePosition(BinaryTreeNode<T>* tn = nullptr) : node(tn) {}

    bool valid() const { return node != nullptr; }

    BinaryTreePosition left() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до ляво поддърво на невалидна позиция");
        return BinaryTreePosition(node->left);
    }

    BinaryTreePosition right() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до дясно поддърво на невалидна позиция");
        return BinaryTreePosition(node->right);
    }

    T const& get() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до стойност на невалидна позиция");
        return node->data;
    }

    T& get() {
        if (!valid())
            throw std::runtime_error("Опит за достъп до стойност на невалидна позиция");
        return node->data;
    }

    operator bool() const { return valid(); }

    T const& operator*() const { return get(); }
    T      & operator*()       { return get(); }

    BinaryTreePosition operator-() const { return left(); }
    BinaryTreePosition operator+() const { return right(); }
};

template <typename T>
class BinaryTree {
protected:
    using N = BinaryTreeNode<T>;
    N *rootNode;

private:
    static N* copy(N* tn) {
        if (tn == nullptr)
            return nullptr;
        return new N{tn->data, copy(tn->left), copy(tn->right)};
    }

    static void erase(N* tn) {
        if (tn != nullptr) {
            erase(tn->left);
            erase(tn->right);
            delete tn;
        }
    }

public:
    using Position = BinaryTreePosition<T>;

    BinaryTree() : rootNode(nullptr) {}
    BinaryTree(T data, BinaryTree&& left = BinaryTree(), BinaryTree&& right = BinaryTree()) {
        rootNode = new N{data, left.rootNode, right.rootNode};
        left.rootNode = right.rootNode = nullptr;
    }
    BinaryTree(BinaryTree const& bt) : rootNode(copy(bt.rootNode)) {}
    BinaryTree& operator=(BinaryTree const& bt) {
        if (this != &bt) {
            erase(rootNode);
            rootNode = copy(bt.rootNode);
        }
        return *this;
    }
    ~BinaryTree() { erase(rootNode); }

    bool empty() const { return rootNode == nullptr; }

    Position rootPos() const { return Position(rootNode); }
    
    T const& root() const {
        if (empty())
            throw std::runtime_error("Опит за достъп до корен на празно дърво");
        return rootNode->data;
    }

    T& root() {
        if (empty())
            throw std::runtime_error("Опит за достъп до корен на празно дърво");
        return rootNode->data;
    }

    BinaryTree left() const {
        if (empty())
            throw std::runtime_error("Опит за достъп до ляво поддърво на празно дърво");
        BinaryTree result;
        result.rootNode = copy(rootNode->left);
        return result;
    }

    BinaryTree right() const {
        if (empty())
            throw std::runtime_error("Опит за достъп до дясно поддърво на празно дърво");
        BinaryTree result;
        result.rootNode = copy(rootNode->right);
        return result;
    }

    static void printDOT(std::ostream& os, Position pos) {
        if (pos) {
            if (-pos) {
                os << "  \"" << *pos << "\" -> \"" << *-pos << "\";\n";
                printDOT(os, -pos);
            }
            if (+pos) {
                os << "  \"" << *pos << "\" -> \"" << *+pos << "\";\n";
                printDOT(os, +pos);
            }
        }
    }

    void printDOT(std::ostream& os = std::cout) const {
        os << "digraph BinaryTree {" << std::endl;
        printDOT(os, rootPos());
        os << "}" << std::endl;
    }

    size_t depth() const {
        return depth(rootPos());
    }

    static size_t depth(Position pos) {
        return !pos ? 0 : 1 + std::max(depth(-pos), depth(+pos));
    }

    bool operator==(BinaryTree const& bt) const {
        return equal(rootPos(), bt.rootPos());
    }

    bool operator!=(BinaryTree const& bt) const {
        return !(*this == bt);
    }   

private:
    static bool equal(Position const& pos1, Position const& pos2) {
        return !pos1 && !pos2 || pos1 && pos2 && *pos1 == *pos2 && equal(-pos1, -pos2) && equal(+pos1, +pos2);
    }
};


#endif // BINARY_TREE_HPP