#ifndef __HASH_TABLE_HPP
#define __HASH_TABLE_HPP

#include <iostream>
#include "key_value_pair.hpp"
#include "double_linked_list.hpp"

template <typename K>
using HashFunction = size_t (*)(K const&);

template <typename K>
size_t id(K const& x) { return x; }

template <typename K, typename V>
class HashTableIterator {
    using KVP = KeyValuePair<K, V>;
    using Bucket = DoubleLinkedList<KVP>;
    using BI = typename Bucket::Iterator;
    Bucket const* currentBucket;
    Bucket const* end;
    BI bucketIterator;
public:
    HashTableIterator() : currentBucket(nullptr), end(nullptr) {}
    HashTableIterator(Bucket const& bucket, Bucket const* _end) : currentBucket(&bucket),
                                                    end(_end) {
        findNextValidBucket();
        if (currentBucket != end)
            bucketIterator = currentBucket->begin();
    }

    bool valid() const { return currentBucket != nullptr && 
                                currentBucket != end &&
                                bucketIterator.valid(); }

    void findNextValidBucket() {
        while (currentBucket != end && currentBucket->empty())
            currentBucket++;
    }

    HashTableIterator next() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до следваща позиция от невалидна позиция");
        HashTableIterator nextit = *this;
        // опит за преминаване на следващия елемент в кофата
        ++(nextit.bucketIterator);
        if (!nextit.bucketIterator.valid()) {
            ++nextit.currentBucket;
            nextit.findNextValidBucket();
            if (nextit.currentBucket != nextit.end)
                nextit.bucketIterator = nextit.currentBucket->begin();
        }
        return nextit;
    }

    KVP const& get() const {
        if (!valid())
            throw std::runtime_error("Опит за достъп до елемент на невалидна позиция");
        return bucketIterator.get();
    }

    KVP& get() {
        if (!valid())
            throw std::runtime_error("Опит за достъп до елемент на невалидна позиция");
        return bucketIterator.get();
    }

    /* Синтактична захар */
    bool operator==(HashTableIterator const& it) const {
        return !valid() && !it.valid() ||
                valid() && it.valid() && bucketIterator == it.bucketIterator;
    }
    bool operator!=(HashTableIterator const& it) const { return !(*this == it); }

    // префиксен
    // (++it) = it2
    HashTableIterator& operator++() {
        return *this = next();
    }

    // постфиксен
    HashTableIterator operator++(int) {
        HashTableIterator old = *this;
        ++(*this);
        return old;
    }

    KVP&       operator*()       { return get(); }
    KVP const& operator*() const { return get(); }

    operator bool() const { return valid(); }
};

template <typename K, typename V, HashFunction<K> hashFunction = id>
class HashTable {
private:
    using KVP = KeyValuePair<K, V>;
    using Bucket = DoubleLinkedList<KVP>;
    using BI = typename Bucket::Iterator;
    static const size_t DEFAULT_CAPACITY = 100;

    void copy(HashTable const& ht) {
        collisions = ht.collisions;
        buckets = ht.buckets;
        capacity = ht.capacity;
        table = new Bucket[capacity];
        for (size_t i = 0; i < capacity; i++)
            table[i] = ht.table[i];
    }

    Bucket* table;
    size_t capacity;
    size_t collisions;
    size_t buckets;

    Bucket&        findBucket(K const& key) {
        return table[hashFunction(key) % capacity];
    }

    Bucket const & findBucket(K const& key) const {
        return table[hashFunction(key) % capacity];
    }

    static BI findInBucket(Bucket const& bucket, K const& key) {
        BI it = bucket.begin();
        while (it && (*it).key != key)
            ++it;
        return it;
    }


    static BI findInBucket(Bucket& bucket, K const& key) {
        BI it = bucket.begin();
        while (it && (*it).key != key)
            ++it;
        return it;
    }

public:
    using Iterator = HashTableIterator<K, V>;


    HashTable(size_t _capacity = DEFAULT_CAPACITY) : capacity(_capacity), collisions(0), buckets(0) {
        table = new Bucket[capacity];
    }

    HashTable(HashTable const& ht) {
        copy(ht);
    }

    HashTable& operator=(HashTable const& ht) {
        if (this != &ht) {
            delete[] table;
            copy(ht);
        }
        return *this;
    }

    ~HashTable() {
        delete[] table;
    }

    bool contains(K const& key) const {
        Bucket const& bucket = findBucket(key);
        return findInBucket(bucket, key).valid();
    }

    V const& lookup(K const& key) const {
        Bucket const& bucket = findBucket(key);
        BI it = findInBucket(bucket, key);
        if (it)
            return (*it).value;
        throw std::runtime_error("Ключът не е намерен!");
    }

    V& lookup(K const& key) {
        Bucket& bucket = findBucket(key);
        BI it = findInBucket(bucket, key);
        if (it)
            return (*it).value;
        throw std::runtime_error("Ключът не е намерен!");
    }

    bool add(K const& key, V const& value) {
        Bucket& bucket = findBucket(key);
        BI it = findInBucket(bucket, key);
        if (it)
            return false;
        if (!bucket.empty())
            collisions++;
        else
            buckets++;
        bucket.insertLast(KVP{key, value});
        return true;
    }

    bool remove(K const& key) {
        Bucket& bucket = findBucket(key);
        BI it = findInBucket(bucket, key);
        KVP tmp;
        if (it) {
            bucket.deleteAt(tmp, it);
            if (!bucket.empty())
                collisions--;
            else
                buckets--;
            return true;
        }
        return false;
    }

    DoubleLinkedList<K> keys() const {
        DoubleLinkedList<K> result;
        for(int i = 0; i < capacity; i++)
            for(KVP const& kvp : table[i])
                result.insertLast(kvp.key);
        return result;
    }

    void printStatistics(std::ostream& os = std::clog) {
        std::clog << "Колизии: " << collisions << std::endl;
        std::clog << "Кофи: " << buckets << std::endl;
    }

    Iterator begin() const {
        return Iterator(table[0], table + capacity);
    }

    Iterator end() const {
        return Iterator(table[capacity], table + capacity);
    }

    bool empty() const { return buckets == 0; }
};

#endif // __HASH_TABLE_HPP