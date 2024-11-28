#include <stdexcept>
#include <cmath>
#include "calculator.hpp"

double Calculator::applyOperation(char op, double left_arg, double right_arg) {
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

int Calculator::priority(char op) {
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