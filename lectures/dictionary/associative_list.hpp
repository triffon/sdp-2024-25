#ifndef ASSOCIATIVE_LIST_HPP
#define ASSOCIATIVE_LIST_HPP

#include "key_value_pair.hpp"
#include "double_linked_list.hpp"
#include "list_high_order.hpp"

template <typename K, typename V>
class AssociativeList : DoubleLinkedList<KeyValuePair<K, V>> {
private:
    using KVP = KeyValuePair<K, V>;
    using DoubleLinkedList<KVP>::insertLast;
public:
    using typename DoubleLinkedList<KVP>::Iterator;
    using DoubleLinkedList<KVP>::begin;
    using DoubleLinkedList<KVP>::end;
    using DoubleLinkedList<KVP>::empty;

    bool contains(K const& key) const {
        for(KVP const& kvp : *this)
            if (kvp.key == key)
                return true;
        return false;
    }

    V const& lookup(K const& key) const {
        for(KVP const& kvp : *this)
            if (kvp.key == key)
                return kvp.value;
        throw std::runtime_error("Ключът не е намерен!");
    }

    V& lookup(K const& key) {
        for(KVP& kvp : *this)
            if (kvp.key == key)
                return kvp.value;
        throw std::runtime_error("Ключът не е намерен!");
    }

    bool add(K const& key, V const& value) {
        if (contains(key))
            return false;
        return insertLast(KVP{key, value});
    }

    bool remove(K const& key) {
        Iterator it = this->begin();
        while (it && (*it).key != key)
            ++it;
        if (!it)
            // ключът го няма
            return false;
        KVP tmp;
        return this->deleteAt(tmp, it);
    }

    DoubleLinkedList<K> keys() const {
        return ListHighOrderFunctions<KVP, DoubleLinkedList, K>::map
                 ([](KVP kvp) { return kvp.key; }, this->begin());
    }
};

#endif // ASSOCIATIVE_LIST_HPP