#ifndef STACK_HORSE_WALKER_HPP
#define STACK_HORSE_WALKER_HPP
#include <cmath>
#include "horse_walker.hpp"
#include "linked_stack.hpp"

class StackHorseWalker : public HorseWalker {
private:
    Walk currentWalk;
    using StackFrame = LinkedStack<Position>;
    LinkedStack<StackFrame> stack;

public:
    StackHorseWalker(size_t boardSize) : HorseWalker(boardSize) {}

    Walk walk(Position const& start, Position const& end) {
        StackFrame initialFrame;
        initialFrame.push(start);
        stack.push(initialFrame);

        while (!stack.empty()) {
            StackFrame& currentFrame = stack.peek();
            if (!currentFrame.empty()) {
                Position current = currentFrame.pop();

                // std::clog << "Пробваме да стъпим на " << current << std::endl;

                // проверка дали не сме в лошата база
                if (insideBoard(current) && !board[current.first][current.second]) {
                    // стъпка напред
                    // std::clog << "Стъпваме на " << current << std::endl;
                    board[current.first][current.second] = true;
                    currentWalk.push_back(current);

                    // добра база
                    if (current == end) {
                        // std::clog << "Намерихме разходка " << currentWalk;
                        return currentWalk;
                    }

                    StackFrame newFrame;

                    // опит за всички възможни ходове на коня
                    for (int i = -2; i <= 2; i++)
                        for (int j = -2; j <= 2; j++)
                            if (i && j && std::abs(i) != std::abs(j)) {
                                Position next = {current.first + i, current.second + j};
                                // std::clog << "Ще пробваме да стъпим на " << next << std::endl;
                                newFrame.push(next);
                            }

                    stack.push(newFrame);
                }
            } else {
                // std::clog << "Стъпка назад!" << std::endl;
                // стъпка назад
                currentWalk.pop_back();
                // махаме празната рамка от стека
                stack.pop();
            }
        }

        return Walk();
    }

    Walk walkAvoidingPositions(Position const& start, Position const& end, 
                            const std::vector<Position>& forbidden) {
        // Reset the board
        for (size_t i = 0; i < board.size(); ++i)
            for (size_t j = 0; j < board[i].size(); ++j)
                board[i][j] = false;
        
        // Mark forbidden positions as visited
        for (const auto& pos : forbidden) {
            if (insideBoard(pos)) {
                board[pos.first][pos.second] = true;
            }
        }
        
        // Check if start or end positions are forbidden
        if (std::find(forbidden.begin(), forbidden.end(), start) != forbidden.end() ||
            std::find(forbidden.begin(), forbidden.end(), end) != forbidden.end()) {
            return Walk();
        }
        
        // Reset forbidden status for start and end if they were marked
        board[start.first][start.second] = false;
        
        // Initialize stack with start position
        currentWalk.clear();
        LinkedStack<Position> posStack;
        posStack.push(start);
        
        while (!posStack.empty()) {
            Position current = posStack.peek();
            
            // Mark current position as visited
            board[current.first][current.second] = true;
            currentWalk.push_back(current);
            
            // If we've reached the end, return the walk
            if (current == end) {
                return currentWalk;
            }
            
            // Flag to track if we found any valid next move
            bool foundNextMove = false;
            
            // Try all possible knight moves
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    if (i != 0 && j != 0 && std::abs(i) != std::abs(j)) {
                        Position next = {current.first + i, current.second + j};
                        if (insideBoard(next) && !board[next.first][next.second]) {
                            // Found a valid move, add to stack and process it next
                            posStack.push(next);
                            foundNextMove = true;
                            break;
                        }
                    }
                }
                if (foundNextMove) break;
            }
            
            // If no valid move was found, backtrack
            if (!foundNextMove) {
                posStack.pop();
                currentWalk.pop_back();
                
                // If we're not at the start position, mark the previous position as unvisited
                if (!currentWalk.empty()) {
                    board[current.first][current.second] = false;
                }
            }
        }
        
        // No path found
        return Walk();
    }
};

#endif // STACK_HORSE_WALKER_HPP