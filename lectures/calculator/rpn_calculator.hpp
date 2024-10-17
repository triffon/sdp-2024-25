#ifndef RPN_CALCULATOR_HPP
#define RPN_CALCULATOR_HPP
#include <string>
#include "linked_stack.hpp"

using ResultStack = LinkedStack<double>;
using OperationStack = LinkedStack<char>;

class RPNCalculator {
    ResultStack results;
    OperationStack ops;
    static double digitValue(char digit) { return digit - '0'; }
    static double applyOperation(char op, double left_arg, double right_arg);
public:
    double calculateRPN(std::string const& rpn);
    std::string convertToRPN(std::string const& expr);
    double calculate(std::string const& expr) {
        return calculateRPN(convertToRPN(expr));
    }
};

#endif // RPN_CALCULATOR_HPP