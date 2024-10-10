#ifndef SDP_STACK_STACK_HPP
#define SDP_STACK_STACK_HPP

#include <stdexcept>

/// @brief Клас за структурата от данни Стек
/// Темплетйтни стойности:
/// Т - типа на променливата, която искаме да пазим в стека
///
template <typename T>
class Stack {
public:
    // максимален брой елементи в стека
    static const size_t MAX = 100;

    // означение, че стекът е празен
    static const size_t EMPTY_STACK = 0;

private:
    // елементите на стека
    T data[MAX];

    // индекс на върха на стека
    size_t number_of_elements;

    bool full() const {
        return number_of_elements == MAX;
    }
public:
    Stack() : number_of_elements(EMPTY_STACK) {}

    // проверка дали стек е празен
    bool empty() const {
        return number_of_elements == EMPTY_STACK;
    }

    // включване на елемент в стек
    void push(T const& x) {
        if (full())
            throw std::runtime_error("Опит за включване в пълен стек");
        data[number_of_elements++] = x;
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        return data[--number_of_elements];
     }

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        return data[number_of_elements];
     }
};

#endif