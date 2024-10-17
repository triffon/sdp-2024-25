#include "rpn_calculator.hpp"
#include <cctype>
#include <cmath>
#include <stdexcept>

double RPNCalculator::applyOperation(char op, double left_arg, double right_arg) {
    switch(op) {
        case '+': return left_arg + right_arg;
        case '-': return left_arg - right_arg;
        case '*': return left_arg * right_arg;
        case '/': return left_arg / right_arg;
        case '^': return pow(left_arg, right_arg);
        default: throw std::invalid_argument("Невалидна операция");
    }
}

double RPNCalculator::calculateRPN(std::string const& s) {
    for(char c : s) {
        if (std::isdigit(c)) {
            // c е цифра
            results.push(digitValue(c));
        } else {
            // c е операция
            double right_arg = results.pop();
            double left_arg  = results.pop();
            results.push(applyOperation(c, left_arg, right_arg));
        }
    }
    return results.pop();
}