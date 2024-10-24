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
    LinkedQueue() : front(nullptr), back(nullptr) { }

    // проверка дали опашката е празна
    bool empty() const { return front == nullptr; }

    // включване на елемент в опашката 
    void enqueue(T const& x) { 
        QueueElement<T> *newback = new QueueElement<T>{x, nullptr};
        if (empty())
            front = newback;
        else
            back->next = newback;
        back = newback;
    }

    // изключване на елемент от опашката
    T dequeue() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празна опашка");
        QueueElement<T>* toDelete = front;
        T result = head();
        front = front->next;
        delete toDelete;
        return result;
    }

    // първият елемент в опашката
    T const& head() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празна опашка");
        return front->data;
    }
};

#endif // LINKED_QUEUE_HPP