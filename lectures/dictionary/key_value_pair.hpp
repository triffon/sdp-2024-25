#ifndef KEY_VALUE_PAIR_HPP
#define KEY_VALUE_PAIR_HPP

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;

    KeyValuePair(K const& _key = K(), V const& _value = V()) : key(_key), value(_value) {}

    bool operator==(const KeyValuePair& other) const {
        return key == other.key;
    }

    bool operator!=(const KeyValuePair& other) const {
        return !(*this == other);
    }

    bool operator<(const KeyValuePair& other) const {
        return key < other.key;
    }

    bool operator<=(const KeyValuePair& other) const {
        return key <= other.key;
    }

    bool operator>(const KeyValuePair& other) const {
        return key > other.key;
    }

    bool operator>=(const KeyValuePair& other) const {
        return key >= other.key;
    }
};

#endif // KEY_VALUE_PAIR_HPP