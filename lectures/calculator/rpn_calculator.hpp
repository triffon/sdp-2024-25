#ifndef RPN_CALCULATOR_HPP
#define RPN_CALCULATOR_HPP
#include <string>
#include "linked_stack.hpp"

using ResultStack = LinkedStack<double>;
using OperationStack = LinkedStack<char>;
using BracesStack = LinkedStack<char>;

class RPNCalculator {
    ResultStack results;
    OperationStack ops;
    BracesStack braces;
    static double digitValue(char digit) { return digit - '0'; }
    static double applyOperation(char op, double left_arg, double right_arg);
    static int priority(char op);
    static bool isSymbol(char op);
public:
    double calculateRPN(std::string const& rpn);
    std::string convertToRPN(std::string const& expr);
    double calculate(std::string const& expr) {
        return calculateRPN(convertToRPN(expr));
    }
};

#endif // RPN_CALCULATOR_HPP