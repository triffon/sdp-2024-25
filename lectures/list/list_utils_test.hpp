#include "doctest.h"

#include "list_utils.hpp"
#include "linked_list.hpp"

#define LISTS LinkedList<int>

TEST_CASE_TEMPLATE("Залепване на списък за друг списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));
    for (int i = 11; i <= 20; i++)
        CHECK(list2.insertLast(i));

    ListUtils<int, SomeList>::append(list1, list2);

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 21);
}

TEST_CASE_TEMPLATE("Залепване на празен списък към списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));

    ListUtils<int, SomeList>::append(list1, list2);

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Залепване на списък към празен списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list2.insertLast(i));

    ListUtils<int, SomeList>::append(list1, list2);

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Обръщане на празен списък", SomeList, LISTS) {
    SomeList list;
    ListUtils<int, SomeList>::reverse(list);
    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Обръщане на списък с числата от 1 до 10", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    ListUtils<int, SomeList>::reverse(list);

    int i = 10;
    for (int j : list)
        CHECK(j == i--);
    CHECK(i == 0);
}