#ifndef HAMMING_GENERATOR_HPP
#define HAMMING_GENERATOR_HPP

#include "linked_queue.hpp"

class HammingGenerator {
    LinkedQueue<unsigned> q2, q3, q5;
    void removeIfEqual(LinkedQueue<unsigned>& q, unsigned x) {
        if (q.head() == x)
            q.dequeue();
    }
public:
    HammingGenerator() {
        q2.enqueue(1);
        q3.enqueue(1);
        q5.enqueue(1);
    }
    unsigned next() {
        unsigned minel = std::min({q2.head(), q3.head(), q5.head()});
        q2.enqueue(minel * 2);
        q3.enqueue(minel * 3);
        q5.enqueue(minel * 5);
        removeIfEqual(q2, minel);
        removeIfEqual(q3, minel);
        removeIfEqual(q5, minel);
        return minel;
    }
};

#endif // HAMMING_GENERATOR_HPP