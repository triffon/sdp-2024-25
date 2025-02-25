#ifndef WARNSDORFF_HORSE_WALKER_HPP
#define WARNSDORFF_HORSE_WALKER_HPP
#include "horse_walker.hpp"
#include <algorithm>

class WarnsdorffHorseWalker : public HorseWalker {
private:
    // Possible knight moves
    const std::vector<std::pair<int, int>> moves = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    // Count available next moves from a position
    int countAccessibleNeighbors(Position const& pos) {
        int count = 0;
        for (const auto& move : moves) {
            Position next = {pos.first + move.first, pos.second + move.second};
            if (insideBoard(next) && !board[next.first][next.second]) {
                count++;
            }
        }
        return count;
    }
    
    bool warnsdorffHelper(Position const& current, Position const& end, Walk& path, int depth) {
        // Add current position to path
        path.push_back(current);
        board[current.first][current.second] = true;
        
        // Check if we've reached the end
        if (current == end) {
            return true;
        }
        
        // Get all possible moves
        std::vector<std::pair<Position, int>> nextMoves;
        for (const auto& move : moves) {
            Position next = {current.first + move.first, current.second + move.second};
            if (insideBoard(next) && !board[next.first][next.second]) {
                // Count accessible neighbors for this move (Warnsdorff's heuristic)
                int accessibleCount = countAccessibleNeighbors(next);
                nextMoves.push_back({next, accessibleCount});
            }
        }
        
        // Sort by number of accessible neighbors (ascending)
        std::sort(nextMoves.begin(), nextMoves.end(), 
                 [](const auto& a, const auto& b) { return a.second < b.second; });
        
        // Try moves in order of fewest accessible neighbors first
        for (const auto& nextMove : nextMoves) {
            if (warnsdorffHelper(nextMove.first, end, path, depth + 1)) {
                return true;
            }
        }
        
        // Backtrack
        path.pop_back();
        board[current.first][current.second] = false;
        return false;
    }
    
public:
    WarnsdorffHorseWalker(Coordinate size) : HorseWalker(size) {}
    
    Walk walk(Position const& start, Position const& end) override {
        // Reset the board
        for (size_t i = 0; i < board.size(); ++i)
            for (size_t j = 0; j < board[i].size(); ++j)
                board[i][j] = false;
        
        Walk path;
        if (warnsdorffHelper(start, end, path, 0)) {
            return path;
        }
        return Walk(); // No path found
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
        
        // Start position can't be forbidden
        if (std::find(forbidden.begin(), forbidden.end(), start) != forbidden.end()) {
            return Walk();
        }
        
        // End position can't be forbidden (unless it's the starting position)
        if (start != end && std::find(forbidden.begin(), forbidden.end(), end) != forbidden.end()) {
            return Walk();
        }
        
        // Reset forbidden start/end positions (we'll handle them separately)
        if (insideBoard(start)) board[start.first][start.second] = false;
        if (insideBoard(end)) board[end.first][end.second] = false;
        
        Walk path;
        if (warnsdorffHelper(start, end, path, 0)) {
            return path;
        }
        return Walk(); // No path found
    }
};

#endif // WARNSDORFF_HORSE_WALKER_HPP 