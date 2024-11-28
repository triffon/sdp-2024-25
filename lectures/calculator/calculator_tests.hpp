#include "doctest.h"
#include "rpn_calculator.hpp"
#include "binary_tree_calculator.hpp"

TEST_CASE("Пресмятане на израза в обратен полски запис от слайдовете") {
    RPNCalculator calc;
    CHECK_EQ(calc.calculateRPN("12+345/-*"), doctest::Approx(6.6));
}

TEST_CASE("Преобразуване на израза от слайдовете в обратен полски запис") {
    RPNCalculator calc;
    CHECK_EQ(calc.convertToRPN("(1+2)*(3-4/5)"), "12+345/-*");
}

TEST_CASE("Пресмятане на аритметичния израз от слайдовете") {
    RPNCalculator calc;
    CHECK_EQ(calc.calculate("(1+2)*(3-4/5)"), doctest::Approx(6.6));
}

TEST_CASE("Опит за деление на 0 в израза връща грешка") {
    RPNCalculator calc;
    CHECK_THROWS_AS(calc.calculate("1/0"), std::invalid_argument);
}

TEST_CASE("Преобразуване на втория израз от слайдовете в обратен полски запис") {
    RPNCalculator calc;
    CHECK_EQ(calc.convertToRPN("(1+2)*(3/4-5)"), "12+34/5-*");
}

TEST_CASE("Пресмятане на аритметичния израз от слайдовете") {
    RPNCalculator calc;
    CHECK_EQ(calc.calculate("(1+2)*(3/4-5)"), doctest::Approx(-12.75));
}

TEST_CASE("Пример за пресмятане на аритметичен израз с двоично дърво") {
    BinaryTreeCalculator calc;
    CHECK_EQ(calc.calculate("((1+2)*(3-(4/5)))"), doctest::Approx(6.6));
}