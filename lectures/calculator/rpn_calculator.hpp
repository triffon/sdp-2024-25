#ifndef RPN_CALCULATOR_HPP
#define RPN_CALCULATOR_HPP
#include <string>
#include "calculator.hpp"
#include "linked_stack.hpp"

using ResultStack = LinkedStack<double>;
using OperationStack = LinkedStack<char>;

class RPNCalculator : public Calculator {
    ResultStack results;
    OperationStack ops;
public:
    double calculateRPN(std::string const& rpn);
    std::string convertToRPN(std::string const& expr);
    double calculate(std::string const& expr) {
        return calculateRPN(convertToRPN(expr));
    }
};

#endif // RPN_CALCULATOR_HPP