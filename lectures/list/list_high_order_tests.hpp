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

TEST_CASE("foldr1 над празен списък") {
    LinkedList<int> list;

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldr(plus, 0, list.begin());
    CHECK_THROWS(ListHighOrderFunctions<int, LinkedList>::foldr1([](int x, int y) { return std::max(x,y); }, list.begin()));
}

TEST_CASE("foldr1 над списък с един елемент, намиращ максимален елемент") {
    LinkedList<int> list;
    CHECK(list.insertLast(5));

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldr(plus, 0, list.begin());
    int m = ListHighOrderFunctions<int, LinkedList>::foldr1([](int x, int y) { return std::max(x,y); }, list.begin());
    CHECK_EQ(m, 5);
}

TEST_CASE("foldr1 над списък с произволни по стойност и по ред числа, намиращ максималния елемент") {
    LinkedList<int> list;
    CHECK(list.insertLast(5));
    CHECK(list.insertLast(7));
    CHECK(list.insertLast(2));
    CHECK(list.insertLast(4));
    CHECK(list.insertLast(1));
    CHECK(list.insertLast(7));
    CHECK(list.insertLast(9));
    CHECK(list.insertLast(3));
    CHECK(list.insertLast(5));
    CHECK(list.insertLast(8));

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldr(plus, 0, list.begin());
    int m = ListHighOrderFunctions<int, LinkedList>::foldr1([](int x, int y) { return std::max(x,y); }, list.begin());
    CHECK_EQ(m, 9);
}

TEST_CASE("foldl над списък с числата от 1 до 10 намира тяхната сума") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // int sum = ListHighOrderFunctions<int, LinkedList>::foldl(plus, 0, list.begin());
    int sum = ListHighOrderFunctions<int, LinkedList>::foldl([](int x, int y) { return x + y; }, 0, list.begin());
    CHECK_EQ(sum, 55);
}

TEST_CASE("Повдигане на числата от 1 до 10 на квадрат с map") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    // LinkedList<int> squares = ListHighOrderFunctions<int, LinkedList>::map(square, list.begin());
    LinkedList<int> squares = ListHighOrderFunctions<int, LinkedList>::map([](int x) { return x * x; }, list.begin());
    LinkedList<int>::Iterator it = squares.begin();
    for (int i = 1; i <= 10; i++)
        CHECK_EQ(*it++, i * i);
}

TEST_CASE("Мутиращо повдигане на числата от 1 до 10 на квадрат с map") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    list.mapMut([](int x) { return x * x; });
    LinkedList<int>::Iterator it = list.begin();
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

TEST_CASE("Мутиращо филтриране, изпразващо списъка") {
    LinkedList<int> list;
    for (int i = 2; i <= 10; i+=2)
        CHECK(list.insertLast(i));

    list.filterMut([](int x) { return x % 2 != 0; });

    CHECK(list.empty());
}

TEST_CASE("Мутиращо филтриране на нечетните числа из числата от 1 до 10") {
    LinkedList<int> list;
    for (int i = 1; i <= 10; ++i)
        CHECK(list.insertLast(i));

    list.filterMut([](int x) { return x % 2 != 0; });
    LinkedList<int>::Iterator it = list.begin();
    for (int i = 1; i <= 10; i += 2)
        CHECK_EQ(*it++, i);
}

TEST_CASE("Мутиращо филтриране на нечетните числа из числата от 2 до 10") {
    LinkedList<int> list;
    for (int i = 2; i <= 10; ++i)
        CHECK(list.insertLast(i));

    list.filterMut([](int x) { return x % 2 != 0; });
    LinkedList<int>::Iterator it = list.begin();
    for (int i = 3; i <= 10; i += 2)
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

TEST_CASE("Да се намери произведението от най-малките положителни елементи на списък от списъци от числа") {
    LinkedList<LinkedList<int>> ll;
    LinkedList<int> l1, l2, l3;

    for (int i = -10; i <= 10; i++) {
        CHECK(l1.insertLast(1*i));
        CHECK(l2.insertLast(2*i));
        CHECK(l3.insertLast(3*i));
    }
    ll.insertFirst(l1);
    ll.insertFirst(l2);
    ll.insertFirst(l3);

    // min(l1) = 1
    // min(l2) = 2
    // min(l3) = 3

    CHECK_EQ(6,
        ListHighOrderFunctions<int, LinkedList, int>::foldr( 
            [](int x, int y) { return x * y; },
            1,
            ListHighOrderFunctions<LinkedList<int>, LinkedList, int>::map(
                [](LinkedList<int> l) { return ListHighOrderFunctions<int, LinkedList>::foldr1([](int currentEl, int recResult) { return std::min(currentEl,recResult); }, l.begin()); },
                ListHighOrderFunctions<LinkedList<int>, LinkedList>::map(
                    [](LinkedList<int> l) { return ListHighOrderFunctions<int, LinkedList>::filter([](int x) { return x > 0; }, l.begin()); },
                    ll.begin()
                ).begin()
            ).begin()
        )
    );
}