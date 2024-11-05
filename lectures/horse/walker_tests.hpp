#include "doctest.h"
#include "recursive_horse_walker.hpp"

#define ALL_WALKERS RecursiveHorseWalker

bool isValidStep(Position const& from, Position const& to) {
    return std::abs((from.first - to.first) * (from.second - to.second)) == 2;
}

bool isValidWalk(Walk const& walk) {
    for(int i = 0; i < walk.size() - 1; i++)
        if (!isValidStep(walk[i], walk[i+1]))
            return false;
    return true;
}

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (2,2) в дъска с размер 3", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(3);
    Walk walk = walker.walk({0, 0}, {2, 2});
    CHECK(isValidWalk(walk));
}

TEST_CASE_TEMPLATE("Ход на коня от (0,0) до (2,2) в дъска с размер 4", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(4);
    Walk walk = walker.walk({0, 0}, {2, 2});
    CHECK(isValidWalk(walk));
}

TEST_CASE_TEMPLATE("Няма ход на коня от (0,0) до (1,1) в дъска с размер 3", SomeWalker, ALL_WALKERS) {
    SomeWalker walker(3);
    Walk walk = walker.walk({0, 0}, {1, 1});
    CHECK(walk.empty());
}

