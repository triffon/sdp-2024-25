#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T>
struct LinkedListElement {
    T data;
    LinkedListElement* next;
};

template <typename T>
class LinkedList;

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

    friend class LinkedList<T>;

    /* Синтактична захар */
    bool operator==(LinkedListIterator const& it) const { return ptr == it.ptr; }
    bool operator!=(LinkedListIterator const& it) const { return !(*this == it); }

    // префиксен
    // (++it) = it2
    LinkedListIterator& operator++() {
        return *this = next();
    }

    // постфиксен
    LinkedListIterator operator++(int) {
        LinkedListIterator old = *this;
        ++(*this);
        return old;
    }

    T&       operator*()       { return get(); }
    T const& operator*() const { return get(); }
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
    I last()  const { return I(back);  }
    I end()   const { return I();      }

    static T const& get(I const& it) { return it.get(); }
    static T      & get(I      & it) { return it.get(); }

    bool insertFirst(T const& el) {
        return insertBefore(el, begin());
    }

    bool insertLast(T const& el) {
        return insertAfter(el, last());
    }

    bool insertBefore(T const& el, I const& it) {
        if (empty() && !it.valid())
            // вмъкване на единствената възможна позиция
            return insertLast(el);
        throw std::runtime_error("Не е реализирана");
    }

    bool insertAfter (T const& el, I const& it) {
        if (!it.valid()) {
            if (empty()) {
                // ок, вмъкваме на едниственото възможно място
                front = back = new E{el, nullptr};
                return true;
            }
            return false;
        }
        E* newElement = new E{el, it.ptr->next};
        it.ptr->next = newElement;
        if (it.ptr == back)
            back = newElement;
        return true;
    }

    bool deleteFirst(T& el) {
        return deleteBefore(el, begin());
    }

    bool deleteLast(T& el) {
        return deleteAfter(el, end());
    }

    bool deleteBefore(T& el, I const& it) {
        throw std::runtime_error("Не е реализирана");
    }

    bool deleteAt    (T& el, I const& it) {
        throw std::runtime_error("Не е реализирана");
    }

    bool deleteAfter (T& el, I const& it) {
        throw std::runtime_error("Не е реализирана");
    }
    
};

#endif // LINKED_LIST_HPP