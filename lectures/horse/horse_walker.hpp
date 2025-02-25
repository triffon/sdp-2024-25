#ifndef HORSE_WALKER_HPP
#define HORSE_WALKER_HPP
#include <vector>
#include <utility>
#include <iostream>

using Coordinate = short;
using ChessRow   = std::vector<bool>;
using Chessboard = std::vector<ChessRow>;
using Position   = std::pair<Coordinate, Coordinate>;
using Walk       = std::vector<Position>;

class HorseWalker {
protected:
    Chessboard board;

    bool insideBoard(Position const& pos) {
        return pos.first >= 0 && pos.first < board.size()
                &&
               pos.second >= 0 && pos.second < board.size();
    }
public:
    HorseWalker(Coordinate size) {
        for(Coordinate i = 0; i < size; i++)
            board.push_back(ChessRow(size));
    }
    virtual Walk walk(Position const& start, Position const& end) = 0;
    
    virtual Walk walkAvoidingPositions(Position const& start, Position const& end, const std::vector<Position>& forbidden) = 0;

    static bool isValidStep(Position const& from, Position const& to) {
        return std::abs((from.first - to.first) * (from.second - to.second)) == 2;
    }

    static bool isValidWalk(Walk const& walk, Position const& start, Position const& end) {
        if (walk.empty() || walk.front() != start || walk.back() != end)
            return false;
        for(int i = 0; i + 1 < walk.size(); i++)
            if (!isValidStep(walk[i], walk[i+1]))
                return false;
        return true;
    }
    
    static bool isValidWalk(const Walk& walk, Position const& start, Position const& end, 
                          const std::vector<Position>& forbidden, size_t boardSize) {
        if (walk.empty()) {
            return false;
        }
        
        if (walk.front() != start || walk.back() != end) {
            return false;
        }
        
        for (size_t i = 1; i < walk.size(); i++) {
            if (!isValidStep(walk[i-1], walk[i])) {
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
};

std::ostream& operator<<(std::ostream& os, Position const& pos) {
    return os << '(' << pos.first << ',' << pos.second << ')';
}

std::ostream& operator<<(std::ostream& os, Walk const& walk) {
    for(Position pos : walk)
      os << pos << ' ';
    return os << std::endl;
}


#endif // HORSE_WALKER_HPP