#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP
#include <stdexcept>

template <typename T>
struct QueueElement {
    T data;
    QueueElement* next;
};

template <typename T>
class LinkedQueue {
private:
    QueueElement<T> *front, *back;

    void copy(LinkedQueue const& lq) {
        QueueElement<T>* toCopy = lq.front;
        while (toCopy != nullptr) {
            enqueue(toCopy->data);
            toCopy = toCopy->next;
        }
    }

    void erase() {
        while(!empty())
            dequeue();
    }

    void move(LinkedQueue && other){
        this->front = other.front;
         other.front=nullptr;
        this->back = other.back;
        other.back=nullptr;
    }
public:
    LinkedQueue() : front(nullptr), back(nullptr) { }
    LinkedQueue(LinkedQueue const& lq) : LinkedQueue() {
        copy(lq);
    }
    LinkedQueue& operator=(LinkedQueue const& lq) {
        if (this != &lq) {
            erase();
            copy(lq);
        }
        return *this;
    }
    LinkedQueue(LinkedQueue && other) noexcept{
        move(std::move(other));
    }
    LinkedQueue& operator=(LinkedQueue && other) noexcept{
        if(this!=&other){
            erase();
            move(std::move(other));
        }
        return *this;
    }
    ~LinkedQueue() {
        erase();
    }

    // проверка дали опашката е празна
    bool empty() const { return front == nullptr && back == nullptr; }

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
        // добра практика, макар и незадължително в случая, е да нулираме back
        if (front == nullptr)
            back = nullptr;
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
