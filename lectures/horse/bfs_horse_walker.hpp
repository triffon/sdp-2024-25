#ifndef BFS_HORSE_WALKER_HPP
#define BFS_HORSE_WALKER_HPP
#include <cmath>
#include "horse_walker.hpp"
#include "linked_queue.hpp"
#include <unordered_map>

// Custom hash function for Position pairs
struct PositionHash {
    size_t operator()(const Position& p) const {
        return std::hash<Coordinate>()(p.first) ^ (std::hash<Coordinate>()(p.second) << 1);
    }
};

// Custom equality function for Position pairs
struct PositionEqual {
    bool operator()(const Position& p1, const Position& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

class BFSHorseWalker : public HorseWalker {
private:
    using ParentMap = std::unordered_map<Position, Position, PositionHash, PositionEqual>;

public:
    BFSHorseWalker(size_t boardSize) : HorseWalker(boardSize) {}

    Walk walk(Position const& start, Position const& end) override {
        // If start and end are the same position, return just that position
        if (start == end) {
            Walk result;
            result.push_back(start);
            return result;
        }

        // Reset the board
        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[i].size(); j++) {
                board[i][j] = false;
            }
        }

        // Queue for BFS
        LinkedQueue<Position> queue;
        // Map to track the path (each position to its parent)
        ParentMap parents;
        
        // Mark start as visited and enqueue it
        board[start.first][start.second] = true;
        queue.enqueue(start);
        
        // BFS loop
        bool found = false;
        while (!queue.empty() && !found) {
            Position current = queue.dequeue();
            
            // Try all 8 possible knight moves
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    // Skip non-knight moves
                    if (i == 0 || j == 0 || std::abs(i) == std::abs(j))
                        continue;
                    
                    Position next = {current.first + i, current.second + j};
                    
                    // Check if it's a valid move
                    if (insideBoard(next) && !board[next.first][next.second]) {
                        // Mark as visited
                        board[next.first][next.second] = true;
                        // Store parent for path reconstruction
                        parents[next] = current;
                        // Add to queue
                        queue.enqueue(next);
                        
                        // Check if we reached the destination
                        if (next == end) {
                            found = true;
                            break;
                        }
                    }
                }
                if (found) break;
            }
        }
        
        // If destination was not found, return empty walk
        if (!found) {
            return Walk();
        }
        
        // Reconstruct the path from end to start, then reverse
        Walk path;
        Position current = end;
        path.push_back(current);
        
        while (current != start) {
            current = parents[current];
            path.insert(path.begin(), current);
        }
        
        return path;
    }
};

#endif // BFS_HORSE_WALKER_HPP 