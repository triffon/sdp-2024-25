#include <fstream>
#include "binary_tree_calculator.hpp"

// <израз> ::= <цифра> | (<израз><операция><израз>)
// приемаме, че изразът е валиден
// по подаден указател към начало на валдиен <израз> посторява дърво,
// представящо израза и установява указателя след края на <израз>

// TODO: проверка за валидност на израза
BinaryTreeCalculator::ExprTree BinaryTreeCalculator::buildTree(char const*& expr) {
    if (std::isdigit(*expr))
        return ExprTree(*expr++);
    ExprTree leftExpr = buildTree(++expr);
    // expr сочи <операция>
    char op = *expr;
    // expr сочи към началото на втория <израз>
    ExprTree rightExpr = buildTree(++expr);
    // expr сочи скобата
    ++expr;
    // прескачаме скобата
    return ExprTree(op, std::move(leftExpr), std::move(rightExpr));
}

double BinaryTreeCalculator::evaluateTree(ExprTree::Position const& pos) const {
    if (!pos)
        throw std::runtime_error("Невалидно дърво на израза!");
    return std::isdigit(*pos)
           ? digitValue(*pos)
           : applyOperation(*pos, evaluateTree(-pos), evaluateTree(+pos));
}


double BinaryTreeCalculator::calculate(std::string const& expr) {
    char const* ptr = expr.c_str();
    exprTree = buildTree(ptr);

    std::ofstream dotFile("exprtree.dot");
    exprTree.printDOT(dotFile);

    return evaluateTree(exprTree.rootPos());
}
