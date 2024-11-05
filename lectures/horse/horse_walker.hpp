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