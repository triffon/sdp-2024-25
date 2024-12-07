#include "doctest.h"
#include "linked_list.hpp"
#include "double_linked_list.hpp"

#define LISTS LinkedList<int>, DoubleLinkedList<int>

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

TEST_CASE_TEMPLATE("Изтриване на всички елементи в списък от 1 до 10 с deleteFirst", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    for(int i = 1, j; list.deleteFirst(j); i++) {
        CHECK_EQ(i, j);
    }

    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Изтриване на всички елементи в списък от 1 до 10 с deleteLast", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    for(int i = 10, j; list.deleteLast(j); i--) {
        CHECK_EQ(i, j);
    }

    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("При копиране на списък с конструктор не се получава споделяне на памет", SomeList, LISTS) {
    SomeList list1;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));

    SomeList list2(list1);

    CHECK(list1.insertFirst(0));
    CHECK(list1.insertLast(11));
    int x = 0;
    CHECK(list2.deleteFirst(x));
    CHECK_EQ(x, 1);
    CHECK(list2.deleteLast(x));
    CHECK_EQ(x, 10);

    int i = 0;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 12);

    i = 2;
    for (int j : list2)
        CHECK(j == i++);
    CHECK(i == 10);
}

TEST_CASE_TEMPLATE("При копиране на списък с операция за присвояване не се получава споделяне на памет", SomeList, LISTS) {
    SomeList list1;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));


    SomeList list2;

    for (int i = 20; i <= 30; i++)
        CHECK(list2.insertLast(i));

    list2 = list1;

    CHECK(list1.insertFirst(0));
    CHECK(list1.insertLast(11));
    int x = 0;
    CHECK(list2.deleteFirst(x));
    CHECK_EQ(x, 1);
    CHECK(list2.deleteLast(x));
    CHECK_EQ(x, 10);

    int i = 0;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 12);

    i = 2;
    for (int j : list2)
        CHECK(j == i++);
    CHECK(i == 10);
}


TEST_CASE_TEMPLATE("Залепване на списък за друг списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));
    for (int i = 11; i <= 20; i++)
        CHECK(list2.insertLast(i));

    list1.append(std::move(list2));

    CHECK(list2.empty());

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 21);
}

TEST_CASE_TEMPLATE("Залепване на празен списък към списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list1.insertLast(i));

    list1.append(std::move(list2));

    CHECK(list2.empty());

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE_TEMPLATE("Залепване на списък към празен списък", SomeList, LISTS) {
    SomeList list1, list2;
    for (int i = 1; i <= 10; i++)
        CHECK(list2.insertLast(i));

    list1.append(std::move(list2));

    CHECK(list2.empty());

    int i = 1;
    for (int j : list1)
        CHECK(j == i++);
    CHECK(i == 11);
}

TEST_CASE("Проверка, че списък е палиндром с isPalindrome()") {
    DoubleLinkedList<int> list;
    CHECK(list.isPalindrome());
    CHECK(list.insertLast(1));
    CHECK(list.isPalindrome());
    CHECK(list.insertLast(2));
    CHECK(!list.isPalindrome());
    CHECK(list.insertLast(1));
    CHECK(list.isPalindrome());
    CHECK(list.insertLast(2));
    CHECK(!list.isPalindrome());
    CHECK(list.insertLast(1));
    CHECK(list.isPalindrome());
}

TEST_CASE("Празният списък е палиндром") {
    DoubleLinkedList<int> list;
    CHECK(list.isPalindrome());
}

TEST_CASE("Списък с 1 елемент е палиндром") {
    DoubleLinkedList<int> list;
    CHECK(list.insertLast(1));
    CHECK(list.isPalindrome());
}

TEST_CASE("Списък с 2 елемента е палиндром, ако елементите са равни") {
    DoubleLinkedList<int> list;
    CHECK(list.insertLast(1));
    CHECK(list.insertLast(1));
    CHECK(list.isPalindrome());
}

TEST_CASE("Списък с 2 елемента не е палиндром, ако елементите не са равни") {
    DoubleLinkedList<int> list;
    CHECK(list.insertLast(1));
    CHECK(list.insertLast(2));
    CHECK(!list.isPalindrome());
}


TEST_CASE_TEMPLATE("Обръщане на празен списък без заделяне на нова памет", SomeList, LISTS) {
    SomeList list;
    list.reverse();
    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Обръщане на списък с 1 елемент без заделяне на нова памет", SomeList, LISTS) {
    const unsigned val = 42;
    SomeList list;

    list.insertFirst(val);
    list.reverse();
    
    CHECK(!list.empty());
    CHECK_EQ(list.begin().get(), val);
}

TEST_CASE_TEMPLATE("Обръщане на списък с числата от 1 до 10 без заделяне на нова памет", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    list.reverse();

    int i = 10;
    for (int j : list)
        CHECK(j == i--);
    CHECK(i == 0);
}

TEST_CASE_TEMPLATE("Сортиране на непразен списък с числата от 1 до 10 в разбъркан ред", SomeList, LISTS) {
    SomeList list;
    CHECK(list.insertLast(5));
    CHECK(list.insertLast(3));
    CHECK(list.insertLast(7));
    CHECK(list.insertLast(1));
    CHECK(list.insertLast(10));
    CHECK(list.insertLast(2));
    CHECK(list.insertLast(9));
    CHECK(list.insertLast(4));
    CHECK(list.insertLast(6));
    CHECK(list.insertLast(8));

    list.sort();

    int i = 1;
    for (int j : list)
        CHECK_EQ(i++, j);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Сортиране на празен списък", SomeList, LISTS) {
    SomeList list;
    list.sort();
    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Сортиране на списък с 1 елемент", SomeList, LISTS) {
    SomeList list;
    CHECK(list.insertLast(42));

    list.sort();

    CHECK_EQ(*list.begin(), 42);
    CHECK_EQ(list.begin().next(), list.end());
}