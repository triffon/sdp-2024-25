#include "doctest.h"
#include "tree.hpp"

TEST_CASE("Създаване на листо") {
    Tree<int> t(42);
    CHECK(t.root() == 42);
}

TEST_CASE("Добавяне на листо като поддърво") {
    Tree<int> t(42);
    Tree<int> t1(1);
    t.addSubtree(t1);
    typename Tree<int>::SubtreeIterator it = t.subtrees();
    CHECK(it.valid());
    CHECK(it.get().root() == 1);
    CHECK((++it).valid() == false);
}

TEST_CASE("Обхождане на по-голямо дърво с дълбочина 3") {
    Tree<int> t(42);
    Tree<int> t1(1);
    Tree<int> t2(2);
    Tree<int> t3(3);
    t3.addSubtree(Tree<int>(5)).addSubtree(Tree<int>(6)).addSubtree(Tree<int>(7));
    t.addSubtree(t1).addSubtree(t2).addSubtree(t3);
    typename Tree<int>::SubtreeIterator it = t.subtrees();
    CHECK(it.valid());
    CHECK(it.get().root() == 1);
    CHECK((++it).valid());
    CHECK(it.get().root() == 2);
    CHECK((++it).valid());
    CHECK(it.get().root() == 3);
    CHECK((++it).valid() == false);
    // проверка на поддърветата на t3
    typename Tree<int>::SubtreeIterator it3 = t3.subtrees();
    CHECK(it3.valid());
    CHECK(it3.get().root() == 5);
    CHECK((++it3).valid());
    CHECK(it3.get().root() == 6);
    CHECK((++it3).valid());
    CHECK(it3.get().root() == 7);
    CHECK((++it3).valid() == false);
}