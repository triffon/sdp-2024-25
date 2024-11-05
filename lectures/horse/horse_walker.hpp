#ifndef HORSE_WALKER_HPP
#define HORSE_WALKER_HPP
#include <vector>
#include <utility>

using Coordinate = short unsigned;
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
};

#endif // HORSE_WALKER_HPP