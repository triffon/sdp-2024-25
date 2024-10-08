#include "doctest.h"
#include "stack.hpp"
#include "resizing_stack.hpp"

#define STACKS Stack<int>, ResizingStack<int>

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