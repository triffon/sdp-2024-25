#include "doctest.h"
#include "linked_list.hpp"

#define LISTS LinkedList<int>

TEST_CASE_TEMPLATE("При създаване списък е празен", SomeList, LISTS) {\
    SomeList list;
    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("При създаване на списък след вмъквъне на елемент вече не е празен", SomeList, LISTS) {\
    SomeList list;

    SUBCASE("В края") {
        list.insertLast(42);
        CHECK(!list.empty());
    }

    SUBCASE("В началото") {
        list.insertFirst(42);
        CHECK(!list.empty());
    }
}

TEST_CASE_TEMPLATE("Създаване на списък с числата от 1 до 10 и обхождането му", SomeList, LISTS) {\
    SomeList list;

    for (int i = 1; i <= 10; i++)
        list.insertLast(i);

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Създаване на списък с нечетните числа от 1 до 10 и вмъкване на четните числа между тях с insertAfter", SomeList, LISTS) {\
    SomeList list;

    for (int i = 1; i <= 10; i += 2)
        list.insertLast(i);

    typename SomeList::Iterator it = list.begin();
    for (int i = 2; i <= 10; i += 2, ++(++it))
        list.insertAfter(i, it);

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 11);
}