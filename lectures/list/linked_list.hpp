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
public:
    LinkedListIterator(LinkedListElement<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }

    LinkedListIterator next() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до следваща позиция от невалидна позиция");
        return LinkedListIterator(ptr->next);
    }

    LinkedListIterator prev() const {
        throw std::runtime_error("Достъп до предишен елемент не се поддържа");
    }

    T const& get() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до елемент на невалидна позиция");
        return ptr->data;
    }

    T& get() {
        if (!valid())
            throw std::runtime_error("Опит за достъп до елемент на невалидна позиция");
        return ptr->data;
    }
};

template <typename T>
class LinkedList {
    LinkedListElement<T> *front, *back;

    using E = LinkedListElement<T>;
    using I = LinkedListIterator<T>;

public:
    using Iterator = I;

    LinkedList() : front(nullptr), back(nullptr) {}

    bool empty() const { return front == nullptr; }

    I begin() const { return I(front); }
    I end()   const { return I(back);  }

    static T const& get(I const& pos) { return pos.get(); }
    static T      & get(I      & pos) { return pos.get(); }

    bool insertFirst(T const& el) {
        return insertBefore(el, begin());
    }

    bool insertLast(T const& el) {
        return insertAfter(el, end());
    }

    bool insertBefore(T const& el, I const& pos) {
        throw std::runtime_error("Не е реализирана");
    }

    bool insertAfter (T const& el, I const& pos) {
        throw std::runtime_error("Не е реализирана");
    }

    bool deleteFirst(T& el) {
        return deleteBefore(el, begin());
    }

    bool deleteLast(T& el) {
        return deleteAfter(el, end());
    }

    bool deleteBefore(T& el, I const& pos) {
        throw std::runtime_error("Не е реализирана");
    }

    bool deleteAt    (T& el, I const& pos) {
        throw std::runtime_error("Не е реализирана");
    }

    bool deleteAfter (T& el, I const& pos) {
        throw std::runtime_error("Не е реализирана");
    }
    
};

#endif // LINKED_LIST_HPP