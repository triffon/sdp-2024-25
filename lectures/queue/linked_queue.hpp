#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

template <typename T>
struct QueueElement {
    T data;
    QueueElement* next;
};

template <typename T>
class LinkedQueue {
private:
    QueueElement<T> *front, *back;
public:
    LinkedQueue() { throw std::runtime_error("Не е реализирано"); }

    // проверка дали опашката е празна
    bool empty() const { throw std::runtime_error("Не е реализирано"); }

    // включване на елемент в опашката 
    void enqueue(T const& x) { throw std::runtime_error("Не е реализирано"); }

    // изключване на елемент от опашката
    T dequeue() { throw std::runtime_error("Не е реализирано"); }

    // първият елемент в опашката
    T const& head() const { throw std::runtime_error("Не е реализирано"); }
};

#endif // LINKED_QUEUE_HPP