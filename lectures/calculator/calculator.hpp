#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

class Calculator {
public:
    virtual double calculate(std::string const& expr) = 0;
    static double digitValue(char digit) { return digit - '0'; }
    static double applyOperation(char op, double left_arg, double right_arg);
    static int priority(char op);
};

#endif // CALCULATOR_HPP