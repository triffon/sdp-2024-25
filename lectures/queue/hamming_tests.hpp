#include "doctest.h"
#include "hamming_generator.hpp"

TEST_CASE("Генерира коректно първите 10 числа на Hamming") {
    HammingGenerator hg;
    CHECK(hg.next() == 1);
    CHECK(hg.next() == 2);
    CHECK(hg.next() == 3);
    CHECK(hg.next() == 4);
    CHECK(hg.next() == 5);
    CHECK(hg.next() == 6);
    CHECK(hg.next() == 8);
    CHECK(hg.next() == 9);
    CHECK(hg.next() == 10);
    CHECK(hg.next() == 12);
}