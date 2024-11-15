#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP
#include <utility>
#include <stdexcept>

template <typename T>
struct DoubleLinkedListElement {
    T data;
    DoubleLinkedListElement *next, *prev;
};

template <typename T>
class DoubleLinkedList;

template <typename T>
class DoubleLinkedListIterator {
    DoubleLinkedListElement<T>* ptr;
public:
    DoubleLinkedListIterator(DoubleLinkedListElement<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }

    DoubleLinkedListIterator next() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до следваща позиция от невалидна позиция");
        return DoubleLinkedListIterator(ptr->next);
    }

    DoubleLinkedListIterator prev() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до следваща позиция от невалидна позиция");
        return DoubleLinkedListIterator(ptr->prev);
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

    friend class DoubleLinkedList<T>;

    /* Синтактична захар */
    bool operator==(DoubleLinkedListIterator const& it) const { return ptr == it.ptr; }
    bool operator!=(DoubleLinkedListIterator const& it) const { return !(*this == it); }

    // префиксен
    // (++it) = it2
    DoubleLinkedListIterator& operator++() {
        return *this = next();
    }

    // постфиксен
    DoubleLinkedListIterator operator++(int) {
        DoubleLinkedListIterator old = *this;
        ++(*this);
        return old;
    }

    // префиксен
    // (--it) = it2
    DoubleLinkedListIterator& operator--() {
        return *this = prev();
    }

    // постфиксен
    DoubleLinkedListIterator operator--(int) {
        DoubleLinkedListIterator old = *this;
        --(*this);
        return old;
    }


    T&       operator*()       { return get(); }
    T const& operator*() const { return get(); }

    operator bool() const { return valid(); }
};

template <typename T>
class DoubleLinkedList {
    DoubleLinkedListElement<T> *front, *back;

    using E = DoubleLinkedListElement<T>;
    using I = DoubleLinkedListIterator<T>;

    void copy(DoubleLinkedList const& list) {
        for (T const& el : list)
            insertLast(el);
    }

    void erase() {
        while (!empty())
            deleteFirst(front->data);
    }

public:
    using Iterator = I;

    DoubleLinkedList() : front(nullptr), back(nullptr) {}
    DoubleLinkedList(DoubleLinkedList const& list) : DoubleLinkedList() {
        copy(list);
    }
    DoubleLinkedList& operator=(DoubleLinkedList const& list) {
        if (this != &list) {
            erase();
            copy(list);
        }
        return *this;
    }
    ~DoubleLinkedList() {
        erase();
    }

    DoubleLinkedList(DoubleLinkedList&& list) : DoubleLinkedList() {
        append(std::move(list));
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& list) {
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

    // O(1)
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
            front = new E{el, front, nullptr};
            front->next->prev = front;
            return true;
        }
        return insertAfter(el, it.prev());
    }

    // O(1)
    bool insertAfter (T const& el, I const& it) {
        if (!it.valid()) {
            if (empty()) {
                // ок, вмъкваме на едниственото възможно място
                front = back = new E{el, nullptr, nullptr};
                return true;
            }
            return false;
        }
        E* newElement = new E{el, it.ptr->next, it.ptr};
        if (it.ptr == back)
            back = newElement;
        else
            newElement->next->prev = newElement;
        newElement->prev->next = newElement;
        return true;
    }

    // O(1)
    bool deleteFirst(T& el) {
        I it = begin();
        return deleteAt(el, it);
    }

    // O(1)
    bool deleteLast(T& el) {
        I it = last();
        return deleteAt(el, it);
    }

    // O(1)
    bool deleteBefore(T& el, I const& it) {
        if (!it.valid())
            return false;
        I prev = it.prev();
        return deleteAt(el, prev);
    }

    // O(1)
    bool deleteAt    (T& el, I& it) {
        if (empty() || !it)
            return false;
        /*
        if (front == it.ptr)
            front = it.ptr->next;
        else
            it.ptr->prev->next = it.ptr->next;
        if (back == itr.ptr)
            back = it.ptr->prev;
        else
            it.ptr->next->prev = it.ptr->prev;
        */
        ((it == begin()) ? front : it.ptr->prev)->next = it.ptr->next;
        ((it == last() ) ? back  : it.ptr->next)->prev = it.ptr->prev;
        el = it.ptr->data;
        if (it == begin())
            front = front->next;
        if (it == last())
            back = back->prev;
        delete it.ptr;
        it = I();
        // изтрили сме последния елемент на списъка
        return true;
    }

    // O(1)
    bool deleteAfter (T& el, I const& it) {
        if (!it.valid())
            return false;
        I next = it.next();
        return deleteAt(el, next);
    }

    // прехвърля елементите на list в нашия списък
    // O(1) по време и по памет
    void append(DoubleLinkedList&& list) {
        if (!list.empty()) {
            (empty() ? front : back ->next) = list.front;
            list.front->prev = back;
            back = list.back;
            list.front = list.back = nullptr;
        }
    }
    
    bool isPalindrome() const {
        if (empty())
            return true;
        I it1 = begin(), it2 = last();
        while (it1 != it2 && it1.prev() != it2 && *it1 == *it2) {
            ++it1;
            --it2;
        }
        // *it1 != *it2 --- лош случай
        // it1 == it2 -- добър случай, нечетна дължина
        // it1.prev() = it2 -- добър случай, четна дължина
        return *it1 == *it2;
    }
};

#endif // DOUBLE_LINKED_LIST_HPP