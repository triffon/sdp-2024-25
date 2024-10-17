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
        top = new StackElement<T>{x, top};
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        StackElement<T>* toDelete = top;
        T result = top->data;
        top = top->next;
        delete toDelete;
        return result;
    } 

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        return top->data;
    }
};

#endif // LINKED_STACK_HPP