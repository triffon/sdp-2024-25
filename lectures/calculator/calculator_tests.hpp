#include "doctest.h"
#include "rpn_calculator.hpp"

TEST_CASE("Пресмятане на израза в обратен полски запис от слайдовете") {
    RPNCalculator calc;
    CHECK_EQ(calc.calculateRPN("12+345/-*"), doctest::Approx(6.6));
}