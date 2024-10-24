#ifndef SQUEUE_HPP
#define SQUEUE_HPP
#include <stdexcept>

template <typename T>
class StaticQueue {
public:
    StaticQueue() {}

    // проверка дали опашката е празна
    bool empty() const { throw std::runtime_error("Не е реализирано"); }

    // включване на елемент в опашката 
    void enqueue(T const& x) { throw std::runtime_error("Не е реализирано"); }

    // изключване на елемент от опашката
    T dequeue() { throw std::runtime_error("Не е реализирано"); }

    // първият елемент в опашката
    T const& head() const { throw std::runtime_error("Не е реализирано"); }
};

#endif // SQUEUE_HPP