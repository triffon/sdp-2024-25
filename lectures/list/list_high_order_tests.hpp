#include "doctest.h"

#include "list_high_order.hpp"
#include "linked_list.hpp"
#include "double_linked_list.hpp"

TEST_CASE("foldr над списък с числата от 1 до 10 намира тяхната сума") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldr(plus, 0, list.begin());
    int sum = ListHighOrderFunctions<int, LinkedList>::foldr([](int x, int y) { return x + y; }, 0, list.begin());
    CHECK_EQ(sum, 55);
}

TEST_CASE("foldl над списък с числата от 1 до 10 намира тяхната сума") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldl(plus, 0, list.begin());
    int sum = ListHighOrderFunctions<int, LinkedList>::foldl([](int x, int y) { return x + y; }, 0, list.begin());
    CHECK_EQ(sum, 55);
}

TEST_CASE("повдигане на числата от 1 до 10 на квадрат с map") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // LinkedList<int> squares = ListHighOrderFunctions<int, LinkedList>::map(square, list.begin());
    LinkedList<int> squares = ListHighOrderFunctions<int, LinkedList>::map([](int x) { return x * x; }, list.begin());
    LinkedList<int>::Iterator it = squares.begin();
    for (int i = 1; i <= 10; i++)
        CHECK_EQ(*it++, i * i);
}

TEST_CASE("Филтриране на нечетните числа из числата от 1 до 10") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // LinkedList<int> odds = ListHighOrderFunctions<int, LinkedList>::filter(odd, list.begin());
    LinkedList<int> odds = ListHighOrderFunctions<int, LinkedList>::filter([](int x) { return x % 2 != 0; }, list.begin());
    LinkedList<int>::Iterator it = odds.begin();
    for (int i = 1; i <= 10; i += 2)
        CHECK_EQ(*it++, i);
}

TEST_CASE("Да се намери сумата от нечетните квадрати на числата от 1 до 10") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    CHECK_EQ(1 + 3 * 3 + 5 * 5 + 7 * 7 + 9 * 9,
         ListHighOrderFunctions<int, LinkedList>::foldr([](int x, int y) { return x + y; }, 0, 
            ListHighOrderFunctions<int, LinkedList>::map([](int x) { return x * x; },     
                ListHighOrderFunctions<int, LinkedList>::filter([](int x) { return x % 2 != 0; }, list.begin()).begin()).begin()));
}

// TODO: Да се намери произведението от най-малките положителни елементи на списък от списъци от числа