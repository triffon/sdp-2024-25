#include "doctest.h"
#include <string>
#include "associative_list.hpp"

#define DICTIONARIES AssociativeList<int, std::string>

TEST_CASE_TEMPLATE("Добавяне на един елемент в речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add(42, "forty-two"));
    CHECK_EQ(dict.lookup(42), "forty-two");

    SUBCASE("Опит за добавяне на втори ключ със същата стойност") {
        CHECK(!dict.add(42, "42"));
        CHECK_EQ(dict.lookup(42), "forty-two");
    }
}

TEST_CASE_TEMPLATE("Добавяне на няколко елемента в речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add(42, "forty-two"));
    CHECK(dict.add(1, "one"));
    CHECK(dict.add(100, "hundred"));
    CHECK_EQ(dict.lookup(42), "forty-two");
    CHECK_EQ(dict.lookup(1), "one");
    CHECK_EQ(dict.lookup(100), "hundred");

    SUBCASE("Намиране на всички ключове") {
        size_t count = 0;
        for (int key : dict.keys()) {
            CHECK((key == 1 || key == 42 || key == 100));
            count++;
        }
        CHECK_EQ(count, 3);
    }
}

TEST_CASE_TEMPLATE("Изтриване на елемент от речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add(42, "forty-two"));
    CHECK(dict.add(1, "one"));
    CHECK(dict.add(100, "hundred"));
    CHECK(dict.contains(1));
    CHECK(dict.remove(1));
    CHECK(!dict.contains(1));
    CHECK(!dict.remove(1));
    CHECK_EQ(dict.lookup(42), "forty-two");
    CHECK_EQ(dict.lookup(100), "hundred");
}

TEST_CASE_TEMPLATE("Добавяне на всички числа от 1 до 100 в речник и изтриването им след това", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    for (int i = 1; i <= 100; i++)
        CHECK(dict.add(i, std::to_string(i)));
    for (int i = 100; i >= 1; i--)
        CHECK_EQ(dict.lookup(i), std::to_string(i));
    for (int i = 1; i <= 100; i++)
        CHECK(dict.remove(i));
    for (int i = 1; i <= 100; i++)
        CHECK(!dict.remove(i));
}