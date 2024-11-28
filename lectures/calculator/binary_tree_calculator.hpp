#ifndef BINARY_TREE_CALCULATOR_HPP
#define BINARY_TREE_CALCULATOR_HPP

#include <string>
#include "binary_tree.hpp"
#include "calculator.hpp"

class BinaryTreeCalculator : public Calculator {
    using ExprTree = BinaryTree<char>;
    ExprTree exprTree;

    static ExprTree buildTree(char const*& expr);
    double evaluateTree(ExprTree::Position const& pos) const;
public:
    double calculate(std::string const& expr);
};

#endif // BINARY_TREE_CALCULATOR_HPP