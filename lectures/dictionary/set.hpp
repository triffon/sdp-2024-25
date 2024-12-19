#ifndef __SET_HPP
#define __SET_HPP

#include "double_linked_list.hpp"

template <typename T, typename I>
class SetIterator {
    I dictIterator;

public:
    SetIterator(I _dictIterator) : dictIterator(_dictIterator) {}

    bool valid() const { return dictIterator.valid(); }

    SetIterator next() const {
        return SetIterator(dictIterator.next()); 
    }

    T const& get() const {
        // връщане на ключа
        return dictIterator.get().key;
    }

    /* Синтактична захар */
    bool operator==(SetIterator const& it) const { return dictIterator == it.dictIterator; }
    bool operator!=(SetIterator const& it) const { return !(*this == it); }

    // префиксен
    // (++it) = it2
    SetIterator& operator++() {
        return *this = next();
    }

    // постфиксен
    SetIterator operator++(int) {
        SetIterator old = *this;
        ++(*this);
        return old;
    }

    T const& operator*() const { return get(); }

    operator bool() const { return valid(); }
};


template <typename T, template <typename, typename> class Dictionary>
class Set : Dictionary<T, bool> {
    using D = Dictionary<T, bool>;
    using DictionaryIterator = typename Dictionary<T, bool>::Iterator;
public:
    using D::remove;
    using D::contains;
    using D::empty;

    using Iterator = SetIterator<T, DictionaryIterator>;

    Iterator begin() const {
        return Iterator(D::begin());
    }

    Iterator end() const {
        return Iterator(D::end());
    }

    bool insert(T const& x) {
        return D::add(x, false);
    }

    DoubleLinkedList<T> elements() {
        return D::keys();
    }
};

#endif // __SET_HPP