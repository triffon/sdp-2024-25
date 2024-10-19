#include "doctest.h"
#include "stack.hpp"
#include "resizing_stack.hpp"
#include "linked_stack.hpp"

#define STACKS Stack<int>, ResizingStack<int>, LinkedStack<int>
#define MOVEABLE_STACKS ResizingStack<int>, LinkedStack<int>


TEST_CASE_TEMPLATE("Стек, създаден по подразбиране, е празен", SomeStack, STACKS) {
    SomeStack s;
    CHECK(s.empty());
}

TEST_CASE_TEMPLATE("След включване на елемент в стека, той вече не е празен", SomeStack, STACKS) {
    SomeStack s;
    s.push(42);
    CHECK(!s.empty());
}

TEST_CASE_TEMPLATE("Опит за изключване от празен стек хвърля изключение", SomeStack, STACKS) {
    SomeStack s;
    CHECK_THROWS(s.pop());
}

TEST_CASE_TEMPLATE("Опит за поглеждане в празен стек хвърля изключение", SomeStack, STACKS) {
    SomeStack s;
    CHECK_THROWS(s.peek());
}

TEST_CASE_TEMPLATE("Включен елемент може да бъде изключен веднага от стека", SomeStack, STACKS) {
    SomeStack s;
    s.push(42);
    CHECK(s.pop() == 42);
}

TEST_CASE_TEMPLATE("Няколко включени елемента в стека се изключват в обратен ред", SomeStack, STACKS) {
    SomeStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
}

TEST_CASE("Хвърля се изключение при опит за добавяне на елемент в пълен стек") {
    Stack<int> s;
    for (int i = 0; i < Stack<int>::MAX; i++)
        s.push(i);
    CHECK_THROWS(s.push(42));
}

TEST_CASE_TEMPLATE("Проверка дали промяна на копиран стек не засяга оригинала", SomeStack, STACKS) {
    SomeStack s1;
    s1.push(1);
    s1.push(2);
    SomeStack s2 = s1;

    SUBCASE("Присвоеният стек e същият като оригинала") {
        CHECK(s2.pop() == 2);
        CHECK(s2.pop() == 1);
        CHECK(s2.empty());
    }

    SUBCASE("Промяна по копирания стек не променя оригинала") {
        s2.pop();
        s2.push(3);
        CHECK(s1.pop() == 2);
    }
}

TEST_CASE_TEMPLATE("Проверка дали промяна на присвоен стек не засяга оригинала", SomeStack, STACKS) {
    SomeStack s1;
    s1.push(1);
    s1.push(2);
    SomeStack s2;
    s2.push(3);
    s2.push(4);
    s2 = s1;

    SUBCASE("Присвоеният стек e същият като оригинала") {
        CHECK(s2.pop() == 2);
        CHECK(s2.pop() == 1);
        CHECK(s2.empty());
    }

    SUBCASE("Промяна по присвоения стек не променя оригинала") {
        s2.pop();
        s2.push(3);
        CHECK(s1.pop() == 2);
    }
}

TEST_CASE_TEMPLATE("Проверка за самоприсвояване чрез копиране", SomeStack, STACKS) {
    SomeStack s;
    s.push(1);
    s.push(2);

    s = s;

    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.empty());
}

TEST_CASE_TEMPLATE("Проверка за самоприсвояване чрез преместване", SomeStack, MOVEABLE_STACKS) {
    SomeStack s;
    s.push(1);
    s.push(2);

    s = std::move(s);

    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.empty());
}

TEST_CASE_TEMPLATE("Проверка дали преместването нa стек на мястото на друг стек e успешно", SomeStack, MOVEABLE_STACKS) {
    SomeStack dummy;
    dummy.push(1);
    dummy.push(2);

    SUBCASE("Проверка на Move constructor") {
        SomeStack s(std::move(dummy));
        CHECK(s.pop() == 2);
        CHECK(s.pop() == 1);
        CHECK(s.empty());
        CHECK_THROWS(dummy.peek());
        CHECK_THROWS(dummy.pop());
    }

    SUBCASE("Проверка на Move assignment operator") {
        SomeStack s;
        s.push(3);
        s.push(4);
        s = std::move(dummy);
        CHECK(s.pop() == 2);
        CHECK(s.pop() == 1);
        CHECK(s.empty());
        CHECK_THROWS(dummy.peek());
        CHECK_THROWS(dummy.pop());
    }
}

TEST_CASE_TEMPLATE("Включване на числата от 1 до 100 в стек ги извлича в обратен ред", SomeStack, STACKS) {
    SomeStack s;
    for (int i = 1; i <= 100; i++)
        s.push(i);
    for (int i = 100; i >= 1; i--)
        CHECK(s.pop() == i);
}