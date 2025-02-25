#ifndef RECURSIVE_HORSE_WALKER_HPP
#define RECURSIVE_HORSE_WALKER_HPP
#include <cmath>
#include "horse_walker.hpp"

class RecursiveHorseWalker : public HorseWalker {
public:
    RecursiveHorseWalker(size_t boardSize) : HorseWalker(boardSize) {}

    Walk walk(Position const& start, Position const& end) override {
        // Reset the board
        for (size_t i = 0; i < board.size(); ++i)
            for (size_t j = 0; j < board[i].size(); ++j)
                board[i][j] = false;

        Walk currentPath;
        currentPath.push_back(start);
        board[start.first][start.second] = true;

        if (findPath(start, end, currentPath))
            return currentPath;
        return Walk();
    }

    Walk walkAvoidingPositions(Position const& start, Position const& end,
                              const std::vector<Position>& forbidden) override {
        // Reset the board
        for (size_t i = 0; i < board.size(); ++i)
            for (size_t j = 0; j < board[i].size(); ++j)
                board[i][j] = false;
                
        // Mark forbidden positions
        for (const auto& pos : forbidden) {
            if (insideBoard(pos)) {
                board[pos.first][pos.second] = true;
            }
        }
        
        // Check if start or end is forbidden
        if (std::find(forbidden.begin(), forbidden.end(), start) != forbidden.end() ||
            std::find(forbidden.begin(), forbidden.end(), end) != forbidden.end()) {
            return Walk();
        }
        
        Walk currentPath;
        currentPath.push_back(start);
        board[start.first][start.second] = true;

        if (findPath(start, end, currentPath))
            return currentPath;
        return Walk();
    }

private:
    bool findPath(Position const& current, Position const& end, Walk& path) {
        if (current == end)
            return true;

        // Try all possible knight moves
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                if (i != 0 && j != 0 && std::abs(i) != std::abs(j)) {
                    Position next = {current.first + i, current.second + j};
                    if (insideBoard(next) && !board[next.first][next.second]) {
                        board[next.first][next.second] = true;
                        path.push_back(next);
                        
                        if (findPath(next, end, path))
                            return true;
                            
                        path.pop_back();
                        board[next.first][next.second] = false;
                    }
                }
            }
        }
        return false;
    }
};

#endif // RECURSIVE_HORSE_WALKER_HPP