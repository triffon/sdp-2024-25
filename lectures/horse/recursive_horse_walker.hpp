#ifndef RECURSIVE_HORSE_WALKER_HPP
#define RECURSIVE_HORSE_WALKER_HPP
#include <cmath>
#include "horse_walker.hpp"

class RecursiveHorseWalker : public HorseWalker {
private:
    Walk currentWalk;

    bool walkHelper(Position const& start, Position const& end) {
        // лоша база
        if (!insideBoard(start) || board[start.first][start.second])
            return false;

        // стъпка напред
        board[start.first][start.second] = true;
        currentWalk.push_back(start);

        // добра база
        if (start == end)
            return true;

        // опит за всички възможни ходове на коня
        for (int i = -2; i <= 2; i++)
            for (int j = -2; j <= 2; j++)
                if (i && j && std::abs(i) != std::abs(j)) {
                    Position next = {start.first + i, start.second + j};
                    if (walkHelper(next, end))
                        return true;
                }

        // стъпка назад
        currentWalk.pop_back();
        return false;
    }
public:
    RecursiveHorseWalker(size_t boardSize) : HorseWalker(boardSize) {}

    Walk walk(Position const& start, Position const& end) {
        if (walkHelper(start, end))
            return currentWalk;
        return Walk();
    }
};

#endif // RECURSIVE_HORSE_WALKER_HPP