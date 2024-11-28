#include "rpn_calculator.hpp"
#include <cctype>
#include <cmath>
#include <stdexcept>

double RPNCalculator::applyOperation(char op, double left_arg, double right_arg) {
    switch(op) {
        case '+': return left_arg + right_arg;
        case '-': return left_arg - right_arg;
        case '*': return left_arg * right_arg;
        case '/':
            if (right_arg == 0)
                throw std::invalid_argument("Опит за деление на 0");
            return left_arg / right_arg;
        case '^': return pow(left_arg, right_arg);
        default: throw std::invalid_argument("Невалидна операция");
    }
}

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
            if(ops.empty())
                throw std::invalid_argument("Броят на затварящите скоби е повече.");

            // c е затваряща скоба, изваждаме всички операции до отваряща скоба
            while (ops.peek() != '('){
                rpn += ops.pop();
                if(ops.empty())
                    throw std::invalid_argument("Броят на затварящите скоби е повече.");
            }
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
    while (!ops.empty()){
        if(ops.peek() == '(')
            throw std::invalid_argument("Има повече отварящи скоби");
        rpn += ops.pop();
    }
    return rpn;
}

int RPNCalculator::priority(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;

        default: throw std::invalid_argument("Невалидна операция");
    }  
}