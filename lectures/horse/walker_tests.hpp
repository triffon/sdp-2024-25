#include "doctest.h"
#include "recursive_horse_walker.hpp"
#include "stack_horse_walker.hpp"

#define ALL_WALKERS RecursiveHorseWalker, StackHorseWalker

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (0,2) в дъска с размер 4", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(4);
    Walk walk = walker.walk({0, 0}, {0, 2});
    CHECK(HorseWalker::isValidWalk(walk, {0, 0}, {0, 2}));
}

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (1,2) в дъска с размер 3", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(3);
    Walk walk = walker.walk({0, 0}, {1, 2});
    CHECK(HorseWalker::isValidWalk(walk, {0, 0}, {1, 2}));
}


TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (2,2) в дъска с размер 3", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(3);
    Walk walk = walker.walk({0, 0}, {2, 2});
    CHECK(HorseWalker::isValidWalk(walk, {0, 0}, {2, 2}));
}

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (2,2) в дъска с размер 4", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(4);
    Walk walk = walker.walk({0, 0}, {2, 2});
    CHECK(HorseWalker::isValidWalk(walk, {0, 0}, {2, 2}));
}

TEST_CASE_TEMPLATE("Няма ход на коня от (0,0) до (1,1) в дъска с размер 3", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(3);
    Walk walk = walker.walk({0, 0}, {1, 1});
    CHECK(walk.empty());
}

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до всяко поле в дъска с размер 4", SomeWalker, ALL_WALKERS) {
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 4; y++) {
            SomeWalker walker(4);
            // std::clog << "Търсим разходка до позиция " << Position({x, y}) << std::endl;
            Walk walk = walker.walk({0, 0}, {x, y});
            CHECK(HorseWalker::isValidWalk(walk, {0, 0}, {x, y}));
        }
}
