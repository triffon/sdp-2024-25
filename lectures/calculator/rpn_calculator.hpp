#ifndef RPN_CALCULATOR_HPP
#define RPN_CALCULATOR_HPP
#include <string>
#include "linked_stack.hpp"

using ResultStack = LinkedStack<double>;

class RPNCalculator {
    ResultStack results;
    static double digitValue(char digit) { return digit - '0'; }
    static double applyOperation(char op, double left_arg, double right_arg);
public:
    double calculateRPN(std::string const& rpn);
};

#endif // RPN_CALCULATOR_HPP