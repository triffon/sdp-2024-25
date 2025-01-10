#ifndef HEAP_HPP
#define HEAP_HPP

#include <exception>

template <typename T, size_t MAX = 100>
class Heap {
    T heap[MAX];
    size_t size;

    bool full() const { return size == MAX; }

    static size_t left(size_t index)   { return 2 * index + 1; }
    static size_t right(size_t index)  { return 2 * index + 2; }
    static size_t parent(size_t index) { return (index - 1) / 2; }

    size_t maxChildIndex(size_t index) {
        // ако няма дясно дете или лявото е по-голямо, тогава връщаме лявото
        // иначе връщаме дясното
        return (right(index) >= size || heap[left(index)] > heap[right(index)])
                    ? left(index) : right(index);
    }

    void siftDown(size_t index) {
        while(left(index) < size) {
            int nextIndex = maxChildIndex(index);
            std::swap(heap[index], heap[nextIndex]);
            index = nextIndex;
        }
    }


    void siftUp(size_t index) {
        while (index > 0 && heap[index] > heap[parent(index)]) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

public:
    Heap() : size(0) {}

    size_t getSize() const { return size; }

    bool empty() const { return size == 0; }

    void enqueue(T const& x) {
        if (full())
            throw std::runtime_error("Пирамидата е пълна!");

        // добавяме елемента като листо
        heap[size] = x;
        siftUp(size++);
    }

    T dequeue() {
        if (empty())
            throw std::runtime_error("Пирамидата е празна!");
        T result = heap[0];
        std::swap(heap[0], heap[--size]);
        siftDown(0);
        return result;
    }

    T head() const { return heap[0]; }
};

#endif // HEAP_HPP