#include "doctest.h"
#include "squeue.hpp"
#include "linked_queue.hpp"

#define QUEUES StaticQueue<int>, LinkedQueue<int>

TEST_CASE_TEMPLATE("Създаване на празна опашка", Queue, QUEUES) {
    Queue q;
    CHECK(q.empty());
}

TEST_CASE_TEMPLATE("При добавяне на елемнт в опашката, тя не е празна", Queue, QUEUES) {
    Queue q;
    q.enqueue(1);
    CHECK(!q.empty());
}

TEST_CASE_TEMPLATE("Опит за изключване на елемент от празна опашка", Queue, QUEUES) {
    Queue q;
    CHECK_THROWS(q.dequeue());
}

TEST_CASE_TEMPLATE("Опит за поглеждане на елемент в празна опашка", Queue, QUEUES) {
    Queue q;
    CHECK_THROWS(q.head());
}

TEST_CASE_TEMPLATE("При добавяне на елемнт в опашката, той е първи", Queue, QUEUES) {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.head() == 1);
}

TEST_CASE_TEMPLATE("При добавяне на елементи в опашката, те излизат в същия ред", Queue, QUEUES) {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
}

TEST_CASE_TEMPLATE("Многократно включване и изключване на елемент в опашка", Queue, QUEUES) {
    Queue q;
    for(int i = 0; i < 1000; i++) {
        q.enqueue(i);
        CHECK(q.dequeue() == i);
    }
    CHECK(q.empty());
}

TEST_CASE("Добавяне на MAX - 1 елемента води до изключение за пълна опашка") {
    StaticQueue<int> q;
    for(int i = 0; i < StaticQueue<int>::MAX - 1; i++) {
        q.enqueue(i);
    }
    CHECK_THROWS(q.enqueue(0));
}
