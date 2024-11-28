#include "doctest.h"
#include "binary_tree.hpp"

#include <fstream>

TEST_CASE("Създаване на празно дърво") {
    BinaryTree<int> bt;
    CHECK(bt.empty());
}

TEST_CASE("Създаване на листо") {
    BinaryTree<int> bt(5);
    CHECK(!bt.empty());
    CHECK_EQ(bt.root(), 5);
    CHECK(bt.left().empty());
    CHECK(bt.right().empty());
}

TEST_CASE("Създаване на по-сложно дърво") {
    BinaryTree<int> bt(1, BinaryTree<int>(2),
                          BinaryTree<int>(3, BinaryTree<int>(4), BinaryTree<int>(5)));
    CHECK(!bt.empty());
    CHECK_EQ(bt.root(), 1);
    CHECK_EQ(bt.left().root(), 2);
    CHECK_EQ(bt.right().root(), 3);
    CHECK_EQ(bt.right().left().root(), 4);
    CHECK_EQ(bt.right().right().root(), 5);

    SUBCASE("Обхождане на дървото") {
        typename BinaryTree<int>::Position pos = bt.rootPos();
        CHECK_EQ(*pos, 1);
        CHECK_EQ(*-pos, 2);
        CHECK_EQ(*+pos, 3);
        CHECK_EQ(*-(+pos), 4);
        CHECK_EQ(*+(+pos), 5);
    }

    std::ofstream dotFile("binary_tree.dot");
    bt.printDOT(dotFile);
}

TEST_CASE("Намиране на дълбочина на празно дърво") {
    BinaryTree<int> bt;
    CHECK_EQ(bt.depth(), 0);
}

TEST_CASE("Намиране на дълбочина на непразно дърво") {
    BinaryTree<int> bt(1, BinaryTree<int>(2),
                          BinaryTree<int>(3, BinaryTree<int>(4), BinaryTree<int>(5)));
    BinaryTree<int> ubertree(10, std::move(bt), BinaryTree<int>(11));
    CHECK_EQ(bt.depth(),  0);
    CHECK_EQ(ubertree.depth(), 4);
}

