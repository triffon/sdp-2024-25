#include "rpn_calculator.hpp"

double RPNCalculator::calculateRPN(std::string const& rpn) {
    for(char c : rpn) {
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

std::string RPNCalculator::convertToRPN(std::string const& expr) {
    std::string rpn;
    for(char c : expr)
        if (std::isdigit(c))
            // c е цифра, записваме я в резултата
            rpn += c;
        else if (c == ')') {
            // c е затваряща скоба, изваждаме всички операции до отваряща скоба
            while (ops.peek() != '(')
                rpn += ops.pop();
            // изваждане на отварящата скоба от стека
            ops.pop();
        } else if (c == '(')
            // c е отваряща скоба, добавяме я в стека
            ops.push(c);
        else {
            // c е операция, записваме я в стека с операции,
            // но преди това тя избутва всички останали операции с по-висок или равен приоритет
            while (!ops.empty() && ops.peek() != '(' && priority(ops.peek()) >= priority(c))
                rpn += ops.pop();
            ops.push(c);
        }
    while (!ops.empty())
        rpn += ops.pop();
    return rpn;
}
