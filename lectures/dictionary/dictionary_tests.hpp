#include "doctest.h"
#include <string>
#include "associative_list.hpp"
#include "bst_dictionary.hpp"
#include "hash_table.hpp"

size_t basicHashFunction(std::string const& s) {
    return s.length();
}

size_t betterHashFunction(std::string const& s) {
    return s[0];
}

size_t sumHashFunction(std::string const& s) {
    size_t result = 0;
    for(char c : s)
        result += c;
    return result;
}

size_t betterSumHashFunction(std::string const& s) {
    size_t result = 0;
    for(int i = 0; i < s.size(); i++) {
        (result *= 17) += s[i];
    }
    return result;
}


//using TestHashTable = HashTable<std::string, int, basicHashFunction>;
//using TestHashTable = HashTable<std::string, int, betterHashFunction>;
//using TestHashTable = HashTable<std::string, int, sumHashFunction>;
using TestHashTable = HashTable<std::string, int, betterSumHashFunction>;


#define DICTIONARIES AssociativeList<std::string, int>, \
                     BSTDictionary<std::string, int>, \
                     TestHashTable

TEST_CASE_TEMPLATE("Добавяне на един елемент в речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add("forty-two", 42));
    CHECK_EQ(dict.lookup("forty-two"), 42);

    SUBCASE("Опит за добавяне на втори ключ със същата стойност") {
        CHECK(!dict.add("forty-two", 42));
        CHECK_EQ(dict.lookup("forty-two"), 42);
    }
}

TEST_CASE_TEMPLATE("Добавяне на няколко елемента в речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add("forty-two", 42));
    CHECK(dict.add("one", 1));
    CHECK(dict.add("hundred", 100));
    CHECK_EQ(dict.lookup("forty-two"), 42);
    CHECK_EQ(dict.lookup("one"), 1);
    CHECK_EQ(dict.lookup("hundred"), 100);

    SUBCASE("Намиране на всички ключове") {
        size_t count = 0;
        for (const std::string& key : dict.keys()) {
            CHECK((key == "one" || key == "forty-two" || key == "hundred"));
            count++;
        }
        CHECK_EQ(count, 3);
    }
}

TEST_CASE_TEMPLATE("Изтриване на елемент от речник", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    CHECK(dict.add("forty-two", 42));
    CHECK(dict.add("one", 1));
    CHECK(dict.add("hundred", 100));
    CHECK(dict.contains("one"));
    CHECK(dict.remove("one"));
    CHECK(!dict.contains("one"));
    CHECK(!dict.remove("one"));
    CHECK_EQ(dict.lookup("forty-two"), 42);
    CHECK_EQ(dict.lookup("hundred"), 100);
}

TEST_CASE_TEMPLATE("Добавяне на всички числа от 1 до 100 в речник и изтриването им след това", SomeDictionary, DICTIONARIES) {
    SomeDictionary dict;
    for (int i = 1; i <= 100; i++)
        CHECK(dict.add(std::to_string(i), i));
    for (int i = 100; i >= 1; i--)
        CHECK_EQ(dict.lookup(std::to_string(i)), i);
    int count = 0;
    for(KeyValuePair<std::string, int> const& kvp : dict) {
        CHECK_EQ(kvp.key, std::to_string(kvp.value));
        count++;
    }
    CHECK_EQ(count, 100);
    for (int i = 1; i <= 100; i++)
        CHECK(dict.remove(std::to_string(i)));
    for (int i = 1; i <= 100; i++)
        CHECK(!dict.remove(std::to_string(i)));
}

TEST_CASE("Добавяне на всички числа от 1 до 100 в хеш таблица и изтриването им след това") {
    TestHashTable dict;
    for (int i = 1; i <= 100; i++)
        CHECK(dict.add(std::to_string(i), i));
    for (int i = 100; i >= 1; i--)
        CHECK_EQ(dict.lookup(std::to_string(i)), i);
    dict.printStatistics();
    for (int i = 1; i <= 100; i++)
        CHECK(dict.remove(std::to_string(i)));
    for (int i = 1; i <= 100; i++)
        CHECK(!dict.remove(std::to_string(i)));
}