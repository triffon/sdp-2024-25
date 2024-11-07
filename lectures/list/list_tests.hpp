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
        CHECK(list.insertLast(42));
        CHECK(!list.empty());
    }

    SUBCASE("В началото") {
        CHECK(list.insertFirst(42));
        CHECK(!list.empty());
    }
}

TEST_CASE_TEMPLATE("Създаване на списък с числата от 1 до 10 и обхождането му", SomeList, LISTS) {\
    SomeList list;

    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Опит за вмъкване след невалидна позиция в непразен списък", SomeList, LISTS) {\
    SomeList list;
    list.insertLast(5);
    CHECK(!list.insertAfter(42, list.end()));
}

TEST_CASE_TEMPLATE("Опит за вмъкване преди невалидна позиция в непразен списък", SomeList, LISTS) {\
    SomeList list;
    list.insertLast(5);
    CHECK(!list.insertBefore(42, list.end()));
}


TEST_CASE_TEMPLATE("Създаване на списък с нечетните числа от 1 до 10 и вмъкване на четните числа между тях с insertAfter", SomeList, LISTS) {\
    SomeList list;

    for (int i = 1; i <= 10; i += 2)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin();
    for (int i = 2; i <= 10; i += 2, ++(++it))
        CHECK(list.insertAfter(i, it));

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Вмъкване на числата от 1 до 10 в началото и обхождането им", SomeList, LISTS) {
    SomeList list;

    for (int i = 10; i >= 1; i--)
        CHECK(list.insertFirst(i));

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Създаване на списък с нечетните числа от 1 до 10 и вмъкване на четните числа между тях с insertBefore", SomeList, LISTS) {\
    SomeList list;

    for (int i = 1; i <= 10; i += 2)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin().next();
    for (int i = 2; i <= 8; i += 2, ++it)
        CHECK(list.insertBefore(i, it));

    int i = 1;
    for (int j : list)
        CHECK(j == i++);
    CHECK(i == 10);
}

TEST_CASE_TEMPLATE("Опит за невалидно изтриване на елемент с deleteAfter ", SomeList, LISTS) {
    SomeList list;
    int i;
    CHECK(!list.deleteAfter(i, list.end()));
    list.insertLast(5);
    CHECK(!list.deleteAfter(i, list.end()));
    CHECK(!list.deleteAfter(i, list.last()));
}

TEST_CASE_TEMPLATE("В списък с числата от 1 до 10 изтриваме четните числа с deleteAfter", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin();
    for(int i = 2, j; it; ++it, i += 2) {
        CHECK(list.deleteAfter(j, it));
        CHECK_EQ(i, j);
    }

    CHECK(list.insertLast(11));

    // в списъка са останали само нечетните елементи
    int i = 1;
    for(int j : list) {
        CHECK_EQ(i, j);
        i += 2;
    }
    CHECK_EQ(i, 13);
}

TEST_CASE_TEMPLATE("Създаване на списък с числата от 1 до 10 и изтриването на всички елементи с deleteAt", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin(), nextit;
    for(int i = 1, j; it; it = nextit, i++) {
        nextit = it.next();
        CHECK(list.deleteAt(j, it));
        CHECK(!it.valid());
        CHECK_EQ(i, j);
    }

    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Създаване на списък с числата от 1 до 11 и изтриването на всички нечетни елементи с deleteAt", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 11; i++)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin(), nextit = it.next();
    for(int i = 1, j; it && nextit; it = nextit, i += 2) {
        nextit = it.next();
        if (nextit)
            nextit = nextit.next();
        CHECK(list.deleteAt(j, it));
        CHECK(!it.valid());
        CHECK_EQ(i, j);
    }

    CHECK(list.insertFirst(0));
    CHECK(list.insertLast(12));

    // в списъка са останали само четните елементи от 0 до 12
    int i = 0;
    for(int j : list) {
        CHECK_EQ(i, j);
        i += 2;
    }
    CHECK_EQ(i, 14);

}

TEST_CASE_TEMPLATE("Опит за невалидно изтриване на елемент с deleteAt", SomeList, LISTS) {
    SomeList list;
    int i;
    typename SomeList::Iterator invalid = list.end();
    CHECK(!list.deleteAt(i, invalid));
    list.insertLast(5);
    CHECK(!list.deleteAt(i, invalid));
}

TEST_CASE_TEMPLATE("Опит за невалидно изтриване на елемент с deleteBefore ", SomeList, LISTS) {
    SomeList list;
    int i;
    CHECK(!list.deleteBefore(i, list.end()));
    list.insertLast(5);
    CHECK(!list.deleteBefore(i, list.end()));
    CHECK(!list.deleteBefore(i, list.begin()));
}

TEST_CASE_TEMPLATE("В списък с числата от 1 до 10 изтриваме с deleteBefore всички нечетни елементи", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    typename SomeList::Iterator it = list.begin().next();
    for(int i = 1, j; it; ++it && ++it, i += 2) {
        CHECK(list.deleteBefore(j, it));
        CHECK_EQ(i, j);
    }

    CHECK(list.insertFirst(0));

    // в списъка са останали само четните елементи
    int i = 0;
    for(int j : list) {
        CHECK_EQ(i, j);
        i += 2;
    }
    CHECK_EQ(i, 12);
}