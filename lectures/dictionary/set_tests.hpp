#include "doctest.h"
#include "set.hpp"
#include "associative_list.hpp"

#define SETS Set<int, AssociativeList>

TEST_CASE_TEMPLATE("Създаване на празно множество", Set, SETS) {
    Set set;
    CHECK(set.empty());
}

TEST_CASE_TEMPLATE("Добавяне на елемент в множество", Set, SETS) {
    Set set;
    CHECK(set.insert(42));
    CHECK(!set.empty());
}

TEST_CASE_TEMPLATE("Добавяне на елементи в множество", Set, SETS) {
    Set set;
    CHECK(set.insert(42));
    CHECK(!set.insert(42));
    CHECK(set.insert(1));
    CHECK(!set.insert(1));
    CHECK(set.insert(100));
    CHECK(!set.insert(100));
    CHECK(!set.empty());

    CHECK(set.contains(42));
    CHECK(set.contains(1));
    CHECK(set.contains(100));
}

TEST_CASE_TEMPLATE("Премахване на елементи от множество", Set, SETS) {
    Set set;
    CHECK(set.insert(42));
    CHECK(set.insert(1));
    CHECK(set.insert(100));

    CHECK(set.remove(42));
    CHECK(!set.remove(42));
    CHECK(set.remove(1));
    CHECK(!set.remove(1));
    CHECK(set.remove(100));
    CHECK(!set.remove(100));
    CHECK(set.empty());
}