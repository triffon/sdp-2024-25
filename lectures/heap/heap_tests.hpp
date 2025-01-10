#include "doctest.h"

#include "heap.hpp"

TEST_CASE("Създаване на празна пирамида") {
    Heap<int> h;
    CHECK(h.empty());
    CHECK_EQ(h.getSize(), 0);
}

TEST_CASE("Пирамида след добавяне на един елемент е непразна") {
    Heap<int> h;
    h.enqueue(1);
    CHECK(!h.empty());
    CHECK_EQ(h.getSize(), 1);
}

TEST_CASE("Извличане на единствения елемент в пирамида") {
    Heap<int> h;
    h.enqueue(1);
    CHECK_EQ(h.dequeue(), 1);
    CHECK(h.empty());
    CHECK_EQ(h.getSize(), 0);
}

TEST_CASE("След добавяне на числата от 1 до 10 в някакъв несортиран ред, те излизат сортирани низходящо") {
    Heap<int> h;
    h.enqueue(5);
    h.enqueue(3);
    h.enqueue(8);
    h.enqueue(2);
    h.enqueue(6);
    h.enqueue(10);
    h.enqueue(1);
    h.enqueue(4);
    h.enqueue(7);
    h.enqueue(9);
    for(int i = 10; i >= 1; i--)
        CHECK_EQ(h.dequeue(), i);
}