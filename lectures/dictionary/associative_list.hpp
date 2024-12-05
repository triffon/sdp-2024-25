#ifndef ASSOCIATIVE_LIST_HPP
#define ASSOCIATIVE_LIST_HPP

#include "key_value_pair.hpp"
#include "double_linked_list.hpp"

template <typename K, typename V>
class AssociativeList : public DoubleLinkedList<KeyValuePair<K, V>> {
public:
    V const& lookup(K const& key) const {
        throw std::logic_error("Function not yet implemented");
    }

    V& lookup(K const& key) {
        throw std::logic_error("Function not yet implemented");
    }

    bool add(K const& key, V const& value) {
        throw std::logic_error("Function not yet implemented");
    }

    bool remove(K const& key) {
        throw std::logic_error("Function not yet implemented");
    }

    DoubleLinkedList<K> keys() const {
        throw std::logic_error("Function not yet implemented");
    }
};

#endif // ASSOCIATIVE_LIST_HPP