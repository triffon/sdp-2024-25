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
