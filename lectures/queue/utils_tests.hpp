#include "doctest.h"
#include "queue_utils.hpp"

TEST_CASE("Изваждане на най-малък елемент от опашка") {
    StaticQueue<int> q;
    q.enqueue(5);
    q.enqueue(9);
    q.enqueue(2);
    q.enqueue(6);
    q.enqueue(7);
    q.enqueue(8);
    q.enqueue(3);
    q.enqueue(4);
    CHECK(QueueUtils<int, StaticQueue>::min(q) == 2);
    size_t count = 0;
    while (!q.empty()) {
        int x = q.dequeue();
        count++;
        CHECK(3 <= x);
        CHECK(x <= 9);
    }
    CHECK(count == 7);
}
