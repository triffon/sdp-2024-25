#ifndef BST_DICTIONARY_HPP
#define BST_DICTIONARY_HPP

#include "key_value_pair.hpp"
#include "binary_search_tree.hpp"
#include "double_linked_list.hpp"

template <typename K, typename V>
class BSTDictionary : BinarySearchTree<KeyValuePair<K, V>> {
private:
    using KVP = KeyValuePair<K, V>;
    using typename BinarySearchTree<KeyValuePair<K, V>>::Position;

    static void collectKeys(DoubleLinkedList<K>& keys, Position const& pos) {
        if (pos) {
            collectKeys(keys, -pos);
            keys.insertLast((*pos).key);
            collectKeys(keys, +pos);
        }
    }

    // лоша бърза реализация на begin() / end()
    DoubleLinkedList<KVP> kvps;

    void collectKVP(Position const& pos) {
        if (pos) {
            collectKVP(-pos);
            kvps.insertLast(*pos);
            collectKVP(+pos);
        }
    }

public:
    using BinaryTree<KVP>::empty;
    using Iterator = typename DoubleLinkedList<KVP>::Iterator;

    Iterator begin() {
        kvps = DoubleLinkedList<KVP>();
        collectKVP(this->rootPos());
        return kvps.begin();
    }

    Iterator end() const {
        return kvps.end();
    }


    bool contains(K const& key) const {
        return this->exists(key);
    }

    V const& lookup(K const& key) const {
        Position pos = this->search(key);
        if (!pos)
            throw std::runtime_error("Ключът не е намерен!");
        return (*pos).value;
    }

    V& lookup(K const& key) {
        Position pos = this->search(key);
        if (!pos)
            throw std::runtime_error("Ключът не е намерен!");
        return (*pos).value;
    }

    bool add(K const& key, V const& value) {
        return this->insert(KVP(key, value));
    }

    bool remove(K const& key) {
        return BinarySearchTree<KVP>::remove(key);
    }

    DoubleLinkedList<K> keys() const {
        DoubleLinkedList<K> result;
        collectKeys(result, this->rootPos());
        return result;
    }
};

#endif // BST_DICTIONARY_HPP