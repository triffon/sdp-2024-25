#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <utility>
#include <stdexcept>

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

    operator bool() const { return valid(); }
};

template <typename T>
class LinkedList {
    LinkedListElement<T> *front, *back;

    using E = LinkedListElement<T>;
    using I = LinkedListIterator<T>;

    // O(n)
    I findPrevious(I const& it) const {
        if (!it.valid())
            return it;
        I prev = begin();
        while (prev && prev.next() != it)
            ++prev;
        return prev;
    }

    void copy(LinkedList const& list) {
        for (T const& el : list)
            insertLast(el);
    }

    void erase() {
        while (!empty())
            deleteFirst(front->data);
    }

public:
    using Iterator = I;

    LinkedList() : front(nullptr), back(nullptr) {}
    LinkedList(LinkedList const& list) : LinkedList() {
        copy(list);
    }
    LinkedList& operator=(LinkedList const& list) {
        if (this != &list) {
            erase();
            copy(list);
        }
        return *this;
    }
    ~LinkedList() {
        erase();
    }

    LinkedList(LinkedList&& list) : LinkedList() {
        append(std::move(list));
    }

    LinkedList& operator=(LinkedList&& list) {
        if (this != &list) {
            erase();
            append(std::move(list));
        }
        return *this;
    }


    bool empty() const { return front == nullptr && back == nullptr; }

    I begin() const { return I(front); }
    I last()  const { return I(back);  }
    I end()   const { return I();      }

    static T const& get(I const& it) { return it.get(); }
    static T      & get(I      & it) { return it.get(); }

    // O(1)
    bool insertFirst(T const& el) {
        return insertBefore(el, begin());
    }

    // O(1)
    bool insertLast(T const& el) {
        return insertAfter(el, last());
    }

    // O(n)
    bool insertBefore(T const& el, I const& it) {
        if (!it.valid()) {
            if (empty())
                // вмъкване на единствената възможна позиция
                return insertLast(el);
            // опит за вмъкване на елемент в непразен списък на невалидна позиция
            return false;
        }
        if (it == begin()) {
            // непразен списък, на който трябва да вмъкнем елемент в началото
            front = new E{el, front};
            return true;
        }
        return insertAfter(el, findPrevious(it));
    }

    // O(1)
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

    // O(1)
    bool deleteFirst(T& el) {
        I it = begin();
        return deleteAt(el, it);
    }

    // O(n)
    bool deleteLast(T& el) {
        I it = last();
        return deleteAt(el, it);
    }

    // O(n)
    bool deleteBefore(T& el, I const& it) {
        I prev = findPrevious(it);
        return deleteAt(el, prev);
    }

    // O(n)
    bool deleteAt    (T& el, I& it) {
        bool result = false;
        // изтриване на първия елемент в непразен списък
        if (!empty() && it == begin()) {
            el = *it;
            front = front->next;
            if (it == last())
                // изтрили сме последния елемент, нулираме back
                back = nullptr;
            delete it.ptr;
            result = true;
        } else
            result = deleteAfter(el, findPrevious(it));
        // инвалидиране на итератора
        it = I();
        return result;
    }

    // O(1)
    bool deleteAfter (T& el, I const& it) {
        if (empty() || !it.valid() || !it.next().valid())
            // не можем да изтрием от празен списък, след невалидна позиция и след края
            return false;
        E* toDelete = it.ptr->next;
        it.ptr->next = toDelete->next;
        el = toDelete->data;
        // проверка дали трябва да актуализираме последния елемент
        if (toDelete == back)
            back = it.ptr;
        delete toDelete;
        return true;
    }

    // прехвърля елементите на list в нашия списък
    // O(1) по време и по памет
    void append(LinkedList&& list) {
        if (!list.empty()) {
            (empty() ? front : back->next) = list.front;
            back = list.back;
            list.front = list.back = nullptr;
        }
    }
    
};

#endif // LINKED_LIST_HPP