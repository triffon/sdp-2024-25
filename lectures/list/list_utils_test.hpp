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

TEST_CASE_TEMPLATE("Разделяне на списък с четна дължина на два с приблизително равни дължини", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 10; i++)
        CHECK(list.insertLast(i));

    SomeList list1, list2;
    ListUtils<int, SomeList>::split(list, list1, list2);

    // Проверка дали елементите са разпределени в двата списъка без да гледаме дали са в правилния ред
    // Събираме елементите от двата списъка в множества
    std::set<int> list1_elements;
    for (int x : list1)
        list1_elements.insert(x);

    std::set<int> list2_elements;
    for (int x : list2)
        list2_elements.insert(x);

    // Проверяваме дали общото множество от елементи е равно на оригиналния списък
    std::set<int> all_elements = list1_elements;
    all_elements.insert(list2_elements.begin(), list2_elements.end());

    std::set<int> original_elements;
    for (int i = 1; i <= 10; i++)
        original_elements.insert(i);

    CHECK(all_elements == original_elements);

    // Проверяваме дали списъците list1 и list2 нямат общи елементи
    for (int x : list1_elements)
        CHECK(list2_elements.find(x) == list2_elements.end());

    // Проверяваме дали дължините на list1 и list2 се различават с не повече от 1
    CHECK(std::abs(int(list1_elements.size() - list2_elements.size())) <= 1);
}

TEST_CASE_TEMPLATE("Разделяне на списък с нечетна дължина на два с приблизително равни дължини", SomeList, LISTS) {
    SomeList list;
    for (int i = 1; i <= 11; i++)
        CHECK(list.insertLast(i));

    SomeList list1, list2;
    ListUtils<int, SomeList>::split(list, list1, list2);

    // Проверка дали елементите са разпределени в двата списъка без да гледаме дали са в правилния ред
    // Събираме елементите от двата списъка в множества
    std::set<int> list1_elements;
    for (int x : list1)
        list1_elements.insert(x);

    std::set<int> list2_elements;
    for (int x : list2)
        list2_elements.insert(x);

    // Проверяваме дали общото множество от елементи е равно на оригиналния списък
    std::set<int> all_elements = list1_elements;
    all_elements.insert(list2_elements.begin(), list2_elements.end());

    std::set<int> original_elements;
    for (int i = 1; i <= 11; i++)
        original_elements.insert(i);

    CHECK(all_elements == original_elements);

    // Проверяваме дали списъците list1 и list2 нямат общи елементи
    for (int x : list1_elements)
        CHECK(list2_elements.find(x) == list2_elements.end());

    // Проверяваме дали дължините на list1 и list2 се различават с не повече от 1
    CHECK(std::abs(int(list1_elements.size() - list2_elements.size())) <= 1);
}

TEST_CASE_TEMPLATE("Разделяне на празен списък", SomeList, LISTS) {
    SomeList list, list1, list2;
    ListUtils<int, SomeList>::split(list, list1, list2);

    CHECK(list1.empty());
    CHECK(list2.empty());
}

TEST_CASE_TEMPLATE("Разделяне на списък с 1 елемент", SomeList, LISTS) {
    SomeList list;
    CHECK(list.insertLast(42));

    SomeList list1, list2;
    ListUtils<int, SomeList>::split(list, list1, list2);

    CHECK_EQ(*list1.begin(), 42);
    CHECK_EQ(list1.begin().next(), list1.end());
    CHECK(list2.empty());
}

TEST_CASE_TEMPLATE("Разделяне на списък с 2 елемента", SomeList, LISTS) {
    SomeList list;
    CHECK(list.insertLast(42));
    CHECK(list.insertLast(43));

    SomeList list1, list2;
    ListUtils<int, SomeList>::split(list, list1, list2);

    CHECK_EQ(*list1.begin() + *list2.begin(), 85);
    CHECK((*list1.begin() == 42 || *list2.begin() == 42));
    CHECK_EQ(list1.begin().next(), list1.end());
    CHECK_EQ(list2.begin().next(), list2.end());
}

TEST_CASE_TEMPLATE("Сливане на два непразни списъка от четни и нечетни числа", SomeList, LISTS) {
    SomeList list1, list2;
    CHECK(list1.insertLast(1));
    CHECK(list1.insertLast(3));
    CHECK(list1.insertLast(5));
    CHECK(list1.insertLast(7));
    CHECK(list1.insertLast(9));

    CHECK(list2.insertLast(2));
    CHECK(list2.insertLast(4));
    CHECK(list2.insertLast(6));
    CHECK(list2.insertLast(8));
    CHECK(list2.insertLast(10));

    SomeList result = ListUtils<int, SomeList>::merge(list1, list2);

    int i = 1;
    for (int j : result)
        CHECK_EQ(i++, j);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Сливане на два списъка, като единият от тях е празен", SomeList, LISTS) {
    SomeList list1, list2;
    CHECK(list2.insertLast(1));
    CHECK(list2.insertLast(2));
    CHECK(list2.insertLast(3));

    SUBCASE("първият е празен") {
        SomeList result = ListUtils<int, SomeList>::merge(list1, list2);

        int i = 1;
        for (int j : result)
            CHECK_EQ(i++, j);
        CHECK_EQ(i, 4);
    }

    SUBCASE("вторият е празен") {
        SomeList result = ListUtils<int, SomeList>::merge(list2, list1);

        int i = 1;
        for (int j : result)
            CHECK_EQ(i++, j);
        CHECK_EQ(i, 4);
    }
}

TEST_CASE_TEMPLATE("Сливане на два празни списъка", SomeList, LISTS) {
    SomeList list1, list2;
    SomeList result = ListUtils<int, SomeList>::merge(list1, list2);
    CHECK(result.empty());
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

    SomeList result = ListUtils<int, SomeList>::mergeSort(list);

    int i = 1;
    for (int j : result)
        CHECK_EQ(i++, j);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Сортиране на празен списък", SomeList, LISTS) {
    SomeList list;
    ListUtils<int, SomeList>::mergeSort(list);
    CHECK(list.empty());
}

TEST_CASE_TEMPLATE("Сортиране на списък с 1 елемент", SomeList, LISTS) {
    SomeList list;
    CHECK(list.insertLast(42));

    ListUtils<int, SomeList>::mergeSort(list);

    CHECK_EQ(*list.begin(), 42);
    CHECK_EQ(list.begin().next(), list.end());
}