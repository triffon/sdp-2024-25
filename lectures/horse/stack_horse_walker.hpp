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
};

#endif // STACK_HORSE_WALKER_HPP