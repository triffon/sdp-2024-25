#include "doctest.h"
#include "stack.hpp"

#define STACKS Stack<int>

TEST_CASE_TEMPLATE("A stack created by default is empty", SomeStack, STACKS) {
    SomeStack s;
    CHECK(s.empty());
}

TEST_CASE_TEMPLATE("After pushing an element on a stack it is no longer empty", SomeStack, STACKS) {
    SomeStack s;
    s.push(42);
    CHECK(!s.empty());
}

TEST_CASE_TEMPLATE("Attempt to pop from an empty stack throws an exception", SomeStack, STACKS) {
    SomeStack s;
    CHECK_THROWS(s.pop());
}

TEST_CASE_TEMPLATE("Attempt to peek from an empty stack throws an exception", SomeStack, STACKS) {
    SomeStack s;
    CHECK_THROWS(s.peek());
}

TEST_CASE_TEMPLATE("An pushed element can be popped from the stack", SomeStack, STACKS) {
    SomeStack s;
    s.push(42);
    CHECK(s.pop() == 42);
}

TEST_CASE_TEMPLATE("Several elements pushed on the stack are removed in reverse order", SomeStack, STACKS) {
    SomeStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
}

TEST_CASE("An exception is thrown if trying to push an element on a full stack") {
    Stack<int> s;
    for (int i = 0; i < Stack<int>::MAX; i++)
        s.push(i);
    CHECK_THROWS(s.push(42));
}