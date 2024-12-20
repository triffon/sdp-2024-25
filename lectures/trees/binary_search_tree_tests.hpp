#include <fstream>
#include  "doctest.h"
#include "binary_search_tree.hpp"

TEST_CASE("Добавяне на елемнт в празно двоично дърво за търсене") {
    BinarySearchTree<int> bst;
    CHECK(bst.insert(42));
    CHECK(bst.exists(42));
    CHECK_EQ(bst.root(), 42);
}

TEST_CASE("Добавяне на числата от 1 до 10 в случаен ред в двоично дърво за търсене и намирането им") {
    BinarySearchTree<int> bst;
    for (int i : {5, 3, 8, 2, 4, 7, 9, 1, 6, 10})
        CHECK(bst.insert(i));
    std::ofstream dotFile("bst.dot");
    bst.printDOT(dotFile);
    for (int i = 1; i <= 10; i++)
        CHECK_EQ(*bst.search(i), i);
    CHECK(!bst.exists(0));
    CHECK(!bst.exists(11));

    SUBCASE("Опит за изтриване на несъществуващ елемент") {
        CHECK(!bst.remove(0));
        CHECK(!bst.remove(11));
    }

    SUBCASE("Последователно изтриване на числата в друг случаен ред") {
        for (int i : {7, 2, 5, 9, 6, 8, 4, 1, 10, 3}) {
            CHECK(bst.remove(i));
            std::ofstream dotFile("bst_after_remove_" + std::to_string(i) + ".dot");
            bst.printDOT(dotFile);
        }
        for (int i = 1; i <= 10; i++)
            CHECK(!bst.exists(i));
    }
}

TEST_CASE("Добавяне на числата от 1 до 10 в нарастващ ред в двоично дърво за търсене и намирането им") {
    BinarySearchTree<int> bst;
    for (int i = 1; i <= 10; i++)
        CHECK(bst.insert(i));
    std::ofstream dotFile("bst2.dot");
    bst.printDOT(dotFile);
    for (int i = 1; i <= 10; i++)
        CHECK_EQ(*bst.search(i), i);
    CHECK(!bst.exists(0));
    CHECK(!bst.exists(11));
}

TEST_CASE("Построяване на идеално балансирано дърво по списък от числата от 1 до 10 в случаен ред") {
    std::vector<int> elements{5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
    BinarySearchTree<int> bst(elements);
    std::ofstream dotFile("balanced_bst.dot");
    bst.printDOT(dotFile);
    for (int i = 1; i <= 10; i++)
        CHECK_EQ(*bst.search(i), i);
    CHECK(!bst.exists(0));
    CHECK(!bst.exists(11));
}