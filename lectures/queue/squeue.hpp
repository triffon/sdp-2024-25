#ifndef SQUEUE_HPP
#define SQUEUE_HPP
#include <stdexcept>

template <typename T>
class StaticQueue {
public:
    // капацитет на опашката
    static const size_t MAX = 100;
private:
    // данните на опашката
    T data[MAX];
    // начало и край на опашката
    int front, back;
public:

    StaticQueue() : front(0), back(-1) {}

    // проверка дали опашката е празна
    bool empty() const {
        return (back + 1) % MAX == front;
    }

    // проверка дали опашката е (почти) пълна
    bool full() const {
        return (back + 2) % MAX == front;
    }

    // включване на елемент в опашката 
    void enqueue(T const& x) {
        if (full())
            throw std::runtime_error("Опит за включване в пълна опашка");
        data[++back %= MAX] = x;
    }

    // изключване на елемент от опашката
    T dequeue() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празна опашка");
        T const& result = data[front];
        ++front %= MAX;
        return result;
    }

    // първият елемент в опашката
    T const& head() const {
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празна опашка");
        return data[front];
    }
};

#endif // SQUEUE_HPP