#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

template <typename T>
struct StackElement {
    T data;
    StackElement* next;
};

template <typename T>
class LinkedStack {
private:
    // указател към върха на стека
    StackElement<T>* top;
public:

    LinkedStack() : top(nullptr) {}

    // проверка дали стек е празен
    bool empty() const {
        return top == nullptr;
    }

    // включване на елемент в стек
    void push(T const& x) {
/*         if (full())
            throw std::runtime_error("Опит за включване в пълен стек");
        data[++top] = x; */
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        /* return data[top--]; */
    } 

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        // return data[top];
    }
};

#endif // LINKED_STACK_HPP