#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <stdexcept>

template <typename T>
struct TreeNode {
    T data;
    TreeNode *left, *right;
};

template <typename T>
class BinaryTree {
    TreeNode *rootNode;

    TreeNode* copy(TreeNode* tn) {
        if (tn == nullptr)
            return nullptr;
        return new TreeNode{tn->data, copy(tn->left), copy(tn->right)};
    }

    void erase(TreeNode* tn) {
        if (tn != nullptr) {
            erase(tn->left);
            erase(tn->right);
            delete tn;
        }
    }

public:
    BinaryTree() : rootNode(nullptr) {}
    BinaryTree(T data, BinaryTree const& left, BinaryTree const& right) {
        rootNode = new TreeNode{data, copy(left.rootNode), copy(right.rootNode)};
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
};


#endif // BINARY_TREE_HPP