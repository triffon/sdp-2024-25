#include <stdexcept>

template <typename T>
class Stack {
public:
    // максимален брой елементи в стека
    static const size_t MAX = 100;

    // означение, че стекът е празен
    static const int EMPTY_STACK = -1;

private:
    // елементите на стека
    T data[MAX];
    // индекс на върха на стека
    int top;
public:
    Stack() : top(EMPTY_STACK) {}

    // проверка дали стек е празен
    bool empty() const {
        return top == EMPTY_STACK;
    }

    // включване на елемент в стек
    void push(T const& x) {
        data[++top] = x;
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        return data[top--];
     }

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        return data[top];
     }
};