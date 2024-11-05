#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T>
struct LinkedListElement {
    T data;
    LinkedListElement* next;
};

template <typename T>
class LinkedListIterator {
    LinkedListElement<T>* ptr;
};

template <typename T>
class LinkedList {
    LinkedListElement<T> *front, *back;

public:
    LinkedList() : front(nullptr), back(nullptr) {}

    bool empty() const { return front == nullptr; }
};

#endif // LINKED_LIST_HPP