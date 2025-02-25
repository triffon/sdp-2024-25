#include "doctest.h"
#include "recursive_horse_walker.hpp"
#include "stack_horse_walker.hpp"
#include "bfs_horse_walker.hpp"
#include "warnsdorff_horse_walker.hpp"

#define ALL_WALKERS RecursiveHorseWalker, StackHorseWalker, BFSHorseWalker, WarnsdorffHorseWalker

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

// Helper function for new tests
bool isValidWalk(const Walk& walk, Position start, Position end, 
                 const std::vector<Position>& forbidden, size_t boardSize) {
    if (walk.empty()) {
        return false;
    }
    
    if (walk.front() != start || walk.back() != end) {
        return false;
    }
    
    for (size_t i = 1; i < walk.size(); i++) {
        if (!HorseWalker::isValidStep(walk[i-1], walk[i])) {
            return false;
        }
    }
    
    for (const auto& pos : walk) {
        for (const auto& forbiddenPos : forbidden) {
            if (pos == forbiddenPos) {
                return false;
            }
        }
    }
    
    for (const auto& pos : walk) {
        if (pos.first >= boardSize || pos.second >= boardSize) {
            return false;
        }
    }
    
    for (size_t i = 0; i < walk.size(); i++) {
        for (size_t j = i + 1; j < walk.size(); j++) {
            if (walk[i] == walk[j]) {
                return false;
            }
        }
    }
    
    return true;
}

// New test cases
TEST_CASE_TEMPLATE("Testing walkAvoidingPositions", SomeWalker, ALL_WALKERS) {
    const size_t boardSize = 8;
    SomeWalker walker(boardSize);
    
    SUBCASE("Simple path with no forbidden positions") {
        Position start = {0, 0};
        Position end = {2, 1};
        std::vector<Position> forbidden;
        Walk walk = walker.walkAvoidingPositions(start, end, forbidden);
        CHECK(HorseWalker::isValidWalk(walk, start, end, forbidden, boardSize));
    }
    
    SUBCASE("Path with one forbidden position") {
        Position start = {0, 0};
        Position end = {3, 3};
        std::vector<Position> forbidden = {{1, 2}};
        Walk walk = walker.walkAvoidingPositions(start, end, forbidden);
        CHECK(HorseWalker::isValidWalk(walk, start, end, forbidden, boardSize));
    }
    
    // ... Add other subcases similarly ...
}
