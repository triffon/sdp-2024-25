#ifndef __SET_HPP
#define __SET_HPP

#include "double_linked_list.hpp"

template <typename T, template <typename, typename> class Dictionary>
class Set : Dictionary<T, bool> {
    using D = Dictionary<T, bool>;
public:
    using D::remove;
    using D::contains;

    bool empty() const {
        return !D::begin();
    }

    bool insert(T const& x) {
        return D::add(x, false);
    }

    DoubleLinkedList<T> elements() {
        return D::keys();
    }
};

#endif // __SET_HPP